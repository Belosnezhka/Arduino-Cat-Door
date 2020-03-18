int detectorPinInside = 8;
int detectorPinOutside = 5;
int dirpin1 =6;
int dirpin2 = 7;
int speedpin = 9;
int openswitch = 4;
int closeswitch = 3;
int motorpwr_close = 112;
int motorpwr_open = 130;
int motorpwr_end = 130;
int motorpwr_start = 95;
boolean window_state;
double time_out = 20000;
double start_time;
boolean failed_to_close = false;
int window_open_time = 15000;
/*
 * set 2 pins to digital input for the microswitches
 */

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(detectorPinInside, INPUT);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(dirpin1, OUTPUT);
pinMode(dirpin2, OUTPUT);
pinMode(speedpin, OUTPUT);
digitalWrite(dirpin1, LOW);
digitalWrite(dirpin2, LOW);
pinMode(openswitch, INPUT_PULLUP);
pinMode(closeswitch, INPUT_PULLUP);
}

void closewindow(){
    digitalWrite(dirpin1, HIGH);//medurs
    digitalWrite(dirpin2, LOW);
    analogWrite(speedpin, motorpwr_start);
    boolean b = true;
    while(b){
      delay(50);
         if(digitalRead(closeswitch) == HIGH){
          Serial.println("Closeswitch pressed");
        b=false;
        failed_to_close = false;
      }
      if(millis()-start_time > 10000){
        analogWrite(speedpin, motorpwr_close);
        Serial.println(digitalRead(detectorPinOutside));

      }
      if(millis()-start_time > 15000){
        analogWrite(speedpin, motorpwr_end);
        Serial.println(digitalRead(detectorPinOutside));

      }
      if(millis()-start_time > time_out){
        Serial.print("Timeout reached: ");
        Serial.println(millis()-start_time);
        b=false;
        failed_to_close = true;
      }
    }
    analogWrite(speedpin, 0);
    digitalWrite(dirpin1, LOW);
    digitalWrite(dirpin2, LOW);
}

void openwindow(){
    digitalWrite(dirpin1, LOW);
    digitalWrite(dirpin2, HIGH);
    analogWrite(speedpin, motorpwr_open);
    boolean b = true;
    while(b){
      delay(50);
      if(digitalRead(openswitch) == HIGH){
        Serial.println("Openswitch pressed");
        b=false;
      }
    }
    analogWrite(speedpin, 0);
    digitalWrite(dirpin1, LOW);
    digitalWrite(dirpin2, LOW);
}

void loop() {
  int outside = digitalRead(detectorPinOutside);
  int inside = digitalRead(detectorPinInside);
 Serial.print(outside);
 Serial.println(inside);

  //Serial.println(" " + String(millis()));
//add if failed_to_close
  if(inside==HIGH || outside==HIGH){
   /* if(failed_to_close){
      Serial.println("Closing failed, trying again");
      delay(2000);
    }else{
    Serial.println("Detected motion");
    }*/
    openwindow();
    delay(window_open_time);
    start_time = millis();
    closewindow();
    Serial.println(digitalRead(detectorPinOutside));
    delay(12000);
        Serial.println(digitalRead(detectorPinOutside));

//    if(digitalRead(openswitch)==LOW){
//      closewindow();
//      delay(2000);
//    }else{
//      openwindow();
//      delay(2000);
//      closewindow();
        
    }

    /**
     * OPEN set direction 
     * digitalWrite(dirpin1, LOW);
     * digitalWrite(dirpin2, HIGH);
     * int speed = 5;(0:255)
     * analogWrite(speedpin, 5);
     * boolean open = false;
     * while(!open){
     * if(digitalRead(microswitchOpen)==LOW(or high)){
     * open = true
     *  }
     * }
     * analogWrite(speedpin, 0);
     * delay(window open time)
     * SET DIRECTION AND CLOSE
     * digitalWrite(dirpin1, HIGH);
     * digitalWrite(dirpin2, LOW);
     * 
     * analogWrite(speedpin, 5);
     * boolean closed = false;
     * while(!closed){
     * if(digitalRead(microswitchClosed)==LOW(or high)){
     * closed = true
     *  }
     * }
     *
    for (int i = 50; i < 90; i++)
  {
    analogWrite(speedpin, i);
    delay(20);
  }
     for (int i = 90; i >= 0; --i)
  {
    analogWrite(speedpin, i);
    delay(20);
  }
    
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  // put your main code here, to run repeatedly:
*/
  }
