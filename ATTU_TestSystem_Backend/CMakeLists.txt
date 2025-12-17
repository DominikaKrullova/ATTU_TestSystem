cmake_minimum_required(VERSION 3.15)

project(ATTU_TestSystem_Backend VERSION 1.0.0)

find_package(oatpp REQUIRED)
find_package(oatpp-websocket REQUIRED)

set(SOURCE_FILES
    source/main.cpp
    source/Client.cpp
    source/Broadcast.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} )

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Externals
    Logging_static
    CommonComponents_static
    HardwareComponents_static
    Sensors_static
    ATTU_TestSystem_Embedded_static
    oatpp::oatpp
    oatpp::oatpp-websocket
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# Build ATTU_TestSystem as a static library for tests and test applications
add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
target_include_directories(
    ${PROJECT_NAME}_static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
)
target_link_libraries(${PROJECT_NAME}_static PUBLIC
    ATTU_static
    Externals
    Logging_static
    CommonComponents_static
    HardwareComponents_static
    Sensors_static
    ATTU_TestSystem_Embedded_static
    oatpp::oatpp
    oatpp::oatpp-websocket
)

if (BUILD_TESTING)
    #add_subdirectory(tests)
endif()
