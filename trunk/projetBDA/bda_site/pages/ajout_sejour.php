<h1>Ajouter un s&eacute;jour</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("SEJOUR", $link);
disconnect_db($link);

?>
