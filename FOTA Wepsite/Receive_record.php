<?php
if(isset($_GET['response']) && $_GET['response'] === 'ok') {
    $fileRead = fopen("Hex_file.txt", "r+");
    $fileWrite = fopen("Record_line.txt", "w");
    $line = fgets($fileRead);
	fwrite($fileWrite,$line);
    fclose($fileWrite);
    
    $Content = file_get_contents("Hex_file.txt");
    $Content = explode("\n", $Content);
    array_splice($Content, 0, 1);
    $newContent = implode("\n", $Content);
    file_put_contents('Hex_file.txt', $newContent);
    
if (feof($fileRead) || !$fileRead)
{
    $test = fopen("Update.txt", "w");
    fwrite($test, 'EAF0');
    fclose($test);
    header("Location: FlashedDone.html");
    exit();
}
    
    fclose($fileRead);
}
?>