#ifndef CONNECTION_ZMQ_H
#define CONNECTION_ZMQ_H

#include "handler_requests.h"

#include <zmq.hpp>
#define ZMQ_NUM_IO_THREADS 1

#define ZMQ_SERVER_PUSH_ADRESS "tcp://benternet.pxl-ea-ict.be:24041"
#define ZMQ_SERVER_SUB_ADRESS "tcp://benternet.pxl-ea-ict.be:24042"

//#define ZMQ_SERVER_PUSH_ADRESS "tcp://localhost:24041"
//#define ZMQ_SERVER_SUB_ADRESS "tcp://localhost:24042"

#define ZMQ_SUB_FILTER_1 "translate?"
#define ZMQ_PUSH_FILTER_1 "translate!"
#define ZMQ_HEARTBEAT_FILTER_1 "translate*"

class connection_zmq
{
public:
	connection_zmq();
	~connection_zmq();

	int connect();
	int disconnect();
	void listen();
	void push_msg();
	void send_heartbeat();

private:
	zmq::context_t ctx;
	zmq::socket_t sub;
	zmq::socket_t push;
	zmq::socket_t heartbeat;
	zmq::message_t zmq_msg;

	handler_requests handler_req;
};

#endif // CONNECTION_ZMQ_H
