#include <WiFi.h>
#include <PubSubClient.h>
#include "time.h"

void connection_init();
void connection_loop();
int sendPayload(char payload[128]);
// void getPayload(char payload[128]);