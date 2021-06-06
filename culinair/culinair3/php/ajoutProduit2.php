<h1>Ajout d'un produit</h1>
<p>
Completer le formulaire pour ajouter un produit
<br></p>
<?php
$formulaireValide = FALSE;
if(isset($_POST['bValider'])) {
	if(isset($_POST['nomProduit']) && trim($_POST['nomProduit']) != '') {
		
		

		// requete select activite
		$nomProduit = mysqli_real_escape_string($connexion, $_POST['nomProduit']);
		$catProduit = mysqli_real_escape_string($connexion, $_POST['catProduit']);
		$adresseProduit = mysqli_real_escape_string($connexion, $_POST['Adresse']);
		$codeProduit = mysqli_real_escape_string($connexion, $_POST['Code']);
		$villeProduit = mysqli_real_escape_string($connexion, $_POST['Ville']);
		$paysProduit = mysqli_real_escape_string($connexion, $_POST['Pays']);
		$continentProduit = mysqli_real_escape_string($connexion, $_POST['Continent']);
		$nomIngredient1 = mysqli_real_escape_string($connexion, $_POST['nomIng1']);
		$nomIngredient2 = mysqli_real_escape_string($connexion, $_POST['nomIng2']);
		$nomIngredient3 = mysqli_real_escape_string($connexion, $_POST['nomIng3']);
		$nomIngredient4 = mysqli_real_escape_string($connexion, $_POST['nomIng4']);
		$nomIngredient5 = mysqli_real_escape_string($connexion, $_POST['nomIng5']);
		$quantIngredient1 = mysqli_real_escape_string($connexion, $_POST['nomquant1']);
		$quantIngredient2 = mysqli_real_escape_string($connexion, $_POST['nomquant2']);
		$quantIngredient3 = mysqli_real_escape_string($connexion, $_POST['nomquant3']);
		$quantIngredient4 = mysqli_real_escape_string($connexion, $_POST['nomquant4']);
		$quantIngredient5 = mysqli_real_escape_string($connexion, $_POST['nomquant5']);
		$Unite1=mysqli_real_escape_string($connexion, $_POST['unit1']);
		$Unite2=mysqli_real_escape_string($connexion, $_POST['unit2']);
		$Unite3=mysqli_real_escape_string($connexion, $_POST['unit3']);
		$Unite4=mysqli_real_escape_string($connexion, $_POST['unit4']);
		$Unite5=mysqli_real_escape_string($connexion, $_POST['unit5']);
		$resultat = mysqli_query($connexion, 'SELECT nomProduit FROM Produit WHERE nomProduitt=\''.$nomProduit.'\';');
		
		if ($nomIngredient1=='' || $nomIngredient2=='')
		{
			echo '<p> il y a moins de deux ingredients vous ne pouvez pas entrer un produit<p>';
			return(0);
		}
	
	$dateestla=mysqli_query($connexion,'select dateDeProvenance from dateprod where dateDeProvenance=CURRENT_DATE;');
	if ($dateestla == TRUE && mysqli_num_rows($dateestla) !=0)
		{
			$iddate=mysqli_query($connexion, 'select iDDate FROM dateprod where dateDeProvenance=CURRENT_DATE;');
			$iddate1=mysqli_fetch_array($iddate,MYSQLI_NUM);
		}
	else
		{
			$requeteDate=mysqli_query($connexion,'INSERT INTO dateprod(dateDeProvenance) VALUES (CURRENT_DATE);');
			$iddate=mysqli_query($connexion, 'SELECT last_insert_id() FROM dateprod;');
			$iddate1=mysqli_fetch_array($iddate,MYSQLI_NUM);
		}				
if ($adresseProduit==''|| $codeProduit==''|| $villeProduit=''||$paysProduit=='')// n'entre pas si l'adresse complete est donnée
			{
				if ($continentProduit=='' || $paysProduit=='')// entre si l'adresse n'est pas une zone géographique
				{
					echo 'Veuillez ajouter une adresse valide';
					mysqli_query($connexion, 'ROLLBACK'); // avorte la transaction
					exit();
				}
			else{// si le lieu est une zone géographique il faut tester si cette adresse existe déjà  et creer la requete qui liera l'adresse et l'ingredient.
				$resultatAdresse=mysqli_query($connexion,'SELECT iDGeo FROM zonegeographique WHERE (continent=\''.$continentProduit.'\' AND paysGeo=\''.$paysProduit.'\');') ;
				if($resultatAdresse == TRUE && mysqli_num_rows($resultatAdresse) != 0){
				$idLieu=mysqli_fetch_array($resultatAdresse,MYSQLI_NUM);
				$requeteAdresse=mysqli_query($connexion,'SELECT * FROM Lieu Where idLieu=0');
				$requeteLiaisonZoneGeo=mysqli_query($connexion,'select * from lieu');
				
				}
				else{ // si ce lieu n'existe pas encore
				$res=mysqli_query($connexion,'INSERT INTO Lieu(latitude,longitude) VALUES (0,0)');
				if ($res==false)
				{mysqli_query($connexion, 'ROLLBACK'); echo 'erreur insertion base de donnée'; exit();}
				$maxIdLieu=mysqli_query($connexion,'SELECT MAX(iDLieu) FROM Lieu');
				$idLieu=mysqli_fetch_array($maxIdLieu,MYSQLI_NUM);
				$requeteAdresse=mysqli_query($connexion,'INSERT INTO zonegeographique (continent,paysGeo) VALUES (\''.$continentProduit.'\',\''.$paysProduit.'\');');
				$requeteLiaisonZoneGeo=mysqli_query($connexion,'INSERT INTO estune2 VALUES ('.$idLieu[0].',LAST_INSERT_ID());');

				}
				
			}
			}
			else{// on entre ici en cas d'adresse COMPLETE
				
						$resultatAdressePhysique=mysqli_query($connexion,'SELECT idLieu FROM adresse WHERE (paysAdresse=\''.$paysProduit.'\' AND codePostal='.$codeProduit.'  AND villeAdresse= \''.$villeProduit.'\' AND adresseAdresse= \''.$adresseProduit.'\' );');
					// testons d'abord si l'adresse existe deja dans la DBASE
					if($resultatAdressePhysique == TRUE && mysqli_num_rows($resultatAdressePhysique) != 0) {
						$idLieu=mysqli_fetch_array($resultatAdressePhysique,MYSQLI_NUM);
						$requeteAdresse=mysqli_query($connexion,'SELECT * FROM Lieu Where idLieu=0');
						$requeteLiaisonZoneGeo=mysqli_query($connexion,'select * from lieu');
					}
				else
					{
						// sinon faudra récupérer l'identifiant de l'adresse
						$res=mysqli_query($connexion,'INSERT INTO Lieu(latitude,longitude) VALUES (0,0)');
						if ($res==false){mysqli_query($connexion, 'ROLLBACK'); echo 'erreur insertion base de donnée'; exit();}
						$maxIdLieu=mysqli_query($connexion,'SELECT MAX(iDLieu) FROM Lieu;');
						$idLieu=mysqli_fetch_array($maxIdLieu,MYSQLI_NUM);
						$requeteAdresse=mysqli_query($connexion,'INSERT INTO adresse (paysAdresse, codePostal,villeAdresse,adresseAdresse,idLieu) VALUES( \''.$paysProduit.'\' , '.$codeProduit.' , \''.$villeProduit.'\' , \''.$adresseProduit.'\' ,'.$idLieu[0].');');
						$requeteLiaisonZoneGeo=mysqli_query($connexion,'select * from lieu');
					}
			}
	
		$resultat = mysqli_query($connexion, 'SELECT nomProduit FROM Produit WHERE nomProduit=\''.$nomProduit.'\';');
			
		if($resultat == TRUE && mysqli_num_rows($resultat) != 0) {
			$idProduit= mysqli_query($connexion,'SELECT iDProduit FROM produit where nomProduit=\''.$nomProduit.'\';');
			$idProduit1=mysqli_fetch_array($idProduit,MYSQLI_NUM);
			$resultat1=mysqli_query($connexion,'SELECT iDLieu FROM provientProd WHERE iDProduit='.$idProduit1[0].');');
			if($resultat1 == TRUE && mysqli_num_rows($resultat1) != 0)
			{
			echo '<p>Ce Produit existe déjà dans la base !</p>';
			//echo "<br>".$requete."<br>";
			}
			echo "<p>Confirmation de l'ajout du Produit : ".$nomProduit."</p>";
			// requete insertion
			
			if ($requeteAdresse==FALSE){
			    echo '<p>Erreur lors de l\'insertion de l\'adresse1!</p>';
			    exit();
			}
			if ($requeteLiaisonZoneGeo==FALSE)
								{
								echo '<p>Erreur lors de la liaison Adresse Ingredient!</p>';
								exit();
								}
			
			$idUnite1=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite1.'\';');
			if($idUnite1 == TRUE && mysqli_num_rows($idUnite1) != 0)
			{
				$iDUnite11=mysqli_fetch_array($idUnite1,MYSQLI_NUM);
			$idIngredient1=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient1.'\';');
			if($idIngredient1 == TRUE && mysqli_num_rows($idIngredient1) != 0)
			{
				$idIngredient11=mysqli_fetch_array($idIngredient1,MYSQLI_NUM);
				$insert1=mysqli_query($connexion,'INSERT INTO apartirde VALUES('.$idIngredient11[0].', '.$iDUnite11[0].', '.$idProduit1[0].','.$quantIngredient1.');');
				if ($insert1==FALSE)
					{
				
					echo '<p>Erreur lors de l\'insertion de l\'ingredient1!</p>';
					exit();
					}
			}
			else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite2=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite2.'\';');
			if($idUnite2 == TRUE && mysqli_num_rows($idUnite2) != 0)
			{
				$iDUnite21=mysqli_fetch_array($idUnite2,MYSQLI_NUM);
			$idIngredient2=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient2.'\';');
			if($idIngredient2 == TRUE && mysqli_num_rows($idIngredient2) != 0)
			{	
			$idIngredient21=mysqli_fetch_array($idIngredient2,MYSQLI_NUM);
			echo '\''.$idIngredient21[0].'\', \''.$iDUnite21[0].'\', \''.$idProduit1[0].'\','.$quantIngredient2.'';
			$insert2=mysqli_query($connexion,'INSERT INTO apartirde VALUES('.$idIngredient21[0].', '.$iDUnite21[0].','.$idProduit1[0].','.$quantIngredient2.');');
			if ($insert2==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient2!</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite3=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite3.'\';');
			if($idUnite3 == TRUE && mysqli_num_rows($idUnite3) != 0)
			{
				$iDUnite31=mysqli_fetch_array($idUnite3,MYSQLI_NUM);
			$idIngredient3=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient3.'\';');
			if($idIngredient3 == TRUE && mysqli_num_rows($idIngredient3) != 0)
			{	
			$idIngredient31=mysqli_fetch_array($idIngredient3,MYSQLI_NUM);
			$insert3=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient31[0].'\', \''.$iDUnite31[0].'\', \''.$idProduit1[0].'\','.$quantIngredient3.');');
			if ($insert3==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient3! produit créé avec 2 ingredients</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite4=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite4.'\';');
			if($idUnite4 == TRUE && mysqli_num_rows($idUnite4) != 0)
			{	
			$iDUnite41=mysqli_fetch_array($idUnite4,MYSQLI_NUM);
			$idIngredient4=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient4.'\';');
			if($idIngredient4 == TRUE && mysqli_num_rows($idIngredient4) != 0)
			{
			$idIngredient41=mysqli_fetch_array($idIngredient4,MYSQLI_NUM);				
			$insert4=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient41[0].'\', \''.$iDUnite41[0].'\', \''.$idProduit1[0].'\','.$quantIngredient4.');');
			if ($insert4==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient4! produit créé avec 3 ingrédients</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite5=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite5.'\';');
			if($idUnite5 == TRUE && mysqli_num_rows($idUnite5) != 0)
			{
				$iDUnite51=mysqli_fetch_array($idUnite5,MYSQLI_NUM);
			$idIngredient5=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient5.'\';');
			if($idIngredient5 == TRUE && mysqli_num_rows($idIngredient5) != 0)
			{	
				$idIngredient51=mysqli_fetch_array($idIngredient5,MYSQLI_NUM);
			$insert5=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient51[0].'\', \''.$iDUnite51[0].'\', \''.$idProduit1[0].'\','.$quantIngredient5.');');
			if ($insert5==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient5! produit créé avec 4 ingredient</p>';
			    exit();
				}
			echo "<p>Confirmation de l'ajout du Produit : ".$nomProduit."</p>";
			$formulaireValide = TRUE;
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
		}
		else {
			

			// requete insertion
			$requete = mysqli_query($connexion,'INSERT INTO Produit(nomProduit,categorieProduit) VALUES(\''.$nomProduit.'\', \''.$catProduit.'\');');
			$idProduit= mysqli_query($connexion, 'SELECT iDProduit FROM Produit WHERE nomProduit=\''.$nomProduit.'\';');
			$idProduit1=mysqli_fetch_array($idProduit,MYSQLI_NUM);
			//echo "<br>".$requete."<br>";
			if($requete == FALSE) {
				
			    echo '<p>Erreur lors de l\'insertion du Produit!</p>';
			    exit();
			}
			else {
				echo "<p> confirmation de l'ajout du produit</p>";
			}
			;
			if ($requeteAdresse==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'adresse3!</p>';
			    exit();
			}
			echo '<p> '.$idLieu[0].','.$idProduit1[0].','.$iddate1[0].'</p>';
			$liaisonAdresseProduit= mysqli_query($connexion, 'INSERT INTO provientprod VALUES('.$idLieu[0].','.$idProduit1[0].','.$iddate1[0].');');
			//$resinsert3=mysqli_query($connexion, $liaisonAdresseProduit);
			if ($liaisonAdresseProduit==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'adresse4!</p>';
			    exit();
			}
					if ($requeteLiaisonZoneGeo==FALSE)
								{
								echo '<p>Erreur lors de la liaison Adresse Ingredient!</p>';
								exit();
								}
			$idUnite1=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite1.'\';');
			if($idUnite1 == TRUE && mysqli_num_rows($idUnite1) != 0)
			{
				$idUnite11=mysqli_fetch_array($idUnite1,MYSQLI_NUM);
			$idIngredient1=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient1.'\';');
			if($idIngredient1 == TRUE && mysqli_num_rows($idIngredient1) != 0)
			{	
				$idIngredient11=mysqli_fetch_array($idIngredient1,MYSQLI_NUM);
				$insert1=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient11[0].'\', \''.$idUnite11[0].'\', \''.$idProduit1[0].'\','.$quantIngredient1.');');
				if ($insert1==FALSE)
					{
				
					echo '<p>Erreur lors de l\'insertion de l\'ingredient1!</p>';
					exit();
					}
			}
			else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite2=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite2.'\';');
			if($idUnite2 == TRUE && mysqli_num_rows($idUnite2) != 0)
			{
				$idUnite21=mysqli_fetch_array($idUnite2,MYSQLI_NUM);
			$idIngredient2=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient2.'\';');
			if($idIngredient2 == TRUE && mysqli_num_rows($idIngredient2) != 0)
			{	
				$idIngredient21=mysqli_fetch_array($idIngredient2,MYSQLI_NUM);
			$insert2=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient21[0].'\', \''.$idUnite21[0].'\', \''.$idProduit1[0].'\','.$quantIngredient2.');');
			if ($insert2==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient2!</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite3=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite3.'\';');
			if($idUnite3 == TRUE && mysqli_num_rows($idUnite3) != 0)
			{
			$idUnite31=mysqli_fetch_array($idUnite3,MYSQLI_NUM);
			$idIngredient3=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient3.'\';');
			if($idIngredient3 == TRUE && mysqli_num_rows($idIngredient3) != 0)
			{	
			$idIngredient31=mysqli_fetch_array($idIngredient3,MYSQLI_NUM);
			$insert3=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient31[0].'\', \''.$idUnite31[0].'\', \''.$idProduit1[0].'\','.$quantIngredient3.');');
			if ($insert3==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient3!</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite4=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite4.'\';');
			if($idUnite4 == TRUE && mysqli_num_rows($idUnite4) != 0)
			{	
			$idUnite41=mysqli_fetch_array($idUnite4,MYSQLI_NUM);
			$idIngredient4=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient4.'\';');
			if($idIngredient4 == TRUE && mysqli_num_rows($idIngredient4) != 0)
			{	
			$idIngredient41=mysqli_fetch_array($idIngredient4,MYSQLI_NUM);
			$insert4=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient41[0].'\', \''.$idUnite41[0].'\', \''.$idProduit[0].'\','.$quantIngredient4.');');
			if ($insert4==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient4!</p>';
			    exit();
				}
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			$idUnite5=mysqli_query($connexion,'SELECT IDUnite FROM Unite WHERE nomUnite= \''.$Unite5.'\';');
			if($idUnite5 == TRUE && mysqli_num_rows($idUnite5) != 0)
			{
				$idUnite51=mysqli_fetch_array($idUnite5,MYSQLI_NUM);
			$idIngredient5=mysqli_query($connexion,'SELECT iDIngredient FROM ingredient WHERE nomIngredient= \''.$nomIngredient5.'\';');
			if($idIngredient5 == TRUE && mysqli_num_rows($idIngredient5) != 0)
			{	
			$idIngredien51=mysqli_fetch_array($idIngredien5,MYSQLI_NUM);
			$insert5=mysqli_query($connexion,'INSERT INTO apartirde VALUES(\''.$idIngredient51[0].'\', \''.$idUnite51[0].'\', \''.$idProduit1[0].'\','.$quantIngredient5.');');
			if ($insert5==FALSE)
				{
				
			    echo '<p>Erreur lors de l\'insertion de l\'ingredient5!</p>';
			    exit();
				}
			echo "<p>Confirmation de l'ajout du Produit : ".$nomIng."</p>";
			$formulaireValide = TRUE;
			}
				else
			{
				echo '<p>entrer un ingredient valide</p>';
				exit();
			}
			}
				else
			{
				echo '<p>entrer une unite valide</p>';
				exit();
			}
			echo "<p>Confirmation de l'ajout du produit : ".$nomProduit."</p>";
		}
		}
}
if(!$formulaireValide) {
?>
<fieldset style="border:solid 1px black; padding:20px; width:80%;">
		<form name="ajoutIngredient" method="post" action="index.php?page=ajoutProduit2.php">
		<table width="100%">
		<tr><td><h2 style="font-weight:bold"> <font color="light blue" >ajout produit : </font></h2></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomProduit">nom du produit : </label></td>
			<td><input type="text" name="nomProduit" id="idNomProduit" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idCatProduit">catégorie du produit : </label></td>
			<td><input type="text" name="catProduit" id="idCatProduit" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout lieu de provenance produit: </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idAdresse">Adresse : </label></td>
			<td><input type="text" name="Adresse" id="idAdresse" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idCode">Code postal : </label></td>
			<td><input type="text" name="Code" id="idCode" /></td>
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
			<td><label style="font-weight:bold" for="idContinent">Continent : </label></td>
			<td><input type="text" name="Continent" id="idContinent" /></td>
		</tr>
		</tr>
		<tr><td><h2 style="font-weight:bold"> <font color="light blue" >Ajout des ingrédients intervenants dans la composition : </font></h2></td></tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout ingredient 1: </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng1">Nom de l'ingredient  : </label></td>
			<td><input type="text" name="nomIng1" id="idNomIng1" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomquant1">Quantite de l'ingredient : </label></td>
			<td><input type="text" name="nomquant1" id="idNomquant1" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idunit1">unite de l'ingredient(entier) : </label></td>
			<td><input type="text" name="unit1" id="idunit1" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout ingredient 2 : </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng2">Nom de l'ingredient : </label></td>
			<td><input type="text" name="nomIng2" id="idNomIng2" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomquant2">Quantite de l'ingredient : </label></td>
			<td><input type="text" name="nomquant2" id="idNomquant2" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idunit2">unite de l'ingredient(entier) : </label></td>
			<td><input type="text" name="unit2" id="idunit2" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout ingredient 3 : </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng3">Nom de l'ingredient : </label></td>
			<td><input type="text" name="nomIng3" id="idNomIng3" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomquant3">Quantite de l'ingredient : </label></td>
			<td><input type="text" name="nomquant3" id="idNomquant3" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idunit3">unite de l'ingredient(entier) : </label></td>
			<td><input type="text" name="unit3" id="idunit3" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout ingredient 4: </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng4">Nom de l'ingredient : </label></td>
			<td><input type="text" name="nomIng4" id="idNomIng4" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomquant4">Quantite de l'ingredient : </label></td>
			<td><input type="text" name="nomquant4" id="idNomquant4" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idunit4">unite de l'ingredient(entier) : </label></td>
			<td><input type="text" name="unit4" id="idunit4" /></td>
		</tr>
		<tr><td><h3 style="font-weight:bold"><font color=194619 > ajout ingredient 5 : </font></h3></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomIng5">Nom de l'ingredient : </label></td>
			<td><input type="text" name="nomIng5" id="idNomIng5" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomquant5">Quantite de l'ingredient : </label></td>
			<td><input type="text" name="nomquant5" id="idNomquant5" /></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idunit5">unite de l'ingredient(entier) : </label></td>
			<td><input type="text" name="unit5" id="idunit5" /></td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bValider" value="Valider"></td>
		</tr></table>
		</form>
	</fieldset>
<?php
}
?>