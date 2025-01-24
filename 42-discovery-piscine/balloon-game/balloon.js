document.addEventListener('DOMContentLoaded', function () {
  const balloon = document.getElementById('balloon');
  const colors = ['red','green', 'blue'];
  let currentColorIndex = 0;
let balloonSize = 200;
  balloon.addEventListener('click', function () {
    currentColorIndex = (currentColorIndex + 1) % colors.length;
    balloon.style.backgroundColor = colors[currentColorIndex];

 // Increase size by 10px
    balloonSize += 10;

    // Set a maximum size of 420px and reset to the initial size if exceeded
    if (balloonSize > 420) {
      balloonSize = 150; // Reset to initial size
    }

    balloon.style.width = balloonSize + 'px';
    balloon.style.height = balloonSize + 'px';
          });
});
