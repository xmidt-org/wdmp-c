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
void parse_get_request(cJSON *request, req_struct **reqObj);
void parse_set_request(cJSON *request, req_struct **reqObj);
void parse_test_and_set_request(cJSON *request, req_struct **reqObj);
void parse_replace_rows_request(cJSON *request, req_struct **reqObj);
void parse_add_row_request(cJSON *request, req_struct **reqObj);
void parse_delete_row_request(cJSON *request, req_struct **reqObj);
/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
/* none */

void wdmp_parse_request(char * payload, req_struct **reqObj)
{
	cJSON *request = NULL;
	char *out = NULL, *command = NULL;
	
	printf("----- Start of wdmp_parse_request ------\n"); 
	
	request=cJSON_Parse(payload);
	
	if(request != NULL)
	{
		command = cJSON_GetObjectItem(request, "command")->valuestring;
		printf("\ncommand %s\n",(command == NULL) ? "NULL" : command);
		
	
		if( command != NULL) 
		{
			out = cJSON_Print(request);
			(*reqObj) = (req_struct *) malloc(sizeof(req_struct));
			memset( (*reqObj), 0, sizeof( req_struct ) );
			
			if ((strcmp(command, "GET") == 0)|| (strcmp(command, "GET_ATTRIBUTES") == 0))
			{
				printf("Request %s\n", out);
				parse_get_request(request, reqObj);
			
			}
		
			else if ((strcmp(command, "SET") == 0) || (strcmp(command, "SET_ATTRIBUTES") == 0))
			{
				printf("\nSET Request: %s\n", out);
				parse_set_request(request, reqObj);

						
			}
			
			else if (strcmp(command, "TEST_AND_SET") == 0)
			{
				printf("\nTest and Set Request: %s\n", out);
				parse_test_and_set_request(request, reqObj);

			}
			
			else if (strcmp(command, "REPLACE_ROWS") == 0)
			{
				printf("\n REPLACE_ROWS Request: %s\n", out);
				parse_replace_rows_request(request, reqObj);
				
			
			}
			else if (strcmp(command, "ADD_ROW") == 0)
			{
				printf("\n ADD_ROW Request: %s\n", out);
				parse_add_row_request(request, reqObj);
						
			}
			
			else if (strcmp(command, "DELETE_ROW") == 0)
			{
				printf("\n DELETE_ROW Request: %s\n", out);
				parse_delete_row_request(request, reqObj);

			}
			
			else
			{
				printf("\n Unknown Command \n");
				wdmp_free_req_struct(*reqObj );
				(*reqObj) = NULL;
			}
		}
    	}
    	else
	{
		printf("Empty payload\n");
	}
    	
    	printf("----- End of wdmp_parse_request ------\n"); 
	   	
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
                printf("Unknown request type\n");
        }
        free(reqObj);
}

void parse_get_request(cJSON *request, req_struct **reqObj)
{

	cJSON *paramArray = NULL;	
	size_t paramCount, i;	
	
	(*reqObj)->u.getReq = (get_req_t *) malloc(sizeof(get_req_t));
	memset((*reqObj)->u.getReq,0,(sizeof(get_req_t)));

	char *param = NULL;
	(*reqObj)->reqType = GET;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	paramArray = cJSON_GetObjectItem(request, "names");
	paramCount = cJSON_GetArraySize(paramArray);
	(*reqObj)->u.getReq->paramCnt = paramCount;
	printf("(*reqObj)->u.getReq->paramCnt : %lu\n",(*reqObj)->u.getReq->paramCnt);
	
	for (i = 0; i < paramCount; i++) 
	{
		(*reqObj)->u.getReq->paramNames[i] = cJSON_GetArrayItem(paramArray, i)->valuestring;
		printf("(*reqObj)->u.getReq->paramNames[%lu] : %s\n",i,(*reqObj)->u.getReq->paramNames[i]);
	}

	if((cJSON_GetObjectItem(request, "attributes") != NULL) && (strncmp(cJSON_GetObjectItem(request, "attributes")->valuestring, "notify", 6) == 0))
	{
		(*reqObj)->reqType = GET_ATTRIBUTES;
		printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
		for (i = 0; i < paramCount; i++) 
		{
			param = (cJSON_GetArrayItem(paramArray, i)->valuestring);
	                printf("param : %s\n",param);
			(*reqObj)->u.getReq->paramNames[i] = param;
			printf("(*reqObj)->u.getReq->paramNames[%lu] : %s\n",i,(*reqObj)->u.getReq->paramNames[i]);
			
		}
	}
	
}

void parse_set_request(cJSON *request, req_struct **reqObj)
{

	cJSON *reqParamObj = NULL, *attributes = NULL,*paramArray = NULL;	
	size_t paramCount, i;
	int notification;
	char notif[20] = "";
	
	printf("parsing Set Request\n");
	
	(*reqObj)->reqType = SET_ATTRIBUTES;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	paramArray = cJSON_GetObjectItem(request, "parameters");
	paramCount = cJSON_GetArraySize(paramArray);

	(*reqObj)->u.setReq = (set_req_t *) malloc(sizeof(set_req_t));
	memset((*reqObj)->u.setReq,0,(sizeof(set_req_t)));

	(*reqObj)->u.setReq->paramCnt = paramCount;
	printf("(*reqObj)->u.setReq->paramCnt : %lu\n",(*reqObj)->u.setReq->paramCnt);
	(*reqObj)->u.setReq->param = (param_t *) malloc(sizeof(param_t) * paramCount);
	memset((*reqObj)->u.setReq->param,0,(sizeof(param_t) * paramCount));

	for (i = 0; i < paramCount; i++) 
	{
		reqParamObj = cJSON_GetArrayItem(paramArray, i);
		(*reqObj)->u.setReq->param[i].name = cJSON_GetObjectItem(reqParamObj, "name")->valuestring;
		printf("(*reqObj)->u.setReq->param[%lu].name : %s\n",i,(*reqObj)->u.setReq->param[i].name);
		
		if (cJSON_GetObjectItem(reqParamObj, "value") != NULL )
		{
			(*reqObj)->reqType = SET;
			(*reqObj)->u.setReq->param[i].value = cJSON_GetObjectItem(reqParamObj, "value")->valuestring;
			printf("(*reqObj)->u.setReq->param[%lu].value : %s\n",i,(*reqObj)->u.setReq->param[i].value);
		}
	
		if (cJSON_GetObjectItem(reqParamObj, "attributes") != NULL )
		{
			attributes = cJSON_GetObjectItem(reqParamObj, "attributes");
			if(cJSON_GetObjectItem(attributes, "notify") != NULL) 
			{
				notification = cJSON_GetObjectItem(attributes, "notify")->valueint;
				printf("notification :%d\n",notification);
				snprintf(notif, sizeof(notif), "%d", notification);
				(*reqObj)->u.setReq->param[i].value = (char *) malloc(sizeof(char) * 20);
				strcpy((*reqObj)->u.setReq->param[i].value, notif);
				printf("(*reqObj)->u.setReq->param[%lu].value : %s\n",i,(*reqObj)->u.setReq->param[i].value);
			}
		}
	
		
		if (cJSON_GetObjectItem(reqParamObj, "dataType") != NULL)
		{
			(*reqObj)->u.setReq->param[i].type = cJSON_GetObjectItem(reqParamObj, "dataType")->valueint;
			printf("(*reqObj)->u.setReq->param[%lu].type : %d\n",i,(*reqObj)->u.setReq->param[i].type);
		}
	}
			
}

void parse_test_and_set_request(cJSON *request, req_struct **reqObj)
{

	cJSON *reqParamObj = NULL, *paramArray = NULL;	
	size_t paramCount, i;
	
	printf("parsing Test and Set Request\n");
	(*reqObj)->reqType = TEST_AND_SET;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	
	paramArray = cJSON_GetObjectItem(request, "parameters");
	paramCount = cJSON_GetArraySize(paramArray);
	
	(*reqObj)->u.testSetReq = (test_set_req_t *) malloc(sizeof(test_set_req_t));
	memset((*reqObj)->u.testSetReq,0,(sizeof(test_set_req_t)));	
	(*reqObj)->u.testSetReq->paramCnt = paramCount;
	printf("(*reqObj)->u.testSetReq->paramCnt : %lu\n",(*reqObj)->u.testSetReq->paramCnt);
	
	(*reqObj)->u.testSetReq->param = (param_t *) malloc(sizeof(param_t) * paramCount);
	
	if(cJSON_GetObjectItem(request, "old-cid") != NULL)
        {
                (*reqObj)->u.testSetReq->oldCid = cJSON_GetObjectItem(request, "old-cid")->valuestring;
                printf("(*reqObj)->u.testSetReq->oldCid : %s\n",(*reqObj)->u.testSetReq->oldCid);
        }
        if(cJSON_GetObjectItem(request, "new-cid") != NULL)
        {
                (*reqObj)->u.testSetReq->newCid = cJSON_GetObjectItem(request, "new-cid")->valuestring;
                printf("(*reqObj)->u.testSetReq->newCid : %s\n",(*reqObj)->u.testSetReq->newCid);
        }
        if(cJSON_GetObjectItem(request, "sync-cmc") != NULL)
        {
	        (*reqObj)->u.testSetReq->syncCmc = cJSON_GetObjectItem(request, "sync-cmc")->valuestring;
	        printf("(*reqObj)->u.testSetReq->syncCmc : %s\n",(*reqObj)->u.testSetReq->syncCmc);
        }
	for (i = 0; i < paramCount; i++) 
	{
		reqParamObj = cJSON_GetArrayItem(paramArray, i);
		(*reqObj)->u.testSetReq->param[i].name = cJSON_GetObjectItem(reqParamObj, "name")->valuestring;
		printf("(*reqObj)->u.testSetReq->param[%lu].name : %s\n",i,(*reqObj)->u.testSetReq->param[i].name);
		
		if (cJSON_GetObjectItem(reqParamObj, "value") != NULL)
		{
			(*reqObj)->u.testSetReq->param[i].value = cJSON_GetObjectItem(reqParamObj, "value")->valuestring;
			printf("(*reqObj)->u.testSetReq->param[%lu].value : %s\n",i,(*reqObj)->u.testSetReq->param[i].value);
			
		}
		
		if (cJSON_GetObjectItem(reqParamObj, "dataType") != NULL)
		{
			(*reqObj)->u.testSetReq->param[i].type = cJSON_GetObjectItem(reqParamObj, "dataType")->valueint;
			printf("(*reqObj)->u.testSetReq->param[%lu].type : %d\n",i,(*reqObj)->u.testSetReq->param[i].type);
		}
	}
}
		
void parse_replace_rows_request(cJSON *request, req_struct **reqObj)
{
	
	cJSON *paramArray = NULL, *subitem = NULL;	
	size_t paramCount,rowCnt, i, j;
	
	printf("parsing Replace Rows Request\n");
	(*reqObj)->reqType = REPLACE_ROWS;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	
	paramArray = cJSON_GetObjectItem(request, "rows");
	rowCnt = cJSON_GetArraySize(paramArray);
	printf("rowCnt : %lu\n",rowCnt);
	
	(*reqObj)->u.tableReq = (table_req_t *) malloc(sizeof(table_req_t));
	memset((*reqObj)->u.tableReq,0,(sizeof(table_req_t)));
	
	(*reqObj)->u.tableReq->rowCnt = rowCnt;
	printf("(*reqObj)->u.tableReq->rowCnt : %lu\n",(*reqObj)->u.tableReq->rowCnt);
	(*reqObj)->u.tableReq->objectName = cJSON_GetObjectItem(request,"table")->valuestring;
	(*reqObj)->u.tableReq->rows = (TableData *) malloc(sizeof(TableData) * rowCnt);
	memset((*reqObj)->u.tableReq->rows,0,(sizeof(TableData) * rowCnt));
	
        for ( i = 0 ; i < rowCnt ; i++)
        {
                subitem = cJSON_GetArrayItem(paramArray, i);
	        paramCount = cJSON_GetArraySize(subitem);
	 	printf("paramCount: %lu\n",paramCount);
	        (*reqObj)->u.tableReq->rows[i].paramCnt = paramCount;
	        printf("(*reqObj)->u.tableReq->rows[%lu].paramCnt : %lu\n",i,(*reqObj)->u.tableReq->rows[i].paramCnt);
	        
	        (*reqObj)->u.tableReq->rows[i].names = (char **) malloc(sizeof(char *) * paramCount);
	        (*reqObj)->u.tableReq->rows[i].values = (char **) malloc(sizeof(char *) * paramCount);
	        for( j = 0 ; j < paramCount ; j++)
	        {
		        (*reqObj)->u.tableReq->rows[i].names[j] = cJSON_GetArrayItem(subitem, j)->string;
		        printf("(*reqObj)->u.tableReq->rows[%lu].names[%lu] : %s\n",i,j,(*reqObj)->u.tableReq->rows[i].names[j]);		
		        		
		        (*reqObj)->u.tableReq->rows[i].values[j] = cJSON_GetArrayItem(subitem, j)->valuestring;
		        printf("(*reqObj)->u.tableReq->rows[%lu].values[%lu] : %s\n",i,j,(*reqObj)->u.tableReq->rows[i].values[j]);	
		        	
	        }
	}
}

void parse_add_row_request(cJSON *request, req_struct **reqObj)
{

	cJSON *paramArray = NULL;	
	size_t paramCount, i;
	
	printf("parsing Add Row Request\n");
	(*reqObj)->reqType = ADD_ROWS;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	
	paramArray = cJSON_GetObjectItem(request, "row");
	paramCount = cJSON_GetArraySize(paramArray);
	printf("paramCount : %lu\n",paramCount);
	
	(*reqObj)->u.tableReq = (table_req_t *) malloc(sizeof(table_req_t));
	memset((*reqObj)->u.tableReq,0,(sizeof(table_req_t)));
	
	(*reqObj)->u.tableReq->rowCnt = 1;
	printf("(*reqObj)->u.tableReq->rowCnt : %lu\n",(*reqObj)->u.tableReq->rowCnt);
	(*reqObj)->u.tableReq->objectName = cJSON_GetObjectItem(request,"table")->valuestring;
	(*reqObj)->u.tableReq->rows = (TableData *) malloc(sizeof(TableData));
	memset((*reqObj)->u.tableReq->rows,0,(sizeof(TableData)));
	
	(*reqObj)->u.tableReq->rows->names = (char **) malloc(sizeof(char *) * paramCount);
        (*reqObj)->u.tableReq->rows->values = (char **) malloc(sizeof(char *) * paramCount);
        (*reqObj)->u.tableReq->rows->paramCnt = paramCount;
        printf("(*reqObj)->u.tableReq->rows->paramCnt : %lu\n",(*reqObj)->u.tableReq->rows->paramCnt);
        
        for ( i = 0 ; i < paramCount ; i++)
        {
	        (*reqObj)->u.tableReq->rows->names[i] = cJSON_GetArrayItem(paramArray, i)->string;
	         printf("(*reqObj)->u.tableReq->rows->names[%lu] : %s\n",i,(*reqObj)->u.tableReq->rows->names[i]);				
	        (*reqObj)->u.tableReq->rows->values[i] = cJSON_GetArrayItem(paramArray, i)->valuestring;
	        printf("(*reqObj)->u.tableReq->rows->values[%lu] : %s\n",i,(*reqObj)->u.tableReq->rows->values[i]);		
	        	
	}
}

void parse_delete_row_request(cJSON *request, req_struct **reqObj)
{
	
	printf("parsing Delete Row Request\n");
	(*reqObj)->reqType = DELETE_ROW;
	printf("(*reqObj)->reqType : %d\n",(*reqObj)->reqType);
	
	(*reqObj)->u.tableReq = (table_req_t *) malloc(sizeof(table_req_t));
	memset((*reqObj)->u.tableReq,0,(sizeof(table_req_t)));
	(*reqObj)->u.tableReq->objectName = cJSON_GetObjectItem(request,"row")->valuestring;
}
