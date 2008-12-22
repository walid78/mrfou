<h1>Liste des s&eacute;jours</h1>

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

$nb_column=0;
$table_name = "SEJOUR";

//Connexion à la base
$connect = ocilogon($login, $user, $db) or die( "Could not connect to Oracle database!");

echo "  
<center>
  <table border=1>
";

$query = "SELECT column_name FROM user_tab_cols WHERE table_name='".$table_name."'";
$stmt = ociparse($connect, $query);
ociexecute($stmt,OCI_DEFAULT);

echo "<tr>";
while(OCIFetchInto ($stmt, $row, OCI_NUM)){
  foreach($row as $tmp)
    echo "<td>".$tmp."</td>";     
}
  echo "</tr>";



/* Nouvelle requete */
$query = "select * from ".$table_name;
$stmt = ociparse($connect, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto ($stmt, $row, OCI_NUM)){
  echo "<tr>";
  
  foreach($row as $tmp)
    echo "<td>".$tmp."</td>"; 
  
  echo "</tr>";
}

echo "
  </table>
</center>";

//On se déconnecte du serveur
ocilogoff($connect);

?>