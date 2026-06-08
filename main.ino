#include <WiFi.h> //wifi lib
#include <WebServer.h> //http req

const char* ssid = "iPhone";
const char* password = "quixoteee";

WebServer server(80); //http server on port 80

//frontend
// This function returns a raw string of text formatted as a webpage.
// It maps perfectly to a front-end view template in web development.
String getHTML() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  // Simple CSS styling to make a clean, centered green button on your phone
  html += "<style>body{text-align:center; font-family:sans-serif; background:#f4f4f4; color:#333;}"
          ".btn{display:inline-block; padding:20px 40px; font-size:24px; background:#23c470; "
          "color:white; border:none; border-radius:8px; text-decoration:none; box-shadow:0 4px 6px rgba(0,0,0,0.1);}</style></head>";
  html += "<body><h1>ESP32-S3 Web Control</h1>";
  html += "<p>Press the button below to wirelessly trigger hardware execution.</p>";
  // When clicked, this hyperlink redirects your browser to the "/toggle" URL path
  html += "<p><a href='/toggle' class='btn'>TOGGLE ONBOARD LED</a></p>";
  html += "</body></html>";
  return html;
}
//route controllers/controllers

int ledPin = 48;

void handleRoot() {
    server.send(200, "text/html", getHTML()); //status 200
}

void handleToggle() {
    //reads e_state of led, inverts it, then writes the new !state back to the pin
    digitalWrite(ledPin, !digitalRead(ledPin));
    server.send(200, "text/html", getHTML());
}

//firmware setup
void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

//pointer to home wifi
    Serial.print("connecting to WiFi");
    WiFi.begin(ssid, password);

    //blocking loop: wait till router assigns IP
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected Successfully!");
    Serial.print("Your local URL is: http://"); Serial.println(WiFi.localIP());

    //url routing config
    server.on("/", handleRoot); //if base URL requested, run handleroot
    server.on("/toggle", handleToggle); //if /toggle path then run handleToggle. kinda like getmapping
    
    //fire up internal web server engine
    server.begin();
    Serial.println("HTTP Web Server Started!");

}

void loop() {
    //async network listener
    server.handleClient();
}