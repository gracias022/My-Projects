let slideIndex = 0;
document.addEventListener('DOMContentLoaded', function() {
    showSlides();
});

// Next/previous controls
function plusSlides(n) {
    gotoSlides(slideIndex += n);
}

function currentSlide(n) {
    gotoSlides(slideIndex = n);
}

function gotoSlides(n) {
    let slides = document.querySelectorAll('.mySlides');
    for (let i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";
    }
    for (let j = 0; j < slides.length; j++) {
        slides[j].style.backgroundColor = "#bbb";
    }
    slides[slideIndex - 1].style.display = "block";
    slides[slideIndex - 1].style.backgroundColor = "#717171";
}

function showSlides() {
    let i;
    let slides = document.querySelectorAll('.mySlides');
    for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
    }
    slideIndex++;
    if (slideIndex > slides.length) {slideIndex = 1}
    slides[slideIndex-1].style.display = "block";
    setTimeout(showSlides, 2000); // Change image every 2 seconds
};
