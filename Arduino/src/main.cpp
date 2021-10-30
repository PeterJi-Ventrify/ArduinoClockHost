#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

String a;

String date;
String time;
String dayOfWeek; 

int serial_timeout = 100;
int firstSpace; // The first space separates the date and time
int firstM;     // The first M notes whether it's AM or PM
int secondSpace; 

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(serial_timeout);
  Serial.println("Initializing...");
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0); 
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  Serial.println("Initial ization Done");
} 


void loop()
{
  while(Serial.available()) 
  {
    a = Serial.readString();
    // a[5] = 32;
    // a[6] = 32;
    // Serial.println(a);
  }
  firstSpace = a.indexOf(' ');
  firstM = a.indexOf('M');
  secondSpace = firstM - 2;
  // a = "mm/dd/yyyy hh:mm:ss AMDoW"
  date = a.substring(0,firstSpace); // Add in spaces to clear the characters on LCD
  time = a.substring(firstSpace+1, secondSpace-3) + " " + a.substring(firstM-1, firstM+1);
  dayOfWeek = a.substring(firstM+1);
       if (dayOfWeek == "Monday")     dayOfWeek = "MON";
  else if (dayOfWeek == "Tuesday")    dayOfWeek = "TUE";
  else if (dayOfWeek == "Wednesday")  dayOfWeek = "WED";
  else if (dayOfWeek == "Thursday")   dayOfWeek = "THU";
  else if (dayOfWeek == "Friday")     dayOfWeek = "FRI";
  else if (dayOfWeek == "Saturday")   dayOfWeek = "SAT";
  else if (dayOfWeek == "Sunday")     dayOfWeek = "SUN";
  lcd.home();
  // Center the cursor for date display
  //lcd.print(a.substring(0,16));
  lcd.print(" " + date + " " + dayOfWeek + " ");
  // Center the cursor for time display
  lcd.setCursor(0,1);
  //lcd.print(a.substring(16));
  if (time.length() == 7) lcd.print("    " + time + "     ");
  else lcd.print("   " + time + "     ");
  if (a.startsWith("00:00", firstM-7))
  {
    for (int i = 0; i < 3; i ++){
      lcd.noBacklight();
      delay(1000);
      lcd.backlight();
      delay(1000);
    }
  }
}