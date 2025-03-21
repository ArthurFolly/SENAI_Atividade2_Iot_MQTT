// Autor: Arthur Folly
// Senai Afonso Pena

// incluindo bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>

// Configurações da rede Wi-Fi
const char* ssid = "TOBI24G";
const char* password = "Xwyzh22Xwyzh22#";

// Configurações do broker MQTT
const char* mqtt_server = "192.168.15.7";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/Atividade2_Arthur";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi conectado");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Conectando ao broker MQTT...");
        if (client.connect("ESP32Client")) {
            Serial.println("conectado");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("falha, rc=");
            Serial.print(client.state());
            Serial.println(" tentando novamente em 10 segundos");
            delay(10000);
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensagem recebida em tópico: ");
    Serial.println(topic);
    Serial.print("Mensagem: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
    
    // Exemplo de envio de mensagem
    client.publish(mqtt_topic, "Mensagem de teste do ESP32 - Atividade 2 SENAI");
    delay(5000);
}
