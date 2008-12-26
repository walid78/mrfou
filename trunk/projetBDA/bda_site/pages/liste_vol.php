<h1>Liste des vols</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("VOL", $link);
disconnect_db($link);

?>