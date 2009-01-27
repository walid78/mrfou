<h1>Valider une r&eacute;servation</h1>

<?php

include("functions.php");
$link = connect_db();

$id_client = $_GET['client'];
$id_dest = $_GET['dest'];
$id_circ = $_GET['circ'];
$id_sejour = $_GET['sejour'];

if($id_circ != ""){
  // Recuperation du nombre d'etapes
  $query = "
 SELECT COUNT(*)
 FROM ETAPE 
 WHERE id_circuit='".$id_circ."'";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);
  while(OCIFetchInto($stmt, $row, OCI_NUM))
    $nb_total_etapes = $row[0];
    
  for($i=0 ; $i<$nb_total_etapes ; ++$i){
    $id_etapes[$i] = $_GET['etape'.$i];
    $id_hotels[$i] = $_GET['hotel'.$i];
  }
    
}

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

  echo "
    </select><br/><br/>";


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
    </select><br/><br/>";

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
    </select><br/><br/>";
    
  }
  
  if($id_circ != ""){
    echo "
    <select>
      <option value=\"\">S&eacute;lectionner un s&eacute;jour</option>";

    $adress = $adress."&circ=".$id_circ;

    // Recuperation des sejours
    $query = "
 SELECT id_sejour, duree, description
 FROM ASSOC_PRIX_SEJOUR_CIRCUIT NATURAL JOIN SEJOUR 
 WHERE id_circuit='".$id_circ."'";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);

    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      if($row[0] == $id_sejour)
	$selected = "SELECTED";
      $ad = $adress."&sejour=".$row[0];
      echo "
      <option onClick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]." jours(".$row[2].")
      </option>";
      $selected = "";
    }
  
    echo "
    </select><br/><br/>";
    
  }

  if($id_sejour != ""){
    $adress = $adress."&sejour=".$id_sejour;
//     $adress = $adress."&date_debut=1";
//************************* Ici : donner le choix entre 4 jours de départ ?
//     echo "
//     <input type=\"text\" 
//            name=\"date_debut\"
//            onClick='parent.location=\"".$adress."\"'           ";

//   }


//   if($date_debut != ""){
    echo "
    <table border=0 align=\"center\" bgcolor=\"white\">
      <tr>
        <td>S&eacute;lectionner une(des) &eacute;tape(s)</td>
      </tr>";
//     $adress = $adress."&sejour=".$id_sejour;

    // Recuperation des etapes
    $query = "
 SELECT id_etape, no_etape, descriptif
 FROM ETAPE 
 WHERE id_circuit='".$id_circ."'";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);

    $num_etapes=0;

    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      $ad = $adress;
      $ad2 = $adress;
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes == $i){
	  if($id_etapes[$i] != ""){
	    $ad = $ad."&etape".$i."=";
	    $ad2 = $ad2."&etape".$i."=".$row[0];
	    $selected = " checked=true";
	  }else{
	    $ad = $ad."&etape".$i."=".$row[0];
	    $ad2 = $ad2."&etape".$i."=";
	  }
	}else{
	  $ad = $ad."&etape".$i."=".$id_etapes[$i];
	  $ad2 = $ad2."&etape".$i."=".$id_etapes[$i];
	}
      }

      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad2 = $ad2."&hotel".$i."=".$id_hotels[$i];
	$ad = $ad."&hotel".$i."=".$id_hotels[$i];
      }      
      
      echo "
      <tr>
        <td>
          <input type=\"checkbox\"
                 name=\"etape".$num_etapes."\"
                 onClick='parent.location=\"".$ad."\"'
                 value=\"".$row[0]."\"".$selected."/>
          ".$row[0].". ".$row[1]." (".$row[2].")
        </td>";
      
      $selected = "";

      // Si l'etape est choisie, on propose les hotels
      if($id_etapes[$num_etapes] != ""){
	// Recuperation des hotels
	$query2 = "
         SELECT id_hotel, nom_hotel
         FROM HOTEL
         WHERE id_etape='".$id_etapes[$num_etapes]."'";
	$stmt2 = ociparse($link, $query2);
	ociexecute($stmt2,OCI_DEFAULT);
	
	echo "
        <td>
          <select>
            <option value=\"\">S&eacute;lectionner un h&ocirc;tel</option>";
	
	while(OCIFetchInto($stmt2, $row, OCI_NUM)){
	  $ad2 = $ad2."&hotel".$num_etapes."=".$row[0];
	  if($id_hotels[$num_etapes] == $row[0])
	    $selected = " SELECTED";
	  echo "
            <option onClick='parent.location=\"".$ad2."\"'
                    value=\"".$row[0]."\"".$selected."/>
            ".$row[0].". H&ocirc;tel ".$row[1]."
            </option>";
	}
	echo "
          </select>
        </td>
        <td>
          <select>
            <option value=\"\">Nombre de chambre simple</option>
          </select>
        </td>
        <td>
          <select>
            <option value=\"\">Nombre de chambre double</option>
          </select>
        </td>";
	

      }
      echo "
      </tr>";
      $selected = "";
      ++$num_etapes;
    }
  
    echo "
    </table><br/>";
    
  }
}
?>
  </form>
</center>

<?php 

disconnect_db($link); 

?>
