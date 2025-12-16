#include <DataDeserialization/EIVAPacket_Deserializer.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

#include "catch.hpp"

CATCH_TEST_CASE("EIVAPacket_Deserializer::DeserializeData skips empty and too-small packets and parses valid ones",
                "[EIVAPacket_Deserializer]")
{
    EIVAPacket_Deserializer deserializer;

    ATTU_Response response;

    // empty packet -> should be skipped
    response.test_data.push_back(std::vector<uint8_t>{});

    // should be skipped
    std::vector<uint8_t> too_small(sizeof(Legacy::eiva_packet) - 1u, 0xAA);
    response.test_data.push_back(too_small);

    Legacy::eiva_packet header{};
    std::memset(&header, 0xAB, sizeof(header));

    std::vector<uint8_t> payload = {0x10, 0x20, 0x30, 0x40};

    std::vector<uint8_t> valid_packet;
    valid_packet.resize(Legacy::eiva_packet_size + payload.size());

    std::memcpy(valid_packet.data(), &header, Legacy::eiva_packet_size);
    std::copy(payload.begin(), payload.end(), valid_packet.begin() + Legacy::eiva_packet_size);

    response.test_data.push_back(valid_packet);

    std::vector<TaggedData> result = deserializer.DeserializeData(response);

    // assert: only the valid packet should produce a TaggedData
    CATCH_REQUIRE(result.size() == 1);

    const TaggedData& tagged = result[0];

    // header bytes match what we put in
    CATCH_REQUIRE(std::memcmp(&tagged.header, &header, sizeof(header)) == 0);

    // data is exactly the payload we appended
    CATCH_REQUIRE(tagged.data.size() == payload.size());
    CATCH_REQUIRE(std::equal(payload.begin(), payload.end(), tagged.data.begin()));
}

CATCH_TEST_CASE("EIVAPacket_Deserializer::DeserializeData returns empty when all packets are invalid",
                "[EIVAPacket_Deserializer]")
{
    EIVAPacket_Deserializer deserializer;
    ATTU_Response           response;

    // empty and too-small packets
    response.test_data.push_back(std::vector<uint8_t>{});
    response.test_data.push_back(std::vector<uint8_t>(sizeof(Legacy::eiva_packet) - 2u, 0x00));

    auto result = deserializer.DeserializeData(response);

    CATCH_REQUIRE(result.empty());
}
