#include <DHT.h>


#include <SoftwareSerial.h>
SoftwareSerial UART(8, 9);
String apiKey = "RN742J8HOPJLODER";

#define DHTTYPE DHT22
#define DHTPIN A0
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  UART.begin(115200);
  dht.begin();
  delay(100);
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  UART.println(cmd);

  if (UART.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }
  else {
    Serial.println("AT+CIPSTART OK");
  }

  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += t;
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  UART.println(cmd);

  if (UART.find(">")) {
    UART.print(getStr);
    Serial.println(getStr);
  }
  else {
    UART.println("AT+CIPCLOSE");
    Serial.println("AT+CIPCLOSE");
  }

  delay(20000);
}
