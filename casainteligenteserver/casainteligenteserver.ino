#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "LucioMob";
const char* password = "Senh@Lucio";

const char* serverAddress = "awsserverurl";
const int serverPort = portserve;

const int ledPin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String("http://") + serverAddress + ":" + serverPort + "/acender"; // Ajuste o endpoint conforme necessário
    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Resposta do servidor:");
      Serial.println(payload);

      if (payload.indexOf("acender") != -1) {
        digitalWrite(ledPin, HIGH);
      } else if (payload.indexOf("apagar") != -1) {
        digitalWrite(ledPin, LOW);
      }
    } else {
      Serial.println("Falha na conexão com o servidor");
    }

    http.end();
  }
  delay(10000);
}
