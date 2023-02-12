#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
#include <iostream>
#include <winsock2.h>

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));

	int r = listen(s, 5);

	//SOCKET accept(SOCKET s, struct sockaddr FAR * addr, int FAR * addrlen);
	SOCKET s2;
	while (true) {
		char buf[255], res[100], b[255], * Res;
		//структура определяет удаленный адрес,
		//с которым  соединяется сокет
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		s2 = accept(s, (struct sockaddr*)&remote_addr, &size);


		while (recv(s2, b, sizeof(b), 0) != 0) {

			int i = 0;
			for (int j = 0; j <= strlen(b); j++)
			{
				if (((b[j] == ' ') && (b[j + 1] == ' ')) || ((b[j] == ' ') && (i == 0))) continue;
				else
				{
					res[i] = b[j];
					i++;
				}
			}
			char Res[100];
			//Res = new char[strlen(res) + 1];
			strcpy(Res, res);
			Res[strlen(res)] = '\0';


			//Посылает данные на соединенный сокет
			send(s2, Res, strlen(Res) + 1, 0);
		}
	}

	closesocket(s2);
	WSACleanup();

}
