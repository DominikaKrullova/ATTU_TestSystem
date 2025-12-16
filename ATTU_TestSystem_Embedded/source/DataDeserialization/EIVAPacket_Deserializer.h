#pragma once

#include <DataTypes/ATTU_Response.h>
#include <DataTypes/TaggedData.h>

class EIVAPacket_Deserializer
{
  public:
    EIVAPacket_Deserializer();

    std::vector<TaggedData> DeserializeData(ATTU_Response data);

  private:
};
