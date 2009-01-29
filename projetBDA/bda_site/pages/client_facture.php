 <h1>Afficher les factures d un client </h1>
 
<?php

include("functions.php");
$link = connect_db();

$id_client = $_GET['id_client'];

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

  echo "
      <option value=\"\">S&eacute;lectionner un client</option>";

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
      <option onClick='parent.location=\"?page=client_facture&id_client=".$row[0]."\"'
              value=\"".$row[0]."\"\>
        ".$row[0].". ".$row[3]."".$row[4]."(".$row[6].")
      </option>";
}

  echo "
    </select><br/><br/>";


?>

  </form>


<?php

  if($id_client != ""){
    
    // Recuperation des destinations
    $query = "SELECT Adresse,Tel,Nom,Prenom FROM CLIENT WHERE (ID_CLient = ".$id_client.")";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    
    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      $ad = $row[0];
      $tel = $row[1];
      $nom = $row[2];
      $prenom = $row[3];
    }
    
    // Recuperation des destinations
    $query = "SELECT total_vol, total_hotel, total_circuit, total_facture
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND
                 (nom = '".$nom."') AND
                 (prenom = '".$prenom."'))";
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
    
    while(OCIFetchInto($stmt, $row, OCI_NUM)){
      echo "Circuit  Hotel  Vol   Total<br/>";    
      echo $row[0]." + ".$row[1]." + ".$row[2]." = ".$row[3]." euros <br/>";    
    }
    
    disconnect_db($link);
  }
?>  
</center>

<!--A rajouter a la derniere requete pour l affichage des totaux de facture-->
<!--(adresse_client = ".$ad.") AND                (tel = ".$tel.") AND-->