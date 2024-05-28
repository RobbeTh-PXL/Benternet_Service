#ifndef HANDLER_MESSAGE_H
#define HANDLER_MESSAGE_H

#include <string>

// Private struct
struct message_data {
	std::string id, q, source, target, cmd;
};

class handler_message
{
public:
	handler_message();
	~handler_message();

	int split_message(std::string message);
	message_data getMsg_data() const;

private:
	message_data msg_data;
};

#endif // HANDLER_MESSAGE_H
