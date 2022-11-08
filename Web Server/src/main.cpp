#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

#include <DHT.h>
#include <Adafruit_Sensor.h>
#define DHTPIN 4 // pino D2
#define DHTTYPE DHT11 // DHT 11
 



#define WIFI_SSID "PROF.RAFAEL"
#define WIFI_PASSWORD ""
IPAddress ip(192,168,1,123); //Configuração do IP do NodeMCU8266
IPAddress gateway(192,168,1,1); // Gateway
IPAddress subnet(255,255,255,0); //Sub-rede

// Sessão SMTP usado para envio de e-mail 
DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
AsyncEventSource events("/events");




String processor(const String& var){

  return String();
}




const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Web Server</title>
  <h3>Web Server - Sistema de Irrigação Automático</h3>
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
    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .card.temperatura{ color: #0e7c7b; }
  </style>
</head>
<body>
  <div class="topnav">
    <h3>WEB SERVER</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card temperatura">
        <h1><i class="fa-solid fa-temperature-three-quarters"></i></h1><p><span class="reading"><span id="temperatura">%TEMPERATURA%</span>&deg;C</span></p>
      </div>
  </div>
  <br> 
  <br> 


<script>
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







                

}
</script>
</body>
</html>)rawliteral";




void setup() {



  
  Serial.begin(9600);

  dht.begin();


  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

// Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 2000);
  });
  server.addHandler(&events);
  server.begin();


}
void loop() {
  
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %");
    Serial.print("  Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");

  delay(1000);
  
 
    //events.send("ping",NULL,millis());
    events.send(String(t).c_str(),"temperatura",millis());

        

  
}