#ifndef NATS_COMPACT_TEST_H
#define NATS_COMPACT_TEST_H

#include <nats/nats.h>
#include <mutex>

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg, void *closure);

class NATS_Compact_Test
{
public:
    NATS_Compact_Test();  
    ~NATS_Compact_Test(); 

    void PublishingMsg();
    void SubscribingForMsg();

    

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
    int64_t subTimeStart{0};
    int64_t subTimeFinish{0};
    int64_t subTimeElapsed{0};
    int64_t pubTimeStart{0};
    int64_t pubTimeFinish{0};
    int64_t pubTimeElapsed{0};
 
};

#endif