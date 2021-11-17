set(MyEngineSrc
        src/native/Socket.h
        src/socket/TcpServer.cpp
        src/socket/TcpServer.h
        src/socket/TcpClient.cpp
        src/socket/TcpClient.h
        src/http/HttpClient.cpp
        src/http/HttpClient.h
        src/http/HttpHeader.h
        src/http/HttpHeader.cpp
        src/http/HttpParser.h
        src/http/HttpParser.cpp
        src/http/HttpRequest.h
        src/http/HttpRequest.cpp
        src/http/HttpResponse.cpp
        src/http/HttpResponse.h
        src/http/HttpServer.h
        src/http/HttpServer.cpp
        src/log/ConsoleFormatter.h
        src/log/ConsoleFormatter.cpp
        src/log/ConsoleAppender.h
        src/log/ConsoleAppender.cpp
        src/log/Logger.h
        src/log/Logger.cpp
        src/log/LogAppender.cpp
        src/log/LogAppender.h
        src/log/LogEvent.cpp
        src/log/LogEvent.h
        src/log/LogFormatter.h
        src/servlet/HttpServlet.cpp
        src/servlet/HttpServlet.h
        src/servlet/ServletContext.h
        src/servlet/ServletContext.cpp
        src/servlet/Servlet.h
        src/servlet/Servlet.cpp
        src/thread/SafeQueue.h
        src/thread/ThreadPool.h
        src/thread/Thread.cpp
        src/plugin/Plugin.h
        src/plugin/Plugin.cpp
        src/Utility.h
        src/app/App.h
        src/app/App.cpp
        src/app/ConfigReader.h
        src/app/ConfigReader.cpp
        src/db/sqlite/SqliteHelper.cpp
        src/db/sqlite/SqliteHelper.h
        src/log/SqliteAppender.cpp
        src/log/SqliteAppender.h
        src/http/HttpRange.cpp
        src/http/HttpRange.h)

file(GLOB_RECURSE YamlCppSrc "thirdparty/yaml-cpp/src/*.cpp" "thirdparty/yaml-cpp/src/*.h")
add_library(yaml-cpp SHARED ${YamlCppSrc})

set(SqliteSrc
        thirdparty/sqlite/shell.c
        thirdparty/sqlite/sqlite3.c
        thirdparty/sqlite/sqlite3.h
        thirdparty/sqlite/sqlite3ext.h
        )
add_library(Sqlite SHARED ${SqliteSrc})

set(CArgsSrc
        thirdparty/CARGS/CArgs.cpp
        thirdparty/CARGS/CArgs.h
        )
add_library(CArgs SHARED ${CArgsSrc})

if (UNIX)
    list(APPEND MyEngineSrc src/native/SocketLinux.cpp)
    add_library(MyEngine SHARED ${MyEngineSrc})
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(MyEngine PUBLIC Threads::Threads dl yaml-cpp Sqlite)
endif ()

function(add_test exec_name)
    add_executable(${exec_name} ${ARGN})
    target_link_libraries(${exec_name} MyEngine)
endfunction(add_test)

function(add_plugin plugin_name)
    set(PluginSrc
            src/servlet/Servlet.h
            src/servlet/Servlet.cpp
            src/servlet/HttpServlet.h
            src/servlet/HttpServlet.cpp
            src/plugin/Plugin.h)
    add_library(${ARGV0} SHARED ${ARGN} ${PluginSrc})
endfunction(add_plugin)

include_directories(src)
include_directories(thirdparty/yaml-cpp/include)
include_directories(thirdparty/sqlite)
include_directories(thirdparty/CARGS)

# 测试文件
add_test(TestTcpClient test/TestTcpClient/main.cpp)
add_test(TestTcpServer test/TestTcpServer/main.cpp)
# add_test(TestHttpServer test/TestHttpServer/main.cpp)
# add_test(TestHttpClient test/TestHttpClient/main.cpp)
# add_test(TestServlet test/TestServlet/main.cpp)
add_test(TestApp test/TestApp/main.cpp)
add_test(TestThreadPool test/TestThreadPool/main.cpp)
add_test(TestLogger test/TestLogger/main.cpp)
# add_test(TestPlugin test/TestPlugin/main.cpp)
add_plugin(Plugin test/TestPlugin/TestServlet.h test/TestPlugin/TestServlet.cpp)
add_test(TestSqlite test/TestSqlite/main.cpp)

# 工具文件
add_executable(PluginManifestViewer
        kit/PluginManifestViewer/main.cpp
        src/servlet/Servlet.h
        src/servlet/Servlet.cpp
        src/servlet/HttpServlet.h
        src/servlet/HttpServlet.cpp
        src/plugin/Plugin.h
        src/plugin/Plugin.cpp)
target_link_libraries(PluginManifestViewer dl)

# 服务器本体
add_executable(Server server/main.cpp)
target_link_libraries(Server MyEngine CArgs)