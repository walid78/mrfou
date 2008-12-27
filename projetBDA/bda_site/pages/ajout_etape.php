<h1>Ajouter une &eacute;tape</h1>

<?php

include("functions.php");
$link = connect_db();
form_add("ETAPE", $link);
disconnect_db($link);

?>
