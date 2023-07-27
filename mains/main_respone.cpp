#include "../inc/Response.hpp"
#include "../inc/ConfigParse.hpp"


int main()
{
	char data[] = "GET /js/test HTTP/1.1\r\nHost: example.com\r\nAccept: application/json\r\n\r\n";
	size_t size = sizeof(data) - 1;
	Request cf;
	try{
		ConfigParse cp;
		cp.createCluster("./config/default.config");
		cf.feed(data, size);
		cf.printMessage();
		std::cout<<"end request_________________________________________\n";
		Response rs;
		rs.setRequest(cf);
		rs.setServer((cp.getServers())[0]);
		rs.BuildResponse();
		rs.response_print();



	}
	catch(std::exception &e)
	{
		std::cout<<e.what()<<std::endl;
	}
	return 0;
}