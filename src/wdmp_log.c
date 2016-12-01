#include <stdio.h>
#include <string.h>
#include "wdmp_log.h"
#include <malloc.h>

/* log handling */
wdmpLogHandler     log_handler =NULL;


void wdmp_log ( int level, const char *msg, ...)
{
	char *pTempChar = NULL;		
	int nbytes = 0;
	
	va_list arg_ptr; 
	
	pTempChar = (char *)malloc(MSG_BUF_SIZE);
	if(pTempChar == NULL)
	{
	    printf("memory allocation failed inside wdmp_log().\n");
	}
	else
	{
		va_start (arg_ptr, msg);
		nbytes = vsnprintf(pTempChar, MSG_BUF_SIZE, msg, arg_ptr);
		va_end(arg_ptr);
		
		if(nbytes < 0)
		{	
			printf("Error occured in msg formatting in wdmp_log\n");
			perror(pTempChar);
		}
		else
		{
			if (NULL != log_handler)
			{			
				log_handler (level, pTempChar);
			
			}
			else
			{						
				if(level == LEVEL_ERROR)
				{
					printf("Error:%s",pTempChar);
				}			
				else if(level == LEVEL_INFO)
				{
					printf("Info:%s",pTempChar);
				}			
				else if(level == LEVEL_DEBUG)
				{
					printf("Debug:%s",pTempChar);
				}			
			}
		}

		if(pTempChar !=NULL)
		{
			free(pTempChar);
			pTempChar = NULL;
		}			
	}	
}

void wdmp_log_set_handler(wdmpLogHandler handler)
{
	if(handler == NULL)
	{
	  log_handler  = NULL;
	  return;
	}
	else
	{
	  log_handler   = handler;
	}
	
}

