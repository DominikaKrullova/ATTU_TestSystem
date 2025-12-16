add_executable(
    Serial_App
    Serial_App.cpp
)


target_link_libraries(Serial_App
    PRIVATE
    Externals
    CommonComponents_static
    ATTU_TestSystem_Embedded_static
)



target_include_directories(Serial_App
    PRIVATE
    ${CMAKE_SOURCE_DIR}/Communication_Test/source
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
    ${CMAKE_SOURCE_DIR}/../ATTU_TestSystem_Embedded/source
)


install(
    TARGETS Serial_App 
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/Communication_Test
)
