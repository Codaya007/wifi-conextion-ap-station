#include <WiFi.h>

const char* ssid = "Vivi-RED";
const char* password = "Mayonesa12345.";

int clients_limit_count = 10;
IPAddress ip_esp(192, 168, 1, 2);
IPAddress gateway_ip(192, 168, 1, 1);
IPAddress subnet_mask(255, 255, 255, 0);
IPAddress dhcp(192, 168, 1, 5);

void printWiFiInfo() {
  Serial.println("============================================================================");
  Serial.println("============================== Información AP ==============================");
  Serial.println("============================================================================");

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("Canal de frecuencia: ");
  Serial.println(WiFi.channel());

  Serial.print("Modo de encriptación: WPA2_PSK");
  Serial.println("WPA2_PSK");

  Serial.print("Máximo de clientes: ");
  Serial.println(String(clients_limit_count));

  Serial.print("Rango de direcciones IP: ");
  char ipRange[50];  // Arreglo para almacenar la cadena formateada
  sprintf(ipRange, "Rango de direcciones IP: %d.%d.%d.%d - %d.%d.%d.%d",
          dhcp[0], dhcp[1], dhcp[2], dhcp[3],
          dhcp[0], dhcp[1], dhcp[2], dhcp[3] + clients_limit_count - 1);
  Serial.println(ipRange);

  Serial.print("Dirección IP del AP: ");
  Serial.println(WiFi.softAPIP());

  Serial.print("Puerta de enlace del AP: ");
  Serial.println(gateway_ip);

  Serial.print("Máscara de subred del AP: ");
  Serial.println(WiFi.softAPSubnetMask());

  Serial.println("============================================================================");
  Serial.println("============================================================================");
  Serial.println("============================================================================\n");
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);

  // Configuro credenciales y seguridad
  WiFi.softAP(ssid, password, 6, WIFI_AUTH_WPA2_PSK, 2);
  // Configuro ips
  WiFi.softAPConfig(ip_esp, gateway_ip, subnet_mask, dhcp);
  printWiFiInfo();
}

void loop() {
}