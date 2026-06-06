#include <WiFi.h> //wifi lib
#include <WebServer.h> //http req

const char* ssid = "1051Top";
const char* password = "Secord1051A";

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

//route controllers/controllers

void handleRoot() {
    server.send(200, "text/html", getHTML()); //status 200
}

void handleToggle() {
    //reads e_state of led, inverts it, then writes the new !state back to the pin
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    server.send(200, "text/html", getHTML());
}

//firmware setup



