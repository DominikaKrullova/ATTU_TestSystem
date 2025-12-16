#include "ASCII_Protocol_Test.h"

ASCII_Protocol_Test::ASCII_Protocol_Test()
{
}

bool ASCII_Protocol_Test::Verify(TestData sent_to_attu, ATTU_Response received_from_attu)
{
    std::vector<TaggedData> tagged_data = deserializer.DeserializeData(received_from_attu);

    if (tagged_data.size() != sent_to_attu.test_data.size())
    {
        return false;
    }

    bool is_equal = true;

    for (size_t i = 0; i < sent_to_attu.test_data.size(); i++)
    {
        const auto& expected = sent_to_attu.test_data[i];
        const auto& actual   = tagged_data[i].data;

        size_t actual_len = actual.size();
        while (actual_len > 0 && actual[actual_len - 1] == 0x00)
        {
            --actual_len;
        }

        bool match = false;
        if (actual_len == expected.size())
        {
            match = std::equal(expected.begin(), expected.end(), actual.begin());
        }

        if (!match)
        {
            is_equal = false;

            // Debug print
            printf("Mismatch at index %zu\n", i);
            printf("Received (%zu/%zu): ", actual_len, actual.size());
            for (size_t j = 0; j < actual.size(); ++j)
                printf("%02x ", actual[j]);
            printf("\nExpected (%zu): ", expected.size());
            for (auto b : expected)
                printf("%02x ", b);
            printf("\n");
        }
    }

    return is_equal;
}
