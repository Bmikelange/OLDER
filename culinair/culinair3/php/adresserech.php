<?php
$formulaireValide = FALSE;
if(isset($_POST['bRechercher'])) {
	if(isset($_POST['valeur']) && trim($_POST['valeur']) != '' && isset($_POST['champRech'])) {
		$valeur = mysqli_real_escape_string($connexion,$_POST['valeur']);
		$valeur2 = mysqli_real_escape_string($connexion,$_POST['valeur2']);
		$valeur3 = mysqli_real_escape_string($connexion,$_POST['valeur3']);
		$valeur4 = mysqli_real_escape_string($connexion,$_POST['valeur4']);
		$table	= mysqli_real_escape_string($connexion,$_POST['champRech']);

		// construction de la requete
		if($_POST['champRech'] == 'adresse') {
			$requete = 'SELECT * FROM '.$table.' WHERE paysAdresse LIKE \'%'.$valeur4.'%\'AND codePostal LIKE '.$valeur3.' villeAdresse LIKE \'%'.$valeur2.'%\'AND adresseAdresse LIKE \'%'.$valeur.'%\';';
			$formulaireValide = TRUE;
			
		}

		if($formulaireValide) {
			//envoi de la requete
				$resultat = mysqli_query($connexion, $requete);
				if($resultat == FALSE || mysqli_num_rows($resultat) == 0) {
					echo '<p>Aucun résultat pour '.$valeur.','.$valeur2.','.$valeur3.','.$valeur4.' !</p>';
				}
				else {
					// affichage des résultats (utilisation de mysqli_field_count pour connaitre le nombre de champs du résultat)
					echo '<p>Résultat(s) de la recherche pour : '.$valeur.','.$valeur2.','.$valeur3.','.$valeur4.'</p>';
					$nbChamps = mysqli_field_count($connexion);
					while ($row = mysqli_fetch_array($resultat, MYSQLI_NUM)) {
						echo '<p><a href="http://www.openstreetmap.org/?query='.$row[1].','.$row[2].','.$row[3].','.$row[4].'">'.$row[1].','.$row[2].','.$row[3].','.$row[4].'</a></p>';
					}
					echo "</table>";
				}
			
		}
	}
}

?>