<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $row = $db->query("SELECT * FROM `board` WHERE idx = '{$_GET['idx']}'")->fetch(PDO::FETCH_OBJ);
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>내용</title>
</head>
<body>
    <h1>제목 : <?php echo $row->title ?> <br> </h1>
    <textarea cols = "200" rows="30" readonly ><?php echo $row->content ?></textarea> <br>
    게시글 번호 : <?php echo $row->idx ?>
    || 작성자 : <?php echo $row->writer ?>
    || 작성일 : <?php echo $row->reg_date ?> <p>
    <button type="button" onclick="history.back();">리스트</button>
</body>
</html>

