
#include <Generators/ASCII_Generator.h>

#include <string>

#include "catch.hpp"

CATCH_TEST_CASE("ASCII_Generator::GenerateASCII returns 'Hello, World!\\n'", "[ASCII_Generator]")
{
    Generator::ASCII_Generator generator;

    TestData data = generator.GenerateASCII();

    CATCH_REQUIRE(data.test_data.size() == 1);
    CATCH_REQUIRE(data.test_data[0].size() == 14);  // "Hello, World!\n" is 14 chars

    std::string str(data.test_data[0].begin(), data.test_data[0].end());
    CATCH_REQUIRE(str == "Hello, World!\n");
}

CATCH_TEST_CASE("ASCII_Generator::GenerateTestData delegates to GenerateASCII", "[ASCII_Generator]")
{
    Generator::ASCII_Generator generator;

    TestData dataFromASCII    = generator.GenerateASCII();
    TestData dataFromTestData = generator.GenerateTestData();

    CATCH_REQUIRE(dataFromASCII.test_data.size() == dataFromTestData.test_data.size());
    CATCH_REQUIRE(dataFromASCII.test_data.size() == 1);

    CATCH_REQUIRE(dataFromASCII.test_data[0] == dataFromTestData.test_data[0]);
}
