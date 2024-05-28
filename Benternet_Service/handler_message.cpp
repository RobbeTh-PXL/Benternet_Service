#include "handler_message.h"
#include <iostream>

handler_message::handler_message() {}

handler_message::~handler_message() {}

int handler_message::split_message(std::string message) {

	// Find the position of the first '>' (ID)
	size_t pos1 = message.find('>');
	if (pos1 == std::string::npos) {
		std::cerr << "Invalid input format! 1" << std::endl;
		return 1;
	}

	// Find the position of the second '>' (SOURCE)
	size_t pos2 = message.find('>', pos1 + 1);
	if (pos2 == std::string::npos) {
		std::cerr << "Invalid input format! 2" << std::endl;
		return 1;
	}

	// Find the position of the dash '-' (TARGET)
	size_t dashPos = message.find('-', pos2 + 1);
	if (dashPos == std::string::npos || dashPos <= pos2) {
		std::cerr << "Invalid input format! dash" << std::endl;
		return 1;
	}

	// Find the position of the third '>' (Q)
	size_t pos3 = message.find('>', pos2 + 1);
	if (pos3 == std::string::npos) {
		std::cerr << "Invalid input format! 3" << std::endl;
		return 1;
	}

	msg_data.id = message.substr(pos1 + 1, pos2 - pos1 - 1);
	msg_data.source = message.substr(pos2 + 1, dashPos - pos2 - 1);
	msg_data.target = message.substr(dashPos + 1, pos3 - dashPos - 1);
	msg_data.q = message.substr(pos3 + 1); // Extract the sentence

	return 0;
}

message_data handler_message::getMsg_data() const
{
	return msg_data;
}
