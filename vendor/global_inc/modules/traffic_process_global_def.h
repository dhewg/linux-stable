#ifndef _TRAFFIC_PROCESS_GLOBAL_DEF_H_
#define _TRAFFIC_PROCESS_GLOBAL_DEF_H_

/* for TRAFFIC PROCESS. */
#define CMD_TRAFFIC_GET_COUNT		(1)
#define CMD_TRAFFIC_GET_DATA		(2)

#define TRAFFIC_MODULE_NAME         "traffic_process"
#define TRAFFIC_MAJOR             	(251)
#define TRAFFIC_MAX_FLOWNUM_RULE 	255
#define TRAFFIC_MAX_DOMAIN_LEN		256
#define PPEMGR_TYPE_UPSTREAM 0
#define PPEMGR_TYPE_DWSTREAM 1
#define PPEMGR_TYPE_BOTH 2	

#define PPEMGR_SIGN_TRAFFIC_DETAIL 0
#define PPEMGR_SIGN_TRAFFIC_MIRROR 1
#define PPEMGR_SIGN_TRAFFIC_MONITOR 2

#define TRAFFIC_MIRROR_PATH 				"/etc/TrafficMirror.data"
#define TRAFFIC_MONITOR_PATH				"/etc/TrafficMonitor.data"

typedef struct _ecnt_ip_addr_ {
  union {
	struct in_addr addr4;
	struct in6_addr addr6;
  } addr;
}ecnt_ip_addr;

typedef struct _ecnt_sock_addr_ {
  union {
	struct sockaddr_in sock_dst;
	struct sockaddr_in6 sock6_dst;
  } sock;
}ecnt_sock_addr;

typedef struct _traffic_monitor_data_s
{
	ecnt_ip_addr ecnt_addr;
	int port;
}traffic_monitor_data;

typedef struct _traffic_mirror_data_s
{
	char ipaddress[40];
	ecnt_sock_addr mirror_dst;
	int to_ai_family;
	int mirror_isloop;
	void *socket;
}traffic_mirror_data;

typedef struct _traffic_mirror_install_data_s
{
	int sockfd_loop;
	int sockfd_wan;
	int sockfd_loopv6;
	int sockfd_wanv6;
	int sockfd_lanv6;
}traffic_mirror_install_data;

typedef enum
{
	E_TRAFFIC_MONITOR		= 1,
	E_TRAFFIC_MIRROR,
	E_TRAFFIC_MAX			= 4
}TRAFFIC_TYPE;

typedef enum
{
	E_CMD_INSTALL 			= 1,
	E_CMD_UNINSTALL,
	E_CMD_MONITOR_CNT,
	E_CMD_MONITOR_DATE,
	E_CMD_ADD_MIRROR_RULE
}TRAFFIC_CMD_TYPE;

typedef struct _traffic_ioctl_data_s
{
	int traffic_type;
	int data_len;
	void *data;
}traffic_ioctl_data;

typedef struct _monitor_file_node_info_
{
	char destAddr[TRAFFIC_MAX_DOMAIN_LEN];
}monitor_file_node_info_t, *pt_monitor_file_node_info;

typedef struct _monitor_file_bundle_info_
{
	char bundle_name[TRAFFIC_MAX_DOMAIN_LEN];
	int node_count;
	monitor_file_node_info_t node[TRAFFIC_MAX_FLOWNUM_RULE];
}monitor_file_bundle_info_t, *pt_monitor_file_bundle_info;

typedef struct _monitor_file_info_
{
	unsigned int monitor_timeout;
	char wan_ipv4[20];
	char wan_ipv6[40];
	char wan_name[65];
	char wan_name6[65];
	monitor_file_bundle_info_t bundle[8];
}monitor_file_info_t, *pt_monitor_file_info;

typedef struct _mirror_file_node_info_
{
	char remoteAddress[TRAFFIC_MAX_DOMAIN_LEN];
	char remotePort[20];
	char direction[12];
	char protocol[12];
	char hostMAC[20];
	char mirrorToIP[64];
	char mirrorToPort[12];
}mirror_file_node_info_t, *pt_mirror_file_node;

typedef struct _mirror_file_info_
{
	int node_count;
	char wan_ipv4[20];
	char wan_ipv6[40];
	char lan_ipv6[40];
	int lan_ipv6_nummask;
	mirror_file_node_info_t node[TRAFFIC_MAX_FLOWNUM_RULE];
}mirror_file_info_t, *pt_mirror_file_info;

#endif
