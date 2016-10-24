#   Copyright 2016 Comcast Cable Communications Management, LLC
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

set(PROJ_WDMP wdmp-c)

file(GLOB HEADERS wdmp-c.h wdmp-c_internal.h)
set(SOURCES wdmp-c.c wdmp-c_internal.c)

add_library(${PROJ_WDMP} STATIC ${HEADERS} ${SOURCES})
add_library(${PROJ_WDMP}.shared SHARED ${HEADERS} ${SOURCES})
set_target_properties(${PROJ_WDMP}.shared PROPERTIES OUTPUT_NAME ${PROJ_WDMP})

install (TARGETS ${PROJ_WDMP} DESTINATION lib${LIB_SUFFIX})
install (TARGETS ${PROJ_WDMP}.shared DESTINATION lib${LIB_SUFFIX})
install (FILES wdmp-c.h wdmp-c_internal.h DESTINATION include/${PROJ_WDMP})
