
#include <WiFi.h>
#include <ESPmDNS.h>
#include "ESP32Ping.h"

const char* ssid = "Internet_UNL";
const char* password = "UNL1859WiFi";
// const char* ssid = "RED-ViVi";
// const char* password = "ladeantes";

unsigned long conection_time = 0;
unsigned long tiempo_transcurrido = 0;

// Defino las ips estáticas
IPAddress esp_ip(10, 20, 137, 164);
IPAddress gateway(10, 20, 136, 1);
IPAddress subnet_mask(255, 255, 252, 0);
// IPAddress esp_ip(172, 20, 10, 12);
// IPAddress gateway(172, 20, 10, 1);
// IPAddress subnet_mask(255, 255, 252, 240);
IPAddress dns(8, 8, 8, 8);

void setup() {
  Serial.begin(115200);

  if (!WiFi.config(esp_ip, gateway, subnet_mask, dns)) {
    Serial.println("No se han podido establecer las configuraciones estáticas");
    return;
  }

  WiFi.begin(ssid, password);

  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red WiFi!");

  if (!MDNS.begin("ESP32VIVI")) {
    Serial.println("No se ha podido establecer el mDNS!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("\nSe ha establecido el mDNS");

  // Imprimimos la información solicitada
  printWiFiInfo();
}

void loop() {
}

String getAuthType() {
  int networksCount = WiFi.scanNetworks();

  for (int i = 0; i < networksCount; i++) {
    if (WiFi.SSID(i) == WiFi.SSID()) {
      switch (WiFi.encryptionType(i)) {
        case (WIFI_AUTH_OPEN): return "Red Abierta";
        case (WIFI_AUTH_WEP): return "WEP";
        case (WIFI_AUTH_WPA_PSK): return "WPA PSK";
        case (WIFI_AUTH_WPA2_PSK): return "WPA2 PSK";
        case (WIFI_AUTH_WPA_WPA2_PSK): return "WPA/WPA2 PSK";
        case (WIFI_AUTH_WPA2_ENTERPRISE): return "WPA2 Enterprise";
        default: return "Desconocida";
      }
      break;
    }
  }
}

void printWiFiInfo() {
  Serial.print("ESTADO DE LA CONEXIÓN: ");
  Serial.println(WiFi.status());

  Serial.println("============================== Detalles de la conexión: ==============================");

  Serial.print("Tipo de autenticación: ");
  Serial.println(getAuthType());

  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Máscara de subred: ");
  Serial.println(WiFi.subnetMask());

  Serial.print("Puerta de enlace: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("============================== Estadísticas de la conexión: ==========================");

  IPAddress ip_objetivo(192, 168, 1, 103);
  int package_size = 32;
  int packages_sent = 0;
  int packages_received = 0;
  int lost_packages = 0;
  int transmission_errors = 0;
  int reception_errors = 0;

  unsigned long start_time = millis();

  if (Ping.ping(ip_objetivo, package_size)) {
    packages_received++;
  } else {
    lost_packages++;
    reception_errors++;
    transmission_errors++;
  }

  packages_sent = packages_received + lost_packages;
  tiempo_transcurrido = millis() - start_time;
  conection_time += tiempo_transcurrido;

  Serial.print("Cantidad de paquetes enviados: ");
  Serial.println(packages_sent);

  Serial.print("Cantidad de paquetes recibidos: ");
  Serial.println(packages_received);

  Serial.print("Número de errores de transmisión: ");
  Serial.println(transmission_errors);

  Serial.print("Número de errores de recepción: ");
  Serial.println(reception_errors);

  Serial.print("Cantidad de bytes transferidos: ");
  Serial.println(package_size);

  Serial.print("Tiempo de conexión activa: ");
  Serial.print(conection_time / 1000);
  Serial.println(" segundos");

  Serial.println("============================== Información del punto de acceso: ======================");

  Serial.print("IP: ");
  Serial.println(WiFi.gatewayIP());

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("MAC del AP: ");
  Serial.println(WiFi.BSSIDstr());

  Serial.print("Canal de frecuencia: ");
  Serial.println(WiFi.channel());

  Serial.print("Nivel de señal del AP (RSSI): ");
  Serial.println(WiFi.RSSI());

  Serial.println("============================== Modo de operación de Wifi: ============================");

  Serial.print("Modo de operación: ");
  Serial.println(WiFi.getMode());
  // STA = 1, AP = 2
  Serial.println(WiFi.getMode() == WIFI_STA ? "Estación (STA)" : "Punto de Acceso (AP)");

  Serial.println("======================================================================================");
}
