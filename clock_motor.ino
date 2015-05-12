long d = 10; //delay
int stps = 0;
int rotations = 0;
int mode = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(8, OUTPUT);  //using this as direction pin
  pinMode(9, OUTPUT); //this is the step control
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void loop() {
  
  if (mode == 0) {
//    Serial.println("mode = 0");
    stps = 0;
  }

  if (mode == 1) {
    fullRotation();
  }
 
  if (mode == 2) {
    calibrate();
  }
  
  if (mode == 3) {
    testRotation();
  }
 
  
  //  If you use delay(10); for both, the you'll move at 50 microsteps/second.
  
  //for adjusting speed
  char c;
  if(Serial.available()) {
    c = Serial.read();
    
    if (c == '0') {  // PRESS '0' TO SET TO 12 POSITION
      stps = 0;
    }
    if (c == 'g') {  // PRESS 'g' TO START MOVING THE MOTOR - it will make one full rotation then stop
      mode = 1;
    }
    if (c == 's') {  // PRESS 's' KEY TO STOP THE MOTOR
      mode = 0;
    }
    if (c == 'c') {  // FOR CALIBRATION - - - press 'c' key to move the motor slowly, then stop when at the top
      mode = 2;
    }
    if (c == 't') {  // FOR CALIBRATION - - - press 'c' key to move the motor slowly, then stop when at the top
      mode = 3;
    }
    

  }
  
}


void fullRotation() {
  d = 65536; //65535 is the max delay you can give
  digitalWrite(9, HIGH); //everytime this is called, the stepper motor will move 1/8th of a full step
  Serial.println("going for long delay!");                     
  delay(5); //this is how long in milliseconds before it flips the motor         
  digitalWrite(9, LOW); 
  myDelay(d); 
  stps = stps + 1;
  
  if (stps >= 385) { // the number of 1/8th steps that this motor takes to make a full rotation
     stps = 0;
     mode = 0;
   }
   
  Serial.println(stps); 
}

//new delay function
void myDelay(long millisecDelay){

  if (millisecDelay > 65534 && millisecDelay < 2*65534){
    int extraDelay = millisecDelay - 65534;
    delay(65534);
    delay(extraDelay);
  }
  else if(millisecDelay > 2*65534)
    Serial.println("Delay too long");
    //    int divisor = millisecDelay/2;
//    if(65535%2 == 0)
//      remainder =0;
//    else
//       int remainder = 1;
//    for(int i = 2; i > 0 ; i--){
//      delay(millisecDelay / 2);
//      }
  else
    delay(millisecDelay);
}

void calibrate() {
  d = 60;
  digitalWrite(9, HIGH); //everytime this is called, the stepper motor will move 1/8th of a full step
                         //1.8 degrees per step, there will be 200 full steps per revolution, or 1600 microsteps per revolution. 
  delay(d); //this is how long in milliseconds before it flips the motor         
  digitalWrite(9, LOW); 
  delay(d); 
  
  Serial.println("calibrating - press 's' when in the start position"); 
}

void testRotation() {
  d = 0;
  digitalWrite(9, HIGH); //everytime this is called, the stepper motor will move 1/8th of a full step
                         //1.8 degrees per step, there will be 200 full steps per revolution, or 1600 microsteps per revolution. 
  delay(d); //this is how long in milliseconds before it flips the motor         
  digitalWrite(9, LOW); 
  delay(d); 
  
  stps = stps + 1;
  
  if (stps >= 385) { // the number of 1/8th steps that this motor takes to make a full rotation
     stps = 0;
     mode = 0;
   }
  
  Serial.println("test rotation"); 
}
  
