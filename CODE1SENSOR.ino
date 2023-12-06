#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial sim800l(9, 10);  // tx rx

#define DHTPIN 4             
#define FLAME_PIN 2          
#define GAS_PIN 3            

DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Arduino with GSM Module Ready");

  sim800l.begin(9600);
  Serial.println("Komunikasi Ready");

  pinMode(FLAME_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  dht.begin();
}

void loop() {
  int flameValue = digitalRead(FLAME_PIN);
  int gasValue = digitalRead(GAS_PIN);
  float temperature = dht.readTemperature();

  if (flameValue == LOW) {
    Serial.println("Deteksi api! Mengirim pesan SMS...");
    sendSMS("sirla#Lahan 5#-4.218266#122.542294#Deteksi Api");
    delay(5000);  
  }

  if (gasValue == HIGH) {
    Serial.println("Deteksi gas berbahaya! Mengirim pesan SMS..."); 
    sendSMS("sirla#Lahan 5#-4.218266#122.542294#Deteksi Gas");
    delay(5000);  
  }

  if (temperature > 50.0) {  
    Serial.println("Suhu tinggi! Mengirim pesan SMS...");
    sendSMS("Suhu tinggi: " + String(temperature) + "°C");
    delay(5000);  
  }

  delay(1000);  
}

void sendSMS(String message) {
  sim800l.println("AT+CMGF=1");  // Set mode SMS
  delay(1000);
  sim800l.println("AT+CMGS=\"+6282310880310\"");  // Ganti nomor dengan nomor tujuan Anda
  delay(1000);
  sim800l.print(message);
  delay(100);
  sim800l.write(26);  // Karakter EOF (End of File) untuk mengirim SMS
  delay(1000);
  Serial.println("SMS Selesai dikirim");
}


