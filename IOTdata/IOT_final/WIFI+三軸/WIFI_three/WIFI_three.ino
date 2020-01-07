#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

Servo myservo; // 建立Servo物件，控制伺服馬達


// connect 2 to TX of Serial USB
// connect 3 to RX of serial USB
SoftwareSerial ser(2,3); // RX, TX

#include <Wire.h> //I2C Arduino Library
#define addr 0x1E //I2C Address for The HMC5883

// this runs once

#define RST_PIN    9   // Reset腳
#define SS_PIN     10     // 晶片選擇腳 (SDA)
MFRC522 mfrc522(SS_PIN, RST_PIN);    // 建立MFRC522物件
MFRC522::MIFARE_Key key;  // 儲存金鑰

byte sector = 15;   // 指定讀寫的「區段」，可能值:0~15
byte block = 1;     // 指定讀寫的「區塊」，可能值:0~3
byte blockData[16] = "bb";   // 最多可存入16個字元


// 若要清除區塊內容，請寫入16個 0
//byte blockData[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// 暫存讀取區塊內容的陣列，MIFARE_Read()方法要求至少要18位元組空間，來存放16位元組。
byte buffer[18];

MFRC522::StatusCode status;

void readBlock(byte _sector, byte _block, byte _blockData[])  {
  if (_sector < 0 || _sector > 15 || _block < 0 || _block > 3) {
    // 顯示「區段或區塊碼錯誤」，然後結束函式。
    Serial.println(F("Wrong sector or block number."));
    return;
  }

  byte blockNum = _sector * 4 + _block;  // 計算區塊的實際編號（0~63）
  byte trailerBlock = _sector * 4 + 3;   // 控制區塊編號

  // 驗證金鑰
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  // 若未通過驗證…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  byte buffersize = 18;
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockNum, _blockData, &buffersize);

  // 若讀取不成功…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("MIFARE_read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  // 顯示「讀取成功！」 Serial.println(F("Data was read."));
}


void setup() {                

  Serial.begin(9600); 
  ser.begin(115200);

  SPI.begin();               // 初始化SPI介面
  mfrc522.PCD_Init();        // 初始化MFRC522卡片
  myservo.attach(5); // 連接數位腳位9，伺服馬達的訊號線

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
  Wire.begin();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
}


// the loop 
  void loop() {
    esp_8266();
  }

    void esp_8266()
      {
        int x,y,z; 

         if ( ! mfrc522.PICC_IsNewCardPresent()) {
              return;  // 退回loop迴圈的開頭
          }

  // 選取一張卡片
         if ( ! mfrc522.PICC_ReadCardSerial()) {  // 若傳回1，代表已讀取到卡片的ID
              return;
          }

      readBlock(sector, block, buffer);      // 區段編號、區塊編號、存放讀取資料的陣列
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1(); 

        for (byte i = 0 ; i < 16 ; i++) {
             Serial.write (buffer[i]);
        }
  
         Wire.beginTransmission(addr);
         Wire.write(0x03); //start with register 3.
         Wire.endTransmission();
         Wire.requestFrom(addr, 6);
        
        if(6<=Wire.available()){
          //  x = Wire.read()<<8; //MSB  x 
          //  x |= Wire.read(); //LSB  x
          //  z = Wire.read()<<8; //MSB  z
          //  z |= Wire.read(); //LSB z
          
              y = Wire.read()<<8; //MSB y
              y |= Wire.read(); //LSB y
              y=  ( y + 300 ) / 6.3 ;
          }
  
        char buf[32];
  // TCP connection
        String cmd = "AT+CIPSTART=\"TCP\",\"";
               cmd += "140.124.72.10"; // api.thingspeak.com                ///////////
               cmd += "\",80";
               ser.println(cmd);
   
        if(ser.find("Error")){
            Serial.println("AT+CIPSTART error");
            return;
          }
  
  // prepare GET string
        
        if((byte)buffer[0]=='a' && (byte)buffer[1]=='a'){                              
                
                myservo.write(180); // 使用write，傳入角度，從0度轉到180度
                delay(333);
                
                myservo.write(0); // 使用write，傳入角度，從0度轉到180度
                delay(500);
                    
                myservo.write(90); 
                delay(100);    
         
           String getStr = "GET /IOT/IOT_insert.php?";                           //////////
            //  getStr +="id=";
            //  getStr += String(r1);
           getStr +="first=";
           getStr += String((char)((byte)buffer[0]));
           getStr +="&second=";
           getStr += String(y);
           getStr += "\r\n\r\n";

           // send data length
           cmd = "AT+CIPSEND=";
           cmd += String(getStr.length());
           ser.println(cmd); 
           
           if(ser.find(">")){
              ser.print(getStr);     //   Serial.println(getStr);  
           } 
           else{
              ser.println("AT+CIPCLOSE");    //   Serial.println("AT+CIPCLOSE");
           }    
           delay(3000);  
        }  

           
             
          
          
         if((byte)buffer[0]=='b' && (byte)buffer[1]=='b'){ 
                
                myservo.write(180); // 使用write，傳入角度，從0度轉到180度
                delay(333);
                
                myservo.write(0); // 使用write，傳入角度，從0度轉到180度
                delay(500);
                    
                myservo.write(90); 
                delay(100);  
          
           String getStr = "GET /IOT/IOT_insert.php?";                           //////////
            //  getStr +="id=";
            //  getStr += String(r1);
           getStr +="first=";
           getStr += String((char)((byte)buffer[0]));
           getStr +="&second=";
           getStr += String(y);
           getStr += "\r\n\r\n";

           // send data length
           cmd = "AT+CIPSEND=";
           cmd += String(getStr.length());
           ser.println(cmd);

           if(ser.find(">")){
                ser.print(getStr);     //Serial.println(getStr);
            } 
            else{
                ser.println("AT+CIPCLOSE");      //Serial.println("AT+CIPCLOSE");
            }  
            delay(3000);
         }
    }
