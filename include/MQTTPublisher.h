#include "MQTTClient.h"
#include <string>
class MQTTPublisher
{
private:
    MQTTPublisher(const MQTTPublisher &);
    MQTTPublisher(MQTTPublisher &&);
    MQTTPublisher &operator=(const MQTTPublisher &);
    std::string ADDRESS = "tcp://127.0.0.1:1883";
    std::string CLIENTID = "ExampleClientPub";
    std::string TOPIC = "MQTT Examples";
    const int QOS = 1;
    const long int TIMEOUT = 10000L;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts;
    MQTTClient_deliveryToken token;
    int rc;

public:
    MQTTPublisher();
    MQTTPublisher(const std::string address,const std::string id,const std::string topic);
    ~MQTTPublisher();
    bool publish(const std::string payload);
};