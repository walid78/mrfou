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
  $j=0;
  $nb_keys = 0;
  $page = $_GET['page'];

  echo "
<form action=\"pages/traitement_supp.php?page=".$page."&table_name=".$table_name."\" method=\"post\">\n";

  echo "  
  <center>
    <table border=1>";

  /* Récupération des noms des colonnes */

  $query = "SELECT column_name 
            FROM user_tab_cols 
            WHERE table_name='".$table_name."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  echo "
      <tr>";
  $nb_col = 0;
  
  while(OCIFetchInto ($stmt, $row, OCI_NUM)){
    foreach($row as $tmp){
      if(($nb_col != 0)){
	
	switch($tmp){

	case "ID_DEST_PREFEREE":
	  echo "<td>DEST PREFEREE</td>";
	  break;

	case "ID_ETAPE":
	  echo "<td>ETAPE</td>";
	  break;

	case "ID_DEST":
	  echo "<td>DEST</td>";
	  break;

	case "ID_CLASSE":
	  echo "<td>CLASSE</td>";
	  break;

	case "ID_CIRCUIT":
	  echo "<td>CIRCUIT</td>";
	  break;

	default:
	  echo "
	<td>".str_replace("_", " ", $tmp)."</td>";   

	}
      }  
    $nb_col++;
    }
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
	
    for($i=1 ; $i<$nb_col ; ++$i){
      switch($table_name){

      case "CLIENT":
	if($table_name == "CLIENT"){
	  //Récup dest_préférée
	  if(($i == 8) AND ($row[$i] != '')){
	    $query2 = "SELECT nom_destination, pays 
                     FROM destination
                     WHERE id_dest='".$row[$i]."'";
	    $stmt2 = ociparse($link, $query2);
	    ociexecute($stmt2,OCI_DEFAULT);
	  
	    while(OCIFetchInto ($stmt2, $row2, OCI_NUM))
	      echo "<td>".$row2[0]."(".$row2[1].")</td>";
	    break;
	  }
	}
	
      case "HOTEL":

	if($table_name == "HOTEL"){
	  //Récup dest_préférée
	  if(($i == 1) AND ($row[$i] != '')){
	    $query2 = "SELECT descriptif 
                     FROM etape
                     WHERE id_etape='".$row[$i]."'";
	    $stmt2 = ociparse($link, $query2);
	    ociexecute($stmt2,OCI_DEFAULT);
	  
	    while(OCIFetchInto ($stmt2, $row2, OCI_NUM))
	      echo "<td>".$row2[0]."</td>";
	    break;
	  }

	  if(($i == 4) AND ($row[$i] != '')){
	    $query2 = "SELECT prix_s, prix_d 
                     FROM classe_hotel
                     WHERE id_classe='".$row[$i]."'";
	    $stmt2 = ociparse($link, $query2);
	    ociexecute($stmt2,OCI_DEFAULT);
	  
	    while(OCIFetchInto ($stmt2, $row2, OCI_NUM))
	      echo "<td>"."Ch. simple : ".$row2[0]."&euro; | Ch. double : ".$row2[1]."&euro;</td>";
	    break;
	  }
	}

      case "VOL":
	if($table_name == "VOL"){
	  if(($i == 1) AND ($row[$i] != '')){
	    $query2 = "SELECT nom_destination, pays 
                     FROM destination
                     WHERE id_dest='".$row[$i]."'";
	    $stmt2 = ociparse($link, $query2);
	    ociexecute($stmt2,OCI_DEFAULT);
	  
	    while(OCIFetchInto ($stmt2, $row2, OCI_NUM))
	      echo "<td>".$row2[0]."(".$row2[1].")</td>";
	    break;
	  }
	}
	  
      case "ETAPE":
	if($table_name == "ETAPE"){
	  if(($i == 2) AND ($row[$i] != '')){
	    $query2 = "SELECT nom_circuit 
                       FROM circuit
                       WHERE id_circuit='".$row[$i]."'";
	    $stmt2 = ociparse($link, $query2);
	    ociexecute($stmt2,OCI_DEFAULT);
	  
	    while(OCIFetchInto ($stmt2, $row2, OCI_NUM))
	      echo "<td>".$row2[0]."</td>";
	    break;
	  }
	}
	  
      default:
	echo "
	<td>".$row[$i]."</td>"; 
      }
    }
	
      echo "
	<td><input type=\"checkbox\" 
                   name=\"row".$j++."\" 
                   value=\"".$keys[0]."=".$row[0]."\"/></td>";

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
  $page = $_GET['page'];
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
   
//     $query = "
// begin
//   ".$query."
// end;";
    
//     echo $query;

    /* A décommenter pour mettre en place la suppression */
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    ocicommit($link);

//     echo $query."<br/>";
    header('location: ../index.php?page='.$page);
   
  }
}

//============================================================================
function traitement_ajout($link){
  $page = $_GET['page'];

  /* Variables globales */

  $table_name = $_GET['table_name'];
  $funcadd= "ajout_";

  switch($table_name){

  case "CLIENT":
    $funcadd = $funcadd."client";
    break;

  case "DESTINATION":
    $funcadd = $funcadd."dest";
    break;

  case "HOTEL":
    $funcadd = $funcadd."hotel";
    break;

  case "CIRCUIT":
    $funcadd = $funcadd."circuit";
    break;

  case "VOL":
    $funcadd = $funcadd."vol";
    break;

  case "ETAPE":
    $funcadd = $funcadd."etape";
    break;

  case "CLASSE_HOTEL":
    $funcadd = $funcadd."classe";
    break;

  case "SEJOUR":
    $funcadd = $funcadd."sejour";
    break;

  default:
    exit("Problème table inconnue.");
  }

  /* Traitement */

  // Recuperation du nombre d'entrees
//  $query = "SELECT count(*) FROM ".$table_name;
  $query = "SELECT count(column_name) FROM user_tab_cols WHERE table_name='".$table_name."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  while(OCIFetchInto ($stmt, $row, OCI_NUM))
    $nb_rows = $row[0];
//   echo $nb_rows."<br/>";

  // Recuperation des colonnes à ajouter
  for($i=0 ; $i < $nb_rows-1 ; $i++){
    $col_to_add[$i] = $_POST['col'.$i];
  }

  $query = $funcadd."(";
  $i=0;
  foreach($col_to_add as $col){
    if($i++ == 0)
      $query = $query."'".$col."'";
    else
      $query = $query.", ".$col;
  }
  $query = $query.");";
  

  $query = "
begin
  ".$query."
end;";

//   echo $query."<br/>";

  /* A décommenter pour mettre en place l'ajout */
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    ocicommit($link);
    header('location: ../index.php?page='.$page);
}

//============================================================================
// function ($link){


?>
