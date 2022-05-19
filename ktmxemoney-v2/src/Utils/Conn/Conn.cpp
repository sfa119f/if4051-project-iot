#include "Conn.h"

// WiFi Config
const char *ssid = "Gandung";
const char *password = "1196a211";

// MQTT Config
const char *mqtt_broker = "202.148.1.57";
const char *topic = "reader";
const int mqtt_port = 1883;
const char *mqtt_ssid = "app-appktmxemoney";
const char *mqtt_password = "BgkfOGumPp6HP9x6mn2prnsNCJ4Hej";

// NTP Config
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;

// Heartbeat Variables
unsigned long prevMillis = 0;
unsigned long prevPubMillis = 0;
unsigned long prevRecMillis = 0;
unsigned int publishInterval = 2000;
unsigned int reconnectInterval = 10000;

// Connection Stuffs
WiFiClient espClient;
PubSubClient client(espClient);

void connection_init()
{
  // Callback for subbed topic
  auto brokerCallback = [](char *topic, byte *payload, unsigned int length)
  {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
  };

  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(brokerCallback);
}

void connection_loop()
{
  unsigned long currentMillis = millis();

  if (client.connected())
  { // if connected to broker
    if (currentMillis - prevPubMillis >= publishInterval)
    {
      prevPubMillis = currentMillis;
      //        String payload = nim + ": " + String(blinkFreq);
      //        client.publish(topic, payload.c_str());
      // client.publish(topic, "asdop");
    }
  }
  else
  {
    if (currentMillis - prevRecMillis >= reconnectInterval)
    {
      prevRecMillis = currentMillis;
      if (WiFi.status() != WL_CONNECTED)
      { // if not connected to broker because of not connected wifi
        WiFi.begin(ssid, password);
        Serial.println("trying wifi");
      }
      else
      { // if connected to wifi but not connected to broker
        Serial.println("wifi connected");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.println("trying mqtt");
        if (client.connect(client_id.c_str(), mqtt_ssid, mqtt_password))
        {
          client.subscribe(topic);
          Serial.println("mqtt connected");
        }
      }
    }
  }
  client.loop();
  delay(1);
}

int sendPayload(char payload[128])
{
  client.publish(topic, payload);
  return 0;
}