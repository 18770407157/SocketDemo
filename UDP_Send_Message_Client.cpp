
/*

Socket�ͻ��˴���
�������������Ϣ
������IP��127.0.0.1
�������˿ڣ�8887
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
	SOCKET client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (client_socket == INVALID_SOCKET) {
		//���������socket��Ч�����������
		perror("socket error !\n");
		return 0;
	}

	/*
	������ַ��server_addr�������ö˿ں�IP
	*/
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	//Ҫ���ӵķ������˿ں� 8887
	server_addr.sin_port = htons(8887);
	//�󶨷������ĵ�ַ127.0.0.1
	InetPton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);

	printf("�����뷢�͸�����������Ϣ��\n");

	while (1)
	{

		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		
		// �Ӽ����ж�ȡ���뵽BUFFER��
		gets_s(buffer, BUFFER_SIZE);

		//�������ݸ�������
		if (sendto(client_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, sizeof(SOCKADDR)) == -1)
		{
			perror("������Ϣʧ��:\n");
			break;
		}


	}


	// �ر�socket 
	closesocket(client_socket);
	WSACleanup();
	return 0;

}