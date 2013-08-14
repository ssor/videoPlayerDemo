#if !defined(UDPHELPER_H)
#define UDPHELPER_H

//long pPlayerDlgHandle;
unsigned long WINAPI setupUDPServer(void* argv);
int SendToClient(char * buffer,char* ip, int port);

#endif

