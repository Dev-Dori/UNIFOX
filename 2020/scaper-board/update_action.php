
<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $row = $db->query("SELECT * FROM `board` WHERE idx = '{$_GET['idx']}'")->fetch(PDO::FETCH_OBJ);
    $bpk = $_POST['pass'] ;
    $idx = $_GET['idx'] ;
    $pass = $row->writer;


    if ($bpk==$pass) {
    $sql = "
    UPDATE `board` SET
     title = '{$_POST['subject']}',
     content = '{$_POST['content']}'
     WHERE idx = '{$_GET['idx']}'
    ";


    }else{
        echo "<script>alert(\"비밀번호가 틀립니다\");history.back(-2)</script>";
    }

    if($db->query($sql)){
        print "<script language=javascript> alert('수정완료'); location.replace('./'); </script>";         
    }
?>

