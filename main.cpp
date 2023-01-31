#include "MQTTPublisher.h"
#include "json.hpp"

int main(int, char**) {
    MQTTPublisher publisher;
    nlohmann::json obj = { {"test","test"} };
    publisher.publish(obj.dump());
    return 0;
}
