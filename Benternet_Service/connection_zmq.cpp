#include "connection_zmq.h"
#include <iostream>

connection_zmq::connection_zmq() : ctx(ZMQ_NUM_IO_THREADS), sub(ctx, ZMQ_SUB), push(ctx, ZMQ_PUSH) {}

connection_zmq::~connection_zmq() {
	disconnect();
	ctx.shutdown();
	ctx.close();
}

int connection_zmq::connect() {
	// Connect to server
	try {
		std::cout << "[+] Connecting To: " << ZMQ_SERVER_SUB_ADRESS << std::endl;
		sub.connect(ZMQ_SERVER_SUB_ADRESS);
		std::cout << "[+] Connecting To: " << ZMQ_SERVER_PUSH_ADRESS << std::endl;
		push.connect(ZMQ_SERVER_PUSH_ADRESS);
		std::cout << "[+] Connected To Server " << std::endl;
	} catch (const zmq::error_t& e) {
		std::cerr << "[-] ZMQ Error: " << e.what() << std::endl;
		return 1; //ERROR_1
	}

	// Set sub filters
	try {
		sub.set(zmq::sockopt::subscribe, ZMQ_SUB_FILTER_1);
		//zmq_sub.set(zmq::sockopt::subscribe, "");
	} catch (const zmq::error_t& e) {
		std::cerr << "[-] ZMQ Error: " << e.what() << std::endl;
		return 2; //ERROR_2;
	}

	return 0;
}

int connection_zmq::disconnect() {
	std::cout << "[+] Disconnecting: " << ZMQ_SERVER_PUSH_ADRESS << std::endl;
	sub.disconnect(ZMQ_SERVER_SUB_ADRESS);
	std::cout << "[+] Disconnecting: " << ZMQ_SERVER_SUB_ADRESS << std::endl;
	push.disconnect(ZMQ_SERVER_SUB_ADRESS);
	std::cout << "[+] Closed Connection To Server " << std::endl;

	return 0;
}

int connection_zmq::listen() {
	while (sub.handle() != NULL) {
		std::cout << "[+] ZMQ Listening..." << std::endl;
		zmq::recv_result_t result = sub.recv(zmq_msg);
		//DEBUG
		if (result.has_value()) {
			std::cout << "[+] ZMQ RX: " << std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size()) << std::endl;
			std::cout << "RESPONDING: " << std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size()) << " Received" << std::endl;
			if (push.handle() != NULL) {
				std::string data = "got>Received: " + std::string(static_cast<char*>(zmq_msg.data()), zmq_msg.size());
				push.send(zmq::buffer(data), zmq::send_flags::none);
			}
		} else {
			std::cerr << "[-] ZMQ Failed to receive message." << std::endl;
		}
	}

	return 0;
}

int connection_zmq::split_message(std::string message) {

	// Find the first occurrence of '>'
	size_t pos1 = message.find('>');
	if (pos1 != std::string::npos) {
		// Extract user
		msg_data.id = message.substr(0, pos1);

		// Find the second occurrence of '>'
		size_t pos2 = message.find('>', pos1 + 1);
		if (pos2 != std::string::npos) {
			// Extract source language and target language
			std::string lang = message.substr(pos1 + 1, pos2 - pos1 - 1);
			size_t hyphenPos = lang.find('-');
			if (hyphenPos != std::string::npos) {
				msg_data.source = lang.substr(0, hyphenPos);
				msg_data.target = lang.substr(hyphenPos + 1);
			}

			// Extract query
			msg_data.q = message.substr(pos2 + 1);

		} else {
			// Error: Second '>' not found
			std::cerr << "Error: Second '>' not found." << std::endl;
			return -1;
		}
	} else {
		// Error: First '>' not found
		std::cerr << "Error: First '>' not found." << std::endl;
		return -1;
	}

	return 0;
}
