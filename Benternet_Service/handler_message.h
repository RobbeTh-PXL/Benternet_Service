#ifndef HANDLER_MESSAGE_H
#define HANDLER_MESSAGE_H

#include <string>

#define LIST_LANG_CMD "langs"
#define DETECT_LANG_CMD "detect"

struct message_data {
	int op;
	std::string id, q, source, target, cmd, cmd_arg;
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
