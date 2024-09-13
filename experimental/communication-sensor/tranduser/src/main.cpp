#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// SENSOR CONFIGURATION
#define DHTPIN 5
#define DHTTYPE DHT22
#define RESET_PIN 4
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MPU6050 mpu;

// LCD CONFIGURATION
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C 0x27, 16 kolom x 2 baris

// SET VARIABLE SENSOR
float humidity, temperature;
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;

String kirim = "";

void setup()
{
  Serial.begin(9600);
  Serial3.begin(115200); // Baudrate Serial ESP8266

  dht.begin();

  // LCD Initialization
  lcd.begin(16, 2); // Inisialisasi LCD
  lcd.backlight();  // Aktifkan lampu latar LCD
  lcd.clear();      // Bersihkan tampilan LCD

  // Konfigurasi pin reset sebagai input pull-up
  pinMode(RESET_PIN, INPUT_PULLUP);

  // Looping mpu6050 update
  if (!mpu.begin())
  {
    Serial.println("Failed to init MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }

  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  delay(100);
}

void loop()
{
  if (digitalRead(RESET_PIN) == LOW)
  {
    // Reset 0 IMU value parameter
    accelX = 0;
    accelY = 0;
    accelZ = 0;
    gyroX = 0;
    gyroY = 0;
    gyroZ = 0;

    Serial.println("IMU values reset!");
    delay(1000); // Delay stabilizer 
  }

  // DHT read
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Print DHT data to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(", Temperature: ");
  Serial.println(temperature);

  // MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  accelX = a.acceleration.x;
  accelY = a.acceleration.y;
  accelZ = a.acceleration.z;
  gyroX = g.gyro.x;
  gyroY = g.gyro.y;
  gyroZ = g.gyro.z;

  // Print MPU6050 data 
  Serial.print("Accel X: ");
  Serial.print(accelX, 2);
  Serial.print(", Y: ");
  Serial.print(accelY, 2);
  Serial.print(", Z: ");
  Serial.println(accelZ, 2);

  Serial.print("Gyro X: ");
  Serial.print(gyroX, 2);
  Serial.print(", Y: ");
  Serial.print(gyroY, 2);
  Serial.print(", Z: ");
  Serial.println(gyroZ, 2);

  // LCD DISPLAY
  lcd.setCursor(0, 0); // Set cursor
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C H:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Acc X:");
  lcd.print(accelX, 1);
  lcd.print(" Y:");
  lcd.print(accelY, 1);
  lcd.print(" Z:");
  lcd.print(accelZ, 1);

  // Serial3 Send
  kirim = "";
  kirim += humidity;
  kirim += ";";
  kirim += temperature;
  kirim += ";";
  kirim += accelX;
  kirim += ";";
  kirim += accelY;
  kirim += ";";
  kirim += accelZ;
  kirim += ";";
  kirim += gyroX;
  kirim += ";";
  kirim += gyroY;
  kirim += ";";
  kirim += gyroZ;

  Serial3.println(kirim);

  if (Serial3.available())
  {
    String msg = "";
    while (Serial3.available())
    {
      msg += char(Serial3.read());
      delay(50);
    }
    Serial.println(msg);
  }

  delay(500); // TRANSMIT DELAY
}
