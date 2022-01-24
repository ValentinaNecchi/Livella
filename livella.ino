#include "pitches.h"
#include "SR04.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
 
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
int i,x;
int j,y;

//suoni del buzzer passivo:
int note[] = {NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int note2[] = {NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5};
int note3[] = {NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_C6};
//ho tenuto tre array con le note per poterle eventualmente modificare
int durata1 = 200;
int durata2 = 200;


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
    tone(A0, note[4],durata1);
  } else {
    
    if (cm1>cm2){
      i=cm1-cm2;
    } else if (cm2>cm1){
      i=cm2-cm1;
    }
    
    if (cm1>cm3){
      j=cm1-cm3;
    } else if (cm3>cm1){
      j=cm3-cm1;
    }
    
  }

    for (x=0;x<i;x++){
      tone(A0, note2[x],durata2);
      delay(500);
    }


    for (y=0;y<j;y++){
      tone(A0, note3[y],durata2);
      delay(500);
    }
  /*if (diff1<diff2){           //vecchie prove di funzionamento
    if 
    //tone(A0, note[0],pausa);
    tone(A0, note[4],pausa2);
    //tone(A0, note[7],pausa);
  }

  if (diff1>diff2){
    //tone(A0, note[0],pausa);
    //tone(A0, note[3],pausa);
    tone(A0, note[7],pausa3);
  } */

  delay(4000);
  lcd.clear();
}
