<h1>Ajouter un h&ocirc;tel</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("HOTEL", $link);
disconnect_db($link);

?>
