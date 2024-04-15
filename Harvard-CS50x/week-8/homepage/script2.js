
var id = ['text1', 'name1', 'text2', 'name2'];
var words = ['You are your\nbest thing.', '- Toni Morrison', 'We will fail\nwhen we fail to try.', '- Rosa Parks'];
var speed = 50; /* The speed/duration of the effect in milliseconds */

document.addEventListener('DOMContentLoaded', function () {
    typeWriter(0, 0);
    });

function typeWriter(wordIndex, charIndex) {
    if (wordIndex < words.length) {
        let txt = words[wordIndex];
        if (charIndex < txt.length) {
            if (txt.charAt(charIndex) == '\n') {
                document.getElementById(id[wordIndex]).appendChild(document.createElement('br'));
                charIndex ++;
            } else {
                document.getElementById(id[wordIndex]).innerHTML += txt.charAt(charIndex);
                charIndex++;
            }

            setTimeout(typeWriter, speed, wordIndex, charIndex);
        } else {
            setTimeout(typeWriter, speed * 10, wordIndex + 1, 0);
        }
    }
  }

  /*setTimeout is a JavaScript function that allows you to delay the execution of a function or code block by a specified amount of time (in milliseconds).
  In this case, the setTimeout function is used to create a typewriter effect, where each character of a text is displayed with a delay between them.*/
