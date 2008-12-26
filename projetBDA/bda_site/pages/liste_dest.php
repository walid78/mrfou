<h1>Liste des destinations</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("DESTINATION", $link);
disconnect_db($link);

?>
