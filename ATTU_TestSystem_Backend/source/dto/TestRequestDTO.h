#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

#include "ATTUConfigDTO.h"
#include "Packet.h"

// If these exist already, include them instead of forward-declaring
// #include "ATTUConfigDto.hpp"
// #include "PortDto.hpp"

// ENUM(TestStatus, v_int32, VALUE(isRunning, 0));
namespace DTO
{
#include OATPP_CODEGEN_BEGIN(DTO)

    class TestStartRequestDto : public oatpp::DTO
    {
        DTO_INIT(TestStartRequestDto, DTO);

        DTO_FIELD(String, testId);
        DTO_FIELD(String, testName);
        DTO_FIELD(String, attuIp);
        DTO_FIELD(UInt32, networkPort);

        // DTO_FIELD(Object<DTO::ATTUConfigDTO>, attuConfig);
        // DTO_FIELD(Object<DTO::Port>, port);

        DTO_FIELD(String, status);
    };

    class TestRequestDto : public Packet
    {
        DTO_INIT(TestRequestDto, DTO);
        DTO_FIELD(Enum<PacketType>::AsNumber, packet_type);
        // DTO_FIELD(Object<TestStartRequestDto>, payload);
        DTO_FIELD(String, payload);
    };

#include OATPP_CODEGEN_END(DTO)
}  // namespace DTO
