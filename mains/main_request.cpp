#include "../inc/Request.hpp"

int main()
{
	char data[] = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nAccept: application/json\r\n\r\n";
	size_t size = sizeof(data) - 1;
	Request cf;
	try{
		cf.feed(data, size);
		cf.printMessage();
	}
	catch(std::exception &e)
	{
		std::cout<<e.what()<<std::endl;
	}
	return 0;
}
