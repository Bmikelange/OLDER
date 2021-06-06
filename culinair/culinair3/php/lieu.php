
  <head>
    <title>carte du monde</title>
    <style type="text/css">
     #basicMap {
          width: 900px;
          height: 600px;
          margin: 0;
    </style>
    <script src="http://www.openlayers.org/api/OpenLayers.js"></script>
    <script>
      function init() {
        map = new OpenLayers.Map("basicMap");
        var mapnik = new OpenLayers.Layer.OSM();
        map.addLayer(mapnik);
        map.setCenter(new OpenLayers.LonLat(13.41,52.52) 
          .transform(
            new OpenLayers.Projection("EPSG:4326"),
            new OpenLayers.Projection("EPSG:900913") 
          ), 0
        );
      }
    </script>
  </head>
  <body onload="init();">
    <div id="basicMap"></div>
	</body>

<h1>Recherche dans la base</h1>

	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=adresserech.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">Rechercher dans</label></td>
			<td>
			<select name="champRech" id="idChamp">
				<option value="adresse">adresse</option>
			</select>
			</td>
			<td><label style="font-weight:bold" for="idValeur">adresse</label></td>
			<td><input type="text" name="valeur" id="idValeur" /></td>
			<td><label style="font-weight:bold" for="idValeur">ville</label></td>
			<td><input type="text" name="valeur2" id="idValeur" /></td>
			</td>
			</td>
			<td><label style="font-weight:bold" for="idValeur">code postal</label></td>
			<td><input type="text" name="valeur3" id="idValeur" /></td>
			<td><label style="font-weight:bold" for="idValeur">Pays</label></td>
			<td><input type="text" name="valeur4" id="idValeur" /></td>
			</td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bRechercher" value="Rechercher"></td>
		</tr></table>
		</form>
	</fieldset>

<h1>Recherche dans la base</h1>

	<fieldset style="border:solid 1px black; padding:20px; width:60%;">
	<!-- <legend style="font-size:11; font-weight:bold;"> Recherche </legend> -->
		<form name="formRecherche" method="post" action="index.php?page=recherchegeo.php">
		<table width="100%">
		<tr>
			<td><label style="font-weight:bold" for="idChamp">Rechercher dans</label></td>
			<td>
			<select name="champRech" id="idChamp">
				<option value="zonegeographique">Zone Geographique</option>
			</select>
			</td>
			<td><label style="font-weight:bold" for="idValeur">continent</label></td>
			<td><input type="text" name="valeur" id="idValeur" /></td>
			<td><label style="font-weight:bold" for="idValeur">pays</label></td>
			<td><input type="text" name="valeur2" id="idValeur" /></td>
		</tr>
		<tr style="text-align:center;">
			<td colspan=2><br/><br/><input type="submit" style="font-variant: small-caps;" name="bRechercher1" value="Rechercher"></td>
		</tr></table>
		</form>
	</fieldset>


<h1> liste des adresses </h1>
<?php
$resultat=mysqli_query($connexion,'select * from adresse');
			if($resultat == FALSE || mysqli_num_rows($resultat) == 0) 
				{
					echo '<p>  aucune adresse</p>';
				}
			else	
				{
					while ($row=mysqli_fetch_array($resultat,MYSQLI_NUM))
					{
						echo '<p><a href="http://www.openstreetmap.org/?query='.$row[1].','.$row[2].','.$row[3].','.$row[4].'>'.$row[1].','.$row[2].','.$row[3].','.$row[4].'</a></p>';
					}
				}
?>

<h2> liste des zones geographiques </h2>

<?php
$resultat=mysqli_query($connexion,'select * from zonegeographique');
			if($resultat == FALSE || mysqli_num_rows($resultat) == 0) 
				{
					echo '<p>  aucune zone geographique</p>';
				}
			else	
				{
					while ($row=mysqli_fetch_array($resultat,MYSQLI_NUM))
					{
						echo '<p><a classe="info" href="http://www.openstreetmap.org/?query='.$row[2].'">'.$row[1].','.$row[2].'</a></p>';
					}
				}
?>
