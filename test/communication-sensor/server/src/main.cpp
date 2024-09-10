#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_BusIO_Register.h>

// Pengaturan WiFi
const char *ssid = "DTEO-VOKASI";   // Ganti dengan SSID WiFi Anda
const char *password = "TEO123456"; // Ganti dengan Password WiFi Anda

const char *server_url = "http://10.17.39.211/server_data.php"; // Endpoint PHP yang benar

WiFiClient client; // Membuat objek WiFiClient

void setup()
{
    Serial.begin(9600); // Serial ESP8266 untuk menerima data dari Arduino Mega
    Serial.println("ESP8266 siap menerima data");

    // Menghubungkan ke WiFi
    WiFi.begin(ssid, password);
    Serial.print("Menghubungkan ke WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi terhubung");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Fungsi untuk parsing suhu dari string data
float parseTemperature(String data)
{
    int tempIndex = data.indexOf("Temp: ") + 6;
    int tempEnd = data.indexOf(" C", tempIndex);
    if (tempIndex >= 6 && tempEnd > tempIndex) // Validasi indeks
    {
        return data.substring(tempIndex, tempEnd).toFloat();
    }
    return NAN; // Mengembalikan NaN jika parsing gagal
}

// Fungsi untuk parsing kelembaban dari string data
float parseHumidity(String data)
{
    int humIndex = data.indexOf("Humidity: ") + 10;
    int humEnd = data.indexOf(" %", humIndex);
    if (humIndex >= 10 && humEnd > humIndex) // Validasi indeks
    {
        return data.substring(humIndex, humEnd).toFloat();
    }
    return NAN; // Mengembalikan NaN jika parsing gagal
}

void loop()
{
    if (Serial.available())
    {
        String data = Serial.readStringUntil('\n'); // Baca data yang dikirimkan dari Arduino Mega
        Serial.print("Data dari Arduino Mega: ");
        Serial.println(data); // Tampilkan data di Serial Monitor ESP8266

        // Contoh format data: "Temp: 25.6 C, Humidity: 60.5%"
        // Pastikan data sesuai format ini, jika tidak, parsing akan gagal.

        if (data.startsWith("Temp: ") && data.indexOf("Humidity: ") != -1) // Validasi format data
        {
            float temperature = parseTemperature(data); // Memanggil fungsi parsing
            float humidity = parseHumidity(data);       // Memanggil fungsi parsing

            // Mengirim data ke server menggunakan HTTP POST jika nilai valid
            if (!isnan(temperature) && !isnan(humidity) && WiFi.status() == WL_CONNECTED)
            {
                HTTPClient http;

                // Membuka koneksi ke server dengan WiFiClient
                http.begin(client, server_url); // Menggunakan URL PHP

                // Menyiapkan HTTP POST
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                String httpRequestData = "suhu=" + String(temperature, 1) + "&kelembaban=" + String(humidity, 1); // Mengirim dengan format presisi yang benar

                // Mengirim data ke server
                int httpResponseCode = http.POST(httpRequestData);

                // Mengecek respon dari server
                if (httpResponseCode > 0)
                {
                    String response = http.getString();
                    Serial.print("Response dari server: ");
                    Serial.println(response);
                }
                else
                {
                    Serial.print("Error pada pengiriman: ");
                    Serial.println(httpResponseCode);
                }

                // Menutup koneksi
                http.end();
            }
            else
            {
                Serial.println("Error: Nilai suhu atau kelembaban tidak valid.");
            }
        }
        else
        {
            Serial.println("Error: Format data tidak sesuai.");
        }

        delay(5000); // Tunggu 5 detik sebelum loop berikutnya
    }
}

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
// WiFiClient client;  // Deklarasi client TCP

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