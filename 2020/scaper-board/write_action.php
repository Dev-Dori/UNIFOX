<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $sql = "
        INSERT INTO `board` (`idx`, `pass`, `title`, `writer`, `content`, `reg_date`)
         VALUES (NULL,'{$_POST['pass']}', '{$_POST['subject']}', '{$_POST['writer']}', '{$_POST['content']}', now());
    ";

    if($db->query($sql)){
        header("Location:./");            
    }else{
            printf-r($db->errorInfo());
    }
?>