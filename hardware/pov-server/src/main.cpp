#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "html.h"
#include "animations.h"
#include "conf/wifi-conf.h"

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED



WiFiServer server(80);

// Declare a led on/off variable
bool ledState = true;
int animation = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  //----------------- WiFi Setup -----------------//
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

  //----------------- LED Setup -----------------//
   pinMode(IR_pin,INPUT);
         for( int i = 0; i<8 ;i++ ) // setting the ports of the leds to OUTPUT
           {
            pinMode(pins[i], OUTPUT);
           }
                
         letterSpace =4;// defining the space between the letters (ms)         
         delayTime =1;// defining the time dots appear (ms)
}


void loop() {

  //----------------- LED Loop -----------------//
 if(digitalRead(IR_pin)==LOW && ledState == true)
  {
    setAnimation(animation);
 
  }

  //----------------- WiFi Loop -----------------//
   WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println(html); // Send the HTML page

            // the content of the HTTP response follows the header:
            //client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            //client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Turn on or off the all the LEDs
        if (currentLine.endsWith("GET /api/display/on")) {
          ledState = true;
        }
        if (currentLine.endsWith("GET /api/display/off")) {
          ledState = false;
        }
        // Set animation api/display/animate/[id]
        if (currentLine.endsWith("GET /api/display/animate/1")) {
          Serial.println("GET /api/display/animate/1");
          animation = 1;
        }
        // Set animation api/display/animate/[id]
        if (currentLine.endsWith("GET /api/display/animate/2")) {
          Serial1.println("GET /api/display/animate/2");
          animation = 2;
        }
        // Set animation api/display/animate/[id]
        if (currentLine.endsWith("GET /api/display/animate/3")) {
          Serial1.println("GET /api/display/animate/3");
          animation = 3;
        }

        
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}