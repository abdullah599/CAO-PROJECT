//Libraries
# include <Arduino.h>
#include<string.h>
# include<WiFi.h>
# include <SPI.h>
# include <Wire.h>
# include <MFRC522.h>
# include <LiquidCrystal_I2C.h>
# include <Firebase_ESP_Client.h>
#include <ESP32Time.h>
//Provide the token generation process info.
# include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
# include "addons/RTDBHelper.h"


//Declaration
int led = 2; // LED/LOCK
int buzzer = 4; //Buzzer

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


//for wifi
#define ssid  "Predator"
#define password "multan123"
unsigned long previousMillis = 0;
unsigned long interval = 30000;

// For firebase
#define API_KEY "AIzaSyAnyGxL0rdgdrYzq2zJCs2bBU5NFUIHLBo"
#define DATABASE_URL "https://cao-project-8bf71-default-rtdb.asia-southeast1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;


// for RFID
#define SS_PIN  25  // ESP32 pin GIOP25 
#define RST_PIN 27 // ESP32 pin GIOP27 
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
bool shouldCheck = false;
String content = "";


/* Set the block to which we want to read data from*/
/* Be aware of Sector Trailer Blocks */
int blockNumForDob = 1;
int blockNumForName = 2;
int blockNumForDesignation = 4;


/* Create another array to read data from Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
byte bufferLen = 18;
byte readBlockData_Name[18];
byte readBlockData_Dob[18];
byte readBlockData_Designation[18];

MFRC522::StatusCode status;

//for time
//ESP32Time rtc;
ESP32Time rtc(0);  // offset in seconds (i will set pakistan time so no need to define offset)



//Function declaration
void initWiFi();
void reconnectWIFI();
void initLCD();
void initFireBase();
void sendDataToFirebase(String path, String data);
void ReadDataFromBlock(int blockNumForName, byte readBlockData_Name[]);
void checkFunction(String content);
void LCD(String m1, String m2);
// Function that gets current epoch time
unsigned long getTime();

void setup()
{
    Serial.begin(916200);
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);
    

    rtc.setTime(30, 01, 22, 18, 5, 2022);  // 17th May 2022 15:24:30
    //initialization
    
    initLCD();
    LCD("Please wait", "Initializing");
    
    initWiFi();
    initFireBase();


    //RFID INITIALIZATION
    SPI.begin();
    mfrc522.PCD_Init();
    delay(50);
    mfrc522.PCD_DumpVersionToSerial();
   
    LCD("System Ready","Scan the card");

}

void loop()
{

    reconnectWIFI(); //if required

     //   /* Prepare the ksy for authentication */
    /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }
    /* Look for new cards */
    /* Reset the loop if no new card is present on RC522 Reader */
    if (!mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    /* Select one of the cards */
    if (!mfrc522.PICC_ReadCardSerial())
    {
        return;
    }
    Serial.print("\n");
    Serial.println("**Card Detected**");
    LCD("Card Detected", "");

    /* Print UID of the Card */
    Serial.print(F("Card UID:"));
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.print("\n");
    /* Print type of card (for example, MIFARE 1K) */
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));




    /* Read data from the same block */
    Serial.print("\n");
    Serial.println("Reading from Data Block...");
    ReadDataFromBlock(blockNumForName, readBlockData_Name);
    ReadDataFromBlock(blockNumForDob, readBlockData_Dob);
    ReadDataFromBlock(blockNumForDesignation, readBlockData_Designation);
      delay(100);
      // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  delay(250);  
    /* If you want to print the full memory dump, uncomment the next line */
    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));


    if (shouldCheck)
    {
        checkFunction(content);
    }
        LCD("System Ready","Scan the card");


}


//For initializing wifi connection
void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
}
void reconnectWIFI()
{
    unsigned long currentMillis = millis();
    // if WiFi is down, try reconnecting
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= interval))
    {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        
        WiFi.disconnect();
        WiFi.reconnect();
        previousMillis = currentMillis;
    }
}

//For initializing LCD
void initLCD()
{
    //LCD initialization
    lcd.init();
    lcd.clear();
    lcd.backlight();// Make sure backlight is on

    // lcd.setCursor(0,0);   //Set cursor to character 0 on line 0
     // lcd.print("Connected with:");

   
}


//For initializing Firebase
void initFireBase()
{
    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Connected to fb");
        signupOK = true;
    }
    else
    {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void sendDataToFirebase(String path, String Uid, String Name, String Dob, String Designation,String Time,String status)
{
    if (Firebase.ready() && signupOK )
    {
      
      
      if (Firebase.RTDB.setString(&fbdo, path+"/Uid", Uid)&&Firebase.RTDB.setString(&fbdo, path+"/Time", Time) && Firebase.RTDB.setString(&fbdo, path+"/Name", Name)&&Firebase.RTDB.setString(&fbdo, path+"/Date of Birth", Dob)&&Firebase.RTDB.setString(&fbdo, path+"/Designation", Designation)&&Firebase.RTDB.setString(&fbdo, path+"/Status", status))
        {
            Serial.println("PASSED");
        }
        else
        {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
        }
    }
}

void ReadDataFromBlock(int blockNumForName, byte readBlockData_Name[])
{
    /* Authenticating the desired data block for Read access using Key A */
    byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumForName, &key, &(mfrc522.uid));

    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Read: ");

        return;
    }
    else
    {
        Serial.println("Authentication success");
    }
    //Read the UID of the card and write to the serial port
    Serial.println();
   
    content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {

        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    content.toUpperCase();
    Serial.println();
    /* Reading data from the Block */
    status = mfrc522.MIFARE_Read(blockNumForName, readBlockData_Name, &bufferLen);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Reading failed: ");
        shouldCheck = true;
        return;
    }
    else
    {
        Serial.println("Block was read successfully");
        shouldCheck = true;
    }
}

void checkFunction(String content)
{
    /* Print the data read from block */
    String name = "";
    String dob = "";
    String desgnation = "";
    for (int j = 0; j < 16; j++)
    {
        name.concat(static_cast<char>(readBlockData_Name[j]));
    }
    for (int j = 0; j < 16; j++)
    {
        dob.concat(static_cast<char>(readBlockData_Dob[j]));
    }
    for (int j = 0; j < 16; j++)
    {
        desgnation.concat(static_cast<char>(readBlockData_Designation[j]));
    }
    
    // char milis[20];
    String milis;
    milis = -rtc.getEpoch();
  
    if (content.substring(1) == "30 31 B8 35"||content.substring(1)=="30 9D 6F 35"||content.substring(1)=="CC CC 06 49")
    {

        Serial.println("Access Granted");
        LCD("Access Granted", " ");
        delay(1000);
        if (name != "") {
              LCD("Welcome", name);
        }
        else {
             LCD("Access Granted", " ");
        }
        digitalWrite(led, HIGH);
        String path = "data/";
        path.concat(milis);
        delay(3000);
        digitalWrite(led, LOW);
        LCD(" ", "Please wait...");
        sendDataToFirebase(path, content.substring(1), name, dob, desgnation, rtc.getDateTime(),"Access Granted");
        
    }
    else
    {

        Serial.println("Access Denied");
        String path = "data/";
        LCD("Access Denied", " ");
        delay(1000);
        if (name != "") {
              LCD(name,"not allowed");
        }
        else {
             LCD("Access Denied", " ");
        }
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(500);
         digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(500); digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(500);

        path.concat(milis);
        LCD(" ", "Please wait...");
        sendDataToFirebase(path, content.substring(1), name, dob, desgnation, rtc.getDateTime(),"Access Denied");
    }
  
    shouldCheck = false;
        LCD("System Ready","Scan the card");
}
void LCD(String m1 , String m2 ) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(m1);
    lcd.setCursor(0, 1);
    lcd.print(m2);

}
unsigned long getTime(){
    
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}
