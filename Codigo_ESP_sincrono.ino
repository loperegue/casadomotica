#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
const char* ssid = "TeleCentro-5466";
const char* pass = "loslocoslopez";
ESP8266WebServer server(80);
Servo Svencom;
Servo Svencoc;
Servo Svendo1;
Servo Svendo2;
Servo Svenofi;
Servo Spuegar;
Servo Spueban;
Servo Spueent;
Servo Spuedo1;
Servo Spuedo2;
Servo Sventi;

char pag[] = R"====(
<!DOCTYPE html>
<html lang="es-ar">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta http-equiv="X-UA-Compatible" content="ie=edge">
        <title>Casa Domótica</title>
        <style>
            @import url("https://fonts.googleapis.com/css?family=Poppins");

            * {
                color: #476bad;
                margin: 0;
                font-size: 45px;
                padding: 0;
            }

            body {
                background-image: url(https://scontent.faep9-2.fna.fbcdn.net/v/t39.30808-6/396290953_122119261118073876_4206895724859313995_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=5f2048&_nc_ohc=bjPMlArDiYgAX_4wl2N&_nc_ht=scontent.faep9-2.fna&oh=00_AfAQpPkgW9u1-pizsJU8FClB9BG6OX64kdNE952LT0Dgxw&oe=65508ADD);
                background-repeat: no-repeat;
                background-position: 50% 50%, center center
                    /*left top*/
                ;
                display: flex;
                flex-direction: column;
                /* justify-content: center;
    align-items: center; */
                height: 100vh;
                width: 100vw;
                font-family: "Poppins", sans-serif;
            }

            /* ----- Código Youtube ----- */
            .ulMenu {
                position: relative;
                font-size: 3em;
            }
            
            .container-clock {
                position: absolute;
                bottom: 180px;
                margin-right: -120px;
            }

            .ulMenu .liMenu {
                list-style: none;
            }

            .ulMenu .liMenu .textMenu {
                position: relative;
                color: #4d3a3a;
                text-decoration: none;
                font-weight: 700;
            }

            .ulMenu .liMenu .textMenu:before {
                content: attr(data-text);
                position: absolute;
                top: -2px;
                width: 100%;
                color: #476bad;
                overflow: hidden;
                white-space: nowrap;
                cursor: pointer;
                transition: 0.2s ease-in-out;
            }

            .ulMenu:hover .liMenu .textMenu:before {
                width: 0;
            }

            .ulMenu .liMenu:hover .textMenu:before {
                width: 100%;
            }
            .rowDiv {
                position: absolute;
                left: 30px;
                margin-top: 100px;
            }
            .botones {
                width: 150px;
                height: 150px;
                border-radius: 100px;
                font-family: "Poppins", sans-serif;
                font-weight: bold;
                border-color: #777778;
                border-width: 10px;
                border-style: solid;
                transition-duration: 0.3s;
                background-color: #b2b3b8;
            }

            .botones:hover {
                background-color: white;
                border-color: #476bad;
            }

            .botones:active  {
                background-color: #8dabe2;
            }
            

        </style>
    </head>
    <body>
        <div>
            <center>
                <h1 style="font-size: 66px;">DHouse</h1>
                <h4 style="margin-top: -25px;font-size: 33px;">Control</h4>
            </center>
        </div>
        <div class="rowDiv">
            <ul class="ulMenu">
                <li class="liMenu" id="Living">
                    <span class="textMenu" data-text="Living" style="colo">Living</span>
                </li>
                <li class="liMenu" id="Cocina">
                    <span class="textMenu" data-text="Cocina">Cocina</span>
                </li>
                <li class="liMenu" id="Comedor">
                    <span class="textMenu" data-text="Comedor">Comedor</span>
                </li>
                <li class="liMenu" id="Garage">
                    <span class="textMenu" data-text="Garage">Garage</span>
                </li>
                <li class="liMenu" id="Baño">
                    <span class="textMenu" data-text="Baño">Baño</span>
                </li>
                <li class="liMenu" id="Entrada">
                    <span class="textMenu" data-text="Entrada">Entrada</span>
                </li>
                <li class="liMenu" id="Dorm1">
                    <span class="textMenu" data-text="Dormitorio 1">Dormitorio 1</span>
                </li>
                <li class="liMenu" id="Dorm2">
                    <span class="textMenu" data-text="Dormitorio 2">Dormitorio 2</span>
                </li>
                <li class="liMenu" id="Pasillo">
                    <span class="textMenu" data-text="Pasillo">Pasillo</span>
                </li>
                <li class="liMenu" id="Oficina">
                    <span class="textMenu" data-text="Oficina">Oficina</span>
                </li>
            </ul>
        </div>
            <div style="position: absolute; right: 120px;">
                <br>
                <a href="/luz"onclick="location.href=this.href+'/'+habitacionSeleccionada;return false;">
                    <button id="luces" class="botones" style="font-size: 40px;">Luz</button>
                </a>
                <br>
                <br>
                <a href="/puerta"onclick="location.href=this.href+'/'+habitacionSeleccionada;return false;">
                    <button id="puerta" class="botones" style="font-size: 35px;">puerta</button>
                </a>                
                <br>
                <br>
                <a href="/ventana"onclick="location.href=this.href+'/'+habitacionSeleccionada;return false;">
                    <button id="ventana" class="botones" style="font-size: 30px;">ventana</button>
                </a>                
                <br>
                <br>
                <a href="/ventilador"onclick="location.href=this.href+'/'+habitacionSeleccionada;return false;">
                    <button id="ventilador" class="botones" style="font-size: 25px;">ventilador</button>
                </a>            
            </div>
        <script>
            const habitaciones = ['Living', 'Cocina', 'Comedor', 'Garage', 'Dorm1', 'Dorm2', 'Pasillo', 'Oficina', 'Baño', 'Entrada']
            const arrayPuerta = ['Living', 'Cocina', 'Comedor', 'Pasillo', 'Oficina']
            const arrayVentana = ['Living', 'Garage', 'Baño', 'Entrada', 'Pasillo']
            const divLuces = document.getElementById('luces');
            const divPuerta = document.getElementById('puerta');
            const divVentana = document.getElementById('ventana');
            const divVentilador = document.getElementById('ventilador');
            let habitacionSeleccionada;
            for (let i = 0; i < habitaciones.length; i++) {
                const habitacion = document.getElementById(habitaciones[i]);
                habitacion.addEventListener('click', () => {
                    habitacionSeleccionada = habitacion.id;
                    if (arrayPuerta.includes(habitacion.id)) {
                        divPuerta.style.visibility = 'hidden';
                    } else {
                        divPuerta.style.visibility = 'visible';
                    }
                    if (arrayVentana.includes(habitacion.id)) {
                        divVentana.style.visibility = 'hidden';
                    } else {
                        divVentana.style.visibility = 'visible';
                    }
                    if (habitacion.id !== 'Oficina') {
                        divVentilador.style.visibility = 'hidden';
                    } else {
                        divVentilador.style.visibility = 'visible';
                    }
                });
            }
        </script>
    </body>
    <body>
        <style>
            * {
                align-items: center;
            }
        </style>
        <div class="container-clock">
            <h1 id="date" style="margin-top: -130px;margin-left: -190px;font-size: 30px;">date</h1>
            <p id="time" style="margin-top: -10px;margin-left: -190px;font-size: 30px;">00:00:00</p>
            <p id="p_temperatura" style="margin-top: -10px;margin-left: -190px;font-size: 30px;">Temperatura:</p>
            <p id="p_humedad" style="margin-top: -10px;margin-left: -190px;font-size: 30px;">Humedad:</p>
        </div>
        <script>
            const time = document.getElementById('time');
            const date = document.getElementById('date');
            const monthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
            const interval = setInterval(() => {
                const local = new Date();
                let day = local.getDate(),
                    month = local.getMonth(),
                    year = local.getFullYear();
                time.innerHTML = local.toLocaleTimeString();
                date.innerHTML = `${day} ${monthNames[month]} ${year}`;
            }, 1000);
        </script>
    </body>
</html>
)====";

void handleRoot(){
  server.send(200, "text/html", pag);
}

void luzliv(){
  Serial.print("4");
  server.send(200, "text/html", pag);
}

void luzcoc(){
  Serial.print("1");
  server.send(200, "text/html", pag);
}

void luzcom(){
  Serial.print("3");
  server.send(200, "text/html", pag);
}

void luzgar(){
  Serial.print("5");
  server.send(200, "text/html", pag);
}

void luzban(){
  Serial.print("2");
  server.send(200, "text/html", pag);
}

void luzent(){
  Serial.print("0");
  server.send(200, "text/html", pag);
}

void luzdo1(){
  Serial.print("6");
  server.send(200, "text/html", pag);
}

void luzdo2(){
  Serial.print("7");
  server.send(200, "text/html", pag);
}

void luzpas(){
  Serial.print("8");
  server.send(200, "text/html", pag);
}

void luzofi(){
  Serial.print("9");
  server.send(200, "text/html", pag);
}

void vencom(){
  Svencom.attach(10);
  if(Svencom.read() > 70){
    Svencom.write(135);
  }else{
    Svencom.write(45);
  }
  server.send(200, "text/html", pag);
}

void vencoc(){
  Svencoc.attach(4);
  if(Svencoc.read() > 70){
    Svencoc.write(135);
  }else{
    Svencoc.write(45);
  }
  server.send(200, "text/html", pag);
}

void vendo1(){
  Svendo1.attach(13);
  if(Svendo1.read() > 70){
    Svendo1.write(135);
  }else{
    Svendo1.write(45);
  }
  server.send(200, "text/html", pag);
}

void vendo2(){
  Svendo2.attach(11);
  if(Svendo2.read() > 70){
    Svendo2.write(135);
  }else{
    Svendo2.write(45);
  }
  server.send(200, "text/html", pag);
}

void venofi(){
  Svenofi.attach(15);
  if(Svenofi.read() > 70){
    Svenofi.write(135);
  }else{
    Svenofi.write(45);
  }
  server.send(200, "text/html", pag);
}

void puegar(){
  Spuegar.attach(12);
  if(Spuegar.read() > 40){
    Spuegar.write(90);
  }else{
    Spuegar.write(0);
  }
  server.send(200, "text/html", pag);
}

void pueban(){
  Spueban.attach(5);
  if(Spueban.read() > 40){
    Spueban.write(90);
  }else{
    Spueban.write(0);
  }
  server.send(200, "text/html", pag);
}

void pueent(){
  Spueent.attach(16);
  if(Spueent.read() > 40){
    Spueent.write(90);
  }else{
    Spueent.write(0);
  }
  server.send(200, "text/html", pag);
}

void puedo1(){
  Spuedo1.attach(9);
  if(Spuedo1.read() > 40){
    Spuedo1.write(90);
  }else{
    Spuedo1.write(0);
  }
  server.send(200, "text/html", pag);
}

void puedo2(){
  Spuedo2.attach(8);
  if(Spuedo2.read() > 40){
    Spuedo2.write(90);
  }else{
    Spuedo2.write(0);
  }
  server.send(200, "text/html", pag);
}

void venti(){
  Sventi.attach(14);
  if(Sventi.read() > 40){
    Sventi.write(90);
  }else{
    Sventi.write(0);
  }
  server.send(200, "text/html", pag);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println("\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n Conectado a: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/luz/Living", luzliv);
  server.on("/luz/Cocina", luzcoc);
  server.on("/luz/Comedor", luzcom);
  server.on("/luz/Garage", luzgar);
  server.on("/luz/Baño", luzban);
  server.on("/luz/Entrada", luzent);
  server.on("/luz/Dorm1", luzdo1);
  server.on("/luz/Dorm2", luzdo2);
  server.on("/luz/Pasillo", luzpas);
  server.on("/luz/Oficina", luzofi);
  server.on("/ventana/Comedor", vencom);
  server.on("/ventana/Cocina", vencoc);
  server.on("/ventana/Dorm1", vendo1);
  server.on("/ventana/Dorm2", vendo2);
  server.on("/ventana/Oficina", venofi);
  server.on("/puerta/Garage", puegar);
  server.on("/puerta/Baño", pueban);
  server.on("/puerta/Entrada", pueent);
  server.on("/puerta/Dorm1", puedo1);
  server.on("/puerta/Dorm2", puedo2);
  server.on("/puerta/Dorm2", puedo2);
  server.on("/ventilador/Oficina", venti);
  server.on("/luz/undefined", handleRoot);
  server.on("/ventana/undefined", handleRoot);
  server.on("/puerta/undefined", handleRoot);
  server.on("/ventilador/undefined", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient(); 
}

