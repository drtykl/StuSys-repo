#include "logmenu.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if (BasicOp::GetOp("localhost", "root", "123456", "stusys") == nullptr)exit(1);
	LogMenu w;
	w.show();
	return a.exec();
}
