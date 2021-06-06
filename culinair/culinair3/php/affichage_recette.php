<?php 
$iDRecette=mysqli_real_escape_string($connexion,$_GET['iDRecette']);
$resultat=mysqli_query($connexion,'SELECT * FROM recette WHERE iDRecette='.$iDRecette.'');
if ($resultat==FALSE || mysqli_num_rows($resultat)==0)
				{
			    echo '<p>Erreur lors de l\'affichage!</p>';
			    exit();
				}
$row=mysqli_fetch_array($resultat,MYSQLI_NUM);

echo "<h1> $row[1]</h1>";
echo "<h2> Nombre de Personnes : $row[2] </h2></br>";

echo "<h2> Categorie : $row[3]</h2></br>";

echo '<h2> Description : </h2></br>';

echo "<p> $row[4] </p>";

$requete='SELECT  * FROM Etapes WHERE iDRecette='.$row[0].';';
$resultatEtapes=mysqli_query($connexion,$requete);

while ($row = mysqli_fetch_assoc($resultatEtapes))
{
	echo "<h3>Etape ".$row['numeroEtape']."</h3></br>";
	$requete="SELECT * FROM instructions WHERE idEtape=".$row['idEtape'].";";
	$resultat_instruction=mysqli_query($connexion,$requete);
	while ($row1 = mysqli_fetch_assoc($resultat_instruction))
	{
	echo"<h3> Instruction ".$row1['numIns']." </h3>";
	echo"<p> ".$row1['descIns']."</p>";
	}
}
?>