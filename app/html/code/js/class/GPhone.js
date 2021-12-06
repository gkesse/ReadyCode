//===============================================
class GPhone extends GObject {
    //===============================================
    slideIndex;
    //===============================================
    constructor() {
        super();
        this.slideIndex = 1;
    }
    //===============================================
    showSlides(index) {
        var i;
        var slides = document.getElementsByClassName("phone_slides");
        var dots = document.getElementsByClassName("phone_slide_bar_dot");
        this.slideIndex = index;
        if (index > slides.length) {this.slideIndex = 1}    
        if (index < 1) {this.slideIndex = slides.length}
        for (i = 0; i < slides.length; i++) {
            slides[i].style.display = "none";  
        }
        for (i = 0; i < dots.length; i++) {
            dots[i].className = dots[i].className.replace(" active", "");
        }
        slides[this.slideIndex-1].style.display = "block";  
        dots[this.slideIndex-1].className += " active";
    }
    //===============================================
}
//===============================================
