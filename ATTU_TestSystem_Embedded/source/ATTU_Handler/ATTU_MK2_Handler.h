#pragma once

#include <DataTypes/TestData.h>

#include <memory>

#include "ATTU_Handler.h"
#include "DataReceiver.h"
#include "DataSender.h"

class ATTU_MK2_Handler : public ATTU_Handler
{
  public:
    ATTU_MK2_Handler();
    virtual ~ATTU_MK2_Handler() = default;

    // void StartHandler();
    // void StopHandler();

    ATTU_Response TagTestData(TestData data_to_tag) override;

  private:
    void SetUpDataSender();
    void SetUpDataReceiver();

    std::unique_ptr<DataReceiver> data_receiver;
    std::unique_ptr<DataSender>   data_sender;
};
