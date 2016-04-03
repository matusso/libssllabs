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

        if (obj.HasMember("hostStartTime") && obj["hostStartTime"].IsInt64()) {
            endpoint.Details.HostStartTime = obj["hostStartTime"].GetInt64();
        }

        if (obj.HasMember("key") && obj["key"].IsObject()) {

        }

        if (obj.HasMember("cert") && obj["cert"].IsObject()) {

        }

        if (obj.HasMember("chain") && obj["chain"].IsObject()) {

        }

        if (obj.HasMember("protocols") && obj["protocols"].IsArray()) {

        }

        if (obj.HasMember("suites") && obj["suites"].IsObject()) {

        }

        if (obj.HasMember("serverSignature") && obj["serverSignature"].IsString()) {
            endpoint.Details.ServerSignature = obj["serverSignature"].GetString();
        }

        if (obj.HasMember("prefixDelegation") && obj["prefixDelegation"].IsBool()) {
            endpoint.Details.PrefixDelegation = obj["prefixDelegation"].GetBool();
        }

        if (obj.HasMember("nonPrefixDelegation") && obj["nonPrefixDelegation"].IsBool()) {
            endpoint.Details.NonPrefixDelegation = obj["nonPrefixDelegation"].GetBool();
        }

        if (obj.HasMember("vulnBeast") && obj["vulnBeast"].IsBool()) {
            endpoint.Details.VulnBeast = obj["vulnBeast"].GetBool();
        }

        if (obj.HasMember("renegSupport") && obj["renegSupport"].IsInt()) {
            endpoint.Details.RenegSupport = obj["renegSupport"].GetInt();
        }

        // * TODO: need to parse stsStatus & sts.. any variable;

        if (obj.HasMember("sessionResumption") && obj["sessionResumption"].IsInt()) {
            endpoint.Details.SessionResumption = obj["sessionResumption"].GetInt();
        }

        if (obj.HasMember("compressionMethods") && obj["compressionMethods"].IsInt()) {
            endpoint.Details.CompressionMethods = obj["compressionMethods"].GetInt();
        }

        if (obj.HasMember("supportsNpn") && obj["supportsNpn"].IsBool()) {
            endpoint.Details.SupportsNpn = obj["supportsNpn"].GetInt();
        }

        if (obj.HasMember("sessionTickets") && obj["sessionTickets"].IsInt()) {
            endpoint.Details.SessionTickets = obj["sessionTickets"].GetInt();
        }

        if (obj.HasMember("ocspStapling") && obj["ocspStapling"].IsBool()) {
            endpoint.Details.OcspStapling = obj["ocspStapling"].GetBool();
        }

        if (obj.HasMember("sniRequired") && obj["sniRequired"].IsBool()) {
            endpoint.Details.SniRequired = obj["sniRequired"].GetBool();
        }

        if (obj.HasMember("httpStatusCode") && obj["httpStatusCode"].IsInt()) {
            endpoint.Details.HttpStatusCode = obj["httpStatusCode"].GetInt();
        }

        if (obj.HasMember("supportsRc4") && obj["supportsRc4"].IsBool()) {
            endpoint.Details.SupportsRc4 = obj["supportsRc4"].GetBool();
        }

        if (obj.HasMember("rc4WithModern") && obj["rc4WithModern"].IsBool()) {
            endpoint.Details.Rc4WithModern = obj["rc4WithModern"].GetBool();
        }

        if (obj.HasMember("rc4Only") && obj["rc4Only"].IsBool()) {
            endpoint.Details.Rc4Only = obj["rc4Only"].GetBool();
        }

        if (obj.HasMember("forwardSecrecy") && obj["forwardSecrecy"].IsInt()) {
            endpoint.Details.ForwardSecrecy = obj["forwardSecrecy"].GetInt();
        }

        if (obj.HasMember("sims") && obj["sims"].IsObject()) {

        }

        if (obj.HasMember("heartbleed") && obj["heartbleed"].IsBool()) {
            endpoint.Details.Heartbleed = obj["heartbleed"].GetBool();
        }

        if (obj.HasMember("heartbeat") && obj["heartbeat"].IsBool()) {
            endpoint.Details.Heartbeat = obj["heartbeat"].GetBool();
        }

        if (obj.HasMember("openSslCcs") && obj["openSslCcs"].IsInt()) {
            endpoint.Details.OpenSslCcs = obj["openSslCcs"].GetInt();
        }

        if (obj.HasMember("poodle") && obj["poodle"].IsBool()) {
            endpoint.Details.Poodle = obj["poodle"].GetBool();
        }

        if (obj.HasMember("poodleTls") && obj["poodleTls"].IsInt()) {
            endpoint.Details.PoodleTls = obj["poodleTls"].GetInt();
        }

        if (obj.HasMember("fallbackScsv") && obj["fallbackScsv"].IsBool()) {
            endpoint.Details.FallbackScsv = obj["fallbackScsv"].GetBool();
        }

        if (obj.HasMember("freak") && obj["freak"].IsBool()) {
            endpoint.Details.Freak = obj["freak"].GetBool();
        }

        if (obj.HasMember("hasSct") && obj["hasSct"].IsInt()) {
            endpoint.Details.HasSct = obj["hasSct"].GetInt();
        }

        if (obj.HasMember("dhPrimes") && obj["dhPrimes"].IsArray()) {

        }

        if (obj.HasMember("dhUsesKnownPrimes") && obj["dhUsesKnownPrimes"].IsInt()) {
            endpoint.Details.DhUsesKnownPrimes = obj["dhUsesKnownPrimes"].GetInt();
        }

        if (obj.HasMember("dhYsReuse") && obj["dhYsReuse"].IsBool()) {
            endpoint.Details.DhYsReuse = obj["dhYsReuse"].GetBool();
        }

        if (obj.HasMember("logjam") && obj["logjam"].IsBool()) {
            endpoint.Details.Logjam = obj["logjam"].GetBool();
        }

        if (obj.HasMember("hstsPolicy") && obj["hstsPolicy"].IsObject()) {
            Endpoint::parseHstsPolicy(obj["hstsPolicy"].GetObject(), endpoint.Details.HstsPolicy);
        }

        if (obj.HasMember("hstsPreloads") && obj["hstsPreloads"].IsArray()) {

        }

        if (obj.HasMember("hpkpPolicy") && obj["hpkpPolicy"].IsObject()) {
            Endpoint::parseHpkpPolicy(obj["hpkpPolicy"].GetObject(), endpoint.Details.HpkpPolicy);
        }

        if (obj.HasMember("hpkpRoPolicy") && obj["hpkpRoPolicy"].IsObject()) {
            Endpoint::parseHpkpPolicy(obj["hpkpRoPolicy"].GetObject(), endpoint.Details.HpkpRoPolicy);
        }

        // * TODO: need to parse drownHosts && drown..;

        return;
    }

    void Endpoint::parseHstsPolicy(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsHstsPolicy_t &hstsPolicy) {

        if (obj.HasMember("LONG_MAX_AGE") && obj["LONG_MAX_AGE"].IsInt64()) {
            hstsPolicy.LONG_MAX_AGE = obj["LONG_MAX_AGE"].GetInt64();
        }

        if (obj.HasMember("header") && obj["header"].IsString()) {
            hstsPolicy.Header.assign(obj["header"].GetString());
        }

        if (obj.HasMember("status") && obj["status"].IsString()) {
            hstsPolicy.Status.assign(obj["status"].GetString());
        }

        if (obj.HasMember("maxAge") && obj["maxAge"].IsInt64()) {
            hstsPolicy.MaxAge = obj["maxAge"].GetInt64();
        }

        if (obj.HasMember("directives") && obj["directives"].IsObject()) {

        }

        return;
    }

    void Endpoint::parseHpkpPolicy(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsHpkpPolicy_t &hpkpPolicy) {

        if (obj.HasMember("status") && obj["status"].IsString()) {
            hpkpPolicy.Status.assign(obj["status"].GetString());
        }

        if (obj.HasMember("pins") && obj["pins"].IsArray()) {

        }

        if (obj.HasMember("matchedPins") && obj["matchedPins"].IsArray()) {

        }

        if (obj.HasMember("directives") && obj["directives"].IsObject()) {

        }

        return;
    }


}