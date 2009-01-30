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
    $add = $row[0];
    $tel = $row[1];
    $nom = $row[2];
      $prenom = $row[3];
  }
  echo $nom;
  echo $prenom;
  
  // Recuperation des id_factures avec leur date selon le client
  $query = "SELECT ID_Facture, Date_Facture 
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND
                 (nom = '".$nom."') AND
                 (prenom = '".$prenom."'))";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);
  $ad  = $adress."&id_facture=all";
  
    echo "<option onClick='parent.location=\"".$ad."\"'        
       value=\"\">Toutes les factures
       </option>";
    
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

  if($id_facture == "all"){
    // Recuperation de toutes les dépenses d'un client dans facture 
    $query = "SELECT nom_dest, pays_dest, nom_circuit, Duree_sejour, total_circuit, total_hotel, Nb_enfant, Nb_adulte,total_vol,  total_facture
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND
                  (nom = '".$nom."') AND
                  (prenom = '".$prenom."'))";
                 
    $stmt = ociparse($link, $query);
    ociexecute($stmt,OCI_DEFAULT);
  }else{
    // Recuperation des dépenses d'un client dans un facture
    $query = "SELECT nom_dest, pays_dest, nom_circuit, Duree_sejour, total_circuit, total_hotel, Nb_enfant, Nb_adulte,total_vol,  total_facture
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND (id_facture = ".$id_facture."))";
  }
 
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
        <td>Duree_Sejour</td>
	<td>Total_Circuit</td>
	<td>Total_Hotel</td>
	<td>NBenfant</td>
	<td>NBadulte</td>
	<td>Total_Vol</td>
	<td>Total_Facture</td>
      </tr>";

    while(OCIFetchInto ($stmt, $row, OCI_NUM)){
      $selected = "SELECTED"; 
       echo "
      <tr>";  
       foreach($row as $tmp){
	 if($tmp == NUUL){
	   
	 }
	 else{
	   echo "
             <td>".$tmp."</td>";
	 }
       }	          
    }
    echo "
       </tr>";
    echo "
    </table>"; 
  
 }
 
// Recuperation des dépenses d'un client dans un facture
$query = "SELECT total_circuit, total_hotel, total_vol
           FROM FACTURATION 
           WHERE ((categorie = 'TOTAL') AND (id_facture = ".$id_facture."))";

echo "
    </select><br/><br/>";  
  
echo "
    <select>
      <option value=\"\">Filtrer une facture</option>";  
 

 echo "
    </select><br/><br/>";  
 
    
    disconnect_db($link);
  
 


?>  
 </form>

</center>
