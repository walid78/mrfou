<!DOCTYPE html 
PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
    <link rel="stylesheet" media="screen" type="text/css" title="style" href="style.css" />
    <title>Recettes</title>
  </head>
  <body>

    <div id="site">

      <div id="haut">

      </div>

      <div id="centre">
        <div id="menu">
          <center><h2>Menu</h2></center>
          <a href="?page=ajouter_repas">Ajouter un repas</a><br/>
          <a href="?page=ajouter_ingr">Ajouter un ingr�dient</a><br/>
          <a href="?page=liste_courses">Liste des courses</a><br/>
          <a href="?page=liste_ingr">Liste des ingr�dients</a><br/>
          <a href="?page=liste_repas">Liste des repas</a><br/>
        </div>

        <div id="page">

<?php
$page = $_GET['page'];

if($page == "")
  $page=liste_ingr;

$pages = array(
			   "ajouter_ingr" => "pages/ajouter_ingredient.php",
			   "ajouter_repas" => "pages/ajouter_repas.php",
			   "liste_courses" => "pages/liste_courses.php",
			   "liste_courses_reset" => "pages/liste_courses_reset.php",
			   "liste_ingr" => "pages/liste_ingredients.php",
			   "liste_repas" => "pages/liste_repas.php",
			   );

include $pages[$page];

?>

        </div>
      </div>

	  <div id="bas">

      </div>

	</div>
  </body>
</html>
