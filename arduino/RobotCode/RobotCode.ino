
/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/communication/SerialEvent/
*/

const int FRONT_IN1 = 34;
const int FRONT_IN2 = 36;
const int FRONT_SPEED = 7; //enable

const int BACK_IN1 = 22;
const int BACK_IN2 = 23;
const int BACK_SPEED = 6;

const int RIGHT_IN1 = 39;
const int RIGHT_IN2 = 41;
const int RIGHT_SPEED = 5; //enable

const int LEFT_IN1 = 43;
const int LEFT_IN2 = 45;
const int LEFT_SPEED = 4; 


String inputString = "";      // a String to hold incoming data
String starterStringJoystick ="";
String xStringJoyStick = "";
String yStringJoyStick ="";
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial1.begin(9600);
  Serial.begin(9600);

  pinMode(FRONT_IN1,OUTPUT);
  pinMode(FRONT_IN2,OUTPUT);
  pinMode(FRONT_SPEED,OUTPUT);
    pinMode(BACK_IN1,OUTPUT);
  pinMode(BACK_IN2,OUTPUT);
  pinMode(BACK_SPEED,OUTPUT);
    pinMode(LEFT_IN1,OUTPUT);
  pinMode(LEFT_IN2,OUTPUT);
  pinMode(LEFT_SPEED,OUTPUT);
    pinMode(RIGHT_IN1,OUTPUT);
  pinMode(RIGHT_IN2,OUTPUT);
  pinMode(RIGHT_SPEED,OUTPUT);
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  digitalWrite(FRONT_IN1,LOW);
  digitalWrite(FRONT_IN2,LOW);
  digitalWrite(FRONT_SPEED,LOW);
    digitalWrite(BACK_IN1,LOW);
  digitalWrite(BACK_IN2,LOW);
  digitalWrite(BACK_SPEED,LOW);
    digitalWrite(LEFT_IN1,LOW);
  digitalWrite(LEFT_IN2,LOW);
  digitalWrite(LEFT_SPEED,LOW);
    digitalWrite(RIGHT_IN1,LOW);
  digitalWrite(RIGHT_IN2,LOW);
  digitalWrite(RIGHT_SPEED,LOW);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  starterStringJoystick.reserve(200);
  xStringJoyStick.reserve(200);
  yStringJoyStick.reserve(200);


}

void loop() {
  Serial.println("blorp");
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.startsWith("wJ")){  //change to be if string starts with wJ  wJ,127,50\n
      //split the string into x and y values.   .split(",")  equivalent
      starterStringJoystick = inputString.substring(0,inputString.indexOf(","));
      inputString = inputString.substring(inputString.indexOf(","),inputString.length());

       starterStringJoystick = inputString.substring(0,inputString.indexOf(","));
      xStringJoyStick = xStringJoyStick.substring(inputString.indexOf(","),inputString.length());

      starterStringJoystick = inputString.substring(0,inputString.indexOf("/n"));
      yStringJoyStick = yStringJoyStick.substring(inputString.indexOf(","),inputString.length());

    int xval = xStringJoyStick.toInt();
    int yval = yStringJoyStick.toInt();

      digitalWrite(FRONT_IN1,HIGH);
      digitalWrite(FRONT_IN2,LOW);
      analogWrite(FRONT_SPEED, abs((xval*2)-1));

      digitalWrite(BACK_IN1,HIGH);
      digitalWrite(BACK_IN2,LOW);
      analogWrite(BACK_SPEED, abs(xval*2)-1);

      digitalWrite(RIGHT_IN1,HIGH);
      digitalWrite(RIGHT_IN2, LOW);
      analogWrite(RIGHT_SPEED, abs(yval*2)-1);

      digitalWrite(LEFT_IN1,HIGH);
      digitalWrite(LEFT_IN2, LOW);
      analogWrite(LEFT_SPEED, abs(yval*2)-1);


    } 
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
