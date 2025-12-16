#pragma once

#include <DataTypes/TestData.h>

namespace Generator
{

    class TestDataGenerator
    {
      public:
        TestDataGenerator()          = default;
        virtual ~TestDataGenerator() = default;

        virtual TestData GenerateTestData() = 0;
    };
}  // namespace Generator
