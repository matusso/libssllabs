//
// Created by burso on 3/24/16.
//

#ifndef SSLLABS_ENDPOINT_H
#define SSLLABS_ENDPOINT_H

#include "../include/ssllabs/ssllabs.h"
#include "../include/rapidjson/document.h"

void getEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj, labsEndpoint_t &endpoint);

labsEndpoint_t getEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj);

#endif //SSLLABS_ENDPOINT_H
