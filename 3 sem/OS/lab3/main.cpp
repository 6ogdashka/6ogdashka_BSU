#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <mutex>
#include <semaphore>
#include <memory>

enum class CurrentAction{
    WORK,
    WAIT_PERMISSION_TO_WORK,
    END_WORK
};

bool start = false;

struct ThreadData {
    std::vector<int> vec;
    std::vector<CurrentAction> Action;
    std::mutex mtx;
    std::vector<std::unique_ptr<std::binary_semaphore>> sem_resume;

    ThreadData(std::vector<int> vec_, std::vector<CurrentAction> Action_, int count) 
        : vec(vec_), Action(Action_) {
        for (int i = 0; i <= count; ++i) {
            sem_resume.push_back(std::make_unique<std::binary_semaphore>(0));
        }
    } 
};

void marker(ThreadData& data, int order) {
    std::freopen("out.txt", "w", stdout);
    while (!start) {
        std::this_thread::yield();
    }
    srand(order);
    std::vector<int> markered_ouwself;
    while (true) {
        int term = rand();
        int idx = term % data.vec.size();
        
        {
            std::lock_guard<std::mutex> lock(data.mtx);
            if (data.vec[idx] == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                data.vec[idx] = order;
                markered_ouwself.push_back(idx);
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            } else {
                std::cout << "Порядковый номер потока:" << order << "\n";
                std::cout << "Было помечено " << markered_ouwself.size() << " элементов\n";
                std::cout << "Элемент с индексом " << idx << " невозможно поменить\n";
                data.Action[order] = CurrentAction::WAIT_PERMISSION_TO_WORK;
            }
        }

        data.sem_resume[order]->acquire();

        {
            std::lock_guard<std::mutex> lock(data.mtx);
            if (data.Action[order] == CurrentAction::END_WORK) {
                break;
            }
        }
    }

    std::lock_guard<std::mutex> lock(data.mtx);
    for (int i : markered_ouwself) {
        data.vec[i] = 0;
    }
    data.Action[order] = CurrentAction::END_WORK;
}

bool IsAllThreadEndWork(ThreadData& data, int marker_count) {
    std::lock_guard<std::mutex> lock(data.mtx);
    return std::all_of(data.Action.begin() + 1, data.Action.begin() + marker_count + 1, [](CurrentAction action) {
        return action == CurrentAction::END_WORK;
    });
}

bool IsAllThreadWaitToPermission(ThreadData& data, int marker_count) {
    std::lock_guard<std::mutex> lock(data.mtx);
    return std::all_of(data.Action.begin() + 1, data.Action.begin() + marker_count + 1, [](CurrentAction action) {
        return action == CurrentAction::WAIT_PERMISSION_TO_WORK || action == CurrentAction::END_WORK;
    });
}

#ifndef TESTING
int main() {
    int memory_size{};
    std::cout << "Введите размерность массива: ";
    std::cin >> memory_size;
    std::vector<int> vec(memory_size, 0);

    int marker_count{};
    std::cout << "Введите количество потоков: ";
    std::cin >> marker_count;

    std::vector<CurrentAction> action_vec(marker_count + 1, CurrentAction::WORK);

    ThreadData data(vec, action_vec, marker_count);

    std::vector<std::thread> threads;
    for (int i = 1; i <= marker_count; ++i) {
        threads.emplace_back(marker, std::ref(data),i);
    }

    start = true;

    while (!IsAllThreadEndWork(data, marker_count)) {
        while (!IsAllThreadWaitToPermission(data, marker_count)) {
            std::this_thread::yield();
        }

        {
            std::lock_guard<std::mutex> lock(data.mtx);
            std::cout << "Содержимое массива: ";
            for (int i : data.vec) { std::cout << i << " "; }
            std::cout << "\n";
            std::cout << "Какому процессу завершить работу? (1-" << marker_count << "): ";
        }

        int order{};
        std::cin >> order;

        {
            std::lock_guard<std::mutex> lock(data.mtx);
            data.Action[order] = CurrentAction::END_WORK;
        }

        data.sem_resume[order]->release();

        {
            std::lock_guard<std::mutex> lock(data.mtx);
            for (int i = 1; i <= marker_count; ++i) {
                if (data.Action[i] != CurrentAction::END_WORK) {
                    data.Action[i] = CurrentAction::WORK;
                }
            }
        }

        for (int i = 1; i <= marker_count; ++i) {
            if (i != order && data.Action[i] != CurrentAction::END_WORK) {
                data.sem_resume[i]->release();
            }
        }
    }

    for (auto& t : threads) {
        t.join();
    }
}
#endif