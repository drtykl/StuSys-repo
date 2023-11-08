#pragma once
#include<string>
#include<iostream>
using string = std::string;

class Student {
public:
	Student() :number(0),age(0),name(""),gender(""){}
	Student(int number, string name, string gender, int age) :number(number),
		name(name),gender(gender),age(age) {}
	void set_number(int number);
	void set_name(string name);
	void set_gender(string gender);
	void set_age(int age);
	int get_number();
	string get_name();
	string get_gender();
	int get_age();
private:
	int number = 0;//学号
	string name = "";//姓名
	string gender = "";//性别
	int age = 0;//年龄
};

