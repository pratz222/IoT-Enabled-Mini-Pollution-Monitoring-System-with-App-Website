#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "MQ135.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Provide the token generation process info.
#include <addons/TokenHelper.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

#define DHTPIN D3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#define WIFI_SSID "Holla_tab"
#define WIFI_PASSWORD "PraiseTheSun2723"

/* 2. Define the API Key */
#define API_KEY "AIzaSyAEcJjMeh4_hTFzWwdyNkY4uAdTvC4EeeQ"

/* 3. Define the RTDB URL */
#define DATABASE_URL "environment-monitoring-2efd6-default-rtdb.firebaseio.com"         //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "pratyush252003@gmail.com"
#define USER_PASSWORD "pratyush#64"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

MQ135 gasSensor = MQ135 (A0);
String quality = "";
float g = (gasSensor.getPPM());

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_BMP280  bmp;

void setup()
{

  Serial.begin(9600);
  dht.begin();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h


  Firebase.begin(&config, &auth);

  //Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();  
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  String q = quality;
  float g = (gasSensor.getPPM()/250);
    if(g < 50){
      quality = "Fresh Air";
      
    }
    else if (g >50 && g <100){
      quality = "OpenWindow";
  
    }
     else{
      quality = "ESCAPE!";
     
    }
   
 
 delay(100);
  if (isnan(h) || isnan(t)) {       // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    String fireHumid = String(h) + String(" %");       //convert integer to string

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
    String fireTemp = String(t) + String(" *C");      //convert integer to string

    Serial.print("Air Quality: ");
    Serial.print(g);
    Serial.println(" PPM");
    String fireGasLevel = String(g) + String(" PPM") ;    //convert integer to string

    
    Serial.println(quality);
    Serial.println();
    String fireComment = String(quality);

    float Pres = (bmp.readPressure()/100); 
    String firePres = String(Pres) + String(" hpa") ;  
    Serial.print("Pressure : ");
    Serial.print(firePres);

   display.clearDisplay();  
   display.setTextSize(1);  
   display.setTextColor(SSD1306_WHITE);  
   
   display.setCursor(0, 0);  
   display.print(" TEMP : "); 
   display.setCursor(75, 0); 
   display.print(fireTemp); 
   
   display.setCursor(0, 12);  
   display.print(" HUMIDITY : ");  
   display.setCursor(80, 12); 
   display.print(fireHumid); 

   display.setCursor(0, 24);  
   display.print(" AQI : ");  
   display.setCursor(50, 24);  
   display.print(fireGasLevel); 

   display.setCursor(0, 36);  
   display.print(" Pres : ");  
   display.setCursor(50, 36);  
   display.print(firePres); 

   display.setCursor(5, 50); 
   display.print(fireComment); 
   display.display();  
   
    
   Firebase.setString(fbdo, "Humid", fireHumid);
   Firebase.setString(fbdo, "Temp",fireTemp);
   Firebase.setString(fbdo, "AQI", fireGasLevel);
   Firebase.setString(fbdo, "Comment",fireComment); 
   Firebase.setString(fbdo, "Pres",firePres); 
   delay(1000);

}
