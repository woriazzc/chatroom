#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cassert>
#include <mysql/mysql.h>
#include <json/json.h>

using namespace std;

class mysqlControler{
private:
    MYSQL* sql;
public:
    mysqlControler();
    ~mysqlControler();
    int isValidUser(const char *user, const char *pwd);
    int insertUser(const char *user, const char *pwd);
};