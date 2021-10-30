# ArduinoClockHost

This repo contains two folders, one for source code of Arduino and one for the source code of the hose machine in C#
I used PlatformIO to program Arduino, but the code should also work in Arduino IDE by simply copying the source code into a sketch.
Please be informed that the LiquidCrystalI2C library is required. 

The C# project contains all source code to run the host machine. For the quickest start, go to bin/debug and run the .exe, then the serial comm UI will be displayed. 
Upon starting the serial comm UI, the com ports should be automatically loaded if the arduino is already plugged in. If not, plugin Arduino to PC and click the check ports button. The last com port should be for Arduino. Then, choose a baudrate that matches the Arduino's. In my programs, I set them both to 115200. 
When com port and baudrate are set, press CONNECT to start sending time and date to Arduino, then Arduino will display date, day of the week and time on the LCD screen. 

To remind myself to stand up every hour, the LCD screen flashes three times at O'clocks. Enjoy! 
