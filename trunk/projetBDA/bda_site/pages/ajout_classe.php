<h1>Ajouter une classe d'h&ocirc;tel</h1>

<?php

include("functions.php");

$link = connect_db();
form_add("CLASSE_HOTEL", $link);
disconnect_db($link);

?>