//
// Created by burso on 3/20/16.
//

#ifndef LIBSSLLABS_SSLLABS_H
#define LIBSSLLABS_SSLLABS_H

const char SSLLABS_API_URL[] = "https://api.ssllabs.com/api/v2";
const char SSLLABS_AGENT[] = "libssllabs/1.0";

#include <vector>
#include <map>
#include <string>
#include <stdint.h>
#include <curl/curl.h>

namespace ssllabs {

    typedef struct labsInfo {
        std::string EngineVersion;
        std::string CriteriaVersion;
        int MaxAssessments;
        int CurrentAssessments;
        int64_t NewAssessmentCoolOff;
        std::vector<std::string> Messages;
    } labsInfo_t;

    typedef struct labsKey {
        int Size;
        int Strength;
        std::string Algorithm;
        bool DebianFlaw;
        int Q;
    } labsKey_t;

    typedef struct labsCert {
        std::string Subject;
        std::vector<std::string> CommonNames;
        std::vector<std::string> AltNames;
        int64_t NotBefore;
        int64_t NotAfter;
        std::string IssuerSubject;
        std::string SigAlg;
        std::string IssuerLabel;
        int RevocationInfo;
        std::vector<std::string> CrlURIs;
        std::vector<std::string> OcspURIs;
        int RevocationStatus;
        int CrlRevocationStatus;
        int OcspRevocationStatus;
        int Sgc;
        std::string ValidationType;
        int Issues;
        bool Sct;
        int MustStaple;
        std::string Sha1Hash;
        std::string PinSha256;
    } labsCert_t;

    typedef struct labsChainCert {
        std::string Subject;
        std::string Label;
        int64_t NotBefore;
        int64_t NotAfter;
        std::string IssuerSubject;
        std::string IssuerLabel;
        std::string SigAlg;
        int Issues;
        std::string KeyAlg;
        int KeySize;
        int KeyStrength;
        int RevocationStatus;
        int CrlRevocationStatus;
        int OcspRevocationStatus;
        std::string Sha1Hash;
        std::string PinSha256;
        std::string Raw;
    } labsChainCert_t;

    typedef struct labsChain {
        std::vector<labsChainCert_t> Certs;
        int Issues;
    } labsChain_t;

    typedef struct labsProtocol {
        int Id;
        std::string Name;
        std::string Version;
        bool V2SuitesDisabled;
        bool ErrorMessage;
        int Q;
    } labsProtocol_t;

    typedef struct labsSimClient {
        int Id;
        std::string Name;
        std::string Platform;
        std::string Version;
        bool IsReference;
    } labsSimClient_t;

    typedef struct labsSimulation {
        labsSimClient_t Client;
        int ErrorCode;
        int Attempts;
        int ProtocolId;
        int SuiteId;
    } labsSimulation_t;

    typedef struct labsSimDetails {
        std::vector<labsSimulation_t> Results;
    } labsSimDetails_t;

    typedef struct labsSuite {
        int Id;
        std::string Name;
        int CipherStrength;
        int DhStrength;
        int DhP;
        int DhG;
        int DhYs;
        int EcdhBits;
        int EcdhStrength;
        int Q;
    } labsSuite_t;

    typedef struct labsSuites {
        std::vector<labsSuite_t> List;
        bool Preference;
    } labsSuites_t;

    typedef struct labsHstsPolicy {
        int64_t LONG_MAX_AGE;
        std::string Header;
        std::string Status;
        std::string Error;
        int64_t MaxAge;
        bool IncludeSubDomains;
        bool Preload;
        std::map<std::string, std::string> Directives;
    } labsHstsPolicy_t;

    typedef struct labsHstsPreload {
        std::string Source;
        std::string Status;
        std::string Error;
        int64_t SourceTime;
    } labsHstsPreload_t;

    typedef struct labsHpkpPin {
        std::string HashFunction;
        std::string Value;
    } labsHpkpPin_t;

    typedef struct labsHpkpPolicy {
        std::string Header;
        std::string Status;
        std::string Error;
        int64_t MaxAge;
        bool IncludeSubDomains;
        std::string ReportUri;
        std::vector<labsHpkpPin_t> Pins;
        std::vector<labsHpkpPin_t> MatchedPins;
        std::map<std::string, std::string> Directives;
    } labsHpkpPolicy_t;

    typedef struct labsEndpointDetails {
        int64_t HostStartTime;
        labsKey_t Key;
        labsCert_t Cert;
        labsChain_t Chain;
        std::vector<labsProtocol_t> Protocols;
        labsSuites_t Suites;
        std::string ServerSignature;
        bool PrefixDelegation;
        bool NonPrefixDelegation;
        bool VulnBeast;
        int RenegSupport;
        int SessionResumption;
        int CompressionMethods;
        bool SupportsNpn;
        std::string NpnProtocols;
        int SessionTickets;
        bool OcspStapling;
        int StaplingRevocationStatus;
        std::string StaplingRevocationErrorMessage;
        bool SniRequired;
        int HttpStatusCode;
        std::string HttpForwarding;
        int ForwardSecrecy;
        bool SupportsRc4;
        bool Rc4WithModern;
        bool Rc4Only;
        labsSimDetails_t Sims;
        bool Heartbleed;
        bool Heartbeat;
        int OpenSslCcs;
        bool Poodle;
        int PoodleTls;
        bool FallbackScsv;
        bool Freak;
        int HasSct;
        std::vector<std::string> DhPrimes;
        int DhUsesKnownPrimes;
        bool DhYsReuse;
        bool Logjam;
        bool ChaCha20Preference;
        labsHstsPolicy_t HstsPolicy;
        std::vector<labsHstsPreload_t> HstsPreloads;
        labsHpkpPolicy_t HpkpPolicy;
        labsHpkpPolicy_t HpkpRoPolicy;
//        std::vector<> DrownHosts;
        bool DrownErrors;
        bool DrownVulnerable;
    } labsEndpointDetails_t;

    typedef struct labsEndpoint {
        std::string IpAddress;
        std::string ServerName;
        std::string StatusMessage;
        std::string StatusDetailMessage;
        std::string Grade;
        std::string GradeTrustIgnored;
        bool HasWarnings;
        bool IsExceptional;
        int Progress;
        int Duration;
        int Eta;
        int Delegation;
        labsEndpointDetails_t Details;
    } labsEndpoint_t;

    typedef struct labsReport {
        std::string Host;
        int Port;
        std::string Protocol;
        bool IsPublic;
        std::string Status;
        std::string StatusMessage;
        int64_t StartTime;
        int64_t TestTime;
        std::string EngineVersion;
        std::string CriteriaVersion;
        int64_t CacheExpiryTime;
        std::vector<labsEndpoint_t> Endpoints;
        std::vector<std::string> CertHostnames;
        std::string RawJson;
    } labsReport_t;

    class SSLlabs {
    public:
        SSLlabs();

        ~SSLlabs();

        long timeout;

        int analyze(const std::string domain, const std::string &data, bool publish = false,
                    bool startNew = false, bool fromCache = false, bool ignoreMismatch = false);
        int analyze(const std::string domain, labsReport_t &report, bool publish = false,
                    bool startNew = false, bool fromCache = false, bool ignoreMismatch = false);
        int getInfo(const std::string &data);
        int getInfo(labsInfo_t &info);
        int getRootCertsRaw(const std::string &certs);
        int getStatusCodes(const std::string &codes);
        int getEndpointData(const std::string domain, const std::string endpoint, const std::string &data);
        int getEndpointData(const std::string domain, const std::string endpoint, labsEndpoint_t &data);

    protected:
        int curl_read(const std::string &command, const std::string &data);

    private:
        void verifyCurlStatus(CURLcode code);
    };

}

#endif //LIBSSLLABS_SSLLABS_H
