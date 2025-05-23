#include <Servo.h>
#include <ArduinoJson.h>

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

//Other Global Bariables
int VERTICAL_UPPER_LIMIT = 50;
int VERTICAL_LOWER_LIMIT = 0;
int HORIZONTAL_UPPER_LIMIT = 180;
int HORIZONTAL_LOWER_LIMIT = 0;

//Setup Global Angle-Tracking variables
int VerticalServo;
int HorizontalServo;

void setup() {
  //Begin Serial
  Serial.begin(9600);


  //Attach Servo Pins to Servo Objects and reset
    VERTICAL.attach(PIN_VERTICAL);
    HORIZONTAL.attach(PIN_HORIZONTAL);

    //Reset all servo angles
    VERTICAL.write(ANGLE_RESET);
    HORIZONTAL.write(ANGLE_RESET);

    //Setup Global Angle-Tracking variables
    VerticalServo = ANGLE_RESET;
    HorizontalServo = ANGLE_RESET;
}

void loop() {
  // put your main code here, to run repeatedly:
  JsonDocument doc;
  String inByte;
  // read from port 1, send to port 0:
  if (Serial.available() > 0) {
    inByte = Serial.readString();
    inByte.trim(); // remove any whitespaces
  }

  if(inByte.length() == 0) return; // Skip if nothing was read

  DeserializationError error = deserializeJson(doc, inByte);

  if (error) {
    Response("Deserialization Error: " + String(error.f_str()), false);
    inByte = "";  // Clear input after error
    return;
  }

  String incomingCommand = doc["action"];
  int parameter = doc["angle"];


  if(incomingCommand.equals("MOVEUP")){
    MoveUp(parameter);
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVEDOWN")){
    MoveDown(parameter);
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVERIGHT")){
    MoveRight(parameter);
    incomingCommand = "";
  }
  else if(incomingCommand.equals("MOVELEFT")){
    MoveLeft(parameter);
    incomingCommand = "";  
  }
  else if(incomingCommand.equals("FIRE")){
    Fire();
    incomingCommand = "";
  }
  inByte = "";
}

void MoveUp(int degree){
  if ((VerticalServo + degree) > VERTICAL_UPPER_LIMIT){
    //return error
    Response("Move Up Delta amount too high: Position At " + String(VerticalServo) + " degrees", false);
  }
  else{
    //go ahead and run command
    VerticalServo += degree;
    VERTICAL.write(VerticalServo);
    Response("Move Up Successful: Position At " + String(VerticalServo) + " degrees", true);
  }
}

void MoveDown(int degree){
  if ((VerticalServo - degree) < VERTICAL_LOWER_LIMIT){
    //return error
    Response("Move Down Delta amount too high: Position At " + String(VerticalServo) + " degrees", false);
  }
  else{
    //go ahead and run command
    VerticalServo -= degree;
    VERTICAL.write(VerticalServo);
    Response("Move Down Successful: Position At " + String(VerticalServo) + " degrees", true);
  }
}

void MoveLeft(int degree){
  if ((HorizontalServo + degree) > HORIZONTAL_UPPER_LIMIT){
    //return error
    Response("Move Left Delta amount too high: Position At " + String(HorizontalServo) + " degrees", false);
  }
  else{
    //go ahead and run command
    HorizontalServo += degree;
    HORIZONTAL.write(HorizontalServo);
    Response("Move Left Successful: Position At " + String(HorizontalServo) + " degrees", true);
  }
}

void MoveRight(int degree){
  if ((HorizontalServo - degree) < HORIZONTAL_LOWER_LIMIT){
    //return error
    Response("Move Right Delta amount too high: Position At " + String(HorizontalServo) + " degrees", false);
  }
  else{
    //go ahead and run command
    HorizontalServo -= degree;
    HORIZONTAL.write(HorizontalServo);
    Response("Move Right Successful: Position At " + String(HorizontalServo) + " degrees", true);
  }
}

void Fire(){
  
  FIRE.attach(PIN_FIRE);
  FIRE.write(0);
  delay(460);
  FIRE.write(180);
  delay(460);
  FIRE.detach();

  Response("Fire Successful", true);
}

String Response(String message, bool successful){
  JsonDocument docSuccess;
  docSuccess["success"] = successful;
  docSuccess["message"] = message;

  String output;
  serializeJson(docSuccess, output);
  Serial.println(output);
  return output;
}
