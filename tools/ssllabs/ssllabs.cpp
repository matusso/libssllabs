#include <iostream>
#include <string>
#include "../../include/ssllabs/ssllabs.h"

using namespace ssllabs;
using namespace std;

int main(int argc, char** argv) {
    ssllabs::SSLlabs ssllabsObject;
    string data;
    labsReport_t report;

    ssllabsObject.analyze("www.google.com", report);
    cout << "HOST: " << report.Host << "\n";
    cout << "PORT: " << report.Port << "\n";
    cout << "PROTOCOL: " << report.Protocol << "\n";
    cout << "isPublic: " << report.IsPublic << "\n";
    cout << "STATUS: " << report.Status << "\n";
    cout << "STARTTIME: " << report.StartTime << "\n";
    cout << "TESTTIME: " << report.TestTime << "\n";
    cout << "ENGINE VERSION: " << report.EngineVersion << "\n";
    cout << "CRITERIA VERSION: " << report.CriteriaVersion << "\n";
    vector<labsEndpoint_t>::iterator it;

    int counter = 1;
    for (it = report.Endpoints.begin(); it != report.Endpoints.end(); it++) {
        cout << "ENDPOINT " << counter << "\n";
        labsEndpoint_t endpoint = *it;
        labsEndpoint_t endpoint2;
        ssllabsObject.getEndpointData("www.google.com", endpoint.IpAddress, endpoint2);
        cout << "\tIP ADDRESS: " << endpoint2.IpAddress << "\n";
        cout << "\tSERVER NAME: " << endpoint2.ServerName << "\n";
        cout << "\tSTATUS MESSAGE: " << endpoint2.StatusMessage << "\n";
        cout << "\tGRADE: " << endpoint2.Grade << "\n";
        cout << "\tGRADE TRUST IGNORED: " << endpoint2.GradeTrustIgnored << "\n";
        cout << "\tHAS WARNINGS: " << endpoint2.HasWarnings << "\n";
        cout << "\tISEXCEPTIONAL: " << endpoint2.IsExceptional << "\n";
        cout << "\tPROGRESS: " << endpoint2.Progress << "\n";
        cout << "\tDURATION: " << endpoint2.Duration << "\n";
        cout << "\tETA: " << endpoint2.Eta << "\n";
        cout << "\tDELEGATION: " << endpoint2.Delegation << "\n";

        cout << "\t\tHOST START TIME: " << endpoint2.Details.HostStartTime << "\n";
        cout << "\t\tKEY INFORMATION\n";
        cout << "\t\t\tSIZE: " << endpoint2.Details.Key.Size << "\n";
        cout << "\t\t\tALGORTIHM: " << endpoint2.Details.Key.Algorithm << "\n";
        cout << "\t\t\tDEBIAN FLAW: " << endpoint2.Details.Key.DebianFlaw << "\n";
        cout << "\t\t\tSTRENGTH: " << endpoint2.Details.Key.Strength << "\n";
        cout << "\t\t\tQ: " << endpoint2.Details.Key.Q << "\n";
        counter++;
    }
    return 0;
}
