#pragma once

#include <DataDeserialization/EivaLegacyPacket.h>

#include <cstdint>
#include <vector>

struct TaggedData
{
    Legacy::eiva_packet  header;
    std::vector<uint8_t> data;
};
