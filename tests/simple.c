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

void get_req_parse ()
{
    printf("\n\n******** GET Request Parsing *******\n\n");
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
    printf("\n\n******** GET_ATTRIBUTES Request Parsing *******\n\n");
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
    printf("\n\n******** SET Request Parsing *******\n\n");
    
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
    printf("\n\n******** SET_ATTRIBUTES Request Parsing *******\n\n");
    
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
    printf("\n\n******** TEST_AND_SET Request Parsing *******\n\n");
    
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
    printf("\n\n******** REPLACE_ROWS Request Parsing *******\n\n");
    
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
    printf("\n\n******** ADD_ROW Request Parsing *******\n\n");
    
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
    printf("\n\n******** DELETE_ROWS Request Parsing *******\n\n");
    
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
    printf("\n\n******** Negative Test case Unknown command *******\n\n");
    
    req_struct *reqObj = NULL;
    char * request= "{ \"names\":[\"Device.DeviceInfo.Webpa.Enable\",\"Device.WiFi.SSID.1.Enable\"],\"command\": \"UNKNOWN\"}";
    wdmp_parse_request(request,&reqObj);
    
    CU_ASSERT( NULL == reqObj);
}

void get_req_empty_names ()
{
    printf("\n\n******** Negative Test case Get Req Empty names *******\n\n");
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


void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "wdmp-c encoding tests", NULL, NULL );
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



/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
        return 1;
    }
    return 0;
}
