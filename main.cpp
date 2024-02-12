#include<Arduino.h>
#define LED 18
#define BUTTON 0

hw_timer_t *My_timer = NULL;
hw_timer_t *Onpause = NULL;

double noteArr[] = {659.25, 587.33, 369.99, 415.30, 554.37, 493.88, 293.66, 329.63, 493.88, 440.00, 277.18, 329.63, 440.00};
double durationArr[] = {166, 166, 333, 333, 166, 166, 333, 333, 166, 166, 333, 333, 666};
double speedArr[] = {1.5, 1.25, 1, 0.75, 0.5};
int j = 0;

void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}

void IRAM_ATTR onSpeed(){
  j++;
}

double Freq2T(double T){
  return  1000000/(T*2);
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  // timerAlarmWrite(My_timer, Freq2T(659.25), true);  // set alarm every 1 sec
  // timerAlarmEnable(My_timer);  // enable the alarm

  attachInterrupt(BUTTON, &onSpeed, RISING);

  Serial0.begin(9600);
}

void loop() {
  for(int i = 0; i< (sizeof(noteArr)/sizeof(double)); i++){
    timerAlarmWrite(My_timer, Freq2T(noteArr[i]), true);
    Serial0.println(j);
    delay(durationArr[i]*speedArr[j%5]);
    timerAlarmEnable(My_timer);
  }
}

 
