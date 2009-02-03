<!DOCTYPE html 
PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />
    <link rel="stylesheet" media="screen" type="text/css" title="style" href="style.css" />
    <title>Projet BDA</title>
  </head>
  <body>

    <div id="site">

      <div id="haut">

      </div>

      <div id="centre">
   
        <div id="menu">
	  <center><h2>R&eacute;servation</h2></center>
          <a href="?page=valider_reserv">Valider une r&eacute;servation</a><br/>

          <center><h2>Consultation</h2></center>
          <a href="?page=liste_client">Liste des clients</a><br/>
          <a href="?page=liste_dest">Liste des destinations</a><br/>
          <a href="?page=liste_hotel">Liste des h&ocirc;tels</a><br/>
          <a href="?page=liste_circuit">Liste des circuits</a><br/>
          <a href="?page=liste_vol">Liste des vols</a><br/>
          <a href="?page=liste_etape">Liste des &eacute;tapes</a><br/>
          <a href="?page=liste_classe">Liste des classes d'h&ocirc;tel</a><br/>
          <a href="?page=liste_sejour">Liste des s&eacute;jours</a><br/>
	  
          <center><h2>Saisie</h2></center>
          <a href="?page=modif_client">Modifier un client</a><br/>
          <a href="?page=ajout_client">Ajouter un client</a><br/>
          <a href="?page=ajout_dest">Ajouter une destination</a><br/>
          <a href="?page=ajout_hotel">Ajouter un hôtel</a><br/>
          <a href="?page=ajout_circuit">Ajouter un circuit</a><br/>
          <a href="?page=ajout_vol">Ajouter un vol</a><br/>
          <a href="?page=ajout_etape">Ajouter une &eacute;tape</a><br/>
          <a href="?page=ajout_classe">Ajouter une classe d'h&ocirc;tel</a><br/>
          <a href="?page=ajout_sejour">Ajouter un s&eacute;jour</a><br/>
        </div>

        <div id="page">

<?php
$page = $_GET['page'];

if($page == "")
  $page="liste_client";

$pages = array(
	       "liste_client" => "pages/liste_client.php",
	       "liste_hotel" => "pages/liste_hotel.php",
	       "liste_vol" => "pages/liste_vol.php",
	       "liste_circuit" => "pages/liste_circuit.php",
	       "liste_etape" => "pages/liste_etape.php",
	       "liste_classe" => "pages/liste_classe.php",
	       "liste_sejour" => "pages/liste_sejour.php",
	       "liste_dest" => "pages/liste_dest.php",
	       "modif_client" => "pages/modif_client.php",
	       "ajout_client" => "pages/ajout_client.php",
	       "ajout_hotel" => "pages/ajout_hotel.php",
	       "ajout_vol" => "pages/ajout_vol.php",
	       "ajout_circuit" => "pages/ajout_circuit.php",
	       "ajout_etape" => "pages/ajout_etape.php",
	       "ajout_classe" => "pages/ajout_classe.php",
	       "ajout_sejour" => "pages/ajout_sejour.php",
	       "ajout_dest" => "pages/ajout_dest.php",
	       "valider_reserv" => "pages/valider_reserv.php"
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
