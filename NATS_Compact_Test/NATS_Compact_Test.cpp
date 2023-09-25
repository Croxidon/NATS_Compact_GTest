#include <iostream>
#include "NATS_Compact_Test.h"
#include <chrono>
#include <unistd.h>
#include <mutex>
extern "C"{
#include <stdio.h>
#include <nats/nats.h>

}

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg, void *closure)
{
    

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
 {   pubTimeStart = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int messagesSent = 0;

    while (true)
    {
        if(s == NATS_OK) {
            s = natsConnection_PublishString(conn, "foo", "This is a test message.\n");
            messagesSent++;
        };  
         pubTimeFinish = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
         pubTimeElapsed = pubTimeFinish - pubTimeStart;
        if (pubTimeElapsed >= 995000) 
        {
            break;
        }
    }  
     std::cout << "Sent " << messagesSent << " messages.\n";
 }

 //Subscribing function
 void NATS_Compact_Test::SubscribingForMsg()
 {
     if (s == NATS_OK)   {s = natsConnection_SubscribeTimeout(&sub, conn, "foo", 60000, onMsg, NULL);}
      subTimeStart = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
     while (true)
     {
        natsSubscription_GetDelivered(sub, &receivedMsgCount);
        subTimeFinish = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        subTimeElapsed = subTimeFinish - subTimeStart;
        std::cout << "Received message count is:" << receivedMsgCount << "\n";
        std::cout << "in:" << subTimeElapsed<< "microseconds\n";
        
      

        if (subTimeElapsed >= 995000)
        {
            break;
        }
        else if (receivedMsgCount > 999)
        {
            break;
        }
        
     }  
     
     
   
 }