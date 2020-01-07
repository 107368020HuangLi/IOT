#include <SPI.h>                                        //引用需要的函式庫
#include <Ethernet.h>
#include <EthernetUdp.h>                  

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };     //乙太網路模組晶片設定   
IPAddress ip(120, 101, 8, 131);                         //乙太網路IP

unsigned int localPort = 8888;                          //本地之監聽port
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];              //設定將傳來的封包
char  ReplyBuffer[] = "acknowledged";                   //字串之回傳
EthernetUDP Udp;                                        //乙太網路模組設定UDP
int fan = 5 ;                                           //風扇腳位設定
int led = 6 ;                                           //LED燈光腳位設定

void setup() {
Ethernet.begin(mac,ip);                                 //乙太網路模組設定開始
Udp.begin(localPort);                                   //設定UDP要監聽的port號
Serial.begin(9600);                                      //序列埠鮑率設定
   pinMode(fan, OUTPUT);                                //設定風扇初始狀態
   digitalWrite(fan, LOW); 
   pinMode(led, OUTPUT);                                //設定LED燈光初始狀態
   digitalWrite(led, LOW);  
}


void loop() {

    int packetSize = Udp.parsePacket();                      //設定UDP傳來之封包

      if(packetSize){                                        //判斷有無封包傳來之資料
          Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);     //讀出封包內容           
          if( String(packetBuffer) == "L" ){                 //根據傳送資料內容做出相對應之調整
               analogWrite(led,255);
               analogWrite(fan,255);              
          }
          else if( String(packetBuffer) == "K" ){
               analogWrite(led,128);
               analogWrite(fan,255);             
          }
          else if( String(packetBuffer) == "J" ){
               analogWrite(led,64);
               analogWrite(fan,255);           
          }         
          else if( String(packetBuffer) == "I" ){
               analogWrite(led,0);
               analogWrite(fan,255);
          }
          else if( String(packetBuffer) == "H" ){
               analogWrite(led,255);
               analogWrite(fan,150);  
          }
          else  if( String(packetBuffer) == "G" ){
               analogWrite(led,128);
               analogWrite(fan,150);
          }
          else if( String(packetBuffer) == "F" ){
               analogWrite(led,64);
               analogWrite(fan,150);  
          }
          else if( String(packetBuffer) == "E" ){
               analogWrite(led,0);
               analogWrite(fan,150);
          }
          else if( String(packetBuffer) == "D" ){
               analogWrite(led,255);
               analogWrite(fan,0);
          }
          else if( String(packetBuffer) == "C" ){
               analogWrite(led,128);
               analogWrite(fan,0);
          }
          else if( String(packetBuffer) == "B" ){
               analogWrite(led,64);
               analogWrite(fan,0);    
          } 
          else  if( String(packetBuffer) == "A" ){
               analogWrite(led,0);
               analogWrite(fan,0);
          }
          else {
            return;
          }      
          Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());     //UDP相關之設定
          Udp.write(ReplyBuffer);
          Udp.endPacket();
         }
            delay(10);
      }
