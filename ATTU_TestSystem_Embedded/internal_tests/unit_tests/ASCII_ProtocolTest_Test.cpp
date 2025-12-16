#include <ATTU_Tests/ASCII_Protocol_Test.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#include "catch.hpp"

// build a raw ATTU "packet" = [Legacy::eiva_packet header][payload][optional trailing zeros]
static std::vector<uint8_t> MakePacket(const std::vector<uint8_t>& payload, bool with_trailing_zeros)
{
    Legacy::eiva_packet header{};
    std::memset(&header, 0xAB, sizeof(header));

    const std::size_t pad = with_trailing_zeros ? 3u : 0u;

    std::vector<uint8_t> packet;
    packet.resize(Legacy::eiva_packet_size + payload.size() + pad);

    std::memcpy(packet.data(), &header, Legacy::eiva_packet_size);

    std::copy(payload.begin(), payload.end(), packet.begin() + Legacy::eiva_packet_size);

    if (pad > 0)
    {
        std::fill(packet.begin() + Legacy::eiva_packet_size + payload.size(), packet.end(), 0x00);
    }

    return packet;
}

CATCH_TEST_CASE("ASCII_Protocol_Test::Verify returns true when payloads match", "[ASCII_Protocol_Test]")
{
    ASCII_Protocol_Test protocol_test;

    TestData sent;
    sent.test_data.push_back({'H', 'e', 'l', 'l', 'o'});
    sent.test_data.push_back({'B', 'y', 'e'});

    ATTU_Response response;
    response.test_data.push_back(MakePacket(sent.test_data[0], false));  // no padding
    response.test_data.push_back(MakePacket(sent.test_data[1], true));   // with trailing zeros

    bool ok = protocol_test.Verify(sent, response);

    CATCH_REQUIRE(ok);
}

CATCH_TEST_CASE("ASCII_Protocol_Test::Verify returns false when any payload differs", "[ASCII_Protocol_Test]")
{
    ASCII_Protocol_Test protocol_test;

    TestData sent;
    sent.test_data.push_back({'O', 'K'});

    std::vector<uint8_t> wrong_payload = {'N', 'O'};
    ATTU_Response        response;
    response.test_data.push_back(MakePacket(wrong_payload, false));

    bool ok = protocol_test.Verify(sent, response);

    CATCH_REQUIRE(ok == false);
}

CATCH_TEST_CASE("ASCII_Protocol_Test::Verify returns false when counts differ", "[ASCII_Protocol_Test]")
{
    ASCII_Protocol_Test protocol_test;

    TestData sent;
    sent.test_data.push_back({'A'});
    sent.test_data.push_back({'B'});

    ATTU_Response response;
    response.test_data.push_back(MakePacket(sent.test_data[0], false));

    bool ok = protocol_test.Verify(sent, response);

    CATCH_REQUIRE(ok == false);
}
