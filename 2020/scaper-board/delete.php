
<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $row = $db->query("SELECT * FROM `board` WHERE idx = '{$_GET['idx']}'")->fetch(PDO::FETCH_OBJ);
    $idx = $_GET['idx'] ;
    $pass = $row->writer;

?>

<!DOCTYPE html>
<head>
    <meta charset="UTF-8">
    <title>삭제 확인</title>
</head>
<body>
    <form action="./delete_action.php?idx=<?php echo $_GET['idx']?>" method="POST">
    정말로 삭제하시겠습니다?  <br>
    비밀번호를 한번 더 입력해주세요 :  <input type="password" name="pass" required>
    <button type="submit">확인</button>
    <button type="button" onclick="location.replace('./');">메인</button>
    </form>
</body>
</html>