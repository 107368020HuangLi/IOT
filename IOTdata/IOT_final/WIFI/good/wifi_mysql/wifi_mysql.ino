#include <SoftwareSerial.h>

// connect 2 to TX of Serial USB
// connect 3 to RX of serial USB
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup() {                
  // initialize the digital pin as an output. 
    
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
 
  // reset ESP8266
  ser.println("AT+RST");
}


// the loop 
void loop() {
  
  //voltage();
  esp_8266();
}

void esp_8266()
{
  
  int r1=random(90,200);
  int r2=random(90,200);
 // convert to string
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
  String getStr = "GET /IOT/IOT_insert.php?";                           //////////
//  getStr +="id=";
//  getStr += String(r1);
  getStr +="first=";
  getStr += String(r1);
  getStr +="&second=";
  getStr += String(r2);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
    Serial.println(getStr);
  }
  else{
   //  ser.println("AT+CIPCLOSE");
    // alert user
   Serial.println("AT+CIPCLOSE");
  }
    
  // thingspeak needs 15 sec delay between updates
  delay(1000);  
}
