<?php
	session_start();
	include('inc/constantes.php');
	include('inc/fonctions.php');
	connectBD();
?>
<!DOCTYPE html>
<html>

<head>
	<meta charset="utf-8" />
	<title>Culin'air</title>
	<!-- lie le style CSS externe  -->
	<link href="css/styles.css" rel="stylesheet" media="all" type="text/css">
	<!-- ajoute une image favicon (dans l'onglet du navigateur) -->
	<link rel="shortcut icon" type="image/x-icon" href="img/couteau_fourchette_croix.png" />
</head>

<body>
	<?php include('static/header.php'); ?>
	<main>
		<?php include('static/menu.php'); ?>
		<section id="contenu">
		<?php
			$nomPage = 'static/accueil.php'; // page par défaut
			if(isset($_GET['page'])) { // verification du parametre "page"
				if(file_exists(addslashes('php/'.$_GET['page']))) // le fichier existe
					$nomPage = addslashes('php/'.$_GET['page']);
			}
			include($nomPage); // inclut le contenu
		?>
		</section>
	</main>
	<?php include('static/footer.php'); ?>
</body>
<?php
//deconnectBD();
?>

</html>