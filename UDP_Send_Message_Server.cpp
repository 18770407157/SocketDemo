
/*

Socket�������˴���
�������˿�8887
����Client���͵���Ϣ
*/

#include <tchar.h>
#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>   
#include <string.h>   
#include <Ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFFER_SIZE 2048
#define FILE_NAME_MAX_SIZE 512 

int main(int argc, char* argv[])
{
	/*
	��ʼ��WSA��ʹ�ó�����Ե���windows socket
	*/
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	/*
	�����������׽��֣�server_socket
	������UDP
	������Ƿ񴴽��ɹ�
	*/
	SOCKET server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (server_socket == INVALID_SOCKET) {
		//���������socket��Ч�����������
		perror("socket error !\n");
		return 0;
	}

	/*
	������ַ��server_addr�������ö˿ں�IP
	*/
	sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	//�˿ں� 8887
	server_addr.sin_port = htons(8887);
	//INADDR_ANY��ʾ����IP��ַ
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;


	//��socket���ַserver_addr��
	if (bind(server_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		perror("bind error !\n");
		return 0;
	}


	while (1)
	{
		// ����ͻ��˵�socket��ַ�ṹ
		sockaddr_in client_addr;
		int client_addr_length = sizeof(client_addr);

		// recv�����������ݵ�������buffer�� 
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		if (recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_length) == -1)
		{
			perror("������Ϣʧ��:\n");
			break;
		}

		char IP_BUFFER[256];
		memset(IP_BUFFER, 0, 256);
		InetNtop(AF_INET, &client_addr.sin_addr, IP_BUFFER, 256);
		printf("��%s��%d���յ���Ϣ:%s\n", IP_BUFFER, ntohs(client_addr.sin_port), buffer);

	}


	// �رշ�����socket 
	closesocket(server_socket);
	WSACleanup();
	return 0;

}