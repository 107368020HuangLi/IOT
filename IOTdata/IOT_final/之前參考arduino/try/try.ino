#include<SPI.h>                                                   //引入所需要的函式庫
#include "pitches.h"
#include<MFRC522.h>
#include <Ethernet.h> 
#include <dht.h>  
#define   dht_dpin 2                                        
#include<SoftwareSerial.h>                                        
dht DHT;                                                          
#define SS_PIN 7                                                  //RFID的腳位設定
#define RST_PIN 9                                                 //RFID的腳位設定
int  light_data=A0;                                               //光敏電阻的腳位設定
                                              
int duration = 50;                                                //蜂鳴器間隔時間設定

                  
byte server[] = { 120, 101, 8, 247 };                             //設定server端的IP
IPAddress ip(120,101,8,131);                                      //設定乙太網路端的IP
EthernetClient client;                                             //乙太網路端的內部設定
SoftwareSerial mySerial(8,9);   
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };              //RFID晶片內部設定
MFRC522 mfrc522(SS_PIN, RST_PIN);                                
MFRC522::MIFARE_Key key;                                    
byte sector = 15;                                                 
byte block = 1;                                                   
byte buffer[18];                                                  
MFRC522::StatusCode status;                                    

int tt_root=0;                                                    //判斷各成員是否在辦公室內
int tt_aa=0;
int tt_bbb=0;
int tt_cc=0;   


int root_at=1;                                                    //上傳個成員是否在辦公室內
int root_not_at=0;

int aa_at=1;
int aa_not_at=0;

int bbb_at=1;
int bbb_not_at=0;

int cc_at=1;
int cc_not_at=0;

void readBlock(byte _sector, byte _block, byte _blockData[])  {            //讀取RFID的設定
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
}


          void setup() {
               Serial.begin(9600);                                                   //序列埠鮑綠設定
               SPI.begin();                                                         //SPI通訊設定        
               mfrc522.PCD_Init();                                                  //RFID讀取設定
        
               for (byte i = 0; i < 6; i++) {
                    key.keyByte[i] = 0xFF;
                   }

               if (Ethernet.begin(mac) == 0) {                                      //判斷乙太網路是否有連                  
                   Ethernet.begin(mac, ip);
                    }
              delay(500);             
             }

      void loop() {        
             DHT.read11(dht_dpin);                                                  //讀取溫溼度感測器之值        
         
           if (client.connect(server, 80)) {                                        //判斷數據是否有成功上傳至server                
              if( tt_aa%2==0 && tt_bbb%2==0 && tt_cc%2==0 && tt_root%2==0 ){               //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_not_at);                                                                        
              }     
         
             if( tt_aa%2==0 && tt_bbb%2==0 && tt_cc%2==0 && tt_root%2==1 ){                //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_at);                
              }
              
              if( tt_aa%2==0 && tt_bbb%2==0 && tt_cc%2==1 && tt_root%2==0 ){               //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_not_at);               
               }

             if( tt_aa%2==0 && tt_bbb%2==0 && tt_cc%2==1 && tt_root%2==1 ){                //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_at);               
               }  

             if( tt_aa%2==0 && tt_bbb%2==1 && tt_cc%2==0 && tt_root%2==0 ){                //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_not_at);                
               } 

              if( tt_aa%2==0 && tt_bbb%2==1 && tt_cc%2==0 && tt_root%2==1 ){               //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_at);              
               }

               if( tt_aa%2==0 && tt_bbb%2==1 && tt_cc%2==1 && tt_root%2==0 ){              //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_not_at);               
               } 
               
              if( tt_aa%2==0 && tt_bbb%2==1 && tt_cc%2==1 && tt_root%2==1 ){               //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       ///上傳資料至MySQL資料庫
                client.print(aa_not_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_at);                
               }

               if( tt_aa%2==1 && tt_bbb%2==0 && tt_cc%2==0 && tt_root%2==0 ){              //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_not_at);                 
               }

               if( tt_aa%2==1 && tt_bbb%2==0 && tt_cc%2==0 && tt_root%2==1 ){              //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_at);                  
               }

               if( tt_aa%2==1 && tt_bbb%2==0 && tt_cc%2==1 && tt_root%2==0 ){              //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_not_at);                
               }

                if( tt_aa%2==1 && tt_bbb%2==0 && tt_cc%2==1 && tt_root%2==1 ){             //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_not_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_at);                
               }

                if( tt_aa%2==1 && tt_bbb%2==1 && tt_cc%2==0 && tt_root%2==0 ){             //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_not_at);               
               }

                if( tt_aa%2==1 && tt_bbb%2==1 && tt_cc%2==0 && tt_root%2==1 ){             //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_not_at);
                client.print("&root=");
                client.print(root_at);                
               }

                if( tt_aa%2==1 && tt_bbb%2==1 && tt_cc%2==1 && tt_root%2==0 ){             //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_not_at);               
               }
               
                if( tt_aa%2==1 && tt_bbb%2==1 && tt_cc%2==1 && tt_root%2==1 ){             //判斷各成員是否有在辦公室中
                client.print("GET /environment_data/InputData_environment_data.php?");     //YOUR URL
                client.print("aa=");                                                       //上傳資料至MySQL資料庫
                client.print(aa_at);         
                client.print("&bbb=");
                client.print(bbb_at);
                client.print("&cc=");
                client.print(cc_at);
                client.print("&root=");
                client.print(root_at);            
               }

                        
                client.print("&light_data=");                                              //上傳燈光至MySQL資料庫
                client.print(analogRead(A0));       
                client.print("&temperature=");                                             //上傳溫度至MySQL資料庫
                client.print(DHT.temperature); 
                client.print("&humidity=");                                                //上傳濕度至MySQL資料庫
                client.println(DHT.humidity);

                delay(1000);
                client.stop();                                                             //從端停止接收資料
         }

            else { 
                 client.stop();                                                            //從端停止接收資料
            }

            if(!mfrc522.PICC_IsNewCardPresent())                                           //讀取RFID資料
            {
              delay(1000);
              return;
            }
    
             if(!mfrc522.PICC_ReadCardSerial())
             {
              delay(1000);
              return;
            }
             
              readBlock(sector, block, buffer);                                        
              
              mfrc522.PICC_HaltA();
              mfrc522.PCD_StopCrypto1();    
            
            
           
            if((byte)buffer[0]=='a' && (byte)buffer[1]=='a')                               //判斷RFID卡身分
             {
              tt_aa=!tt_aa;                                                                //成員進出辦公室的判斷
              tone(3,  NOTE_C5, duration);                                                 //蜂鳴器設定
              delay(100);    
             }
            
            if((byte)buffer[0]=='r' && (byte)buffer[1]=='o'  && (byte)buffer[2]=='o' && (byte)buffer[3]=='t')       
             {
              tt_root=!tt_root;    
              tone(3,  NOTE_C5, duration);
              delay(100);   
             }

             if((byte)buffer[0]=='b' && (byte)buffer[1]=='b' && (byte)buffer[2]=='b'   )       
             {
              tt_bbb=!tt_bbb;     
              tone(3,  NOTE_C5, duration);
               delay(100);  
             }

             if((byte)buffer[0]=='c' && (byte)buffer[1]=='c'    )       
             {
              tt_cc=!tt_cc;      
              tone(3,  NOTE_C5, duration);
              delay(100); 
             }     
        }  
