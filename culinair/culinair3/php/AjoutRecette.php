
<?php
$formulaireValide = FALSE;
if(isset($_POST['bValider'])) {
	
$compteurFormulaire1=1;
$compteurFormulaire2=1;
$compteurInstruction=1;
$compteurEtape=1;
$titre=mysqli_real_escape_string($connexion,$_POST['nomRecette']);
$desc_Recette=mysqli_real_escape_string($connexion,$_POST['description_recette']);
$nbDePersonnes=mysqli_real_escape_string($connexion,$_POST['nbDePersonnes']);
$categorie=mysqli_real_escape_string($connexion,$_POST['categorie']);
$requete_recette='INSERT INTO recette(titre,nbDePersonne,description,categorie) VALUES (\''.$titre.'\','.$nbDePersonnes.', \''.$desc_Recette.'\',\''.$categorie.'\');';
//echo '<p> '.$requete_recette.'</p>';
mysqli_query($connexion,$requete_recette);
$iDRec_tab=mysqli_query($connexion, 'SELECT MAX(iDRecette) FROM recette');

$idRec=mysqli_fetch_array($iDRec_tab,MYSQLI_NUM);

while ($compteurFormulaire1<=5)
{
	$requete1='INSERT INTO etapes(numeroEtape,iDRecette) VALUES ('.$compteurEtape.','.$idRec[0].');';
	$etapeDejaCree=FALSE;
	while($compteurFormulaire2<=5){
		
		$value=$_POST['E'.$compteurFormulaire1.'_instruction_'.$compteurFormulaire2.''] ;
		$descriptionInstruction=mysqli_real_escape_string($connexion,$value);
		if(isset($_POST['E'.$compteurFormulaire1.'_instruction_'.$compteurFormulaire2.'']) && trim($_POST['E'.$compteurFormulaire1.'_instruction_'.$compteurFormulaire2.'']) != '')
		{
			if($etapeDejaCree==FALSE)
			{			$compteurEtape++;
				$etapeDejaCree=TRUE;
			mysqli_query($connexion,$requete1);
			$iDetape_tab=mysqli_query($connexion, 'SELECT MAX(iDEtape) FROM etapes');
			$idEtape=mysqli_fetch_array($iDetape_tab,MYSQLI_NUM);
			
			}
		$requete2 = 'INSERT INTO instructions(numIns,descIns,iDEtape) VALUES('.$compteurInstruction.', \''.$descriptionInstruction.'\', '.$idEtape[0].');';
		mysqli_query($connexion,$requete2);
		$compteurInstruction++;
		}
		
		$compteurFormulaire2++;
echo $value;}




$etapeDejaCree=FALSE;
$compteurFormulaire1++;
$compteurFormulaire2=1;
$compteurInstruction=1;
}



/* if($resInsert == FALSE) {
			    echo '<p>Erreur lors de l\'insertion de la recette</p>';
			    exit();
			} */
}

// $E1_Instruction_1= mysqli_real_escape_string($connexion, $_POST['E1_Instruction_1']);
// $E1_Instruction_2= mysqli_real_escape_string($connexion, $_POST['E1_Instruction_2']);
// $E1_Instruction_3= mysqli_real_escape_string($connexion, $_POST['E1_Instruction_3']);
// $E1_Instruction_4= mysqli_real_escape_string($connexion, $_POST['E1_Instruction_4']);
// $E1_Instruction_5= mysqli_real_escape_string($connexion, $_POST['E1_Instruction_5']);
// $E2_Instruction_1= mysqli_real_escape_string($connexion, $_POST['E2_Instruction_1']);
// $E2_Instruction_2= mysqli_real_escape_string($connexion, $_POST['E2_Instruction_2']);
// $E2_Instruction_3= mysqli_real_escape_string($connexion, $_POST['E2_Instruction_3']);
// $E2_Instruction_4= mysqli_real_escape_string($connexion, $_POST['E2_Instruction_4']);
// $E2_Instruction_5= mysqli_real_escape_string($connexion, $_POST['E2_Instruction_5']);
// $E3_Instruction_1= mysqli_real_escape_string($connexion, $_POST['E3_Instruction_1']);
// $E3_Instruction_2= mysqli_real_escape_string($connexion, $_POST['E3_Instruction_2']);
// $E3_Instruction_3= mysqli_real_escape_string($connexion, $_POST['E3_Instruction_3']);
// $E3_Instruction_4= mysqli_real_escape_string($connexion, $_POST['E3_Instruction_4']);
// $E3_Instruction_5= mysqli_real_escape_string($connexion, $_POST['E3_Instruction_5']);
// $E4_Instruction_1= mysqli_real_escape_string($connexion, $_POST['E4_Instruction_1']);
// $E4_Instruction_2= mysqli_real_escape_string($connexion, $_POST['E4_Instruction_2']);
// $E4_Instruction_3= mysqli_real_escape_string($connexion, $_POST['E4_Instruction_3']);
// $E4_Instruction_4= mysqli_real_escape_string($connexion, $_POST['E4_Instruction_4']);
// $E4_Instruction_5= mysqli_real_escape_string($connexion, $_POST['E4_Instruction_5']);
// $E5_Instruction_1= mysqli_real_escape_string($connexion, $_POST['E5_Instruction_1']);
// $E5_Instruction_2= mysqli_real_escape_string($connexion, $_POST['E5_Instruction_2']);
// $E5_Instruction_3= mysqli_real_escape_string($connexion, $_POST['E5_Instruction_3']);
// $E5_Instruction_4= mysqli_real_escape_string($connexion, $_POST['E5_Instruction_4']);
// $E5_Instruction_5= mysqli_real_escape_string($connexion, $_POST['E5_Instruction_5']);





if(!$formulaireValide) {
?>
<fieldset style="border:solid 1px black; padding:20px; width:40%;">
	<legend style="font-size:18; font-weight:bold;"> Ajouter la recette </legend>
		<form name="ajoutRecette" method="post" action="index.php?page=AjoutRecette.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idNomRecette">Nom de la recette : </label></td>
			<tr><td><input type="text" name="nomRecette" id="idNomRecette" ></td></tr>
			
		</tr>
		<tr><h2 style="font-weight:bold"> Informations sur la recette : </h2></tr>

			<tr> <td><label style="font-weight:bold" for="descRecette">  Description de la recette : </label></td> </tr>
		</tr>
		
		<tr>
			<td><textarea name="description_recette" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomRecette">Nombre de personnes : </label></td>
			<tr><td><input type="text" name="nbDePersonnes" id="idNomRecette" ></td></tr>
			
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idNomRecette"> Categorie : </label></td>
			<tr><td><input type="text" name="categorie" id="idNomRecette" ></td></tr>
			
		</tr>
		
		
		<tr><td><h2 style="font-weight:bold"> Etape 1 : </h2></td>
			<tr><td><p style="font-weight:bold">Instruction 1 : </p></td></tr>
		</tr>
		<tr>
			<td><textarea name="E1_instruction_1" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_1_Instruction2">  Instruction 2 : </label></td>
		</tr>
		<tr>
			<td><textarea name="E1_instruction_2" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_1_Instruction3"> Instruction 3 : </label></td>
		</tr>
		<tr>
			<td><textarea name="E1_instruction_3" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_1_Instruction4">  Instruction 4 : </label></td>
			</tr>
		<tr>
	<td><textarea name="E1_instruction_4" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_1_Instruction5"> Instruction 5 : </label></td>
			</tr>
		<tr>
	<td><textarea name="E1_instruction_5" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr> <td><h2 style="font-weight:bold"> Etape 2 : </h2></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_2_Instruction1"> Instruction 1 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E2_instruction_1" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_2_Instruction2"> Instruction 2 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E2_instruction_2" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_2_Instruction3"> Instruction 3 : </label></td>
			</tr>
		<tr>
<td><textarea name="E2_instruction_3" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_2_Instruction4"> Instruction 4 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E2_instruction_4" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_2_Instruction5"> Instruction 5 : </label></td>
			</tr>
		<tr>
			<td><textarea name="E2_instruction_5" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr> <td><h2 style="font-weight:bold"> Etape 3 : </h2></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_3_Instruction1"> Instruction 1 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E3_instruction_1" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_3_Instruction2"> Instruction 2 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E3_instruction_2" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_3_Instruction3"> Instruction 3 : </label></td>
			</tr>
		<tr>
<td><textarea name="E3_instruction_3" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_3_Instruction4"> Instruction 4 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E3_instruction_4" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_3_Instruction5"> Instruction 5 : </label></td>
			</tr>
		<tr>
			<td><textarea name="E3_instruction_5" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr> <td><h2 style="font-weight:bold"> Etape 4 : </h2></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_4_Instruction1"> Instruction 1 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E4_instruction_1" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_4_Instruction2"> Instruction 2 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E4_instruction_2" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_4_Instruction3"> Instruction 3 : </label></td>
			</tr>
		<tr>
<td><textarea name="E4_instruction_3" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_4_Instruction4"> Instruction 4 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E4_instruction_4" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_4_Instruction5"> Instruction 5 : </label></td>
			</tr>
		<tr>
			<td><textarea name="E4_instruction_5" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr> <td><h2 style="font-weight:bold"> Etape 5 : </h2></td></tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_5_Instruction1"> Instruction 1 : </label></td>s
			</tr>
		<tr>
		<td><textarea name="E5_instruction_1" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_5_Instruction2"> Instruction 2 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E5_instruction_2" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_5_Instruction3"> Instruction 3 : </label></td>
			</tr>
		<tr>
<td><textarea name="E5_instruction_3" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_5_Instruction4"> Instruction 4 : </label></td>
			</tr>
		<tr>
		<td><textarea name="E5_instruction_4" style="width:600px;height:150px;"></textarea></td>
		</tr>
		<tr>
			<td><label style="font-weight:bold" for="idEtape_5_Instruction5"> Instruction 5 : </label></td>
			</tr>
		<tr>
			<td><textarea name="E5_instruction_5" style="width:600px;height:150px;"></textarea></td>
		</tr>
		
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bValider" value="Valider"></td>
		</tr></table>
		</form>
	</fieldset>
	<?php
	}
	?>