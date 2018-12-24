#include <LiquidCrystal.h>          //load the liquid crystal library
#include <ESP8266WiFi.h>            //load the esp8266wifi library for networking
#include <WiFiClientSecure.h>       //load the WiFiClientSecure library
#include <WiFiClient.h>             //load the WiFiClient library
#include <ESP8266WebServer.h>       //load the ESP8266WebServer library

#include "index.h";

int soilPin = A0;
int moistureValue;
int soilPower = 0;                  //Variable for Soil moisture Power

int trigPin = 16;                   //trigger pin connected to pin 16
int echoPin = 5;                    //echo pin connected to pin 5

float pingTime;                     //time for ping to hit target and rseturn
float speedOfSoundInAir = 1254;     //for storing speed of sound
float waterLevel;                   //distance from sensor to target
float maxWaterLevel = 5.0;          //maximum waterLevel beyond which buzzer will be activated

/*Wi-Fi Settings*/
const char* ssid = "TP-LINK_403E";    // your wireless network name (SSID)
const char* password = "avnishy44";   // your Wi-Fi network password

WiFiClient client;                    //client object to deal with THINGSPEAK
ESP8266WebServer server1(80);         //Server on port 80

/*ThingSpeak Settings*/
const int channelID = 390558;
String writeAPIKey = "W4AW46UBF59VPKD9";      // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 10 * 1000;        // post data every 10 seconds

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  String s = MAIN_page;    
  s.replace("@@moistureContent@@", String(moistureValue));
  s.replace("@@waterLevel@@", String(waterLevel));
  server1.send(200, "text/html", s);    
}

void setup() {

  pinMode(soilPin , INPUT);           //set soilPin as input
  pinMode(trigPin , OUTPUT);          //set trigger pin as output
  pinMode(echoPin , INPUT);           //set echo pin as input
  
  Serial.begin(115200);               //start serial monitor

  /*CONECT TO WIFI*/
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);               //check for wifi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());           //print localIP address of your WiFi module

  server1.on("/", handleRoot);               //Which routine to handle at root location
  server1.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {

  server1.handleClient();                    //Handle client requests
  
  /*SEND DATA TO ARDUINO USING THIS SERIAL MONITOR*/
  Serial.print(WiFi.localIP());
  Serial.print(",");
  Serial.print(readSoil());
  Serial.print(",");
  Serial.print(readWaterLevel());
  Serial.println();

  writeOnCloud();                         //write sensor data on thingspeak Cloud
  
  delay(postingInterval);                 //wait and then post again
  
}


int readSoil()
{
    digitalWrite(soilPower, HIGH);        //turn soilPower pin "On"
    delay(10);                            //wait 10 milliseconds 
    moistureValue = analogRead(soilPin);  //Read the analog value form sensor 
    digitalWrite(soilPower, LOW);         //turn soilPower pin "Off"
    return moistureValue;                 //send current moisture value
}

int readWaterLevel(){
  
  /*FINDING THE WATER LEVEL*/
  digitalWrite(trigPin , LOW);    //set the trigger pin to low
  delayMicroseconds(2000);        //pause to let signal settle
  digitalWrite(trigPin , HIGH);   //set trig pin high
  delayMicroseconds(15);          //pause in high state
  digitalWrite(trigPin , LOW);    //bring trig pin back to low

  pingTime = pulseIn(echoPin , HIGH);  //tells arduino to measure period of high output of a pulse which goes low-high-low 
  //ping time is in micro seconds as sensor outputs values in micro seconds
  
  //convert ping time to hour
  pingTime = pingTime / 1000000.;   //converts ping time to seconds
  pingTime = pingTime / 3600.;      //converts pingtime to hours

  waterLevel = pingTime * speedOfSoundInAir / 2 * 100000.;  //calculate the distance in centimeters(by dividing by 100000 we convert km to cm)
  return waterLevel;
}

void writeOnCloud(){
  /*WRITING DATA TO THINGSPEAK CLOUD*/
  if (client.connect(server, 80)) {
    
    /*Construct API request body*/
    String body = "field1=";
           body += String(moistureValue);
           body += "&";
           body += "field2=";
           body += String(waterLevel);

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  client.stop();

}
