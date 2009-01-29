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
    $dates_entree[$i] = $_GET['date_entree'.$i];
    $dates_sortie[$i] = $_GET['date_sortie'.$i];
    $nb_simples[$i] = $_GET['nb_s'.$i];
    $nb_doubles[$i] = $_GET['nb_d'.$i];
  }
    
}

$adress = "?page=valider_reserv";

echo"
<center>
  <form action=\"pages/traitement_reserv.php\" method=\"post\">
    <select>
      <option value=\"\"
              onclick='parent.location=\"".$adress."\"'>
        S&eacute;lectionner un client
      </option>";

// Recuperation des clients
$query = "SELECT * FROM CLIENT";
$stmt = ociparse($link, $query);
ociexecute($stmt,OCI_DEFAULT);
$selected = "";

while(OCIFetchInto($stmt, $row, OCI_NUM)){
  if($row[0] == $id_client)
    $selected = "SELECTED";
  $ad = $adress."&client=".$row[0];
  echo "
      <option onclick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[3]." ".$row[4]."(".$row[6].")
      </option>";
  $selected = "";
}

  echo "
    </select><br/><br/>";


if($id_client != ""){
  $adress = $adress."&client=".$id_client;

  echo "
    <select>
      <option value=\"\"
              onclick='parent.location=\"".$adress."\"'>
        S&eacute;lectionner une destination
      </option>";

  // Recuperation des destinations
  $query = "SELECT * FROM DESTINATION";
  $stmt = ociparse($link, $query);
  ociexecute($stmt,OCI_DEFAULT);

  while(OCIFetchInto($stmt, $row, OCI_NUM)){
    if($row[0] == $id_dest)
      $selected = "SELECTED";
    $ad = $adress."&dest=".$row[0];
    echo "
      <option onclick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]."(".$row[2].")
      </option>";
    $selected = "";
  }
  
  echo "
    </select><br/><br/>";

  if($id_dest != ""){
    $adress = $adress."&dest=".$id_dest;

    echo "
    <select>
      <option value=\"\"
              onclick='parent.location=\"".$adress."\"'>
        S&eacute;lectionner un circuit
      </option>";

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
      <option onclick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]."
      </option>";
      $selected = "";
    }
  
    echo "
    </select><br/><br/>";
    
  }
  
  if($id_circ != ""){
    $adress = $adress."&circ=".$id_circ;

    echo "
    <select>
      <option value=\"\"
              onclick='parent.location=\"".$adress."\"'>
        S&eacute;lectionner un s&eacute;jour
      </option>";

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
      <option onclick='parent.location=\"".$ad."\"' 
              value=\"".$row[0]."\"".$selected.">
        ".$row[0].". ".$row[1]." jours(".$row[2].")
      </option>";
      $selected = "";
    }
  
    echo "
    </select><br/><br/>";
    
  }

  if($id_sejour != ""){
    echo "
    <table border=0 align=\"center\" bgcolor=\"white\">
      <tr>
        <td>S&eacute;lectionner une(des) &eacute;tape(s)</td>
      </tr>";
    $adress = $adress."&sejour=".$id_sejour;

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

      $ad3 = $ad2;

      /* Ajout des variables hotel */
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad2 = $ad2."&hotel".$i."=".$id_hotels[$i];
	$ad = $ad."&hotel".$i."=".$id_hotels[$i];
	$ad3 = $ad3."&hotel".$i."=".$id_hotels[$i];
      }
      
      $ad4 = $ad3;

      /* Ajout des variables date_entree */
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad3 = $ad3."&date_entree".$i."=".$dates_entree[$i];
	$ad = $ad."&date_entree".$i."=".$dates_entree[$i];
	$ad2 = $ad2."&date_entree".$i."=".$dates_entree[$i];
	$ad4 = $ad4."&date_entree".$i."=".$dates_entree[$i];
      }
      
      $ad5 = $ad4;

      /* Ajout des variables date_sortie */
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad4 = $ad4."&date_sortie".$i."=".$dates_sortie[$i];
	$ad = $ad."&date_sortie".$i."=".$dates_sortie[$i];
	$ad2 = $ad2."&date_sortie".$i."=".$dates_sortie[$i];
	$ad3 = $ad3."&date_sortie".$i."=".$dates_sortie[$i];
	$ad5 = $ad5."&date_sortie".$i."=".$dates_sortie[$i];
      }

      $ad6 = $ad5;

      /* Ajout des variables nb_s */
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad5 = $ad5."&nb_s".$i."=".$nb_simples[$i];
	$ad = $ad."&nb_s".$i."=".$nb_simples[$i];
	$ad2 = $ad2."&nb_s".$i."=".$nb_simples[$i];
	$ad3 = $ad3."&nb_s".$i."=".$nb_simples[$i];
	$ad4 = $ad4."&nb_s".$i."=".$nb_simples[$i];
	$ad6 = $ad6."&nb_s".$i."=".$nb_simples[$i];
      }

      $adress = $ad6;

      /* Ajout des variables nb_d */
      for($i=0 ; $i<$nb_total_etapes ; ++$i){
	if($num_etapes != $i)
	  $ad6 = $ad6."&nb_d".$i."=".$nb_doubles[$i];
	$ad = $ad."&nb_d".$i."=".$nb_doubles[$i];
	$ad2 = $ad2."&nb_d".$i."=".$nb_doubles[$i];
	$ad3 = $ad3."&nb_d".$i."=".$nb_doubles[$i];
	$ad4 = $ad4."&nb_d".$i."=".$nb_doubles[$i];
	$ad5 = $ad5."&nb_d".$i."=".$nb_doubles[$i];
	$adress = $adress."&nb_d".$i."=".$nb_doubles[$i];
      }

      echo "
      <tr>
        <td>
          <input type=\"checkbox\"
                 name=\"etape".$num_etapes."\"
                 onclick='parent.location=\"".$ad."\"'
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
            <option onclick='parent.location=\"".$ad2."\"'
                    value=\"".$row[0]."\"".$selected."/>
            ".$row[0].". H&ocirc;tel ".$row[1]."
            </option>";
	  $selected = "";
	}
                  
	echo "
          </select>
        </td>
        <td>
          <input type=\"text\"
                 name=\"date_entree".$num_etapes."\"";

	if($dates_entree[$num_etapes] == '')
	  echo "
                 value=\"date d'entr&eacute;e JJ/MM/AA\"";
	else
	  echo "
                 value=\"".$dates_entree[$num_etapes]."\"";
	echo "
                 onchange=\"location.replace('".$ad3."&date_entree".$num_etapes."='+this.value);\"
                 onfocus=\"if (this.value=='date d\'entr&eacute;e JJ/MM/AA') {this.value=''}\"
                 onblur=\"if (this.value=='') {this.value='date d\'entr&eacute;e JJ/MM/AA'}\"
          />
        </td>
        <td>
          <input type=\"text\"
                 name=\"date_sortie".$num_etapes."\"";
	if($dates_sortie[$num_etapes] == '')
	  echo "
                 value=\"date de sortie JJ/MM/AA\"";
	else
	  echo "
                 value=\"".$dates_sortie[$num_etapes]."\"";
	echo "
                 onchange=\"location.replace('".$ad4."&date_sortie".$num_etapes."='+this.value);\"
                 onfocus=\"if (this.value=='date de sortie JJ/MM/AA') {this.value=''}\"
                 onblur=\"if (this.value=='') {this.value='date de sortie JJ/MM/AA'}\"
          />
        </td>";
      }

      /* Si on a les dates d'entrée et sortie d'un hôtel */
      if( ($dates_entree[$num_etapes] != '') &&
	  ($dates_sortie[$num_etapes] != '') &&
	  ($id_hotels[$num_etapes] != '') &&
	  ($id_etapes[$num_etapes] != '')){

	// Recuperation des disponibilites d'hotels
	$query2 = "
         SELECT nb_s, nb_d, date_reservation_debut, date_reservation_fin
         FROM facturation
         WHERE (((date_reservation_debut <= to_date('".$dates_entree[$num_etapes]."','DD/MM/YY')) AND
                 (date_reservation_fin >= to_date('".$dates_entree[$num_etapes]."','DD/MM/YY'))) OR
                ((date_reservation_debut <= to_date('".$dates_sortie[$num_etapes]."','DD/MM/YY')) AND
                 (date_reservation_fin >= to_date('".$dates_sortie[$num_etapes]."','DD/MM/YY'))) OR
                ((date_reservation_debut >= to_date('".$dates_entree[$num_etapes]."','DD/MM/YY')) AND
                 (date_reservation_fin <= to_date('".$dates_sortie[$num_etapes]."','DD/MM/YY'))) AND
                (address_hotel IN (SELECT adresse 
                                   FROM hotel
                                   WHERE id_hotel=".$id_hotels[$num_etapes].")))";

	$stmt2 = ociparse($link, $query2);
	ociexecute($stmt2,OCI_DEFAULT);
	
 	while(OCIFetchInto($stmt2, $row, OCI_NUM)){
	  $nb_jours=0;

	  for( $i=mktime(explode("/",$dates_entree[$num_etapes])) ; 
               $i<=mktime(explode("/",$dates_fin[$num_etapes])) ; 
               $i+=86400, ++$nb_jours)
	    {
	      if(($i >= mktime(explode("/",$row[2]))) && ($i <= mktime(explode("/",$row[3])))){	
		if($nb_s_occup[$nb_jours] == '')
		  $nb_s_occup[$nb_jours]=0;
		if($nb_d_occup[$nb_jours] == '')
		  $nb_d_occup[$nb_jours]=0;

		$nb_s_occup[$nb_jours] += $row[0];
		$nb_d_occup[$nb_jours] += $row[1];
	      }
	    }
	}


	// Occupation maximum de l'hotel sur la periode
	$max_s_occup = 0;
	$max_d_occup = 0;
	for($i=1 ; $i<=$nb_jours ; ++$i){
	  if($nb_s_occup[$i] > $max_s_occup){
	    $max_s_occup = $nb_s_occup[$i];
	  }

	  if($nb_d_occup[$i] > $max_d_occup){
	    $max_d_occup = $nb_d_occup[$i];
	  }
	}


	// Récupération des capacites de l'hotel
	$query2 = "
         SELECT capac_s, capac_d
         FROM hotel
         WHERE (id_hotel =".$id_hotels[$num_etapes].")";

	$stmt2 = ociparse($link, $query2);
	ociexecute($stmt2,OCI_DEFAULT);
	
 	while(OCIFetchInto($stmt2, $row, OCI_NUM)){
	  $dispo_s = $row[0] - $max_s_occup;
	  $dispo_d = $row[1] - $max_d_occup;
	}
	
	// Chambres simples
	echo "
        <td>
          <select>
            <option value=\"\">
              Chambre simple
            </option>";
	
	for($i=0 ; $i<=$dispo_s ; ++$i){
	  if(($nb_simples[$num_etapes] != "") && ($nb_simples[$num_etapes] == $i))
	    $selected = " SELECTED";
	  echo "
            <option value=\"".$i."\"
                    name=\"nb_s".$num_etapes."\"
                    onclick='parent.location=\"".$ad5."&nb_s".$num_etapes."=".$i."\"'
                    ".$selected.">
              ".$i."
            </option>";
	  $selected = "";
	}

	echo "
          </select>
        </td>";
	
	// Chambres doubles
	echo "
        <td>
          <select>
            <option value=\"\">
              Chambre double
            </option>";
	
	for($i=0 ; $i<=$dispo_d ; ++$i){
	  if(($nb_doubles[$num_etapes] != "") && ($nb_doubles[$num_etapes] == $i))
	    $selected = " SELECTED";
	  echo "
            <option value=\"".$i."\"
                    name=\"nb_d".$num_etapes."\"
                    onclick='parent.location=\"".$ad6."&nb_d".$num_etapes."=".$i."\"'
                    ".$selected.">
              ".$i."
            </option>";
	  $selected = "";
	}

	echo "
          </select>
        </td>";
      }
      echo "
      </tr>";

      ++$num_etapes;
    }
  
    echo "
    </table><br/>";
    
    for($i=0 ; $i<=$num_etapes ; ++$i){
      if(($nb_simples[$i] != '') &&
	 ($nb_doubles[$i] != '')){
	echo "
      <select>
        <option value=\"\"
                onclick='parent.location=\"".$adress."\"'>
                Nombre d'adultes
        </option>
      </select>";

	echo "
      <select>
        <option value=\"\"
                onclick='parent.location=\"".$adress."\"'>
                Nombre d'enfants
        </option>
      </select>";
	break;
      }
    }

  }
}
?>
  </form>
</center>

<?php 

disconnect_db($link); 

?>
