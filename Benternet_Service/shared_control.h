#ifndef SHARED_CONTROL_H
#define SHARED_CONTROL_H

#include <mutex>

class shared_control
{
public:
	shared_control();
	~shared_control();

	static void lock_request_queue();
	static void unlock_request_queue();

	static void lock_response_queue();
	static void unlock_response_queue();

private:
	static std::mutex request_queue_mutex;
	static std::mutex response_queue_mutex;
};

#endif // SHARED_CONTROL_H
