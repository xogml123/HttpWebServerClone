#include "ParseFile.hpp"
#include "Server.hpp"
#include "Webserv.hpp"
#include <iostream>

int main(int argc, char *args[])
{
	ParseFile parser;

	if (argc > 1 && parser.checkFileName(args[1]) == false)
	{
		std::cout << "checkFileName\n";
		return EXIT_FAILURE;
	}

	try
	{
		parser.doParsing(argc > 1 ? args[1] : DEFAULT_FILE);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}


    Webserv webserv(parser);
    webserv.createServers();

	return EXIT_SUCCESS;
}
