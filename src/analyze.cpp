//
// Created by burso on 3/22/16.
//

#include <iostream>
#include "../include/ssllabs/ssllabs.h"
#include "../include/rapidjson/document.h"

int SSLlabs::analyze(const std::string domain, const std::string &data,
                     bool publish, bool startNew, bool fromCache, bool ignoreMismatch) {
    std::string command("/analyze?host=");

    command += domain;
    if (startNew && fromCache) {
        std::cerr << "could not use startNew and fromCache at the same time\n";
        return -1;
    }

    if (publish) {
        command += "&publish=on";
    }

    if (startNew) {
        command += "&startNew=on";
    }

    if (fromCache) {
        command += "&fromCache=on";
    }
    else {
        if (ignoreMismatch) {
            command += "&ignoreMismatch=on";
        }
    }

    return curl_read(command, data);
}

int SSLlabs::analyze(const std::string domain, labsReport_t &report,
                     bool publish, bool startNew, bool fromCache, bool ignoreMismatch) {
    std::string command("/analyze?host=");
    std::string data = {};
    rapidjson::Document document;

    command += domain;
    if (startNew && fromCache) {
        std::cerr << "could not use startNew and fromCache at the same time\n";
        return -1;
    }

    if (publish) {
        command += "&publish=on";
    }

    if (startNew) {
        command += "&startNew=on";
    }

    if (fromCache) {
        command += "&fromCache=on";
    }
    else {
        if (ignoreMismatch) {
            command += "&ignoreMismatch=on";
        }
    }

    if (curl_read(command, data) != 0) {
        return -1;
    }

    if (document.Parse<0>(data.c_str()).HasParseError()) {
        std::cerr << "could not parse json document\n";
        return -1;
    }

    report.RawJson.assign(data);

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

    if (document.HasMember("endpoints") && document["endpoints"].IsArray()) {
        for(auto i = document["endpoints"].GetArray().Begin(); i != document["endpoints"].GetArray().End(); i++) {
            if (i->IsObject()) {
                labsEndpoint_t endpoint;
                auto j = i->GetObject();
                if (j.HasMember("ipAddress") && j["ipAddress"].IsString()) {
                    endpoint.IpAddress.assign(j["ipAddress"].GetString());
                }

                if (j.HasMember("serverName") && j["serverName"].IsString()) {
                    endpoint.ServerName.assign(j["serverName"].GetString());
                }

                if (j.HasMember("statusMessage") && j["statusMessage"].IsString()) {
                    endpoint.StatusMessage.assign(j["statusMessage"].GetString());
                }

                if (j.HasMember("statusDetailsMessage") && j["statusDetailsMessage"].IsString()) {
                    endpoint.StatusDetailMessage.assign(j["statusDetailsMessage"].GetString());
                }

                if (j.HasMember("grade") && j["grade"].IsString()) {
                    endpoint.Grade.assign(j["grade"].GetString());
                }

                if (j.HasMember("gradeTrustIgnored") && j["gradeTrustIgnored"].IsString()) {
                    endpoint.GradeTrustIgnored.assign(j["gradeTrustIgnored"].GetString());
                }

                if (j.HasMember("hasWarnings") && j["hasWarnings"].IsBool()) {
                    endpoint.HasWarnings = j["hasWarnings"].GetBool();
                }

                if (j.HasMember("isExceptional") && j["isExceptional"].IsBool()) {
                    endpoint.IsExceptional = j["isExceptional"].GetBool();
                }

                if (j.HasMember("progress") && j["progress"].IsInt()) {
                    endpoint.Progress = j["progress"].GetInt();
                }

                if (j.HasMember("duration") && j["duration"].IsInt()) {
                    endpoint.Duration = j["duration"].GetInt();
                }

                if (j.HasMember("eta") && j["eta"].IsInt()) {
                    endpoint.Eta = j["eta"].GetInt();
                }

                if (j.HasMember("delegation") && j["delegation"].IsInt()) {
                    endpoint.Delegation = j["delegation"].GetInt();
                }

                report.Endpoints.push_back(endpoint);
            }
        }

    }


    return 0;
}