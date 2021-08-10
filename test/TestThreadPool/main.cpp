#include <iostream>
#include <thread/ThreadPool.h>

volatile int i;

static void doWork(int number) {
    i += number;
}

int main() {
    std::shared_ptr<int> pn = std::make_shared<int>(100);
    MyEngine::ThreadPool pool(5);
    for (int j = 0; j < 20; j++)
        pool.execute(doWork, j);
    pool.shutdown();
    return 0;
}