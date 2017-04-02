#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define I2C_ADDR 0x27 // <
#define BACKLIGHT_PIN 3
DHT dht;
LiquidCrystal_I2C lcd(I2C_ADDR,2,1,0,4,5,6,7);

void setup()
{
	Serial.begin(9600);
    Serial.println();
    Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

    dht.setup(2);
    lcd.begin (16,2);
}

void loop()
{
    
	delay(dht.getMinimumSamplingPeriod());

    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

      Serial.print(dht.getStatusString());
	  Serial.print("\tHumidity :");
	  Serial.print(humidity, 1);
	  Serial.print("\t\tTemp C:");
	  Serial.print(temperature, 1);
	  Serial.print("\t\tTemp F:");
	  Serial.println(dht.toFahrenheit(temperature), 1);

	  // Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home ();
    
    lcd.setCursor(1,0);
    lcd.print("Humidity:"); 
    lcd.print(humidity);
    lcd.setCursor(0,1);
    lcd.print("C:");
    lcd.print(temperature);
    lcd.print("  F:");
    lcd.print(dht.toFahrenheit(temperature));

}
