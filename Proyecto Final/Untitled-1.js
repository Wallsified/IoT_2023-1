/* 
Función que traduce (en teoria) el envio del cálculo de decibeles  
a la interfaz web. 
*/

setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("DECIBEL_ID").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/decibel", true);
  xhttp.send();
}, 100);

/* function recieveDecibels() {
  var decibelsAgain = new XMLHttpRequest();
  decibelsAgain.open("GET", "/decibel", true);
  decibelsAgain.send();
  return decibelsAgain.responseText;
}

function changeOpacity() {
  var stringDecibel = recieveDecibels();
  var db = Number(stringDecibel);
  switch (db) {
    case 0 < db <= 29:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      break;
    case 30 <= db <= 59:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      break;
    case 60 <= db <= 89:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      document.getElementsByClassName("segment-3").style.opacity = 100;
      break;
    case 90 <= db <= 119:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      document.getElementsByClassName("segment-3").style.opacity = 100;
      document.getElementsByClassName("segment-4").style.opacity = 100;
      break;
    case 120 <= db <= 149:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      document.getElementsByClassName("segment-3").style.opacity = 100;
      document.getElementsByClassName("segment-4").style.opacity = 100;
      document.getElementsByClassName("segment-5").style.opacity = 100;
      break;
    case 150 <= db <= 179:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      document.getElementsByClassName("segment-3").style.opacity = 100;
      document.getElementsByClassName("segment-4").style.opacity = 100;
      document.getElementsByClassName("segment-5").style.opacity = 100;
      document.getElementsByClassName("segment-6").style.opacity = 100;
      break;
    case 180 <= db <= 200:
      document.getElementsByClassName("segment-1").style.opacity = 100;
      document.getElementsByClassName("segment-2").style.opacity = 100;
      document.getElementsByClassName("segment-3").style.opacity = 100;
      document.getElementsByClassName("segment-4").style.opacity = 100;
      document.getElementsByClassName("segment-5").style.opacity = 100;
      document.getElementsByClassName("segment-6").style.opacity = 100;
      document.getElementsByClassName("segment-7").style.opacity = 100;
      break;
  }
} */

/* 
La familia de funciones xPartOpacity cambian la opacidad del elemento en HTML, mediante CSS
*/
/* function onePartOpacity(event) {
  const onePart = event.target;
  onePart.setAttribute("style", "opacity = 100%");
}

function twoPartOpacity(event) {
  const twoPart = event.target;
  twoPart.setAttribute("style", "opacity = 100%");
}

function threePartOpacity(event) {
  const threePart = event.target;
  threePart.setAttribute("style", "opacity = 100%");
}

function fourPartOpacity(event) {
  const fourPart = event.target;
  fourPart.setAttribute("style", "opacity = 100%");
}

function fivePartOpacity(event) {
  const fivePart = event.target;
  fivePart.setAttribute("style", "opacity = 100%");
} */

/* function sixPartOpacity(event) {
  const sixPart = event.target;
  sixPart.setAttribute("style", "opacity = 100%");
}

function sevenPartOpacity(event) {
  const sevenPart = event.target;
  sevenPart.setAttribute("style", "opacity = 100%");
}
 */
/* 
Función que interactua con los segmentos de la bateria en sentido de los decibeles
detectados por el ESP32.

Nota. Seguramente esto se puede super simplificar y optmizar, igual que lo de arriba,
pero la verdad no somos programadores de JavaScript asi que se intentó. 
*/

/* setOpacity(function () {
  var decibels = new XMLHttpRequest();
  decibels.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("SENSOR_ID").innerHTML = this.responseText;
    }
    decibels.open("GET", "/sensor", true);
    decibels.send();
    var db = Number(decibels.responseText);
    switch (db) {
      case 0 < db <= 29:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        break;
      case 30 <= db <= 59:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        break;
      case 60 <= db <= 89:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        document.getElementsByClassName("segment-3").style.opacity = 100;
        break;
      case 90 <= db <= 119:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        document.getElementsByClassName("segment-3").style.opacity = 100;
        document.getElementsByClassName("segment-4").style.opacity = 100;
        break;
      case 120 <= db <= 149:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        document.getElementsByClassName("segment-3").style.opacity = 100;
        document.getElementsByClassName("segment-4").style.opacity = 100;
        document.getElementsByClassName("segment-5").style.opacity = 100;
        break;
      case 150 <= db <= 179:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        document.getElementsByClassName("segment-3").style.opacity = 100;
        document.getElementsByClassName("segment-4").style.opacity = 100;
        document.getElementsByClassName("segment-5").style.opacity = 100;
        document.getElementsByClassName("segment-6").style.opacity = 100;
        break;
      case 180 <= db <= 200:
        document.getElementsByClassName("segment-1").style.opacity = 100;
        document.getElementsByClassName("segment-2").style.opacity = 100;
        document.getElementsByClassName("segment-3").style.opacity = 100;
        document.getElementsByClassName("segment-4").style.opacity = 100;
        document.getElementsByClassName("segment-5").style.opacity = 100;
        document.getElementsByClassName("segment-6").style.opacity = 100;
        document.getElementsByClassName("segment-7").style.opacity = 100;
        break;
    }
  };
}, 100);
 */
/* function changeOpacity() {
  var decibelString = new XMLHttpRequest();
  decibelString.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("SENSOR_ID").innerHTML = this.responseText;
    }
  decibelString.open("GET", "/sensor", true);
  decibelString.send();
  };
  var decibelToInt = Number(decibelString.responseText);
  switch (decibelToInt) {
    case 0 < decibelToInt <= 29:
      onePartOpacity();
      break;
    case 30 <= decibelToInt <= 59:
      onePartOpacity();
      twoPartOpacity();
      break;
    case 60 <= decibelToInt <= 89:
      onePartOpacity();
      twoPartOpacity();
      threePartOpacity();
      break;
    case 90 <= decibelToInt <= 119:
      onePartOpacity();
      twoPartOpacity();
      threePartOpacity();
      fourPartOpacity();
      break;
    case 120 <= decibelToInt <= 149:
      onePartOpacity();
      twoPartOpacity();
      threePartOpacity();
      fourPartOpacity();
      fivePartOpacity();
      break;
    case 150 <= decibelToInt <= 179:
      onePartOpacity();
      twoPartOpacity();
      threePartOpacity();
      fourPartOpacity();
      fivePartOpacity();
      sixPartOpacity();
      break;
    case 180 <= decibelToInt <= 200:
      onePartOpacity();
      twoPartOpacity();
      threePartOpacity();
      fourPartOpacity();
      fivePartOpacity();
      sixPartOpacity();
      sevenPartOpacity();
      break;
  }
} */
