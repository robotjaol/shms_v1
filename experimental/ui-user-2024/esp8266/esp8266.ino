#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>

const char *ssid = "DTEO-VOKASI";   // SSD WIFI SET
const char *password = "TEO123456"; // PASSWORD WIFI

float humidity, temperature;
float accelX, accelY, accelZ;
float gyroX, gyroY, gyroZ;

void connectToWifi()
{
    WiFi.mode(WIFI_OFF); // Prevents reconnection issue
    delay(1000);
    WiFi.mode(WIFI_STA); // Connect ESP as station

    WiFi.begin(ssid, password); // Connect to WiFi
    Serial.println("");

    Serial.print("Connecting");
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) // Timeout 10 detik jika tidak connect wifi
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        // Serial.println("Connect To Wifi function Done");
    }
    else
    {
        Serial.println("Failed to connect to WiFi");
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Setup Function START");
    connectToWifi();
}

void kirimDataKeServer()
{
    // Serial.println("Kirim Data Ke Server START");
    WiFiClient client; // Declare WiFiClient
    HTTPClient http;   // Declare objek HTTPClient
    String postData;

    postData = "humidity=";
    postData += humidity;
    postData += "&temperature=";
    postData += temperature;
    postData += "&accelX=";
    postData += accelX;
    postData += "&accelY=";
    postData += accelY;
    postData += "&accelZ=";
    postData += accelZ;
    postData += "&gyroX=";
    postData += gyroX;
    postData += "&gyroY=";
    postData += gyroY;
    postData += "&gyroZ=";
    postData += gyroZ;

    // CUSTOM IP dan path server
    http.begin(client, "http://10.17.39.211/shms/get_data.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Req Server
    int httpCode = http.POST(postData); // req by post mas
    String payload = http.getString();  // get respon server

    // Cek Respon server
    Serial.println(httpCode); //  HTTP return code
    Serial.println(payload);  //  request response payload
    http.end();
}

String splitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop()
{
    if (Serial.available())
    {
        Serial.println("Data received");
        String msg = "";
        while (Serial.available())
        {
            char receivedChar = char(Serial.read());
            msg += receivedChar;

            // Debugging last data update
            if (receivedChar == '\n')
            {
                break;
            }
            delay(10); // buffer delay
        }

        // Cetak ulang data
        // Serial.println("Data from ATmega:");
        Serial.println(msg);

        // Konversi data
        humidity = splitString(msg, ';', 0).toFloat();
        temperature = splitString(msg, ';', 1).toFloat();
        accelX = splitString(msg, ';', 2).toFloat();
        accelY = splitString(msg, ';', 3).toFloat();
        accelZ = splitString(msg, ';', 4).toFloat();
        gyroX = splitString(msg, ';', 5).toFloat();
        gyroY = splitString(msg, ';', 6).toFloat();
        gyroZ = splitString(msg, ';', 7).toFloat();

        // Kirim data ke server
        kirimDataKeServer();
        delay(500); // delay 500 ms sebelum pengiriman data
    }
}
