#pragma once

#include <ATTU_Tests/VerificationLogic.h>
#include <DataDeserialization/EIVAPacket_Deserializer.h>

class ASCII_Protocol_Test : public VerificationLogic
{
  public:
    ASCII_Protocol_Test();
    ~ASCII_Protocol_Test() = default;

    bool Verify(TestData sent_to_attu, ATTU_Response received_from_attu) override;

  private:
    EIVAPacket_Deserializer deserializer;
};
