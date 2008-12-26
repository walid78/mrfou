<h1>Liste des clients</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("CLIENT", $link);
disconnect_db($link);

?>
