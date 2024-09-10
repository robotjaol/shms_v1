#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Pengaturan WiFi
const char* ssid = "DTEO-VOKASI";          // Ganti dengan SSID WiFi Anda
const char* password = "TEO123456";        // Ganti dengan Password WiFi Anda

const char* server_ip = "http://10.17.39.211/server_data.php";  // Endpoint PHP yang benar

WiFiClient client;  // Membuat objek WiFiClient

void setup() {
  Serial.begin(9600);  // Serial ESP8266 untuk menerima data dari Arduino Mega
  Serial.println("ESP8266 siap menerima data");

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi terhubung");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // Baca data yang dikirimkan dari Arduino Mega
    Serial.print("Data dari Arduino Mega: ");
    Serial.println(data);  // Tampilkan data di Serial Monitor ESP8266     

    // Contoh format data: "Temp: 25.6 C, Humidity: 60.5"
    // Parsing data suhu dan kelembaban dari string
    float temperature = parseTemperature(data);
    float humidity = parseHumidity(data);

    // Mengirim data ke server menggunakan HTTP POST
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Membuka koneksi ke server dengan WiFiClient
      http.begin(client, server_ip);  // Menggunakan URL PHP

      // Menyiapkan HTTP POST
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "suhu=" + String(temperature) + "&kelembaban=" + String(humidity);

      // Mengirim data ke server
      int httpResponseCode = http.POST(httpRequestData);

      // Mengecek respon dari server
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("Response dari server: ");
        Serial.println(response);
      } else {
        Serial.print("Error pada pengiriman: ");
        Serial.println(httpResponseCode);
      }

      // Menutup koneksi
      http.end();
    }

    delay(5000);  // Tunggu 5 detik sebelum loop berikutnya
  }
}

// Fungsi untuk parsing suhu dari string data
float parseTemperature(String data) {
  int tempIndex = data.indexOf("Temp: ") + 6;
  int tempEnd = data.indexOf(" C", tempIndex);
  return data.substring(tempIndex, tempEnd).toFloat();
}

// Fungsi untuk parsing kelembaban dari string data
float parseHumidity(String data) {
  int humIndex = data.indexOf("Humidity: ") + 10;
  return data.substring(humIndex).toFloat();
}
