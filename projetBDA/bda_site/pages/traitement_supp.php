<?php

include("functions.php");

/* Connexion */

$link = connect_db();

/* Requete */

$query = "SELECT count(*) FROM ";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

echo $stmt;