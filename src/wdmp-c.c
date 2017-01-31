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

void wdmp_parse_request(char * payload, req_struct **reqObj)
{
	cJSON *request = NULL;
	char *out = NULL, *command = NULL;
	
	request=cJSON_Parse(payload);
		
	if(request != NULL)
	{
		command = cJSON_GetObjectItem(request, "command")->valuestring;
		WdmpPrint("WDMP-C: command %s\n",(command == NULL) ? "NULL" : command);
			
		if( command != NULL) 
		{
			out = cJSON_PrintUnformatted(request);
			(*reqObj) = (req_struct *) malloc(sizeof(req_struct));
			memset( (*reqObj), 0, sizeof( req_struct ) );
			
			if ((strcmp(command, "GET") == 0)|| (strcmp(command, "GET_ATTRIBUTES") == 0))
			{
				WdmpInfo("WDMP-C: Request %s\n", out);
				parse_get_request(request, reqObj);
			
			}		
			else if ((strcmp(command, "SET") == 0))
			{
				WdmpInfo("WDMP-C: SET Request: %s\n", out);
				parse_set_request(request, reqObj);
						
			}
			else if ((strcmp(command, "SET_ATTRIBUTES") == 0))
			{
				WdmpInfo("WDMP-C: SET ATTRIBUTES Request: %s\n", out);
				parse_set_attr_request(request, reqObj);
						
			}			
			else if (strcmp(command, "TEST_AND_SET") == 0)
			{
				WdmpInfo("WDMP-C: Test and Set Request: %s\n", out);
				parse_test_and_set_request(request, reqObj);

			}			
			else if (strcmp(command, "REPLACE_ROWS") == 0)
			{
				WdmpInfo("WDMP-C: REPLACE_ROWS Request: %s\n", out);
				parse_replace_rows_request(request, reqObj);				
			
			}
			else if (strcmp(command, "ADD_ROW") == 0)
			{
				WdmpInfo("WDMP-C: ADD_ROW Request: %s\n", out);
				parse_add_row_request(request, reqObj);
						
			}			
			else if (strcmp(command, "DELETE_ROW") == 0)
			{
				WdmpInfo("WDMP-C: DELETE_ROW Request: %s\n", out);
				parse_delete_row_request(request, reqObj);
			}			
			else
			{
				WdmpError("WDMP-C: Unknown Command \n");
				wdmp_free_req_struct(*reqObj );
				(*reqObj) = NULL;
			}
		}
    	}
    	else
	{
		WdmpInfo("WDMP-C: Empty payload\n");
	}
 	
}

void wdmp_form_response(res_struct *resObj, char **payload)
{
        cJSON *response = NULL;
        
        if(resObj != NULL)
	{
	        response = cJSON_CreateObject();
	        WdmpPrint("WDMP-C: resObj->reqType: %d\n",resObj->reqType);
	        
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
                                WdmpError("WDMP-C: Unknown request type\n");
                                wdmp_free_res_struct(resObj );
                                resObj = NULL;
                                cJSON_Delete(response);
                                response = NULL;
                        }
                        break;
                }
	}
	
        if(response != NULL)
	{
	        WdmpInfo("WDMP-C: Response Payload :%s\n",cJSON_PrintUnformatted(response));
                *payload = cJSON_PrintUnformatted(response);
		cJSON_Delete(response);
	}

}

void wdmp_free_req_struct( req_struct *reqObj )
{
        size_t i;

        switch( reqObj->reqType ) 
        {
                case GET:
                case GET_ATTRIBUTES:
                {
                        if(reqObj->u.getReq)
                        {
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
                                if(reqObj->u.testSetReq->param)
                                {
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
                                if(reqObj->u.tableReq->rows)
                                {
                                        for (i = 0; i < reqObj->u.tableReq->rowCnt; i++)
                                        { 
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
                WdmpError("WDMP-C: Unknown request type\n");
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
                                                free(resObj->u.paramRes->params[i].value);
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

