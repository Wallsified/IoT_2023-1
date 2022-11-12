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
  