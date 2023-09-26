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
boost::thread subThread0(&NATS_Compact_Test::SubscribingForMsg, &x, 0);
boost::thread subThread1(&NATS_Compact_Test::SubscribingForMsg, &x, 1);
boost::thread subThread2(&NATS_Compact_Test::SubscribingForMsg, &x, 2);
boost::thread pubThread(&NATS_Compact_Test::PublishingMsg, &x);
subThread0.join();
subThread1.join();
subThread2.join();
pubThread.join();
boost::this_thread::sleep_for(boost::chrono::seconds(10));

EXPECT_GE(x.receivedMsgCount[0], 1000);
EXPECT_GE(x.receivedMsgCount[1], 1000);
EXPECT_GE(x.receivedMsgCount[2], 1000);
std::cout << "Received message count is:" << x.receivedMsgCount[0] << " for thread number 0"  << " in:" << x.subTimeElapsed[0]<< "microseconds\n";
std::cout << "Received message count is:" << x.receivedMsgCount[1] << " for thread number 1"  << " in:" << x.subTimeElapsed[1]<< "microseconds\n";
std::cout << "Received message count is:" << x.receivedMsgCount[2] << " for thread number 2"  << " in:" << x.subTimeElapsed[2]<< "microseconds\n";
        
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
