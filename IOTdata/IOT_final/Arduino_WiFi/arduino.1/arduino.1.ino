void setup() {
    Serial.begin(115200);               //initial the Serial
}

void loop()
{
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  
  a = analogRead(A0);
  b = analogRead(A1);
  c = analogRead(A2);
  d = analogRead(A3);
  e = analogRead(A4);
  f = analogRead(A5);
  
  float pa = (((10000000/a)-9745.9)/445.03);
  float pb = (((10000000/b)-9745.9)/445.03);
  float pc = (((10000000/c)-9745.9)/445.03);
  float pd = (((10000000/d)-9745.9)/445.03);
  float pe = (((10000000/e)-9745.9)/445.03);
  float pf = (((10000000/f)-9745.9)/445.03);

  Serial.print(pa);
  Serial.print(",");
  Serial.print(pb);
  Serial.print(",");
  Serial.print(pc);
  Serial.print(",");
  Serial.print(pd);
  Serial.print(",");
  Serial.print(pe);
  Serial.print(",");
  Serial.print(pf);
 // Serial.print("~");
 // Serial.println();
  
        delay(5000);
    
   
}
