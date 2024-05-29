#include "shared_control.h"

shared_control::shared_control() {}
shared_control::~shared_control() {}

std::mutex shared_control::request_queue_mutex;
std::mutex shared_control::response_queue_mutex;

void shared_control::lock_request_queue() {std::lock_guard<std::mutex> lock(request_queue_mutex);}
void shared_control::unlock_request_queue() {std::lock_guard<std::mutex> unlock(request_queue_mutex);}

void shared_control::lock_response_queue() {std::lock_guard<std::mutex> lock(response_queue_mutex);}
void shared_control::unlock_response_queue() {std::lock_guard<std::mutex> lock(response_queue_mutex);}
