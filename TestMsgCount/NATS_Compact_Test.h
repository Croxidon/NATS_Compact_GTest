#ifndef NATS_COMPACT_TEST_H
#define NATS_COMPACT_TEST_H

#include <nats/nats.h>

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg, void *closure);

class NATS_Compact_Test
{
public:
    NATS_Compact_Test();  
    ~NATS_Compact_Test(); 

    void PublishingMsg();
    void SubscribingForMsg();
    int64_t MessageCount();
    

private:
    natsConnection *conn;
    natsOptions *opts;
    natsSubscription *sub;
    natsMsg *msg;
    natsStatus s;
    char subject[256] = "foo";
    char serverAdress[256] = "localhost:4222";
    char message[256] = "This is a test message.\n";
public:
    int64_t receivedMsgCount{0};
    int64_t timeStart;
    int64_t timeFinish;
    int64_t timElapsed;
};

#endif