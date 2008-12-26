<h1>Liste des s&eacute;jours</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("SEJOUR", $link);
disconnect_db($link);

?>
