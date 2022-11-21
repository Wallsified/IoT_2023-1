var db = { //ah yes, objects in JavaScript
  value: "", //atributo único del objeto db
  letmeKnow() {
    console.log("DB changed");
  },
  get giveDb() { //getter
    return this.value;
  },
  set setDB(value) { //setter
    this.value = value;
    //this.letmeKnow();
  },
};

setInterval(function () {
  var xhttp = new XMLHttpRequest(); //Request al ESP32
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) { //Digamos, si si hay algo del otro lado del código
      //var innerDB = document.getElementById("DECIBEL_ID").innerHTML;
      //document.getElementById("DECIBEL_ID").innerHTML = this.responseText;
      db.setDB = Number(this.responseText); //consideramos la respuesta y la transformamos a numero. 
      var giveMeSomeNoise = db.giveDb; //Asignamos la respuesta a una variable y de ahi trabajamos. 
      if (giveMeSomeNoise != 49) { //49 es el valor db promedio de un cuarto. Consideramos lecturas mayores.
        setTimeout(gameOn(giveMeSomeNoise), 3000); //función tipo delay de Javascript. Recibe una función y el tiempo. 
      } else if ((giveMeSomeNoise = 49)) {
        gameOff();
      }
    }
  };
  xhttp.open("GET", "/decibel", true); //Confirmamos solicitud.
  xhttp.send(); //Mandamos solicitud.
}, 100);

/* 
Función que considera un valor de entrada para alterar propiedades CSS de elementos HTML
*/
function gameOn(value) {
  if (49 <= value && value <= 51) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    console.log("Bingpot! Segmento uno activado");
    setTimeout(gameOff, 6000);
  } else if (52 <= value && value <= 54) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (55 <= value && value <= 57) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (58 <= value && value <= 60) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (61 <= value && value <= 63) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (64 <= value && value <= 66) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-6").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  } else if (67 <= value && value < 70) {
    document.getElementById("segment-1").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-2").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-3").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-4").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-5").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-6").setAttribute("style", "opacity:100%;");
    document.getElementById("segment-7").setAttribute("style", "opacity:100%;");
    document.getElementById("circle").setAttribute("style", "opacity:100%;");
    setTimeout(gameOff, 6000);
  }
}

/* 
Función contraria a gameOn. "Apaga" los elementos HTML del archivo. 
*/
function gameOff() {
  document.getElementById("segment-1").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-2").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-3").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-4").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-5").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-6").setAttribute("style", "opacity:0%;");
  document.getElementById("segment-7").setAttribute("style", "opacity:0%;");
  document.getElementById("circle").setAttribute("style", "opacity:0%;");
}
