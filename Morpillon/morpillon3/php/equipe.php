<h1>composer votre equipe(4 a 8 morpion)</h1>
<?php
$formulaireValide = FALSE;
if(isset($_POST['bcreer'])) {
	if(isset($_POST['color']) && trim($_POST['color']) != '') {
    if(isset($_POST['choix_guerrier'])){
      $choixGuerrier = $_POST['choix_guerrier'];
    }else{
      $choixGuerrier = array();
    }
    if(isset($_POST['choix_archer'])){
      $choixArcher = $_POST['choix_archer'];
    }else{
      $choixArcher = array();
    }
    if(isset($_POST['choix_sorcier'])){
      $choixSorcier = $_POST['choix_sorcier'];
    }else{
      $choixSorcier = array();
    }
    $tot = sizeof($choixSorcier) + sizeof($choixArcher) + sizeof($choixGuerrier);
	if($tot>8 or $tot<4)
	{
		echo '<h2> ERREUR !! tu ne peux pas selectionner ce nombre de morpion(4 a 8) </h2><br/>';
		$formulaireValide=False;
	}else{
		$nomequipe=$_POST['nameEq'];
		if (isset($couleur)) {
        $couleur = $_POST['color'];
      }else{
        $couleur = 'bleu';
      }
		$requete_date='insert into date(dates) values(curdate());';
		$test=$connexion->query($requete_date);
		$lastID = $connexion->insert_id;
		$requete= 'insert into team(name,color,IDDa) values(\''.$nomequipe.'\',\''.$couleur.'\','.$lastID.');';
		$connexion->query($requete);
        $lastId = $connexion->insert_id;
		for ($i=0;$i<sizeof($choixArcher);$i++){
		$requete='insert into appartienta() values('.$choixArcher[$i].','.$lastId.');';
		$connexion->query($requete);
	}
	for ($i=0;$i<sizeof($choixGuerrier);$i++){
		$requete='insert into appartienta() values('.$choixGuerrier[$i].','.$lastId.');';
		$connexion->query($requete);
	}
	for ($i=0;$i<sizeof($choixSorcier);$i++){
		$requete='insert into appartienta() values('.$choixSorcier[$i].','.$lastId.');';
		$connexion->query($requete);
	}
	echo 'votre  equipe à été créée, elle s appelle : '.$nomequipe.' elle est de couleur '.$couleur.' elle contient '.$tot.' morpions';
	$formulaireValide=true;
	}	
	}
}
if(isset($_POST['bcreeraleat'])){
	$choixmorpion=rand(4,8);
	$choixnom=rand(0,10);
	$choixcouleur=rand(0,5);
	$arraynom=array(
	"pierre",
	"pomme",
	"trust",
	"force",
	"pierrick",
	"pommick",
	"trustick",
	"forcick",
	"pommicku",
	"trusticku",
	"forcicku",
	);
	$arraycouleur=array(
	"rouge",
	"vert",
	"jaune",
	"bleu",
	"violet",
	"rose",
	);
	global $connexion;
	$requete_date='insert into date(dates) values(CURDATE());';
	$test=mysqli_query($connexion,$requete_date);
	$lastID=mysqli_insert_id($connexion);
	$requete_equipe='insert into team(name,color,IDDa) values(\''.$arraynom[$choixnom].'\',\''.$arraycouleur[$choixcouleur].'\','.$lastID.');';
	$test=mysqli_query($connexion,$requete_equipe);
	$lastID=mysqli_insert_id($connexion);
	$table	= mysqli_real_escape_string($connexion,'morpion');
	$requete=('select count(IDMo) from '.$table.';');
	$test=$connexion->query($requete);
	$test1=mysqli_fetch_array($test);
	for ($i=0;$i<$choixmorpion;$i++){
		$positionmorpion=rand(1,$test1[0]);
		echo 'on prends le morpion '.$positionmorpion.'<br/> ';
		$requete_morpion='insert into appartienta values('.$positionmorpion.','.$lastID.');';
		$test=$connexion->query($requete_morpion);
	}
	echo 'votre  equipe à été créée, elle s appelle : '.$arraynom[$choixnom].' elle est de couleur '.$arraycouleur[$choixcouleur].' elle contient '.$choixmorpion.' morpions ';
	$formulaireValide=true;
}	

if(!$formulaireValide) {
?>	
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> CREATION D'EQUIPE</h3> 
		<form name="formcreation" method="post" action="index.php?page=equipe.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idcolor">choix de la couleur</label></td>
			<td>
			<select name="color" id="idcolor">
				<option value="Sbleu">bleu</option>
				<option value="Sjaune">jaune</option>
				<option value="Srouge">rouge</option>
				<option value="Svert">vert</option>
				<option value="Snoir">noir</option>
				<option value="Srose">rose</option>
			</select>
			</td>
			<td><label style="font-weight:bold" for="idname">choix du nom</label></td>
			<td>
			<input name="nameEq" id="idname" type="text">
			</td>
		</tr>
		<tr>
		<td rowspan=2><label style="font-weight:bold">choix des morpions(PDV,PM,PA)</label></td>
		<td><label style="font-weight:bold">sorciers</label></td>
		<td><label style="font-weight:bold">archer</label></td>
		<td><label style="font-weight:bold">guerrier</label></td>
		</tr>
		<tr>
		<td>
		<?php 
		$table	= mysqli_real_escape_string($connexion,'morpion');
		$requete='select count(IDMo) from morpion natural join sorcerer ;';
		$compter=mysqli_query($connexion,$requete);
		$compter2=mysqli_fetch_array($compter);
		for ($i=1;$i<=$compter2[0];$i++)
		{
			$requete='select morpion.IDMo,name,life,mana,attack from morpion natural join sorcerer where sorcerer.IDSo='.$i.';';
			$verif=$connexion->query($requete);
			$verif2=mysqli_fetch_array($verif);
		echo '<div><a href="#"><INPUT type="checkbox" name="choix_sorcier[]" value=\''.$verif2[0].'\'>'.$verif2[1].' <span> vie : '.$verif2[2].' , mana : '.$verif2[3].', attaque : '.$verif2[4].'</span> </a> </div>';}?>
		</td>
		<td>
		<?php 
		$table	= mysqli_real_escape_string($connexion,'morpion');
		$requete='select count(IDMo) from morpion natural join archery;';
		$compter=mysqli_query($connexion,$requete);
		$compter2=mysqli_fetch_array($compter);
		for ($i=1;$i<=$compter2[0];$i++)
		{
			$requete='select morpion.IDMo,name,life,mana,attack from morpion natural join archery where archery.IDAr='.$i.';';
			$verif=$connexion->query($requete);
			$verif2=mysqli_fetch_array($verif);
		?>
		<?php echo '<div><a href="#"><INPUT type="checkbox" name="choix_archer[]" value=\''.$verif2[0].'\'>'.$verif2[1].' <span> vie : '.$verif2[2].' , mana : '.$verif2[3].', attaque : '.$verif2[4].'</span> </a> </div>';}?>
		</td>
		<td>
		<?php 
		$table	= mysqli_real_escape_string($connexion,'morpion');
		$requete='select count(IDMo) from morpion natural join knight;';
		$compter=mysqli_query($connexion,$requete);
		$compter2=mysqli_fetch_array($compter);
		for ($i=1;$i<=$compter2[0];$i++)
		{
			$requete='select morpion.IDMo, name,life,mana,attack from morpion natural join knight where knight.IDKn='.$i.';';
			$verif=$connexion->query($requete);
			$verif2=mysqli_fetch_array($verif);
		?>
		<?php echo '<div><a href="#"><INPUT type="checkbox" name="choix_guerrier[]" value=\''.$verif2[0].'\'>'.$verif2[1].' <span> vie : '.$verif2[2].' , mana : '.$verif2[3].', attaque : '.$verif2[4].'</span> </a></div>';}?>
		</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bcreer" value="creer"></td>
		</tr></table>
		</form>
	</fieldset>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<h3> CREATION D'EQUIPE ALEATOIRE</h3> 
	<form name="test" method="post" action="index.php?page=equipe.php">
	
	<input type="submit" style="font-variant: small-caps;" name="bcreeraleat" value="creer">
	</form>
	</fieldset>
	
<?php
}
?>