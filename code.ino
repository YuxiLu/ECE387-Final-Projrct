//  The circuit:
// * LCD RS pin to digital pin 19
// * LCD Enable pin to digital pin 18
// * LCD D4 pin to digital pin 17
// * LCD D5 pin to digital pin 16
// * LCD D6 pin to digital pin 15
// * LCD D7 pin to digital pin 14
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V

// include the library code:
#include <LiquidCrystal.h>

int ledPin[]={12,11,10,9,8};
int ButtonPin[]={7,6,5,4,3};
boolean ledState[]={0,0,0,0,0};

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 19, en = 18, d4 = 17, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int n[5]={};
unsigned long time_now;
int i,j;
int score=0;


void setup() {

// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  
  for(int i=0;i<5;i++){
    pinMode(ledPin[i], OUTPUT);
    pinMode(ButtonPin[i], INPUT_PULLUP);
  }
  
  for(int i=0;i<5;i++){
    digitalWrite(ledPin[i],LOW);
  }
  
  time_now=millis();
}


void loop() {
  // Execute every 1500ms
  if(millis()>=time_now+1500){
    
    // first turn off all LEDs
    for(i=0;i<5;i++){
      digitalWrite(ledPin[i],LOW);
    }
    
    time_now=millis();
    
    // Execute random number selection, 
    // and light the selected LED
    for(i=0; i<3; i++){
      do{
        n[i]=random(5);
        for(j=0; j<i; j++){
          if(n[i]==n[j]){
            break;
          }
        }      
      }while(j!=i);
      digitalWrite(ledPin[n[i]],HIGH);
      ledState[i]=HIGH;
    }
  }

  // Check whether the button corresponding to the selected LED is pressed, 
  // if it is pressed, add 1 to the score
  for(i=0;i<3;i++){
    if(digitalRead(ButtonPin[n[i]])==LOW && ledState[i]==HIGH){
      digitalWrite(ledPin[n[i]],LOW);
      ledState[i]=LOW;
      score++;
    }
  }

  // Display the score on the LCD
  Serial.println(score);
  // Display from the third position in the first row
  lcd.setCursor(2, 0); 
  lcd.print("Score:");
  lcd.print(score); 
}
