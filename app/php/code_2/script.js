//===============================================
var g_file = null;
var g_slice = null;
var g_slice_size = 256;
var g_file_size = 0;
var g_start = 0;
var g_end = 0;
//===============================================
function onEvent(obj, action) {
    if(action == "image_load") {
        g_file = obj.files[0];
        g_file_size = g_file.size;
        message("<div>g_file_size : {0}</div>", g_file_size);
        setTimeout(onTimer, 1);
    }
}
//===============================================
function onTimer() {
    g_end = g_start + g_slice_size;
    if(g_file_size - g_end < 0) {
        g_end = g_file_size;
    }    
    g_slice = slice(g_file, g_start, g_end);
    onSend(g_slice, g_start, g_end);
    if (g_end < g_size) {
        g_start += g_slice_size;
        setTimeout(onTimer, 1);
    }
}
//===============================================
function onSlice(file, start, end) {
    var lSlice = (file.mozSlice) ? file.mozSlice :
    (file.webkitSlice) ? file.webkitSlice :
    (file.slice) ? file.slice : noop;
    return lSlice.bind(file)(start, end);
}
//===============================================
function onSend(slice, start, end) {
    var lFormData = new FormData();
    var lXmlHttp = new XMLHttpRequest();
    lXmlHttp.open('POST', '/upload', true);

    lFormData.append('start', start);
    lFormData.append('end', end);
    lFormData.append('file', slice);

    lXmlHttp.send(formdata);
}
//===============================================
