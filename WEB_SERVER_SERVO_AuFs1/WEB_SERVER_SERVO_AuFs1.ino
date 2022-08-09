#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//===================//
#include "PageIndex.h"; //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file
#define LEDonBoard 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define ServoPort 16   //--> Defining Servo Port
#define backport 5
#define sidechanger 4
//==========================================//
const char *ssid = "APOLLO";
const char *password = "0978653421";
//==========================================//

Servo myservo;  //--> create servo object to control a servo
ESP8266WebServer server(80);  //--> Server on port 80

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
//----------------------------------------

//----------------------------------------Procedure for handling servo control
void handleServo() {
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);   //--> Move the servo motor according to the POS value
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plane", "");
}
// MOTORES TESTE AuFs 1
void handleMotorbackwards()  
{
  String back = server.arg("backwards");
  int motorbackwards = back.toInt();
  digitalWrite(backport,HIGH);
  digitalWrite(sidechanger,HIGH);
  delay (2000);
  digitalWrite(backport,LOW);
  digitalWrite(sidechanger,LOW);
}
//----------------------------------------
//----------------------------------------Setup----------------------------------------
void setup() {
  ArduinoOTA.begin();
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");

  pinMode(LEDonBoard, OUTPUT); //--> On Board LED port Direction output
  digitalWrite(LEDonBoard, HIGH); //--> Turn off Led On Board

  myservo.attach(ServoPort, 450, 3000); // attach(pin,min,max) PINO, pulso em microsegundos , MAX do pulso
  pinMode(backport, OUTPUT);  //DEFINIR MOTOR de saida
  pinMode(sidechanger, OUTPUT); //DEFINIR PORTA DE MUDANCA DE LADO
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(LEDonBoard, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------

  //----------------------------------------Initialize Webserver
  server.on("/", handleRoot);
  server.on("/setPOS", handleServo);
  server.on("/back", handleMotorbackwards);
  server.begin();
}
//=====================
//========LOOP=========
//=====================
void loop() {
  server.handleClient();
  //=========== BLACK BOX ============
  ArduinoOTA.handle();              //
  delay (500);                      //
  //==================================
}




// ESSE CODIGO TOTALMENTE NAO FOI ROBADO DO GIT HUB
