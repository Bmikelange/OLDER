<?php
$formulaireValide = FALSE;
if(isset($_POST['bRechercher'])) {
	if(isset($_POST['valeur']) && trim($_POST['valeur']) != '' && isset($_POST['champRech'])) {
		$valeur = mysqli_real_escape_string($connexion,$_POST['valeur']);
		$table	= mysqli_real_escape_string($connexion,$_POST['champRech']);

		// construction de la requete
		if($_POST['champRech'] == 'Ingredient') {
			$requete = 'SELECT * FROM '.$table.' WHERE nomIngredient LIKE \'%'.$valeur.'%\';';
			$formulaireValide = TRUE;
			
		}
		else if($_POST['champRech'] == 'Produit') {
			$requete = 'SELECT * FROM '.$table.' WHERE nomProduit LIKE \'%'.$valeur.'%\';';
			$formulaireValide = TRUE;
		}

		if($formulaireValide) {
			//envoi de la requete
			if($_POST['champRech'] == 'Ingredient') {
				$resultat = mysqli_query($connexion, $requete);
				if($resultat == FALSE || mysqli_num_rows($resultat) == 0) {
					echo '<p>Aucun résultat pour '.$valeur.' !</p>';
				}
				else {
					// affichage des résultats (utilisation de mysqli_field_count pour connaitre le nombre de champs du résultat)
					echo '<p>Résultat(s) de la recherche pour : '.$valeur.'</p>';
					echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> ingredient</th> <th class=\"thIng\">categorie</th> <th class=\"thIng\"> quantite disponible </th></tr>";
					$nbChamps = mysqli_field_count($connexion);
					while ($row = mysqli_fetch_array($resultat, MYSQLI_NUM)) {
						echo "<tr> <td class=\"tdIng\">".$row[1]." </td> <td class=\"tdIng\"> ".$row[2]." </td> <td class=\"tdIng\"> ".$row[3]." ";
						echo '<a class="info" href="#">  (lieu ingredient :) <span>paris</span> </a></td></tr>';
					}
					echo "</table>";
				}
			}
			else{
				$resultat = mysqli_query($connexion, $requete);
				if($resultat == FALSE || mysqli_num_rows($resultat) == 0) {
					echo '<p>Aucun résultat pour '.$valeur.' !</p>';
				}
				else {
					// affichage des résultats (utilisation de mysqli_field_count pour connaitre le nombre de champs du résultat)
					echo '<p>Résultat(s) de la recherche pour : '.$valeur.'</p>';
					echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> ingredient</th> <th class=\"thIng\">categorie</th></tr>";
					$nbChamps = mysqli_field_count($connexion);
					while ($row = mysqli_fetch_array($resultat, MYSQLI_NUM)) {
						echo "<tr> <td class=\"tdIng\">".$row[1]."</td> <td class=\"tdIng\"> ".$row[2]." ";
						echo '<a class="info" href="#">  (lieu ingredient :) <span>paris</span> </a></td></tr>';
					}
					echo "</table>";
				}
			}
		}
	}
}

?>
<h1>Recherche dans la base</h1>

	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=affichageIngredient.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">Rechercher dans</label></td>
			<td>
			<select name="champRech" id="idChamp">
				<option value="Ingredient">Ingredient</option>
				<option value="Produit">Produit</option>
			</select>
			</td>
			<td><label style="font-weight:bold" for="idValeur">la valeur</label></td>
			<td><input type="text" name="valeur" id="idValeur" /></td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bRechercher" value="Rechercher"></td>
		</tr></table>
		</form>
	</fieldset>



<h2> liste des ingrédients </h2>

<?php $requete = 'SELECT * FROM ingredient ORDER by nomIngredient;';

// envoi de la requete au SGBD
$resultat = mysqli_query($connexion, $requete);

if($resultat == FALSE) {
	printf("<p style='font-color: red;'>Erreur : problème d'exécution de la requête.</p>");
}
else {
	if(mysqli_num_rows($resultat) == 0) { // aucun résultat
		echo "<p>Il n'y a aucun ingrédient dans la base.</p>";
	}
	else { // au moins un résultat
		echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> ingredient</th> <th class=\"thIng\">categorie</th> <th class=\"thIng\"> quantite disponible </th></tr>";
		while ($row = mysqli_fetch_assoc($resultat)) { // boucle sur chaque n-uplet
			echo "<tr> <td class=\"tdIng\">".htmlspecialchars($row['nomIngredient'])." </td> <td class=\"tdIng\">".htmlspecialchars($row['categorieIngredient'])."</td> <td class=\"tdIng\"> ".htmlspecialchars($row['quantiteDispo'])." ";
			echo '<a class="info" href="#">  (lieu ingredient :) <span>paris</span> </a> </td> </tr>';
		}
echo "</table>";}}
?>
<h2> liste des produits </h2>
<?php $requete = 'SELECT * FROM produit ORDER by nomProduit;';

// envoi de la requete au SGBD
$resultat = mysqli_query($connexion, $requete);

if($resultat == FALSE) {
	printf("<p style='font-color: red;'>Erreur : problème d'exécution de la requête.</p>");
}
else {
	if(mysqli_num_rows($resultat) == 0) { // aucun résultat
		echo "<p>Il n'y a aucun produit dans la base.</p>";
	}
	else { // au moins un résultat
		echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> produit</th> <th class=\"thIng\">categorie</th></tr>";
		while ($row = mysqli_fetch_assoc($resultat)) { // boucle sur chaque n-uplet
			echo "<tr> <td class=\"tdIng\">".htmlspecialchars($row['nomProduit'])." </td> <td class=\"tdIng\">".htmlspecialchars($row['categorieProduit'])."";
		echo '<a class="info" href="#">  (lieu ingredient :) <span>paris</span> </a> </td> </tr>';}
			echo "</table>";}}
?>

