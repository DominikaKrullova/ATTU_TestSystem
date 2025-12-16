
add_executable(
    Embedded_UnitTests
    test_main.cpp
    unit_tests/ASCII_Generator_Test.cpp
    unit_tests/DataSender_Test.cpp
    unit_tests/EIVAPacket_Deserializer_Test.cpp
    unit_tests/ASCII_ProtocolTest_Test.cpp
)

target_link_libraries(Embedded_UnitTests
    PRIVATE
    Externals
    HardwareComponents_static
    ATTU_TestSystem_Embedded_static 
    Sensors_static
    CommonComponents_static
    ROTV_static
    SensorService_static
    DDS_static
)

target_include_directories(Embedded_UnitTests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/ATTU_TestSystem_Embedded/source
)

add_test(NAME Embedded_UnitTests COMMAND Embedded_UnitTests)

set_tests_properties(Embedded_UnitTests PROPERTIES LABELS "embedded;unit")

install(
    TARGETS Embedded_UnitTests
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/internal_tests/unit
)

