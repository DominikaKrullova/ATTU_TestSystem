#include "ASCII_Generator.h"

#include <cstdlib>

namespace Generator
{
    TestData ASCII_Generator::GenerateASCII()
    {
        TestData out;
        out.test_data.push_back({'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\n'});
        return out;
    }

    TestData ASCII_Generator::GenerateTestData()
    {
        return GenerateASCII();
    }

}  // namespace Generator