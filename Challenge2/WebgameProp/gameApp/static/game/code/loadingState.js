/**
	State that loads all the resources for the game.
	Code by Rob Kleffner, 2011
*/

Mario.LoadingState = function() {
    this.Images = [];
    this.ImagesLoaded = false;
    this.ScreenColor = 0;
    this.ColorDirection = 1;
    this.ImageIndex = 0;
};

Mario.LoadingState.prototype = new Enjine.GameState();

Mario.LoadingState.prototype.Enter = function() {
    var i = 0;
    for (i = 0; i < 15; i++) {
        this.Images[i] = {};
    }
    
    this.Images[0].name = "background";
    this.Images[1].name = "endScene";
    this.Images[2].name = "enemies";
    this.Images[3].name = "fireMario";
    this.Images[4].name = "font";
    this.Images[5].name = "gameOverGhost";
    this.Images[6].name = "items";
    this.Images[7].name = "logo";
    this.Images[8].name = "map";
    this.Images[9].name = "mario";
    this.Images[10].name = "particles";
    this.Images[11].name = "racoonMario";
    this.Images[12].name = "smallMario";
    this.Images[13].name = "title";
    this.Images[14].name = "worldMap";

    this.Images[0].src = "/static/game/images/bgsheet.png";
    this.Images[1].src = "/static/game/images/endscene.gif";
    this.Images[2].src = "/static/game/images/enemysheet.png";
    this.Images[3].src = "/static/game/images/firemariosheet.png";
    this.Images[4].src = "/static/game/images/font.gif";
    this.Images[5].src = "/static/game/images/gameovergost.gif";
    this.Images[6].src = "/static/game/images/itemsheet.png";
    this.Images[7].src = "/static/game/images/logo.gif";
    this.Images[8].src = "/static/game/images/mapsheet.png";
    this.Images[9].src = "/static/game/images/mariosheet.png";
    this.Images[10].src = "/static/game/images/particlesheet.png";
    this.Images[11].src = "/static/game/images/racoonmariosheet.png";
    this.Images[12].src = "/static/game/images/smallmariosheet.png";
    this.Images[13].src = "/static/game/images/title.gif";
    this.Images[14].src = "/static/game/images/worldmap.png";
    
    Enjine.Resources.AddImages(this.Images);
    
    
    //load the array of tile behaviors
    Mario.Tile.LoadBehaviors();
};

Mario.LoadingState.prototype.Exit = function() {
    delete this.Images;
};

Mario.LoadingState.prototype.Update = function(delta) {
    if (!this.ImagesLoaded) {
        this.ImagesLoaded = true;
        var i = 0;
        for (i = 0; i < this.Images.length; i++) {
            if (Enjine.Resources.Images[this.Images[i].name].complete !== true) {
                this.ImagesLoaded = false;
                break;
            }
        }
    }
    
    this.ScreenColor += this.ColorDirection * 255 * delta;
    if (this.ScreenColor > 255) {
        this.ScreenColor = 255;
        this.ColorDirection = -1;
    } else if (this.ScreenColor < 0) {
        this.ScreenColor = 0;
        this.ColorDirection = 1;
    }
};

Mario.LoadingState.prototype.Draw = function(context) {
    if (!this.ImagesLoaded) {
        var color = parseInt(this.ScreenColor, 10);
        context.fillStyle = "rgb(" + color + "," + color + "," + color + ")";
        context.fillRect(0, 0, 640, 480);
    } else {
        context.fillStyle = "rgb(0, 0, 0)";
        context.fillRect(0, 0, 640, 480);
    }
};

Mario.LoadingState.prototype.CheckForChange = function(context) {
    if (this.ImagesLoaded) {
		//set up the global map state variable
		Mario.GlobalMapState = new Mario.MapState();
	
        context.ChangeState(new Mario.TitleState());
    }
};