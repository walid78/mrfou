<h1>Liste des &eacute;tapes</h1>

<?php

include("functions.php");

$link = connect_db();
list_table("ETAPE", $link);
disconnect_db($link);

?>
