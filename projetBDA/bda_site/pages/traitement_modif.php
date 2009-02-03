<?php

include("functions.php");
$link = connect_db();

$id_client = $_GET['id_client'];
$nom = $_POST['nom'];
$prenom = $_POST['prenom'];
$adresse = $_POST['adresse'];
$age = $_POST['age'];
$tel = $_POST['tel'];
$email = $_POST['email'];
$classe_sociale = $_POST['classe_sociale'];

$query = "UPDATE client
          SET client.nom='".$nom."',
              client.prenom='".$prenom."',
              client.age=".$age.",
              client.tel='".$tel."',
              client.email='".$email."',
              client.classe_sociale='".$classe_sociale."',
              client.adresse='".$adresse."'
          WHERE id_client=".$id_client;

$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);
ocicommit($link);
header('location: ../index.php?page=liste_client');

disconnect_db($link);

?>