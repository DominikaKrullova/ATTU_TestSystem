#include <ATTU_Handler/DataSender.h>
#include <Connection/MockConnection.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <vector>

#include "catch.hpp"

// mockConnection's protected counters
class InspectableMockConnection : public MockConnection
{
  public:
    using MockConnection::MockConnection;

    std::uint64_t GetTotalWritesCount() const
    {
        return total_writes_count;
    }
    std::uint64_t GetTotalWriteBytes() const
    {
        return total_write_bytes;
    }
    const std::vector<uint8_t>& GetLastWrite() const
    {
        return last_write;
    }
};

CATCH_TEST_CASE("DataSender::SendData writes all chunks to the connection", "[DataSender]")
{
    auto                       mock     = std::make_unique<InspectableMockConnection>();
    InspectableMockConnection* mock_ptr = mock.get();

    mock_ptr->MockDataAdd(std::vector<uint8_t>{0x00}, std::chrono::milliseconds(0));

    DataSender sender(std::move(mock));

    TestData data;
    data.test_data.push_back({'H', 'i'});       // 2 bytes
    data.test_data.push_back({'!', '!', '!'});  // 3 bytes

    const std::size_t expected_chunks = data.test_data.size();

    std::size_t expected_bytes = 0;
    for (const auto& chunk : data.test_data)
    {
        expected_bytes += chunk.size();
    }

    sender.SendData(data);

    CATCH_REQUIRE(mock_ptr->GetTotalWritesCount() == expected_chunks);
    CATCH_REQUIRE(mock_ptr->GetTotalWriteBytes() == expected_bytes);

    const auto& last = mock_ptr->GetLastWrite();
    CATCH_REQUIRE(last.size() == data.test_data.back().size());
    CATCH_REQUIRE(std::equal(last.begin(), last.end(), data.test_data.back().begin()));
}
