"use strict";  
document.getElementById("colorButton").addEventListener("click", myFunc);
function getRandomColor() {
    const letters ="0123456789ABCDEF"
    let color = "#";
        for(let i=0; i<6; i++) {
            color += letters[Math.floor(Math.random() * 16)];
}
    return color;
}

function changeColor() {
    console.log("Changing color...");
    const randomColor = getRandomColor();
    document.body.style.backgroundColor = randomColor;
}
function myFunc() {
    changeColor();
}
