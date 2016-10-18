#include <Key.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte colPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte rowPins[COLS] = {8,9,10,11}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



#include <SoftwareSerial.h>

SoftwareSerial lcd(2, 3);  // This is required, to start an instance of an LCD

int wrongAnswerDelay=10000;

void setup()
{
  pinMode(13, OUTPUT);
  
  lcd.begin(9600);  // Start the LCD at 9600 baud
  clearDisplay();  // Clear the display
  setLCDCursor(0);  
  lcd.print("Merry Xmas");
  setLCDCursor(16);  
  lcd.print("From Mom and Dad");
  
  // Flash the backlight:
  for (int i=0; i<10; i++)
  {
    setBacklight(0);
    delay(250);
    setBacklight(255);
    delay(250);
  }
}

void loop()
{
  waitForAnswer("Pi to 6 digits", "314159");

  waitForAnswer("Mom's birthday", "051467");

  clearDisplay();
  setLCDCursor(0);  
  lcd.print("Look in junk drawer for hint");
  delay(10000);

  waitForAnswer("x=", "3");
  
  clearDisplay();
  setLCDCursor(0);  
  lcd.print("Look around the office computer");
  delay(10000);

  waitForAnswer("Charles Darwin ship", "C");

  waitForAnswer("Larry Bird's #", "33");
  
  clearDisplay();
  setLCDCursor(0);  
  lcd.print("Finn has your next clue");
  delay(10000);  

  waitForAnswer("What year?", "1776");

  waitForAnswer("# of cartons?", "11");


  clearDisplay();  // Clear the display
  setLCDCursor(0);  
  lcd.print("Congratulations");

  // Flash the backlight:
  for (int i=0; i<10; i++)
  {
    setBacklight(0);
    delay(250);
    setBacklight(255);
    delay(250);
  }    

  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the vo
}

void setBacklight(byte brightness)
{
  lcd.write(0x80);  // send the backlight command
  lcd.write(brightness);  // send the brightness value
}

void clearDisplay()
{
  lcd.write(0xFE);  // send the special command
  lcd.write(0x01);  // send the clear screen command
}

void setLCDCursor(byte cursor_position)
{
  lcd.write(0xFE);  // send the special command
  lcd.write(0x80);  // send the set cursor command
  lcd.write(cursor_position);  // send the cursor position
}

void wrongAnswer(void)
{
  int seconds=60;
  
  clearDisplay();  // Clear the display
  setLCDCursor(0);  
  lcd.print("Wrong Answer");

  while(seconds)
  {
    setLCDCursor(16);
    lcd.print("               ");
    setLCDCursor(16);
    lcd.print(seconds);    
    delay(1000);
    seconds--;
  }

}

void waitForAnswer(String text, String answer)
{
  String input("");
  char key=0;
  int numKeys=0;
  bool wrong=true;
  int answerLen=answer.length();  


  while(wrong)
  {
    key=0;
    numKeys=0;
    clearDisplay();  // Clear the display
    setLCDCursor(0);  
    lcd.print(text);    
    input="";
    
    while(numKeys < answerLen)
    {
      key=keypad.getKey();
        
      if (key == NO_KEY)
      {
        continue;
      }
      setLCDCursor(16);
      lcd.print("              ");
      
      if (key == 'B')
      {
        input.remove(input.length()-1);
        numKeys--;
        if (numKeys==0)
        {
          input.remove(0);
        }
      }
      else
      {
        input += key;
        numKeys++;
      }
      setLCDCursor(16);
      lcd.print(input);
      
    } 
  
    if (input == answer)
    {
      wrong=false;
      break;
    }
  
    wrongAnswer();

  }
}


