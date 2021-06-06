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
	<title>morpillon</title>
	<link href="./css/styles.css" rel="stylesheet" media="all" type="text/css" />
	<link rel="shortcut icon" type="image/x-icon" href="img/papillon.jpg" />
</head>

<body>
	<?php include('static/header.php'); ?>
	<main>
		<?php include('static/menu.php'); ?>
		<section id="contenu">
		<?php
			$nomPage = 'static/accueil.php'; 
			if(isset($_GET['page'])) { 
				if(file_exists(addslashes('php/'.$_GET['page']))) 
					$nomPage = addslashes('php/'.$_GET['page']);
			}
			include($nomPage); 
		?>
		</section>
	</main>
	<?php include('static/footer.php'); ?>
</body>
<?php
//deconnectBD();
?>

</html>