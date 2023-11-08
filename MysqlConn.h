#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
using string = std::string;

class MysqlConn
{
public:
	MysqlConn();
	~MysqlConn();
	bool connect(string host, string user, string pwd, string db_name ,int port = 3306);
	bool update(string sql);
	bool query(string sql);
	bool next();//���ؽ����һ��
	string value(int index);//ÿ����ÿ�е�����
	bool transaction();
	bool commit();
	bool rollback();
	int col_count();
private:
	void free_result();
	MYSQL* m_con = nullptr;
	MYSQL_RES* m_result = nullptr;
	MYSQL_ROW m_row = nullptr;
	int now_count = 0;
};

