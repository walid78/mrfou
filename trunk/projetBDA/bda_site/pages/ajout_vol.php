<h1>Ajouter un vol</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("VOL", $link);
disconnect_db($link);

?>