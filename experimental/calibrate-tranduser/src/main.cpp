#include <Wire.h>
#include <Arduino.h>
#include <HX711.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>

#define D7S_ADDRESS 0x55
#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 2

HX711 scale;
Adafruit_MPU6050 mpu;
Adafruit_ADXL345_Unified adxl = Adafruit_ADXL345_Unified();

float calibration_factor = -7050;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();

  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }

  if (!adxl.begin())
  {
    Serial.println("Failed to find ADXL345 chip");
    while (1)
    {
      delay(10);
    }
  }

  Serial.println("Connecting...");
  delay(1000);
}

float readAcceleration()
{
  int16_t xAccel = 0, yAccel = 0, zAccel = 0;

  Wire.beginTransmission(D7S_ADDRESS);
  Wire.write(0x20);
  Wire.endTransmission();
  Wire.requestFrom(D7S_ADDRESS, 6);

  if (Wire.available() == 6)
  {
    xAccel = Wire.read() | (Wire.read() << 8);
    yAccel = Wire.read() | (Wire.read() << 8);
    zAccel = Wire.read() | (Wire.read() << 8);
  }

  float x = xAccel * 0.001;
  float y = yAccel * 0.001;
  float z = zAccel * 0.001;

  return sqrt(x * x + y * y + z * z);
}

void printWeight()
{
  long weight = scale.get_units(10);
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");
}

void printMPU6050()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("MPU6050 Acceleration - X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" Z: ");
  Serial.println(a.acceleration.z);
}

void printADXL345()
{
  sensors_event_t event;
  adxl.getEvent(&event);

  Serial.print("ADXL345 Acceleration - X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" Z: ");
  Serial.println(event.acceleration.z);
}

void loop()
{
  float acceleration = readAcceleration();
  Serial.print("Earthquake: ");
  Serial.print(acceleration);
  Serial.print(" m/s², ");

  printWeight();
  printMPU6050();
  printADXL345();

  delay(200);
}
