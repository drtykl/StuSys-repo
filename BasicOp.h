#pragma once
#include"MysqlConn.h"
#include"Student.h"
#include<vector>


//µ¥ÀýÄ£Ê½
class BasicOp {
public:
    static BasicOp* GetOp();
    static BasicOp* GetOp(string host, string user, string pwd, string db_name, int port = 3306);
    static void DeleteOp();
    Student* number_search(int number);
    std::vector<Student> name_search(string name);
    std::vector<Student> all_search();
    bool add(int number, string name, string gender, int age);
    bool erase(int number);
    bool modify(int number, string name, string gender, int age);
    bool login(string account, string password);
private:
    static BasicOp* op;
    bool db_connect(string host, string user, string pwd, string db_name, int port = 3306);
    BasicOp();
    ~BasicOp();
    MysqlConn conn;
};
