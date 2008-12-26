<h1>Liste des classes d'h&ocirc;tel</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("CLASSE", $link);
disconnect_db($link);

?>