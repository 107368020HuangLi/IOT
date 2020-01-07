#include <SoftwareSerial.h>
SoftwareSerial esp8266(2, 3);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
Serial.println("Ar OK");
esp8266.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(esp8266.available()){
    Serial.write(esp8266.read());
  }

   if(Serial.available()){
    esp8266.write(Serial.read());
  }
  
}
