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
#include "../src/wdmp_internal.h"

#define MAX_PARAM_LEN 128

void get_req_parse ()
{
    int i,paramCount;
    char *request = NULL;
    req_struct *reqObj = NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
    
    request = "{ \"names\":[\"Device.DeviceInfo.Webpa.Enable\",\"Device.DeviceInfo.Webpa.\"],\"command\": \"GET\"}";
    
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    
    CU_ASSERT_EQUAL( GET, reqObj->reqType );
    
    if(reqObj->u.getReq)
    {
        WdmpPrint("ParamCount : %zu\n",reqObj->u.getReq->paramCnt);
        paramCount = (int)reqObj->u.getReq->paramCnt;
        for (i = 0; i < paramCount; i++) 
        {
            WdmpPrint("paramNames[%d] : %s\n",i,reqObj->u.getReq->paramNames[i]);
            
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
    
    int i,paramCount;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
    
    payload= "{ \"names\":[\"Device.WiFi.SSID.1.Enable\",\"Device.WiFi.SSID.1.SSID\"],\"attributes\":\"notify\",\"command\": \"GET_ATTRIBUTES\"}";
    
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_get_request(request,&reqObj,WDMP_TR181);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( GET_ATTRIBUTES, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("ParamCount : %zu\n",reqObj->u.getReq->paramCnt);
    paramCount = (int)reqObj->u.getReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
    {
        WdmpPrint("paramNames[%d] : %s\n",i,reqObj->u.getReq->paramNames[i]);
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.SSID.1.Enable", reqObj->u.getReq->paramNames[0] );
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.SSID.1.SSID", reqObj->u.getReq->paramNames[1] );
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }

    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}

void set_req_parse ()
{
    
    int i,paramCount;
    char *request = NULL;
    req_struct *reqObj = NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
      
    request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"value\":\"XB3\",\"dataType\":0},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"14cfe2142142\",\"dataType\":0}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
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

void set_req_parse_with_attributes ()
{
    
    int i,paramCount;
    char *request = NULL;
    req_struct *reqObj = NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
      
    request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"value\":\"XB3\",\"dataType\":0,\"attributes\": { \"notify\": 1}},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"14cfe2142142\",\"dataType\":0,\"attributes\": { \"notify\": 1}}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
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
    
    int i,paramCount;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
      
    payload = "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"attributes\": { \"notify\": 1}},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"attributes\": { \"notify\": 0}}],\"command\":\"SET_ATTRIBUTES\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_set_attr_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET_ATTRIBUTES, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
    {
        WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
        WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
        WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
    }
	
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.ProductClass", reqObj->u.setReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.SerialNumber", reqObj->u.setReq->param[1].name );
    CU_ASSERT_STRING_EQUAL( "1", reqObj->u.setReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "0", reqObj->u.setReq->param[1].value ); 
    CU_ASSERT_EQUAL( WDMP_INT, reqObj->u.setReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_INT, reqObj->u.setReq->param[1].type );  
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }

    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}

void test_and_set_req_parse ()
{
    int i,paramCount;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
      
    payload = "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"value\":\"XB3\",\"dataType\":0},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"14cfe2142142\",\"dataType\":0}],\"new-cid\":\"1234\",\"old-cid\":\"aq12\",\"sync-cmc\":\"512\",\"command\":\"TEST_AND_SET\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_test_and_set_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( TEST_AND_SET, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.testSetReq->paramCnt);
    WdmpInfo("New Cid : %s\n",reqObj->u.testSetReq->newCid);
    WdmpInfo("Old Cid : %s\n",reqObj->u.testSetReq->oldCid);
    WdmpInfo("Sync Cmc : %s\n",reqObj->u.testSetReq->syncCmc);
    
    CU_ASSERT_STRING_EQUAL( "1234", reqObj->u.testSetReq->newCid ); 
    CU_ASSERT_STRING_EQUAL( "aq12", reqObj->u.testSetReq->oldCid ); 
    CU_ASSERT_STRING_EQUAL( "512", reqObj->u.testSetReq->syncCmc ); 
    
    paramCount = (int)reqObj->u.testSetReq->paramCnt;
    
    for (i = 0; i < paramCount; i++) 
    {
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.testSetReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.testSetReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.testSetReq->param[i].type);
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
    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}

void replace_rows_req_parse ()
{
    
    int i,paramCount,j,rowCnt;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
       
    payload= "{\"rows\":{\"0\":{\"DeviceName\":\"Device1\",\"MacAddress\":\"12:2:3:5:11\"},\"1\":{\"DeviceName\":\"Device2\",\"MacAddress\":\"2:1:3:5:7\"} },\"table\" : \"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.\",\"command\":\"REPLACE_ROWS\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_replace_rows_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( REPLACE_ROWS, reqObj->reqType );
    
    WdmpInfo("Req Type : %d\n",reqObj->reqType);
    WdmpInfo("Object Name : %s\n",reqObj->u.tableReq->objectName);
    WdmpInfo("Row Count : %zu\n",reqObj->u.tableReq->rowCnt);
    rowCnt = (int)reqObj->u.tableReq->rowCnt;
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 2, rowCnt );
    
    for ( i = 0 ; i < rowCnt ; i++)
    {
        WdmpPrint("ParamCount: %zu\n",reqObj->u.tableReq->rows[i].paramCnt);
        paramCount = (int)reqObj->u.tableReq->rows[i].paramCnt;
        
        for( j = 0 ; j < paramCount ; j++)
        {
	        WdmpPrint("rows[%d].names[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].names[j]);				
	        WdmpPrint("rows[%d].values[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].values[j]);			
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
    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}

void add_row_req_parse ()
{
    
    int i,paramCount,j,rowCnt;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");

    payload = "{\"row\":{\"DeviceName\":\"Device1\",\"MacAddress\":\"12:2:3:5:11\"},\"table\":\"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.\",\"command\":\"ADD_ROW\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_add_row_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( ADD_ROWS, reqObj->reqType );
    
    WdmpInfo("Req Type : %d\n",reqObj->reqType);
    WdmpInfo("Object Name : %s\n",reqObj->u.tableReq->objectName);
    WdmpInfo("Row Count : %zu\n",reqObj->u.tableReq->rowCnt);
    
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 1, reqObj->u.tableReq->rowCnt );
    rowCnt = (int)reqObj->u.tableReq->rowCnt;
    
    for ( i = 0 ; i < rowCnt ; i++)
    {
        WdmpPrint("ParamCount: %zu\n",reqObj->u.tableReq->rows[i].paramCnt);
        paramCount = (int)reqObj->u.tableReq->rows[i].paramCnt;
        
        for( j = 0 ; j < paramCount ; j++)
        {
	        WdmpPrint("rows[%d].names[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].names[j]);				
	        WdmpPrint("rows[%d].values[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].values[j]);			
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
    if(NULL != request)
    {
        cJSON_Delete(request);
    }		
}

void delete_row_req_parse ()
{
    
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
    
    payload = "{\"row\":\"Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.\",\"command\":\"DELETE_ROW\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_delete_row_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( DELETE_ROW, reqObj->reqType );
    
    WdmpInfo("Req Type : %d\n",reqObj->reqType);
    WdmpInfo("Object Name : %s\n",reqObj->u.tableReq->objectName);
    WdmpInfo("Row Count : %zu\n",reqObj->u.tableReq->rowCnt);
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 0, reqObj->u.tableReq->rowCnt );

    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }

    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}


void test_unknown_command ()
{
    WdmpInfo("\n***************************************************** \n\n");
    
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":[\"Device.DeviceInfo.Webpa.Enable\",\"Device.WiFi.SSID.1.Enable\"],\"command\": \"UNKNOWN\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL == reqObj);
    if (NULL != reqObj) 
    {
	wdmp_free_req_struct(reqObj );
    }
}

void get_req_empty_names ()
{
    WdmpInfo("\n***************************************************** \n\n");
    int paramCount;
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":\" \",\"command\": \"GET\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    
    CU_ASSERT_EQUAL( GET, reqObj->reqType );
    
    if(reqObj->u.getReq)
    {
        WdmpPrint("ParamCount : %zu\n",reqObj->u.getReq->paramCnt);
        paramCount = (int)reqObj->u.getReq->paramCnt;
        CU_ASSERT_EQUAL( 0, paramCount );
        
    }

    if (NULL != reqObj) 
    {
        wdmp_free_req_struct(reqObj );
    }  
}

void get_req_empty_notify ()
{
    WdmpInfo("\n***************************************************** \n\n");
    req_struct *reqObj = NULL;
    
    char * request= "{ \"names\":[\"Device.WiFi.SSID.1.Enable\",\"Device.WiFi.SSID.1.SSID\"],\"attributes\":\"\",\"command\": \"GET_ATTRIBUTES\"}";
    
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL == reqObj);    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
}

void set_req_empty_notify ()
{
    WdmpInfo("\n***************************************************** \n\n");
    
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass\",\"attributes\": \"\"}],\"command\":\"SET_ATTRIBUTES\"}";

    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET_ATTRIBUTES, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
	}	
    CU_ASSERT( NULL == reqObj->u.setReq->param[0].value );
   
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
}

void test_and_set_without_cid ()
{
    WdmpInfo("\n***************************************************** \n\n");
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.X_CISCO_COM_FirmwareName\",\"value\":\"TG1682\",\"dataType\":0}],\"sync-cmc\":\"512\",\"command\":\"TEST_AND_SET\"}";
 
    wdmp_parse_request(request,&reqObj);

    WdmpInfo("Request Type : %d\n",reqObj->reqType);    
    WdmpInfo("New Cid : %s\n",reqObj->u.testSetReq->newCid); 
    WdmpInfo("Old Cid : %s\n",reqObj->u.testSetReq->oldCid);    
    
    CU_ASSERT( NULL != reqObj);    
    CU_ASSERT ( NULL == reqObj->u.testSetReq->newCid ); 
    CU_ASSERT ( NULL == reqObj->u.testSetReq->oldCid );
    CU_ASSERT_EQUAL( TEST_AND_SET, reqObj->reqType );    
    CU_ASSERT_STRING_EQUAL( "512", reqObj->u.testSetReq->syncCmc ); 
    
    paramCount = (int)reqObj->u.testSetReq->paramCnt;
    
    for (i = 0; i < paramCount; i++) 
    {
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.testSetReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.testSetReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.testSetReq->param[i].type);
    }
    
    CU_ASSERT_EQUAL( 1, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.X_CISCO_COM_FirmwareName", reqObj->u.testSetReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "TG1682", reqObj->u.testSetReq->param[0].value );   
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.testSetReq->param[0].type );
   
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void empty_test_and_set ()
{
    WdmpInfo("\n***************************************************** \n\n");
    
    req_struct *reqObj = NULL;
      
    char * request= "{\"command\":\"TEST_AND_SET\"}";

    wdmp_parse_request(request,&reqObj);

    WdmpInfo("Request Type : %d\n",reqObj->reqType);    
    WdmpInfo("New Cid : %s\n",reqObj->u.testSetReq->newCid);    
    WdmpPrint("param struct is %s\n", (char*)reqObj->u.testSetReq->param);
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( TEST_AND_SET, reqObj->reqType );
    CU_ASSERT(NULL == reqObj->u.testSetReq->param);   
   
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void set_req_null_param_value ()
{
    WdmpInfo("\n***************************************************** \n\n");
    
    int i,paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.HardwareVersion\",\"value\":\"\",\"dataType\":0},{\"name\":\"Device.WiFi.SSID.Enable\",\"value\":\"true\",\"dataType\":3}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpInfo("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
	}
	
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.HardwareVersion", reqObj->u.setReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.SSID.Enable", reqObj->u.setReq->param[1].name );
    CU_ASSERT( NULL == reqObj->u.setReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "true" , reqObj->u.setReq->param[1].value );  
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_BOOLEAN, reqObj->u.setReq->param[1].type );  
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void set_req_value_field_empty ()
{
    WdmpInfo("\n***************************************************** \n\n");
    
    int paramCount;
    req_struct *reqObj = NULL;
      
    char * request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.HardwareVersion\",\"dataType\":0}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    
    WdmpPrint("param.name : %s\n",reqObj->u.setReq->param[0].name);
    WdmpPrint("param.value : %s\n",reqObj->u.setReq->param[0].value);
    WdmpPrint("param.type : %d\n",reqObj->u.setReq->param[0].type);
	
    CU_ASSERT_EQUAL( 1, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.HardwareVersion", reqObj->u.setReq->param[0].name );
    CU_ASSERT( NULL == reqObj->u.setReq->param[0].value );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[0].type );
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
		
}

void verify_get_reponse(cJSON *response, res_struct *resObj)
{
        cJSON *paramArray = NULL, *resParamObj = NULL, *value = NULL, *valueObj = NULL;
        size_t i, j;
        WDMP_RESPONSE_STATUS_CODE statusCode;
        char *result = NULL;
        
        WdmpInfo("Status code: %d\n", cJSON_GetObjectItem(response, "statusCode")->valueint);
        getStatusCode(&statusCode, resObj->paramCnt, resObj->retStatus);
        CU_ASSERT_EQUAL((int)statusCode, cJSON_GetObjectItem(response, "statusCode")->valueint);
        
        paramArray = cJSON_GetObjectItem(response, "parameters");
        
        CU_ASSERT( NULL != paramArray );
        
        WdmpPrint("Parameter count: %d\n",cJSON_GetArraySize(paramArray));
        CU_ASSERT_EQUAL( (int)resObj->paramCnt, cJSON_GetArraySize(paramArray) );
                
        for (i = 0; i < resObj->paramCnt; i++) 
	{
		resParamObj = cJSON_GetArrayItem(paramArray, i);
		
		WdmpPrint("Returnparamcount[%zu]: %d\n",i, cJSON_GetObjectItem(resParamObj, "parameterCount")->valueint); 
		CU_ASSERT_EQUAL((int)resObj->u.getRes->retParamCnt[i],cJSON_GetObjectItem(resParamObj, "parameterCount")->valueint);
		
		if( resObj->u.getRes->retParamCnt[i] > 1)
		{
		        WdmpPrint("ParamName[%zu] : %s\n",i, cJSON_GetObjectItem(resParamObj, "name")->valuestring);
		        CU_ASSERT_STRING_EQUAL( resObj->u.getRes->paramNames[i], cJSON_GetObjectItem(resParamObj, "name")->valuestring );
		        
		        value = cJSON_GetObjectItem(resParamObj, "value");
		        CU_ASSERT( NULL != value );
		        CU_ASSERT_EQUAL((int)resObj->u.getRes->retParamCnt[i],cJSON_GetArraySize(value));
		        
		        for (j = 0; j < resObj->u.getRes->retParamCnt[i]; j++)
		        {
		                valueObj = cJSON_GetArrayItem(value, j);
		                
		                WdmpPrint("Name[%zu][%zu] : %s\n", i,j,cJSON_GetObjectItem(valueObj, "name")->valuestring );
		                CU_ASSERT_STRING_EQUAL( resObj->u.getRes->params[i][j].name, cJSON_GetObjectItem(valueObj, "name")->valuestring );
		                WdmpPrint("Value[%zu][%zu] : %s\n", i,j,cJSON_GetObjectItem(valueObj, "value")->valuestring );
		                CU_ASSERT_STRING_EQUAL( resObj->u.getRes->params[i][j].value, cJSON_GetObjectItem(valueObj, "value")->valuestring );
		                WdmpPrint("Type[%zu][%zu] : %d\n", i,j,cJSON_GetObjectItem(valueObj, "dataType")->valueint);
	                        CU_ASSERT_EQUAL((int)resObj->u.getRes->params[i][j].type,cJSON_GetObjectItem(valueObj, "dataType")->valueint);
		        }
		        
		        WdmpPrint("DataType[%zu] : %d\n",i, cJSON_GetObjectItem(resParamObj, "dataType")->valueint);
		        CU_ASSERT_EQUAL( WDMP_NONE, cJSON_GetObjectItem(resParamObj, "dataType")->valueint );
		        
		        WdmpPrint("Message[%zu] : %s\n",i,cJSON_GetObjectItem(resParamObj, "message")->valuestring);
		        mapWdmpStatusToStatusMessage(resObj->retStatus[i], &result);
                        CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(resParamObj, "message")->valuestring);
		        
		}
		else if( resObj->u.getRes->retParamCnt[i] == 1)
		{
		        j = 0;
		        WdmpPrint("ParamName[%zu] : %s\n",i, cJSON_GetObjectItem(resParamObj, "name")->valuestring);
		        CU_ASSERT_STRING_EQUAL( resObj->u.getRes->paramNames[i], cJSON_GetObjectItem(resParamObj, "name")->valuestring );
		        WdmpPrint("Name[%zu][%zu] : %s\n", i,j,cJSON_GetObjectItem(resParamObj, "name")->valuestring );
	                CU_ASSERT_STRING_EQUAL( resObj->u.getRes->params[i][j].name, cJSON_GetObjectItem(resParamObj, "name")->valuestring );
	                WdmpPrint("Value[%zu][%zu] : %s\n", i,j,cJSON_GetObjectItem(resParamObj, "value")->valuestring );
	                CU_ASSERT_STRING_EQUAL( resObj->u.getRes->params[i][j].value, cJSON_GetObjectItem(resParamObj, "value")->valuestring );
	                WdmpPrint("Type[%zu][%zu] : %d\n", i,j,cJSON_GetObjectItem(resParamObj, "dataType")->valueint);
                        CU_ASSERT_EQUAL((int)resObj->u.getRes->params[i][j].type,cJSON_GetObjectItem(resParamObj, "dataType")->valueint);
                        
                        WdmpPrint("Message[%zu] : %s\n",i,cJSON_GetObjectItem(resParamObj, "message")->valuestring);
                        mapWdmpStatusToStatusMessage(resObj->retStatus[i], &result);
                        CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(resParamObj, "message")->valuestring);
		}
		else
		{
                        WdmpPrint("ParamName[%zu] : %s\n",i, cJSON_GetObjectItem(resParamObj, "name")->valuestring);
                        CU_ASSERT_STRING_EQUAL( resObj->u.getRes->paramNames[i], cJSON_GetObjectItem(resParamObj, "name")->valuestring );
                         
                        WdmpPrint("Value[%zu] : %s\n", i,cJSON_GetObjectItem(resParamObj, "value")->valuestring );
	                CU_ASSERT_STRING_EQUAL( "EMPTY", cJSON_GetObjectItem(resParamObj, "value")->valuestring );   
		}
	}
	
	if(result)
        {
                free(result); 
        }
	
}

void verify_param_response(cJSON *response, res_struct *resObj)
{
        cJSON *paramArray = NULL, *resParamObj = NULL, *attributes = NULL;
        size_t i;
        WDMP_RESPONSE_STATUS_CODE statusCode;
        char *result = NULL;
        
        WdmpInfo("Status code: %d\n", cJSON_GetObjectItem(response, "statusCode")->valueint);
        getStatusCode(&statusCode, resObj->paramCnt, resObj->retStatus);
        CU_ASSERT_EQUAL((int)statusCode, cJSON_GetObjectItem(response, "statusCode")->valueint);
        
        paramArray = cJSON_GetObjectItem(response, "parameters");
        
        CU_ASSERT( NULL != paramArray );
        
        WdmpPrint("Parameter count: %d\n",cJSON_GetArraySize(paramArray));
        CU_ASSERT_EQUAL( (int)resObj->paramCnt, cJSON_GetArraySize(paramArray) );
                
        for (i = 0; i < resObj->paramCnt; i++) 
	{
		resParamObj = cJSON_GetArrayItem(paramArray, i);
		WdmpPrint("Name[%zu] : %s\n", i,cJSON_GetObjectItem(resParamObj, "name")->valuestring );
                CU_ASSERT_STRING_EQUAL( resObj->u.paramRes->params[i].name, cJSON_GetObjectItem(resParamObj, "name")->valuestring );
                
                if(resObj->reqType == GET_ATTRIBUTES)
                {
                        attributes = cJSON_GetObjectItem(resParamObj, "attributes");
                        CU_ASSERT( NULL != attributes );
                        WdmpPrint("Value[%zu] : %d\n", i,cJSON_GetObjectItem(attributes, "notify")->valueint );
                        CU_ASSERT_EQUAL( atoi(resObj->u.paramRes->params[i].value), cJSON_GetObjectItem(attributes, "notify")->valueint );
                }
                WdmpPrint("Message[%zu] : %s\n",i,cJSON_GetObjectItem(resParamObj, "message")->valuestring);
                mapWdmpStatusToStatusMessage(resObj->retStatus[i], &result);
                CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(resParamObj, "message")->valuestring);
	}
	
	if(result)
        {
                free(result); 
        }
	
}

void verify_testandset_response(cJSON *response, res_struct *resObj)
{
        cJSON *paramArray = NULL, *resParamObj = NULL;
        size_t i;
        WDMP_RESPONSE_STATUS_CODE statusCode;
        char *result = NULL;
        
        WdmpInfo("Status code: %d\n", cJSON_GetObjectItem(response, "statusCode")->valueint);
        getStatusCode(&statusCode, 1, resObj->retStatus);
        CU_ASSERT_EQUAL((int)statusCode, cJSON_GetObjectItem(response, "statusCode")->valueint);
        
        paramArray = cJSON_GetObjectItem(response, "parameters");
        
        CU_ASSERT( NULL != paramArray );
        
        WdmpPrint("Parameter count: %d\n",cJSON_GetArraySize(paramArray));
        CU_ASSERT_EQUAL( (int)resObj->paramCnt, cJSON_GetArraySize(paramArray) );
                
        for (i = 0; i < resObj->paramCnt; i++) 
	{
		resParamObj = cJSON_GetArrayItem(paramArray, i);
		WdmpPrint("Name[%zu] : %s\n", i,cJSON_GetObjectItem(resParamObj, "name")->valuestring );
		if(0 == strcmp(cJSON_GetObjectItem(resParamObj, "name")->valuestring, WDMP_SYNC_PARAM_CID))
		{
		        WdmpPrint("CID: %s\n", cJSON_GetObjectItem(resParamObj, "value")->valuestring);
                        CU_ASSERT_STRING_EQUAL( resObj->u.paramRes->syncCID, cJSON_GetObjectItem(resParamObj, "value")->valuestring );
                }
                else if(0 == strcmp(cJSON_GetObjectItem(resParamObj, "name")->valuestring, WDMP_SYNC_PARAM_CMC))
                {
                        WdmpPrint("CMC: %d\n", cJSON_GetObjectItem(resParamObj, "value")->valueint);
                        CU_ASSERT_EQUAL( atoi(resObj->u.paramRes->syncCMC), cJSON_GetObjectItem(resParamObj, "value")->valueint );
                }
                
	}
	
	WdmpInfo("Message : %s\n",cJSON_GetObjectItem(response, "message")->valuestring);
	mapWdmpStatusToStatusMessage(resObj->retStatus[0], &result);
        CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(response, "message")->valuestring);
        
        if(result)
        {
                free(result); 
        }
}

void verify_table_response(cJSON *response, res_struct *resObj)
{
        WDMP_RESPONSE_STATUS_CODE statusCode;
        char *result = NULL;
        
        WdmpInfo("Status code: %d\n", cJSON_GetObjectItem(response, "statusCode")->valueint);
                
        if(resObj->reqType == ADD_ROWS)
        {
                CU_ASSERT_EQUAL(WDMP_ADDROW_STATUS_SUCCESS, cJSON_GetObjectItem(response, "statusCode")->valueint);
                WdmpPrint("New row: %s\n", cJSON_GetObjectItem(response, "row")->valuestring);
                CU_ASSERT_STRING_EQUAL(resObj->u.tableRes->newObj, cJSON_GetObjectItem(response, "row")->valuestring);
        }
        else
        {
                getStatusCode(&statusCode, 1, resObj->retStatus);
                CU_ASSERT_EQUAL((int)statusCode, cJSON_GetObjectItem(response, "statusCode")->valueint);
        }
        
        WdmpInfo("Message : %s\n",cJSON_GetObjectItem(response, "message")->valuestring);
        mapWdmpStatusToStatusMessage(resObj->retStatus[0], &result);
        CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(response, "message")->valuestring);

        if(result)
        {
                free(result);
        }
}

void verify_failure_response(cJSON *response, res_struct *resObj)
{
        WDMP_RESPONSE_STATUS_CODE statusCode;
        char *result = NULL;
        
        WdmpInfo("Status code: %d\n", cJSON_GetObjectItem(response, "statusCode")->valueint);
        getStatusCode(&statusCode, 1, resObj->retStatus);
        CU_ASSERT_EQUAL((int)statusCode, cJSON_GetObjectItem(response, "statusCode")->valueint);
                
        WdmpInfo("Message : %s\n",cJSON_GetObjectItem(response, "message")->valuestring);
        mapWdmpStatusToStatusMessage(resObj->retStatus[0], &result);
        CU_ASSERT_STRING_EQUAL(result, cJSON_GetObjectItem(response, "message")->valuestring);

        if(result)
        {
                free(result);
        }
}

void get_res_form()
{
        res_struct *resObj = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        cJSON *response = cJSON_CreateObject();
        
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
        
        resObj->u.getRes->params[0][0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[0][0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[0][0].name, "Device.WIFi.SSID.1.SSID");
        strcpy(resObj->u.getRes->params[0][0].value, "ssid1");
        resObj->u.getRes->params[0][0].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[1][0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[1][0].name, "Device.DeviceInfo.Webpa.Enable");
        strcpy(resObj->u.getRes->params[1][0].value, "true");
        resObj->u.getRes->params[1][0].type = WDMP_BOOLEAN;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_get_response(resObj, response);
        
        CU_ASSERT( NULL != response);
	
	    verify_get_reponse(response, resObj);

        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
            cJSON_Delete(response);
        }
}

void get_wildcard_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON * response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
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
        
        resObj->u.getRes->params[0][0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[0][0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[0][0].name, "Device.WIFi.SSID.1.Enable");
        strcpy(resObj->u.getRes->params[0][0].value, "true");
        resObj->u.getRes->params[0][0].type = WDMP_BOOLEAN;
        
        resObj->u.getRes->params[1][0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[1][0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[1][0].name, "Device.Webpa.PostData");
        strcpy(resObj->u.getRes->params[1][0].value, "Not Supported");
        resObj->u.getRes->params[1][0].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][1].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[1][1].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[1][1].name, "Device.Webpa.X_RDKCENTRAL-COM_WebPA_Notification");
        strcpy(resObj->u.getRes->params[1][1].value, "Not Supported");
        resObj->u.getRes->params[1][1].type = WDMP_STRING;
        
        resObj->u.getRes->params[1][2].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[1][2].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[1][2].name, "Device.Webpa.X_RDKCENTRAL-COM_Connected-Client");
        strcpy(resObj->u.getRes->params[1][2].value,  "Not Supported");
        resObj->u.getRes->params[1][2].type = WDMP_STRING;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_get_reponse(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void get_attr_res_form()
{
        res_struct *resObj = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        response = cJSON_CreateObject();
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->params[0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->params[0].name, "Device.WIFi.SSID.1.Enable");
        strcpy(resObj->u.paramRes->params[0].value, "1");
        
        resObj->u.paramRes->params[1].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->params[1].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->params[1].name , "Device.WIFi.SSID.1.SSID");
        strcpy(resObj->u.paramRes->params[1].value, "1");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_get_attr_response(resObj,response);
        
        CU_ASSERT( NULL != response);
        
        verify_param_response(response,resObj);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
	{
		cJSON_Delete(response);
	}
}

void set_res_form()
{
        res_struct *resObj = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        response = cJSON_CreateObject();
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.paramRes->params[0].name, "Device.DeviceInfo.Webpa.Enable");
        resObj->u.paramRes->params[1].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.paramRes->params[1].name, "Device.WiFi.SSID.2.SSID");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_set_response(resObj, response);
        
        CU_ASSERT( NULL != response);
        
        verify_param_response(response,resObj);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
	{
		cJSON_Delete(response);
	}
}

void set_attr_res_form()
{
        res_struct *resObj = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        response = cJSON_CreateObject();
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.paramRes->params[0].name , "Device.WiFi.SSID.1.Enable");
        resObj->u.paramRes->params[1].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.paramRes->params[1].name , "Device.WiFi.SSID.1.SSID");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_set_response(resObj, response);
        
        CU_ASSERT( NULL != response);
        
        verify_param_response(response,resObj);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
	{
		cJSON_Delete(response);
	}
}

void test_and_set_res_form()
{
        res_struct *resObj = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        response = cJSON_CreateObject();
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = TEST_AND_SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        
        resObj->u.paramRes->syncCMC = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->syncCID = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.paramRes->syncCMC , "512");
        strcpy(resObj->u.paramRes->syncCID , "1234");
        
        resObj->timeSpan = NULL;
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_test_and_set_response(resObj, response);
        
        CU_ASSERT( NULL != response);
        
        verify_testandset_response(response,resObj);

        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
	{
		cJSON_Delete(response);
	}
}

void add_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = ADD_ROWS;
        
        resObj->u.tableRes = (table_res_t *) malloc(sizeof(table_res_t));
        
        resObj->u.tableRes->newObj = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        strcpy(resObj->u.tableRes->newObj , "Device.WiFi.AccessPoint.10001.X_CISCO_COM_MacFilterTable.1.");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_table_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void replace_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = REPLACE_ROWS;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_table_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);

}

void delete_row_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = DELETE_ROW;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj, &payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_table_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void table_res_form()
{
        res_struct *resObj = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        response = cJSON_CreateObject();
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = ADD_ROWS;
        resObj->u.tableRes = (table_res_t *) malloc(sizeof(table_res_t));
        resObj->u.tableRes->newObj = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.tableRes->newObj , "Device.NAT.PortMapping.5.");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_SUCCESS;
        
        wdmp_form_table_response(resObj, response);
        
        CU_ASSERT( NULL != response);
        
        verify_table_response(response,resObj);

        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
	{
		cJSON_Delete(response);
	}

}

void test_get_status_code()
{
        WDMP_RESPONSE_STATUS_CODE statusCode;
        WDMP_STATUS * ret = NULL;
        int paramCount = 3;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        ret = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS)*paramCount);
        
        ret[0] = WDMP_SUCCESS;
        ret[1] = WDMP_SUCCESS;
        ret[2] = WDMP_ERR_WIFI_BUSY;
        
        getStatusCode(&statusCode, paramCount, ret);
        
        CU_ASSERT_EQUAL( WDMP_STATUS_WIFI_BUSY, statusCode );
        
        WdmpInfo("statusCode : %d\n",statusCode);
        
        if(ret)
        {
                free(ret);
        }
}

void test_map_wdmp_status()
{
        WDMP_STATUS status;
        char *result = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        status = WDMP_ERR_SET_OF_CMC_OR_CID_NOT_SUPPORTED;
                
        mapWdmpStatusToStatusMessage(status, &result);
        
        CU_ASSERT( NULL != result );
        
        CU_ASSERT_STRING_EQUAL( "SET of CMC or CID is not supported", result );
        
        WdmpInfo("result : %s\n",result);
        
        if(result)
        {
                free(result);
        }
}

void neg_get_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON * response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET;
        resObj->paramCnt = 2;
        
        resObj->u.getRes = (get_res_t *) malloc(sizeof(get_res_t));
        memset(resObj->u.getRes, 0, sizeof(get_res_t));
        
        resObj->u.getRes->retParamCnt = NULL;
        
        resObj->u.getRes->paramCnt = resObj->paramCnt;
        resObj->u.getRes->paramNames = (char **) malloc(sizeof(char *) * resObj->u.getRes->paramCnt);
        resObj->u.getRes->paramNames[0] = "Device.WIFi.SSID.1.Enable";
        resObj->u.getRes->paramNames[1] = "Device.DeviceIfo.SSID.";
        
        resObj->u.getRes->params = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_ERR_UNSUPPORTED_NAMESPACE;
        resObj->retStatus[1] = WDMP_ERR_UNSUPPORTED_NAMESPACE;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void get_wildcard_empty_value_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET;
        resObj->paramCnt = 2;
        
        resObj->u.getRes = (get_res_t *) malloc(sizeof(get_res_t));
        memset(resObj->u.getRes, 0, sizeof(get_res_t));
        
        resObj->u.getRes->retParamCnt = (size_t *) malloc(sizeof(size_t)*2);
        resObj->u.getRes->retParamCnt[0] = 1;
        resObj->u.getRes->retParamCnt[1] = 0;
        
        resObj->u.getRes->paramCnt = resObj->paramCnt;
        resObj->u.getRes->paramNames = (char **) malloc(sizeof(char *) * resObj->u.getRes->paramCnt);
        resObj->u.getRes->paramNames[0] = "Device.WIFi.SSID.2.Enable";
        resObj->u.getRes->paramNames[1] = "Device.Hosts.Host.";
        
        resObj->u.getRes->params = (param_t **) malloc(sizeof(param_t*)*2);
        memset(resObj->u.getRes->params, 0, sizeof(param_t*)*2);
        
        resObj->u.getRes->params[0]= (param_t *) malloc(sizeof(param_t)*resObj->u.getRes->retParamCnt[0]);
        resObj->u.getRes->params[1]= NULL;
        
        resObj->u.getRes->params[0][0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.getRes->params[0][0].value = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.getRes->params[0][0].name , "Device.WIFi.SSID.2.Enable");
        strcpy(resObj->u.getRes->params[0][0].value , "true");
        resObj->u.getRes->params[0][0].type = WDMP_BOOLEAN;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_SUCCESS;
        resObj->retStatus[1] = WDMP_SUCCESS;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_get_reponse(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_get_attr_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = GET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_ERR_INVALID_ATTRIBUTES;
        resObj->retStatus[1] = WDMP_ERR_INVALID_ATTRIBUTES;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_set_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_ERR_WILDCARD_NOT_SUPPORTED;
        resObj->retStatus[1] = WDMP_ERR_WILDCARD_NOT_SUPPORTED;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_set_attr_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = SET_ATTRIBUTES;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = (param_t *) malloc(sizeof(param_t)*2);
        memset(resObj->u.paramRes->params, 0, sizeof(param_t)*2);
        
        resObj->u.paramRes->params[0].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->params[1].name = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->params[0].name , "Device.WiFi.SSID.4.SSID");
        strcpy(resObj->u.paramRes->params[1].name , "Device.WiFi.Radio.2.Enable");
        
        resObj->timeSpan = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS) * 2);
        resObj->retStatus[0] = WDMP_ERR_INVALID_PARAMETER_NAME;
        resObj->retStatus[1] = WDMP_ERR_INVALID_PARAMETER_NAME;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_param_response(response, resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_test_and_set_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = TEST_AND_SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        
        resObj->u.paramRes->syncCMC = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->syncCID = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->syncCMC , "128");
        strcpy(resObj->u.paramRes->syncCID , "abcd");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_SETTING_CMC_OR_CID;
        
        wdmp_form_response(resObj, &payload);

        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_testandset_response(response, resObj);
        
        WdmpInfo("Payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void test_cmc()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = TEST_AND_SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        resObj->u.paramRes->syncCMC = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        resObj->u.paramRes->syncCID = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->syncCMC, "1234");
        strcpy(resObj->u.paramRes->syncCID, "abcd");
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_CMC_TEST_FAILED;
        
        wdmp_form_response(resObj, &payload);

        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response, resObj);
        
        WdmpInfo("Payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void test_and_set_without_cid_res_form()
{

        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = TEST_AND_SET;
        resObj->paramCnt = 2;
        
        resObj->u.paramRes = (param_res_t *) malloc(sizeof(param_res_t));
        memset(resObj->u.paramRes, 0, sizeof(param_res_t));
        
        resObj->u.paramRes->params = NULL;
        
        resObj->u.paramRes->syncCMC = (char *) malloc(sizeof(char) * MAX_PARAM_LEN);
        
        strcpy(resObj->u.paramRes->syncCMC, "128");
        resObj->u.paramRes->syncCID = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_NEW_CID_IS_MISSING;
        
        wdmp_form_response(resObj, &payload);

        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response, resObj);
        
        WdmpInfo("Payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_add_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = ADD_ROWS;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_NOT_WRITABLE;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);
}

void neg_replace_rows_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = REPLACE_ROWS;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_INVALID_PARAMETER_VALUE;
        
        wdmp_form_response(resObj,&payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);

}

void neg_delete_row_res_form()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        cJSON *response = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = DELETE_ROW;
        
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_INVALID_PARAMETER_NAME;
        
        wdmp_form_response(resObj, &payload);
        
        CU_ASSERT( NULL != payload);
        
        response = cJSON_Parse(payload);
        
        verify_failure_response(response,resObj);
        
        WdmpInfo("payload :%s\n",payload);
        
        if(NULL != resObj)
        {
                wdmp_free_res_struct(resObj);
        }
        
        if(response != NULL)
        {
                cJSON_Delete(response);
        }
        free(payload);

}

void test_unknown_req_type()
{
        res_struct *resObj = NULL;
        char *payload = NULL;
        
        WdmpInfo("\n***************************************************** \n\n");
        
        resObj = (res_struct *) malloc(sizeof(res_struct));
        memset(resObj, 0, sizeof(res_struct));
        
        resObj->reqType = 10;
        resObj->u.tableRes = NULL;
        
        resObj->timeSpan = NULL;
        
        resObj->retStatus = (WDMP_STATUS *) malloc(sizeof(WDMP_STATUS));
        resObj->retStatus[0] = WDMP_ERR_INVALID_PARAMETER_NAME;
        
        wdmp_form_response(resObj, &payload);
        
        CU_ASSERT( NULL == payload);
}

void get_large_parameter_req_parse()
{
        int i,paramCount;
        char *request = NULL;
        req_struct *reqObj = NULL;

        WdmpInfo("\n***************************************************** \n\n");

        request = "{ \"names\":[\"Device.DeviceInfo.Webpa.sfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR\",\"Device.DeviceInfo.Webpa.\"],\"command\": \"GET\"}";

        wdmp_parse_request(request,&reqObj);

        CU_ASSERT( NULL != reqObj);

        WdmpInfo("Request Type : %d\n",reqObj->reqType);

        CU_ASSERT_EQUAL( GET, reqObj->reqType );

        if(reqObj->u.getReq)
        {
                WdmpPrint("ParamCount : %zu\n",reqObj->u.getReq->paramCnt);
                paramCount = (int)reqObj->u.getReq->paramCnt;
                for (i = 0; i < paramCount; i++) 
                {
                    WdmpPrint("paramNames[%d] : %s\n",i,reqObj->u.getReq->paramNames[i]);
                    
                }
        }

        CU_ASSERT_EQUAL( 2, paramCount );
        CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.Webpa.sfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR", reqObj->u.getReq->paramNames[0] );
        CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.Webpa.", reqObj->u.getReq->paramNames[1] );

        if (NULL != reqObj) {
                wdmp_free_req_struct(reqObj );
        }  
}

void set_large_parameter_req_parse()
{
    int i,paramCount;
    char *request = NULL;
    req_struct *reqObj = NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
      
    request= "{\"parameters\":[{\"name\":\"Device.DeviceInfo.ProductClass.sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR\",\"value\":\"XB3\",\"dataType\":0},{\"name\":\"Device.DeviceInfo.SerialNumber\",\"value\":\"sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR\",\"dataType\":0}],\"command\":\"SET\"}";
 
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( SET, reqObj->reqType );
    
    WdmpInfo("Request Type : %d\n",reqObj->reqType);
    WdmpPrint("Param Count : %zu\n",reqObj->u.setReq->paramCnt);
    paramCount = (int)reqObj->u.setReq->paramCnt;
    for (i = 0; i < paramCount; i++) 
	{
	    WdmpPrint("param[%d].name : %s\n",i,reqObj->u.setReq->param[i].name);
	    WdmpPrint("param[%d].value : %s\n",i,reqObj->u.setReq->param[i].value);
	    WdmpPrint("param[%d].type : %d\n",i,reqObj->u.setReq->param[i].type);
	}
	
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.ProductClass.sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR", reqObj->u.setReq->param[0].name );
    CU_ASSERT_STRING_EQUAL( "Device.DeviceInfo.SerialNumber", reqObj->u.setReq->param[1].name );
    CU_ASSERT_STRING_EQUAL( "XB3", reqObj->u.setReq->param[0].value );
    CU_ASSERT_STRING_EQUAL( "sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR", reqObj->u.setReq->param[1].value );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[0].type );
    CU_ASSERT_EQUAL( WDMP_STRING, reqObj->u.setReq->param[1].type );  
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
}

void test_large_parameter_table_request()
{
    int i,paramCount,j,rowCnt;
    cJSON *request = NULL;
    req_struct *reqObj = NULL;
    char * payload= NULL;
    
    WdmpInfo("\n***************************************************** \n\n");
       
    payload= "{\"rows\":{\"0\":{\"DeviceName\":\"Device1\",\"sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR\":\"12:2:3:5:11\"},\"1\":{\"DeviceName\":\"sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR\",\"MacAddress\":\"2:1:3:5:7\"} },\"table\" : \"Device.WiFi.AccessPoint.10001.X_CISCO_COM_sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR.\",\"command\":\"REPLACE_ROWS\"}";
 
    CU_ASSERT( NULL != payload);
    
    request = cJSON_Parse(payload);
    
    (reqObj) = (req_struct *) malloc(sizeof(req_struct));
    memset( (reqObj), 0, sizeof( req_struct ) );
    
    parse_replace_rows_request(request,&reqObj);
    
    CU_ASSERT( NULL != reqObj);
    CU_ASSERT_EQUAL( REPLACE_ROWS, reqObj->reqType );
    
    WdmpInfo("Req Type : %d\n",reqObj->reqType);
    WdmpInfo("Object Name : %s\n",reqObj->u.tableReq->objectName);
    WdmpInfo("Row Count : %zu\n",reqObj->u.tableReq->rowCnt);
    rowCnt = (int)reqObj->u.tableReq->rowCnt;
    CU_ASSERT_STRING_EQUAL( "Device.WiFi.AccessPoint.10001.X_CISCO_COM_sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR.", reqObj->u.tableReq->objectName );
    CU_ASSERT_EQUAL( 2, rowCnt );
    
    for ( i = 0 ; i < rowCnt ; i++)
    {
        WdmpPrint("ParamCount: %zu\n",reqObj->u.tableReq->rows[i].paramCnt);
        paramCount = (int)reqObj->u.tableReq->rows[i].paramCnt;
        
        for( j = 0 ; j < paramCount ; j++)
        {
	        WdmpPrint("rows[%d].names[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].names[j]);				
	        WdmpPrint("rows[%d].values[%d] : %s\n",i,j,reqObj->u.tableReq->rows[i].values[j]);			
        }
    }
    
    CU_ASSERT_EQUAL( 2, paramCount );
    CU_ASSERT_STRING_EQUAL( "DeviceName", reqObj->u.tableReq->rows[0].names[0] );
    CU_ASSERT_STRING_EQUAL( "Device1", reqObj->u.tableReq->rows[0].values[0] );
    CU_ASSERT_STRING_EQUAL( "sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR", reqObj->u.tableReq->rows[0].names[1] );
    CU_ASSERT_STRING_EQUAL( "12:2:3:5:11", reqObj->u.tableReq->rows[0].values[1] );
    CU_ASSERT_STRING_EQUAL( "DeviceName", reqObj->u.tableReq->rows[1].names[0] );
    CU_ASSERT_STRING_EQUAL( "sfdgfgherejfjfjkksfhjgkeraskkkkkkkkkkdweqlfdrkfhgsrsjljrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGsfdgfgherejrehigeiruwegwegwiegfuwgfegfwegfwefegaugdfosFYQWPIYRSDAWIEUFTGJVHEDFKWJESDFWEGFWEGFGAQWWEGYTEHERHAEGTWERHTBQR4WYTR", reqObj->u.tableReq->rows[1].values[0] );
    CU_ASSERT_STRING_EQUAL( "MacAddress", reqObj->u.tableReq->rows[1].names[1] );
    CU_ASSERT_STRING_EQUAL( "2:1:3:5:7", reqObj->u.tableReq->rows[1].values[1] );
    
    if (NULL != reqObj) {
        wdmp_free_req_struct(reqObj );
    }
    if(NULL != request)
    {
        cJSON_Delete(request);
    }
}
void add_request_parse_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "wdmp-c request parsing tests", NULL, NULL );
    
    /* positive scenario tests */
    CU_add_test( *suite, "Test Get Request Parse", get_req_parse );
    CU_add_test( *suite, "Test Get attr Request Parse", get_attr_req_parse );
    CU_add_test( *suite, "Test Set Request Parse", set_req_parse );
    CU_add_test( *suite, "Test Set Request Parse with both value and attributes field", set_req_parse_with_attributes );
    CU_add_test( *suite, "Test Set attr Request Parse", set_attr_req_parse );
    CU_add_test( *suite, "Test Test and set Request Parse", test_and_set_req_parse );
    CU_add_test( *suite, "Test Replace row Request Parse", replace_rows_req_parse );
    CU_add_test( *suite, "Test Add row Request Parse", add_row_req_parse );
    CU_add_test( *suite, "Test Delete row Request Parse", delete_row_req_parse );
        
    /* negative scenario tests */
    CU_add_test( *suite, "Test Unknown command", test_unknown_command );
    CU_add_test( *suite, "Test Get Empty names", get_req_empty_names );
    CU_add_test( *suite, "Test Get Empty notify", get_req_empty_notify );
    CU_add_test( *suite, "Test Set Empty notify", set_req_empty_notify );
    CU_add_test( *suite, "Test and Set without cid", test_and_set_without_cid );
    CU_add_test( *suite, "Test Empty Test and Set Request", empty_test_and_set );
    CU_add_test( *suite, "Test Set Req NULL Param value", set_req_null_param_value );
    CU_add_test( *suite, "Test Set Req empty value field", set_req_value_field_empty );
    CU_add_test( *suite, "Test Get large parameter name Request", get_large_parameter_req_parse );
    CU_add_test( *suite, "Test Set large parameter name and value Request", set_large_parameter_req_parse );
    CU_add_test( *suite, "Test large parameter table Request", test_large_parameter_table_request );
 
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
    CU_add_test( *suite, "Table response Form", table_res_form );  
    CU_add_test( *suite, "Get status code", test_get_status_code );
    CU_add_test( *suite, "Map wdmp status", test_map_wdmp_status );   
    
    CU_add_test( *suite, "Negative Get Response Form", neg_get_res_form );
    CU_add_test( *suite, "Get Wildcard empty Response Form", get_wildcard_empty_value_res_form);
    CU_add_test( *suite, "Negative Get attributes Response Form", neg_get_attr_res_form );
    CU_add_test( *suite, "Negative Set Response Form", neg_set_res_form );   
    CU_add_test( *suite, "Negative Set attributes Response Form", neg_set_attr_res_form );  
    CU_add_test( *suite, "Negative test and set Response Form", neg_test_and_set_res_form);
    CU_add_test( *suite, "Test CMC ", test_cmc);  
    CU_add_test( *suite, "Test and set without CID Response Form", test_and_set_without_cid_res_form);  
    CU_add_test( *suite, "Negative Add row Response Form", neg_add_rows_res_form );
    CU_add_test( *suite, "Negative Replace rows Response Form", neg_replace_rows_res_form );
    CU_add_test( *suite, "Negative Delete row Response Form", neg_delete_row_res_form );
    CU_add_test( *suite, "Test unknown request type", test_unknown_req_type);
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
        
            CU_basic_show_failures( CU_get_failure_list() );
           
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
