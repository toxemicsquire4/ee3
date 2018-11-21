#define blue 10 //PIN for lights
#define red 11
#define green 12

#define sensorr 0 //PIN for analog sensors
#define sensorl 1
#define sensorc 2

#define leftm 6  //MOTOR PWM pins
#define rightm 5

#define straight_speed 200 //speed values
#define turning_speed 110
#define slight_turning_speed 160
#define stop_speed 0
#define time 100

#define left_thresh 100 //thresh_hold values for sensors
#define center_thresh 100
#define right_thresh 100
int end_count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(blue, OUTPUT); //initialize 
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode(leftm, OUTPUT);
  pinMode(rightm, OUTPUT);
  Serial.begin (9600);
}

void leftMO(){ //deprecate
  analogWrite(leftm, 50);
  delay(time);
}
void rightMO(){ //deprecate
  analogWrite(rightm, 50);
  delay(time);
}


void middle_light(){ //green turns on for middle
     digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
}
void right_light(){ //red turns on for right turn
  digitalWrite(red, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
}

void left_light(){ //blue turns on for left turn
  digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
}
void no_light() { //when it really just turns all lights on b/c it can't find track
  digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
}
void end_light(){ //blue and red turn on when all sensors sense black
  
  digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
}

void loop() {
  int leftvol = analogRead(sensorl); // next three lines init sensors
  int rightvol = analogRead(sensorr);
  int centervol = analogRead (sensorc);
  unsigned long currentMillis = millis();
  
  Serial.print (leftvol); //next couple lines print out to serial mapper & serial plotter info
  Serial.print("  ");
  Serial.print(rightvol);
  Serial.print("  ");
  Serial.println (centervol*2);

  
  bool left_signal = (leftvol > left_thresh) && (rightvol < right_thresh) && (centervol < center_thresh); // 1,2,3 are basic cases for going forward, left and right based on IR sensors
  bool right_signal = (leftvol < left_thresh) && (rightvol > right_thresh) && (centervol < center_thresh);
  bool straight_signal = (leftvol < left_thresh) && (rightvol < right_thresh) && (centervol > center_thresh);
  
  bool left_straight_signal = (leftvol > left_thresh) && (rightvol < right_thresh) && (centervol > center_thresh); //4, 5 are for small variations to allow car to be more smooth
  bool right_straight_signal = (leftvol < left_thresh) && (rightvol > right_thresh) && (centervol > center_thresh);
  
  bool no_signal = (leftvol < left_thresh) && (rightvol < right_thresh) && (centervol < center_thresh); //6, 7 are for when there is error and there is end
  bool end_signal = (leftvol > left_thresh) && (rightvol > right_thresh) && (centervol > center_thresh);


  if(straight_signal){ //if the middle sensor is at the threshhold and neither the others is, then keep going straight and green on
    analogWrite(rightm, straight_speed);
    analogWrite(leftm, straight_speed);
    middle_light();
  }
  else if(left_signal){ //left sensor is being detected, so therefore you must slow down left motor so right motor can overtake so the car can turn, and the left light is the blue light
    analogWrite(rightm, straight_speed);
    analogWrite(leftm, turning_speed);
    left_light();
  }
  else if (right_signal){ //right sensor is being detected, so slow down right motor and keep left motor at straight speed to overtake ,and red light is right light
    analogWrite(rightm, turning_speed);
    analogWrite(leftm, straight_speed);
    right_light();
  }
  else if(left_straigh_signal) { //when left & middle are on threshhold, then kinda go left by slightly weakning left motor
    analogWrite(rightm, straight_speed);
    analogWrite(leftm, slight_turning_speed);
    left_light();
  }
  else if(right_straigh_signal) { //when right & middle are on threshhold, then kinda go left by slightly weakning right motor
    analogWrite(rightm, slight_turning_speed);
    analogWrite(leftm, straight_speed);
    right_light();
  }
  else if(no_signal){ //No signal means we've gone off the track, therefore we can't do anything, just keep going forwards & turn all lights on as indication of error
    analogWrite(rightm, straight_speed);
    analogWrite(leftm, straight_speed)
    no_light();
    
  }
  else if(end_signal){ //we have to check if there is the end line twice so we have a counter in the init part of the code that will count how many times
    if(end_count == 0){ //first time we see it we have to wait for the second time
      end_count++;
    }
    if(end_count == 1){ //initate shutdown sequence
      analogWrite(rightm, stop_speed);
      analogWrite(leftm, stop_speed);
      end_light();
      delay(5000);
      exit(0); //online forums says this is supposed to allow the loop to exit, but idk we'll see
    }
  }

 

//  analogWrite(leftm, 250);            FROM HERE: DEBUG CODE
// analogWrite(rightm, 250);
//
//
// 
//  Serial.println();
//  if ((leftvol>left_thresh)&&(rightvol>right_thresh)&&(centervol>center_thresh)){
//    digitalWrite(red, HIGH);
//    digitalWrite(blue, HIGH);
//    digitalWrite(green, LOW);
//    analogWrite(leftm, 0);
//    analogWrite(rightm, 0);
//  }
//  else if (rightvol>right_thresh){//move right
//    digitalWrite(red, HIGH);
//    digitalWrite(green, LOW);
//    digitalWrite(blue, LOW);
//  }
//  else if (leftvol>left_thresh) {//move left
//    digitalWrite(red, LOW);
//    digitalWrite(green, LOW);
//    digitalWrite(blue, HIGH);
//  }
//  else if (centervol>center_thresh){//move straight
//    digitalWrite(red, LOW);
//    digitalWrite(green, HIGH);
//    digitalWrite(blue, LOW);
//  }                                   TO HERE: DEBUG CODE
  
  // put your main code here, to run repeatedly:


}
