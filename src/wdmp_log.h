#include <stdarg.h>
#include <cimplog.h>

#define LEVEL_ERROR 0
#define LEVEL_INFO  1
#define LEVEL_DEBUG 2

#define MSG_BUF_SIZE	4096

#ifdef CIMP_LOGGER

#define WdmpError(...)	cimplog_error("WDMP-C", __VA_ARGS__)
#define WdmpInfo(...)	cimplog_info("WDMP-C", __VA_ARGS__)
#define WdmpPrint(...)	cimplog_debug("WDMP-C", __VA_ARGS__)
 
#else

#define WdmpError(...)	wdmp_log (LEVEL_ERROR, __VA_ARGS__)
#define WdmpInfo(...)	wdmp_log (LEVEL_INFO, __VA_ARGS__)
#define WdmpPrint(...)	wdmp_log (LEVEL_DEBUG, __VA_ARGS__)

#endif

