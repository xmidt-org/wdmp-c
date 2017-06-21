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
#include "wdmp_internal.h"
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


/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

void wdmp_parse_generic_request(char * payload, PAYLOAD_TYPE payload_type, req_struct **reqObj)
{
    cJSON *request = NULL;
    char *out = NULL, *command = NULL;

    if (!payload || !reqObj)
    {
        WdmpPrint("wdmp_parse_generic_request - invalid param!\n");
        return;
    }

    request = cJSON_Parse(payload);
    if (request != NULL)
    {
	if(cJSON_GetObjectItem(request, "command") != NULL)
	{
		
        	command = cJSON_GetObjectItem(request, "command")->valuestring;
        	WdmpPrint("command %s\n", (command == NULL) ? "NULL" : command);
	}
	
        if (command != NULL)
        {
            out = cJSON_PrintUnformatted(request);

            //allocate structure according to payload type
            if (payload_type == WDMP_TR181 || payload_type == WDMP_SNMP)
            {
                (*reqObj) = (req_struct *) malloc(sizeof(req_struct));
                memset((*reqObj), 0, sizeof(req_struct));
            }
            else
            {
                // allocate according to payload type.
                // - currently no other data types supported
                WdmpPrint("wdmp_parse_generic_request - invalid payload_type : %d\n", payload_type);
                cJSON_Delete(request);
                return;
            }

            if ((strcmp(command, "GET") == 0) || (strcmp(command, "GET_ATTRIBUTES") == 0))
            {
                WdmpInfo("Request %s\n", out);
                parse_get_request(request, reqObj, payload_type);
            }
            else if ((strcmp(command, "SET") == 0))
            {
                WdmpInfo("SET Request: %s\n", out);
                parse_set_request(request, reqObj, payload_type);
            }
            else if ((strcmp(command, "SET_ATTRIBUTES") == 0))
            {
                WdmpInfo("SET ATTRIBUTES Request: %s\n", out);
                parse_set_attr_request(request, reqObj);
            }
            else if (strcmp(command, "TEST_AND_SET") == 0)
            {
                WdmpInfo("Test and Set Request: %s\n", out);
                parse_test_and_set_request(request, reqObj);
            }
            else if (strcmp(command, "REPLACE_ROWS") == 0)
            {
                WdmpInfo("REPLACE_ROWS Request: %s\n", out);
                parse_replace_rows_request(request, reqObj);
            }
            else if (strcmp(command, "ADD_ROW") == 0)
            {
                WdmpInfo("ADD_ROW Request: %s\n", out);
                parse_add_row_request(request, reqObj);
            }
            else if (strcmp(command, "DELETE_ROW") == 0)
            {
                WdmpInfo("DELETE_ROW Request: %s\n", out);
                parse_delete_row_request(request, reqObj);
            }
            else
            {
                WdmpError("Unknown Command \n");
                wdmp_free_req_struct(*reqObj);
                (*reqObj) = NULL;
            }

            if (out != NULL)
            {
                free(out);
            }
        }

        cJSON_Delete(request);
    }
    else
    {
        WdmpInfo("Empty payload\n");
    }

    return;
}

void wdmp_parse_request(char * payload, req_struct **reqObj)
{
	wdmp_parse_generic_request(payload, WDMP_TR181, reqObj);
	return;
}

void wdmp_form_response(res_struct *resObj, char **payload)
{
        cJSON *response = NULL;
        
        if(resObj != NULL)
	{
	        response = cJSON_CreateObject();
	        WdmpPrint("resObj->reqType: %d\n",resObj->reqType);
	        
                switch( resObj->reqType ) 
                {
                
                        case GET:
                        {
                                wdmp_form_get_response(resObj, response);
                        }
                        break;
                        
                        case GET_ATTRIBUTES:
                        {
                                wdmp_form_get_attr_response(resObj, response);
                        }
                        break;
                        
                        case SET:
                        case SET_ATTRIBUTES:
                        {
		                wdmp_form_set_response(resObj, response);
                        }
                        break;
                        
                        case TEST_AND_SET:
                        {
		                wdmp_form_test_and_set_response(resObj, response);
                        }
                        break;
                        
                        case REPLACE_ROWS:
                        case DELETE_ROW:
                        case ADD_ROWS:
                        {
                                wdmp_form_table_response(resObj, response);
                        }
                        break;
                        
                        default:
                        {
                                WdmpError("Unknown request type\n");
                                wdmp_free_res_struct(resObj );
                                resObj = NULL;
                                cJSON_Delete(response);
                                response = NULL;
                        }
                        break;
                }
	}
	else
	{		
		response = cJSON_CreateObject();
		cJSON_AddStringToObject(response, "message", "Invalid Input Command");	
		cJSON_AddNumberToObject(response, "statusCode", WDMP_STATUS_GENERAL_FALURE);	
	
	}
	
	
        if(response != NULL)
	{
                *payload = cJSON_PrintUnformatted(response);
                WdmpInfo("Response Payload :%s\n", *payload);
		cJSON_Delete(response);
	}

}

void wdmp_free_req_struct( req_struct *reqObj )
{
    size_t i, j;

    switch( reqObj->reqType ) 
    {
        case GET:
        case GET_ATTRIBUTES:
        {
            if(reqObj->u.getReq)
            {
                for(i = 0; i < reqObj->u.getReq->paramCnt; i++)
                {
                    free(reqObj->u.getReq->paramNames[i]);
                }
                free(reqObj->u.getReq);
            }     
        }
        break;

        case SET:
        case SET_ATTRIBUTES:
        {
            if(reqObj->u.setReq)
            {
                if(reqObj->u.setReq->param)
                {
                    for (i = 0; i < reqObj->u.setReq->paramCnt; i++)
                    {
                        free(reqObj->u.setReq->param[i].name); 
                        free(reqObj->u.setReq->param[i].value);
                    }
                    free(reqObj->u.setReq->param);
                }
                free(reqObj->u.setReq);
            }
        }
        break;

        case TEST_AND_SET:
        {
            if(reqObj->u.testSetReq)
            {
                if(reqObj->u.testSetReq->newCid)
                {
                    free(reqObj->u.testSetReq->newCid);
                }

                if(reqObj->u.testSetReq->oldCid)
                {
                    free(reqObj->u.testSetReq->oldCid);
                }

                if(reqObj->u.testSetReq->syncCmc)
                {
                    free(reqObj->u.testSetReq->syncCmc);
                }

                if(reqObj->u.testSetReq->param)
                {
                    for(i=0; i< reqObj->u.testSetReq->paramCnt; i++)
                    {
                        free(reqObj->u.testSetReq->param[i].name);
                        free(reqObj->u.testSetReq->param[i].value);
                    }
                    free(reqObj->u.testSetReq->param);
                }
                free(reqObj->u.testSetReq);
            }
        }
        break;

        case REPLACE_ROWS:
        case ADD_ROWS:
        case DELETE_ROW:
        {
            if(reqObj->u.tableReq)
            {
                if(reqObj->u.tableReq->objectName)
                {
                    free(reqObj->u.tableReq->objectName);
                }
                if(reqObj->u.tableReq->rows)
                {
                    for (i = 0; i < reqObj->u.tableReq->rowCnt; i++)
                    {
                        for(j=0; j<reqObj->u.tableReq->rows[i].paramCnt; j++)
                        {
                            free(reqObj->u.tableReq->rows[i].names[j]);
                            free(reqObj->u.tableReq->rows[i].values[j]);
                        } 
                        free(reqObj->u.tableReq->rows[i].names);
                        free(reqObj->u.tableReq->rows[i].values);
                    }
                    free(reqObj->u.tableReq->rows);
                }
                free(reqObj->u.tableReq);
            }
        }
        break;

        default:
        WdmpError("Unknown request type\n");
    }
    free(reqObj);
}

void wdmp_free_res_struct( res_struct *resObj )
{
        size_t i, j;
        switch( resObj->reqType ) 
        {
                case GET:
                {
                        if(resObj->u.getRes)
                        {
                                if(resObj->u.getRes->paramNames)
                                {
                                        free(resObj->u.getRes->paramNames);
                                }
                                
                                if(resObj->u.getRes->params)
                                {
                                        for (i = 0; i < resObj->u.getRes->paramCnt; i++)
                                        {
                                                if(resObj->u.getRes->params[i])
                                                {
                                                        for (j = 0; j < resObj->u.getRes->retParamCnt[i]; j++)
                                                        { 
                                                                free(resObj->u.getRes->params[i][j].name);
                                                                free(resObj->u.getRes->params[i][j].value);
                                                        }
                                                        free(resObj->u.getRes->params[i]);
                                                }
                                        }
                                        free(resObj->u.getRes->params);
                                }
                                
                                if(resObj->u.getRes->retParamCnt)
                                {
                                        free(resObj->u.getRes->retParamCnt);
                                }
                                
                                free(resObj->u.getRes);
                        }
                }
                break;
                
                case GET_ATTRIBUTES:
                case SET:
                case SET_ATTRIBUTES:
                case TEST_AND_SET:
                {
                        if(resObj->u.paramRes)
                        {
                                if(resObj->u.paramRes->params)
                                {
                                        for (i = 0; i < resObj->paramCnt; i++)
                                        { 
                                                free(resObj->u.paramRes->params[i].name);
                                                if(resObj->u.paramRes->params[i].value)
                                                {
                                                	free(resObj->u.paramRes->params[i].value);
                                                }
                                        }
                                        free(resObj->u.paramRes->params);
                                }
                                if(resObj->u.paramRes->syncCMC)
                                {
                                        free(resObj->u.paramRes->syncCMC);
                                }
                                if(resObj->u.paramRes->syncCID)
                                {
                                        free(resObj->u.paramRes->syncCID);
                                }
                                free(resObj->u.paramRes);
                        }
                }
                break;
                
                case REPLACE_ROWS:
                case ADD_ROWS:
                case DELETE_ROW:
                {
                        if(resObj->u.tableRes)
                        {
                                if(resObj->u.tableRes->newObj)
                                {
                                        free(resObj->u.tableRes->newObj);
                                }
                                free(resObj->u.tableRes);
                        }
                }
                break;
        }
        
        if(resObj->timeSpan)
        {
                if(resObj->timeSpan->spans)
                {
                        free(resObj->timeSpan->spans);
                }
                free(resObj->timeSpan);
        }
        
        if(resObj->retStatus)
        {
        
                free(resObj->retStatus);
        }
        
        free(resObj);
}
/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/

