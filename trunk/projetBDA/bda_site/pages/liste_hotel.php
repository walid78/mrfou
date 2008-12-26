<h1>Liste des h&ocirc;tels</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("HOTEL", $link);
disconnect_db($link);

?>
