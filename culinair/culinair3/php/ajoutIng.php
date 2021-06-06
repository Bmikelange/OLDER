<h1>Ajout d'un ingredient</h1>
<p>
Completer le formulaire pour ajouter un ingredient
<br></p>
<?php
$formulaireValide = FALSE;

if(isset($_POST['bValider'])) {
	// ON UTILISE START TRANSACTION ET COMMIT/ROLLBACK POUR PRESERVER LES PROPRIETES ACID DE LA DB
	mysqli_query($connexion, 'START TRANSACTION');
	if(isset($_POST['nomIng']) && trim($_POST['nomIng']) != '') {
		
		
		
		// echappement des variables
		$nomIng = mysqli_real_escape_string($connexion, $_POST['nomIng']);
		$catIng = mysqli_real_escape_string($connexion, $_POST['nomCategorieIng']);
		$adresse= mysqli_real_escape_string($connexion, $_POST['adresse']);
		$continent= mysqli_real_escape_string($connexion, $_POST['continent']);
		$pays= mysqli_real_escape_string($connexion, $_POST['Pays']);
		$codePostal= mysqli_real_escape_string($connexion, $_POST['CodePostal']);
		$ville=mysqli_real_escape_string($connexion, $_POST['Ville']);
		$quantIngAjout=mysqli_real_escape_string($connexion, $_POST['nomQuanting']);
		
		
		$requeteLiaisonZoneGeoAdr='SELECT * FROM Lieu Where idLieu=0';
		
		
		if ($adresse==''|| $codePostal==''|| $ville=''||$pays=='')// n'entre pas si l'adresse complete est donnée
			{
				if ($continent=='' || $pays=='')// entre si l'adresse n'est pas une zone géographique
				{
					echo 'Veuillez ajouter une adresse valide';
					mysqli_query($connexion, 'ROLLBACK'); // avorte la transaction
					exit();
				}
			else{// si le lieu est une zone géographique il faut tester si cette adresse existe déjà  et creer la requete qui liera l'adresse et l'ingredient.
				$resultatAdresse=mysqli_query($connexion,'SELECT iDGeo FROM zonegeographique WHERE (continent=\''.$continent.'\' AND paysGeo=\''.$pays.'\');') ;
				if($resultatAdresse == TRUE && mysqli_num_rows($resultatAdresse) != 0){
				$idLieu=mysqli_fetch_array($resultatAdresse,MYSQLI_NUM);
				$requeteAdresse='SELECT * FROM Lieu Where idLieu=0';
				
				}
				else{ // si ce lieu n'existe pas encore
				$res=mysqli_query($connexion,'INSERT INTO Lieu(latitude,longitude) VALUES (0,0)');
				if ($res==false)
				{mysqli_query($connexion, 'ROLLBACK'); echo 'erreur insertion base de donnée'; exit();}
				$maxIdLieu=mysqli_query($connexion,'SELECT MAX(iDLieu) FROM Lieu');
				$idLieu=mysqli_fetch_array($maxIdLieu,MYSQLI_NUM);
				$requeteAdresse=mysqli_query($connexion,'INSERT INTO zonegeographique (continent,paysGeo) VALUES (\''.$continent.'\',\''.$pays.'\');');
				$requeteLiaisonZoneGeoAdr='INSERT INTO estune2 VALUES ('.$idLieu[0].',LAST_INSERT_ID());';
				

				}
				
			}
			}
			else{// on entre ici en cas d'adresse COMPLETE
				
						$resultatAdressePhysique=mysqli_query($connexion,'SELECT idLieu FROM adresse WHERE (paysAdresse=\''.$pays.'\' AND codePostal='.$codePostal.'  AND villeAdresse= \''.$ville.'\' AND adresseAdresse= \''.$adresse.'\' );');
					// testons d'abord si l'adresse existe deja dans la DBASE
					if($resultatAdressePhysique == TRUE && mysqli_num_rows($resultatAdressePhysique) != 0) {
						$idLieu=mysqli_fetch_array($resultatAdressePhysique,MYSQLI_NUM);
						$requeteAdresse='SELECT * FROM Lieu Where idLieu=0';
					}
				else
					{
						// sinon faudra récupérer l'identifiant de l'adresse
						$res=mysqli_query($connexion,'INSERT INTO Lieu(latitude,longitude) VALUES (0,0)');
						if ($res==false){mysqli_query($connexion, 'ROLLBACK'); echo 'erreur insertion base de donnée'; exit();}
						$maxIdLieu=mysqli_query($connexion,'SELECT MAX(iDLieu) FROM Lieu;');
						$idLieu=mysqli_fetch_array($maxIdLieu,MYSQLI_NUM);
						$requeteAdresse=mysqli_query($connexion,'INSERT INTO adresse (paysAdresse, codePostal,villeAdresse,adresseAdresse,idLieu) VALUES( \''.$pays.'\' , '.$codePostal.' , \''.$ville.'\' , \''.$adresse.'\' ,'.$idLieu[0].');');
					}
			}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%     MILESTONE     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			// INGREDIENT DEJA DANS LA BASE DE DONNEE????
			
		$resultat = mysqli_query($connexion, 'SELECT iDIngredient FROM Ingredient WHERE nomIngredient=\''.$nomIng.'\';');
			
		if($resultat == TRUE && mysqli_num_rows($resultat) != 0) 
		{	
	//OUAIP!! ING deja dans la base de donnee reste à tester si l'origine existe deja E.G [kiwi francais]!=[kiwi neo-zelandais]
	// et la c'est le bordel
					
					$idIng=mysqli_fetch_array($resultat,MYSQLI_NUM);
					$resultat1=mysqli_query($connexion,'SELECT iDLieu FROM provientIng WHERE iDIngredient='.$idIng[0].');');
					if($resultat1 == TRUE && mysqli_num_rows($resultat1) != 0) 
					// un meme ingredient de meme origine existe deja dans la DB
					// mise à jour de la quantité d'ingredient disponible
					
								{
								
								$requete = 'UPDATE Ingredient SET quantiteDispo=quantiteDispo+'.$quantIngAjout.' where iDIngredient='.$idIng1[0].';';
								//echo "<br>".$requete."<br>";
								$resInsert = mysqli_query($connexion, $requete);
											if($resInsert == FALSE) 
											{
											// si la requete echoue
											mysqli_query($connexion,'ROLLBACK');
											echo '<p>Erreur lors de l\'insertion de l\'ingredient!</p>';
											exit();
											}
											echo '<p>Cet ingredient existe déjà dans la base ! La quantité disponible a été ajoutée à celle déjà existante</p>';
											mysqli_query($connexion,'COMMIT;');
											// normalement si on arrive ici on ne devrait plus executer de requete par la suite
								}
								// requete insertion
					else{
								$requete = 'INSERT INTO provientIng(iDLieu,iDIngredient) VALUES('.$idLieu[0].', '.$idIng[0].');';
								//echo "<br>".$requete."<br>";
								$resInsert = mysqli_query($connexion, $requete);
								if($resInsert == FALSE) 
										{
										echo '<p>Erreur lors de l\'insertion de l\'ingredient!</p>';
										mysqli_query($connexion,'ROLLBACK;');
										exit();
										}
					mysqli_query($connexion,'COMMIT;');
					echo "<p>Confirmation de l'ajout de l'ingrédient : ".$nomIng."</p>";
					$formulaireValide = TRUE;
					
					
					}}
		else 
		{	// IL FAUT INSERER DANS LA DB L INGREDIENT ET LE LIEU
					
					$requete = 'INSERT INTO ingredient(nomIngredient,categorieIngredient,quantiteDispo) VALUES(\''.$nomIng.'\', \''.$catIng.'\', '.$quantIngAjout.');';
					//echo "<br>".$requete."<br>";
					$resInsert = mysqli_query($connexion, $requete);
					if($resInsert == FALSE) 
								{
									
									echo '<p>Erreur lors de l\'insertion de l\'ingredient!</p>';
									exit();
								}
					if ($requeteAdresse==FALSE)
								{
								echo '<p>Erreur lors de l\'insertion de l\'adresse!</p>';
								exit();
								}
					
					$resInsert3=mysqli_query($connexion,$requeteLiaisonZoneGeoAdr);
					if ($resInsert3==FALSE)
								{
								echo '<p>Erreur lors de la liaison Adresse Ingredient!</p>';
								exit();
								}
					$maxIdIng=mysqli_query($connexion,'SELECT MAX(iDIngredient) FROM Ingredient');
					$idIng=mysqli_fetch_array($maxIdIng);
					$liaisonAdresseIngredient='INSERT INTO provientIng(iDLieu,iDIngredient) VALUES('.$idLieu[0].', '.$idIng[0].');';
					$resInsert4=mysqli_query($connexion, $liaisonAdresseIngredient);
					if ($resInsert4==FALSE)
								{
								echo '<p>Erreur lors de la liaison Adresse Ingredient!</p>';
								exit();
								}
					
					mysqli_query($connexion,'COMMIT;');
					echo "<p>Confirmation de l'ajout de l'ingrédient : ".$nomIng."</p>";
					$formulaireValide = TRUE;
			}
	}
}
if(!$formulaireValide) {//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      MILESTONE     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//							FORMULAIRE HTML 
?>
		
<fieldset style="border:solid 1px black; padding:20px; width:40%;">
		<form name="ajoutIngredient" method="post" action="index.php?page=ajoutIng.php">
		<table width="100%">
		<tr><td><h3 style="font-weight:bold"> Ajout ingredient :</h3><td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng">Nom de l'ingredient : </label></td>
			<td><input type="text" name="nomIng" id="idNomIng" /></td>
			
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idCategorieIng">Categorie de l'ingredient : </label></td>
			<td><input type="text" name="nomCategorieIng" id="idCategorieIng" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idQuantAjout">Quantité à ajouter : </label></td>
			<td><input type="text" name="nomQuanting" id="idQuantAJout" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"> Ajout adresse :</h3><td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idadresse">Adresse : </label></td>
			<td><input type="text" name="adresse" id="idadresse" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idCodePostal">Code postal : </label></td>
			<td><input type="text" name="CodePostal" id="iCodePostal" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idVille">Ville : </label></td>
			<td><input type="text" name="Ville" id="idVille" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idPays">Pays : </label></td>
			<td><input type="text" name="Pays" id="idPays" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idcontinent">Continent : </label></td>
			<td><input type="text" name="continent" id="idcontinent" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"> Ajout date format(mm/dd/yyyy) :</h3><td></tr>
		<tr>
			<td><label style="font-weight:bold" for="labelDatedeProvenance">Date de provenance : </label></td>
			<td><input type="text" name="dateDeProvenance" id="idDatedeProvenance" /></td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bValider" value="Valider"></td>
		</tr></table>
		</form>
	</fieldset>
<?php
}
?>

