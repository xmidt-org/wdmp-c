/**
 * Copyright 2016 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef __WDMP_C_H__
#define __WDMP_C_H__

#include <stdbool.h>
#include <stdint.h>


typedef enum
{
    WDMP_STRING = 0,
    WDMP_INT,
    WDMP_UINT,
    WDMP_BOOLEAN,
    WDMP_DATETIME,
    WDMP_BASE64,
    WDMP_LONG,
    WDMP_ULONG,
    WDMP_FLOAT,
    WDMP_DOUBLE,
    WDMP_BYTE,
    WDMP_NONE
} DATA_TYPE;

typedef struct
{
    char *name;
    char *value;
    DATA_TYPE type;
} ParamVal;

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
/* none */

/**
 *  To parse command from given request
 *  @param payload [in]  payload from request
 *  
 */

void __wdmp_parse_request(char * payload );

/**
 *  To convert json to struct 
 *  @param request [in]  request
 *  @param paramvalArr [in]  paramvalArr struct to be updated
 *  @param paramCount [in]  parameter count
 *  @param command [in]  GET /SET request 
 *  
 */

void __wdmp_json_to_struct(char * request, ParamVal  **paramvalArr,int *paramCount,char * command);

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/* none */

#endif
