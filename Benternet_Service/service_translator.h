#ifndef SERVICE_TRANSLATOR_H
#define SERVICE_TRANSLATOR_H

#include <string>

#define TRANS_SERVER "http://localhost:5000"
#define TRANS_SERVER_ENDPOINT "/translate"

#define TRANS_FORMAT "text"
#define TRANS_RESULT_FIELD "translation"

class service_translator
{
public:
	service_translator();
	~service_translator();

	std::string translate(std::string q, std::string source, std::string target);
};

#endif // SERVICE_TRANSLATOR_H
