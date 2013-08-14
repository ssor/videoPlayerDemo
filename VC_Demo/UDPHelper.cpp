#include "stdafx.h"
#include "Player.h"
#include "PlayerDlg.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>

#include "global_def.h"
#include "Dav2Pic.h"

using namespace std;

#pragma comment(lib, "WS2_32.lib")

#define default_video_path  "c:\\davs"   
//#define default_video_path  "c:\\Users\\ssor\\Desktop\\video" 
#define default_udp_port 10001

//pPlayerDlgHandle= 0;
char* file_buffer = NULL;
void openDavFile(char* fileName)
{
	long handle = getPlayerDlgHandle();
    CPlayerDlg* dlg = (CPlayerDlg*)handle;
	if(file_buffer == NULL){
		file_buffer = (char*) malloc(1024);
	}
	ZeroMemory(file_buffer,1024);
    sprintf(file_buffer,"%s\\%s", default_video_path, fileName);
	dlg->OpenDavFile(file_buffer);//必需用绝对路径
	//dlg->OpenDavFile("c:\\test1-1374132261.dav");//必需用绝对路径
}

unsigned long WINAPI  setupUDPServer(void* argv)
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData = {0}; 

	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		cout << "initlization failed!" << endl;

		return 0;
	}

	SOCKET  s = 0;
	sockaddr_in sin = {0}; 

	sin.sin_family = AF_INET;
	sin.sin_port = htons(default_udp_port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;

	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout << "bind failed!" << endl;

		return 0;
	}

	char  buffer[1024] = "\0";
	sockaddr_in addr  = {0};
	int  nLen  = 0;

	nLen = sizeof(sockaddr_in);

	cout << "------- now service start -------------" << endl;

	while (true)
	{
		int nRecv = 0;

		cout << "wait to receive data............" << endl;

		nRecv = recvfrom(s, buffer, 1024, 0, (sockaddr*)&addr, &nLen);

		//***********************************
		/* 网络地址转化成ip地址 */

		char *clnt_ip;
		unsigned clnt_port;

		clnt_ip = inet_ntoa(addr.sin_addr);
		clnt_port = addr.sin_port;//端口转换。其实可以用inet_ntohs()
		
		//************************************


		if (nRecv > 0)
		{
			buffer[nRecv] = '\0';

			cout << "receve buffer: " << buffer << endl;
			setPicName(buffer);
			openDavFile(buffer);
			//可以将返回数据至发送方
			sendto(s, buffer, strlen(buffer), 0, (sockaddr*)&addr, sizeof(addr));
		}
	}

	closesocket(s);
}

int SendToClient(char * buffer,char* ip, int port)
{
	sockaddr_in addr = {0};
	int nLen  = sizeof(sockaddr_in);
	SOCKET s;

	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	addr.sin_family = AF_INET;
	addr.sin_port  = htons(port);
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sendto(s, buffer, strlen(buffer), 0, (sockaddr*)&addr, sizeof(addr));

	//while (true)
	//{
	//	cout << "Please input send data: " << endl;
	//	cin >> buffer;

	//	if ((strcmp(buffer, "quit") == 0) || (strcmp(buffer, "exit")) == 0)
	//	{
	//		cout << "process exit...." << endl;

	//		break;
	//	}
	//}
	return 0;
}