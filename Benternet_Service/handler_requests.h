#ifndef HANDLER_REQUESTS_H
#define HANDLER_REQUESTS_H

#include <string.h>
#include <list>

#include "handler_message.h"
#include "service_translator.h"

struct response_data {
	std::string id, response;
};

class handler_requests
{
public:
	handler_requests();
	~handler_requests();

	void request_service();

	void addRequest_queue_item(std::string entry);
	response_data getResponse_queue_item() const;
	int getResponse_queu_size() const;
	void popResponse_queue_item();

private:
	handler_message handle_msg;
	service_translator translate;
	static std::list<std::string> request_queue;
	static std::list<response_data> response_queue;
};

#endif // HANDLER_REQUESTS_H
