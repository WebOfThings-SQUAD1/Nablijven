

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./public/assets/main.css">
    <title> Login</title>
</head>

<body background="./public/assets/defaultbg-2.jpeg">
    <div class="container">

        <div class="user_icon">
        <!-- <img src="./public/assets/_img_login_user.jpeg" class="user-icon" alt="logo" width="200px" height="200p"> -->
        <img src="./public/assets/usericon.png" class="user-icon" alt="logo" width="200px" height="200p">
        </div>
        <div class="user_text">User</div>

        <div class="controls">
            <div class="inputControl" id="container_pw">
                <input type="password" class="input_password" id="input_password" placeholder=" Password">
                <button id="password_button" type="button" value=" ➔"> ➔</button>
            </div>

            <div  id="container_error" class="hide">
                <span type="disabled" class="input_password">Password incorrect. Try Again.</span>
                <button id="error_close">Ok</button>
            </div>
        </div>
        


    </div>
    <script type="text/javascript" src="./public/assets/main.js"></script>
</body>

</html>
