#define blue 10
#define red 11
#define green 12
#define sensorr 0
#define sensorl 1
#define sensorc 2
#define leftm 6
#define rightm 5

#define time 100
// for left, threshold is 300
//center, threshold is 39
//for right, threshold is 90
#define left_thresh 100
#define center_thresh 100
#define right_thresh 100
void setup() {
  // put your setup code here, to run once:
  pinMode(blue, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode(leftm, OUTPUT);
  pinMode(rightm, OUTPUT);
  
  Serial.begin (9600);
}
void leftMO(){
  analogWrite(leftm, 50);
  delay(time);
}


void rightMO(){
  analogWrite(rightm, 50);
  delay(time);
}


void loop() {
  int leftvol = analogRead(sensorl);
  int rightvol = analogRead(sensorr);
  int centervol = analogRead (sensorc);
  unsigned long currentMillis = millis();
  Serial.print (leftvol);
  Serial.print("  ");
 Serial.print(rightvol);
Serial.print("  ");
Serial.println (centervol*2);
 

  analogWrite(leftm, 250);
 analogWrite(rightm, 250);


 
  Serial.println();
  if ((leftvol>left_thresh)&&(rightvol>right_thresh)&&(centervol>center_thresh)){
    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    analogWrite(leftm, 0);
    analogWrite(rightm, 0);
  }
  else if (rightvol>right_thresh){//move right
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }
  else if (leftvol>left_thresh) {//move left
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
  }
  else if (centervol>center_thresh){//move straight
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
  }
  
  // put your main code here, to run repeatedly:

}
