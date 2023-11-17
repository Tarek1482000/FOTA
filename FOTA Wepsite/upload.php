<?php
if(isset($_FILES['upload'])) {

   // Define a variable to store the file name
   $fileName = $_FILES['upload']['name'];

   // Define a variable to store the temporary file name
   $fileTempName = $_FILES['upload']['tmp_name'];

   // Define the destination folder for the uploaded file (not needed in this case)
   $uploadDir = "uploads/";

   // Check if there's any error with the uploaded file
   if($_FILES['upload']['error'] === UPLOAD_ERR_OK) {

      // Read the uploaded file data
      $fileData = file_get_contents($fileTempName);

      // Write the file data to the Hex_file.txt file
      if(file_put_contents('Hex_file.txt', $fileData)) {
         // Write "EAF1" into the Update.txt file
         file_put_contents('Update.txt', 'EAF1');
         
         // Redirect to uploadpagedone.html
         header("Location: uploadpagedone.html");
         exit();
      } else {
         echo "Error writing file!";
      }

   } else {
      echo "Error uploading file!";
   }
}
