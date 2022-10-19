//===============================================
// detecter l'evenement ctrl + v
//===============================================
window.addEventListener("paste", function(thePasteEvent){
    // Use thePasteEvent object here ...
}, false);

//===============================================
// recuperer la liste des elements
//===============================================
var items = pasteEvent.clipboardData.items;

//===============================================
// visualiser le contenu des elements
//===============================================
{
    name: "image.png", 
    lastModified: 1499172701225, 
    lastModifiedDate: Tue Jul 04 2017 14:51:41 GMT+0200 (W. Europe Daylight Time),
    webkitRelativePath: "", 
    size: 158453,
    type:"image/png",
    webkitRelativePath:""
}

//===============================================
// récupérer l'image du presse-papiers
//===============================================
function retrieveImageFromClipboardAsBlob(pasteEvent, callback){
	if(pasteEvent.clipboardData == false){
        if(typeof(callback) == "function"){
            callback(undefined);
        }
    };

    var items = pasteEvent.clipboardData.items;

    if(items == undefined){
        if(typeof(callback) == "function"){
            callback(undefined);
        }
    };

    for (var i = 0; i < items.length; i++) {
        // Skip content if not image
        if (items[i].type.indexOf("image") == -1) continue;
        // Retrieve image on clipboard as blob
        var blob = items[i].getAsFile();

        if(typeof(callback) == "function"){
            callback(blob);
        }
    }
}

//===============================================
// definir un canevas
//===============================================
<canvas style="border:1px solid grey;" id="mycanvas">

//===============================================
// afficher le Blob à l'intérieur d'un canevas
//===============================================
<script>
window.addEventListener("paste", function(e) {

    // Handle the event
    retrieveImageFromClipboardAsBlob(e, function(imageBlob){
        // If there's an image, display it in the canvas
        if(imageBlob){
            var canvas = document.getElementById("mycanvas");
            var ctx = canvas.getContext('2d');
            
            // Create an image to render the blob on the canvas
            var img = new Image();

            // Once the image loads, render the img on the canvas
            img.onload = function(){
                // Update dimensions of the canvas with the dimensions of the image
                canvas.width = this.width;
                canvas.height = this.height;

                // Draw the image
                ctx.drawImage(img, 0, 0);
            };

            // Crossbrowser support for URL
            var URLObj = window.URL || window.webkitURL;

            // Creates a DOMString containing a URL representing the object given in the parameter
            // namely the original Blob
            img.src = URLObj.createObjectURL(imageBlob);
        }
    });
}, false);
</script>

//===============================================
// recuperer l'image en base64
//===============================================
function retrieveImageFromClipboardAsBase64(pasteEvent, callback, imageFormat){
	if(pasteEvent.clipboardData == false){
        if(typeof(callback) == "function"){
            callback(undefined);
        }
    };

    var items = pasteEvent.clipboardData.items;

    if(items == undefined){
        if(typeof(callback) == "function"){
            callback(undefined);
        }
    };

    for (var i = 0; i < items.length; i++) {
        // Skip content if not image
        if (items[i].type.indexOf("image") == -1) continue;
        // Retrieve image on clipboard as blob
        var blob = items[i].getAsFile();

        // Create an abstract canvas and get context
        var mycanvas = document.createElement("canvas");
        var ctx = mycanvas.getContext('2d');
        
        // Create an image
        var img = new Image();

        // Once the image loads, render the img on the canvas
        img.onload = function(){
            // Update dimensions of the canvas with the dimensions of the image
            mycanvas.width = this.width;
            mycanvas.height = this.height;

            // Draw the image
            ctx.drawImage(img, 0, 0);

            // Execute callback with the base64 URI of the image
            if(typeof(callback) == "function"){
                callback(mycanvas.toDataURL(
                    (imageFormat || "image/png")
                ));
            }
        };

        // Crossbrowser support for URL
        var URLObj = window.URL || window.webkitURL;

        // Creates a DOMString containing a URL representing the object given in the parameter
        // namely the original Blob
        img.src = URLObj.createObjectURL(blob);
    }
}

//===============================================
// recuperer l'image en base64
//===============================================
window.addEventListener("paste", function(e){

    // Handle the event
    retrieveImageFromClipboardAsBase64(e, function(imageDataBase64){
        // If there's an image, open it in the browser as a new window :)
        if(imageDataBase64){
            // data:image/png;base64,iVBORw0KGgoAAAAN......
            window.open(imageDataBase64);
        }
    });
}, false);

//===============================================
// liens
//===============================================

// presse-papier : coller image
https://ourcodeworld.com/articles/read/491/how-to-retrieve-images-from-the-clipboard-with-javascript-in-the-browser

// Coller une image du presse-papiers à l'aide de JavaScript
https://stackoverflow.com/questions/490908/paste-an-image-from-clipboard-using-javascript
