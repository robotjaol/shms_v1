#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define DHTPIN 4
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MPU6050 mpu;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{

  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  if (!mpu.begin())
  {
    Serial.println("Failed to initialize MPU6050");
    lcd.setCursor(0, 0);
    lcd.print("MPU6050 Failed");
    while (1)
      ;
  }
  Serial.println("MPU6050 initialized");

  dht.begin();
  if (dht.readTemperature() == NAN || dht.readHumidity() == NAN)
  {
    Serial.println("Failed to initialize DHT");
    lcd.setCursor(0, 1);
    lcd.print("DHT Failed");
    while (1)
      ;
  }
  Serial.println("DHT initialized");
}

void loop()
{

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Failed to read DHT22");
    lcd.setCursor(0, 0);
    lcd.print("DHT Failed");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Ax:");
    lcd.print(a.acceleration.x);
    lcd.setCursor(8, 0);
    lcd.print("Ay:");
    lcd.print(a.acceleration.y);

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print("C H:");
    lcd.print(humidity);
    lcd.print("%");
  }
  delay(1000);
}