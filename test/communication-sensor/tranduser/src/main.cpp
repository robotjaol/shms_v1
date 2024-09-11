#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// SENSOR CONFIGURATION
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MPU6050 mpu;

// SET VARIABLE SENSOR
float humidity, temperature;
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;

String kirim = "";

void setup(){
  Serial.begin(9600);
  Serial3.begin(115200);  // Baudrate Serial ESP8266
  
  dht.begin();
  
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  
  delay(100);
}

void loop(){
  // DHT read
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // DHT
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
  
  // LCD DISPLAY
  Serial.print("Accel X: "); Serial.print(accelX); 
  Serial.print(", Y: "); Serial.print(accelY); 
  Serial.print(", Z: "); Serial.println(accelZ);
  Serial.print("Gyro X: "); Serial.print(gyroX); 
  Serial.print(", Y: "); Serial.print(gyroY); 
  Serial.print(", Z: "); Serial.println(gyroZ);
  
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

  if(Serial3.available()){
    String msg = "";
    while(Serial3.available()){
      msg += char(Serial3.read());
      delay(50);
    }
    Serial.println(msg);
  }

  delay(500);  // TRANSMIT DELAY
}
