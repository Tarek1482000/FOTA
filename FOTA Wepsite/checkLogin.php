<?php

$username = $_POST['username'];
$password = $_POST['password'];

if($username == "Tarek" && $password == "123") {
   echo "Welcome, " . $username . "!";
   header("Location: upload.html");
} else {
   echo "Invalid login credentials. Please try again.";
   header("Location: hostindex.html");
   exit;
}

?>