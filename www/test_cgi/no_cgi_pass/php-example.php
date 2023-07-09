
<h1>HELLO</h1>

<?php
 
  $say = htmlspecialchars($_GET['say']);
  $to  = htmlspecialchars($_GET['to']);

  echo  $say, ' ', $to;
  echo "Hello";
?>
