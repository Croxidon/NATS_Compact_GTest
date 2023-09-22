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
NATS_Compact_Test x;
boost::thread pubThread(&NATS_Compact_Test::PublishingMsg, &x);
boost::thread subThread(&NATS_Compact_Test::SubscribingForMsg, &x);
pubThread.join();
subThread.join();

std::lock_guard<std::mutex> lock(x.mtx);
    

 ASSERT_GE(x.receivedMsgCount, 1000);
 ASSERT_LE(x.subTimeElapsed, 1000000);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
