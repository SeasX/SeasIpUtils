#ifndef _SEASIPUTILS_STRUCt_COMMON_H_
#define _SEASIPUTILS_STRUCt_COMMON_H_

#include "php_seasiputils.h"

typedef struct process_result_t
{
    char *command[100];
    long length;
} process_result;

typedef struct ping_result_t
{
    char *hostname;
    char *sin_addr;
    char *datalen;
    long ntransmitted;
    long nreceived;
    long nrepeats;
    long nchecksum;
    long nerrors;
    int packet_loss;
    long time_ms;
    char *rtt_min_ms;
    char *rtt_avg_ms;
    char *rtt_max_ms;
    char *rtt_mdev_ms;
    int pipesize;
    char *ipg_ms;
    char *ewma_ms;

    int raw_result_length;
    char *raw_result[50];
} ping_result;

typedef struct ping_exception_t
{
    int exception_code;
    char *exception_message;
} ping_exception;

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#define SEASIPUTILS_EXCEPTION_PROCESS_ERROR    5001

#endif /* _SEASIPUTILS_STRUCt_COMMON_H_ */