/*
+----------------------------------------------------------------------+
| SeasIpUtils                                                          |
+----------------------------------------------------------------------+
| This source file is subject to version 2.0 of the Apache license,    |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.apache.org/licenses/LICENSE-2.0.html                      |
| If you did not receive a copy of the Apache2.0 license and are unable|
| to obtain it through the world-wide-web, please send a note to       |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
| Author: Neeke.Gao  <neeke@php.net>                                   |
+----------------------------------------------------------------------+
*/

#ifndef _PHP_SEASIPUTILS_H_
#define _PHP_SEASIPUTILS_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "include/SeasIpUtils.h"

#ifdef PHP_WIN32
#include "win32/time.h"
#include <windows.h>
#elif defined(NETWARE)
#include <sys/timeval.h>
#include <sys/time.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

extern zend_module_entry seasiputils_module_entry;
#define phpext_seasiputils_ptr &seasiputils_module_entry

#ifdef PHP_WIN32
# define PHP_SEASIPUTILS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
# define PHP_SEASIPUTILS_API __attribute__ ((visibility("default")))
#else
# define PHP_SEASIPUTILS_API
#endif

ZEND_BEGIN_MODULE_GLOBALS(seasiputils)
zend_bool enable_ping;
ZEND_END_MODULE_GLOBALS(seasiputils)

extern ZEND_DECLARE_MODULE_GLOBALS(seasiputils);

#ifndef E_EXCEPTION
# define E_EXCEPTION (1<<15L)
#endif

PHP_MINIT_FUNCTION(seasiputils);
PHP_MSHUTDOWN_FUNCTION(seasiputils);
PHP_RINIT_FUNCTION(seasiputils);
PHP_RSHUTDOWN_FUNCTION(seasiputils);
PHP_MINFO_FUNCTION(seasiputils);

PHP_FUNCTION(seasiputils_get_version);

extern zend_class_entry *seasiputils_ce;
PHP_METHOD(SEASIPUTILS_RES_NAME, __construct);
PHP_METHOD(SEASIPUTILS_RES_NAME, __destruct);
PHP_METHOD(SEASIPUTILS_RES_NAME, pingExecute);

#endif /* _PHP_SEASIPUTILS_H_ */

