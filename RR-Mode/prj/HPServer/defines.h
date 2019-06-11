/*
 * defines.h
 *
 *  Created on: 2012-9-12
 *      Author: yaowei
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <assert.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>

#include <event.h>

#include <log4cxx/logger.h>
#include <log4cxx/logstring.h>
#include <log4cxx/propertyconfigurator.h>
using namespace log4cxx;
extern LoggerPtr g_logger;

// 拷贝和赋值重载的宏定义替换
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
            TypeName(const TypeName&); \
            void operator=(const TypeName&)
// 之所以拷贝后面有分号，而赋值后面没分号，是因为
// 1.宏定义没有分号，2.宏名在使用处后面有分号正好
// 补给最后的分号。


#define CRLF "\r\n"

#define TOKEN_LENGTH 5
#define TOKEN_STR	 "12345"

#endif /* DEFINES_H_ */
