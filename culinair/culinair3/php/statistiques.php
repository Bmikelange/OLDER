<statistiques>
<?php
$select1=mysqli_query($connexion, 'select count(iDRecette) from recette ');
$selectrecette=mysqli_fetch_array($select1,MYSQLI_NUM);
$select2=mysqli_query($connexion, 'select count(iDAdresse) from adresse ');
$select_adresse=mysqli_fetch_array($select2,MYSQLI_NUM);
$select3=mysqli_query($connexion, 'select count(iDGeo) from zonegeographique ');
$select_geo=mysqli_fetch_array($select3,MYSQLI_NUM);
$select4=mysqli_query($connexion, 'select count(iDIngredient) from ingredient ');
$selectIngredient=mysqli_fetch_array($select4,MYSQLI_NUM);
$select5=mysqli_query($connexion, 'select count(iDProduit) from produit ');
$select_produit=mysqli_fetch_array($select5,MYSQLI_NUM);
$select6=mysqli_query($connexion, 'select count(iDLieu) from Lieu ');
$select_lieu=mysqli_fetch_array($select6,MYSQLI_NUM);
echo "<table class=\"tableauIngredient\"><tr> <th class=\"thIng\"> nombre de recette</th> <th class=\"thIng\">nombre d'adresse</th> <th class=\"thIng\"> nombre de zone geographique </th><th class=\"thIng\"> nombre d'Ingredient </th><th class=\"thIng\"> nombre de Produit </th><th class=\"thIng\"> nombre de Lieu </th></tr>";
				$nbChamps = mysqli_field_count($connexion);
					echo "<tr> <td class=\"tdIng\">".$selectrecette[0]." </td> <td class=\"tdIng\"> ".$select_adresse[0]." </td> <td class=\"tdIng\"> ".$select_geo[0]."</td> <td class=\"tdIng\"> ".$selectIngredient[0]." </td><td class=\"tdIng\"> ".$select_produit[0]." </td><td class=\"tdIng\"> ".$select_lieu[0]." </td>";
					echo '</tr>';
				echo "</table>";
?>
</statistiques>