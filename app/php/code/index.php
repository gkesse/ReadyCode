<!DOCTYPE html>
<html lang="fr">
    <head>
        <title>ReadyApp</title>
    </head>
    <body onload="onEvent(this, 'on_init')">
        <!-- ============================================ -->
        <div><input type="file" onchange="onEvent(this, 'image_load')" multiple/></div>
        <!-- ============================================ -->
        <div id="msg"></div>
        <!-- ============================================ -->
        <script src="/chunk-uploader.js"></script>
        <script src="/manager.js"></script>
        <script src="/script.js"></script>
        <!-- ============================================ -->
    </body>
</html>