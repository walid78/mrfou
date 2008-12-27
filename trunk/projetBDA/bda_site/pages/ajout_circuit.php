<h1>Ajouter un circuit</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("CIRCUIT", $link);
disconnect_db($link);

?>