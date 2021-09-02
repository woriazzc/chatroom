#include "mysqlControler.h"

mysqlControler::mysqlControler(){
    ifstream in;
    in.open("./utils/config.json");
    assert(in.is_open());
    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(in, root)){
        printf("Config read Error.");
        exit(-1);
    }
    const char* DB_HOST = root["DB_HOST"].asCString();
    const char* DB_USER = root["DB_USER"].asCString();
    const char* DB_PWD = root["DB_PASSWORD"].asCString();
    const char* DB_NAME = root["DB_NAME"].asCString();
    unsigned DB_PORT = root["DB_PORT"].asUInt();

    sql = new MYSQL;

    mysql_init(sql);
    mysql_real_connect(sql, DB_HOST, DB_USER, DB_PWD, DB_NAME, DB_PORT, NULL, 0);
}

mysqlControler::~mysqlControler(){
    mysql_close(sql);
    delete(sql);
}

int mysqlControler::isValidUser(const char *user, const char *pwd){
    char qry[500];
    memset(qry, 0, sizeof(qry));
    sprintf(qry, "SELECT uid FROM user WHERE username='%s' AND password='%s'", user, pwd);
    mysql_query(sql, qry);
    MYSQL_RES *result = mysql_store_result(sql);
    int flg = 0;
    if(result && (mysql_num_rows(result)))
        flg = 1;
    mysql_free_result(result);
    return flg;
}

int mysqlControler::insertUser(const char *user, const char *pwd){
    char qry[500];
    memset(qry, 0, sizeof(qry));
    sprintf(qry, "INSERT INTO user VALUES(NULL, '%s', '%s')", user, pwd);
    return mysql_query(sql, qry) == 0;
}
