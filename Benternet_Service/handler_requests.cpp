#include "handler_requests.h"
#include <iostream>
#include "shared_control.h"

handler_requests::handler_requests() {}

handler_requests::~handler_requests() {}

std::list<std::string> handler_requests::request_queue;
std::list<response_data> handler_requests::response_queue;

void handler_requests::request_service() {
	std::cout << "[+] Request Thread started" << std::endl;
	while (1) {
		shared_control::lock_request_queue();
		if (!request_queue.empty()) {
			std::cout << "handling new request" << std::endl;
			if (handle_msg.split_message(request_queue.front()) == 0) {
				request_queue.pop_front();
				shared_control::unlock_request_queue();
				// Fetch splitted message
				message_data msg_data = handle_msg.getMsg_data();

				shared_control::lock_response_queue();
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

				response_data last_response_entry = response_queue.back();
				std::cout << "ID: " << last_response_entry.id << " Response: " << last_response_entry.response << std::endl;
				shared_control::unlock_response_queue();

			} else {
				std::cerr << "[-] Error splitting message." << std::endl;
			}
		} else {
			continue;
		}
	}

	std::cout << "[-] Request Thread exited" << std::endl;
}

void handler_requests::addRequest_queue_item(std::string entry)
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

int handler_requests::getResponse_queu_size() const {
	return response_queue.size();
}

void handler_requests::popResponse_queue_item() {
	response_queue.pop_front();
}
