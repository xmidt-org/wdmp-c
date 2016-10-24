/**
 *  Copyright 2010-2016 Comcast Cable Communications Management, LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <cJSON.h>

#include "../src/wdmp-c.h"
#include "../src/wdmp-c_internal.h"

void get_req_parse ()
{
    printf("\n***************************************************** \n\n");
    int i,paramCount;
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":[\"Device.DeviceInfo.Webpa.Enable\",\"Device.DeviceInfo.Webpa.\"],\"command\": \"GET\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    
    printf("Request Type : %d\n",reqObj->reqType);
    
    CU_ASSERT_EQUAL( GET, reqObj->reqType );
    
    if(reqObj->u.getReq)
    {
        printf("ParamCount : %lu\n",reqObj->u.getReq->paramCnt);
        paramCount = (int)reqObj->u.getReq->paramCnt;
        for (i = 0; i < paramCount; i++) 
        {
            printf("paramNames[%d] : %s\n",i,reqObj->u.getReq->paramNames[i]);
            
        }
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.Webpa.Enable", reqObj->u.getReq->paramNames[0] );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.Webpa.", reqObj->u.getReq->paramNames[1] );
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }  
}

void get_attr_req_parse ()
{
    printf("\n***************************************************** \n\n");
    int i,paramCount;
    req_struct *reqObj = NULL;
    
    char * request= "{ \"names\":[\"Device.WiFi.SSID.1.Enable\",\"Device.WiFi.SSID.1.SSID\"],\"attributes\":\"notify\",\"command\": \"GET_ATTRIBUTES\"}";
    
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( GET_ATTRIBUTES, reqObj->reqType );
    
    printf("Request Type : %d\n",reqObj->reqType);
    printf("ParamCount : %lu\n",reqObj->u.getReq->paramCnt);
    paramCount = (int)reqObj->u.getReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
    {
        printf("paramNames[%d] : %s\n",i,reqObj->u.getReq->paramNames[i]);
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.SSID.1.Enable", reqObj->u.getReq->paramNames[0] );
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.SSID.1.SSID", reqObj->u.getReq->paramNames[1] );
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
}

void set_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"value\":\"XB3\",\"dataType\":0},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"14cfe2142142\",\"dataType\":0}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET, reqObj->reqType );
    
    printf("Request Type : %d\n",reqObj->reqType);
    printf("Param Count : %lu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    printf("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    printf("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    printf("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
	}
	
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.ProductClass", reqObj->u.setReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.SerialNumber", reqObj->u.setReq->param[1].name );
    CU_ASSERT_STRING_EQUAL( "XB3", reqObj->u.setReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "14cfe2142142", reqObj->u.setReq->param[1].value );  
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[1].type );  
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void set_attr_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"attributes\": { \"notify\": 1}},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"attributes\": { \"notify\": 0}}],\"command\":\"SET_ATTRIBUTES\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET_ATTRIBUTES, reqObj->reqType );
    
    printf("Request Type : %d\n",reqObj->reqType);
    printf("Param Count : %lu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    printf("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    printf("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    printf("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
	}
	
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.ProductClass", reqObj->u.setReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.SerialNumber", reqObj->u.setReq->param[1].name );
    CU_ASSERT_STRING_EQUAL( "1", reqObj->u.setReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "0", reqObj->u.setReq->param[1].value ); 
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[1].type );  
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void test_and_set_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"value\":\"XB3\",\"dataType\":0},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"14cfe2142142\",\"dataType\":0}],\"new-cid\":\"1234\",\"old-cid\":\"aq12\",\"sync-cmc\":\"512\",\"command\":\"TEST_AND_SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( TEST_AND_SET, reqObj->reqType );
    
    printf("Request Type : %d\n",reqObj->reqType);
    printf("Param Count : %lu\n",reqObj->u.testSetReq->paramCnt);
    printf("New Cid : %s\n",reqObj->u.testSetReq->newCid);
    printf("Old Cid : %s\n",reqObj->u.testSetReq->oldCid);
    printf("Sync Cmc : %s\n",reqObj->u.testSetReq->syncCmc);
    
    CU_ASSERT_STRING_EQUAL( "1234", reqObj->u.testSetReq->newCid ); 
    CU_ASSERT_STRING_EQUAL( "aq12", reqObj->u.testSetReq->oldCid ); 
    CU_ASSERT_STRING_EQUAL( "512", reqObj->u.testSetReq->syncCmc ); 
    
    paramCount = (int)reqObj->u.testSetReq->paramCnt;
    
    for (i = 0; i < paramCount; i++) 
    {
	    printf("param[%d].name : %s\n",i,reqObj->u.testSetReq->param[i].name);
	    printf("param[%d].value : %s\n",i,reqObj->u.testSetReq->param[i].value);
	    printf("param[%d].type : %d\n",i,reqObj->u.testSetReq->param[i].type);
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.ProductClass", reqObj->u.testSetReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.SerialNumber", reqObj->u.testSetReq->param[1].name );
    CU_ASSERT_STRING_EQUAL( "XB3", reqObj->u.testSetReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "14cfe2142142", reqObj->u.testSetReq->param[1].value ); 
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.testSetReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.testSetReq->param[1].type ); 
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void replace_rows_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    int i,paramCount,j,rowCnt;
    req_struct *reqObj = NULL;
       
    char * request= "{\"rows\":{\"0\":{\"DeviceName\":\"Device1\",\"MacAddress\":\"12:2:3:5:11\"},\"1\":{\"DeviceName\":\"Device2\",\"MacAddress\":\"2:1:3:5:7\"} },\"table\" : \"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.\",\"command\":\"REPLACE_ROWS\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( REPLACE_ROWS, reqObj->reqType );
    
    printf("Req Type : %d\n",reqObj->reqType);
    printf("Object Name : %s\n",reqObj->u.tableReq->objectName);
    printf("Row Count : %lu\n",reqObj->u.tableReq->rowCnt);
    rowCnt = (int)reqObj->u.tableReq->rowCnt;
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 2, rowCnt );
    
    for ( i = 0 ; i < rowCnt ; i++)
    {
        printf("ParamCount: %lu\n",reqObj->u.tableReq->rows[i].paramCnt);
        paramCount = (int)reqObj->u.tableReq->rows[i].paramCnt;
        
        for( j = 0 ; j < paramCount ; j++)
        {
	        printf("rows[%d].names[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].names[j]);				
	        printf("rows[%d].values[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].values[j]);			
        }
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "DeviceName", reqObj->u.tableReq->rows[0].names[0] );
    CU_ASSERT_STRING_EQUAL( "Device1", reqObj->u.tableReq->rows[0].values[0] );
    CU_ASSERT_STRING_EQUAL( "MacAddress", reqObj->u.tableReq->rows[0].names[1] );
    CU_ASSERT_STRING_EQUAL( "12:2:3:5:11", reqObj->u.tableReq->rows[0].values[1] ); 
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }		
}

void add_row_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    int i,paramCount,j,rowCnt;
    req_struct *reqObj = NULL;

    char * request= "{\"row\":{\"DeviceName\":\"Device1\",\"MacAddress\":\"12:2:3:5:11\"},\"table\":\"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.\",\"command\":\"ADD_ROW\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( ADD_ROWS, reqObj->reqType );
    
    printf("Req Type : %d\n",reqObj->reqType);
    printf("Object Name : %s\n",reqObj->u.tableReq->objectName);
    printf("Row Count : %lu\n",reqObj->u.tableReq->rowCnt);
    
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 1, reqObj->u.tableReq->rowCnt );
    rowCnt = (int)reqObj->u.tableReq->rowCnt;
    
    for ( i = 0 ; i < rowCnt ; i++)
    {
        printf("ParamCount: %lu\n",reqObj->u.tableReq->rows[i].paramCnt);
        paramCount = (int)reqObj->u.tableReq->rows[i].paramCnt;
        
        for( j = 0 ; j < paramCount ; j++)
        {
	        printf("rows[%d].names[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].names[j]);				
	        printf("rows[%d].values[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].values[j]);			
        }
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "DeviceName", reqObj->u.tableReq->rows[0].names[0] );
    CU_ASSERT_STRING_EQUAL( "Device1", reqObj->u.tableReq->rows[0].values[0] );
    CU_ASSERT_STRING_EQUAL( "MacAddress", reqObj->u.tableReq->rows[0].names[1] );
    CU_ASSERT_STRING_EQUAL( "12:2:3:5:11", reqObj->u.tableReq->rows[0].values[1] ); 
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }		
}

void delete_row_req_parse ()
{
    printf("\n***************************************************** \n\n");
    
    req_struct *reqObj = NULL;
    
    char * request= "{\"row\":\"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.\",\"command\":\"DELETE_ROW\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( DELETE_ROW, reqObj->reqType );
    
    printf("Req Type : %d\n",reqObj->reqType);
    printf("Object Name : %s\n",reqObj->u.tableReq->objectName);
    printf("Row Count : %lu\n",reqObj->u.tableReq->rowCnt);
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 0, reqObj->u.tableReq->rowCnt );

    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }		
}


void test_unknown_command ()
{
    printf("\n***************************************************** \n\n");
    
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":[\"Device.DeviceInfo.Webpa.Enable\",\"Device.WiFi.SSID.1.Enable\"],\"command\": \"UNKNOWN\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL == reqObj);
}

void get_req_empty_names ()
{
    printf("\n***************************************************** \n\n");
    int paramCount;
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":\" \",\"command\": \"GET\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    
    printf("Request Type : %d\n",reqObj->reqType);
    
    CU_ASSERT_EQUAL( GET, reqObj->reqType );
    
    if(reqObj->u.getReq)
    {
        printf("ParamCount : %lu\n",reqObj->u.getReq->paramCnt);
        paramCount = (int)reqObj->u.getReq->paramCnt;
        CU_ASSERT_EQUAL( 0, paramCount );
        
    }

    if (NULL != reqObj) 
    {
        wdmp_free_req_struct(reqObj );
    }  
}

void get_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET;
        resObj->paramCnt = 2;
        
        resObj->u.getRes = (get_res_t *) malloc(sizeof(get_res_t));
        memset(resObj->u.getRes, 0, sizeof(get_res_t));
        
        resObj->u.getRes->retParamCnt = (size_t *) malloc(sizeof(size_t)*2);
        resObj->u.getRes->retParamCnt[0] = 1;
        resObj->u.getRes->retParamCnt[1] = 1;
        
        resObj->u.getRes->paramCnt = resObj->paramCnt;
        resObj->u.getRes->paramNames = (char **) malloc(sizeof(char *) * resObj->u.getRes->paramCnt);
        resObj->u.getRes->paramNames[0] = "Device.WIFi.SSID.1.SSID";
        resObj->u.getRes->paramNames[1] = "Device.DeviceInfo.Webpa.Enable";
        
        resObj->u.getRes->params = (param_t **) malloc(sizeof(param_t*)*2);
        memset(resObj->u.getRes->params, 0, sizeof(param_t*)*2);
        
        resObj->u.getRes->params[0]= (param_t *) malloc(sizeof(param_t)*resObj->u.getRes->retParamCnt[0]);
        resObj->u.getRes->params[1]= (param_t *) malloc(sizeof(param_t)*resObj->u.getRes->retParamCnt[1]);
        
        resObj->u.getRes->params[0][0].name = "Device.WIFi.SSID.1.SSID";
        resObj->u.getRes->params[0][0].value = "ssid1";
        resObj->u.getRes->params[0][0].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][0].name = "Device.DeviceInfo.Webpa.Enable";
        resObj->u.getRes->params[1][0].value = "true";
        resObj->u.getRes->params[1][0].type = WDMP_BOOLEAN;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj, &payload);
        
        printf("payload :%s\n",payload);
}

void get_wildcard_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET;
        resObj->paramCnt = 2;
        
        resObj->u.getRes = (get_res_t *) malloc(sizeof(get_res_t));
        memset(resObj->u.getRes, 0, sizeof(get_res_t));
        
        resObj->u.getRes->retParamCnt = (size_t *) malloc(sizeof(size_t)*2);
        resObj->u.getRes->retParamCnt[0] = 1;
        resObj->u.getRes->retParamCnt[1] = 3;
        
        resObj->u.getRes->paramCnt = resObj->paramCnt;
        resObj->u.getRes->paramNames = (char **) malloc(sizeof(char *) * resObj->u.getRes->paramCnt);
        resObj->u.getRes->paramNames[0] = "Device.WIFi.SSID.1.Enable";
        resObj->u.getRes->paramNames[1] = "Device.Webpa.";
        
        resObj->u.getRes->params = (param_t **) malloc(sizeof(param_t*)*2);
        memset(resObj->u.getRes->params, 0, sizeof(param_t*)*2);
        
        resObj->u.getRes->params[0]= (param_t *) malloc(sizeof(param_t)*resObj->u.getRes->retParamCnt[0]);
        resObj->u.getRes->params[1]= (param_t *) malloc(sizeof(param_t)*resObj->u.getRes->retParamCnt[1]);
        
        resObj->u.getRes->params[0][0].name = "Device.WIFi.SSID.1.Enable";
        resObj->u.getRes->params[0][0].value = "true";
        resObj->u.getRes->params[0][0].type = WDMP_BOOLEAN;
        
        resObj->u.getRes->params[1][0].name = "Device.Webpa.PostData";
        resObj->u.getRes->params[1][0].value = "Not Supported";
        resObj->u.getRes->params[1][0].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][1].name = "Device.Webpa.X_RDKCENTRAL-COM_WebPA_Notification";
        resObj->u.getRes->params[1][1].value = "Not Supported";
        resObj->u.getRes->params[1][1].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][2].name = "Device.Webpa.X_RDKCENTRAL-COM_Connected-Client";
        resObj->u.getRes->params[1][2].value = "Not Supported";
        resObj->u.getRes->params[1][2].type = WDMP_STRING;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        printf("payload :%s\n",payload);
}

void get_attr_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = "Device.WIFi.SSID.1.Enable";
        resObj->u.paramRes->params[0].value = "1";
        
        resObj->u.paramRes->params[1].name = "Device.WIFi.SSID.1.SSID";
        resObj->u.paramRes->params[1].value = "1";
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        printf("payload :%s\n",payload);
}

void set_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = "Device.DeviceInfo.Webpa.Enable";
        resObj->u.paramRes->params[1].name = "Device.WiFi.SSID.2.SSID";
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj, &payload);
        
        printf("payload :%s\n",payload);
}

void set_attr_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = "Device.WiFi.SSID.1.Enable";
        resObj->u.paramRes->params[1].name = "Device.WiFi.SSID.1.SSID";
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj, &payload);
        
        printf("payload :%s\n",payload);
}

void test_and_set_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = TEST_AND_SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = "Device.DeviceInfo.Webpa.X_COMCAST-COM_CID";
        resObj->u.paramRes->params[0].value = "1234";
        
        resObj->u.paramRes->params[1].name = "Device.DeviceInfo.Webpa.X_COMCAST-COM_CMC";
        resObj->u.paramRes->params[1].value = "512";
        
        resObj->timeSpan = NULL;
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        printf("payload :%s\n",payload);
}

void add_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = ADD_ROWS;
        
        resObj->u.tableRes = (table_res_t *) malloc(sizeof(table_res_t));
        
        resObj->u.tableRes->newObj = "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.";
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        printf("payload :%s\n",payload);
}

void replace_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = REPLACE_ROWS;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        printf("payload :%s\n",payload);

}

void delete_row_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        printf("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = DELETE_ROW;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj, &payload);
        
        printf("payload :%s\n",payload);

}

void add_request_parse_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "wdmp-c request parsing tests", NULL, NULL );
    
    CU_add_test( *suite, "Test Get Request Parse", get_req_parse );
    CU_add_test( *suite, "Test Get attr Request Parse", get_attr_req_parse );
    CU_add_test( *suite, "Test Set Request Parse", set_req_parse );
    CU_add_test( *suite, "Test Set attr Request Parse", set_attr_req_parse );
    CU_add_test( *suite, "Test Test and set Request Parse", test_and_set_req_parse );
    CU_add_test( *suite, "Test Replace row Request Parse", replace_rows_req_parse );
    CU_add_test( *suite, "Test Add row Request Parse", add_row_req_parse );
    CU_add_test( *suite, "Test Delete row Request Parse", delete_row_req_parse );    
    CU_add_test( *suite, "Test Unknown command", test_unknown_command );
    CU_add_test( *suite, "Test Empty_names", get_req_empty_names );
   
}

void add_response_form_suites ( CU_pSuite *suite )
{
    *suite = CU_add_suite( "wdmp-c Response forming tests", NULL, NULL );
    
    CU_add_test( *suite, "Get Response Form", get_res_form );
    CU_add_test( *suite, "Get wild card Response Form", get_wildcard_res_form );
    CU_add_test( *suite, "Get attributes Response Form", get_attr_res_form );
    CU_add_test( *suite, "Set Response Form", set_res_form );
    CU_add_test( *suite, "Set attributes Response Form", set_attr_res_form );
    CU_add_test( *suite, "Test and Set Response Form", test_and_set_res_form );
    CU_add_test( *suite, "Add row Response Form", add_rows_res_form );
    CU_add_test( *suite, "Replace rows Response Form", replace_rows_res_form );
    CU_add_test( *suite, "Delete row Response Form", delete_row_res_form );            
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite req_suite = NULL, res_suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) 
    {
        add_request_parse_suites( &req_suite );
        add_response_form_suites( &res_suite );

        if( NULL != req_suite ||  NULL != res_suite) 
        {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) 
    {
        return 1;
    }
    return 0;
}
