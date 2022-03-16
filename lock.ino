#include <SoftwareSerial.h>

int pir = 5;
int pir_stat = 0;
//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  pinMode(pir, INPUT);
  pinMode(pir_stat, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  //Begin serial communication with Arduino and SIM800L
 
}

void loop()
{
  pir_stat = digitalRead(pir);
  if(pir_stat == HIGH){
     digitalWrite(LED_BUILTIN, HIGH);
     Serial.println("DETECTED");
      mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("ATD+ +919650691311;"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  delay(15000);
  mySerial.println("ATH");
     updateSerial();
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Undetected");
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
