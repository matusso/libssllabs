//
// Created by burso on 3/22/16.
//

#include <iostream>
#include "../include/ssllabs/ssllabs.h"
#include "../include/rapidjson/document.h"

int SSLlabs::analyze(const std::string domain, const std::string &data) {
    std::string command("/analyze?host=");

    command += domain;
    curl_read(command, data);
    return 0;
}

int SSLlabs::analyze(const std::string domain, labsReport_t &report) {
    std::string command("/analyze?host=");
    std::string data = {};
    rapidjson::Document document;

    command += domain;
    curl_read(command, data);

    if (document.Parse<0>(data.c_str()).HasParseError()) {
        std::cerr << "could not parse json document\n";
        return -1;
    }

    if (document.HasMember("host") && document["host"].IsString()) {
        report.Host.assign(document["host"].GetString());
    }

    if (document.HasMember("port") && document["port"].IsInt()) {
        report.Port = document["port"].GetInt();
    }

    if (document.HasMember("protocol") && document["protocol"].IsString()) {
        report.Protocol.assign(document["protocol"].GetString());
    }

    if (document.HasMember("isPublic") && document["isPublic"].IsBool()) {
        report.IsPublic = document["isPublic"].GetBool();
    }

    if (document.HasMember("status") && document["status"].IsString()) {
        report.Status.assign(document["status"].GetString());
    }

    if (document.HasMember("startTime") && document["startTime"].IsInt64()) {
        report.StartTime = document["startTime"].GetInt64();
    }

    if (document.HasMember("testTime") && document["testTime"].IsInt64()) {
        report.TestTime = document["testTime"].GetInt64();
    }

    if (document.HasMember("engineVersion") && document["engineVersion"].IsString()) {
        report.EngineVersion.assign(document["engineVersion"].GetString());
    }

    if (document.HasMember("criteriaVersion") && document["criteriaVersion"].IsString()) {
        report.CriteriaVersion.assign(document["criteriaVersion"].GetString());
    }

    return 0;
}