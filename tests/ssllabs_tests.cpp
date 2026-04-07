#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <ssllabs/ssllabs.h>

#include "parsers.h"

namespace {

const char *kInfoResponse = R"json({
  "engineVersion": "2.4.1",
  "criteriaVersion": "2025q1",
  "clientMaxAssessments": 10,
  "currentAssessments": 2,
  "newAssessmentCoolOff": 1500,
  "messages": ["ready", "cached"]
})json";

const char *kAnalyzeResponse = R"json({
  "host": "example.com",
  "port": 443,
  "protocol": "HTTP",
  "isPublic": true,
  "status": "READY",
  "statusMessage": "Ready",
  "startTime": 1700000000000,
  "testTime": 1700000001000,
  "engineVersion": "2.4.0",
  "criteriaVersion": "2025q1",
  "cacheExpiryTime": 1700000002000,
  "certHostnames": ["example.com", "www.example.com"],
  "endpoints": [
    {
      "ipAddress": "192.0.2.10",
      "serverName": "edge-1",
      "statusMessage": "Ready",
      "statusDetailsMessage": "Secure",
      "grade": "A+",
      "gradeTrustIgnored": "A",
      "hasWarnings": false,
      "isExceptional": true,
      "progress": 100,
      "duration": 12,
      "eta": 0,
      "delegation": 1,
      "details": {
        "hostStartTime": 1700000003000,
        "key": {
          "size": 2048,
          "alg": "RSA",
          "debianFlaw": false,
          "strength": 112
        },
        "cert": {
          "subject": "CN=example.com",
          "commonNames": ["example.com"],
          "altNames": ["www.example.com"],
          "notBefore": 1700000004000,
          "notAfter": 1800000004000,
          "issuerSubject": "CN=Example CA",
          "issuerLabel": "Example CA",
          "sigAlg": "SHA256withRSA",
          "revocationInfo": 1,
          "crlURIs": ["http://example.com/crl"],
          "ocspURIs": ["http://example.com/ocsp"],
          "revocationStatus": 0,
          "crlRevocationStatus": 0,
          "ocspRevocationStatus": 0,
          "sgc": 0,
          "issues": 0,
          "sct": true,
          "mustStaple": 0,
          "sha1Hash": "sha1",
          "pinSha256": "pin"
        },
        "chain": {
          "issues": 0,
          "certs": [
            {
              "subject": "CN=leaf",
              "label": "Leaf",
              "notBefore": 1,
              "notAfter": 2,
              "issuerSubject": "CN=CA",
              "issuerLabel": "CA",
              "sigAlg": "RSA",
              "issues": 0,
              "keyAlg": "RSA",
              "keySize": 2048,
              "keyStrength": 112,
              "revocationStatus": 0,
              "crlRevocationStatus": 0,
              "ocspRevocationStatus": 0,
              "sha1Hash": "leaf",
              "pinSha256": "leaf-pin",
              "raw": "raw-leaf"
            },
            {
              "subject": "CN=intermediate",
              "notBefore": 3,
              "notAfter": 4,
              "issuerSubject": "CN=Root",
              "sigAlg": "RSA",
              "issues": 1,
              "keyAlg": "RSA",
              "keySize": 4096,
              "keyStrength": 128,
              "revocationStatus": 1,
              "crlRevocationStatus": 1,
              "ocspRevocationStatus": 1,
              "sha1Hash": "int",
              "pinSha256": "int-pin",
              "raw": "raw-int"
            }
          ]
        },
        "protocols": [
          {
            "id": 771,
            "name": "TLS",
            "version": "1.2"
          },
          {
            "id": 772,
            "version": "1.3"
          }
        ],
        "suites": {
          "preference": true,
          "list": [
            {
              "id": 4865,
              "name": "TLS_AES_128_GCM_SHA256",
              "cipherStrength": 128,
              "dhStrength": 42
            },
            {
              "id": 4866,
              "name": "TLS_AES_256_GCM_SHA384",
              "cipherStrength": 256
            }
          ]
        },
        "serverSignature": "ExampleServer",
        "prefixDelegation": true,
        "nonPrefixDelegation": false,
        "vulnBeast": false,
        "renegSupport": 1,
        "sessionResumption": 2,
        "compressionMethods": 0,
        "supportsNpn": false,
        "sessionTickets": 1,
        "ocspStapling": true,
        "sniRequired": false,
        "httpStatusCode": 200,
        "supportsRc4": false,
        "rc4WithModern": false,
        "rc4Only": false,
        "forwardSecrecy": 1,
        "sims": {
          "results": [
            {
              "errorCode": 0,
              "attempts": 1,
              "protocolId": 771,
              "suiteId": 4865,
              "client": {
                "id": 1,
                "name": "Chrome",
                "version": "124",
                "isReference": true
              }
            },
            {
              "errorCode": 1,
              "attempts": 2,
              "protocolId": 772,
              "suiteId": 4866,
              "client": {
                "id": 2,
                "name": "Safari",
                "isReference": false
              }
            }
          ]
        },
        "heartbleed": false,
        "heartbeat": false,
        "openSslCcs": 0,
        "poodle": false,
        "poodleTls": 0,
        "fallbackScsv": true,
        "freak": false,
        "hasSct": 1,
        "dhPrimes": ["prime1", "prime2"],
        "dhUsesKnownPrimes": 1,
        "dhYsReuse": false,
        "logjam": false,
        "hstsPolicy": {
          "LONG_MAX_AGE": 31536000,
          "header": "max-age=31536000",
          "status": "present",
          "maxAge": 31536000
        },
        "hpkpPolicy": {
          "status": "not-supported"
        },
        "hpkpRoPolicy": {
          "status": "not-supported"
        },
        "drownErrors": false,
        "drownVulnerable": false
      }
    }
  ]
})json";

class TestFailure : public std::runtime_error {
public:
    explicit TestFailure(const std::string &message)
        : std::runtime_error(message) {
    }
};

template <typename Actual, typename Expected>
void expectEqual(const Actual &actual, const Expected &expected, const std::string &message) {
    if (actual == expected) {
        return;
    }

    std::ostringstream stream;
    stream << message << " (expected: " << expected << ", actual: " << actual << ")";
    throw TestFailure(stream.str());
}

void expectTrue(bool condition, const std::string &message) {
    if (!condition) {
        throw TestFailure(message);
    }
}

void testParseInfoResponseClearsStaleState() {
    ssllabs::labsInfo_t info = {};
    info.EngineVersion = "stale";
    info.Messages.push_back("stale");

    expectEqual(ssllabs::detail::parseInfoResponse(kInfoResponse, info), 0, "info response should parse");
    expectEqual(info.EngineVersion, std::string("2.4.1"), "engine version should match fixture");
    expectEqual(info.CriteriaVersion, std::string("2025q1"), "criteria version should match fixture");
    expectEqual(info.MaxAssessments, 10, "max assessments should match fixture");
    expectEqual(info.CurrentAssessments, 2, "current assessments should match fixture");
    expectEqual(info.NewAssessmentCoolOff, static_cast<int64_t>(1500), "cool off should match fixture");
    expectEqual(info.Messages.size(), static_cast<std::size_t>(2), "messages should be replaced");
    expectEqual(info.Messages[0], std::string("ready"), "first message should match fixture");
    expectEqual(info.Messages[1], std::string("cached"), "second message should match fixture");
}

void testParseAnalyzeResponseCapturesNestedData() {
    ssllabs::labsReport_t report = {};
    report.Host = "stale";
    report.CertHostnames.push_back("stale");

    expectEqual(ssllabs::detail::parseAnalyzeResponse(kAnalyzeResponse, report), 0, "analyze response should parse");

    expectEqual(report.Host, std::string("example.com"), "host should match fixture");
    expectEqual(report.Port, 443, "port should match fixture");
    expectEqual(report.Protocol, std::string("HTTP"), "protocol should match fixture");
    expectTrue(report.IsPublic, "report should be public");
    expectEqual(report.Status, std::string("READY"), "status should match fixture");
    expectEqual(report.StatusMessage, std::string("Ready"), "status message should match fixture");
    expectEqual(report.CacheExpiryTime, static_cast<int64_t>(1700000002000), "cache expiry should be parsed");
    expectEqual(report.CertHostnames.size(), static_cast<std::size_t>(2), "cert hostnames should be replaced");
    expectEqual(report.CertHostnames[1], std::string("www.example.com"), "cert hostname should match fixture");
    expectEqual(report.Endpoints.size(), static_cast<std::size_t>(1), "one endpoint should be parsed");

    const ssllabs::labsEndpoint_t &endpoint = report.Endpoints.front();
    expectEqual(endpoint.IpAddress, std::string("192.0.2.10"), "endpoint IP should match fixture");
    expectEqual(endpoint.StatusDetailMessage, std::string("Secure"), "endpoint details message should match fixture");
    expectEqual(endpoint.Details.Key.Algorithm, std::string("RSA"), "key algorithm should match fixture");
    expectEqual(endpoint.Details.Chain.Certs.size(), static_cast<std::size_t>(2), "two chain certs should be parsed");
    expectEqual(endpoint.Details.Chain.Certs[1].Label, std::string(), "second chain cert should not inherit a stale label");
    expectEqual(endpoint.Details.Protocols.size(), static_cast<std::size_t>(2), "two protocols should be parsed");
    expectEqual(endpoint.Details.Protocols[1].Name, std::string(), "second protocol should not inherit a stale name");
    expectEqual(endpoint.Details.Protocols[1].Version, std::string("1.3"), "second protocol version should match fixture");
    expectEqual(endpoint.Details.Suites.List.size(), static_cast<std::size_t>(2), "two suites should be parsed");
    expectEqual(endpoint.Details.Suites.List[0].DhStrength, 42, "first suite should preserve its DH strength");
    expectEqual(endpoint.Details.Suites.List[1].DhStrength, 0, "second suite should not inherit a stale DH strength");
    expectEqual(endpoint.Details.Sims.Results.size(), static_cast<std::size_t>(2), "two simulations should be parsed");
    expectEqual(endpoint.Details.Sims.Results[1].Client.Version, std::string(), "second simulated client should not inherit a stale version");
    expectEqual(endpoint.Details.Sims.Results[1].Client.Name, std::string("Safari"), "second simulated client should match fixture");
}

void testInvalidAnalyzeFlagsFailFast() {
    ssllabs::SSLlabs client;
    ssllabs::labsReport_t report = {};

    expectEqual(client.analyze("example.com", report, false, true, true), -1, "conflicting analyze flags should fail before any request");
}

int runTest(const char *name, void (*test)()) {
    try {
        test();
        std::cout << "[PASS] " << name << '\n';
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "[FAIL] " << name << ": " << error.what() << '\n';
        return 1;
    }
}

} // namespace

int main() {
    int failures = 0;

    failures += runTest("parseInfoResponse clears stale state", testParseInfoResponseClearsStaleState);
    failures += runTest("parseAnalyzeResponse captures nested data", testParseAnalyzeResponseCapturesNestedData);
    failures += runTest("invalid analyze flags fail fast", testInvalidAnalyzeFlagsFailFast);

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
