 <h1>Afficher les factures d un client </h1>
 
<?php

include("functions.php");
$link = connect_db();

$id_client = $_GET['client'];

?>

//formulaire

<center>
  <form action="pages/affichage_fact.php?" method="post">
    <select title="Client" name="sel1">
      <option value="">S&eacute;lectionner une facture pour un
      client</option>


<?php
      
// Recuperation des clients
$query = "SELECT * FROM CLIENT";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
        value=\"".$row[0]."\>
        ".$row[0].". ".$row[3]."".$row[4]."(".$row[6].")
      </option>";
}

?>
 </form>
</center>