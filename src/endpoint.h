//
// Created by burso on 3/24/16.
//

#ifndef SSLLABS_ENDPOINT_H
#define SSLLABS_ENDPOINT_H

#include "../include/ssllabs/ssllabs.h"
#include "../include/rapidjson/document.h"

namespace ssllabs {

    class Endpoint {
    public:
        static void getEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj, labsEndpoint_t &endpoint);

        static labsEndpoint_t getEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj);

    protected:

    private:

    };

}

#endif //SSLLABS_ENDPOINT_H
