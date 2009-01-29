 <h1>Consulter les factures d un client </h1>
 
<?php

include("functions.php");
$link = connect_db();

$id_client = $_GET['id_client'];
$id_facture = $_GET['id_facture'];

?>

<!-- formulaire -->

<center>
  <form>
    <select>

<?php

// Recuperation des clients
$query = "SELECT * FROM CLIENT";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);
$adress = "?page=client_facture";
$selected = "";

  echo "
      <option value=\"\">S&eacute;lectionnez un client</option>";

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  if($row[0] == $id_client)
    $selected = "SELECTED";
  $ad = $adress."&id_client=".$row[0];
  echo "
      <option onClick='parent.location=\"".$ad."\"'
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[3]." ".$row[4]." (".$row[6].")
      </option>";
   $selected = "";
}

  echo "
    </select><br/><br/>";


  if($id_client != ""){
    echo "
    <select>
      <option value=\"\">S&eacute;lectionnez une date de facture </option>";

    $adress = $adress."&id_client=".$id_client;
    
    // Recuperation des données clients
    $query = "SELECT Adresse,Tel,Nom,Prenom FROM CLIENT WHERE (ID_CLient = ".$id_client.")";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    
    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      $ad = $row[0];
      $tel = $row[1];
      $nom = $row[2];
      $prenom = $row[3];
    }

    // Recuperation des id_factures avec leur date
    $query = "SELECT ID_Facture, Date_Facture 
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND
                 (nom = '".$nom."') AND
                 (prenom = '".$prenom."'))";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);

    while(OCIFetchInto($stmt, $row, OCI_NUM)){ 
     if($row[0] == $id_facture)
       $selected = "SELECTED";
     $ad = $adress."&id_facture=".$row[0];
      echo "<option onClick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]."
      </option>";
   $selected = "";
    }
  }

echo "
    </select><br/><br/>";

 if($id_facture != ""){

    // Recuperation des dépenses dans factures
    $query = "SELECT nom_dest, pays_dest, nom_circuit, total_circuit, total_hotel, Nb_enfant, Nb_adulte,total_vol,  total_facture
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND
                 (nom = '".$nom."') AND
                 (prenom = '".$prenom."'))";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    
    echo "    
    <table border=1>";

    echo "
      <tr>";  
    echo "
	<td>Dest</td>
	<td>Pays</td>
        <td>Nom_Circuit</td>
	<td>Total_Circuit</td>
	<td>Total_Hotel</td>
	<td>NBenfant</td>
	<td>NBadulte</td>
	<td>Total_Vol</td>
	<td>Total_Facture</td>
      </tr>";

    while(OCIFetchInto ($stmt, $row, OCI_NUM)){
      $selected = "SELECTED";  
       foreach($row as $tmp){
      echo "
	<td>".$tmp."</td>"; 
       }
      
    }

    echo "
    </table>";

    disconnect_db($link);
  
 }


 echo "
    </select><br/><br/>";

?>  
 </form>

</center>
