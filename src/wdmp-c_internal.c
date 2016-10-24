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
#include "wdmp-c_internal.h"
/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */
/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/

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

void wdmp_form_get_response(res_struct *resObj, cJSON *response)
{
        cJSON *parameters = NULL,*resParamObj = NULL, *value = NULL, *valueObj = NULL;
        size_t i, paramCount, j;
        char *result = NULL;
        WDMP_RESPONSE_STATUS_CODE statusCode = WDMP_STATUS_GENERAL_FALURE;
        
        printf("resObj->paramCnt : %lu\n",resObj->paramCnt);
        paramCount = resObj->paramCnt;
        printf("paramCount : %lu\n",paramCount);
        result = (char *) malloc(sizeof(char) * MAX_PARAMETER_LEN);
                
        if(resObj->u.getRes)
        {
                
                getStatusCode(&statusCode, paramCount, resObj->retStatus);
                printf("statusCode : %d\n",statusCode);
                if(statusCode == WDMP_STATUS_SUCCESS)
                {
                        cJSON_AddItemToObject(response, "parameters", parameters =cJSON_CreateArray());
                        printf("resObj->u.getRes->paramCnt : %lu\n",resObj->u.getRes->paramCnt);
                        for (i = 0; i < paramCount; i++) 
                        {
                                cJSON_AddItemToArray(parameters, resParamObj = cJSON_CreateObject());
                                printf("resObj->u.getRes->retParamCnt[%lu] : %lu\n",i,resObj->u.getRes->retParamCnt[i]);
                                if(resObj->u.getRes->retParamCnt[i] >= 1)
                                {
		                        if(resObj->u.getRes->retParamCnt[i] > 1)
		                        {
		                                printf("resObj->u.getRes->paramNames[%lu] : %s\n",i,resObj->u.getRes->paramNames[i]);
                                                cJSON_AddStringToObject(resParamObj, "name", resObj->u.getRes->paramNames[i]);
                                                cJSON_AddItemToObject(resParamObj, "value",value = cJSON_CreateArray());
                                                for (j = 0; j < resObj->u.getRes->retParamCnt[i]; j++) 
                                                {
                                                        cJSON_AddItemToArray(value, valueObj = cJSON_CreateObject());
                                                        printf("resObj->u.getRes->params[%lu][%lu].name :%s\n",i,j,resObj->u.getRes->params[i][j].name);
                                                        cJSON_AddStringToObject(valueObj, "name", resObj->u.getRes->params[i][j].name);
		                                        printf("resObj->u.getRes->params[%lu][%lu].value :%s\n",i,j,resObj->u.getRes->params[i][j].value);
		                                        cJSON_AddStringToObject(valueObj, "value",resObj->u.getRes->params[i][0].value);
		                                        printf("resObj->u.getRes->params[%lu][%lu].type :%d\n",i,j,resObj->u.getRes->params[i][j].type);
		                                        cJSON_AddNumberToObject(valueObj, "dataType",resObj->u.getRes->params[i][j].type);
                                                }
                                                cJSON_AddNumberToObject(resParamObj, "dataType",WDMP_NONE);
		                                cJSON_AddNumberToObject(resParamObj, "parameterCount", resObj->u.getRes->retParamCnt[i]);
		                                mapWdmpStatusToStatusMessage(resObj->retStatus[i], result);
		                                cJSON_AddStringToObject(resParamObj, "message", result);
		                        }
		                        else
		                        {
		                                printf("resObj->u.getRes->params[%lu][0].name :%s\n",i,resObj->u.getRes->params[i][0].name);
                                                cJSON_AddStringToObject(resParamObj, "name", resObj->u.getRes->params[i][0].name);
		                                printf("resObj->u.getRes->params[%lu][0].value :%s\n",i,resObj->u.getRes->params[i][0].value);
		                                cJSON_AddStringToObject(resParamObj, "value",resObj->u.getRes->params[i][0].value);
		                                printf("resObj->u.getRes->params[%lu][0].type :%d\n",i,resObj->u.getRes->params[i][0].type);
		                                cJSON_AddNumberToObject(resParamObj, "dataType",resObj->u.getRes->params[i][0].type);
		                                cJSON_AddNumberToObject(resParamObj, "parameterCount", resObj->u.getRes->retParamCnt[i]);
		                                mapWdmpStatusToStatusMessage(resObj->retStatus[i], result);
		                                cJSON_AddStringToObject(resParamObj, "message", result);
		                        }
                                }
                                else
                                {
                                        printf("resObj->u.getRes->paramNames[%lu] : %s\n",i,resObj->u.getRes->paramNames[i]);
                                        cJSON_AddStringToObject(resParamObj, "name", resObj->u.getRes->paramNames[i]);
                                        cJSON_AddStringToObject(resParamObj, "value","EMPTY");
                                        cJSON_AddNumberToObject(resParamObj, "parameterCount", resObj->u.getRes->retParamCnt[i]);
                                }
                        }
                }
                else
                {
                        mapWdmpStatusToStatusMessage(resObj->retStatus[0], result);
		        cJSON_AddStringToObject(response, "message", result);
                }
        }
        
        cJSON_AddNumberToObject(response, "statusCode", statusCode);
        
        if(result)
        {
                free(result); 
        }
}

 void wdmp_form_get_attr_response(res_struct *resObj, cJSON *response)
{
        cJSON *parameters = NULL,*resParamObj = NULL, *attributes = NULL;
        size_t i, paramCount;
        char *result = NULL;
        int notification;
        WDMP_RESPONSE_STATUS_CODE statusCode = WDMP_STATUS_GENERAL_FALURE;
        
        printf("resObj->paramCnt : %lu\n",resObj->paramCnt);
        paramCount = resObj->paramCnt;
        printf("paramCount : %lu\n",paramCount);
                
        if(resObj->u.paramRes)
        {
                
                getStatusCode(&statusCode, paramCount, resObj->retStatus);
                result = (char *) malloc(sizeof(char) * MAX_PARAMETER_LEN);
                if(statusCode == WDMP_STATUS_SUCCESS)
                {
                        cJSON_AddItemToObject(response, "parameters", parameters =cJSON_CreateArray());
                        for (i = 0; i < paramCount; i++) 
                        {
                                cJSON_AddItemToArray(parameters, resParamObj = cJSON_CreateObject());
                                printf("resObj->u.paramRes->params[%lu].name :%s\n",i,resObj->u.paramRes->params[i].name);
                                cJSON_AddStringToObject(resParamObj, "name", resObj->u.paramRes->params[i].name);
                                cJSON_AddItemToObject(resParamObj, "attributes",attributes = cJSON_CreateObject());
                                printf("resObj->u.paramRes->params[%lu].value :%s\n",i,resObj->u.paramRes->params[i].value);
		                notification = atoi(resObj->u.paramRes->params[i].value);
		                printf("notification : %d\n", notification);
		                cJSON_AddNumberToObject(attributes, "notify", notification);
		                printf("resObj->retStatus[i] :%d\n",resObj->retStatus[i]);
                                mapWdmpStatusToStatusMessage(resObj->retStatus[i], result);
                                cJSON_AddStringToObject(resParamObj, "message", result);
                        }
                }
                else
                {
                        mapWdmpStatusToStatusMessage(resObj->retStatus[0], result);
		        cJSON_AddStringToObject(response, "message", result);
                }
                
                if(result)
                {
                        free(result); 
                }
        }
        
        printf("statusCode : %d\n",statusCode);
        cJSON_AddNumberToObject(response, "statusCode", statusCode);
        
}

 void wdmp_form_set_response(res_struct *resObj, cJSON *response)
{
        cJSON *parameters = NULL,*resParamObj = NULL;
        size_t i, paramCount;
        char *result = NULL;
        WDMP_RESPONSE_STATUS_CODE statusCode = WDMP_STATUS_GENERAL_FALURE;
        
        printf("resObj->paramCnt : %lu\n",resObj->paramCnt);
        paramCount = resObj->paramCnt;
        printf("paramCount : %lu\n",paramCount);  
        
        result = (char *) malloc(sizeof(char) * MAX_PARAMETER_LEN);
        
        if(resObj->u.paramRes->params)
        {
                cJSON_AddItemToObject(response, "parameters", parameters =cJSON_CreateArray());
                
                for (i = 0; i < paramCount; i++) 
                {
                        cJSON_AddItemToArray(parameters, resParamObj = cJSON_CreateObject());
                        
                        printf("resObj->u.paramRes->params[%lu].name :%s\n",i,resObj->u.paramRes->params[i].name);
                        cJSON_AddStringToObject(resParamObj, "name", resObj->u.paramRes->params[i].name);
                        
                        printf("resObj->retStatus[%lu] : %d\n",i,resObj->retStatus[i]);
                        mapWdmpStatusToStatusMessage(resObj->retStatus[i], result);
                        cJSON_AddStringToObject(resParamObj, "message", result);
                }
                
                printf("resObj->retStatus : %d\n",resObj->retStatus[0]);
                getStatusCode(&statusCode, paramCount, resObj->retStatus);
        
        }
        else
        {
                mapWdmpStatusToStatusMessage(resObj->retStatus[0], result);
	        cJSON_AddStringToObject(response, "message", result);
        }
        
        if(result)
        {
                free(result); 
        }
        printf("statusCode : %d\n",statusCode);
        cJSON_AddNumberToObject(response, "statusCode", statusCode);
}

 void wdmp_form_test_and_set_response(res_struct *resObj, cJSON *response)
{
        cJSON *parameters = NULL,*resParamObj = NULL;
        size_t i, paramCount;
        char *result = NULL;
        WDMP_RESPONSE_STATUS_CODE statusCode = WDMP_STATUS_GENERAL_FALURE;
        
        printf("resObj->paramCnt : %lu\n",resObj->paramCnt);
        paramCount = resObj->paramCnt;
        printf("paramCount : %lu\n",paramCount);
        
        result = (char *) malloc(sizeof(char) * MAX_PARAMETER_LEN);
                        
        if(resObj->u.paramRes->params)
        {
                cJSON_AddItemToObject(response, "parameters", parameters =cJSON_CreateArray());
                
                for (i = 0; i < paramCount; i++) 
                {
                        cJSON_AddItemToArray(parameters, resParamObj = cJSON_CreateObject());
                        printf("resObj->u.paramRes->params[%lu].name :%s\n",i,resObj->u.paramRes->params[i].name);
                        cJSON_AddStringToObject(resParamObj, "name", resObj->u.paramRes->params[i].name);
                        printf("resObj->u.paramRes->params[%lu].value :%s\n",i,resObj->u.paramRes->params[i].value);
                        cJSON_AddStringToObject(resParamObj, "value", resObj->u.paramRes->params[i].value);
                }
                
                mapWdmpStatusToStatusMessage(resObj->retStatus[0], result);
                cJSON_AddStringToObject(resParamObj, "message", result);
                
                printf("resObj->retStatus : %d\n",resObj->retStatus[0]);
                getStatusCode(&statusCode, 1, resObj->retStatus);
                
        }
        else
        {
                mapWdmpStatusToStatusMessage(resObj->retStatus[0], result);
                cJSON_AddStringToObject(resParamObj, "message", result);
        }
        
        if(result)
        {
                free(result); 
        }
        
        printf("statusCode : %d\n",statusCode);
        cJSON_AddNumberToObject(response, "statusCode", statusCode);
        
}

 void mapWdmpStatusToStatusMessage(WDMP_STATUS status, char *result) 
{
	if (status == WDMP_SUCCESS) 
	{ 
		strcpy(result,"Success");
	} 
	else if (status == WDMP_ERR_INVALID_PARAMETER_NAME) 
	{
		strcpy(result, "Invalid parameter name");
	} 
	else if (status == WDMP_ERR_INVALID_PARAMETER_TYPE) 
	{
		strcpy(result,"Invalid parameter type");
	}
	else if (status == WDMP_ERR_INVALID_PARAMETER_VALUE) 
	{
		strcpy(result,"Invalid parameter value");
	} 
	else if (status == WDMP_ERR_NOT_WRITABLE) 
	{
		strcpy(result,"Parameter is not writable");
	}
	else if (status == WDMP_ERR_NOT_EXIST) 
	{
		strcpy(result,"Parameter does not exist");
	} 
	else if (status == WDMP_FAILURE) 
	{
		strcpy(result,"Failure");
	} 
	else if (status == WDMP_ERR_TIMEOUT) 
	{
		strcpy(result,"Error Timeout");
	}
	else if (status == WDMP_ERR_SETATTRIBUTE_REJECTED) 
	{
		strcpy(result,"SetAttribute rejected");
	} 
	else if (status == WDMP_ERR_NAMESPACE_OVERLAP) 
	{
		strcpy(result,"Error namespace overlap");
	} 
	else if (status == WDMP_ERR_UNKNOWN_COMPONENT) 
	{
		strcpy(result,"Error unkown component");
	} 
	else if (status == WDMP_ERR_NAMESPACE_MISMATCH) 
	{
		strcpy(result,"Error namespace mismatch");
	} 
	else if (status == WDMP_ERR_UNSUPPORTED_NAMESPACE) 
	{
		strcpy(result,"Error unsupported namespace");
	} 
	else if (status == WDMP_ERR_DP_COMPONENT_VERSION_MISMATCH) 
	{
		strcpy(result,"Error component version mismatch");
	} 
	else if (status == WDMP_ERR_INVALID_PARAM) 
	{
		strcpy(result,"Invalid Param");
	}
	else if (status == WDMP_ERR_UNSUPPORTED_DATATYPE) 
	{
		strcpy(result,"Unsupported datatype");
	}
	else if (status == WDMP_ERR_WIFI_BUSY) 
	{
		strcpy(result,"WiFi is busy");
	}
	else if (status == WDMP_ERR_INVALID_ATTRIBUTES)
	{
	        strcpy(result,"Invalid attributes");
	}
	else if (status == WDMP_ERR_WILDCARD_NOT_SUPPORTED)
	{
	        strcpy(result,"Wildcard is not supported");
	}
	else if (status == WDMP_ERR_SET_OF_CMC_OR_CID_NOT_SUPPORTED)
	{
	        strcpy(result,"SET of CMC or CID is not supported");
	}
	else if (status == WDMP_ERR_VALUE_IS_EMPTY)
	{
	        strcpy(result,"Parameter value field is not available");
	}
	else if (status == WDMP_ERR_VALUE_IS_NULL)
	{
	        strcpy(result,"Parameter value is null");
	}
	else if (status == WDMP_ERR_DATATYPE_IS_NULL)
	{
	        strcpy(result,"Parameter dataType is null");
	}
	else if (status == WDMP_ERR_CMC_TEST_FAILED)
	{
	        strcpy(result,"CMC test failed");
	}
	else if (status == WDMP_ERR_NEW_CID_IS_MISSING)
	{
	        strcpy(result,"New-Cid is missing");
	}
	else if (status == WDMP_ERR_CID_TEST_FAILED)
	{
	        strcpy(result,"CID test failed");
	}
	else if (status == WDMP_ERR_ATOMIC_GET_SET_FAILED)
	{
	        strcpy(result,"Atomic Set failed");
	}
	else if (status == WDMP_ERR_SETTING_CMC_OR_CID)
	{
	        strcpy(result,"Error setting CID/CMC");
	}else if (status == WDMP_ERR_INVALID_INPUT_PARAMETER)
	{
	        strcpy(result,"Invalid Input parameter - CID/CMC value cannot be set");
	}
	else 
	{
		strcpy(result,"Unknown Error");
	}
}

 void getStatusCode(WDMP_RESPONSE_STATUS_CODE *statusCode, int paramCount, WDMP_STATUS * ret)
{
	int i =0;
	for (i = 0; i < paramCount; i++) 
	{
		printf("ret[%d] = %d\n",i,ret[i]);
		if (ret[i] == WDMP_SUCCESS) 
		{
			*statusCode = WDMP_STATUS_SUCCESS;
		}
		else if (ret[i] == WDMP_ERR_WIFI_BUSY)
		{
			*statusCode = WDMP_STATUS_WIFI_BUSY;
			break;
		}
		else if (ret[i] == WDMP_ERR_CMC_TEST_FAILED)
		{
			*statusCode = WDMP_STATUS_CMC_TEST_FAILED;
			break;
		}
		else if (ret[i] == WDMP_ERR_CID_TEST_FAILED)
		{
			*statusCode = WDMP_STATUS_CID_TEST_FAILED;
			break;
		}
		else if (ret[i] == WDMP_ERR_ATOMIC_GET_SET_FAILED)
		{
			*statusCode = WDMP_STATUS_ATOMIC_GET_SET_FAILED;
			break;
		}
		else 
		{
			*statusCode = WDMP_STATUS_GENERAL_FALURE;
			break;
		}
	}
	printf("statusCode = %d\n",*statusCode);
}
/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/* none */
