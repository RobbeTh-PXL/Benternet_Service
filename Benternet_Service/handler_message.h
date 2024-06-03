#ifndef HANDLER_MESSAGE_H
#define HANDLER_MESSAGE_H

#include <string>
#include <list>

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
	const std::list<std::string> lang_cmd = {
		"ar", "az", "bg", "bn", "ca", "cs", "da", "de", "el", "en", "eo", "es", "et", "fa", "fi", "fr",
		"ga", "he", "hi", "hu", "id", "it", "ja", "ko", "lt", "lv", "ms", "nb", "nl", "pl", "pt", "ro",
		"ru", "sk", "sl", "sq", "sv", "th", "tl", "tr", "uk", "ur", "zh", "zt"
	};

	const std::string lyrics = "Never gonna give you up Never gonna let you down Never gonna run around and desert you Never gonna make you cry Never gonna say goodbye Never gonna tell a lie and hurt you";
};

#endif // HANDLER_MESSAGE_H
