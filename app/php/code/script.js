//===============================================
function onEvent(obj, action) {
    message(action + "...<br>");
    //===============================================
    if(action == "on_init") {
    }
    //===============================================
    else if(action == "image_load") {
        for(var i = 0; i < obj.files.length; i++) {
            (function() {
                var lFile = obj.files[i];
                var chunk_uploader = new MyChunkUploader();
                
                chunk_uploader.on_ready = function(response) {
                };

                chunk_uploader.on_done = function() {
                    message("<div>on_done...</div>");
                    message("<div>file_name : {0}</div>", lFile.name);
                    message("<div>file_size : {0} KB</div>", (lFile.size/(1024)).toFixed(2));
                };
                
                chunk_uploader.on_error = function(object, err_type) {
                    message("<div>on_error...</div>");
                };

                chunk_uploader.on_abort = function(object) {
                    message("<div>on_abort...</div>");
                };

                chunk_uploader.on_upload_progress = function(progress) {
                };

                chunk_uploader.upload_chunked('/upload.php',lFile);
            })();
        }
    }
    //===============================================
}
//===============================================
