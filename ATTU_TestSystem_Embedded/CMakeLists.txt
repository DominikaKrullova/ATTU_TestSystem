cmake_minimum_required(VERSION 3.15)

project(ATTU_TestSystem_Embedded VERSION 1.0.0)


set(SOURCE_FILES
    source/Generators/ASCII_Generator.cpp
    source/ATTU_Handler/DataSender.cpp
    source/ATTU_Handler/ATTU_MK2_Handler.cpp
    source/ATTU_Handler/DataReceiver.cpp
    source/main.cpp
    source/ATTU_Tests/ASCII_Protocol_Test.cpp
    source/DataDeserialization/EIVAPacket_Deserializer.cpp
    source/ATTU_Tests/TestController.cpp

)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} )

message(ATTU_TestSystem_Embedded CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    # ATTU_static
    Externals
    Logging_static
    CommonComponents_static
    HardwareComponents_static
    Sensors_static
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# Build ATTU_TestSystem as a static library for tests and test applications
add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
# add_library(${ATTU_TestSystem_Backend} SHARED ${SOURCE_FILES})
target_include_directories(
    ${PROJECT_NAME}_static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    
)
target_link_libraries(${PROJECT_NAME}_static PUBLIC
    # ATTU_static
    Externals
    Logging_static
    CommonComponents_static
    HardwareComponents_static
    Sensors_static
)

if (BUILD_TESTING)
    add_subdirectory(internal_tests)
endif()
