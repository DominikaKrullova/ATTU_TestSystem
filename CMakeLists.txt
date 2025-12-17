
cmake_minimum_required(VERSION 3.15)

project(ATTU_TestSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -ldl -g -Wall -DLOGURU_STACKTRACES=0 -DCATCH_CONFIG_PREFIX_ALL -Wno-reorder -Wno-unused-variable -Wno-unused-but-set-variable")


if (BUILD_TESTING)
enable_testing()
endif()

add_subdirectory(EIVA_Embedded)
add_subdirectory(ATTU_TestSystem_Embedded)
add_subdirectory(ATTU_TestSystem_Backend)
# add_subdirectory(Test_Applications)


# ENSURE THESE ARE OFF WHEN BUILDING A RELEASE!
#-------- debugging options --------
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# add_compile_options(-fsanitize=thread)
# add_link_options(-fsanitize=thread)
#-----------------------------------
