<?php
    $db = new PDO("mysql:host=127.0.0.1;dbname=ufboard;charset=utf8","root","");
    $rows = $db->query("SELECT * FROM board")->fetchALL(PDO::FETCH_OBJ);


    if($rows) {
        echo "(연결상태 : 좋음)<br>";
    } else {
        die("파일 없음 : " .mysqli_error());
    }
?>

<!DOCTYPE html>
<head>
    <meta charset="UTF-8">
    <title>게시물 목록</title>

    <style> 
        table{ 
        border-top: 1px solid #444444; 
        border-collapse: collapse; 
        } 
        tr{ border-bottom: 1px solid #444444; 
            padding: 10px; 
            } 
        td{ border-bottom: 1px solid #efefef; 
            padding: 10px; 
            } 
        table .even{ background: #efefef; } 
        .text{ text-align:center; 
                padding-top:20px; 
                color:#000000 }
        .text:hover{ text-decoration: underline; } 
        a:link {color : #57A0EE; text-decoration:none;} 
        a:hover { text-decoration : underline;} </style>

</head>
<body>
<form action="./update.php" method="GET">
    <table align = "center">
    <caption><h2 align=center>게시판</h2></caption>
    <thead align = "center">
        <tr>
        <td width = "50" align="center">번호</td>
        <td width = "500" align = "center">제목</td>
        <td width = "100" align = "center">아이디</td>
        <td width = "200" align = "center">날짜</td>
        <td width = "80" align = "center"><button type="submit">수정</button></caption>
        <td width = "80" align = "center"><button type="button" onclick="location.href='./write.html'">글쓰기</button></caption>
        </td>
        </tr>
    </thead>
    <tbody>
        <tr>  
           
           <?php foreach ($rows as $row): ?>
           <td width = "50" align = "center"><?php echo $row->idx ?></td>
           <td width = "500" align = "center"><a href="./view.php?idx=<?php echo $row->idx ?>"><?php echo $row->title ?></a></td>
           <td width = "100" align = "center"><?php echo $row->writer ?></td>
           <td width = "200" align = "center"><?php echo $row->reg_date ?></td>
           <td width = "50" align = "center"><input type="radio" name="idx" value="<?php echo $row->idx ?>" required></td>
           </form>
        </tr>
    </tbody>  
    <?php endforeach?>
    </table>
    </form>
</body>
</html>