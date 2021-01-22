<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $row = $db->query("SELECT * FROM `board` WHERE idx = '{$_GET['idx']}'")->fetch(PDO::FETCH_OBJ);
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>수정</title>
</head>
<body>
    <form action="./update_action.php?idx=<?php echo $_GET['idx']?>" method="POST">
    <h1>제목 : <input type="text" name="subject" value="<?php echo $row->title ?>" style="width:500px;height:30px"><br> </h1>
    <textarea name="content" cols = "200" rows="30"><?php echo $row->content ?></textarea> <br>
    게시글 번호 : <?php echo $row->idx ?>
    || 작성자 : <?php echo $row->writer ?>
    || 작성일 : <?php echo $row->reg_date ?> <p>
    비밀번호 : 	<input type="password" name="pass" required><p>
    <button type="button" onclick="history.back();">리스트</button>
    <input type="submit" name="update" value="수정">
    <a href="./delete.php?idx=<?php echo $row->idx ?>"><input type="button" name="update" value="삭제"></a>
    </form>
</body>
</html>

