#include <QCoreApplication>

#include "service_translator.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	service_translator translator;

	translator.zmq_connect();
	translator.zmq_listen();

	return a.exec();
}
