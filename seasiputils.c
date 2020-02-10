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

#include "php_seasiputils.h"

ZEND_DECLARE_MODULE_GLOBALS(seasiputils);
static PHP_GINIT_FUNCTION(seasiputils);
static PHP_GSHUTDOWN_FUNCTION(seasiputils);

#ifdef COMPILE_DL_SEASIPUTILS
ZEND_GET_MODULE(seasiputils)
#endif

zend_class_entry *seasiputils_ce;

const zend_function_entry seasiputils_functions[] =
{
    PHP_FE(seasiputils_get_version, NULL)
    {
        NULL, NULL, NULL
    }
};

#if ZEND_MODULE_API_NO >= 20050922
zend_module_dep seasiputils_deps[] =
{
    {
        NULL, NULL, NULL
    }
};
#endif

ZEND_BEGIN_ARG_INFO_EX(seasiputils_pingExecute_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, ping_command)
ZEND_END_ARG_INFO()

const zend_function_entry seasiputils_methods[] =
{
    PHP_ME(SEASIPUTILS_RES_NAME, __construct,   NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(SEASIPUTILS_RES_NAME, __destruct,    NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)

    PHP_ME(SEASIPUTILS_RES_NAME, pingExecute,   seasiputils_pingExecute_arginfo, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

    {
        NULL, NULL, NULL
    }
};

PHP_INI_BEGIN()
STD_PHP_INI_ENTRY("seasiputils.enable_ping", "1", PHP_INI_SYSTEM, OnUpdateBool, enable_ping, zend_seasiputils_globals, seasiputils_globals)
PHP_INI_END()

static PHP_GINIT_FUNCTION(seasiputils)
{
    memset(seasiputils_globals, 0, sizeof(zend_seasiputils_globals));
}

static PHP_GSHUTDOWN_FUNCTION(seasiputils)
{

}

PHP_MINIT_FUNCTION(seasiputils)
{
    zend_class_entry seasiputils;

    REGISTER_INI_ENTRIES();

    REGISTER_STRINGL_CONSTANT("SEASIPUTILS_VERSION",   SEASIPUTILS_VERSION,   sizeof(SEASIPUTILS_VERSION) - 1,  CONST_PERSISTENT | CONST_CS);
    REGISTER_STRINGL_CONSTANT("SEASIPUTILS_AUTHOR",    SEASIPUTILS_AUTHOR,    sizeof(SEASIPUTILS_AUTHOR) - 1,   CONST_PERSISTENT | CONST_CS);

    INIT_CLASS_ENTRY(seasiputils, SEASIPUTILS_RES_NAME, seasiputils_methods);

#if PHP_VERSION_ID >= 70000
    seasiputils_ce = zend_register_internal_class_ex(&seasiputils, NULL);
#else
    seasiputils_ce = zend_register_internal_class_ex(&seasiputils, NULL, NULL TSRMLS_CC);
#endif

    seasiputils_ce->ce_flags |= ZEND_ACC_FINAL;

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(seasiputils)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}

PHP_RINIT_FUNCTION(seasiputils)
{
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(seasiputils)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(seasiputils)
{
    php_info_print_table_start();

    if (PG(expose_php) && !sapi_module.phpinfo_as_text)
    {
        php_info_print_table_header(2, "SeasIpUtils support", SEASIPUTILS_LOGO_IMG"enabled");
    }
    else
    {
        php_info_print_table_header(2, "SeasIpUtils support", "Enabled");
    }

    php_info_print_table_row(2, "SeasIpUtils Version", SEASIPUTILS_VERSION);
    php_info_print_table_row(2, "SeasIpUtils Author", SEASIPUTILS_AUTHOR);
    php_info_print_table_row(2, "SeasIpUtils Supports", SEASIPUTILS_SUPPORTS);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}

zend_module_entry seasiputils_module_entry =
{
#if ZEND_MODULE_API_NO >= 20050922
    STANDARD_MODULE_HEADER_EX, NULL,
    seasiputils_deps,
#else
    STANDARD_MODULE_HEADER,
#endif
    SEASIPUTILS_RES_NAME,
    seasiputils_functions,
    PHP_MINIT(seasiputils),
    PHP_MSHUTDOWN(seasiputils),
    PHP_RINIT(seasiputils),
    PHP_RSHUTDOWN(seasiputils),
    PHP_MINFO(seasiputils),
    SEASIPUTILS_VERSION,
    PHP_MODULE_GLOBALS(seasiputils),
    PHP_GINIT(seasiputils),
    PHP_GSHUTDOWN(seasiputils),
    NULL,
    STANDARD_MODULE_PROPERTIES_EX
};

/* {{{ proto string seasiputils_get_version()
   Return SeasIpUtils version */
PHP_FUNCTION(seasiputils_get_version)
{
    SEASIPUTILS_RETURN_STRINGL(SEASIPUTILS_VERSION, strlen(SEASIPUTILS_VERSION));
}
/* }}} */

PHP_METHOD(SEASIPUTILS_RES_NAME, __construct)
{
    RETURN_TRUE;
}

PHP_METHOD(SEASIPUTILS_RES_NAME, __destruct)
{
    RETURN_TRUE;
}

int processCommand(char *rawStr, process_result *command)
{
    char input[50] = {'\0'};
    sprintf(input, "%s", rawStr);
    command->length = 0;

    char *delim = " ";
    char *p = strtok(input,delim);
    while(p!=NULL)
    {
        char *tmp;
        spprintf(&tmp, 0, "%s", p);
        command->command[command->length] = tmp;
        p = strtok(NULL,delim);
        command->length++;
    }

    return SUCCESS;
}

int efreeCommand(process_result *command)
{
    int i = 0;
    for (i=0; i<command->length; i++)
    {
        efree(command->command[i]);
    }
    command->length = 0;
    efree(command);

    return SUCCESS;
}

int efreeResult(ping_result *result)
{
    if (result->hostname) efree(result->hostname);
    if (result->sin_addr) efree(result->sin_addr);
    if (result->datalen) efree(result->datalen);

    if (result->rtt_min_ms) efree(result->rtt_min_ms);
    if (result->rtt_avg_ms) efree(result->rtt_avg_ms);
    if (result->rtt_max_ms) efree(result->rtt_max_ms);
    if (result->rtt_mdev_ms) efree(result->rtt_mdev_ms);

    if (result->ipg_ms) efree(result->ipg_ms);
    if (result->ewma_ms) efree(result->ewma_ms);

    int i = 0;
    for (i = 0; i < result->raw_result_length; i++)
    {
        efree(result->raw_result[i]);
    }

    efree(result);

    return SUCCESS;
}

/* {{{ proto bool pingExecute(string ping_command)*/
PHP_METHOD(SEASIPUTILS_RES_NAME, pingExecute)
{
    zval *_ping_command;
    int argc = ZEND_NUM_ARGS();

#if PHP_VERSION_ID >= 70000
    zval raw_result_array;
#else
    zval *raw_result_array;
#endif

    if (zend_parse_parameters(argc TSRMLS_CC, "z", &_ping_command) == FAILURE)
    {
        return;
    }

    if (argc > 0 && (IS_STRING == Z_TYPE_P(_ping_command) && Z_STRLEN_P(_ping_command) > 0))
    {
        process_result *command = (process_result *)emalloc(sizeof(process_result));
        ping_result *result = (ping_result *)emalloc(sizeof(ping_result));

        processCommand(Z_STRVAL_P(_ping_command), command);

        ping_exception *exception = ping_main(command->length, command->command, result);
        if (NULL != exception && exception->exception_code)
        {
            seasx_throw_exception(exception->exception_code TSRMLS_CC, exception->exception_message);
        }

        array_init(return_value);
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("hostname"), result->hostname);
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("sin_addr"), result->sin_addr);
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("datalen"), result->datalen);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("ntransmitted"), result->ntransmitted);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("nreceived"), result->nreceived);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("nrepeats"), result->nrepeats);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("nchecksum"), result->nchecksum);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("nerrors"), result->nerrors);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("time_ms"), result->time_ms);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("packet_loss"), result->packet_loss);
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("pipesize"), result->pipesize);
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("rtt_min_ms"), result->rtt_min_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("rtt_avg_ms"), result->rtt_avg_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("rtt_max_ms"), result->rtt_max_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("rtt_mdev_ms"), result->rtt_mdev_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("ipg_ms"), result->ipg_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_STRING_EX(return_value, SEASIPUTILS_STRS("ewma_ms"), result->ewma_ms ?: "");
        SEASIPUTILS_ADD_ASSOC_LONG_EX(return_value, SEASIPUTILS_STRS("raw_result_length"), result->raw_result_length);

        SEASIPUTILS_ARRAY_INIT(raw_result_array);

        int i = 0;
        for (i=0; i<result->raw_result_length; i++)
        {
            SEASIPUTILS_ADD_NEXT_INDEX_STRING(raw_result_array, result->raw_result[i]);
        }
        SEASIPUTILS_ADD_ASSOC_ZVAL_EX_EX(return_value, SEASIPUTILS_STRS("raw_result"), raw_result_array);

        efreeCommand(command);
        efreeResult(result);
    }
    else
    {
        RETURN_FALSE;
    }
}
/* }}} */

void seasx_throw_exception(int type TSRMLS_DC, const char *format, ...)
{
    va_list args;
    char *message = NULL;

    va_start(args, format);
    vspprintf(&message, 0, format, args);

#if PHP_VERSION_ID >= 70000
    zend_throw_exception_ex(NULL, type, "%s", message);
#else
    zend_throw_exception_ex(NULL, type TSRMLS_CC, "%s", message);
#endif

    efree(message);
    va_end(args);
}
