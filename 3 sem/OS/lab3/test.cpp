#define TESTING
#include "main.cpp"
#include <gtest/gtest.h>
#include <chrono>

TEST(Lab3Test, InitializationAndZeroFill) {
    int size = 10;
    int count = 2;
    std::vector<int> vec(size, 0);
    std::vector<CurrentAction> actions(count + 1, CurrentAction::WORK);
    
    ThreadData data(vec, actions, count);

    EXPECT_EQ(data.vec.size(), size);
    for (int val : data.vec) {
        EXPECT_EQ(val, 0);
    }
    EXPECT_EQ(data.sem_resume.size(), count + 1);
}

TEST(Lab3Test, CheckAllThreadsEndWork) {
    int size = 5;
    int count = 2;
    std::vector<int> vec(size, 0);
    std::vector<CurrentAction> actions(count + 1, CurrentAction::WORK);
    
    ThreadData data(vec, actions, count);

    EXPECT_FALSE(IsAllThreadEndWork(data, count));

    data.Action[1] = CurrentAction::END_WORK;
    data.Action[2] = CurrentAction::END_WORK;

    EXPECT_TRUE(IsAllThreadEndWork(data, count));
}

TEST(Lab3Test, MarkerCleanupOnTermination) {
    start = false;
    int size = 5;
    std::vector<int> vec(size, 0);
    std::vector<CurrentAction> actions(2, CurrentAction::WORK);
    
    ThreadData data(vec, actions, 1);

    std::thread t(marker, std::ref(data), 1);

    start = true;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        std::lock_guard<std::mutex> lock(data.mtx);
        if (data.Action[1] == CurrentAction::WAIT_PERMISSION_TO_WORK) {
            data.Action[1] = CurrentAction::END_WORK;
            data.sem_resume[1]->release();
            break;
        }
    }

    t.join();

    for (int v : data.vec) {
        EXPECT_EQ(v, 0);
    }
}