#include "MQTTPublisher.h"

MQTTPublisher::MQTTPublisher(){
    if ((this->rc = MQTTClient_create(&(this->client), this->ADDRESS.c_str(), this->CLIENTID.c_str(),
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         MQTTClient_destroy(&(this->client));
         exit(EXIT_FAILURE);
    }
    this->conn_opts = MQTTClient_connectOptions_initializer;
    this->conn_opts.keepAliveInterval = 20;
    this->conn_opts.cleansession = 1;
    if ((this->rc = MQTTClient_connect(this->client, &(this->conn_opts))) != MQTTCLIENT_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
}

MQTTPublisher::MQTTPublisher(const std::string address,const std::string id,const std::string topic){
    this->ADDRESS = address;
    this->CLIENTID = id;
    this->TOPIC = topic;
    if ((this->rc = MQTTClient_create(&(this->client), this->ADDRESS.c_str(), this->CLIENTID.c_str(),
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         MQTTClient_destroy(&(this->client));
         exit(EXIT_FAILURE);
    }
    this->conn_opts = MQTTClient_connectOptions_initializer;
    this->conn_opts.keepAliveInterval = 20;
    this->conn_opts.cleansession = 1;
    if ((this->rc = MQTTClient_connect(this->client, &(this->conn_opts))) != MQTTCLIENT_SUCCESS)
    {
        exit(EXIT_FAILURE);
    }
}

MQTTPublisher::~MQTTPublisher(){
    if ((this->rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS)
        printf("Failed to disconnect, return code %d\n", this->rc);
    MQTTClient_destroy(&(this->client));
}

bool MQTTPublisher::publish(const std::string payload){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    std::string casted_payload = const_cast<std::string&>(payload);
    pubmsg.payload = &casted_payload;
    pubmsg.payloadlen = casted_payload.size();
    pubmsg.qos = this->QOS;
    pubmsg.retained = 0;
    if ((this->rc = MQTTClient_publishMessage(this->client, this->TOPIC.c_str(), &pubmsg, &(this->token))) != MQTTCLIENT_SUCCESS)
    {
         printf("Failed to publish message, return code %d\n", rc);
         exit(EXIT_FAILURE);
    }
    rc = MQTTClient_waitForCompletion(this->client, this->token, this->TIMEOUT);
    if(rc != -1)
    {
        printf("Message %s with delivery token %d delivered\n", casted_payload.c_str(),this->token);
        return true;
    } 
    return false;
}
