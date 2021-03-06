# - Find Sodium
# Find the native libsodium includes and library.
# Once done this will define
#
#  SODIUM_INCLUDE_DIR    - where to find libsodium header files, etc.
#  SODIUM_LIBRARY        - List of libraries when using libsodium.
#  SODIUM_FOUND          - True if libsodium found.
#

find_library(SODIUM_LIBRARY names sodium libsodium HINTS ${SODIUM_ROOT_DIR}/lib)
find_path(SODIUM_INCLUDE_DIR names sodium.h HINTS ${SODIUM_ROOT_DIR}/include)

# handle the QUIETLY and REQUIRED arguments and set SODIUM_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sodium REQUIRED_VARS SODIUM_LIBRARY SODIUM_INCLUDE_DIR)

mark_as_advanced(SODIUM_LIBRARY SODIUM_INCLUDE_DIR)
