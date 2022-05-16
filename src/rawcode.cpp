
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


// // //Libraries
// // #include <Arduino.h>
// // #include <SPI.h>
// // #include <Wire.h>
// // #include <MFRC522.h>
// // #include<Firebase_ESP_Client.h>
// // //Declaration

// // // for RFID
// // #define SS_PIN  25  // ESP32 pin GIOP25 
// // #define RST_PIN 27 // ESP32 pin GIOP27 
// // MFRC522 mfrc522(SS_PIN, RST_PIN);
// // MFRC522::MIFARE_Key key;

// //  // set the LCD address to 0x27 for a 16 chars and 2 line display




// // /* Set the block to which we want to write data */
// // /* Be aware of Sector Trailer Blocks */
// // int blockNumForDob = 1;  
// // int blockNumForName = 2;  
// // int blockNumForDesignation = 4;  
// // /* Create an array of 16 Bytes and fill it with data */
// // /* This is the actual data which is going to be written into the card */
// // byte blockDataName [16] = {"Ibrahim"};
// // byte blockDataDob [16] = {"8 Feb 2003"};
// // byte blockDataDesignation [16] = {"Worker"};


// // /* Create another array to read data from Block */
// // /* Legthn of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
// // byte bufferLen = 18;
// // byte readBlockData_Name[18];
// // byte readBlockData_Dob[18];
// // byte readBlockData_Designation[18];

// // MFRC522::StatusCode status;


// // void WriteDataToBlock(int blockNumForName, byte blockDataName[]) 
// // {
// //   /* Authenticating the desired data block for write access using Key A */
// //   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumForName, &key, &(mfrc522.uid));
// //   if (status != MFRC522::STATUS_OK)
// //   {
// //     Serial.print("Authentication failed for Write: ");

// //     return;
// //   }
// //   else
// //   {
// //     Serial.println("Authentication success");
// //   }


// //   /* Write data to the block */
// //   status = mfrc522.MIFARE_Write(blockNumForName, blockDataName, 16);
// //   if (status != MFRC522::STATUS_OK)
// //   {
// //     Serial.print("Writing to Block failed: ");

// //     return;
// //   }
// //   else
// //   {
// //     Serial.println("Data was written into Block successfully");
// //   }

// // }

// // void ReadDataFromBlock(int blockNumForName, byte readBlockData_Name[]) 
// // {
// //   /* Authenticating the desired data block for Read access using Key A */
// //   byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumForName, &key, &(mfrc522.uid));

// //   if (status != MFRC522::STATUS_OK)
// //   {
// //      Serial.print("Authentication failed for Read: ");

// //      return;
// //   }
// //   else
// //   {
// //     Serial.println("Authentication success");
// //   }

// //   /* Reading data from the Block */
// //   status = mfrc522.MIFARE_Read(blockNumForName, readBlockData_Name, &bufferLen);
// //   if (status != MFRC522::STATUS_OK)
// //   {
// //     Serial.print("Reading failed: ");

// //     return;
// //   }
// //   else
// //   {
// //     Serial.println("Block was read successfully");  
// //   }

// // }

// // void setup() {
// //   Serial.begin(921600);




// //   //RFID INITIALIZATION
// //   SPI.begin();
// //   mfrc522.PCD_Init();
// //   delay(50);

// //     Serial.println("**Card Searching**");

// // }



// // void loop()
// // {
// //   /* Prepare the ksy for authentication */
// //   /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
// //   for (byte i = 0; i < 6; i++)
// //   {
// //     key.keyByte[i] = 0xFF;
// //   }
// //   /* Look for new cards */
// //   /* Reset the loop if no new card is present on RC522 Reader */
// //   if ( ! mfrc522.PICC_IsNewCardPresent())
// //   {
// //     return;
// //   }

// //   /* Select one of the cards */
// //   if ( ! mfrc522.PICC_ReadCardSerial()) 
// //   {
// //     return;
// //   }
// //   Serial.print("\n");
// //   Serial.println("**Card Detected**");
// //   /* Print UID of the Card */
// //   Serial.print(F("Card UID:"));
// //   for (byte i = 0; i < mfrc522.uid.size; i++)
// //   {
// //     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
// //     Serial.print(mfrc522.uid.uidByte[i], HEX);
// //   }
// //   Serial.print("\n");
// //   /* Print type of card (for example, MIFARE 1K) */
// //   Serial.print(F("PICC type: "));
// //   MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
// //   Serial.println(mfrc522.PICC_GetTypeName(piccType));

// //   //  /* Call 'WriteDataToBlock' function, which will write data to the block */
// //   //  Serial.print("\n");
// //   //  Serial.println("Writing to Data Block...");
// //   //  WriteDataToBlock(blockNumForName, blockDataName);
// //   //  WriteDataToBlock(blockNumForDob, blockDataDob);
// //   //  WriteDataToBlock(blockNumForDesignation, blockDataDesignation);

// //    /* Read data from the same block */
// //    Serial.print("\n");
// //    Serial.println("Reading from Data Block...");
// //    ReadDataFromBlock(blockNumForName, readBlockData_Name);
// //    ReadDataFromBlock(blockNumForDob, readBlockData_Dob);
// //    ReadDataFromBlock(blockNumForDesignation, readBlockData_Designation);
// //    /* If you want to print the full memory dump, uncomment the next line */
// //    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

// //    /* Print the data read from block */
// //    Serial.print("\n");
// //    Serial.print("Name:");
// //    Serial.print(blockNumForName);
// //    Serial.print(" --> ");
// //    for (int j=0 ; j<16 ; j++)
// //    {
// //      Serial.write(readBlockData_Name[j]);
// //    }
// //    Serial.print("\n");

// //    /* Print the data read from block */
// //    Serial.print("\n");
// //    Serial.print("DOB:");
// //    Serial.print(blockNumForDob);
// //    Serial.print(" --> ");
// //    for (int j=0 ; j<16 ; j++)
// //    {
// //      Serial.write(readBlockData_Dob[j]);
// //    }
// //    Serial.print("\n");

// //    /* Print the data read from block */
// //    Serial.print("\n");
// //    Serial.print("Designation:");
// //    Serial.print(blockNumForDesignation);
// //    Serial.print(" --> ");
// //    for (int j=0 ; j<16 ; j++)
// //    {
// //      Serial.write(readBlockData_Designation[j]);
// //    }
// //    Serial.print("\n");
// // }

