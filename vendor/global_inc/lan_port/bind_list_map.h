#ifndef __BIND_LIST_MAP_H__
#define __BIND_LIST_MAP_H__

struct bindlist_map
{
    char *bindif;
    char *realif;
    char  bit;
    char  mark;
};

/* support four lan port and four wlan port */
static const struct bindlist_map bl_map_data[] = 
{
    {"LAN1",        "eth0.1",    0x0,       0x1},
    {"LAN2",        "eth0.2",    0x1,       0x2},
    {"LAN3",        "eth0.3",    0x2,       0x3},
    {"LAN4",        "eth0.4",    0x3,       0x4},
    {"LAN5",        "eth0.5",    0x4,       0x5},
    {"LAN6",        "eth0.6",    0x5,       0x6},
    {"LAN7",        "eth0.7",    0x6,       0x7},
    {"LAN8",        "eth0.8",    0x7,       0x8},

    {"SSID1",       "ra0",       0x8,       0x9},
    {"SSID2",       "ra1",       0x9,       0xA},
    {"SSID3",       "ra2",       0xA,       0xB},
    {"SSID4",       "ra3",       0xB,       0xC},
    {"SSID5",       "ra4",       0xC,       0xD},
    {"SSID6",       "ra5",       0xD,       0xE},
    {"SSID7",       "ra6",       0xE,       0xF},
    {"SSID8",       "ra7",       0xF,       0x10},

    {"SSIDAC1",     "rai0",      0x10,      0x11},
    {"SSIDAC2",     "rai1",      0x11,      0x12},
    {"SSIDAC3",     "rai2",      0x12,      0x13},
    {"SSIDAC4",     "rai3",      0x13,      0x14},
    {"SSIDAC5",     "rai4",      0x14,      0x15},
    {"SSIDAC6",     "rai5",      0x15,      0x16},
    {"SSIDAC7",     "rai6",      0x16,      0x17},
    {"SSIDAC8",     "rai7",      0x17,      0x18},

    {"USB",         "usb0",      0x18,      0x19},
    {"WDS",         "wds0",      0x19,      0x1A},
};

static inline int mark_convert_bind_itf_name(int mark, char* bind_itf_name, int size)
{
	int i = 0;
	memset(bind_itf_name, 0, size);
	for(i = 0; i < sizeof(bl_map_data) / sizeof(bl_map_data[0]); i++)
	{
		if(bl_map_data[i].mark == mark)
		{
			snprintf(bind_itf_name, size, bl_map_data[i].bindif);
			return 0;
		}
	}
	
	return -1;
}

static inline int mark_convert_real_itf_name(int mark, char* real_itf_name, int size)
{
	int i = 0;
	memset(real_itf_name, 0, size);
	for(i = 0; i < sizeof(bl_map_data) / sizeof(bl_map_data[0]); i++)
	{
		if(bl_map_data[i].mark == mark)
		{
			snprintf(real_itf_name, size, bl_map_data[i].realif);
			return 0;
		}
	}
	
	return -1;
}

static inline int bit_convert_bind_itf_name(int bit, char* bind_itf_name, int size)
{
	int i = 0;
	memset(bind_itf_name, 0, size);
	for(i = 0; i < sizeof(bl_map_data) / sizeof(bl_map_data[0]); i++)
	{
		if(bl_map_data[i].bit == bit)
		{
			snprintf(bind_itf_name, size, bl_map_data[i].bindif);
			return 0;
		}
	}
	
	return -1;
}

static inline int bit_convert_real_itf_name(int bit, char* real_itf_name, int size)
{
	int i = 0;
	memset(real_itf_name, 0, size);
	for(i = 0; i < sizeof(bl_map_data) / sizeof(bl_map_data[0]); i++)
	{
		if(bl_map_data[i].bit == bit)
		{
			snprintf(real_itf_name, size, bl_map_data[i].realif);
			return 0;
		}
	}
	
	return -1;
}


#endif

