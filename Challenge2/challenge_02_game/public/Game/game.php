<!DOCTYPE html>
<html>
	<head>
		<title>Infinite Mario - JavaScript</title>
        <script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.4.2/jquery.min.js"></script>
		<script type='text/javascript' src='code/midi.js'></script>
	</head>
    <style>
        body{
            display: flex;
            justify-content: center;
            align-items: center;
            width: 100vw;
            height: 100vh;
            background: black;
        }
    </style>
	<body>
		<canvas id="canvas" width="640" height="480">
			<p>Your browser does not support the canvas element.</p>
		</canvas>

        <!-- Enjine Includes -->
        <script src="Enjine/core.js"></script>
        <script src="Enjine/gameCanvas.js"></script>
        <script src="Enjine/keyboardInput.js"></script>
        <script src="Enjine/resources.js"></script>
        <script src="Enjine/drawable.js"></script>
        <script src="Enjine/state.js"></script>
        <script src="Enjine/gameTimer.js"></script>
        <script src="Enjine/camera.js"></script>
        <script src="Enjine/drawableManager.js"></script>
        <script src="Enjine/sprite.js"></script>
        <script src="Enjine/spriteFont.js"></script>
        <script src="Enjine/frameSprite.js"></script>
        <script src="Enjine/animatedSprite.js"></script>
        <script src="Enjine/collideable.js"></script>
        <script src="Enjine/application.js"></script>

        <!-- Actual game code -->
        <script src="code/setup.js"></script>
        <script src="code/spriteCuts.js"></script>
        <script src="code/level.js"></script>
        <script src="code/backgroundGenerator.js"></script>
        <script src="code/backgroundRenderer.js"></script>
        <script src="code/improvedNoise.js"></script>
        <script src="code/notchSprite.js"></script>
        <script src="code/character.js"></script>
        <script src="code/levelRenderer.js"></script>
        <script src="code/levelGenerator.js"></script>
        <script src="code/spriteTemplate.js"></script>
        <script src="code/enemy.js"></script>
        <script src="code/fireball.js"></script>
        <script src="code/sparkle.js"></script>
        <script src="code/coinAnim.js"></script>
        <script src="code/mushroom.js"></script>
		<script src="code/particle.js"></script>
		<script src="code/fireFlower.js"></script>
        <script src="code/bulletBill.js"></script>
        <script src="code/flowerEnemy.js"></script>
        <script src="code/shell.js"></script>

        <script src="code/titleState.js"></script>
        <script src="code/loadingState.js"></script>
        <script src="code/loseState.js"></script>
        <script src="code/winState.js"></script>
        <script src="code/mapState.js"></script>
        <script src="code/levelState.js"></script>

        <script src="code/music.js"></script>


        <script src="code/_endSingal.js"></script>
        <script src="code/_perlinSeeder.js"></script>


        <script>$(document).ready(function() { new Enjine.Application().Initialize(new Mario.LoadingState(), 320, 240) });</script>
	</body>
</html>
