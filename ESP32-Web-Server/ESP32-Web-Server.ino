// Thanks to Rui Santos for the Skeleton 
// This file is based on his code
// Check out his GitHub Profile
// https://github.com/RuiSantosdotme

#include <WiFi.h>

const char* ssid = "<add your WiFi SSID here>";
const char* password = "<add your password here>";

WiFiServer server(80);
String header;

String State_26 = "off";
String State_27 = "off";

const int output26 = 26;
const int output27 = 27;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);

  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   

  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                // String to hold incoming data from the client

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);

        header += c;
        if (c == '\n') {                    
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              State_26 = "on";
              digitalWrite(output26, HIGH);

            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              State_26 = "off";
              digitalWrite(output26, LOW);

            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              State_27 = "on";
              digitalWrite(output27, HIGH);

            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              State_27 = "off";
              digitalWrite(output27, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>GPIO 26 - State " + State_26 + "</p>");

            if (State_26=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } 
            
            else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            client.println("<p>GPIO 27 - State " + State_27 + "</p>");
            if (State_27=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            }
            
            else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
          
            client.println();
            break;
          } 
          
          else {
            currentLine = "";
          }
        } 
        
      else if (c != '\r') {  
        currentLine += c;
      }
    }
  }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}