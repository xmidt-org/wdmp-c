#   Copyright 2010-2016 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

cmake_minimum_required(VERSION 2.8.7)

project(wdmp-c)
include(ExternalProject)

add_definitions(-std=c99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -Werror -Wall -DCIMP_LOGGER")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE -Werror -Wall -DCIMP_LOGGER")

set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/_install)
set(PREFIX_DIR ${CMAKE_CURRENT_BINARY_DIR}/_prefix)
set(INCLUDE_DIR ${INSTALL_DIR}/include)
set(LIBRARY_DIR ${INSTALL_DIR}/lib${LIB_SUFFIX})
include_directories(${INCLUDE_DIR}
                    ${INCLUDE_DIR}/cjson
                    ${CURL_INCLUDE_DIRS}
					${INCLUDE_DIR}/cimplog)
				
include_directories (SYSTEM /usr/include)

if (NOT BUILD_YOCTO)

# cJSON external dependency
ExternalProject_Add(cJSON
    PREFIX ${PREFIX_DIR}/cJSON
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG "aafb64a1c549b7b927e339df6d35b1d5059dc235"
    CMAKE_ARGS += -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
)
add_library(libcjson STATIC IMPORTED)
add_dependencies(libcjson cjson)


# cimplog external dependency
ExternalProject_Add(cimplog
    PREFIX ${PREFIX_DIR}/cimplog
    GIT_REPOSITORY https://github.com/Comcast/cimplog.git
    GIT_TAG "master"
    CMAKE_ARGS += -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
                  -DBUILD_TESTING=OFF
)
add_library(libcimplog STATIC IMPORTED)
add_dependencies(libcimplog cimplog)

endif ()

enable_testing()

include(CTest)

add_subdirectory(src)
if (BUILD_TESTING)
  add_subdirectory(tests)
endif (BUILD_TESTING)
