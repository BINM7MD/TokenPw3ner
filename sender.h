#pragma once
#include <vector>
#include <string>


class Sender {
public:
	std::vector<std::string> Post(std::string token);
	const char *webhook = "WebHook";
};
