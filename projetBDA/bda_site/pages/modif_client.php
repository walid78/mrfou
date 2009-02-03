<?php 

include("functions.php");
$link = connect_db();

$id_client = $_GET['id_client'];
$adress = "?page=modif_client";

echo"
<center>
  <form>
    <select>
      <option value=\"\"
              onclick='parent.location=\"".$adress."\"'>
        S&eacute;lectionner un client
      </option>";


// Recuperation des clients
$query = "SELECT id_client, nom, prenom, email 
          FROM client";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);
$selected = "";

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  if($row[0] == $id_client)
    $selected = "SELECTED";
  $ad = $adress."&id_client=".$row[0];
  echo "
      <option onclick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\" ".$selected.">
        ".$row[1]." ".$row[2]."(".$row[3].")
      </option>";
  $selected = "";
}

echo "
    </select>
  </form><br/><br/>";

if($id_client != ''){
  // Recuperation des clients
  $query = "SELECT nom, prenom, adresse, tel, email, classe_sociale, age
            FROM client
            WHERE id_client=".$id_client;
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);
  $selected = "";

  echo "
  <form action=\"pages/traitement_modif.php?id_client=".$id_client."\" method=\"post\">";

  while(OCIFetchInto($stmt, $row, OCI_NUM)){
    echo "
    Nom: 
    <input type=\"text\" 
           name=\"nom\"
           value=\"".$row[0]."\"
           onfocus=\"if (this.value=='".$row[0]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[0]."'}\"
    /><br/>

    Pr&eacute;nom: 
    <input type=\"text\" 
           name=\"prenom\"
           value=\"".$row[1]."\"
           onfocus=\"if (this.value=='".$row[1]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[1]."'}\"
    /><br/>

    Adresse: 
    <input type=\"text\" 
           name=\"adresse\"
           value=\"".$row[2]."\"
           onfocus=\"if (this.value=='".$row[2]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[2]."'}\"
    /><br/>

    T&eacute;l&eacute;phone: 
    <input type=\"text\" 
           name=\"tel\"
           value=\"".$row[3]."\"
           onfocus=\"if (this.value=='".$row[3]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[3]."'}\"
    /><br/>

    Email: 
    <input type=\"text\" 
           name=\"email\"
           value=\"".$row[4]."\"
           onfocus=\"if (this.value=='".$row[4]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[4]."'}\"
    /><br/>

    Classe sociale: 
    <input type=\"text\" 
           name=\"classe_sociale\"
           value=\"".$row[5]."\"
           onfocus=\"if (this.value=='".$row[5]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[5]."'}\"
    /><br/>

    &Acirc;ge: 
    <input type=\"text\" 
           name=\"age\"
           value=\"".$row[6]."\"
           onfocus=\"if (this.value=='".$row[6]."') {this.value=''}\"
           onblur=\"if (this.value=='') {this.value='".$row[6]."'}\"
    /><br/>";
  }
  
  echo "
    <input type=\"submit\" value=\"Envoyer\"
  </form>
</center>";

}

disconnect_db($link);
?>
