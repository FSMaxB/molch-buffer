cmake_minimum_required (VERSION 2.6)

GET_PROPERTY(MOLCH_BUFFER GLOBAL PROPERTY MOLCH_BUFFER)
if (MOLCH_BUFFER)
    return()
endif (MOLCH_BUFFER)
SET_PROPERTY(GLOBAL PROPERTY MOLCH_BUFFER "true")

project (molch-buffer)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

enable_testing()

#check if running debug build
if ("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    if("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
        set(SECURITY_C_FLAGS "-O0")
    else()
        set(SECURITY_C_FLAGS "-Og")
    endif()
else()
    if(APPLE)
        set(SECURITY_C_FLAGS "-O1 -Wformat -Wformat-security -fPIE")
        #TODO: Find secure Linker flags that work on Mac OS X
    else(APPLE)
        set(SECURITY_C_FLAGS "-fstack-protector-strong -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=2 -O1 -Wformat -Wformat-security -fPIE")
        set(SECURITY_LINK_FLAGS "-z relro,now,noexecstack,noexecheap -pie")
    endif(APPLE)
endif()

find_package(Sodium REQUIRED)

include_directories(${SODIUM_INCLUDE_DIR})
SET(libs ${libs} ${SODIUM_LIBRARY})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -Wall -Wextra -Werror ${SECURITY_C_FLAGS}")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} ${SECURITY_LINK_FLAGS}")

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS --trace-children=yes --leak-check=full --error-exitcode=10)

if("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND")
    message(WARNING "valgrind not found")
endif("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND")

if("${DISABLE_MEMORYCHECK_COMMAND}" MATCHES "TRUE")
    set(MEMORYCHECK_COMMAND "MEMORYCHECK_COMMAND-NOTFOUND")
endif("${DISABLE_MEMORYCHECK_COMMAND}" MATCHES "TRUE")

add_library(molch-buffer buffer)
target_link_libraries(molch-buffer ${libs})

#test
add_executable(buffer-test buffer-test)
target_link_libraries(buffer-test molch-buffer)
add_test(buffer-test buffer-test)
if(NOT ("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND"))
    add_test("buffer-test-valgrind" ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} "./buffer-test")
endif(NOT ("${MEMORYCHECK_COMMAND}" MATCHES "MEMORYCHECK_COMMAND-NOTFOUND"))
