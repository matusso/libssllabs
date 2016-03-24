//
// Created by burso on 3/24/16.
//

#include <iostream>
#include "endpoint.h"

int getEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> obj, labsEndpoint_t &endpoint) {
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

    return 0;
}
