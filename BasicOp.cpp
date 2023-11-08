#include"BasicOp.h"

BasicOp* BasicOp::op = nullptr;

BasicOp* BasicOp::GetOp()
{
	if (op == nullptr) {
		op = new BasicOp();
	}
	return op;
}

BasicOp* BasicOp::GetOp(string host, string user, string pwd, string db_name, int port)
{
	if (op != nullptr) {
		delete op;
	}
	op = new BasicOp();
	if (op->db_connect(host, user, pwd, db_name, port))return op;
	delete op;
	op = nullptr;
	return op;
}

void BasicOp::DeleteOp()
{
	if (op != nullptr) {
		delete op;
		op = nullptr;
	}
}

BasicOp::BasicOp(){}

BasicOp::~BasicOp(){}

Student* BasicOp::number_search(int number)
{
	string sql;
	Student* student = nullptr;
	sql = "select * from student where number=";
	sql += std::to_string(number);
	if (conn.query(sql)) {
		if (conn.next()) {
			string name = conn.value(1);
			string gender = conn.value(2);
			int age = atoi(conn.value(3).c_str());
			student = new Student(number, name, gender, age);
		}
	}
	return student;
}

std::vector<Student> BasicOp::name_search(string name)
{
	string sql;
	std::vector<Student>ret;
	sql = "select * from student where name=\"" + name+"\"";
	if (conn.query(sql)) {
		while (conn.next()) {
			int number = atoi(conn.value(0).c_str());
			string gender = conn.value(2);
			int age = atoi(conn.value(3).c_str());
			Student stu(number, name, gender, age);
			ret.push_back(stu);
		}
	}
	return ret;
}

std::vector<Student> BasicOp::all_search()
{
	string sql;
	std::vector<Student>ret;
	sql = "select * from student";
	if (conn.query(sql)) {
		while (conn.next()) {
			int number = atoi(conn.value(0).c_str());
			string name = conn.value(1);
			string gender = conn.value(2);
			int age = atoi(conn.value(3).c_str());
			Student stu(number, name, gender, age);
			ret.push_back(stu);
		}
	}
	return ret;
}

bool BasicOp::add(int number, string name, string gender, int age)
{
	string sql;
	sql = "insert into student set number =";
	sql += std::to_string(number);
	sql += ",name =\"" + name + "\"";
	sql += ",gender =\"" + gender + "\"";
	sql += ",age =";
	sql += std::to_string(age);
	return conn.update(sql);
}

bool BasicOp::erase(int number)
{
	string sql;
	sql = "delete from student where number =";
	sql += std::to_string(number);
	return conn.update(sql);
}

bool BasicOp::modify(int number, string name, string gender, int age)
{
	string sql;
	sql = "update student set number =";
	sql += std::to_string(number);
	sql += ",name =\"" + name + "\"";
	sql += ",gender =\"" + gender + "\"";
	sql += ",age =";
	sql += std::to_string(age);
	sql += " where number =";
	sql += std::to_string(number);
	return conn.update(sql);
}

bool BasicOp::login(string account, string password)
{
	string sql;
	sql = "select password from user where account = \"" + account + "\"";
	if (conn.query(sql)) {
		if (conn.next()) {
			if(password == string(conn.value(0)))return true;
		}
	}
	return false;
}

bool BasicOp::db_connect(string host, string user, string pwd, string db_name, int port)
{
	return conn.connect(host, user, pwd, db_name, port);
}
