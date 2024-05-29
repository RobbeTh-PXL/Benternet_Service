#include <QCoreApplication>

#include "connection_zmq.h"
#include "handler_requests.h"
#include <thread>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	connection_zmq zmq_network;
	handler_requests request;

	zmq_network.connect();

	std::thread zmq_listen([&zmq_network]() {
		zmq_network.listen();
	});

	std::thread zmq_push([&zmq_network]() {
		zmq_network.push_msg();
	});

	std::thread perform_requests([&request]() {
		request.request_service();
	});

	return a.exec();
}
