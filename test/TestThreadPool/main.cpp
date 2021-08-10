#include <iostream>
#include <thread/ThreadPool.h>

volatile int i;

void doWork(void *number) {
    i = *(int *) number;
}

int main() {
    std::shared_ptr<int> pn = std::make_shared<int>(100);
    MyEngine::ThreadPool pool(5);
    pool.init();
    pool.commit({doWork, (void *) pn.get()});
    pool.shutdown();
    return 0;
}