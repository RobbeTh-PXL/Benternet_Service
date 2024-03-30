#include <QCoreApplication>

#include "connection_zmq.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	connection_zmq zmq_network;

	//zmq_network.connect();
	//zmq_network.listen();

	return a.exec();
}
