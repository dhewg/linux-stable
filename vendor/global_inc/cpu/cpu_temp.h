#ifndef __CPU_TEMP_H__
#define __CPU_TEMP_H__

#define CPU_TEMP_SOCK 		"/tmp/cpu_temp_sock"
#define CPU_TEMP_MSG_LEN	32
#define MAX_CLIENTS			5

typedef struct cpu_temp_msg_s
{
	int cpu_temp;
}cpu_temp_msg_t;

#endif
