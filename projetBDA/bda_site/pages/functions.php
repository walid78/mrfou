<?php

  //============================================================================
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

  //============================================================================
function disconnect_db($link){
  ocilogoff($link);
}

  //============================================================================
function list_table($table_name, $link){
  /* Variables globales */
  $i=0;
  $nb_keys = 0;

  echo "
<form action=\"pages/traitement_supp.php?table_name=".$table_name."\" method=\"post\">\n";

  echo "  
  <center>
    <table border=1>";

  /* Récupération des noms des colonnes */

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


  /* Recuperation des cles primaire */

  $query = "SELECT column_name FROM user_cons_columns WHERE constraint_name in 
(SELECT index_name FROM user_constraints WHERE table_name='".$table_name."' and CONSTRAINT_TYPE='P')";

  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    foreach($row as $tmp)
      $keys[$nb_keys++] = $tmp;     
  }


  /* Nouvelle requete */
  $query = "SELECT * FROM ".$table_name;
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);
  $id=0;

  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    echo "
      <tr>";
	
    foreach($row as $tmp){
      echo "
	<td>".$tmp."</td>"; 
    }
	
    if($table_name != "ETAPE"){
      echo "
	<td><input type=\"checkbox\" 
                   name=\"row".$i++."\" 
                   value=\"".$keys[0]."=".$row[0]."\"/></td>";
    }else{
      echo "
	<td><input type=\"checkbox\"
                   name=\"row".$i++."\" 
                   value=\"".$keys[0]."=".$row[0]."&".$keys[1]."=".$row[1]."\"/></td>";
    }

    echo "
      </tr>";
  }

  echo "
    </table>
    <input align=\"right\" type=\"reset\" value=\"Tout d&eacute;s&eacute;lectionner\"/> 
    <input align=\"right\" type=\"submit\" value=\"Supprimer\"/>
  </center>
</form>";

}

  //============================================================================
function traitement_supp($link){

  /* Variables globales */

  $table_name = $_GET['table_name'];
  $nb_rows = 0;
  $nb_rows_to_del = 0;

  /* Traitement */

  // Recuperation du nombre d'entrees
  $query = "SELECT count(*) FROM ".$table_name;
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  while(OCIFetchInto ($stmt, $row, OCI_NUM))
    $nb_rows = $row[0];

  // Recuperation des lignes a supprimer
  for($i=0 ; $i < $nb_rows ; $i++){
    if($_POST['row'.$i] != ""){
      $rows_to_del[$nb_rows_to_del++] = $_POST['row'.$i];
    }
  }

  if($nb_rows_to_del == 0){
    //   deconnect_db($link);
    //   header('location: ../index.php?page=liste_repas&mess=err_plat');
    exit("Aucune ligne s&eacute;lectionn&eacute;e");
  }

  // Requete de suppression pour chaque ligne selectionnee
  foreach($rows_to_del as $row){
    $query = "DELETE FROM ".$table_name." WHERE ( ";

    // on recupere les donnees dans un tableau de type "cle prim" => "valeur"
    // exemple : "id_circuit" => "2"
    parse_str($row, $elems);

    $i=0;
    foreach($elems as $elem){
      $keys = array_keys($elems);
      if($i>0)
	$query = $query."AND ";
      $query = $query."".$keys[$i++]."=".$elem." ";
    }
    
    $query = $query.")";
   

    /* A décommenter pour mettre en place la suppression */
    //   $stmt = ociparse($link, $query);
    //   ociexecute($stmt,OCI_DEFAULT);

    echo $query."<br/>";
   
  }
}

function form_add($table_name){
  /* Variables */
  $i=0;

  /* Récupération des noms des colonnes */

  $query = "SELECT column_name FROM user_tab_cols WHERE table_name='".$table_name."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  echo "
<form action=\"pages/traitement_ajout.php?table_name=".$table_name."\" method=\"post\">";

  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    foreach($row as $tmp){
      echo "
  ".$tmp." : <input type=\"text\" title=\"".$tmp."\" name=\"col".$i++."\" value=\"\"/><br/>";
    }
  }
  
}

?>
