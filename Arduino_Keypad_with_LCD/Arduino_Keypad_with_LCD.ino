//
//#include<LiquidCrystal.h>
//#include<Keypad.h>
//
//LiquidCrystal lcd(3, 2, 9, 10, 11, 12);
//char keys[4][4] =
//{
//  {'7', '8', '9', '/'},
//  {'4', '5', '6', '*'},
//  {'1', '2', '3', '-'},
//  {'c', '0', '=', '+'}
//};
//
//byte rowPins[] = {A3, A2, A1, A0};
//byte colPins[] =  {4, 5, 6, 7};
//Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);
//// calculator
//boolean isPNMD[4] = {false, false, false, false};
//char takeInputasString[5] = "Empty";
//int integerInput;
//int tempInteger;
//int resultP= integerInput +resultP;
//int resultN =  resultN-integerInput;
//
//int resultM =  resultM*integerInput;
//int resultD =  resultD/integerInput;
//
//void setup() {
//
//  // put your setup code here, to run once:
//  pinMode(13, OUTPUT);
//  lcd.begin(16, 2);
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//
//  char input = keypad.getKey();
//
//  int results = 0;
//
//
//  if (input) {
//    if (input == 'c') {
//      lcd.clear();
//      strcpy(takeInputasString, "");
//    }
//    if (input == '=') {
//      tempInteger = (int)strtol(takeInputasString, (char **)NULL, 10)
//
//      if (isPNMD[0] == 1) {
//        lcd.print(input);//=
//        lcd.setCursor(0, 1);
//        lcd.print(resultP);
//      }
//      if (isPNMD[1] == 1) {
//        lcd.print(input);// -
//        lcd.setCursor(0, 1);
//        lcd.print(resultN);
//      }
//      if (isPNMD[2] == 1) {
//        lcd.print(input);// *
//        lcd.setCursor(0, 1);
//        lcd.print(resultM);
//      }
//      if (isPNMD[3] == 1) {
//        lcd.print(input);//  /
//        lcd.setCursor(0, 1);
//        lcd.print(resultD);
//      }
//
//      for (int i = 0; i < 4; i++) {
//        isPNMD[i] = 0;
//      }
//      strcpy(takeInputasString, "");
//
//    }
//
//    if (input == '+') {
//      integerInput = (int)strtol(takeInputasString, (char **)NULL, 10);
//      strcpy(takeInputasString, "");
//      lcd.print(input);
//    }
//
//    if (input == '-') {
//      integerInput = (int)strtol(takeInputasString, (char **)NULL, 10);
//      strcpy(takeInputasString, "");
//      lcd.print(input);
//    }
//    if (input == '/') {
//      integerInput = (int)strtol(takeInputasString, (char **)NULL, 10);
//      strcpy(takeInputasString, "");
//      lcd.print(input);
//    }
//    if (input == '*') {
//      integerInput = (int)strtol(takeInputasString, (char **)NULL, 10);
//      strcpy(takeInputasString, "");
//      lcd.print(input);
//    }
//
//    else {
//      strncat(takeInputasString, &input, 1);
//    }
//
//  }
//}
//
//
//
#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(3, 2, 9, 10, 11, 12);

// Define the keys present on the keypad
char keys[4][4] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'c', '0', '=', '+'}
};

// Specify the pins used for the rows and columns of the keypad
byte rowPins[] = {A3, A2, A1, A0};
byte colPins[] =  {4, 5, 6, 7};

// Initialize the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

// Flags to indicate which operation is selected
boolean isPNMD[4] = {false, false, false, false}; // Plus, Minus, Multiply, Divide

// Variables for input handling and calculations
char takeInputasString[16] = ""; // Increased size to handle larger numbers and prevent overflow
long integerInput = 0;
long result = 0;

void setup() {
  lcd.begin(16, 2); // Initialize the LCD
  lcd.clear(); // Clear the LCD
}

void loop() {
  char input = keypad.getKey(); // Read the input from the keypad

  if (input) {
    lcd.clear(); // Clear the LCD to display the current input
    if (input == 'c') { // Clear the input and reset the calculator
      strcpy(takeInputasString, "");
      result = 0;
      for (int i = 0; i < 4; i++) {
        isPNMD[i] = false;
      }
      lcd.clear();
    } else if (input == '=') {
      integerInput = strtol(takeInputasString, NULL, 10); // Convert the string input to an integer
      // Perform the operation based on the flag set
      if (isPNMD[0]) result += integerInput;
      if (isPNMD[1]) result -= integerInput;
      if (isPNMD[2]) result *= integerInput;
      if (isPNMD[3]) result /= integerInput;

      // Display the result
      lcd.print(result);

      // Reset the operation flags
      for (int i = 0; i < 4; i++) {
        isPNMD[i] = false;
      }
      strcpy(takeInputasString, ""); // Reset the input string
    } else if (input == '+' || input == '-' || input == '*' || input == '/') {
      // Convert the current input string to an integer
      integerInput = strtol(takeInputasString, NULL, 10);
      if (result == 0) { // For the first operation, store the integerInput into result
        result = integerInput;
      }
//      if (result) { // For the first operation, store the integerInput into result
//        if(input =='+'){
//        result = result+integerInput;
//        }
//      }
      strcpy(takeInputasString, ""); // Clear the input string for the next number
      lcd.print(input); // Display the operation

      // Set the appropriate operation flag
      isPNMD[0] = (input == '+');
      isPNMD[1] = (input == '-');
      isPNMD[2] = (input == '*');
      isPNMD[3] = (input == '/');
    } else {
      // Append the current numeric input or '.' to the input string
      if (strlen(takeInputasString) < sizeof(takeInputasString) - 1) {
        strncat(takeInputasString, &input, 1);
        lcd.print(takeInputasString); // Display the current input string
      }
    }
  }
}
