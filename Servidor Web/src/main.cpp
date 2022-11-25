#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 4      // pino D2
#define DHTTYPE DHT11 // DHT 11
#define WIFI_SSID "PROF.RAFAEL"
#define WIFI_PASSWORD ""

int rele = 5;
int sensor_solo = A0;

IPAddress ip(192, 168, 1, 127);     // Configuração do IP do NodeMCU8266
IPAddress gateway(192, 168, 1, 1);  // Gataway
IPAddress subnet(255, 255, 255, 0); // Sub-rede

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";


// Sessão SMTP usado para envio de e-mail
DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
AsyncEventSource events("/events");


String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}


String processor(const String &var)
{
  
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"5\" " + outputState(rele) + "><span class=\"slider\"></span></label>";
    
    return buttons;
  }
  
  return String();

}



const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Web Server</title>
  <h3>Sistema de Irrigação Automático</h3>
  <meta name="viewport" content="width=device-width, initial-scale=1"; charset=utf-8>
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v6.2.0/css/all.css">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    i { font-size: 6em;}
    .topnav { overflow: hidden; background-color: #334A51; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 1000px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .card.temperatura{ color: #0e7c7b; }
    .card.solo{ color: #0e7c7b; }
    .card.solenoide{ color: #0e7c7b; }
    .switch {
  position: relative;
  display: inline-block;
  width: 60px;
  height: 34px;
}
/* Hide default HTML checkbox */
.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}
/* The slider */
.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  -webkit-transition: .4s;
  transition: .4s;
}
.slider:before {
  position: absolute;
  content: "";
  height: 26px;
  width: 26px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
}
input:checked + .slider {
  background-color: #2196F3;
}
input:focus + .slider {
  box-shadow: 0 0 1px #2196F3;
}
input:checked + .slider:before {
  -webkit-transform: translateX(26px);
  -ms-transform: translateX(26px);
  transform: translateX(26px);
}
/* Rounded sliders */
.slider.round {
  border-radius: 34px;
  position: center;
}
.slider.round:before {
  border-radius: 50%;
}
  </style>
</head>
<body>
  <div class="topnav">
    <h3>WEB SERVER</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card temperatura">
        <h4>Sensor de Temperatura</h4>
        <h1><i class="fa-solid fa-temperature-three-quarters"></i></h1><p><span class="reading"><span id="temperatura">%TEMPERATURA%</span>&deg;C</span></p>
      </div>
      <div class="card solo">
        <h4>Sensor de Solo</h4>
        <h1><i class='fas fa-seedling'></i></h1><p><span class="reading"><span id="solo">%SOLO%</span>&#37</span></p> 
      </div>
      <div class="card solenoide">
        <h4>Solenoide</h4>
        <h1><i class="fas fa-hand-holding-water"></i></h1><p><span class="reading"><span id="solenoide">%SOLENOIDE%</span></span></p> 
         <p>%BUTTONPLACEHOLDER%</p>
      </div>
  </div>
  <br> 
  <br> 
<script>

function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=0", true); 
  
  }
  else { xhr.open("GET", "/update?output="+element.id+"&state=1", true); 
  
  }
  xhr.send();
}

if (!!window.EventSource) {
 var source = new EventSource('/events');
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 source.addEventListener('temperatura', function(e) {
  console.log("temperatura", e.data);
  document.getElementById("temperatura").innerHTML = e.data;
 }, false);
 source.addEventListener('solo', function(e) {
  console.log("solo", e.data);
  document.getElementById("solo").innerHTML = e.data;
 }, false);
source.addEventListener('solenoide', function(e) {
  console.log("solenoide", e.data);
  document.getElementById("solenoide").innerHTML = e.data;
 }, false);
}
</script>
</body>
</html>)rawliteral";

void setup()
{
  Serial.begin(9600);
  dht.begin();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);

  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html, processor); });

   server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });




  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client)
                   {
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 2000); });
  server.addHandler(&events);
  server.begin();
}
void loop()
{
  // float h = dht.readHumidity();
  float t = dht.readTemperature();
  int est_solo = 100 - (analogRead(sensor_solo) * 100 / 1024);

  Serial.print("Umidade: ");
  Serial.print(est_solo);
  Serial.print(" %");
  Serial.print("  Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  Serial.println(digitalRead(rele));

  delay(1000);
  // events.send("ping",NULL,millis());
  events.send(String(t).c_str(), "temperatura", millis());
  events.send(String(est_solo).c_str(), "solo", millis());
  
  if(digitalRead(rele) == 0){
    events.send(String("Irrigando").c_str(), "solenoide", millis());
  }else{events.send(String("").c_str(), "solenoide", millis());}
}