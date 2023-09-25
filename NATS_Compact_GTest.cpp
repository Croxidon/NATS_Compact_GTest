#include <gtest/gtest.h>
#include <boost/thread/thread.hpp>
#include <boost/chrono/chrono.hpp>
#include "NATS_Compact_Test/NATS_Compact_Test.h"


class NATS_GTest : public ::testing::Test {
public:
   
    NATS_GTest() {
      
    }

    ~NATS_GTest() override {

        
    }
    
    
   
};


TEST(NATSGTest, TestPublishSubscribe) {
NATS_Compact_Test x(3);
boost::thread pubThread(&NATS_Compact_Test::PublishingMsg, &x);
boost::thread subThread0(&NATS_Compact_Test::SubscribingForMsg, &x, 0);
boost::thread subThread1(&NATS_Compact_Test::SubscribingForMsg, &x, 1);
boost::thread subThread2(&NATS_Compact_Test::SubscribingForMsg, &x, 2);
pubThread.join();
subThread0.join();
subThread1.join();
subThread2.join();


ASSERT_GE(x.receivedMsgCount[0], 1000);
ASSERT_LE(x.subTimeElapsed[0], 1000000);
ASSERT_GE(x.receivedMsgCount[1], 1000);
ASSERT_LE(x.subTimeElapsed[1], 1000000);
ASSERT_GE(x.receivedMsgCount[2], 1000);
ASSERT_LE(x.subTimeElapsed[2], 1000000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
