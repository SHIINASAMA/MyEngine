set(native_src
        src/native/Socket.h)

if (UNIX)
    list(APPEND native_src src/native/SocketLinux.cpp)
elseif (WIN32)
elseif(APPLE)
endif()

add_library(MyEngineLib ${native_src})

function(add_test exec_name src)
    add_executable(${exec_name} ${src})
    target_link_libraries(${exec_name} ${MyEngineLib})
endfunction(add_test)

add_test(NativeLinux test/NativeLinux.cpp)