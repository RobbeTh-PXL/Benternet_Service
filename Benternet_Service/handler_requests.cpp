#include "handler_requests.h"
#include <iostream>

handler_requests::handler_requests() {}

handler_requests::~handler_requests() {}

int handler_requests::request_service() {
	if (handle_msg.split_message(request_queue.front()) == 0) {
		request_queue.pop_front();
		// Fetch splitted message
		message_data msg_data = handle_msg.getMsg_data();

		switch (msg_data.op) {
		case 0:
			response_queue.push_back({msg_data.id, translate.translate(msg_data.q, msg_data.source, msg_data.target)});
			break;

		case 1:
			response_queue.push_back({msg_data.id,translate.langs(msg_data.cmd_arg)});
			break;

		case 2:
			response_queue.push_back({msg_data.id, "Not yet implemented"});
			break;

		default:
			response_queue.push_back({msg_data.id, "ERROR"});
			std::cerr << "[-] Switch case out of bounds." << std::endl;
			break;
		}

		const auto& last_response_entry = response_queue.back();
		std::cout << "ID: " << last_response_entry.id << " Response: " << last_response_entry.response << std::endl;

	} else {
		std::cerr << "[-] Error splitting message." << std::endl;
		return 1;
	}

	return 0;
}

void handler_requests::addData_queue_item(std::string entry)
{
	request_queue.push_back(entry);
}

response_data handler_requests::getResponse_queue_item() const
{
	if (!response_queue.empty()) {
		return response_queue.front();
	} else {
		// Handle the case when the list is empty
		throw std::runtime_error("Response queue is empty.");
	}
}

void handler_requests::popResponse_queue_item() {
	response_queue.pop_front();
}
