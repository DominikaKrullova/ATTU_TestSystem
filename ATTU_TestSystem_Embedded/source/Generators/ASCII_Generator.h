#pragma once

#include <DataTypes/TestData.h>
#include <Generators/TestDataGenerator.h>

#include <cstdint>
#include <vector>

namespace Generator
{
    class ASCII_Generator : public TestDataGenerator
    {
      public:
        ASCII_Generator()          = default;
        virtual ~ASCII_Generator() = default;

        TestData GenerateASCII();

        TestData GenerateTestData() override;
    };
}  // namespace Generator
