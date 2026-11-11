
/************************************************************************
 *
 *  loader_api.h
 *
 *  API file for load image module
 *
 * ######################################################################
 *
 * mips_start_of_header
 * 
 *  $Id: launch.h,v 1.6 2008-06-26 22:16:44 chris Exp $
 * 
 * Copyright (c) [Year(s)] MIPS Technologies, Inc. All rights reserved.
 *
 * Unpublished rights reserved under U.S. copyright law.
 *
 * PROPRIETARY/SECRET CONFIDENTIAL INFORMATION OF MIPS TECHNOLOGIES,
 * INC. FOR INTERNAL USE ONLY.
 *
 * Under no circumstances (contract or otherwise) may this information be
 * disclosed to, or copied, modified or used by anyone other than employees
 * or contractors of MIPS Technologies having a need to know.
 *
 * 
 * mips_end_of_header
 *
 ************************************************************************/
#ifndef NOTIFY_H
#define NOTIFY_H
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>

#define DBUS_MQ_FLAG_PATH "/tmp/dbus_mq"
#define DBUS_PROJ_ID 0x05

#define NOTIFY_TCAPI_SAVE_CALLED 	1 /*message queue for tcapi_save been called*/
#define NOTIFY_OBJECT_ADD		 	2 /*message queue for adding object*/
#define NOTIFY_OBJECT_DEL		 	3 /*message queue for deleteing object*/
#define NOTIFY_OBJECT_INITALL		4 /*message queue for init notify tab*/

typedef struct _dbus_notify_msg_data_s
{
	int notify_type;
	char object_path[64];
	char interface_name[64];
}dbus_notify_msg_data_t;

typedef struct _dbus_notify_msg_s
{
	int msgq_type;
	dbus_notify_msg_data_t text;
}dbus_notify_msg_t;

static inline int ctc_notify2dbus(int notify_type, char* object_path, char* interface_name)
{
	int ret;
	key_t mqkey;
	int mqid;
	dbus_notify_msg_t notify_msg;

	memset(&notify_msg, 0, sizeof(dbus_notify_msg_t));

	notify_msg.msgq_type = 1;
	notify_msg.text.notify_type = notify_type;
	if (NULL != object_path)
	{
		strncpy(notify_msg.text.object_path, object_path, 
			sizeof(notify_msg.text.object_path) - 1);
	}

	if (NULL != interface_name)
	{
		strncpy(notify_msg.text.interface_name, interface_name, 
			sizeof(notify_msg.text.interface_name) - 1);
	}
	
	mqkey = ftok(DBUS_MQ_FLAG_PATH, DBUS_PROJ_ID);
	mqid = msgget(mqkey, 0);   
	if(mqid < 0)
	{
		printf("\r\n open message queue fail!");
		return -1;
	}
	ret = msgsnd(mqid, &notify_msg, sizeof(dbus_notify_msg_data_t), IPC_NOWAIT);
	if(ret < 0)
	{
		printf("\r\n write message fail!");
		return -1;
	}
	
	return ret;	
}

#endif /* NOTIFY_H */
