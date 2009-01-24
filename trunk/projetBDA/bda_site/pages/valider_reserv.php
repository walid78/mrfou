<h1>Valider une r&eacute;servation</h1>

<?php

include("functions.php");
$link = connect_db();

if($_GET['client'] != "")
  $id_client = $_GET['client'];
if($_GET['dest'] != "")
  $id_dest = $_GET['dest'];
if($_GET['circ'] != "")
  $id_circ = $_GET['circ'];

?>

<center>
  <form action="pages/traitement_ajout.php?table_name=CLIENT" method="post">
    <select title="Client" name="sel1">
      <option value="">S&eacute;lectionner un client</option>
<?php
      
// Recuperation des clients
$query = "SELECT * FROM CLIENT";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);
$adress = "?page=valider_reserv";
$selected = "";

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  if($row[0] == $id_client)
    $selected = "SELECTED";
  $ad = $adress."&client=".$row[0];
  echo "
      <option onClick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[3]."".$row[4]."(".$row[6].")
      </option>";
  $selected = "";
}

?>
    </select><br/> 
<?php
if($id_client != ""){
  echo "
    <select>
      <option value=\"\">S&eacute;lectionner une destination</option>";

  $adress = $adress."&client=".$id_client;

  // Recuperation des destinations
  $query = "SELECT * FROM DESTINATION";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  while(OCIFetchInto($stmt, $row, OCI_NUM)){
    if($row[0] == $id_dest)
      $selected = "SELECTED";
    $ad = $adress."&dest=".$row[0];
    echo "
      <option onClick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]."(".$row[2].")
      </option>";
    $selected = "";
  }
  
  echo "
    </select><br/>";

  if($id_dest != ""){
    echo "
    <select>
      <option value=\"\">S&eacute;lectionner un circuit</option>";

    $adress = $adress."&dest=".$id_dest;

    // Recuperation des circuits
    $query = "
 SELECT id_circuit, nom_circuit
 FROM ASSOC_DEST_CIRCUIT NATURAL JOIN CIRCUIT 
 WHERE id_dest='".$id_dest."'";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);

    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      if($row[0] == $id_circ)
	$selected = "SELECTED";
      $ad = $adress."&circ=".$row[0];
      echo "
      <option onClick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]."
      </option>";
      $selected = "";
    }
  
    echo "
    </select><br/>";
    
  }
}
?>
  </form>
</center>

<?php 

disconnect_db($link); 

?>
