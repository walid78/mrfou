<h1>Ajouter une destination</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("DESTINATION", $link);
disconnect_db($link);

?>
