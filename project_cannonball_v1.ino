#include <Servo.h>
#include <TimerOne.h>

//Define important addresses
#define SLAVE_ADDRESS 0x08
#define PIN_MOTOR_1_ENA 6;
#define PIN_MOTOR_2_ENB 5;
#define PIN_MOTOR_1_IN1 0;
#define PIN_MOTOR_1_IN2 1;
#define PIN_MOTOR_1_IN3 2;
#define PIN_MOTOR_1_IN4 4;



//MAIN PIN SETUPS, DO NOT CHANGE:
int PIN_VERTICAL = 10;
int PIN_HORIZONTAL = 9;

int PIN_FIRE = 3;

//Global Constants
int ANGLE_RESET = 0;
int FIRE_RESET = 90;
int BASE_SPEED = 0;

//Other Global Constants
int VERTICAL_UPPER_LIMIT = 180;
int VERTICAL_LOWER_LIMIT = 0;
int HORIZONTAL_UPPER_LIMIT = 180;
int HORIZONTAL_LOWER_LIMIT = 0;
int FIRE_WAIT_TIME = 100;

//Setup Servo Objects DO NOT CHANGE:
Servo VERTICAL;
Servo HORIZONTAL;
Servo FIRE;

//Setup Global Angle-Tracking variables
int VerticalServo;
int HorizontalServo;
int MotorSpeed;

private void MoveUp(int degree){
  if ((VerticalServo + degree) > VERTICAL_UPPER_LIMIT){
    //return error
    System.out.println("Vertical Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo += degree;
    VERTICAL.write(VerticalServo);
  }
}

private void MoveDown(int degree){
  if ((VerticalServo - degree) < VERTICAL_LOWER_LIMIT){
    //return error
    System.out.println("Vertical Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo -= degree;
    VERTICAL.write(VerticalServo);
  }
}

private void MoveRight(int degree){
  if ((HorizontalServo + degree) > HORIZONTAL_UPPER_LIMIT){
    //return error
    System.out.println("Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo += degree;
    VERTICAL.write(VerticalServo);
  }
}
private void MoveLeft(int degree){
  if ((HorizontalServo - degree) < HORIZONTAL_LOWER_LIMIT){
    //return error
    System.out.println("Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo -= degree;
    VERTICAL.write(VerticalServo);
  }
}
private void Fire(){
  FIRE.write(0);
  delay(FIRE_WAIT_TIME);
  FIRE.write(90);
}
private void Arm(int mode){
  int spinSpeed = 0;
  if(mode == 1){
    spinSpeed = 10;
  }
  else if (mode == 2){
    spinSpeed = 50;
  }
  else if(mode == 3){
    spinSpeed = 98;
  }

  Timer1.initialize(spinSpeed)//KHZ = spinSpeed / 10
  Timer1.pwm(PIN_MOTOR_1_ENA, 512);
  Timer1.pwm(PIN_MOTOR_2_ENB, 512);
  
}
private void Disarm(){
  analogWrite(PIN_MOTOR_1_ENA, 0);
  analogWrite(PIN_MOTOR_2_ENB, 0);
}


void setup() {

  //Attach Servo Pins to Servo Objects and reset
  try{
    VERTICAL.attach(PIN_VERTICAL);
    HORIZONTAL.attach(PIN_HORIZONTAL);
    FIRE.attach(PIN_FIRE);

    //Reset all servo angles
    VERTICAL.write(ANGLE_RESET);
    HORIZONTAL.write(ANGLE_RESET);
    FIRE.write(FIRE_RESET);

    //Setup Global Angle-Tracking variables
    int VerticalServo = ANGLE_RESET;
    int HorizontalServo = ANGLE_RESET;
    int MotorSpeed = BASE_SPEED;

    //Setup DC motors
    pinMode(PIN_MOTOR_1_ENA, OUTPUT);
    pinMode(PIN_MOTOR_2_ENB, OUTPUT);
    pinMode(PIN_MOTOR_1_IN1, OUTPUT);
    pinMode(PIN_MOTOR_1_IN2, OUTPUT);
    pinMode(PIN_MOTOR_2_IN3, OUTPUT);
    pinMode(PIN_MOTOR_2_IN4, OUTPUT);

    //Set rotation direction
    digitalWrite(PIN_MOTOR_1_IN1, LOW);
    digitalWrite(PIN_MOTOR_1_IN2, HIGH);
    digitalWrite(PIN_MOTOR_2_IN3, HIGH);
    digitalWrite(PIN_MOTOR_2_IN4, LOW);

    //Turn off motors
    analogWrite(PIN_MOTOR_1_ENA, 0);
    analogWrite(PIN_MOTOR_2_ENB, 0);
    
   
  } catch (Exception e){
    System.out.println("Error: " + e);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  String incomingCommand = Serial.readString().

  switch (incomingCommand){
    case "MOVEUP":
      break;
    case "MOVEDOWN":
      break;
    case "MOVERIGHT":
      break;
    case "MOVELEFT":
      break;
    case "FIRE":
      break;
    case "ARM":
      break;
    case "DISARM":
      break;
  }

}
