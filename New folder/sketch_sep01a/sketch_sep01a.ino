#include "ESP8266WiFi.h"
#include <ESP8266WebServer.h>
const char* ssid = "DIGI_Adi"; //Enter SSID
const char* password = "1234543210"; //Enter Password

ESP8266WebServer server(80);

void handleRoot();  
void handleLed();// function prototypes for HTTP handlers
void handleNotFound();

void setup(void)
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  server.on("/",HTTP_GET, handleLed); 
  server.onNotFound(handleNotFound);   
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

bool state = false;

void loop(void){
  server.handleClient();   
  
  
  // Listen for HTTP requests from clients
}

void handleLed() {
  if(server.arg("led") == "True")
    digitalWrite(LED_BUILTIN, LOW);
  if(server.arg("led") == "False")
    digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/plain", "200: found");
  // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
