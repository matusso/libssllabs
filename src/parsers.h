#ifndef SSLLABS_PARSERS_H
#define SSLLABS_PARSERS_H

#include <string_view>

#include <ssllabs/ssllabs.h>

namespace ssllabs::detail {

int parseInfoResponse(std::string_view json, labsInfo_t &info);
int parseAnalyzeResponse(std::string_view json, labsReport_t &report);
int parseEndpointResponse(std::string_view json, labsEndpoint_t &endpoint);

} // namespace ssllabs::detail

#endif // SSLLABS_PARSERS_H
