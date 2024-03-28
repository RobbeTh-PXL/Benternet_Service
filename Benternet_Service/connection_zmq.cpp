#include "connection_zmq.h"

connection_zmq::connection_zmq() : zmq_ctx(ZMQ_NUM_IO_THREADS), zmq_sub(zmq_ctx, ZMQ_SUB), zmq_push(zmq_ctx, ZMQ_PUSH) {}

connection_zmq::~connection_zmq() {
	zmq_disconnect();
	zmq_ctx.shutdown();
	zmq_ctx.close();
}

int connection_zmq::zmq_connect() {
	// Connect to server
	try {
		std::cout << "[+] Connecting To: " << ZMQ_SERVER_SUB_ADRESS << std::endl;
		zmq_sub.connect(ZMQ_SERVER_SUB_ADRESS);
		std::cout << "[+] Connecting To: " << ZMQ_SERVER_PUSH_ADRESS << std::endl;
		zmq_push.connect(ZMQ_SERVER_PUSH_ADRESS);
		std::cout << "[+] Connected To Server " << std::endl;
	} catch (const zmq::error_t& e) {
		std::cerr << "[-] ZMQ Error: " << e.what() << std::endl;
		return 1; //ERROR_1
	}

	// Set sub filters
	try {
		zmq_sub.set(zmq::sockopt::subscribe, ZMQ_SUB_FILTER_1);
		//zmq_sub.set(zmq::sockopt::subscribe, "");
	} catch (const zmq::error_t& e) {
		std::cerr << "[-] ZMQ Error: " << e.what() << std::endl;
		return 2; //ERROR_2;
	}

	return 0;
}

int connection_zmq::zmq_disconnect() {
	std::cout << "[+] Disconnecting: " << ZMQ_SERVER_PUSH_ADRESS << std::endl;
	zmq_sub.disconnect(ZMQ_SERVER_SUB_ADRESS);
	std::cout << "[+] Disconnecting: " << ZMQ_SERVER_SUB_ADRESS << std::endl;
	zmq_push.disconnect(ZMQ_SERVER_SUB_ADRESS);
	std::cout << "[+] Closed Connection To Server " << std::endl;

	return 0;
}

int connection_zmq::zmq_listen() {
	while (zmq_sub.handle() != NULL) {
		std::cout << "[+] ZMQ Listening..." << std::endl;
		zmq::recv_result_t result = zmq_sub.recv(zmq_msg);
		//DEBUG
		if (result.has_value()) {
			std::cout << "[+] ZMQ RX: " << std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size()) << std::endl;
			std::cout << "RESPONDING: " << std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size()) << " Received" << std::endl;
			if (zmq_push.handle() != NULL) {
				std::string data = "got>Received: " + std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
				zmq_push.send(zmq::buffer(data), zmq::send_flags::none);
			}
		} else {
			std::cerr << "[-] ZMQ Failed to receive message." << std::endl;
		}
	}

	return 0;
}
