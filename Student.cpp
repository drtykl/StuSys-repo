#include"Student.h"

void Student::set_number(int number){
	this->number = number;
}

void Student::set_name(string name){
	this->name = name;
}

void Student::set_gender(string gender)
{
	this->gender = gender;
}

void Student::set_age(int age)
{
	this->age = age;
}

int Student::get_number()
{
	return this->number;
}

string Student::get_name()
{
	return this->name;
}

string Student::get_gender()
{
	return this->gender;
}

int Student::get_age()
{
	return this->age;
}
