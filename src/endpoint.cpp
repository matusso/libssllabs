//
// Created by burso on 3/24/16.
//

#include <iostream>
#include "endpoint.h"

namespace ssllabs {

    int SSLlabs::getEndpointData(const std::string domain, const std::string endpoint, const std::string &data) {
        std::string command = {};

        command = "/getEndpointData?host=" + domain + "&s=" + endpoint;
        return curl_read(command, data);
    }

    int SSLlabs::getEndpointData(const std::string domain, const std::string endpoint, labsEndpoint_t &data) {
        std::string command = {};
        std::string json = {};
        rapidjson::Document document;

        command = "/getEndpointData?host=" + domain + "&s=" + endpoint;
        curl_read(command, json);

        if (document.Parse<0>(json.c_str()).HasParseError()) {
            std::cerr << "could not parse json document\n";
            return -1;
        }

        if (document.IsObject()) {
            Endpoint::parseEndpointData(document.GetObject(), data);
        }

        return 0;
    }

    void Endpoint::parseEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj, labsEndpoint_t &endpoint) {
        if (obj.HasMember("ipAddress") && obj["ipAddress"].IsString()) {
            endpoint.IpAddress.assign(obj["ipAddress"].GetString());
        }

        if (obj.HasMember("serverName") && obj["serverName"].IsString()) {
            endpoint.ServerName.assign(obj["serverName"].GetString());
        }

        if (obj.HasMember("statusMessage") && obj["statusMessage"].IsString()) {
            endpoint.StatusMessage.assign(obj["statusMessage"].GetString());
        }

        if (obj.HasMember("statusDetailsMessage") && obj["statusDetailsMessage"].IsString()) {
            endpoint.StatusDetailMessage.assign(obj["statusDetailsMessage"].GetString());
        }

        if (obj.HasMember("grade") && obj["grade"].IsString()) {
            endpoint.Grade.assign(obj["grade"].GetString());
        }

        if (obj.HasMember("gradeTrustIgnored") && obj["gradeTrustIgnored"].IsString()) {
            endpoint.GradeTrustIgnored.assign(obj["gradeTrustIgnored"].GetString());
        }

        if (obj.HasMember("hasWarnings") && obj["hasWarnings"].IsBool()) {
            endpoint.HasWarnings = obj["hasWarnings"].GetBool();
        }

        if (obj.HasMember("isExceptional") && obj["isExceptional"].IsBool()) {
            endpoint.IsExceptional = obj["isExceptional"].GetBool();
        }

        if (obj.HasMember("progress") && obj["progress"].IsInt()) {
            endpoint.Progress = obj["progress"].GetInt();
        }

        if (obj.HasMember("duration") && obj["duration"].IsInt()) {
            endpoint.Duration = obj["duration"].GetInt();
        }

        if (obj.HasMember("eta") && obj["eta"].IsInt()) {
            endpoint.Eta = obj["eta"].GetInt();
        }

        if (obj.HasMember("delegation") && obj["delegation"].IsInt()) {
            endpoint.Delegation = obj["delegation"].GetInt();
        }

        if (obj.HasMember("details") && obj["details"].IsObject()) {
            parseEndpointDetails(obj["details"].GetObject(), endpoint);
        }

        return;
    }

    labsEndpoint_t Endpoint::parseEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj) {
        labsEndpoint_t endpoint = {};

        parseEndpointData(obj, endpoint);
        return endpoint;
    }

    void Endpoint::parseEndpointDetails(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject & obj, labsEndpoint_t &endpoint) {

        return;
    }


}