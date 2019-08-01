//
// Created by lukas on 06.04.19.
//

#include "API.h"
#include "Hashmap.h"

#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h>


std::string API::request(std::string myurl) {
    Hashmap<std::string, std::string> map;
    std::vector<std::string> str;

    return request(std::move(myurl), false, map, str);
}

std::string
API::request(std::string myurl, bool post, Hashmap<std::string, std::string> &map, std::vector<std::string> &headers) {
    CURL *curl;

    curl = curl_easy_init();

    struct curl_slist *list = nullptr;
    for (int j = 0; j < headers.size(); ++j) {
        list = curl_slist_append(list, headers.at((unsigned long) (j)).c_str());
    }

    std::string readString;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);


        //ssl verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        if (post) {
            std::stringstream poststring;
            poststring << "{";
            for (int i = 0; i < map.size(); i++) {
                poststring << "\"" + map.getKey(i) << "\": \"" + map.getValue(i) << "\"";
                if (i < map.size() - 1) {
                    poststring << ", ";
                }
            }
            poststring << "}";

            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, poststring.str().c_str());
        } else {
            if (map.size() > 0) {
                std::string getstring;
                for (int i = 0; i < map.size(); i++) {
                    getstring += map.getKey(i) + "=" + map.getValue(i);
                    if (i < map.size() - 1) {
                        getstring += "&";
                    }
                }

                myurl += "?" + getstring;
            }
        }

        curl_easy_setopt(curl, CURLOPT_URL, myurl.c_str());


        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

        curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    return readString;
}

size_t API::write_data(void *contents, size_t size, size_t nmemb, FILE *stream) {
    ((std::string *) stream)->append((char *) contents, size * nmemb);
    return size * nmemb;
}
