#ifndef NATS_COMPACT_TEST_H
#define NATS_COMPACT_TEST_H

#include <nats/nats.h>
#include <mutex>
#include <vector>

static void
onMsg(natsConnection *conn, natsSubscription *sub, natsMsg *msg, void *closure);

class NATS_Compact_Test
{
public:
    NATS_Compact_Test(int a);  
    ~NATS_Compact_Test(); 

    void PublishingMsg();
    void SubscribingForMsg(int threadNumber);

    

private:
    natsConnection *conn;
    natsOptions *opts;
    natsSubscription *sub0, *sub1, *sub2;
    natsMsg *msg;
    natsStatus s;
    char subject[256] = "foo";
    char serverAdress[256] = "localhost:4222";
    char message[256] = "This is a test message.\n";
    public:
    std::vector<int64_t> receivedMsgCount;
    std::vector<int64_t> subTimeStart;
    std::vector<int64_t> subTimeFinish;
    std::vector<int64_t> subTimeElapsed;
    int64_t pubTimeStart{0};
    int64_t pubTimeFinish{0};
    int64_t pubTimeElapsed{0};
    int threadCount;

 
};

#endif