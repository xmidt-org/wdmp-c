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
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>

#include "wdmp-c.h"
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

void __wdmp_parse_request(char * payload)
{
    cJSON *request = NULL;
    char * command = NULL;
    char *out = NULL;
    
    request=cJSON_Parse(payload);
    
    
    if(request != NULL)
	{
		cJSON *response = cJSON_CreateObject();

		out = cJSON_PrintUnformatted(request);
		printf("Request: %s\n", out);
		free(out);
		
		command = cJSON_GetObjectItem(request, "command")->valuestring;
	
		printf("\ncommand %s\n",(command == NULL) ? "NULL" : command);

		if( command != NULL) 
		{
			out = cJSON_Print(request);
			if (strcmp(command, "GET") == 0)
			{
				printf("Get Request %s\n", out);
				
			}
			else if (strcmp(command, "GET_ATTRIBUTES") == 0)
			{
				printf("Get attribute Request %s\n", out);
				
			}
			else if (strcmp(command, "SET") == 0)
			{
				printf("\nSet Request: %s\n", out);
								
			}
			else if(strcmp(command, "SET_ATTRIBUTES") == 0)
			{
				printf("\nSet attribute Request: %s\n", out);
				
			}
		
			else if (strcmp(command, "SET_ATOMIC") == 0)
			{
				printf("\nSet Atomic Request: %s\n", out);
				
			}
			else if (strcmp(command, "TEST_AND_SET") == 0)
			{
				printf("\nTest and Set Request: %s\n", out);
				
			}
			else if (strcmp(command, "REPLACE_ROWS") == 0)
			{
				printf("\n REPLACE_ROWS Request: %s\n", out);
				
			}
			else if (strcmp(command, "ADD_ROW") == 0)
			{
				printf("\n ADD_ROW Request: %s\n", out);
				
				
			}
			else if (strcmp(command, "DELETE_ROW") == 0)
			{
				printf("\n DELETE_ROW Request: %s\n", out);
				
			}
			free(out);
											
		}
				
		if(request != NULL)
		{
			cJSON_Delete(request);
		}
		if(response != NULL)
		{
			cJSON_Delete(response);
		} 
		
	}
    
}


void __wdmp_json_to_struct(char * request, ParamVal  **paramvalArr,int *paramCount,char * command)
{
    cJSON *reqParamObj;
    cJSON * processRequest=cJSON_Parse(request);
    int i;
    cJSON *paramArray = cJSON_GetObjectItem(processRequest, "parameters");
    int parameterCount = cJSON_GetArraySize(paramArray);
    printf("parameterCount is %d \n",parameterCount);
    *paramCount = parameterCount;
    ParamVal *parametervalArr = (ParamVal *) malloc(sizeof(ParamVal) * parameterCount);
    for (i = 0; i < parameterCount; i++) 
	{
	    
	    reqParamObj = cJSON_GetArrayItem(paramArray, i);
	    
	    // Process param name for GET request
	    parametervalArr[i].name = cJSON_GetObjectItem(reqParamObj, "name")->valuestring; 
	    
	    
	    // Process value and datatype only for SET request
	    if(strcmp(command,"SET")==0)
	    {
	    
	        if (cJSON_GetObjectItem(reqParamObj, "value") == NULL)
		    {
		        printf("Value field is not available in param\n");
		        break;
		    }
		    else
		    {
		        if(cJSON_GetObjectItem(reqParamObj, "value")->valuestring != NULL && strlen(cJSON_GetObjectItem(reqParamObj, "value")->valuestring) == 0)
			    {
			        printf("Param value is NULL");
			        break;
			    }
			    else if(cJSON_GetObjectItem(reqParamObj, "value")->valuestring == NULL)
			    {
			        printf("Parameter value field is not a string\n");
			        break;
			    }
			    else
			    {
			        parametervalArr[i].value = cJSON_GetObjectItem(reqParamObj, "value")->valuestring;
			        
			    }
				
		    }
		    if (cJSON_GetObjectItem(reqParamObj, "dataType") == NULL)
		    {
			    printf("parameter datatype is NULL\n");
		       	break;
		    }
		    else
		    {
			    parametervalArr[i].type = cJSON_GetObjectItem(reqParamObj, "dataType")->valueint;
			    
		    }
		
		}
	}
	
    	*paramvalArr = parametervalArr;
        cJSON_Delete(processRequest);
}


/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/* none */
