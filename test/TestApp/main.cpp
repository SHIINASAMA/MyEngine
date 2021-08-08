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

class MyServlet2 : public HttpServlet {
    void doPost(HttpRequest *request, HttpResponse *response) override {
        string bodyString = request->getBody();
        string baseString = {"<h1> Your post data is </h1><h2>" + bodyString + "</h2>"};
        response->setBody(baseString);
        response->setContentLength(baseString.length());
        response->setServer("My App");
    }
};

int main(int argc, char **argv) {
    App::CreateApp("0.0.0.0", 80);
    auto app = App::GetApp();
    app->regServlet("def_get", "/", new MyServlet0);
    app->regServlet("hello", "/hello_page", new MyServlet1);
    app->regServlet("post_test", "/post_page", new MyServlet2);
    app->exec();
}