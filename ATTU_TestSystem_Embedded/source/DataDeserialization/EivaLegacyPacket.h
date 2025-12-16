#pragma once

#include <stdint.h>

#include <string>

namespace Legacy
{
#define MAX_PACKET_LENGTH 2048
#define META_DATA_PORT 55511

    const size_t eiva_packet_size        = 24;
    const size_t eiva_packet_header_size = 8;
// Packet structure.
#pragma pack(push, 1)
    struct eiva_packet
    {
        uint8_t  header[4] = {'E', 'I', 'V', 'A'};
        uint32_t length;  // total number of bytes - (eiva_packet_header_size)

        // ver_ipno in orginal packet;
        // first two bytes = 1; last two bytes is the last field in tcp/ip address (1-254)
        uint16_t version = 1;
        uint16_t domain;  // last field in tcp/ip address (1-254)

        uint32_t instrument_id;  // sensor number (COM port number) data originates from
        uint32_t time_stamp_s;   // seconds
        uint32_t time_stamp_us;  // microseconds
        // uint8_t data[MAX_PACKET_LENGTH]; // data from instrument
    };
#pragma pack(pop)
}  // namespace Legacy