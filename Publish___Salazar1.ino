#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "ARTEFACTOS"
#define WLAN_PASS       "ARTEFACTOS"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "wpineda21"
#define AIO_KEY         "aio_uaSI59FyiA9WPU93wmYk535Ay2Sf"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds for Publishing***************************************/
// Setup a feed called 'photocell' for publishing.
Adafruit_MQTT_Publish BolitasVerdes = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensor1");

Adafruit_MQTT_Publish BolitasAzules = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensor2");

// Setup a feed called 'LDR' for publishing.
Adafruit_MQTT_Publish LDR = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ldr");

/****************************** Feeds for Subscribing***************************************/
// Setup a feed called 'slider' for subscribing to changes on the slider
Adafruit_MQTT_Subscribe Lab04 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/lab04", MQTT_QOS_1);

// Setup a feed called 'onoff' for subscribing to changes to the button
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff", MQTT_QOS_1);

/*************************** Sketch Code ************************************/

void slidercallback(double x) {
  Serial.print("Hey we're in a slider callback, the slider value is: ");
  Serial.println(x);
}

void onoffcallback(char *data, uint16_t len) {
  Serial.print("Hey we're in a onoff callback, the button value is: ");
  Serial.println(data);
  String message = String(data);
      message.trim();
      if (message == "ON") {digitalWrite(D0, HIGH);}
      if (message == "OFF") {digitalWrite(D0, LOW);}}

//*********************************************** SetUp *****************************/
void setup() {
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  delay(10);
  //****************************************** Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  //********************************************* Callback Functions
  Lab04.setCallback(onoffcallback);
  //onoffbutton.setCallback(onoffcallback);
  
  // Setup MQTT subscription for feed's.
  mqtt.subscribe(&Lab04);
  //mqtt.subscribe(&onoffbutton);

}
  int sensor1 = D2;// verde
  int sensor2= D1;// azules
  int valor = 0;
  int valor2 = 0;
  int contador = 0;
  int contador2 = 0;
//***************************************************** Loop ********************************/
void loop() {
  MQTT_connect();
  mqtt.processPackets(1000);
  if(! mqtt.ping()) {   // ping the server to keep the mqtt connection alive
    mqtt.disconnect();}

      // put your main code here, to run repeatedly:
      valor = digitalRead(sensor1);
      // Serial.println(valor);
      //delay(1000);
      if(valor == 1){
          contador++;
           Serial.println("las cosas Verdes como tus ojos fueron: ");
            Serial.println(contador);
      if (! BolitasVerdes.publish(contador)) {
          Serial.println(F("Failed"));
        } else {
          Serial.println(F("OK!"));
        }
      delay(3000);
          }else {      
          Serial.println("no se conto nada VERDE   majes :(");     
       };
      delay(1000); 

      
        valor2 = digitalRead(sensor2);
        // Serial.println(valor);
        delay(1000);
        if(valor2 == 1){
            contador2++;
            Serial.println("las cosas azules que conte fue: ");
            Serial.println(contador2);
             if (! BolitasAzules.publish(contador2)) {
                Serial.println(F("Failed"));
              } else {
                Serial.println(F("OK!"));
              }
            delay(3000);
            }else {      
            Serial.println("no conte nada Azul Majes ");     
         };

}

// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;}
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 10 seconds
       retries--;
       if (retries == 0) {       // basically die and wait for WDT to reset me
         while (1);}}
  Serial.println("MQTT Connected!");
}
