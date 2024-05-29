#ifndef SERVICE_TRANSLATOR_H
#define SERVICE_TRANSLATOR_H

#include <string>

#define TRANS_SERVER "http://localhost:5000"

#define TRANS_SERVER_ENDPOINT "/translate"
#define TRANS_FORMAT "text"
#define TRANS_RESULT_FIELD "translatedText"

#define LANG_SERVER_ENDPOINT "/languages"
#define LANG_RESULT_LIST_ID "code"
#define LANG_RESULT_LIST_ITEMS "targets"

#define DETECT_SERVER_ENDPOINT "/detect"
#define DETECT_RESULT_FIELD_CONF "confidence"
#define DETECT_RESULT_LIST_LANG "language"

class service_translator
{
public:
	service_translator();
	~service_translator();

	std::string translate(std::string q, std::string source, std::string target);
	std::string langs(std::string language);
	std::string detect();
};

#endif // SERVICE_TRANSLATOR_H
