// O'Shea House Temperature Variation Analysis Scanner
// Using the DHT11 sensor, arduino will collect data to study the variation of temperature throughout household rooms,
//  From this, the data can be analyzed to see where the greatest heat/cooling loss will be. THIS IS MEANT TO BE RUN WITH COOLTERM

// Increments will run to record temperature every 5 minutes for eight hours; for the greatest accuracy, run at same time each day
// Author: Tom O'Shea, toshea97@vt.edu


// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"

// set the DHT Pin
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// create arrays for temp, humidity
int temp[96]; //recorded every 5 minutes for 8 hours
int humidity[96];
int t = 0; //initialize the incrementer 

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  dht.begin();
  
  // Print a message to the LCD.
  lcd.print("Prog:   %");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");

  //open serial port for comms
  Serial.begin(9600); //sets serial port for communication
}

void loop() {

  while (t < 95)
  {
    
 
    
    // read humidity
    float h = dht.readHumidity();
    //read temperature in Fahrenheit
    float f = dht.readTemperature(true);

// record and print to serial. Connect to CoolTerm for easy access to data for processsing
      temp[t] = f;
      humidity[t] = h;
      duration[t] = t;
      //Serial.println(duration[t]);
      Serial.println(temp[t]);
      Serial.println(humidity[t]);
      

//Calculate Progress
int tot = 96; //number of increments in the proc
double prog = (t/tot)*100;
int roundProg = round(prog);

   if (isnan(h) || isnan(f)) 
   {
    lcd.print("ERROR");
    return;
   }

   // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(6, 0);
    lcd.print(roundProg);
    lcd.setCursor(6,6);
    lcd.print(f); 
//    lcd.setCursor(12,1);
//    lcd.print(t);
//    lcd.setCursor(14,1);
//    lcd.print(i);
    
    t++; //increment time value

    delay(300000); //wait five minutes
  }

// after recording is complete
lcd.setCursor(0, 1);
lcd.print('Complete');

int j = 0;


}

