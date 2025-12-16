#pragma once

#include <DataTypes/ATTU_Response.h>
#include <DataTypes/TestData.h>

#include <vector>

class VerificationLogic
{
  public:
    VerificationLogic()          = default;
    virtual ~VerificationLogic() = default;

    virtual bool Verify(TestData sent_to_attu, ATTU_Response received_from_attu) = 0;
};
