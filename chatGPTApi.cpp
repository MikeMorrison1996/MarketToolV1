#include "ChatGPTApi.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

std::string CallChatGPT(const std::string& inputText) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string apiKey = "Bearer YOUR_OPENAI_API_KEY";  // Replace with your actual API key
        std::string url = "https://api.openai.com/v1/chat/completions";

        // Construct the JSON body for the request
        nlohmann::json requestBody = {
                {"model", "gpt-4"},
                {"messages", {
                                  {{"role", "system"}, {"content", "You are a helpful assistant."}},
                                  {{"role", "user"}, {"content", inputText}}
                          }}
        };

        std::string postData = requestBody.dump();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
