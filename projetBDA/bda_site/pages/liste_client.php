<?php

$db = "(DESCRIPTION =
    (ADDRESS_LIST =
      (ADDRESS = (PROTOCOL = TCP)(HOST = dbserver)(PORT = 1521))
    )
    (CONNECT_DATA =
      (SERVICE_NAME = mastergl)
    )
  )";

$login = "burno";

$user = "burno";

//Connexion à la base
$connect = ocilogon($login, $user, $db) or die( "Could not connect to Oracle database!");

$query = "select * from Client";

//On parse la requête à effectuer sans oublier de lui passer la chaine de connexion en paramêtre
$stmt = oci_parse($connect, $query);

//On execute la requête en lui passant l'option OCI_DEFAULT
oci_execute($stmt,OCI_DEFAULT);


echo "D&eacute;but----<br>\n\n";


while (oci_fetch($stmt)){ //On parcourt les résultats
//   echo ociresult($stmt,1).", "; //On récupère le premier champ de la ma_table
//   echo ociresult($stmt,2).", "; //On récupère le premier champ de la ma_table
//   echo ociresult($stmt,3).", "; //On récupère le premier champ de la ma_table
//   echo ociresult($stmt,4).", "; //On récupère le premier champ de la ma_table
//   echo ociresult($stmt,5).", "; //On récupère le premier champ de la ma_table
//   echo ociresult($stmt,6)." <br/>"; //On récupère le premier champ de la ma_table
  print_r();
}
  

echo "<br>----fin\n\n";

//On se déconnecte du serveur
ocilogoff($connect);

?>