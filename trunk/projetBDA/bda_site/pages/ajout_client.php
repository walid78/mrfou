<h1>Ajouter un client</h1>

<?php
   
include("functions.php");
$link = connect_db();
form_add("CLIENT", $link);
disconnect_db($link);

?>
