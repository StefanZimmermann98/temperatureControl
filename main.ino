#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DHT.h>

//Pin Definitionen

  int d0 = 16;
  int d1 = 5;
  int d2 = 4;
  int d3 = 0;
  int d4 = 2;
  int d5 = 14;
  int d6 = 12;
  int d7 = 13;
  int d8 = 15;
  int d9 = 3;
  int d10 = 1;
  
ESP8266WebServer server(80);
DHT dht(d6,DHT22);

// Custom Definitionen

  String wifi_kennung = "";
  String wifi_passwort = "";
  int status_d4 = 0;



  
void setup() {
  Serial.begin(115200);
  dht.begin();
  Serial.println("ESP wurde gestartet");
  WiFi.begin(wifi_kennung,wifi_passwort);
  Serial.print("Verbindung wird hergestellt");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\n");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  if (MDNS.begin("test")) {
    Serial.println("DNS online");
  }

  server.onNotFound([] () {
    server.send(404, "text/plain","Link wurde nicht gefunden!");
  });

  server.on("/", []() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    if (isnan(temperature) || isnan(humidity)){
      server.send(200,"text/plain","error");
    } else {
      String s = "{'temperature':" + String(temperature) + ",'humidity':" + String(humidity) + "}";
      server.send(200,"text/plain",s);
    }
    
  });
  
  server.begin();

  
}



void loop() {
  delay(2000);
  float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    if (isnan(temperature) || isnan(humidity)){
      Serial.print("nö");
    } else {
      Serial.println(String(temperature));
    }
  server.handleClient();
}
