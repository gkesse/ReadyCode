//===============================================
var lMsg_Map = document.querySelectorAll(".msg");
//===============================================
var lObs_Options = {
    root: null,
    rootMargin: '0px',
    threshold: 1.0
};
//===============================================
var lObs = new IntersectionObserver(objs => {
    objs.forEach(obj => {
        var lSpot_Node = document.getElementsByClassName("spot")[0];
        if (obj.intersectionRatio > 0) {
            var lTarget = obj.target;
            if(lTarget.dataset.state == "on") {return;}
            // start lazy loading
            var lEditor = ace.edit(lTarget);
            lEditor.setTheme("ace/theme/monokai");
            lEditor.session.setMode("ace/mode/c_cpp");
            // end lazy loading
            lTarget.dataset.state = "on";
        } 
    });
}, lObs_Options);
//===============================================
lMsg_Map.forEach(obj => {
    lObs.observe(obj);
});
//===============================================
