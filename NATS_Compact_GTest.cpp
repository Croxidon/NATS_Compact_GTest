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
NATS_Compact_Test x,y,z;
boost::thread pubThread(&NATS_Compact_Test::PublishingMsg, &x);
boost::thread subThread1(&NATS_Compact_Test::SubscribingForMsg, &x);
boost::thread subThread2(&NATS_Compact_Test::SubscribingForMsg, &y);
boost::thread subThread3(&NATS_Compact_Test::SubscribingForMsg, &z);
pubThread.join();
subThread1.join();
subThread2.join();
subThread3.join();


 ASSERT_GE(x.receivedMsgCount, 1000);
 ASSERT_LE(x.subTimeElapsed, 1000000);
  ASSERT_GE(y.receivedMsgCount, 1000);
 ASSERT_LE(y.subTimeElapsed, 1000000);
  ASSERT_GE(z.receivedMsgCount, 1000);
 ASSERT_LE(z.subTimeElapsed, 1000000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
