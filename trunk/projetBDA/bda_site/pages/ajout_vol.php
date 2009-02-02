<h1>Ajouter un vol</h1>

<center>
  <form action="pages/traitement_ajout.php?page=liste_vol&table_name=VOL" method="post">
    <select title="ID_DEST" name="col0">
      <option value="">Choisir une destination</option>
<?php

include("functions.php");
$link = connect_db();

// // Recuperation du nombre d'entrees
// $query = "SELECT count(*) FROM DESTINATION";
// $stmt = ociparse($link, $query);
// ociexecute($stmt,OCI_DEFAULT);

// while(OCIFetchInto($stmt, $row, OCI_NUM))
//   $nb_dest = $row[0];

// Recuperation des destinations
$query = "SELECT * FROM DESTINATION";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
      <option value=\"".$row[0]."\">".$row[0].". ".$row[1]." (".$row[2].")</option>";
}

disconnect_db($link);

?>
    </select><br/>
    <input type="text" title="PRIX_ENFANT" name="col1" value="PRIX_ENFANT"/><br/>
    <input type="text" title="PRIX_ADULTE" name="col2" value="PRIX_ADULTE"/><br/>
    <input type="submit" value="Ajouter"/>
  </form>
</center>
