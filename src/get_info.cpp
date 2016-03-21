//
// Created by burso on 3/21/16.
//

#include <iostream>
#include "../include/ssllabs/ssllabs.h"
#include "../include/rapidjson/document.h"

int SSLlabs::getInfo(const std::string &info) {
    std::string url(SSLLABS_API_URL);

    url += "/info";
    curl_read(url, info);

    return 0;
}

int SSLlabs::getInfo(labsInfo_t &info) {
    std::string url(SSLLABS_API_URL);
    std::string data = {};
    rapidjson::Document document;

    url += "/info";
    curl_read(url, data);

    if (document.Parse<0>(data.c_str()).HasParseError()) {
        std::cerr << "could not parse json document\n";
        return -1;
    }

    if (document.HasMember("engineVersion") && document["engineVersion"].IsString()) {
        info.EngineVersion.assign(document["engineVersion"].GetString());
    }

    if (document.HasMember("criteriaVersion") && document["criteriaVersion"].IsString()) {
        info.CriteriaVersion.assign(document["criteriaVersion"].GetString());
    }

    if (document.HasMember("clientMaxAssessments") && document["clientMaxAssessments"].IsInt()) {
        info.MaxAssessments = document["clientMaxAssessments"].GetInt();
    }

    if (document.HasMember("currentAssessments") && document["currentAssessments"].IsInt()) {
        info.CurrentAssessments = document["currentAssessments"].GetInt();
    }

    if (document.HasMember("newAssessmentCoolOff") && document["newAssessmentCoolOff"].IsInt64()) {
        info.NewAssessmentCoolOff = document["newAssessmentCoolOff"].GetInt64();
    }

    if (document.HasMember("messages") && document["messages"].IsArray()) {
        for (auto i = document["messages"].GetArray().Begin(); i != document["messages"].GetArray().End(); i++) {
            if (i->IsString()) {
                info.Messages.push_back(i->GetString());
            }
        }
    }


    return 0;
}