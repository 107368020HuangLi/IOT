#include <SoftwareSerial.h>

// LED 
int ledPin = 13;
int sensor_pin=A0;  // variable for sensor
float sample=0;
float bat_volt =0;     // for temperature

// replace with your channel's thingspeak API key
String apiKey = "RN742J8HOPJLODER";

// connect 2 to TX of Serial USB
// connect 3 to RX of serial USB
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);    

  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
  // reset ESP8266
  ser.println("AT+RST");
}


// the loop 
void loop() {
  
  // blink LED on board
  digitalWrite(ledPin, HIGH);   
  delay(200);               
  digitalWrite(ledPin, LOW);

  //voltage();
  esp_8266();
}

void esp_8266()
{
  int r=random(90,200);
 // convert to string
  char buf[32];
  //String strVolt = dtostrf( bat_volt, 4, 1, buf);
  Serial.print(r);
  Serial.println(" V");
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
   
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(r);
  getStr +="&field2=";
  getStr += String(r);
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
    
  // thingspeak needs 15 sec delay between updates
  delay(16000);  
}
