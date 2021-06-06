<?php
if(isset($_POST['bequipe']))
{
	$eq=$_POST['equipe1'];
	$eq2=$_POST['equipe2'];
	if($eq!=$eq2)
	{
	$requete='insert into party(winer,IDDa,IDDi,IDEq,IDEq_team) values("0",1,1,'.$eq.','.$eq2.');';
	$connexion->query($requete);
	$lastId=$connexion->insert_id;
	$parcourt=$connexion->query('select count(IDMo) from appartienta where IDEq='.$eq.';');
	$parcourt2=mysqli_fetch_array($parcourt);
	$parcourt3=$connexion->query('select IDMo from appartienta where IDEq='.$eq.';');
	$parcourt4=mysqli_fetch_all($parcourt3);
	$g=0;
	for($i=0;$i<$parcourt2[0];$i++)
	{
		$save1=$connexion->query('select IDMo,life,mana,attack from archery where IDMo='.$parcourt4[$i][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq.' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/pap_ar.jpg" where IDMo='.$save[0].';');
		}
		$save1=$connexion->query('select IDMo,life,mana,attack from sorcerer where IDMo='.$parcourt4[$i][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq.' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/pap_sor.jpg" where IDMo='.$save[0].';');
		}
		$save1=$connexion->query('select IDMo,life,mana,attack,proba from knight where IDMo='.$parcourt4[$i][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq.',proba='.$save[4].' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/pap_kn.jpg" where IDMo='.$save[0].';');
		}
		$g=$g+1;
	}
	$parcourt=$connexion->query('select count(IDMo) from appartienta where IDEq='.$eq2.';');
	echo 'select count(IDMo) from appartienta where IDEq='.$eq2.';';
	$parcourt2=mysqli_fetch_array($parcourt);
	$parcourt3=$connexion->query('select IDMo from appartienta where IDEq='.$eq2.';');
	$parcourt4=mysqli_fetch_all($parcourt3);
	for($i=$g;$i<$g+$parcourt2[0];$i++)
	{
		$save1=$connexion->query('select IDMo,life,mana,attack from archery where IDMo='.$parcourt4[$i-$g][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq2.' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/sca_ar.jpg" where IDMo='.$save[0].';');
		}
		$save1=$connexion->query('select IDMo,life,mana,attack from sorcerer where IDMo='.$parcourt4[$i-$g][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq2.' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/sca_sor.jpg" where IDMo='.$save[0].';');
		}
		$save1=$connexion->query('select IDMo,life,mana,attack,proba from knight where IDMo='.$parcourt4[$i-$g][0].';');
		$save=mysqli_fetch_array($save1);
		if($save[0]!=null){
		$connexion->query('update sauvegarde set IDMo='.$save[0].',life='.$save[1].',mana='.$save[2].',attack='.$save[3].',IDEq='.$eq2.',proba='.$save[4].' where IDsauvegarde='.($i+1).';');
		$connexion->query('update morpion set icone="./img/sca_kn.jpg" where IDMo='.$save[0].';');
		}
		
	}
	$rand=rand(0,1);
	$connexion->query('update jeu set verifjo='.$rand.';');
	 if(isset($_POST['equipe1']) && trim($_POST['equipe1']) != '') {
	 		$equipe=$_POST['equipe1'];
	 }
	$requete='update jeu set verifeq=1,party='.$lastId.';';
	$connexion->query($requete);
	}
	else{echo '<h1 style="color:#FF0000";>vous ne pouvez choisir deux fois la même équipe </h1>';}
}
$equipe='select verifeq from jeu';
$equipe1=$connexion->query($equipe);
$equipe2=mysqli_fetch_array($equipe1);
if($equipe2[0]==1)
{
  $joueur='select verifjo from jeu';
  $joueur1=$connexion->query($joueur);
  $joueur2=mysqli_fetch_array($joueur1);
  if($joueur2[0]==0)
  {
	 $req=mysqli_fetch_all($connexion->query('select IDEq from matrice where IDpos<=9;'));
		for ($i=0;$i<9;$i=$i+3)
		{
			if($req[$i][0]!=0)
			{				
			if($req[$i][0]==$req[$i+1][0] && $req[$i][0]==$req[$i+2][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[$i][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
			}
		}
		for ($i=0;$i<3;$i++)
		{
			if ($req[$i][0]!=0)
			{
			if($req[$i][0]==$req[$i+3][0] && $req[$i][0]==$req[$i+6][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[$i][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}
		}
		if ($req[0][0]!=0)
		{
		if($req[0][0]==$req[4][0] && $req[0][0]==$req[8][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[0][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}
		if ($req[2][0]!=0)
		{
		if($req[2][0]==$req[4][0] && $req[2][0]==$req[6][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[2][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}	
		$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDEq in(select IDEq_team from party where IDPa in(select party from jeu));'));
		$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from sauvegarde where IDEq in(select IDEq_team from party where IDPa in(select party from jeu));'));
		if($req[0]==0 && $req1[0]==0)
		{
					$req2=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa in(select party from jeu);'));
					$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req2[0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php }
	if(isset($_POST['baction']))
	{
	 		if($_POST['action']=='action1')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDMo!=0;'));
				$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from sauvegarde where IDeq in(select IDEq from party where IDpa in (select party from jeu));'));
				if($req[0]<9 )
				if ($req1[0]!=0)
				{
				{
				$requete='update jeu set verifac=0';
				$connexion->query($requete);
				}
				}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez plus poser de morpions vous n en avez plus</h1>';}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez plus poser de morpions la grille est pleine</h1>';}
			}
			if($_POST['action']=='action2')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq in(select IDEq from party where IDpa in (select party from jeu));'));
				if ($req[0]!=0)
				{
				$requete='update jeu set verifac=1';
				$connexion->query($requete);
				}
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer sans avoir de morpion sur la grille </h1>';}
			}
			if($_POST['action']=='action3')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq in(select IDEq from party where IDpa in (select party from jeu)) and IDMo in (select IDMo from sorcerer);'));
				if ($req[0]!=0)
				{
				$requete='update jeu set verifac=2';
				$connexion->query($requete);
				}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas lancer de sort sans sorcier </h1>';}
			}
}
    $action='select verifac from jeu';
    $action1=$connexion->query($action);
    $action2=mysqli_fetch_array($action1);
    if($action2[0]==0)
    { 
		$z=1;
		if(isset($_POST['bposer']))
		{
			$test5=mysqli_fetch_array($connexion->query('select party from jeu;'));
			$test1=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['action'].' and IDMo!=0;'));
			if($test1[0]==null)
			{
				$morp=$_POST['poser'];
				$test=$connexion->query('select * from archery where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq_team from appartienta inner join party on party.IDEq_team=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[4].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[2].', mana='.$test1[3].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				}
				$test=$connexion->query('select * from sorcerer where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq_team from appartienta inner join party on party.IDEq_team=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[4].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[2].', mana='.$test1[3].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				}
				$test=$connexion->query('select * from knight where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq_team from appartienta inner join party on party.IDEq_team=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[5].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[3].', mana='.$test1[2].', proba='.$test1[4].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				}
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq_team from appartienta inner join party on party.IDEq_team=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].';'));
				$connexion->query('update sauvegarde set IDMo=0,life=0,mana=0,attack=0,IDEq=0,proba=0 where IDMo='.$morp.' and IDEq='.$test3[0].';');
				$requete='update jeu set verifac=3';
				$connexion->query($requete);
				$connexion->query('update jeu set verifjo=1;');
				?>
				<fieldset style="border:solid 1px black; padding:20px; width:60%;">
				<h3> passer au prochain tour</h3> 
				<form name="formcreation" method="post" action="index.php?page=3X3.php">
				<table width="100%">
				<tr style="text-align:center;">
				<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="btest" value="next"></td>
				</tr></table>
				</form>
				</fieldset>
				<?php
				$z=0;
			}
			else { echo '<h3> vous ne pouvez pas poser la , choisissez une autre coordonnée</h3>';}
		}
		if($z==1){
	?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix de la ncase ou poser le morpion</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idposer">choix de la position ou vous posez le morpion</label></td>
			<td>
			<select name="action" id="idposer">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idposer">choix du morpion à poser</label></td>
			<td>
			<select name="poser" id="idposer">;
			<?php $requete=$connexion->query('select count(IDMO) from appartienta where IDEq in (select IDEq_team from party where IDPa=(select party from jeu));');
			$requete2=mysqli_fetch_array($requete);
			$requete3=$connexion->query('select IDsauvegarde,IDMo,life,mana,attack from sauvegarde where IDEq in (select IDEq_team from party where IDPa=(select party from jeu));');
			$requete4=mysqli_fetch_all($requete3);
			for($i=0;$i<$requete2[0];$i++)
			{
				if ($requete4[$i][1]!=0)
				{
					echo '<option value='.$requete4[$i][1].'> morpion '.$requete4[$i][1].' vie : '.$requete4[$i][2].' , mana : '.$requete4[$i][3].', attaque : '.$requete4[$i][4].'</option>';
				}
			} ?>
			</select>
			</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bposer" value="poser"></td>
		</tr></table>
		</form>
	</fieldset>
		<?php }}
    if($action2[0]==1)
    {   
	$z=0;
		if(isset($_POST['battaque']))
		{
		$sel=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['attaquant'].';'));
		if($sel[0]!=0 || $sel[0]!=-1)
		{
			$sel2=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['attaquant'].';'));
			$sel3=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa=(select party from jeu);'));
			$sel5=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['case'].';'));
			if($sel2[0]==$sel3[0])
			{
			if($sel5[0]!=$sel2[0])
			{
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from knight where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
				if($_POST['case']==($_POST['attaquant']+1) || $_POST['case']==($_POST['attaquant']-1) || $_POST['case']==($_POST['attaquant']+3) || $_POST['case']==($_POST['attaquant']-3))
				{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice where IDpos='.$_POST['attaquant'].';'));
					$req2=mysqli_fetch_array($connexion->query('select proba from matrice where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$crit=rand(1,100);
					if ($crit<=$req2[0])
					{
						$connexion->query('update matrice set life='.$req1[0].'-(2*'.$req[0].') where IDpos='.$_POST['case'].';');
					}
					else{$connexion->query('update matrice set life='.$req1[0].'-'.$req[0].' where IDpos='.$_POST['case'].';');}
					if ($req2[0]<30)
					{
						$connexion->query('update matrice set proba='.$req2[0].'+5 where IDpos='.$_POST['attaquant'].';');
					}
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=1;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
				}
				else{echo '<h1 style="color:#FF0000";>un guerrier ne peut pas attaquer a plus d une case de sa position </h1>';}
			}
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from sorcerer where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
				if($_POST['case']==($_POST['attaquant']+1) || $_POST['case']==($_POST['attaquant']-1) || $_POST['case']==($_POST['attaquant']+3) || $_POST['case']==($_POST['attaquant']-3))
				{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice  where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$connexion->query('update matrice set life='.$req1[0].'-'.$req[0].' where IDpos='.$_POST['case'].';');
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=1;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
				}
				else{echo '<h1 style="color:#FF0000";>un sorcier ne peut pas attaquer a plus d une case de sa position </h1>';}
			}
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from archery where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice  where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$connexion->query('update matrice set life='.$req1[0].'-'.$req[0].' where IDpos='.$_POST['case'].';');
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=1;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
			}
			}
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer un de vos allié </h1>';}
			}	
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer avec un morpion qui n est pas a vous </h1>';}
		}
		else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer avec une case vide ou innexistante</h1>';}
		}
		if(!$z)
		{
		?>
		<fieldset style="border:solid 1px black; padding:20px; width:60%;">
		<h3> choix de la ncase ou attaquer</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="icase">choix de la ncase</label></td>
			<td>
			<select name="case" id="icase">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
		<tr>
			<td><label style="font-weight:bold" for="idattaquant">choix de la position de l attaquant</label></td>
			<td>
			<select name="attaquant" id="idattaquant">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="battaque" value="attaque"></td>
		</tr></table>
		</form>
	</fieldset>
    <?php
		}}
    if($action2[0]==2)
	{	$suivant=0;
		if(isset($_POST['bsort']))
		{	
			
			$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
			$req0=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));'));
			if ($req[0]<=$req0[0])
			{
				if($_POST['sort']==1)
				{
					$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa in (select party from jeu);'));
					echo 'select IDEq_team from party and IDPa in (select party from jeu);';
					if($req[0]!=$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=0 && $req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));'));
						$connexion->query('update matrice set mana='.$req1[0].'-'.$req[0].' where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));');
						$req=mysqli_fetch_array($connexion->query('select power from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['pos'].';'));
						$connexion->query('update matrice set life=('.$req1[0].'-'.$req[0].') where IDpos='.$_POST['pos'].';');
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['pos'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['pos'].';');
							}
							$connexion->query('update jeu set verifjo=1;');
							$connexion->query('update jeu set verifac=3;');
							$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php	
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer une case vide ou innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer vos propre morpion</h1>';}
				}
				if($_POST['sort']==2)
				{
					$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa in (select party from jeu);'));
					if($req[0]==$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=0 && $req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));'));
						$connexion->query('update matrice set mana= ('.$req1[0].'-'.$req[0].') where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));');
						$req=mysqli_fetch_array($connexion->query('select power from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDMo='.$_POST['pos'].';'));
						$connexion->query('update matrice set life=('.$req1[0].'+'.$req[0].') where IDpos='.$_POST['pos'].';');
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['pos'].';'));
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from archery where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].');'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from archery where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].');'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from sorcerer where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].')'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from sorcerer where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].');'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from knight where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].');'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from knight where IDMo in (select IDMo from matrice where IDpos='.$_POST['pos'].');'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
							$connexion->query('update jeu set verifjo=1;');
							$connexion->query('update jeu set verifac=3;');
							$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas soigner une case vide ou innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas soigner les morpions adverses morpion</h1>';}
				}
				if($_POST['sort']==3)
				{
						$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa in (select party from jeu);'));
					if($req[0]!=$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));'));
						$connexion->query('update matrice set mana=('.$req1[0].'-'.$req[0].') where IDMo='.$_POST['case'].' and IDEq in (select IDEq_team from party where IDPa in (select party from jeu));');
						$connexion->query('update matrice set IDMo=-1,icone="./img/interdit.png",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['pos'].';');
						$connexion->query('update jeu set verifjo=1;');
						$connexion->query('update jeu set verifac=3;');
						$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas detruire une case innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas detruire vos propre morpion</h1>';}
				}
			}
			else{echo '<h1 style="color:#FF0000";>vous n avez pas assez de mana pour lancer ce sort</h1>';
		}}
		if(!$suivant){
		?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix de la ncase ou lancer le nsort</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idpos">choix de la position de lancer du nsort</label></td>
			<td>
			<select name="pos" id="idpos">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
			<tr>
			<td><label style="font-weight:bold" for="iattaquant">choix de la position du sorcier</label></td>
			<td>
			<?php
			$req=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa in (select party from jeu);'));
			$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq='.$req[0].' and IDMo in (select IDMo from sorcerer);'));
			$req0=mysqli_fetch_all($connexion->query('select IDMo,IDpos from matrice where IDeq='.$req[0].' and IDMo in (select IDMo from sorcerer);'));?>
			<select name="case" id="idcase">;
			<?php for ($i=0;$i<$req[0];$i++)
			{
			echo '<option value='.$req0[$i][0].'>'.$req0[$i][1].'</option>';}?>
			</select>
			</td>
			</tr>
			<tr>
			<td><label style="font-weight:bold" for="idsort">choix du sort</label></td>
			<td>
			<select name="sort" id="idsort">;
			<option value=1>boule de feu</option>
			<option value=2>soin</option>
			<option value=3>armageddon</option>
			</select>
			</td>
			</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsort" value="action"></td>
		</tr></table>
		</form>
	</fieldset>
    <?php 
	}}
	if($action2[0]==3){?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix des actions</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idaction">choix de votre action</label></td>
			<td>
			<select name="action" id="idaction">;
			<option value='action1'>poser morpion</option>
			<option value='action2'>attaquer</option>
			<option value='action3'>lancersort</option>;}
			</select>
			</td>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="baction" value="action"></td>
		</tr>
		</tr></table>
		</form>
	</fieldset>
 <?php 
  }
 }
  else{if($joueur2[0]==1)
  {
	  $req=mysqli_fetch_all($connexion->query('select IDEq from matrice where IDpos<=9;'));
		for ($i=0;$i<9;$i=$i+3)
		{
			if($req[$i][0]!=0)
			{				
			if($req[$i][0]==$req[$i+1][0] && $req[$i][0]==$req[$i+2][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[$i][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
			}
		}
		for ($i=0;$i<3;$i++)
		{
			if ($req[$i][0]!=0)
			{
			if($req[$i][0]==$req[$i+3][0] && $req[$i][0]==$req[$i+6][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[$i][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}
		}
		if ($req[0][0]!=0)
		{
		if($req[0][0]==$req[4][0] && $req[0][0]==$req[8][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[0][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}
		if ($req[2][0]!=0)
		{
		if($req[2][0]==$req[4][0] && $req[2][0]==$req[6][0])
			{
				$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr>
					</tr>
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req[2][0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php 
			}
		}
		$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDEq in(select IDEq from party where IDPa in(select party from jeu));'));
		$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from sauvegarde where IDEq in(select IDEq from party where IDPa in(select party from jeu));'));
		if($req[0]==0 && $req1[0]==0)
		{
					$req2=mysqli_fetch_array($connexion->query('select IDEq_team from party where IDPa in(select party from jeu));'));
					$connexion->query('update jeu set verifjo=3;');?>
					<fieldset style="border:solid 1px black; padding:20px; width:60%;">
					<h3> fin de la partie</h3> 
					<form name="formcreation" method="post" action="index.php?page=3X3.php">
					<table width="100%">
					<tr style="text-align:center;">
					<?php echo '<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bfin2" value="'.$req2[0].'"></td>';?>
					</tr></table>
					</form>
					</fieldset>
				<?php }
	if(isset($_POST['baction']))
	{
	 		if($_POST['action']=='action1')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDMo!=0;'));
				$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from sauvegarde where IDeq in(select IDEq from party where IDpa in (select party from jeu));'));
				if($req[0]<9 )
				if ($req1[0]!=0)
				{
				{
				$requete='update jeu set verifac=0';
				$connexion->query($requete);
				}
				}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez plus poser de morpions vous n en avez plus</h1>';}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez plus poser de morpions la grille est pleine</h1>';}
			}
			if($_POST['action']=='action2')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq in(select IDEq from party where IDpa in (select party from jeu));'));
				if ($req[0]!=0)
				{
				$requete='update jeu set verifac=1';
				$connexion->query($requete);
				}
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer sans avoir de morpion sur la grille </h1>';}
			}
			if($_POST['action']=='action3')
			{
				$req=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq in(select IDEq from party where IDpa in (select party from jeu)) and IDMo in (select IDMo from sorcerer);'));
				if ($req[0]!=0)
				{
				$requete='update jeu set verifac=2';
				$connexion->query($requete);
				}
				else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas lancer de sort sans sorcier </h1>';}
			}
}
    $action='select verifac from jeu';
    $action1=$connexion->query($action);
    $action2=mysqli_fetch_array($action1);
    if($action2[0]==0)	
    {	$z=1;
		if(isset($_POST['bposer']))
		{
		$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['action'].';'));
		if($req[0]!=(-1))
		{
			$test5=mysqli_fetch_array($connexion->query('select party from jeu'));
			$test1=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['action'].' and IDMo!=0'));
			if($test1[0]==null)
			{
				$morp=$_POST['poser'];
				$test=$connexion->query('select * from archery where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq from appartienta inner join party on party.IDEq=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[4].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[2].', mana='.$test1[3].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				}
				$test=$connexion->query('select * from sorcerer where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq from appartienta inner join party on party.IDEq=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[4].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[2].', mana='.$test1[3].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				$test=$connexion->query('select * from knight where IDMO='.$morp.';');
				$test1=mysqli_fetch_array($test);}
				if($test)
				{
				$test2=mysqli_fetch_array($connexion->query('select icone from morpion where IDMO='.$morp.';'));
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq from appartienta inner join party on party.IDEq=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update matrice set IDMO='.$test1[5].',icone=\''.$test2[0].'\',life='.$test1[1].',attack='.$test1[3].', mana='.$test1[2].', proba='.$test1[4].', IDEq='.$test3[0].' where IDpos='.$_POST['action'].';');
				}
				$requete='update jeu set verifac=3';
				$connexion->query($requete);
				$connexion->query('update jeu set verifjo=0;');
				$test3=mysqli_fetch_array($connexion->query('select party.IDEq from appartienta inner join party on party.IDEq=appartienta.IDEq where IDMO='.$morp.' and IDPa='.$test5[0].' ;'));
				$connexion->query('update sauvegarde set IDMo=0,life=0,mana=0,attack=0,IDEq=0,proba=0 where IDMo='.$morp.' and IDEq='.$test3[0].';');
				$z=0;
				?>
				<fieldset style="border:solid 1px black; padding:20px; width:60%;">
				<h3> passer au prochain tour</h3> 
				<form name="formcreation" method="post" action="index.php?page=3X3.php">
				<table width="100%">
				<tr style="text-align:center;">
				<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
				</tr></table>
				</form>
				</fieldset>
				<?php
			}
			else { echo '<h3> vous ne pouvez pas poser la , choisissez une autre coordonnée</h3>';}
		}else { echo '<h3> vous ne pouvez pas poser sur une case détruite , choisissez une autre coordonnée</h3>';}}
	if($z==1){
?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix de la ncase ou poser le morpion</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idaction">choix de votre action</label></td>
			<td>
			<select name="action" id="idaction">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
			<tr>
			<td><label style="font-weight:bold" for="idposer">choix du morpion à poser</label></td>
			<td>
			<?php 
			$requete=$connexion->query('select count(IDMO) from appartienta where IDEq in (select IDEq from party where IDPa in (select party from jeu));');
			$requete2=mysqli_fetch_array($requete);
			$requete3=$connexion->query('select IDsauvegarde,IDMo,life,mana,attack from sauvegarde where IDEq in (select IDEq from party where IDPa=(select party from jeu));');
			$requete4=mysqli_fetch_all($requete3);
			echo '<select name="poser" id="idposer">;';
			for($i=0;$i<$requete2[0];$i++)
			{
				if ($requete4[$i][1]!=0)
				{
					echo '<option value='.$requete4[$i][1].'> morpion '.$requete4[$i][1].' vie : '.$requete4[$i][2].' , mana : '.$requete4[$i][3].', attaque : '.$requete4[$i][4].'</option>';
				}
			} 
			echo '</select>'
			?>
			</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bposer" value="poser"></td>
		</tr></table>
		</form>
	</fieldset>
    <?php }}
    if($action2[0]==1)
    { $z=0;
		if(isset($_POST['battaque']))
		{
		$sel=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['attaquant'].';'));
		if($sel[0]!=0 || $sel[0]!=-1)
		{
			$sel2=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['attaquant'].';'));
			$sel3=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa=(select party from jeu);'));
			$sel5=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['case'].';'));
			if($sel2[0]==$sel3[0])
			{
			if($sel5[0]!=$sel2[0])
			{
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from knight where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
				if($_POST['case']==($_POST['attaquant']+1) || $_POST['case']==($_POST['attaquant']-1) || $_POST['case']==($_POST['attaquant']+3) || $_POST['case']==($_POST['attaquant']-3))
				{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$req2=mysqli_fetch_array($connexion->query('select proba from matrice where IDpos='.$_POST['attaquant'].';'));
					$crit=rand(1,100);
					if ($crit<=$req2[0])
					{
						$connexion->query('update matrice set life='.$req1[0].'-(2*'.$req[0].') where IDpos='.$_POST['case'].';');
					}
					else{$connexion->query('update matrice set life='.$req1[0].'-'.$req[0].' where IDpos='.$_POST['case'].';');}
					if ($req2[0]<30)
					{
						$connexion->query('update matrice set proba='.$req2[0].'+5 where IDpos='.$_POST['attaquant'].';');
					}
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=0;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
				}
				else{echo '<h1 style="color:#FF0000";>un guerrier ne peut pas attaquer a plus d une case de sa position </h1>';}
			}
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from sorcerer where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
				if($_POST['case']==($_POST['attaquant']+1) || $_POST['case']==($_POST['attaquant']-1) || $_POST['case']==($_POST['attaquant']+3) || $_POST['case']==($_POST['attaquant']-3))
				{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice  where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$connexion->query('update matrice set life=('.$req1[0].'-'.$req[0].') where IDpos='.$_POST['case'].';');
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=0;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
				}
				else{echo '<h1 style="color:#FF0000";>un sorcier ne peut pas attaquer a plus d une case de sa position </h1>';}
			}
			$sel1=mysqli_fetch_array($connexion->query('select count(IDMo) from archery where IDMo='.$sel[0].';'));
			if($sel1[0]==1)
			{
					$req=mysqli_fetch_array($connexion->query('select attack from matrice  where IDpos='.$_POST['attaquant'].';'));
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
					$connexion->query('update matrice set life='.$req1[0].'-'.$req[0].' where IDpos='.$_POST['case'].';');
					$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDpos='.$_POST['case'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['case'].';');
							}
							$connexion->query('update jeu set verifjo=0;');
							$connexion->query('update jeu set verifac=3;');
							$z=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
					<?php
			}
			}
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer un de vos allié </h1>';}
			}	
			else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer avec un morpion qui n est pas a vous </h1>';}
		}
		else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer avec une case vide ou innexistante</h1>';}
		}
		if(!$z)
		{
	?>
		<fieldset style="border:solid 1px black; padding:20px; width:60%;">
		<h3> choix de la ncase ou attaquer</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="icase">choix de la ncase</label></td>
			<td>
			<select name="case" id="icase">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
		<tr>
			<td><label style="font-weight:bold" for="idattaquant">choix de la position de l attaquant</label></td>
			<td>
			<select name="attaquant" id="idattaquant">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="battaque" value="attaque"></td>
		</tr></table>
		</form>
	</fieldset>
    <?php
		}}
    if($action2[0]==2)
    {
		$suivant=0;
		if(isset($_POST['bsort']))
		{	
			
			$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
			$req0=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));'));
			if ($req[0]<=$req0[0])
			{
				if($_POST['sort']==1)
				{
					$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa in (select party from jeu);'));
					if($req[0]!=$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=0 && $req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));'));
						$connexion->query('update sorcerer set mana=('.$req1[0].'-'.$req[0].') where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));');
						$req=mysqli_fetch_array($connexion->query('select power from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDMo='.$_POST['pos'].';'));
						$connexion->query('update matrice set mana=('.$req1[0].'-4) where IDMo='.$_POST['pos'].';');
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDMo='.$_POST['pos'].';'));
						if($req1[0]<=0)
							{
								$connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['pos'].';');
							}
							$connexion->query('update jeu set verifjo=0;');
							$connexion->query('update jeu set verifac=3;');
							$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php	
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer une case vide ou innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas attaquer vos propre morpion</h1>';}
				}
				if($_POST['sort']==2)
				{
					$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa in (select party from jeu);'));
					if($req[0]==$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=0 && $req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));'));
						$connexion->query('update sorcerer set mana=('.$req1[0].'-'.$req[0].') where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));');
						$req=mysqli_fetch_array($connexion->query('select power from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDMo='.$_POST['pos'].';'));
						$connexion->query('update matrice set mana=('.$req1[0].'+3) where IDMo='.$_POST['pos'].';');
						$req1=mysqli_fetch_array($connexion->query('select life from matrice where IDMo='.$_POST['pos'].';'));
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from archery where IDMo='.$_POST['pos'].';'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from archery where IDMo='.$_POST['pos'].';'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from sorcerer where IDMo='.$_POST['pos'].';'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from sorcerer where IDMo='.$_POST['pos'].';'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
						$type=mysqli_fetch_array($connexion->query('select count(IDMo) from knight where IDMo='.$_POST['pos'].';'));
						if($type[0]==1)
						{
						$req2=mysqli_fetch_array($connexion->query('select life from knight where IDMo='.$_POST['pos'].';'));
						if($req1[0]>=$req2[0])
							{
								$connexion->query('update matrice set life='.$req2[0].';');
							}
						}
							$connexion->query('update jeu set verifjo=0;');
							$connexion->query('update jeu set verifac=3;');
							$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas soigner une case vide ou innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas soigner les morpions adverses morpion</h1>';}
				}
				if($_POST['sort']==3)
				{
					$req=mysqli_fetch_array($connexion->query('select IDEq from matrice where IDpos='.$_POST['pos'].';'));
					$req1=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa in (select party from jeu);'));
					if($req[0]!=$req1[0])
					{
					$req=mysqli_fetch_array($connexion->query('select IDMo from matrice where IDpos='.$_POST['pos'].';'));
					if($req1[0]!=(-1))
					{
						$req=mysqli_fetch_array($connexion->query('select cost from sort where IDSt='.$_POST['sort'].';'));
						$req1=mysqli_fetch_array($connexion->query('select mana from matrice where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));'));
						$connexion->query('update matrice set mana=('.$req1[0].'-'.$req[0].') where IDMo='.$_POST['case'].' and IDEq in (select IDEq from party where IDPa in (select party from jeu));');
						$connexion->query('update matrice set IDMo=-1,icone="./img/interdit.png",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$_POST['pos'].';');
						$connexion->query('update jeu set verifjo=0;');
						$connexion->query('update jeu set verifac=3;');
						$suivant=1;
							?>
							<fieldset style="border:solid 1px black; padding:20px; width:60%;">
							<h3> passer au prochain tour</h3> 
							<form name="formcreation" method="post" action="index.php?page=3X3.php">
							<table width="100%">
							<tr style="text-align:center;">
							<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsuivant" value="next"></td>
							</tr></table>
							</form>
							</fieldset>
				<?php
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas detruire une case innexistante</h1>';}
					}
					else{echo '<h1 style="color:#FF0000";>vous ne pouvez pas detruire vos propre morpion</h1>';}
				}
			}
			else{echo '<h1 style="color:#FF0000";>vous n avez pas assez de mana pour lancer ce sort</h1>';
		}
		}
		if(!$suivant){
		?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix de la ncase ou lancer le nsort</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idpos">choix de la position de lancer du nsort</label></td>
			<td>
			<select name="pos" id="idpos">;
			<option value=1>1X1</option>
			<option value=2>1X2</option>
			<option value=3>1X3</option>
			<option value=4>2X1</option>
			<option value=5>2X2</option>
			<option value=6>2X3</option>
			<option value=7>3X1</option>
			<option value=8>3X2</option>
			<option value=9>3X3</option>
			</select>
			</td>
			</tr>
			<tr>
			<td><label style="font-weight:bold" for="iattaquant">choix de la position du sorcier</label></td>
			<td>
			<?php
			$req=mysqli_fetch_array($connexion->query('select IDEq from party where IDPa in (select party from jeu);'));
			$req1=mysqli_fetch_array($connexion->query('select count(IDMo) from matrice where IDeq='.$req[0].' and IDMo in (select IDMo from sorcerer);'));
			$req0=mysqli_fetch_all($connexion->query('select IDMo,IDpos from matrice where IDeq='.$req[0].' and IDMo in (select IDMo from sorcerer);'));
			?>
			<select name="case" id="idcase">;
			<?php for ($i=0;$i<$req[0];$i++)
			{
			echo '<option value='.$req0[$i][0].'>'.$req0[$i][1].'</option>';}?>
			</select>
			</td>
			</tr>
			<tr>
			<td><label style="font-weight:bold" for="idsort">choix du sort</label></td>
			<td>
			<select name="sort" id="idsort">;
			<option value=1>boule de feu</option>
			<option value=2>soin</option>
			<option value=3>armageddon</option>
			</select>
			</td>
			</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bsort" value="action"></td>
		</tr></table>
		</form>
	</fieldset>
    <?php 
	}}
	if($action2[0]==3){?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix des actions</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idaction">choix de votre action</label></td>
			<td>
			<select name="action" id="idaction">;
			<option value='action1'>poser morpion</option>
			<option value='action2'>attaquer</option>
			<option value='action3'>lancersort</option>;}
			</select>
			</td>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="baction" value="action"></td>
		</tr>
		</tr></table>
		</form>
	</fieldset>
	<?php }
  }
  else{if($joueur2[0]==2)
	  {
		  echo '<h2>pas de gagnant </h2>';
		  $connexion->query('update jeu set verifeq=0;');
		  $connexion->query('update jeu set party=0;');
		  $connexion->query('update jeu set verifac=3');
		  for($i=1;$i<=16;$i++)
		  {
			   $connexion->query('update sauvegarde set IDMo=0,life=0,mana=0,attack=0,IDEq=0,proba=0 where IDsauvegarde='.$i.';');
			   $connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$i.';');
		  }
	  }
	  else{
			$req=mysqli_fetch_array($connexion->query('select name from team where IDEq='.$_POST['bfin2'].';'));
			echo '<h2>l equipe '.$req[0].' gagne la partie</h2>';
		  $connexion->query('update jeu set verifeq=0;');
		  $connexion->query('update jeu set party=0;');
		  $connexion->query('update jeu set verifac=3');
		  for($i=1;$i<=16;$i++)
		  {
			   $connexion->query('update sauvegarde set IDMo=0,life=0,mana=0,attack=0,IDEq=0,proba=0 where IDsauvegarde='.$i.';');
			   $connexion->query('update matrice set IDMo=0,icone="icone",life=0,mana=0,attack=0,IDEq=0,proba=0 where IDpos='.$i.';');
		  }
	  }
  }
}}
else{
?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> choix des equipes</h3> 
		<form name="formcreation" method="post" action="index.php?page=3X3.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idequ1">choix de la premiere equipe</label></td>
			<td>
			<?php 
			$requete='select count(IDEq) from team;';
			$compter=mysqli_query($connexion,$requete);
			$compter2=mysqli_fetch_array($compter);
			echo '<select name="equipe1" id="idequ1">';
			for($i=0;$i<=$compter2[0];$i++){
			$requete='select IDEq, name from team where IDEq='.$i.';';
			$selection=$connexion->query($requete);
			$selection2=mysqli_fetch_array($selection);
			echo	'<option value='.$selection2[0].'>'.$selection2[1].'</option>';}
			echo '</select>';?>
			</td>
			<td><label style="font-weight:bold" for="idequ2">choix de la deuxieme equipe</label></td>
			<td>
			<?php 
			$requete='select count(IDEq) from team;';
			$compter=mysqli_query($connexion,$requete);
			$compter2=mysqli_fetch_array($compter);
			echo '<select name="equipe2" id="idequ2">';
			for($i=0;$i<=$compter2[0];$i++){
			$requete='select IDEq, name from team where IDEq='.$i.';';
			$selection1=$connexion->query($requete);
			$selection3=mysqli_fetch_array($selection1);
			echo	'<option value='.$selection3[0].'>'.$selection3[1].'</option>';}
			echo '</select>';?>
			</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bequipe" value="equipe"></td>
		</tr></table>
		</form>
	</fieldset>
<?php 
}
?>
<table id="table_2">
<tr>
<th class="thtrav"></th>
<td class="tdtrav"><img src="./img/un.png" width=150px height=150px /></td>
<td class="tdtrav"><img src="./img/deux.png" width=150px height=150px /></td>
<td class="tdtrav"><img src="./img/trois.png" width=150px height=150px /></td>
</tr>
<tr>
<th class="thtrav"><img src="./img/un.png" width=150px height=150px /></th>
<td class="tdtrav";><?php
$value=$connexion->query('select * from matrice where IDpos=1;');
$value1=mysqli_fetch_array($value);
$test2=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value1[7].';'));
$test3=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value1[1].';'));
echo '<a href="#"><img src="'.$value1[2].'" width=150px height=150px/><span>attaque : '.$value1[4].' , vie : '.$value1[3].' , mana : '.$value1[5].' , crit : '.$value1[6]. ' <br/>, equipe :'.$test2[0].' , morpion :'.$test3[0].'</span></a>';?></td>
<td class="tdtrav"><?php 
$value3=$connexion->query('select * from matrice where IDpos=2;');
$value2=mysqli_fetch_array($value3);
$test19=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value2[7].';'));
$test4=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value2[1].';'));
echo '<a href="#"><img src="'.$value2[2].'" width=150px height=150px/><span>attaque : '.$value2[4].' , vie : '.$value2[3].' , mana : '.$value2[5].' , crit : '.$value2[6].' <br/>, equipe :'.$test19[0].' , morpion :'.$test4[0].'</span></a>';?></td>
<td class="tdtrav"><?php 
$value4=$connexion->query('select * from matrice where IDpos=3;');
$value5=mysqli_fetch_array($value4);
$test5=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value5[7].';'));
$test6=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value5[1].';'));
echo '<a href="#"><img src="'.$value5[2].'" width=150px height=150px/><span>attaque : '.$value5[4].' , vie : '.$value5[3].' , mana : '.$value5[5].' , crit : '.$value5[6].' <br/>, equipe :'.$test5[0].' , morpion :'.$test6[0].'</span>';?></td></td>
</tr>
<tr>
<th class="thtrav"><img src="./img/deux.png" width=150px height=150px /></th>
<td class="tdtrav"><?php 
$value6=$connexion->query('select * from matrice where IDpos=4;');
$value7=mysqli_fetch_array($value6);
$test7=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value7[7].';'));
$test8=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value7[1].';'));
echo '<a href="#"><img src="'.$value7[2].'" width=150px height=150px/><span>attaque : '.$value7[4].' , vie : '.$value7[3].' , mana : '.$value7[5].' , crit : '.$value7[6].' <br/>, equipe :'.$test7[0].' , morpion :'.$test8[0].'</span></a>';?></td></td>
<td class="tdtrav"><?php 
$value8=$connexion->query('select * from matrice where IDpos=5;');
$value9=mysqli_fetch_array($value8);
$test9=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value9[7].';'));
$test10=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value9[1].';'));
echo '<a href="#"><img src="'.$value9[2].'" width=150px height=150px/><span>attaque : '.$value9[4].' , vie : '.$value9[3].' , mana : '.$value9[5].' , crit : '.$value9[6].' <br/>, equipe :'.$test9[0].' , morpion :'.$test10[0].'</span></a>';?></td></td>
<td class="tdtrav"><?php
$value10=$connexion->query('select * from matrice where IDpos=6;');
$value11=mysqli_fetch_array($value10);
$test11=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value11[7].';'));
$test12=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value11[1].';'));
echo '<a href="#"><img src="'.$value11[2].'" width=150px height=150px/><span>attaque : '.$value11[4].' , vie : '.$value11[3].' , mana : '.$value11[5].' , crit : '.$value11[6].' <br/>, equipe :'.$test11[0].' , morpion :'.$test12[0].'</span></a>';?></td>
<tr>
<th class="thtrav"><img src="./img/trois.png" width=150px height=150px /></th>
<td class="tdtrav"><?php 
$value12=$connexion->query('select * from matrice where IDpos=7;');
$value13=mysqli_fetch_array($value12);
$test13=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value13[7].';'));
$test14=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value13[1].';'));
echo '<a href="#"><img src="'.$value13[2].'" width=150px height=150px/><span>attaque : '.$value13[4].' , vie : '.$value13[3].' , mana : '.$value13[5].' , crit : '.$value13[6].' <br/>, equipe :'.$test13[0].' , morpion :'.$test14[0].'</span></a>';?></td>
<td class="tdtrav"><?php
$value14=$connexion->query('select * from matrice where IDpos=8;');
$value15=mysqli_fetch_array($value14);
$test15=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value15[7].';'));
$test16=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value15[1].';'));
echo '<a href="#"><img src="'.$value15[2].'" width=150px height=150px/><span>attaque : '.$value15[4].' , vie : '.$value15[3].' , mana : '.$value15[5].' , crit : '.$value15[6].' <br/>, equipe :'.$test15[0].' , morpion :'.$test16[0].'</span></a>';?></td>
<td class="tdtrav"><?php 
$value16=$connexion->query('select * from matrice where IDpos=9;');
$value17=mysqli_fetch_array($value16);
$test17=mysqli_fetch_array($connexion->query('select name,color from team where IDEq='.$value17[7].';'));
$test18=mysqli_fetch_array($connexion->query('select name from morpion where IDMo='.$value17[1].';'));
echo '<a href="#"><img src="'.$value17[2].'" width=150px height=150px/><span>attaque : '.$value17[4].' , vie : '.$value17[3].' , mana : '.$value17[5].' , crit : '.$value17[6].' <br/>, equipe :'.$test17[0].' , morpion :'.$test18[0].'</span></a>';?></td>
</tr>
</table>