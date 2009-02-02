<h1>Ajouter un h&ocirc;tel</h1>

<center>
  <form action="pages/traitement_ajout.php?page=liste_hotel&table_name=HOTEL" method="post">
    <select title="ID_ETAPE" name="col0">
      <option value="">Choisir une etape</option>
<?php

include("functions.php");
$link = connect_db();

// Recuperation des etapes
$query = "SELECT * FROM ETAPE";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
      <option value=\"".$row[0]."\">".$row[0].". ".$row[2]."</option>";
}

?>
    </select><br/>
    <input type="text" title="NOM_HOTEL" name="col1" value="NOM_HOTEL"/><br/>
    <input type="text" title="ADRESSE" name="col2" value="ADRESSE"/><br/>
    <select title="ID_CLASSE" name="col3">
      <option value="">Choisir une classe d'<!--'-->h&ocirc;tel</option>
<?php

// Recuperation des etapes
$query = "SELECT * FROM CLASSE_HOTEL";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  echo "
      <option value=\"".$row[0]."\">".$row[0].". S:".$row[1].", D:".$row[2]."</option>";
}

disconnect_db($link);

?>
    </select><br/>
    <input type="text" title="CAPA_S" name="col4" value="CAPA_S"/><br/>
    <input type="text" title="CAPA_D" name="col5" value="CAPA_D"/><br/>
    <input type="submit" value="Ajouter"/>
  </form>
</center>
