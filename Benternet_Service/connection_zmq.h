#ifndef CONNECTION_ZMQ_H
#define CONNECTION_ZMQ_H

#include <iostream>

#include <zmq.hpp>
#define ZMQ_NUM_IO_THREADS 1

#define ZMQ_SERVER_PUSH_ADRESS "tcp://benternet.pxl-ea-ict.be:24041"
#define ZMQ_SERVER_SUB_ADRESS "tcp://benternet.pxl-ea-ict.be:24042"

#define ZMQ_SUB_FILTER_1 "test"

class connection_zmq
{
public:
	connection_zmq();
	~connection_zmq();

	int connect();
	int disconnect();
	int listen();

private:
	zmq::context_t ctx;
	zmq::socket_t sub;
	zmq::socket_t push;
	zmq::message_t zmq_msg;
};

#endif // CONNECTION_ZMQ_H