<?php

/* Global variables */

function connect_db(){

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
  
  $link = ocilogon($login, $user, $db) or die( "Could not connect to Oracle database!");

  return $link;
}

function disconnect_db($link){
  ocilogoff($link);
}

function list_table($table_name, $link){

  echo "  
<center>
  <table border=1>
";

  $query = "SELECT column_name FROM user_tab_cols WHERE table_name='".$table_name."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  echo "<tr>";
  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    foreach($row as $tmp)
      echo "<td>".$tmp."</td>";     
  }
  echo "</tr>";



  /* Nouvelle requete */
  $query = "SELECT * FROM ".$table_name;
  $stmt = ociparse($link, $query);
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

}

?>
