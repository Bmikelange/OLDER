<h1>choisissez le type de jeu dont vous voulez connaitre les règles ou les statistiques générales de jeu</h1>
<?php
$formulaireValide = FALSE;
if(isset($_POST['bRechercher'])) {
	if($_POST['champRech'] == 'classique3X3'){
		?>
		<h2> le morpion classique 3X3</h2>
		<h4>Jeu qui se joue sur un damier de 3 cases par 3 cases.<br/>
		A son  tour un joueur posera un de ses morpions sur une case vide.<br/>
		Le but est d'alligner trois morpions de son équipe.</h4>
<?php	
	}
	if($_POST['champRech'] == 'modifie3X3'){
		?>
		<h2> le morpion modifié 3X3</h2>
		<h4>Jeu qui se joue sur un damier de 3 cases par 3 cases.<br/>
		Il existe trois types de morpions: guerrier, archer et sorcier.<br/>
		Chaque morpion possède au moins deux carractériqtique, attack et life .<br/>
		Seuls les sorciers ont de la mana.le totale des caractéristiques est toujours égal à 10.<br/>
		A son  tour un joueur à le choix entre trois action poser un de ses morpions sur une case vide,<br/>
		attaquer un morpion adverse, ou lancer un sort avec un sorcier.<br/>
		Le but est d'alligner trois morpions de son équipe ou de tuer tout les morpions de son adversaires.</h4>
	<?php	
	}
	if($_POST['champRech'] == 'modifie4X4'){
		?>
		<h2> le morpion modifié 3X3</h2>
		<h4>Jeu qui se joue sur un damier de 3 cases par 3 cases.<br/>
		Il existe trois types de morpions: guerrier, archer et sorcier.<br/>
		Chaque morpion possède au moins deux carractériqtique, attack et life .<br/>
		Seuls les sorciers ont de la mana.le totale des caractéristiques est toujours égal à 10.<br/>
		A son  tour un joueur à le choix entre trois action poser un de ses morpions sur une case vide,<br/>
		attaquer un morpion adverse, ou lancer un sort avec un sorcier.<br/>
		Le but est d'alligner quatres morpions de son équipe ou de tuer tout les morpions de son adversaires.</h4>
	<?php	
	}
	if($_POST['champRech'] == 'statistique'){
		?>
			<fieldset style="border:solid 1px black; padding:20px; width:60%;">
		<form name="formRecherche" method="post" action="index.php?page=regles.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">afficher les actions de la partie séléctionnée</label></td>
			<td>
		<?php $req=mysqli_fetch_array($connexion->query('select count(IDPa) from party ;'));
		$req1=mysqli_fetch_all($connexion->query('select IDPa from party ;'));
		echo '<select name="classe" id="idclasse">';
		for($i=0;$i<$req[0];$i++)
			{
				echo '<option value='.$req1[$i][0].'> party'.$req1[$i][0].'</option>';
			}
			echo '</select>';?>
			</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bparty" value="party"></td>
		</tr></table>
		</form>
	</fieldset>
	<?php
	}
		
}
if(isset($_POST['bparty'])) {
	
}
if(!$formulaireValide) {
?>
	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=regles.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">afficher les règles de</label></td>
			<td>
			<select name="champRech" id="idChamp">
				<option value="classique3X3">classique 3X3</option>
				<option value="statistique">statistique</option>
				<option value="modifie3X3">modifié 3X3</option>
				<option value="modifie4X4">modifié 4X4</option>
			</select>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bRechercher" value="Rechercher"></td>
		</tr></table>
		</form>
	</fieldset>
<?php
}
?>