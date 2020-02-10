/*
  +----------------------------------------------------------------------+
  | SeasIpUtils                                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Chitao Gao  <neeke@php.net>                                  |
  +----------------------------------------------------------------------+
*/

#ifndef _SEASIPUTILS_H_
#define _SEASIPUTILS_H_

#include "php.h"
#include "php_ini.h"
#include "main/php_main.h"
#include "php_streams.h"
#include "zend_extensions.h"
#include "zend_exceptions.h"
#include "ext/standard/info.h"
#include "ext/standard/file.h"
#include "ext/standard/php_string.h"
#include "ext/date/php_date.h"
#include "php7_wrapper.h"
#include "ping_common.h"

#if PHP_VERSION_ID >= 70000
#include "zend_smart_str.h"
#else
#include "ext/standard/php_smart_str.h"
#endif

#ifdef ZTS
#include "TSRM.h"
#define SEASIPUTILS_G(v) TSRMG(seasiputils_globals_id, zend_seasiputils_globals *, v)
#else
#define SEASIPUTILS_G(v) (seasiputils_globals.v)
#endif

#ifndef E_EXCEPTION
# define E_EXCEPTION (1<<15L)
#endif

#include <stdlib.h>

#define SEASIPUTILS_RES_NAME                    "SeasIpUtils"
#define SEASIPUTILS_AUTHOR                      "Chitao.Gao  [ neeke@php.net ]"
#define SEASIPUTILS_VERSION                     "0.1.0"
#define SEASIPUTILS_VERSION_ID                  00100
#define SEASIPUTILS_SUPPORTS                    "https://github.com/SeasX/SeasIpUtils"

#define SL_S(s)                                 s, sizeof(s) - 1


#define SEASIPUTILS_LOGO_DATA "data:image/png;base64,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"

#define SEASIPUTILS_LOGO_IMG "<a href=\"http://seasx.io\"><img src=\""SEASIPUTILS_LOGO_DATA"\" height=\"20px\" alt=\"SeasIpUtils logo\"></a>\n"

#include "struct_common.h"

void seasx_throw_exception(int type TSRMLS_DC, const char *format, ...);

#endif /* _SEASIPUTILS_H_ */

