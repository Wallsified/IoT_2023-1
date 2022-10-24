/* 
Función que traduce el envio del voltaje del LDR del ESP32 a la interfaz web. 
*/
setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("SENSOR_ID").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/sensor", true);
  xhttp.send();
}, 100);

/*  
Función que hace los cambios entre el valor del slider http y como se ve reflejado en el ESP32
*/

function updateSliderPWM(element) {
  var sliderValue = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = sliderValue;
  console.log(sliderValue);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value=" + sliderValue, true);
  xhr.send();
}

/* 
Función que cambia el estado de los LEDS 1 y 5 del ESP32 según los switches en la interfaz. 
*/
function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if (element.checked) {
    xhr.open("GET", "/update?output=" + element.id + "&state=1", true);
  } else {
    xhr.open("GET", "/update?output=" + element.id + "&state=0", true);
  }
  xhr.send();
}
