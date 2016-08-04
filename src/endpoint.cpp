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
            Endpoint::parseKey(obj["key"].GetObject(), endpoint.Details.Key);
        }

        if (obj.HasMember("cert") && obj["cert"].IsObject()) {
            Endpoint::parseCert(obj["cert"].GetObject(), endpoint.Details.Cert);
        }

        if (obj.HasMember("chain") && obj["chain"].IsObject()) {
            Endpoint::parseChain(obj["chain"].GetObject(), endpoint.Details.Chain);
        }

        if (obj.HasMember("protocols") && obj["protocols"].IsArray()) {
            labsProtocol_t labsProtocol;

            for (auto itr = obj["protocols"].GetArray().Begin(); itr != obj["protocols"].GetArray().End(); itr++) {
                parseProtocosls(itr->GetObject(), labsProtocol);
                endpoint.Details.Protocols.push_back(labsProtocol);
            }
        }

        if (obj.HasMember("suites") && obj["suites"].IsObject()) {
            Endpoint::parseLabsSuites(obj["suites"].GetObject(), endpoint.Details.Suites);
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
            parseSimulationDetails(obj["sims"].GetObject(), endpoint.Details.Sims);
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
            for (auto itr = obj["dhPrimes"].GetArray().Begin(); itr != obj["dhPrimes"].GetArray().End(); itr++) {
                if (itr->IsString()) {
                    endpoint.Details.DhPrimes.push_back(itr->GetString());
                }
            }
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

        // * TODO: need to parse drownHosts;

        if (obj.HasMember("drownErrors") && obj["drownErrors"].IsBool()) {
            endpoint.Details.DrownErrors = obj["drownErrors"].GetBool();
        }

        if (obj.HasMember("drownVulnerable") && obj["drownVulnerable"].IsBool()) {
            endpoint.Details.DrownVulnerable = obj["drownVulnerable"].GetBool();
        }

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

    void Endpoint::parseLabsSuites(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsSuites_t &labsSuites) {


        if (obj.HasMember("preference") && obj["preference"].IsBool()) {
            labsSuites.Preference = obj["preference"].GetBool();
        }

        if (obj.HasMember("list") && obj["list"].IsArray()) {
            labsSuite_t labsSuite;
            for (auto itr = obj["list"].GetArray().Begin(); itr != obj["list"].GetArray().End(); itr++) {
                parseSuitesList(itr->GetObject(), labsSuite);
                labsSuites.List.push_back(labsSuite);
            }
        }
    }

    void Endpoint::parseKey(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsKey_t &labsKey) {

        if (obj.HasMember("size") && obj["size"].IsInt()) {
            labsKey.Size = obj["size"].GetInt();
        }

        if (obj.HasMember("alg") && obj["alg"].IsString()) {
            labsKey.Algorithm.assign(obj["alg"].GetString());
        }

        if (obj.HasMember("debianFlaw") && obj["debianFlaw"].IsBool()) {
            labsKey.DebianFlaw = obj["debianFlaw"].GetBool();
        }

        if (obj.HasMember("strength") && obj["strength"].IsInt()) {
            labsKey.Strength = obj["strength"].GetInt();
        }
    }

    void Endpoint::parseCert(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsCert_t &labsCert) {

        if (obj.HasMember("subject") && obj["subject"].IsString()) {
            labsCert.Subject.assign(obj["subject"].GetString());
        }

        if (obj.HasMember("commonNames") && obj["commonNames"].IsArray()) {
            for (auto itr = obj["commonNames"].GetArray().Begin(); itr != obj["commonNames"].GetArray().End(); itr++) {
                if (itr->IsString()) {
                    labsCert.CommonNames.push_back(itr->GetString());
                }
            }
        }

        if (obj.HasMember("altNames") && obj["altNames"].IsArray()) {
            for (auto itr = obj["altNames"].GetArray().Begin(); itr != obj["altNames"].GetArray().End(); itr++) {
                if (itr->IsString()) {
                    labsCert.AltNames.push_back(itr->GetString());
                }
            }
        }

        if (obj.HasMember("notBefore") && obj["notBefore"].IsInt64()) {
            labsCert.NotBefore = obj["notBefore"].GetInt64();
        }

        if (obj.HasMember("notAfter") && obj["notAfter"].IsInt64()) {
            labsCert.NotAfter = obj["notAfter"].GetInt64();
        }

        if (obj.HasMember("issuerSubject") && obj["issuerSubject"].IsString()) {
            labsCert.IssuerSubject.assign(obj["issuerSubject"].GetString());
        }

        if (obj.HasMember("issuerLabel") && obj["issuerLabel"].IsString()) {
            labsCert.IssuerLabel.assign(obj["issuerLabel"].GetString());
        }

        if (obj.HasMember("sigAlg") && obj["sigAlg"].IsString()) {
            labsCert.SigAlg.assign(obj["sigAlg"].GetString());
        }

        if (obj.HasMember("revocationInfo") && obj["revocationInfo"].IsInt()) {
            labsCert.RevocationInfo = obj["revocationInfo"].GetInt();
        }

        if (obj.HasMember("crlURIs") && obj["crlURIs"].IsArray()) {
            for (auto itr = obj["crlURIs"].GetArray().Begin(); itr != obj["crlURIs"].GetArray().End(); itr++) {
                if (itr->IsString()) {
                    labsCert.CrlURIs.push_back(itr->GetString());
                }
            }
        }

        if (obj.HasMember("ocspURIs") && obj["ocspURIs"].IsArray()) {
            for (auto itr = obj["ocspURIs"].GetArray().Begin(); itr != obj["ocspURIs"].GetArray().End(); itr++) {
                if (itr->IsString()) {
                    labsCert.OcspURIs.push_back(itr->GetString());
                }
            }
        }

        if (obj.HasMember("revocationStatus") && obj["revocationStatus"].IsInt()) {
            labsCert.RevocationStatus = obj["revocationStatus"].GetInt();
        }

        if (obj.HasMember("crlRevocationStatus") && obj["crlRevocationStatus"].IsInt()) {
            labsCert.CrlRevocationStatus = obj["crlRevocationStatus"].GetInt();
        }

        if (obj.HasMember("ocspRevocationStatus") && obj["ocspRevocationStatus"].IsInt()) {
            labsCert.OcspRevocationStatus = obj["ocspRevocationStatus"].GetInt();
        }

        if (obj.HasMember("sgc") && obj["sgc"].IsInt()) {
            labsCert.Sgc = obj["sgc"].GetInt();
        }

        if (obj.HasMember("issues") && obj["issues"].IsInt()) {
            labsCert.Issues = obj["issues"].GetInt();
        }

        if (obj.HasMember("sct") && obj["sct"].IsBool()) {
            labsCert.Sct = obj["sct"].GetBool();
        }

        if (obj.HasMember("mustStaple") && obj["mustStaple"].IsInt()) {
            labsCert.MustStaple = obj["mustStaple"].GetInt();
        }

        if (obj.HasMember("sha1Hash") && obj["sha1Hash"].IsString()) {
            labsCert.Sha1Hash.assign(obj["sha1Hash"].GetString());
        }

        if (obj.HasMember("pinSha256") && obj["pinSha256"].IsString()) {
            labsCert.PinSha256.assign(obj["pinSha256"].GetString());
        }

    }

    void Endpoint::parseChain(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsChain_t &labsChain) {

        if (obj.HasMember("issues") && obj["issues"].IsInt()) {
            labsChain.Issues = obj["issues"].GetInt();
        }

        if (obj.HasMember("certs") && obj["certs"].IsArray()) {
            labsChainCert_t labsChainCert;

            for (auto itr = obj["certs"].GetArray().Begin(); itr != obj["certs"].GetArray().End(); itr++) {
                parseChainCert(itr->GetObject(), labsChainCert);
                labsChain.Certs.push_back(labsChainCert);
            }
        }

    }

    void Endpoint::parseChainCert(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj,
                                  labsChainCert_t &labsChainCert) {

        if (obj.HasMember("subject") && obj["subject"].IsString()) {
            labsChainCert.Subject.assign(obj["subject"].GetString());
        }

        if (obj.HasMember("label") && obj["label"].IsString()) {
            labsChainCert.Label.assign(obj["label"].GetString());
        }

        if (obj.HasMember("notBefore") && obj["notBefore"].IsInt64()) {
            labsChainCert.NotBefore = obj["notBefore"].GetInt64();
        }

        if (obj.HasMember("notAfter") && obj["notAfter"].IsInt64()) {
            labsChainCert.NotAfter = obj["notAfter"].GetInt64();
        }

        if (obj.HasMember("issuerSubject") && obj["issuerSubject"].IsString()) {
            labsChainCert.IssuerSubject.assign(obj["issuerSubject"].GetString());
        }

        if (obj.HasMember("issuerLabel") && obj["issuerLabel"].IsString()) {
            labsChainCert.IssuerLabel.assign(obj["issuerLabel"].GetString());
        }

        if (obj.HasMember("sigAlg") && obj["sigAlg"].IsString()) {
            labsChainCert.SigAlg.assign(obj["sigAlg"].GetString());
        }

        if (obj.HasMember("issues") && obj["issues"].IsInt()) {
            labsChainCert.Issues = obj["issues"].GetInt();
        }

        if (obj.HasMember("keyAlg") && obj["keyAlg"].IsString()) {
            labsChainCert.KeyAlg.assign(obj["keyAlg"].GetString());
        }

        if (obj.HasMember("keySize") && obj["keySize"].IsInt()) {
            labsChainCert.KeySize = obj["keySize"].GetInt();
        }

        if (obj.HasMember("keyStrength") && obj["keyStrength"].IsInt()) {
            labsChainCert.KeyStrength = obj["keyStrength"].GetInt();
        }

        if (obj.HasMember("revocationStatus") && obj["revocationStatus"].IsInt()) {
            labsChainCert.RevocationStatus = obj["revocationStatus"].GetInt();
        }

        if (obj.HasMember("crlRevocationStatus") && obj["crlRevocationStatus"].IsInt()) {
            labsChainCert.CrlRevocationStatus = obj["crlRevocationStatus"].GetInt();
        }

        if (obj.HasMember("ocspRevocationStatus") && obj["ocspRevocationStatus"].IsInt()) {
            labsChainCert.OcspRevocationStatus = obj["ocspRevocationStatus"].GetInt();
        }

        if (obj.HasMember("sha1Hash") && obj["sha1Hash"].IsString()) {
            labsChainCert.Sha1Hash.assign(obj["sha1Hash"].GetString());
        }

        if (obj.HasMember("pinSha256") && obj["pinSha256"].IsString()) {
            labsChainCert.PinSha256.assign(obj["pinSha256"].GetString());
        }

        if (obj.HasMember("raw") && obj["raw"].IsString()) {
            labsChainCert.Raw.assign(obj["raw"].GetString());
        }
    }

    void Endpoint::parseSuitesList(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsSuite_t &labsSuite) {

        if (obj.HasMember("id") && obj["id"].IsInt()) {
            labsSuite.Id = obj["id"].GetInt();
        }

        if (obj.HasMember("name") && obj["name"].IsString()) {
            labsSuite.Name.assign(obj["name"].GetString());
        }

        if (obj.HasMember("cipherStrength") && obj["cipherStrength"].IsInt()) {
            labsSuite.CipherStrength = obj["cipherStrength"].GetInt();
        }

        if (obj.HasMember("dhStrength") && obj["dhStrength"].IsInt()) {
            labsSuite.DhStrength = obj["dhStrength"].GetInt();
        }

        if (obj.HasMember("dhP") && obj["dhP"].IsInt()) {
            labsSuite.DhP = obj["dhP"].GetInt();
        }

        if (obj.HasMember("dhG") && obj["dhG"].IsInt()) {
            labsSuite.DhG = obj["dhG"].GetInt();
        }

        if (obj.HasMember("dhYs") && obj["dhYs"].IsInt()) {
            labsSuite.DhYs = obj["dhYs"].GetInt();
        }
    }

    void Endpoint::parseProtocosls(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj, labsProtocol_t &labsProtocol) {

        if (obj.HasMember("id") && obj["id"].IsInt()) {
            labsProtocol.Id = obj["id"].GetInt();
        }

        if (obj.HasMember("name") && obj["name"].IsString()) {
            labsProtocol.Name.assign(obj["name"].GetString());
        }

        if (obj.HasMember("version") && obj["version"].IsString()) {
            labsProtocol.Version.assign(obj["version"].GetString());
        }
    }

    void Endpoint::parseSimulationResults(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj,
                                    labsSimulation_t &labsSimulation) {

        if (obj.HasMember("errorCode") && obj["errorCode"].IsInt()) {
            labsSimulation.ErrorCode = obj["errorCode"].GetInt();
        }

        if (obj.HasMember("attempts") && obj["attempts"].IsInt()) {
            labsSimulation.Attempts = obj["attempts"].GetInt();
        }

        if (obj.HasMember("protocolId") && obj["protocolId"].IsInt()) {
            labsSimulation.ProtocolId = obj["protocolId"].GetInt();
        }

        if (obj.HasMember("suiteId") && obj["suiteId"].IsInt()) {
            labsSimulation.SuiteId = obj["suiteId"].GetInt();
        }

        if (obj.HasMember("client") && obj["client"].IsObject()) {
            parseSimulationClient(obj["client"].GetObject(), labsSimulation.Client);
        }
    }

    void Endpoint::parseSimulationClient(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj,
                                         labsSimClient_t &labsSimClient) {

        if (obj.HasMember("id") && obj["id"].IsInt()) {
            labsSimClient.Id = obj["id"].GetInt();
        }

        if (obj.HasMember("name") && obj["name"].IsString()) {
            labsSimClient.Name.assign(obj["name"].GetString());
        }

        if (obj.HasMember("version") && obj["version"].IsString()) {
            labsSimClient.Version.assign(obj["version"].GetString());
        }

        if (obj.HasMember("isReference") && obj["isReference"].IsBool()) {
            labsSimClient.IsReference = obj["isReference"].GetBool();
        }
    }

    void Endpoint::parseSimulationDetails(const rapidjson::GenericValue<rapidjson::UTF8<char>,
            rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject &obj,
                                          labsSimDetails_t &labsSimDetails) {

            if (obj.HasMember("results") && obj["results"].IsArray()) {
                for (auto itr = obj["results"].GetArray().Begin(); itr != obj["results"].GetArray().End(); itr++) {
                    labsSimulation_t labsSimulation;

                    if (itr->IsObject()) {
                        parseSimulationResults(itr->GetObject(), labsSimulation);
                        labsSimDetails.Results.push_back(labsSimulation);
                    }
                }
            }

    }
}