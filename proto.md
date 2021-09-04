```c++
#define LOGIN "0"
#define CONN "1"
#define MESSAGE "2"
#define ENROLL "3"
#define DISCONN "4"
#define USRLST "5"
```

### LOGIN 登录

#### 请求：

0

username

password

#### 回应：

0

0 (用户名密码错误) / 1(已在线) / uid($\ge 1$)

### CONN 连接

#### 请求：

1

uid

content ('username connected')

### MESSAGE 消息

#### 请求：

2

uid

content ('username: time \n msg')

### ENROLL 注册

#### 请求：

3

username

password

#### 回应：

3

0 (错误) / uid ($\ge 1$)

### DISCONN 断开连接

#### 请求：

4

uid

content ('username disconnected')

### USRLST 用户列表

#### 回应：

5

userCount

user1 \n user2 \n ...



## SERVER_IP

./chatui/chatroom/config.h

## GOGOGO

make server

./chatui/build-chatroom-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug/chatroom.exe

## Dependency

linux

mysql

jsoncpp