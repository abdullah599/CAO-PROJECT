
// #include <SPI.h>
// #include <Wire.h>
// #include <MFRC522.h>
// #include <Firebase_ESP_Client.h>


// #define SS_PIN 25     
// #define RST_PIN 27
  
 
// MFRC522 mfrc522(SS_PIN, RST_PIN);


// void setup(){
  

//   Serial.begin(916200);
//   SPI.begin();
//   mfrc522.PCD_Init();
//   delay(50);
//   mfrc522.PCD_DumpVersionToSerial();

// }

// void loop()
// {
   

   
//   // New cards scan
//   if ( ! mfrc522.PICC_IsNewCardPresent())
//   {
//     return;
//   }
//   // if the card was read
//   if ( ! mfrc522.PICC_ReadCardSerial())
//   {
//     return;
//   }
//   //Read the UID of the card and write to the serial port
//   Serial.println();
//   Serial.print("UID Tag :");
//   String content = "";
//   byte letter;
//   for (byte i = 0; i < mfrc522.uid.size; i++)
//   {
//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     content.concat(String(mfrc522.uid.uidByte[i], HEX));
//   }
//   content.toUpperCase();
//   Serial.println();
//     mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
//     if (content.substring(1) == "30 31 B8 35") 
//         {
//           Serial.println("Access Granted");
//         }
//         else   
//         {
//           Serial.println("Access Denied");;
//         }
//    //  else if (content.substring(1) == "7C 00 F7 21")
//    //      {
//    //        access_granted();
//    //      }
//    //  else   
//    //      {
//    //        access_denied();
//    //      }
// }

// void access_granted(){
//    Serial.println("Access Granted! ");
  
//    Serial.println("Welcome To Home");

//    for (int i=0; i<=0; i++)
//    {
//     digitalWrite(audioBuzzer, HIGH);
//     delay(200); 
//     digitalWrite(audioBuzzer, LOW);
//     delay(200); 
//    }
//    digitalWrite(lock, HIGH);
//    digitalWrite(ledRed, LOW);
//    digitalWrite(ledGreen, HIGH);
//    digitalWrite(ledBlue, LOW);
//    delay(5000); 

// }

// void access_denied(){
//    Serial.println("Access Denied! ");
   
//    Serial.println("Not Valid Card");
//    digitalWrite(lock, LOW);
//    digitalWrite(ledGreen, LOW);
//    digitalWrite(ledBlue, LOW);

//    for (int i=0; i<=1; i++)
//    {
//     digitalWrite(audioBuzzer, HIGH);
//     digitalWrite(ledRed, HIGH);
//     delay(200); 
//     digitalWrite(audioBuzzer, LOW);
//     digitalWrite(ledRed, LOW);
//     delay(200); 
//    }
//    digitalWrite(ledBlue, HIGH);
//    delay(500);
   
//  }