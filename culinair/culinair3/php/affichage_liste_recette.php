<h1>Liste des recettes</h1>

<?php
$formulaireValide = FALSE;
if(isset($_POST['bRechercher'])) {
	if(isset($_POST['valeur']) && trim($_POST['valeur']) != '') {
		$valeur = mysqli_real_escape_string($connexion,$_POST['valeur']);
		

		// construction de la requete
			$requete = 'SELECT * FROM recette WHERE titre LIKE \'%'.$valeur.'%\';';
			$formulaireValide=TRUE;
		

		if($formulaireValide) {
			//envoi de la requete
			$resultat = mysqli_query($connexion, $requete);
			if($resultat == FALSE || mysqli_num_rows($resultat) == 0) {
				echo '<p>Aucun résultat pour '.$valeur.' !</p>';
			}
			else {
				// affichage des résultats (utilisation de mysqli_field_count pour connaitre le nombre de champs du résultat)
				echo '<p>Résultat(s) de la recherche pour : '.$valeur.'</p>';
				echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> recette</th> <th class=\"thIng\">categorie</th> <th class=\"thIng\"> Nombre de Personnes</th></tr>";
				$nbChamps = mysqli_field_count($connexion);
				while ($row = mysqli_fetch_array($resultat, MYSQLI_NUM)) {
					echo "<tr> <td class=\"tdIng\"><a href=\"index.php?page=affichage_recette.php&amp;iDRecette=".$row[0]."\">".$row[1]." </a></td> <td class=\"tdIng\"> ".$row[3]." </td> <td class=\"tdIng\"> ".$row[2]." ";
					echo '</tr>';
				}
				echo "</table>";
			}
		}
	}
}

?>
<h1>Recherche dans la base</h1>

	<fieldset style="border:solid 1px black; padding:20px; width:40%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=affichage_liste_recette.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">Rechercher :</label></td>
			<td><input type="text" name="valeur" id="idValeur" /></td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bRechercher" value="Rechercher"></td>
		</tr></table>
		</form>
	</fieldset>



<h2> liste des recettes </h2>

<?php $requete = 'SELECT titre, categorie,nbDePersonne FROM recette ORDER by titre;';

// envoi de la requete au SGBD
$resultat = mysqli_query($connexion, $requete);

if($resultat == FALSE) {
	printf("<p style='font-color: red;'>Erreur : problème d'exécution de la requête.</p>");
}
else {
	if(mysqli_num_rows($resultat) == 0) { // aucun résultat
		echo "<p>Il n'y a aucune recette dans la base.</p>";
	}
	else { // au moins un résultat
		echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> Recette</th> <th class=\"thIng\">categorie</th> <th class=\"thIng\"> nombre de personnes </th></tr>";
		while ($row = mysqli_fetch_assoc($resultat)) { // boucle sur chaque n-uplet
			echo "<tr> <td class=\"tdIng\">".htmlspecialchars($row['titre'])." </td> <td class=\"tdIng\">".htmlspecialchars($row['categorie'])."</td> <td class=\"tdIng\"> ".htmlspecialchars($row['nbDePersonne'])."</td> </tr>";
		}
echo "</table>";}}
?>
