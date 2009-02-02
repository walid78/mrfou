<h1>Ajouter une &eacute;tape</h1>

<center>
  <form action="pages/traitement_ajout.php?page=liste_etape&table_name=ETAPE" method="post">
    <input type="text" title="NO_ETAPE" name="col0" value="NO_ETAPE"/><br/>
    <select title="ID_CIRCUIT" name="col1">
      <option value="">Choisir un circuit</option>
<?php

include("functions.php");
$link = connect_db();

// Recuperation des destinations
$query = "SELECT * FROM CIRCUIT";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
      <option value=\"".$row[0]."\">".$row[0].". ".$row[1]."</option>";
}

disconnect_db($link);

?>
    </select><br/>
    <input type="text" title="DESCRIPTIF" name="col2" value="DESCRIPTIF"/><br/>
    <input type="submit" value="Ajouter"/>
  </form>
</center>
