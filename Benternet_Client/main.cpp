#include "mainwindow.h"

#include <QApplication>
#include <thread>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	std::thread recv_msg([&w]() {
		w.incoming_msg();
	});

	w.show();
	return a.exec();
}
