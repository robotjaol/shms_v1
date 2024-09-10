#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// Pin connected
#define DHTPIN 5
#define BUTTON_PIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float tempOffset = 2.0;
float humOffset = -3.0;

float accelOffsetX = 0;
float accelOffsetY = 0;
float accelOffsetZ = 0;
float gyroOffsetX = 0;
float gyroOffsetY = 0;
float gyroOffsetZ = 0;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600); // Komunikasi Serial ke ESP8266
  Serial.println("MPU6050 & DHT22 OLED + LCD demo");

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!mpu.begin())
  {
    Serial.println("MPU6050 init failed");
    while (1)
      yield();
  }
  Serial.println("MPU6050 found");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    while (1)
      ;
  }
  display.display();
  delay(500);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setRotation(0);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void resetMPUOffsets()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  accelOffsetX = a.acceleration.x;
  accelOffsetY = a.acceleration.y;
  accelOffsetZ = a.acceleration.z;

  gyroOffsetX = g.gyro.x;
  gyroOffsetY = g.gyro.y;
  gyroOffsetZ = g.gyro.z;

  Serial.println("MPU6050 offsets reset!");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Offset telah");
  lcd.setCursor(0, 1);
  lcd.print("di-reset!");

  delay(1500);
}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mengatur ulang");
    lcd.setCursor(0, 1);
    lcd.print("posisi...");
    delay(2000);
    resetMPUOffsets();
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float accelX = a.acceleration.x - accelOffsetX;
  float accelY = a.acceleration.y - accelOffsetY;
  float accelZ = a.acceleration.z - accelOffsetZ;

  float gyroX = g.gyro.x - gyroOffsetX;
  float gyroY = g.gyro.y - gyroOffsetY;
  float gyroZ = g.gyro.z - gyroOffsetZ;

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  temperature += tempOffset;
  humidity += humOffset;

  // Tampilkan di Serial Mega
  Serial.println("MPU6050:");
  Serial.print("Acc X: ");
  Serial.print(accelX, 1);
  Serial.print(" Y: ");
  Serial.print(accelY, 1);
  Serial.print(" Z: ");
  Serial.println(accelZ, 1);
  Serial.print("Gyro X: ");
  Serial.print(gyroX, 1);
  Serial.print(" Y: ");
  Serial.print(gyroY, 1);
  Serial.print(" Z: ");
  Serial.println(gyroZ, 1);
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.println(humidity);

  // Kirim data ke ESP8266
  Serial1.print("Temp: ");
  Serial1.print(temperature);
  Serial1.print(" C, Humidity: ");
  Serial1.println(humidity);
  Serial1.print("Acc X: ");
  Serial1.print(accelX, 1);
  Serial1.print(" Y: ");
  Serial1.print(accelY, 1);
  Serial1.print(" Z: ");
  Serial1.println(accelZ, 1);
  Serial1.print("Gyro X: ");
  Serial1.print(gyroX, 1);
  Serial1.print(" Y: ");
  Serial1.print(gyroY, 1);
  Serial1.print(" Z: ");
  Serial1.println(gyroZ, 1);

  // Tampilkan di OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Acc (m/s^2)");
  display.print(accelX, 1);
  display.print(",");
  display.print(accelY, 1);
  display.print(",");
  display.print(accelZ, 1);
  display.println("");
  display.println("Gyro (rps)");
  display.print(gyroX, 1);
  display.print(",");
  display.print(gyroY, 1);
  display.print(",");
  display.print(gyroZ, 1);
  display.println("");
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C  Humidity: ");
  display.println(humidity);
  display.display();

  // Tampilkan di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("G X:");
  lcd.print(gyroX, 1);
  lcd.setCursor(8, 0);
  lcd.print("Y:");
  lcd.print(gyroY, 1);
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 1);

  delay(750);
}
