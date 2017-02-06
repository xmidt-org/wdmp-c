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
/**
 * @brief Handler used by wdmp_log_set_handler to receive all log
 * notifications produced by the library on this function.
 *
 * @param level The log level
 *
 * @param log_msg The actual log message reported.
 *
 */
typedef void (*wdmpLogHandler) (int level, const char * log_msg);

/**
* @brief Allows to define a log handler that will receive all logs
* produced under the provided content.
* 
* @param handler The handler to be called for each log to be
* notified. Passing in NULL is allowed to remove any previously
* configured handler.
*/

void wdmp_log_set_handler(wdmpLogHandler handler);

/**
* @brief handle log message based on log level
* 
* @param level of log info,debug,error
* @param logging message
*/

void wdmp_log (  int level, const char *fmt, ...);
