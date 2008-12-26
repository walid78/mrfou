<?php

include("functions.php");

$link = connect_db();
traitement_supp($link);
disconnect_db($link);

?>    