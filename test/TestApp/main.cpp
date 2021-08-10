#include <app/App.h>
#include <iostream>
#include <servlet/HttpServlet.h>

using namespace MyEngine;

int main(int argc, char **argv) {
    App::CreateApp("0.0.0.0", 8000);
    auto app = App::GetApp();
    app->start();
    string cmd;
    while (true) {
        std::cin >> cmd;
        if (cmd == "exit") {
            app->shutdown();
            return 0;
        }
    }
}