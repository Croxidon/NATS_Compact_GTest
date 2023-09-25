#include <iostream>
#include "NATS_Compact_Test.h"
#include <chrono>
#include <unistd.h>
#include <mutex>
#include <vector>
#include <boost/thread/thread.hpp>
extern "C"{
#include <stdio.h>
#include <nats/nats.h>

}

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg0, void *closure)
{
    

    // Need to destroy the message!
    natsMsg_Destroy(msg0);
}

 //Constructor
 NATS_Compact_Test::NATS_Compact_Test(int a)
 {
    int threadCount = a;
    for (int i = 0; i < threadCount; i++)
    {
        receivedMsgCount.push_back(0);
        subTimeStart.push_back(0);
        subTimeFinish.push_back(0);
        subTimeElapsed.push_back(0);
        
    }
    
    s0 = natsOptions_Create(&opts0);
    s0 = natsConnection_ConnectTo(&conn0, serverAdress);
    s1 = natsOptions_Create(&opts1);
    s1 = natsConnection_ConnectTo(&conn1, serverAdress);
    s2 = natsOptions_Create(&opts2);
    s2 = natsConnection_ConnectTo(&conn2, serverAdress);

    if (s0 == NATS_OK)
    {
        std::cout << "Connection established s0.\n";
    }
     if (s1 == NATS_OK)
    {
        std::cout << "Connection established s1.\n";
    }
     if (s2 == NATS_OK)
    {
        std::cout << "Connection established s2.\n";
    }
 }
     
 //Destroyer
 NATS_Compact_Test::~NATS_Compact_Test()
 {
     natsSubscription_Destroy(sub0);
     natsSubscription_Destroy(sub1);
     natsSubscription_Destroy(sub2);
     natsConnection_Destroy(conn0);
     natsConnection_Destroy(conn1);
     natsConnection_Destroy(conn2);
 }

 //Message publishing function
 void NATS_Compact_Test::PublishingMsg()
 {   pubTimeStart = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int messagesSent = 0;

    while (true)
    {
        if(s0 == NATS_OK) {
            s0 = natsConnection_PublishString(conn0, "foo", "This is a test message.\n");
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
 void NATS_Compact_Test::SubscribingForMsg(int threadNumber)
 {
     if (s0 == NATS_OK && s1==NATS_OK && s2==NATS_OK)   {
        switch (threadNumber)
        {
        case 0:
            s0 = natsConnection_SubscribeTimeout(&sub0, conn0, "foo", 60000, onMsg, NULL);
            break;
            case1:
            s1 = natsConnection_SubscribeTimeout(&sub1, conn1, "foo", 60000, onMsg, NULL);
            break;
            case2:
            s2 = natsConnection_SubscribeTimeout(&sub2, conn2, "foo", 60000, onMsg, NULL);
            break;
        default:
            break;
        }
        
        }
      subTimeStart[threadNumber] = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
     while (true)
     {
        switch (threadNumber)
        {
        case 0:
           natsSubscription_GetDelivered(sub0, &receivedMsgCount[threadNumber]);
            break;
         case 1:
           natsSubscription_GetDelivered(sub1, &receivedMsgCount[threadNumber]);
            break;
         case 2:
           natsSubscription_GetDelivered(sub2, &receivedMsgCount[threadNumber]);
            break;
        
        default:
            break;
        }
        
        subTimeFinish[threadNumber] = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        subTimeElapsed[threadNumber] = subTimeFinish[threadNumber] - subTimeStart[threadNumber];
        std::cout << "Received message count is:" << receivedMsgCount[threadNumber] << " for thread number" << threadNumber << " in:" << subTimeElapsed[threadNumber]<< "microseconds\n";
        
      

        if (subTimeElapsed[threadNumber] >= 995000)
        {
            break;
        }
        else if (receivedMsgCount[threadNumber] > 999)
        {
            break;
        }
        
     }  
     
     
   
 }