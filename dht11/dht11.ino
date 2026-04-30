#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ====== WIFI ======
#define WIFI_SSID "Digite a senha:"
#define WIFI_PASS "password"

// ====== DHT11 ======
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ====== URL DA API (Render) ======
String serverName = "https://api-sensor.onrender.com/sensor";

// ====== CONTROLE ======
float ultimaTemp    = -1000;
float ultimaUmidade = -1000;

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  Serial.print("Conectando ao WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi desconectado!");
    delay(2000);
    return;
  }

  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if(isnan(temp) || isnan(hum)){
    Serial.println("Erro ao ler DHT11");
    delay(2000);
    return;
  } 

  //evita envio repetido
  if (abs(temp - ultimaTemp) < 0.2 && abs(hum - ultimaUmidade) < 1.0){
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" | Umidade: ");
  Serial.print(hum);

  HTTPClient htpp;

  // monta URL com parametros
  String url = serverName + "?temp=" + String(temp) + "&hum=" + String(hum);

  Serial.print("Enviando para: ");
  Serial.println(url);

  http.begin(url);

  int httpResponseCode = http.GET();

  Serial.print("Resposta HTTP: ");
  Serial.print(httpResponseCode);

  http.end();

  ultimaTemp = temp;
  ultimaUmidade  = hum;

  delay(5000);
}
