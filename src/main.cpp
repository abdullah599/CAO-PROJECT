
//Libraries
#include <Arduino.h>
#include<WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Firebase_ESP_Client.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


//Declaration

//for wifi
#define ssid  "Abdullah"
#define password "multan123"

// For firebase
#define API_KEY "AIzaSyAnyGxL0rdgdrYzq2zJCs2bBU5NFUIHLBo"
#define DATABASE_URL "https://cao-project-8bf71-default-rtdb.asia-southeast1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


//Function declaration
void initWiFi();



LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(916200);
  //WiFi initialization
  initWiFi();
  //LCD initialization
  lcd.init();
  lcd.clear();         
  lcd.backlight();// Make sure backlight is on


  lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
  lcd.print("Connected with:");
  
  lcd.setCursor(0,1);   //Move cursor to character 0 on line 1
  lcd.print(WiFi.SSID());

  
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connected to fb");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setString(&fbdo, "testdata/SSID", WiFi.SSID())){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      lcd.setCursor(0, 1);
      lcd.print("Data sent to firebase");
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    count++;
    
    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "testdata/float", 0.01 + random(0,100))){
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}


//For initializing wifi connection
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }  
}
