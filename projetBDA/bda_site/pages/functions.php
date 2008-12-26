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
  $i=0;

  echo "
<form action=\"pages/traitement_supp.php\" method=\"post\">\n";

  echo "  
<center>
  <table border=1>";

  $query = "SELECT column_name FROM user_tab_cols WHERE table_name='".$table_name."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  echo "
    <tr>";
  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    foreach($row as $tmp)
      echo "
      <td>".$tmp."</td>";     
  }
  echo "
      <td>DEL</td>
    </tr>";



  /* Nouvelle requete */
  $query = "SELECT * FROM ".$table_name;
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);
  $id=0;

  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    echo "
    <tr>";
  
    foreach($row as $tmp){
      if($id==0)
	$id=$tmp;
      echo "
      <td>".$tmp."</td>"; 
    }
    
    echo "
      <td><input type=\"checkbox\" name=\"".$table_name."".$i++."\" value=\"".$id."\"/></td>
    </tr>";
    $id=$i=0;
  }

  echo "
  </table>
</center>";

  echo "
</form>";

}

?>
