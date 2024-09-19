#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

// Write callback for cURL to store the response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Function to call Hugging Face API (use your model, e.g., FinBERT or any other)
std::string CallHuggingFace(const std::string& inputText, const std::string& huggingFaceApiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        // Define the Hugging Face model's API endpoint
        std::string url = "https://api-inference.huggingface.co/models/ProsusAI/finbert";

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + huggingFaceApiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Input for the sentiment anal///ysis
        std::string postData = "{\"inputs\": \"" + inputText + "\"}";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Point to the CA certificate file (for SSL verification)
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/Users/Bigmi/CLionProjects/MarketTool/certs/cacert.pem");

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}
