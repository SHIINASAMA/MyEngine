set(engine_src
        src/native/Socket.h
        src/socket/TcpClient.h
        src/socket/TcpClient.cpp
        src/socket/TcpServer.h src/socket/TcpServer.cpp)

if (UNIX)
    list(APPEND engine_src src/native/SocketLinux.cpp)
elseif (WIN32)
elseif (APPLE)
endif ()

add_library(MyEngineLib ${engine_src})

function(add_test exec_name src)
    add_executable(${exec_name} ${src})
    target_link_libraries(${exec_name} MyEngineLib)
endfunction(add_test)

add_test(TestTcpClient test/TestTcpClient/main.cpp)
add_test(TestTcpServer test/TestTcpServer/main.cpp)