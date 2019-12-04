//Henry's Bench
//KY-031 Knock Sensor Tutorial

#include <dht.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

int knockPin = 3; // Use Pin 10 as our Input
int knockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;

unsigned long lastKnockTime; // Record the time that we measured a shock

int knockAlarmTime = 500; // Number of milli seconds to keep the knock alarm high

DS3231 rtc(SDA, SCL);
dht DHT;
#define DHT11_PIN 9
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup ()
{
  rtc.begin();
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Created By:");

  lcd.setCursor(0, 1);
  lcd.print("Ryan Richardson"); 
  pinMode (knockPin, INPUT) ; // input from the KY-031
}
void loop ()
{
  knockVal = digitalRead (knockPin) ; // read KY-031 Value
  
  if (knockVal == LOW) // If we see a knock
  {
  
    lastKnockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("KNOCK, KNOCK");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastKnockTime) > knockAlarmTime  &&  bAlarm){
      Serial.println("no knocks");
      bAlarm = false;
    }
  }
  if(bAlarm == true) {
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(rtc.getTimeStr());
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("F");  
    delay(4000);
    lcd.setCursor(0, 0);
    lcd.print("Created By:     ");
    lcd.setCursor(0, 1);
    lcd.print("Ryan Richardson ");
  }
}
