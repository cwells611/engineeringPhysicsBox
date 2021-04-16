//Imports the Libraries Needed 
#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal.h>

//Initilize IR Pin
int RECV_PIN = 6;

//Create Servo  and LCD Objects
Servo lidServo;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Initial Password and User Password Set 
String password = "12345";
String userPassword = "";

//Counter Initilize 
int counter = 1;

void passCheck(String pass, String passAttempt) {
  if(pass.equals(passAttempt)) {
    lcd.clear();
    lcd.print("Correct");
    for(int i = 45; i >= 10; i--) {
      delay(50);
      lidServo.write(i);
    }
    delay(10000);
    for(int i = 0; i <= 100; i++) {
      delay(50);
      lidServo.write(i);
    }
  }
  else {
    lcd.clear();
    lcd.print("Incorrect");
    delay(5000);
    lcd.clear();
  }
}

void setup() {
  // put your setup code here, to run once:
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  
  //Attach Servo to Pin 5
  lidServo.attach(5);

  //Initializes Size of LCD
  lcd.begin(16, 2);

  //Asks for Password
  lcd.print("Password:");

  //Sets Cursor on 2nd Row, first column to enter password
  lcd.setCursor(0, 2);
}

void mainFunction() {
  //Continually checks to see if the IR Receiver has received any codes,
  //and if it has, checks to make sure the password length has not been reached,
  //and if that has not occured, it checks the code and prints the corresponding number
  //on the screen
  if(IrReceiver.decode()) {
    while(counter <= 10) {
      switch(IrReceiver.decodedIRData.decodedRawData) {
        case 0xF30CBF00:
          lcd.print("0");
          userPassword += "0";
          break;
        case 0xEF10BF00:
          lcd.print("1");
          userPassword += "1";
          break;
        case 0xEE11BF00:
          lcd.print("2");
          userPassword += "2";
          break;
        case 0xED12BF00:
          lcd.print("3");
          userPassword += "3" ;
          break;
        case 0xEB14BF00:
          lcd.print("4");
          userPassword += "4";
          break;
        case 0xEA15BF00:
          lcd.print("5");
          userPassword += "5";
          break;
        case 0xE916BF00:
          lcd.print("6");
          userPassword += "6";
          break;
        case 0xE718BF00:
          lcd.print("7");
          userPassword += "7";
          break;
        case 0xE619BF00:
          lcd.print("8");
          userPassword += "8";
          break;
        case 0xE51ABF00:
          lcd.print("9");
          userPassword += "9";
          break;
      }
      counter++;
      break;
    }
    IrReceiver.resume();
  }

  if(counter >= 10) {
    passCheck(password, userPassword);
    delay(100000);
  }
}

void loop() {
  mainFunction();
}
