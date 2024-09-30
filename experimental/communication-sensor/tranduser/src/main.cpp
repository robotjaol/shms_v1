#include <DHT.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//--------DHT----------//
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature;
String kirim = "";

//--------MPU6050-----------//
Adafruit_MPU6050 mpu;
const int resetPin = 4; // reset x, y, dan z

const int EEPROM_OFFSET_X = 0;
const int EEPROM_OFFSET_Y = 4;
const int EEPROM_OFFSET_Z = 8;

float offsetX = 0;
float offsetY = 0;
float offsetZ = 0;

// Set the I2C address for your specific LCD module
int lcdAddress = 0x27; // Adjust to your LCD
LiquidCrystal_I2C lcd(lcdAddress, 16, 2);

//----Battery
// Baterai
const int adcPin = A0; // Pin ADC untuk mengukur tegangan baterai
float batteryVoltage = 0.0;
int batteryPercentage = 0;

void setup()
{
  Serial.begin(9600);
  Serial3.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();

  while (!Serial)
    delay(10);

  Serial.println("MPU6050 test!");
  pinMode(resetPin, INPUT);
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");

  EEPROM.get(EEPROM_OFFSET_X, offsetX);
  EEPROM.get(EEPROM_OFFSET_Y, offsetY);
  EEPROM.get(EEPROM_OFFSET_Z, offsetZ);

  Serial.print("Saved offset X: ");
  Serial.println(offsetX);
  Serial.print("Saved offset Y: ");
  Serial.println(offsetY);
  Serial.print("Saved offset Z: ");
  Serial.println(offsetZ);

  delay(2500);
}

void loop()
{
  static bool isReset = false;
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  if (digitalRead(resetPin) == HIGH)
  {
    isReset = true;

    // Set offsets to zero
    offsetX = -a.acceleration.x;
    offsetY = -a.acceleration.y;
    offsetZ = -a.acceleration.z;

    // Save offsets to EEPROM
    EEPROM.put(EEPROM_OFFSET_X, offsetX);
    EEPROM.put(EEPROM_OFFSET_Y, offsetY);
    EEPROM.put(EEPROM_OFFSET_Z, offsetZ);
  }

  // Offset Correction
  float correctedX = a.acceleration.x + offsetX;
  float correctedY = a.acceleration.y + offsetY;
  float correctedZ = a.acceleration.z + offsetZ;

  Serial.print("Acceleration X: ");
  Serial.print(correctedX);
  Serial.print(", Y: ");
  Serial.print(correctedY);
  Serial.print(", Z: ");
  Serial.print(correctedZ);
  Serial.println(" m/s^2");

  if (correctedZ > 2 || correctedZ < -1 || correctedY > 2 || correctedY < -1 || correctedX > 2 || correctedX < -1)
  {
    Serial.print("Miring");
  }
  else
  {
    Serial.println("Baik");
  }
  Serial.println("");

  Serial.print("kelembaban: ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(temperature);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kelembaban: ");
  lcd.setCursor(11, 0);
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.setCursor(5, 1);
  lcd.print(temperature);
  delay(2500);

  int adcValue = analogRead(adcPin);
  batteryVoltage = (adcValue / 4095.0) * 8.4; // 8.4V

  // Menghitung persentase baterai (1 - 100%)
  batteryPercentage = map(batteryVoltage * 100, 6.4 * 100, 8.4 * 100, 0, 100); // Persentase baterai
  if (batteryPercentage < 0)
    batteryPercentage = 0; // Batasi nilai minimum 0%
  if (batteryPercentage > 100)
    batteryPercentage = 100; // Batasi nilai maksimum 100%

  lcd.setCursor(0, 1);
  lcd.print("Bat: ");
  lcd.setCursor(5, 1);
  lcd.print(batteryPercentage);
  lcd.print("%");

  lcd.clear();
  if (correctedZ > 2 || correctedZ < -1 || correctedY > 2 || correctedY < -1 || correctedX > 2 || correctedX < -1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Kemiringan: ");
    lcd.setCursor(0, 1);
    lcd.print("Baik");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Kemiringan: ");
    lcd.setCursor(0, 1);
    lcd.print("Baik");
  }
  Serial.println("");

  kirim = "";
  kirim += humidity;
  kirim += ";";
  kirim += temperature;
  kirim += ";";
  kirim += correctedX;
  kirim += ";";
  kirim += correctedY;
  kirim += ";";
  kirim += correctedZ;

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
  delay(2500);
}

// #include <Arduino.h>
// #include <Adafruit_MPU6050.h>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <DHT.h>
// #include <LiquidCrystal_I2C.h>

// // SENSOR CONFIGURATION
// #define DHTPIN 5
// #define DHTTYPE DHT22
// #define RESET_PIN 4
// DHT dht(DHTPIN, DHTTYPE);
// Adafruit_MPU6050 mpu;

// // LCD CONFIGURATION
// LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C 0x27, 16 kolom x 2 baris

// // SET VARIABLE SENSOR
// float humidity, temperature;
// float accelX, accelY, accelZ;
// float gyroX, gyroY, gyroZ;

// String kirim = "";

// void setup()
// {
//   Serial.begin(9600);
//   Serial3.begin(115200); // Baudrate Serial ESP8266

//   dht.begin();

//   // LCD Initialization
//   lcd.begin(16, 2); // Inisialisasi LCD
//   lcd.backlight();  // Aktifkan lampu latar LCD
//   lcd.clear();      // Bersihkan tampilan LCD

//   // Konfigurasi pin reset sebagai input pull-up
//   pinMode(RESET_PIN, INPUT_PULLUP);

//   // Looping mpu6050 update
//   if (!mpu.begin())
//   {
//     Serial.println("Failed to init MPU6050 chip");
//     while (1)
//     {
//       delay(10);
//     }
//   }

//   Serial.println("MPU6050 Found!");
//   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
//   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
//   mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

//   delay(100);
// }

// void loop()
// {
//   if (digitalRead(RESET_PIN) == LOW)
//   {
//     // Reset 0 IMU value parameter
//     accelX = 0;
//     accelY = 0;
//     accelZ = 0;
//     gyroX = 0;
//     gyroY = 0;
//     gyroZ = 0;

//     Serial.println("IMU values reset!");
//     delay(1000); // Delay stabilizer
//   }

//   // DHT read
//   humidity    = dht.readHumidity();
//   temperature = dht.readTemperature();

//   // Print DHT data to Serial Monitor
//   Serial.print("Humidity: ");
//   Serial.print(humidity);
//   Serial.print(", Temperature: ");
//   Serial.println(temperature);

//   // MPU6050
//   sensors_event_t a, g, temp;
//   mpu.getEvent(&a, &g, &temp);

//   accelX = a.acceleration.x;
//   accelY = a.acceleration.y;
//   accelZ = a.acceleration.z;
//   gyroX = g.gyro.x;
//   gyroY = g.gyro.y;
//   gyroZ = g.gyro.z;

//   // Print MPU6050 data
//   Serial.print("Accel X: ");
//   Serial.print(accelX, 2);
//   Serial.print(", Y: ");
//   Serial.print(accelY, 2);
//   Serial.print(", Z: ");
//   Serial.println(accelZ, 2);

//   Serial.print("Gyro X: ");
//   Serial.print(gyroX, 2);
//   Serial.print(", Y: ");
//   Serial.print(gyroY, 2);
//   Serial.print(", Z: ");
//   Serial.println(gyroZ, 2);

//   // LCD DISPLAY
//   lcd.setCursor(0, 0); // Set cursor
//   lcd.print("T:");
//   lcd.print(temperature);
//   lcd.print("C H:");
//   lcd.print(humidity);
//   lcd.print("%");

//   lcd.setCursor(0, 1);
//   lcd.print("Acc X:");
//   lcd.print(accelX, 1);
//   lcd.print(" Y:");
//   lcd.print(accelY, 1);
//   lcd.print(" Z:");
//   lcd.print(accelZ, 1);

//   // Serial3 Send
//   kirim = "";
//   kirim += humidity;
//   kirim += ";";
//   kirim += temperature;
//   kirim += ";";
//   kirim += accelX;
//   kirim += ";";
//   kirim += accelY;
//   kirim += ";";
//   kirim += accelZ;
//   kirim += ";";
//   kirim += gyroX;
//   kirim += ";";
//   kirim += gyroY;
//   kirim += ";";
//   kirim += gyroZ;

//   Serial3.println(kirim);

//   if (Serial3.available())
//   {
//     String msg = "";
//     while (Serial3.available())
//     {
//       msg += char(Serial3.read());
//       delay(50);
//     }
//     Serial.println(msg);
//   }

//   delay(500); // TRANSMIT DELAY
// }
