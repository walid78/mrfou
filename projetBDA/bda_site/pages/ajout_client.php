<h1>Ajouter un client</h1>

<center>
  <form action="pages/traitement_ajout.php?table_name=CLIENT" method="post">
    <input type="text" title="ADRESSE" name="col0" value="ADRESSE"/><br/>
    <input type="text" title="TEL" name="col1" value="TEL"/><br/>
    <input type="text" title="NOM" name="col2" value="NOM"/><br/>
    <input type="text" title="PRENOM" name="col3" value="PRENOM"/><br/>
    <input type="text" title="AGE" name="col4" value="AGE"/><br/>
    <input type="text" title="EMAIL" name="col5" value="EMAIL"/><br/>
    <input type="text" title="CLASSE_SOCIALE" name="col6" value="CLASSE_SOCIALE"/><br/>
    <select title="ID_DEST_PREFEREE" name="col7">
      <option value="">Choisir une destination pr&eacute;f&eacute;r&eacute;e</option>
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
    <input type="text" title="INVESTISSEMENT_MOYEN" name="col8" value="INVESTISSEMENT_MOYEN"/><br/>
    <input type="submit" value="Ajouter"/>
  </form>
</center>
