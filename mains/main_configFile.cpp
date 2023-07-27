#include "../inc/ConfigFile.hpp"

int main()
{
	try
	{
		ConfigFile cf("./config/default.config");
		std::string tmp = cf.readFile();
		std::cout<<"name :"<<cf.getName()<<std::endl
				<<"size :"<<cf.getSize()<<std::endl
				<<"content :"<<std::endl<<tmp<<std::endl;
		std::cout<<"size after :"<<tmp.length()<<std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	} 

	return 0;
}