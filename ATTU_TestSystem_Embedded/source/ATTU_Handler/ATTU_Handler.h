#pragma once

#include <DataTypes/ATTU_Response.h>
#include <DataTypes/TestData.h>

class ATTU_Handler
{
  public:
    ATTU_Handler()          = default;
    virtual ~ATTU_Handler() = default;

    virtual ATTU_Response TagTestData(TestData data_to_tag) = 0;

  private:
};
