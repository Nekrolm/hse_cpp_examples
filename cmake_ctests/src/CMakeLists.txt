add_executable(Test test.cpp)
target_link_libraries(Test PRIVATE GTest::gtest)
add_test(NAME TestExample COMMAND $<TARGET_FILE:Test>)