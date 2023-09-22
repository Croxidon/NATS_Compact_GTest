#include <iostream>
#include "NATS_Compact_Test.h"
#include <chrono>
#include <unistd.h>
extern "C"{
#include <stdio.h>
#include <nats/nats.h>
}

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg, void *closure)
{
    printf("Received msg: %s - %.*s\n",
           natsMsg_GetSubject(msg),
           natsMsg_GetDataLength(msg),
           natsMsg_GetData(msg));

    // Need to destroy the message!
    natsMsg_Destroy(msg);
}


 //Constructor
 NATS_Compact_Test::NATS_Compact_Test()
 {
     s = natsOptions_Create(&opts);
     s = natsConnection_ConnectTo(&conn, serverAdress);
     if (s == NATS_OK)
     {
        std::cout << "Connection established.\n";
     }
 }
     
 //Destroyer
 NATS_Compact_Test::~NATS_Compact_Test()
 {
     natsSubscription_Destroy(sub);
     natsConnection_Destroy(conn);
 }
 //Message publishing function
 void NATS_Compact_Test::PublishingMsg()
 {  
    if(s == NATS_OK) {s = natsConnection_PublishString(conn, "foo", "This is a test message.\n");};   
 }
 //Subscribing function
 void NATS_Compact_Test::SubscribingForMsg()
 {
     if (s == NATS_OK)   {s = natsConnection_SubscribeTimeout(&sub, conn, "foo", 60000, onMsg, NULL);}
     int64_t timeStart = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
     while (true)
     {
        natsSubscription_GetDelivered(sub, &receivedMsgCount);
        int64_t timeFinish = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        int64_t timeElapsed = timeFinish - timeStart;
        std::cout << "Received message count is:" << receivedMsgCount << "\n";
        std::cout << "in:" << timeElapsed<< "microseconds\n";
     }  
     
     
   
 }