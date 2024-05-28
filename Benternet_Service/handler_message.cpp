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

	// Find the position of the dash '-' (TARGET/CMD)
	size_t dashPos = message.find('-', pos2 + 1);
	if (dashPos == std::string::npos) {
		std::cout << "No dash found, looking for cmd" << std::endl;

		size_t cmdPos = message.find(LIST_LANG_CMD, pos2 + 1);
		if (cmdPos != std::string::npos) {
			// Find the position of the third '>' (CMD_ARG)
			size_t pos3 = message.find('>', pos2 + 1);
			if (pos3 == std::string::npos) {
				std::cerr << "Invalid input format! 3" << std::endl;
				return 1;
			}
			msg_data.op = 1;
			msg_data.id = message.substr(pos1 + 1, pos2 - pos1 - 1);
			msg_data.cmd = message.substr(pos2 + 1, sizeof(LIST_LANG_CMD) - 1);
			msg_data.cmd_arg = message.substr(pos3 + 1);
			std::cout << "CMD list lang found" << std::endl;
			return 0;
		} else {
			cmdPos = message.find(DETECT_LANG_CMD, pos2 + 1);
			if (cmdPos != std::string::npos) {
				// Find the position of the third '>' (CMD_ARG)
				size_t pos3 = message.find('>', pos2 + 1);
				if (pos3 == std::string::npos) {
					std::cerr << "Invalid input format! 3" << std::endl;
					return 1;
				}
				msg_data.op = 2;
				msg_data.id = message.substr(pos1 + 1, pos2 - pos1 - 1);
				msg_data.cmd = message.substr(pos2 + 1, sizeof(DETECT_LANG_CMD) - 1);
				msg_data.cmd_arg = message.substr(pos3 + 1);
				std::cout << "CMD detect lang found" << std::endl;
				return 0;

			}

			return 1;
		}

		std::cerr << "Invalid input format! dash/cmd" << std::endl;
		return 1;
	}

	// Find the position of the third '>' (Q)
	size_t pos3 = message.find('>', pos2 + 1);
	if (pos3 == std::string::npos) {
		std::cerr << "Invalid input format! 3" << std::endl;
		return 1;
	}

	msg_data.op = 0;
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
