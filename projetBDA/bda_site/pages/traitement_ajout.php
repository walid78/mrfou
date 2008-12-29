<?php

include("functions.php");

$link = connect_db();
traitement_ajout($link);
disconnect_db($link);

?>    