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
        static void parseEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj, labsEndpoint_t &endpoint);

        static labsEndpoint_t parseEndpointData(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>> &obj);

    protected:

    private:
        static void parseEndpointDetails(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject & obj, labsEndpoint_t &endpoint);

        static void parseHstsPolicy(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject & obj, labsHstsPolicy_t &hstsPolicy);

        static void parseHpkpPolicy(const rapidjson::GenericValue<rapidjson::UTF8<char>,
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>::ConstObject & obj, labsHpkpPolicy_t &hpkpPolicy);
    };

}

#endif //SSLLABS_ENDPOINT_H
