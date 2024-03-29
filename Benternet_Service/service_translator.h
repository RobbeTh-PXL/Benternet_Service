#ifndef SERVICE_TRANSLATOR_H
#define SERVICE_TRANSLATOR_H

#include <iostream>

#include <cpprest/http_client.h>

#define TRANS_SERVER "http://localhost:5000"
#define TRANS_SERVER_ENDPOINT "/translate"

class service_translator
{
public:
	service_translator();
	~service_translator();

	int translate();

private:
	std::string translated_text;
};

#endif // SERVICE_TRANSLATOR_H
