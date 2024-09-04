// ================== PLOTTER 1 ==================

#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "DTEO-VOKASI";
const char* password = "TEO123456";
const char* server_ip = "10.17.38.137";
const uint16_t server_port = 5000;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Menghubungkan ke WiFi");
    Serial.print(" (Percobaan ");
    Serial.print(++attempt);
    Serial.println(")");
    
    if (attempt > 20) { 
      Serial.println("Gagal terhubung ke WiFi. Periksa kredensial atau jaringan.");
      return;  
    }
  }

  Serial.println("Terhubung ke WiFi!");
  Serial.print("IP Address ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    static unsigned long lastSendTime = 0;
    unsigned long currentTime = millis();
    
    if (currentTime - lastSendTime >= 1000) {
      lastSendTime = currentTime;
      
      // dummy data
      float x = currentTime / 1000.0;
      float y = sin(x);

      // Format data dalam CSV
      String data = String(x, 2) + "," + String(y, 2);

      udp.beginPacket(server_ip, server_port);
      udp.print(data);
      udp.endPacket();
      
      Serial.print("Mengirim data: ");
      Serial.println(data);
    }
  } else {
    Serial.println("WiFi Pedot. Mencoba menghubungkan kembali...");
    WiFi.reconnect();
  }

  delay(10); // CPU HEALER
}

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


