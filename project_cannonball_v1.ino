#include <Servo.h>
#include <TimerOne.h>



//Define important addresses
#define SLAVE_ADDRESS 0x08
#define PIN_MOTOR_1_ENA 6
#define PIN_MOTOR_2_ENB 5
#define PIN_MOTOR_1_IN1 0
#define PIN_MOTOR_1_IN2 1
#define PIN_MOTOR_2_IN3 2
#define PIN_MOTOR_2_IN4 4



//MAIN PIN SETUPS, DO NOT CHANGE:
#define PIN_VERTICAL 10
#define PIN_HORIZONTAL 9
#define PIN_FIRE 3

//Servo Delcarations
Servo VERTICAL;
Servo HORIZONTAL;
Servo FIRE;

//Global Variables
int ANGLE_RESET = 0;
int FIRE_RESET = 90;
int BASE_SPEED = 0;

//Other Global Bariables
int VERTICAL_UPPER_LIMIT = 180;
int VERTICAL_LOWER_LIMIT = 0;
int HORIZONTAL_UPPER_LIMIT = 180;
int HORIZONTAL_LOWER_LIMIT = 0;
int FIRE_WAIT_TIME = 100;

//Setup Global Angle-Tracking variables
int VerticalServo;
int HorizontalServo;
int MotorSpeed;




void setup() {
  //Begin Serial
  Serial.begin(9600);


  //Attach Servo Pins to Servo Objects and reset
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
}

void loop() {
  // put your main code here, to run repeatedly:

  String incomingCommand = "";

  if(incomingCommand.equals("MOVEUP")){
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVEDOWN")){
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVERIGHT")){
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVELEFT")){
    incomingCommand = "";  
  }
  else if(incomingCommand.equals("FIRE")){
    incomingCommand = "";
  }
  else if(incomingCommand.equals("ARM")){
    incomingCommand = "";
  }
  else if(incomingCommand.equals("DISARM")){
    
  }
}

void MoveUp(int degree){
  if ((VerticalServo + degree) > VERTICAL_UPPER_LIMIT){
    //return error
    Serial.println("Vertical Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo += degree;
    VERTICAL.write(VerticalServo);
  }
}

void MoveDown(int degree){
  if ((VerticalServo - degree) < VERTICAL_LOWER_LIMIT){
    //return error
    Serial.println("Vertical Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo -= degree;
    VERTICAL.write(VerticalServo);
  }
}

void MoveRight(int degree){
  if ((HorizontalServo + degree) > HORIZONTAL_UPPER_LIMIT){
    //return error
    Serial.println("Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo += degree;
    VERTICAL.write(VerticalServo);
  }
}
void MoveLeft(int degree){
  if ((HorizontalServo - degree) < HORIZONTAL_LOWER_LIMIT){
    //return error
    Serial.println("Degree delta amount too high");
  }
  else{
    //go ahead and run command
    VerticalServo -= degree;
    VERTICAL.write(VerticalServo);
  }
}
void Fire(){
  FIRE.write(0);
  delay(FIRE_WAIT_TIME);
  FIRE.write(90);
}
void Arm(int mode){
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

  Timer1.initialize(spinSpeed);//KHZ = spinSpeed / 10
  Timer1.pwm(PIN_MOTOR_1_ENA, 512);
  Timer1.pwm(PIN_MOTOR_2_ENB, 512);
  
}
void Disarm(){
  analogWrite(PIN_MOTOR_1_ENA, 0);
  analogWrite(PIN_MOTOR_2_ENB, 0);
}
