#include <SPI.h> //引入SPI函式庫
#include <MFRC522.h> //引入函式庫
 
#define SS_PIN 10 //設定NSS腳位
#define RST_PIN 9 //設定RST腳位
MFRC522 rfid(SS_PIN, RST_PIN);
 
void setup() {
Serial.begin(9600);//設定鮑率為9600
SPI.begin(); //初始化SPI
rfid.PCD_Init(); // 初始化MFRC522模組
}
 
void loop() {
 
if ( ! rfid.PICC_IsNewCardPresent())//檢查是否有新的卡片
return;
 
if ( ! rfid.PICC_ReadCardSerial())//檢查是否有讀取到卡片的UID
return;
Serial.print(F("PICC type: "));
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);//讀取卡片的類型
Serial.println(rfid.PICC_GetTypeName(piccType));
 
Serial.println(F("A new card has been detected."));
Serial.println(F("The NUID tag is:"));
Serial.print(F("In hex: "));
printHex(rfid.uid.uidByte, rfid.uid.size);//呼叫副程式 並將UID和UID長度傳送至printHex()將UID值用十六進制顯示
Serial.println();
Serial.print(F("In dec: "));
printDec(rfid.uid.uidByte, rfid.uid.size);//呼叫副程式 並將UID和UID長度傳送至printDec()將UID值用十進制顯示
Serial.println();
 
// Halt PICC
rfid.PICC_HaltA();
 
// Stop encryption on PCD
rfid.PCD_StopCrypto1();
}
 
void printHex(byte *buffer, byte bufferSize) {//將UID值以十六近制顯示在序列阜監控視窗
for (byte i = 0; i < bufferSize; i++) {
Serial.print(buffer[i] < 0x10 ? " 0" : " ");
Serial.print(buffer[i], HEX);
}
}
 
void printDec(byte *buffer, byte bufferSize) {  //將UID值以十近制顯示在序列阜監控視窗
for (byte i = 0; i < bufferSize; i++) {
Serial.print(buffer[i] < 0x10 ? " 0" : " ");
Serial.print(buffer[i], DEC);
}
}
