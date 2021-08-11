file(GLOB_RECURSE MyEngineSrc "src/*.cpp" "src/*.h")
file(GLOB_RECURSE YamlCppSrc "thirdparty/yaml-cpp/src/*.cpp" "thirdparty/yaml-cpp/src/*.h")

if (UNIX)
    add_library(MyEngine SHARED ${MyEngineSrc} ${YamlCppSrc})
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(MyEngine PUBLIC Threads::Threads dl)
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

function(add_exec exec_name)
    add_executable(${exec_name} ${ARGN})
    target_link_libraries(${exec_name} MyEngine)
endfunction(add_exec)

# 测试文件
add_test(TestTcpClient test/TestTcpClient/main.cpp)
add_test(TestTcpServer test/TestTcpServer/main.cpp)
add_test(TestHttpServer test/TestHttpServer/main.cpp)
add_test(TestHttpClient test/TestHttpClient/main.cpp)
add_test(TestServlet test/TestServlet/main.cpp)
add_test(TestApp test/TestApp/main.cpp)
add_test(TestThreadPool test/TestThreadPool/main.cpp)
add_test(TestLogger test/TestLogger/main.cpp)
add_test(TestPlugin test/TestPlugin/main.cpp)
add_plugin(Plugin test/TestPlugin/TestServlet.h test/TestPlugin/TestServlet.cpp)

# 工具文件
add_exec(PluginManifestViewer kit/PluginManifestViewer/main.cpp)