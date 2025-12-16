
#pragma once

#include <oatpp/Types.hpp>
#include <oatpp/macro/codegen.hpp>

namespace DTO
{

#include OATPP_CODEGEN_BEGIN(DTO)
    // clang-format off
    // NOTE(dfo): No trailing ',' on the last line
    ENUM(PacketType, v_uint32,
        VALUE(UNKNOWN, 0),
        VALUE(Sync, 1),
        VALUE(ATTUConfig, 2),
        VALUE(TestResult, 3)
    );
    // clang-format on

    // NOTE(dfo): This is not standard inheritance
    // Packets that inherit from this still have to declare the packet_type DTO_FIELD in their own definition
    class Packet : public oatpp::DTO
    {
        DTO_INIT(Packet, DTO)

        DTO_FIELD(Enum<PacketType>::AsNumber, packet_type);
    };

    ENUM(ConnectionType, v_int32, VALUE(COM, 0), VALUE(IP, 1));

    class COMConnection : public oatpp::DTO
    {
        DTO_INIT(COMConnection, DTO);

        DTO_FIELD(String, device);
        DTO_FIELD(UInt32, com_port_type);
        DTO_FIELD(UInt32, baudrate);
        DTO_FIELD(UInt32, data_bits);
        DTO_FIELD(UInt32, stop_bits);
        DTO_FIELD(UInt32, parity);
        DTO_FIELD(UInt32, flow_control);
    };

    class IPConnection : public oatpp::DTO
    {
        DTO_INIT(IPConnection, DTO);

        DTO_FIELD(String, ip);
        DTO_FIELD(UInt32, port);
        DTO_FIELD(UInt32, protocol);
    };

    class TestResult : public oatpp::DTO
    {
        DTO_INIT(TestResult, DTO)

        DTO_FIELD(String, test_id);
        DTO_FIELD(Boolean, result);
    };

#include OATPP_CODEGEN_END(DTO)
}  // namespace DTO