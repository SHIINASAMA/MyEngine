#include <app/App.h>
#include <servlet/HttpServlet.h>

using namespace MyEngine;

class MyServlet0 : public HttpServlet {
    void doGet(HttpRequest *request, HttpResponse *response) override {
        string baseString = {"<h1>This is MY APP.</h1>"};
        response->setBody(baseString);
        response->setContentLength(baseString.length());
        response->setServer("My App");
    }
};

class MyServlet1 : public HttpServlet {
    void doGet(HttpRequest *request, HttpResponse *response) override {
        string baseString = {"<h1>Hello<h2>"};
        response->setBody(baseString);
        response->setContentLength(baseString.length());
        response->setServer("My App");
    }
};

int main() {
    App::CreateApp("0.0.0.0", 80);
    auto app = App::GetApp();
    app->regServlet("myServlet0", "/", new MyServlet0);
    app->regServlet("myServlet1", "/hello_page",new MyServlet1);
    app->exec();
}