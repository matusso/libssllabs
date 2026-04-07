#include "parsers.h"

#include <iostream>

#include <rapidjson/document.h>

#include "endpoint.h"

namespace {

int parseJsonObject(std::string_view json, rapidjson::Document &document) {
    if (document.Parse(json.data(), json.size()).HasParseError() || !document.IsObject()) {
        std::cerr << "could not parse json document\n";
        return -1;
    }

    return 0;
}

} // namespace

namespace ssllabs::detail {

int parseInfoResponse(std::string_view json, labsInfo_t &info) {
    rapidjson::Document document;
    if (parseJsonObject(json, document) != 0) {
        return -1;
    }

    info = {};

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
        for (auto itr = document["messages"].GetArray().Begin(); itr != document["messages"].GetArray().End(); ++itr) {
            if (itr->IsString()) {
                info.Messages.push_back(itr->GetString());
            }
        }
    }

    return 0;
}

int parseAnalyzeResponse(std::string_view json, labsReport_t &report) {
    rapidjson::Document document;
    if (parseJsonObject(json, document) != 0) {
        return -1;
    }

    report = {};
    report.RawJson.assign(json.data(), json.size());

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

    if (document.HasMember("statusMessage") && document["statusMessage"].IsString()) {
        report.StatusMessage.assign(document["statusMessage"].GetString());
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

    if (document.HasMember("cacheExpiryTime") && document["cacheExpiryTime"].IsInt64()) {
        report.CacheExpiryTime = document["cacheExpiryTime"].GetInt64();
    }

    if (document.HasMember("certHostnames") && document["certHostnames"].IsArray()) {
        for (auto itr = document["certHostnames"].GetArray().Begin(); itr != document["certHostnames"].GetArray().End(); ++itr) {
            if (itr->IsString()) {
                report.CertHostnames.push_back(itr->GetString());
            }
        }
    }

    if (document.HasMember("endpoints") && document["endpoints"].IsArray()) {
        for (auto itr = document["endpoints"].GetArray().Begin(); itr != document["endpoints"].GetArray().End(); ++itr) {
            if (itr->IsObject()) {
                report.Endpoints.push_back(Endpoint::parseEndpointData(*itr));
            }
        }
    }

    return 0;
}

int parseEndpointResponse(std::string_view json, labsEndpoint_t &endpoint) {
    rapidjson::Document document;
    if (parseJsonObject(json, document) != 0) {
        return -1;
    }

    endpoint = {};
    Endpoint::parseEndpointData(document.GetObject(), endpoint);
    return 0;
}

} // namespace ssllabs::detail
