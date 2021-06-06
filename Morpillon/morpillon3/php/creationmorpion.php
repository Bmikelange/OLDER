<?php 
$formulaireValide=0;
if(isset($_POST['bcreer']))
{
	if($_POST['classe']==1)
	{
		if($_POST['mana']==0)
		{
			if(($_POST['attack']+$_POST['vie'])==10)
			{
				$connexion->query('insert into morpion(`name`, `icone`, `IDCr`) values(\''.$_POST['morpion'].'\',\'./img/pap_kn.jpg\',0);');
				$morp=$connexion->insert_id;
				$id=mysqli_fetch_array($connexion->query('select count(IDKn) from knight;'));
				$connexion->query('insert into knight( IDkn,`life`, `attack`, `mana`, `proba` ,`IDMo`) values('.$id[0].'+1,'.$_POST['vie'].','.$_POST['attack'].',0,5,'.$morp.');');
				echo '<h2 style="color:#00FF00";>votre morpion à bien été créé</h2>';
				$formulaireValide=1;
			}
			else{echo '<h1 style="color:#FF0000";>les statistiques d un guerrier ne peuvent pas etre différentes de 10</h1>';}
		}
		else{echo '<h1 style="color:#FF0000";>un guerrier ne peut pas avoir ce nombre de mana</h1>';}
	}
	if($_POST['classe']==2)
	{
		if(($_POST['attack']+$_POST['vie']+$_POST['mana'])==10)
			{
				$connexion->query('insert into morpion(`name`, `icone`, `IDCr`) values(\''.$_POST['morpion'].'\',\'./img/pap_So.jpg\',0);');
				$morp=$connexion->insert_id;
				$id=mysqli_fetch_array($connexion->query('select count(IDSo) from sorcerer;'));
				$connexion->query('insert into sorcerer( IDSo,`life`, `attack`, `mana`, `IDMo`) values('.$id[0].'+1,'.$_POST['vie'].','.$_POST['attack'].','.$_POST['mana'].','.$morp.');');
				echo '<h2 style="color:#00FF00";>votre morpion à bien été créé</h2>';
				$formulaireValide=1;
			}
			else{echo '<h1 style="color:#FF0000";>les statistiques d un mage ne peuvent pas etre différentes de 10</h1>';}
	}
	if($_POST['classe']==3)
	{
		if($_POST['mana']==0)
		{
			if(($_POST['attack']+$_POST['vie'])==10)
			{
				$connexion->query('insert into morpion(`name`, `icone`, `IDCr`) values(\''.$_POST['morpion'].'\',\'./img/pap_Ar.jpg\',0);');
				$morp=$connexion->insert_id;
				$id=mysqli_fetch_array($connexion->query('select count(IDAr) from archery;'));
				$connexion->query('insert into archery( IDAr,`life`, `attack`, `mana`, `IDMo`) values('.$id[0].'+1,'.$_POST['vie'].','.$_POST['attack'].',0,'.$morp.');');
				echo '<h2 style="color:#00FF00";>votre morpion à bien été créé</h2>';
				$formulaireValide=1;
			}
			else{echo '<h1 style="color:#FF0000";>les statistiques d un archer ne peuvent pas etre différentes de 10</h1>';}
		}
		else{echo '<h1 style="color:#FF0000";>un archer ne peut pas avoir ce nombre de mana</h1>';}
	}
}
if(!$formulaireValide) {
?>
<h2>créez vos morpion </h2>
<h4>Il y a trois types de morpion : les guerriers, les mages et les archers.<br/>
	les morpions ont un nom et trois statistiques,l'attaque,la vie et le mana.<br/>
    Seuls les mages peuvent avoir du mana. Le total des caractéristiques de chaque morpion ne peut pas dépasser 10.<br/></h4>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=creationmorpion.php">
		<table width="100%">
		<td><p>le nom du morpion : <input type="text" name="morpion" /></p></td>
		<td><label style="font-weight:bold" for="idclasse"></label></td>
			<td>
			<p>classe :<select name="classe" id="idclasse">
				<option value=1>guerrier</option>
				<option value=2>mage</option>
				<option value=3>archer</option>
			</select></p>
			</td>
			<td><label style="font-weight:bold" for="idat"></label></td>
			<td>
			<p>attaque :<select name="attack" id="idat">
				<option value=1>1</option>
				<option value=2>2</option>
				<option value=3>3</option>
				<option value=4>4</option>
				<option value=5>5</option>
				<option value=6>6</option>
				<option value=7>7</option>
				<option value=8>8</option>
				<option value=9>9</option>
			</select></p>
			</td>
			<td><label style="font-weight:bold" for="idvi"></label></td>
			<td>
			<p>vie :<select name="vie" id="idvi">
				<option value=1>1</option>
				<option value=2>2</option>
				<option value=3>3</option>
				<option value=4>4</option>
				<option value=5>5</option>
				<option value=6>6</option>
				<option value=7>7</option>
				<option value=8>8</option>
				<option value=9>9</option>
			</select></p>
			</td>
			<td><label style="font-weight:bold" for="idma"></label></td>
			<td>
			<p>mana: <select name="mana" id="idma">
				<option value=0>0</option>
				<option value=1>1</option>
				<option value=2>2</option>
				<option value=3>3</option>
				<option value=4>4</option>
				<option value=5>5</option>
				<option value=6>6</option>
				<option value=7>7</option>
				<option value=8>8</option>
				<option value=9>9</option>
			</select></p>
			</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bcreer" value="Creer"></td>
		</tr></table>
		</form>
	</fieldset>
<?php
}
?>