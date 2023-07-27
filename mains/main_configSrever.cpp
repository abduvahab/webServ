#include "../inc/ConfigParse.hpp"

int main()
{
	ConfigParse cf;
	try{
		// cf.file_to_map("./config/default.config");
		cf.createCluster("./config/default.config");
		// cf.creatServer();
		//  cf.conf_print();
	}
	catch(std::exception &e)
	{
		std::cout<<e.what()<<std::endl;
	}
	return 0;
}