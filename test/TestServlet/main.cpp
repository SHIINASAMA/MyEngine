#include <servlet/Servlet.h>

class MyServlet : public MyEngine::Servlet{};

void print_type_name(){
    MyEngine::Servlet servlet;
    printf("%s\n", servlet.getClassName().c_str());
    MyServlet myServlet;
    printf("%s\n", myServlet.getClassName().c_str());
}

int main(){
    print_type_name();
    return 0;
}