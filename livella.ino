#include "pitches.h"
#include "SR04.h"
#include <LiquidCrystal.h>

#define RS A5
#define EN A4
#define D4 A3
#define D5 A2
#define D6 A1
#define D7 A0
 
#define TRIG_PIN1 13
#define ECHO_PIN1 12
#define TRIG_PIN2 11
#define ECHO_PIN2 10
#define TRIG_PIN3 9
#define ECHO_PIN3 8
SR04 sr04a = SR04(ECHO_PIN1,TRIG_PIN1);   //primo sensore
SR04 sr04b = SR04(ECHO_PIN2,TRIG_PIN2);   //seconddo sensore
SR04 sr04c = SR04(ECHO_PIN3,TRIG_PIN3);   //terzo sensore
int cm1;     //distanza rilevata dal primo sensore
int cm2;     //distanza rilevata dal secondo sensore
int cm3;     //distanza rilevata dal terzo sensore
int diff1;    //differenza tra misurazione sensore 1 e 2
int diff2;    //differenza tra misurazione sensore 1 e 3
int x;

int note[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int durata;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void Misura(){
  if (cm1>cm3){
    x=cm1-cm3;
  } else if (cm3>cm1){
    x=cm3-cm1;
  }
  //x deve essere compreso tra 0 e 7

  if (cm2>cm3){
    durata=10*(cm2-cm3);
  } else if (cm3>cm2){
    durata=200*(cm3-cm2);
  }
  //durata deve quindi andare da 700 a 10
}


void setup() {
  lcd.begin(16,2); 
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  cm1=sr04a.Distance();
  cm2=sr04b.Distance();
  cm3=sr04c.Distance();

  diff1=cm1-cm2;
  diff2=cm1-cm3;
  
  lcd.setCursor(0,0);
  lcd.print("Dist 1-2: "); 
  lcd.print(diff1);
  delay(10);
  lcd.setCursor(0,1);
  lcd.print("Dist 1-3: ");
  lcd.print(diff2);

  if (cm1==cm2 && cm1==cm3){
    tone(5, note[7]);
  } else {
    Misura();
    tone(5, note[x],durata);
  }
  
  delay(1000);
  lcd.clear();
}
