# MyEngine

这是一个使用 CPP 实现的一个简单的 Servlet Server

## 平台

暂时只支持 <kbd> Linux </kbd>

## 架构

### 主体结构

```text
---------------------
|   CUSTOM SERVLET  | --> 实现 Servlet 响应请求
---------------------
|    APPLICATION    | --> 应用程序层
---------------------
|    HTTP SERVER    | --> 处理简单的 Http 请求
---------------------
|     TCP SOCKET    | --> 通用套接字
---------------------
| Native SOCKET API | --> 抽象出公共接口，可以对不同平台的 Native API 进行封装
---------------------
```

### Native SOCKET API

```text
socket_t
socket()        : socket_t
connect()       : bool
bind()          : bool
listen()        : bool
accept()        : socket_t
close()         : bool
isShutdown()      : bool
setsockopt()    : bool
```

### TCP SERVER

```text
--------------
| Tcp Server |
--------------
| Tcp Client |
--------------
|   Socket   |
--------------
```

### HTTP SERVER

```text
----------------------------------------------
|               Custom Server                |
|--------------------------------------------|     ---------------------
|             |         HTTP ACCEPT          | --> |      PARSER       |
| HTTP SERVER |------------------------------|     |--------------------
|             | HTTP Request | HTTP Response |     |  Worker Interface |
|-------------|------------------------------|     |--------------------
| TCP SERVER  |   accept(), recv(), send()   |     | Socket Connection |
----------------------------------------------     ---------------------
```

### SERVLET

```
------------------------------------------------------
|                   HTTP SERVLET                     |
|----------------------------------------------------|
| HttpServletRequest | HttpServletResponse |         |
|------------------------------------------| SERVLET |
|    HttpRequest     |     HttpResponse    |         |
------------------------------------------------------
```

### APPLICATION

```text
-----------------------------------------
|              MAIN LOOP                |
-----------------------------------------
|          SERVLET CONTROLLER           |
-----------------------------------------
|  Register, Unregister  | Exec Servlet |
-----------------------------------------
```
