#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "CESJT";
const char* pass = "itisjtsmg";
uint8_t ventilafunca =0;
uint8_t servofunc1 =0;
uint8_t servofunc2 =0;
uint8_t servofunc3 =0;
uint8_t servofunc4 =0;
uint8_t servofunc5 =0;
uint8_t servofunc6 =0;
uint8_t servofunc7 =0;
Servo Svencoc;
Servo Svendo2;
Servo Svenofi;
Servo Spuegar;
Servo Spueban;
Servo Spueent;
Servo Spuedo2;
Servo Sventi;
ESP8266WebServer server(80);
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
                background-image: url(https://scontent.faep9-2.fna.fbcdn.net/v/t39.30808-6/396290953_122119261118073876_4206895724859313995_n.jpg?_nc_cat=111&ccb=1-7&_nc_sid=3635dc&_nc_ohc=p4LH1SMtCR4AX8bv55s&_nc_ht=scontent.faep9-2.fna&oh=00_AfDMjLHWv1TGnNV4yAZELKHvGpKyA4Yf6Q2UXp1UBRJbjw&oe=656C3A5D);
                background-repeat: no-repeat;
                background-position: 50% 50%, center center;
                display: flex;
                flex-direction: column;
                height: 100vh;
                width: 100vw;
                font-family: "Poppins", sans-serif;
            }

            .ulMenu {
                position: relative;
                font-size: 3em;
            }
            
            .container-clock {
                position: absolute;
                bottom: 150px;
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
                <li class="liMenu" id="Bano">
                    <span class="textMenu" data-text="Bano">Bano</span>
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
            const habitaciones = ['Living', 'Cocina', 'Comedor', 'Garage', 'Dorm1', 'Dorm2', 'Pasillo', 'Oficina', 'Bano', 'Entrada']
            const arrayPuerta = ['Living', 'Cocina', 'Comedor', 'Pasillo', 'Oficina']
            const arrayVentana = ['Living', 'Garage', 'Bano', 'Entrada', 'Pasillo']
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
            <p id="p_temperatura" style="margin-top: -10px;margin-left: -190px;font-size: 30px;">Temperatura: {TTT}</p>
            <p id="p_humedad" style="margin-top: -10px;margin-left: -190px;font-size: 30px;">Humedad: {HHH}</p>
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

String getPage() {
  String cpy = pag;
  cpy.replace("{TTT}", String(dht.readTemperature())+"°C");
  cpy.replace("{HHH}", String(dht.readHumidity())+"%");
  return cpy;
}

void handleRoot(){
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzliv(){
  Serial.print("4");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzcoc(){
  Serial.print("1");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzcom(){
  Serial.print("3");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzgar(){
  Serial.print("5");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzban(){
  Serial.print("2");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzent(){
  Serial.print("0");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzdo1(){
  Serial.print("6");
  String page = getPage(); 
  server.send(200, "text/html", page);
}

void luzdo2(){
  Serial.print("7");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzpas(){
  Serial.print("8");
  String page = getPage();
  server.send(200, "text/html", page);
}

void luzofi(){
  Serial.print("9");
  String page = getPage();
  server.send(200, "text/html", page);
}

void vencom(){
  Serial.print("10");
  String page = getPage();
  server.send(200, "text/html", page);
  
}

void vencoc(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc1 == 1){
    Svencoc.write(150);
    servofunc1 = 0;
  }else{
    Svencoc.write(50);
    servofunc1 = 1;
  }
}

void vendo1(){
  Serial.print("11");
  String page = getPage();
  server.send(200, "text/html", page);
}

void vendo2(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc2 == 1){
    Svendo2.write(140);
    servofunc2=0;
  }else{
    Svendo2.write(40);
    servofunc2=1;
  }
}

void venofi(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc3 == 1){
    Svenofi.write(130);
    servofunc3=0;
  }else{
    Svenofi.write(30);
    servofunc3=1;
  }
}

void puegar(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc4 ==1){
    Spuegar.write(180);
    servofunc4=0;
  }else{
    Spuegar.write(70);
    servofunc4=1;
  }
}

void pueban(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc5 ==1){
    Spueban.write(90);
    servofunc5=0;
  }else{
    Spueban.write(0);
    servofunc5=1;
  }
}

void pueent(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc6 ==1){
    Spueent.write(110);
    servofunc6=0;
  }else{
    Spueent.write(20);
    servofunc6=1;
  }
}

void puedo1(){
  Serial.print("12");
  String page = getPage();
  server.send(200, "text/html", page);
}

void puedo2(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(servofunc7 == 1){
    Spuedo2.write(90);
    servofunc7=0;
  }else{
    Spuedo2.write(0);
    servofunc7=1;
  }
}

void venti(){
  String page = getPage();
  server.send(200, "text/html", page);
  if(ventilafunca == 1){
    Sventi.write(90);
    ventilafunca = 0;
  }else{
    Sventi.write(0);
    ventilafunca = 1;
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  Svendo2.attach(13, 500, 2400);
  Svenofi.attach(15, 500, 2400);
  Svencoc.attach(4, 500, 2400);
  Spuegar.attach(12, 500, 2400);
  Spueban.attach(5, 500, 2400);
  Spueent.attach(16, 500, 2400);
  Spuedo2.attach(2, 500, 2400);
  Sventi.attach(14, 500, 2400);
  Svendo2.write(90);
  Svenofi.write(90);
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
  server.on("/luz/Bano", luzban);
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
  server.on("/puerta/Bano", pueban);
  server.on("/puerta/Entrada", pueent);
  server.on("/puerta/Dorm1", puedo1);
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
