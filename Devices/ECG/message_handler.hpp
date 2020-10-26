#include <vector>
#include "MQTTAsync.h"

vector<string> split(const char* data);

void handle_incoming_messages(void *context, char *topicName, int topicLen, MQTTAsync_message *message);