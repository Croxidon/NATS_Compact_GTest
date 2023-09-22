#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/chrono/chrono.hpp>
#include "NATS_Compact_Test.h"


int main()
{
    int y{0};
    NATS_Compact_Test x;
    x.PublishingMsg();

    
    
    return 0;
}