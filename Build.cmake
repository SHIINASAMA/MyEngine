set(engine_src
        src/native/Socket.h
        src/socket/TcpClient.h
        src/socket/TcpClient.cpp
        src/socket/TcpServer.h
        src/socket/TcpServer.cpp
        src/http/HttpRequest.h
        src/http/HttpHeader.cpp
        src/http/HttpRequest.cpp
        src/http/HttpResponse.cpp
        src/http/HttpServer.h
        src/http/HttpServer.cpp
        src/http/HttpParser.h
        src/http/HttpParser.cpp
        src/http/HttpClient.h
        src/http/HttpClient.cpp
        src/servlet/Servlet.h
        src/servlet/Servlet.cpp
        src/servlet/ServletContext.h
        src/servlet/ServletContext.cpp
        src/servlet/HttpServlet.h
        src/servlet/HttpServlet.cpp
        src/app/App.h
        src/app/App.cpp
        src/app/NotFindServlet.h
        src/app/NonsupportMethodServlet.h
        src/app/SuccessServlet.h
        src/app/ErrorServlet.h
        src/Utility.h
        src/http/HttpHeader.h
        src/http/HttpResponse.h
        src/thread/ThreadPool.h
#        src/thread/SafeQueue.h
        )

if (UNIX)
    add_library(MyEngineLib ${engine_src} src/native/SocketLinux.cpp)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(MyEngineLib PUBLIC Threads::Threads)
elseif (WIN32)
elseif (APPLE)
endif ()

function(add_test exec_name src)
    add_executable(${exec_name} ${src})
    target_link_libraries(${exec_name} MyEngineLib)
endfunction(add_test)

add_test(TestTcpClient test/TestTcpClient/main.cpp)
add_test(TestTcpServer test/TestTcpServer/main.cpp)
add_test(TestHttpServer test/TestHttpServer/main.cpp)
add_test(TestHttpClient test/TestHttpClient/main.cpp)
add_test(TestServlet test/TestServlet/main.cpp)
add_test(TestApp test/TestApp/main.cpp)
add_test(TestThreadPool test/TestThreadPool/main.cpp)