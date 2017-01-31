#include <Arduino.h>
#include <avr/wdt.h>
#include <math.h>

char deviceEvent[30]="";
const int TEMPPIN = 5;
const int LEDPIN = 13;
const int MOSPIN = 0;
int B=3975; //B value of the thermistor

void setup() {
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int value = Serial.parseInt();
    if(value == 101) {
      blinkLED();
    } else if(value == 105) {
      blink5LED();
    } else if(value == 110) {
      blink10LED();
    } else if(value == 115) {
      reboot();
    } else {
      blinkLED();
    }
 } 
  
  strcpy(deviceEvent, "");
  char val[10];
  strcat(deviceEvent,"status temp:");
  dtostrf(getTemp(),1,2, val);
  strcat(deviceEvent,val);
  strcat(deviceEvent,",mois:");
  int sensorValue = analogRead(MOSPIN);
  itoa(sensorValue/10, val, 10);
  strcat(deviceEvent,val);
  
  Serial.println(deviceEvent);
  delay(1000);
}

double getTemp(void) {
  double temperature;
  int a = analogRead(TEMPPIN);
  float resistance=(float)(1023-a)*10000/a; //get the resistance of the sensor;
  temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;//convert to temperature via datasheet&nbsp;;
  return temperature;
}

void blinkLED(void){
  digitalWrite(LEDPIN, HIGH);
  delay(1000);              
  digitalWrite(LEDPIN, LOW);
  delay(1000); 
}

void blink5LED(void){
  for(int i=0;i<5;i++){
    digitalWrite(LEDPIN, HIGH);
    delay(1000);              
    digitalWrite(LEDPIN, LOW);
    delay(1000);
  } 
}

void blink10LED(void){
  for(int i=0;i<10;i++){
    digitalWrite(LEDPIN, HIGH);
    delay(1000);              
    digitalWrite(LEDPIN, LOW);
    delay(1000);
  } 
}

void reboot(void) {
  wdt_enable(WDTO_15MS); // turn on the WatchDog and wait.
  for(;;) { 
    // do nothing and wait for the eventual...
  } 
}
