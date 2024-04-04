#include "service_translator.h"
#include <iostream>

service_translator::service_translator() {}

service_translator::~service_translator() {}

std::string service_translator::translate(std::string q, std::string source, std::string target) {

	// Create an HTTP client
	std::cout << "[+] Translation Started" << std::endl;
	web::http::client::http_client client(U(TRANS_SERVER));

	// Prepare the request data
	web::uri_builder builder(U(TRANS_SERVER_ENDPOINT));
	builder.append_query(U("q"), U(q));
	builder.append_query(U("source"), U(source));
	builder.append_query(U("target"), U(target));
	builder.append_query(U("format"), U(TRANS_FORMAT));

	// Build the request URI
	web::uri request_uri = builder.to_uri();

	// Prepare the request headers
	web::http::http_request request(web::http::methods::POST);
	request.headers().set_content_type(U("application/x-www-form-urlencoded"));
	request.headers().add(U("Accept"), U("application/json"));

	// Set the request URI
	request.set_request_uri(request_uri);

	std::string translated_text = "";

	try {
		// Send the request asynchronously
		client.request(request).then([](web::http::http_response response) {
		   // Check if the request was successful (status code 200)
		   if (response.status_code() == web::http::status_codes::OK) {
			   // Extract and print the response body
			   return response.extract_json();
		   } else {
			   // If the request failed, set an error
			   throw std::runtime_error("Request failed with status code " + std::to_string(response.status_code()));

			   // Return empty json
			   //std::cerr << "Request failed with status code " << response.status_code() << std::endl;
			   //return pplx::task_from_result(web::json::value());
		   }
		}).then([&translated_text](web::json::value responseBody) {
			// Print the response body
			std::cout << responseBody.serialize() << std::endl;
			// Check if the response contains a "translation" field
			if (responseBody.has_field(U(TRANS_RESULT_FIELD))) {
				// Extract the translated text
				translated_text = responseBody[U(TRANS_RESULT_FIELD)].as_string();
			} else {
				// Print an error message if the response does not contain a "translation" field
				throw std::runtime_error("Translation not found in response");
			}
		}).wait();

	} catch (const std::exception& e) {
		// Handle exceptions thrown during asynchronous operations
		std::cerr << "An error occurred: " << e.what() << std::endl;
		// Set translated text to error
		translated_text = e.what();
	}

	return translated_text;
}
