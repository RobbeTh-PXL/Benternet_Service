#include "service_translator.h"

service_translator::service_translator() {}

service_translator::~service_translator() {}

int service_translator::translate() {

	// Create an HTTP client
	std::cout << "[+] Translation Started" << std::endl;
	web::http::client::http_client client(U(TRANS_SERVER));

	// Prepare the request data
	web::uri_builder builder(U(TRANS_SERVER_ENDPOINT));
	builder.append_query(U("q"), U("closet"));
	builder.append_query(U("source"), U("en"));
	builder.append_query(U("target"), U("nl"));
	builder.append_query(U("format"), U("text"));

	// Build the request URI
	web::uri request_uri = builder.to_uri();

	// Prepare the request headers
	web::http::http_request request(web::http::methods::POST);
	request.headers().set_content_type(U("application/x-www-form-urlencoded"));
	 request.headers().add(U("Accept"), U("application/json"));

	// Set the request URI
	request.set_request_uri(request_uri);

	// Send the request asynchronously
	client.request(request).then([](web::http::http_response response) {
							   // Check if the request was successful (status code 200)
							   if (response.status_code() == web::http::status_codes::OK) {
								   // Extract and print the response body
								   return response.extract_json();
							   } else {
								   // If the request failed, print the status code
								   std::cerr << "Request failed with status code " << response.status_code() << std::endl;
								   return pplx::task_from_result(web::json::value());
							   }
						   }).then([](web::json::value responseBody) {
			// Print the response body
			std::cout << responseBody.serialize() << std::endl;
		}).wait();

	return 0;
}
