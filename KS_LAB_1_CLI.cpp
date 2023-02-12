﻿#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
#include <winsock2.h>
#include <iostream>
using namespace std;

int main() {

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1280);
	//т.к. клиент и сервер на одном компьютере,
	// пишем адрес 127.0.0.1
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	connect(s, (struct sockaddr*)&peer, sizeof(peer));

	char buf[255], b[255];
	cout << "Enter the string, please" << endl;
	cin.getline(buf, 100, '\n');

	send(s, buf, sizeof(buf), 0);
	if (recv(s, b, sizeof(b), 0) != 0) {
		/*b[strlen(b)] = '\0';*/ //Удаление ненужных символов
						 // в конце строки	
		cout << b << endl;
	}

	closesocket(s);

	WSACleanup();

	return 0;
}
