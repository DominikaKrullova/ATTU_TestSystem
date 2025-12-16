#pragma once
// NEEDS TO BE CHECKED

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "Packet.h"
namespace DTO
{
#include OATPP_CODEGEN_BEGIN(DTO)

    class ATTUConfigDTO : public Packet
    {
        DTO_INIT(ATTUConfigDTO, DTO)

        DTO_FIELD(Enum<PacketType>::AsNumber, packet_type);
        DTO_FIELD(String, ip);
        // DTO_FIELD(Bool, gps);
        // DTO_FIELD(Bool, ntp);
    };

#include OATPP_CODEGEN_END(DTO)
}  // namespace DTO