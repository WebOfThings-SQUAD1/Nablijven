/**
	Represents a simple static sprite.
	Code by Rob Kleffner, 2011
*/

Enjine.Resources = {
    Images: {},

    Destroy: function() {
        delete this.Images;
        return this;
    },
    
    //***********************/
    //Images
    AddImage: function(name, src) {
        var tempImage = new Image();
		this.Images[name] = tempImage;
        tempImage.src = src;
        return this;
	},
	
	AddImages: function(array) {
		for (var i = 0; i < array.length; i++) {
            var tempImage = new Image();
            this.Images[array[i].name] = tempImage;
            tempImage.src = array[i].src;
        }
        return this;
	},
	
	ClearImages: function() {
		delete this.Images;
        this.Images = new Object();
        return this;
	},
	
	RemoveImage: function(name) {
		delete this.Images[name];
		return this;
	},
};