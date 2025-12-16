#include "EIVAPacket_Deserializer.h"

EIVAPacket_Deserializer::EIVAPacket_Deserializer()
{
}

std::vector<TaggedData> EIVAPacket_Deserializer::DeserializeData(ATTU_Response data)
{
    std::vector<TaggedData> list_tagged_data;

    for (auto&& tagged_data : data.test_data)
    {
        if (tagged_data.empty())
        {
            continue;
        }
        if (tagged_data.size() < sizeof(Legacy::eiva_packet))
        {
            printf("received data is too small!\n");
            continue;
        }

        Legacy::eiva_packet* header_ptr;
        header_ptr = (Legacy::eiva_packet*)tagged_data.data();

        TaggedData out;
        out.header = *header_ptr;
        out.data   = std::vector<uint8_t>(tagged_data.begin() + Legacy::eiva_packet_size, tagged_data.end());
        list_tagged_data.push_back(out);
    }
    return list_tagged_data;
}
