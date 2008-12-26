<h1>Liste des circuits</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("CIRCUIT", $link);
disconnect_db($link);

?>