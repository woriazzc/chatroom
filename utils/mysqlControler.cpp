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
    int uid = 0;
    MYSQL_ROW column;
    if(result && (mysql_num_rows(result))){
        while(column = mysql_fetch_row(result)){
            uid = atoi(column[0]);
        }
    }
    mysql_free_result(result);
    return uid;
}

int mysqlControler::insertUser(const char *user, const char *pwd){
    char qry[500];
    memset(qry, 0, sizeof(qry));
    sprintf(qry, "INSERT INTO user VALUES(NULL, '%s', '%s')", user, pwd);
    if(mysql_query(sql, qry) != 0)
        return 0;
    else
        return mysqlControler::isValidUser(user, pwd);
}

const char * mysqlControler::qryUserName(int uid){
    char qry[500];
    memset(qry, 0, sizeof(qry));
    sprintf(qry, "SELECT username FROM user WHERE uid=%d", uid);
    mysql_query(sql, qry);
    MYSQL_RES *result = mysql_store_result(sql);
    char *user;
    MYSQL_ROW column;
    if(result && (mysql_num_rows(result))){
        while(column = mysql_fetch_row(result)){
            user = column[0];
        }
    }
    return user;
}