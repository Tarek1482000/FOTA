<?php

if(isset($_GET['status']) && $_GET['status'] === 'return')
{
	header("Location: upload.html");
}
?>