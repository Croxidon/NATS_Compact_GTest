add_test([=[NATSGTest.TestPublishSubscribe]=]  /home/crox/Desktop/NATS_Compact_GTest/build/NATS_Compact_GTest [==[--gtest_filter=NATSGTest.TestPublishSubscribe]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NATSGTest.TestPublishSubscribe]=]  PROPERTIES WORKING_DIRECTORY /home/crox/Desktop/NATS_Compact_GTest/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  NATS_Compact_GTest_TESTS NATSGTest.TestPublishSubscribe)
