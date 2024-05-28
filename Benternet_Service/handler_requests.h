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

	int request_service();

	void addData_queue_item(std::string entry);
	response_data getResponse_queue_item() const;
	void popResponse_queue_item();

private:
	handler_message handle_msg;
	service_translator translate;
	std::list<std::string> request_queue;
	std::list<response_data> response_queue;
};

#endif // HANDLER_REQUESTS_H
