#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>

// const char *ssid = "UncleMutho";  
// const char *password = "12345678";

const char *ssid = "DTEO-VOKASI";  
const char *password = "TEO123456";

float humidity, temperature, x, y, z;


void kirimDataKeServer();
void connectToWifi();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  connectToWifi();
}

void connectToWifi(){
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

String splitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String msg = "";
    while(Serial.available()){
      msg += char(Serial.read());
      delay(50);
    }

    humidity = splitString(msg, ';', 0).toFloat();
    temperature = splitString(msg, ';', 1).toFloat();
    x = splitString(msg, ';', 2).toFloat();
    y = splitString(msg, ';', 3).toFloat();
    z = splitString(msg, ';', 4).toFloat();
    kirimDataKeServer();
//    Serial.print(msg);
  }
}

void kirimDataKeServer(){
  HTTPClient http;    //Declare object of class HTTPClient
  WiFiClient client;
  String postData;
  //Post Data
  postData = "humidity=";
  postData += humidity;
  postData += "&temperature=";
  postData += temperature;
  postData += "&x=";
  postData += x;
  postData += "&y=";
  postData += y;
  postData += "&z=";
  postData += z;

  http.begin(client, "http://10.17.36.151/WebsiteMonitoring/shmsjiwakkk/sensor.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
      
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
      
  
}

// #include <ESP8266WiFi.h>
// #include <ESP8266HTTPClient.h>
// #include <WiFiClient.h>
// #include <Wire.h>
// #include <Adafruit_BusIO_Register.h>

// const char *ssid = "DTEO-VOKASI";   // SSD WIFI SET
// const char *password = "TEO123456"; // PASSWORD WIFI

// float humidity, temperature;
// float accelX, accelY, accelZ;
// float gyroX, gyroY, gyroZ;

// void connectToWifi()
// {
//     WiFi.mode(WIFI_OFF); // Prevents reconnection issue
//     delay(1000);
//     WiFi.mode(WIFI_STA); // Connect ESP as station

//     WiFi.begin(ssid, password); // Connect to WiFi
//     Serial.println("");

//     Serial.print("Connecting");
//     unsigned long startTime = millis();
//     while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) // Timeout 10 detik jika tidak connect wifi
//     {
//         delay(500);
//         Serial.print(".");
//     }

//     if (WiFi.status() == WL_CONNECTED)
//     {
//         Serial.println("");
//         Serial.print("Connected to ");
//         Serial.println(ssid);
//         Serial.print("IP address: ");
//         Serial.println(WiFi.localIP());
//         // Serial.println("Connect To Wifi function Done");
//     }
//     else
//     {
//         Serial.println("Failed to connect to WiFi");
//     }
// }

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("Setup Function START");
//     connectToWifi();
// }

// void kirimDataKeServer()
// {
//     // Serial.println("Kirim Data Ke Server START");
//     WiFiClient client; // Declare WiFiClient
//     HTTPClient http;   // Declare objek HTTPClient
//     String postData;

//     postData = "humidity=";
//     postData += humidity;
//     postData += "&temperature=";
//     postData += temperature;
//     postData += "&accelX=";
//     postData += accelX;
//     postData += "&accelY=";
//     postData += accelY;
//     postData += "&accelZ=";
//     postData += accelZ;
//     postData += "&gyroX=";
//     postData += gyroX;
//     postData += "&gyroY=";
//     postData += gyroY;
//     postData += "&gyroZ=";
//     postData += gyroZ;

//     // CUSTOM IP dan path server
//     http.begin(client, "http://10.17.39.211/structural-server/server.php");
//     http.addHeader("Content-Type", "application/x-www-form-urlencoded");

//     // Req Server
//     int httpCode = http.POST(postData); // req by post mas
//     String payload = http.getString();  // get respon server

//     // Cek Respon server
//     Serial.println(httpCode); //  HTTP return code
//     Serial.println(payload);  //  request response payload
//     http.end();
// }

// String splitString(String data, char separator, int index)
// {
//     int found = 0;
//     int strIndex[] = {0, -1};
//     int maxIndex = data.length() - 1;

//     for (int i = 0; i <= maxIndex && found <= index; i++)
//     {
//         if (data.charAt(i) == separator || i == maxIndex)
//         {
//             found++;
//             strIndex[0] = strIndex[1] + 1;
//             strIndex[1] = (i == maxIndex) ? i + 1 : i;
//         }
//     }
//     return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
// }

// void loop()
// {
//     if (Serial.available())
//     {
//         Serial.println("Data received");
//         String msg = "";
//         while (Serial.available())
//         {
//             char receivedChar = char(Serial.read());
//             msg += receivedChar;

//             // Debugging last data update
//             if (receivedChar == '\n')
//             {
//                 break;
//             }
//             delay(10); // buffer delay
//         }

//         // Cetak ulang data
//         // Serial.println("Data from ATmega:");
//         Serial.println(msg);

//         // Konversi data
//         humidity = splitString(msg, ';', 0).toFloat();
//         temperature = splitString(msg, ';', 1).toFloat();
//         accelX = splitString(msg, ';', 2).toFloat();
//         accelY = splitString(msg, ';', 3).toFloat();
//         accelZ = splitString(msg, ';', 4).toFloat();
//         gyroX = splitString(msg, ';', 5).toFloat();
//         gyroY = splitString(msg, ';', 6).toFloat();
//         gyroZ = splitString(msg, ';', 7).toFloat();

//         // Kirim data ke server
//         kirimDataKeServer();
//         delay(500); // delay 500 ms sebelum pengiriman data
//     }
// }

// // ================== PLOTTER 1 ==================

// #include <WiFi.h>
// #include <WiFiUdp.h>

// const char* ssid = "DTEO-VOKASI";
// const char* password = "TEO123456";
// const char* server_ip = "10.17.38.137";
// const uint16_t server_port = 5000;

// WiFiUDP udp;

// void setup() {
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);

//   int attempt = 0;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print("Menghubungkan ke WiFi");
//     Serial.print(" (Percobaan ");
//     Serial.print(++attempt);
//     Serial.println(")");

//     if (attempt > 20) {
//       Serial.println("Gagal terhubung ke WiFi. Periksa kredensial atau jaringan.");
//       return;
//     }
//   }

//   Serial.println("Terhubung ke WiFi!");
//   Serial.print("IP Address ESP32: ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     static unsigned long lastSendTime = 0;
//     unsigned long currentTime = millis();

//     if (currentTime - lastSendTime >= 1000) {
//       lastSendTime = currentTime;

//       // dummy data
//       float x = currentTime / 1000.0;
//       float y = sin(x);

//       // Format data dalam CSV
//       String data = String(x, 2) + "," + String(y, 2);

//       udp.beginPacket(server_ip, server_port);
//       udp.print(data);
//       udp.endPacket();

//       Serial.print("Mengirim data: ");
//       Serial.println(data);
//     }
//   } else {
//     Serial.println("WiFi Pedot. Mencoba menghubungkan kembali...");
//     WiFi.reconnect();
//   }

//   delay(10); // CPU HEALER
// }

// ======================= READY GUYS ===================

// #include <WiFi.h>
// #include <WiFiUdp.h>

// const char* ssid = "DTEO-VOKASI";
// const char* password = "TEO123456";
// const char* server_ip = "10.17.38.137";
// const uint16_t server_port = 5000;

// WiFiUDP udp;

// void setup() {
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);

//   int attempt = 0;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print("Menghubungkan ke WiFi");
//     Serial.print(" (Percobaan ");
//     Serial.print(++attempt);
//     Serial.println(")");

//     if (attempt > 20) {
//       Serial.println("Gagal terhubung ke WiFi. Periksa kredensial atau jaringan.");
//       return;
//     }
//   }

//   Serial.println("Terhubung ke WiFi!");
//   Serial.print("IP Address ESP32: ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     udp.beginPacket(server_ip, server_port);
//     udp.print("Jonathan Ganteng!");
//     udp.endPacket();
//     Serial.println("Mengirim data: Jonathan Ganteng!");
//   } else {
//     Serial.println("WiFi terputus. Mencoba menghubungkan kembali...");
//     WiFi.reconnect();
//   }

//   delay(1000);
// }

// ==============================================================
// #include <WiFi.h>
// #include <WiFiUdp.h>

// const char* ssid = "ITS-WIFI-NGELAG";  // SSID WiFi
// const char* password = "jonaits2022";  // Password WiFi
// const char* server_ip = "192.168.146.100";  // ip wifi laptop
// const uint16_t server_port = 5000;

// WiFiUDP udp;

// void setup() {
//   Serial.begin(115200);
//   WiFi.begin(ssid, password);

//   int attempt = 0;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print("Menghubungkan ke WiFi");
//     Serial.print(" (Percobaan ");
//     Serial.print(++attempt);
//     Serial.println(")");

//     if (attempt > 20) {
//       Serial.println("Gagal Terhubung");
//       return;
//     }
//   }

//   Serial.println("Terhubung ke WiFi!");
//   Serial.print("IP Address ESP32: ");
//   Serial.println(WiFi.localIP());
// }

// void loop() {
//   if (WiFi.status() == WL_CONNECTED) {
//     udp.beginPacket(server_ip, server_port);  // RUN UDP
//     udp.print("Hello from ESP32!");  //
//     udp.endPacket();

//     Serial.println("Send ; Jon");
//   } else {
//     Serial.println("WiFi pedot");
//     WiFi.reconnect();
//   }

//   delay(1000);  // Tunggu 1 detik sebelum mengirim data lagi
// }

// #include <WiFi.h>

// // const char* ssid = "ITS-WIFI-NGELAG";  // SSID WiFi
// // const char* password = "jonaits2022";  // Password WiFi
// // const char* server_ip = "192.168.146.100";  // IP Address laptop
// // const uint16_t server_port = 5000;  // Port server

// const char* ssid = "DTEO-VOKASI";  // SSID WiFi
// const char* password = "TEO123456";  // Password WiFi
// const char* server_ip = "10.17.38.137";  // IP Address laptop
// const uint16_t server_port = 5000;  // Port server
// WiFiClient client;  // Declare client TCP

// void setup() {
//   Serial.begin(115200);  // Inisialisasi komunikasi serial
//   WiFi.begin(ssid, password);  // Hubungkan ke WiFi

//   int attempt = 0;
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print("Menghubungkan ke WiFi");
//     Serial.print(" (Percobaan ");
//     Serial.print(++attempt);
//     Serial.println(")");

//     if (attempt > 20) {
//       Serial.println("Gagal terhubung ke WiFi. Periksa kredensial atau jaringan.");
//       return;
//     }
//   }

//   Serial.println("Terhubung ke WiFi!");
//   Serial.print("IP Address ESP32: ");
//   Serial.println(WiFi.localIP());  // Cetak IP address ESP32

//   // Coba koneksi ke server
//   if (client.connect(server_ip, server_port)) {
//     Serial.println("Terhubung ke server TCP!");
//   } else {
//     Serial.println("Gagal terhubung ke server.");
//   }
// }

// void loop() {
//   if (client.connected()) {  // Periksa apakah client masih terhubung ke server
//     client.println("Hello from ESP32!");  // Kirim pesan ke server
//     Serial.println("Mengirim data: Hello from ESP32!");  // Cetak pesan yang dikirim
//   } else {
//     Serial.println("Koneksi terputus. Mencoba menghubungkan kembali...");
//     if (client.connect(server_ip, server_port)) {
//       Serial.println("Kembali terhubung ke server TCP!");
//     }
//   }

//   delay(1000);  // Tunggu 1 detik sebelum mengirim data lagi
// }