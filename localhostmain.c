#include<stdio.h>
#include<winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main() {

	WSADATA wsa;
	printf("windows ag kutuphanesini baslatmayi deniyor bekleyiniz...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("baslatılırken bir hata olustu hata kodu : %d\n", WSAGetLastError());
		return 1;
	}

	printf("BASARILI\n");


	
	SOCKET SunucuSoketi;
	SunucuSoketi = socket(AF_INET, SOCK_STREAM, 0);

	printf("soket kontrolu..\n");

	if (SunucuSoketi == INVALID_SOCKET)
	{
		printf("soket oluşturulamadı hata kodu :%d", WSAGetLastError());
		WSACleanup();
		return 1;
	}


	printf("soket olusturuldu");



	//sunucu adresi ve boş portları kullanma
	struct sockaddr_in sunucuAdresi;
	sunucuAdresi.sin_family = AF_INET;
	sunucuAdresi.sin_addr.s_addr = INADDR_ANY;
	sunucuAdresi.sin_port = htons(1453);

	if (bind(SunucuSoketi, (struct sockaddr*)&sunucuAdresi, sizeof(sunucuAdresi)) == SOCKET_ERROR) {
		printf("HATA: Adres sokete baglanamadi (Bind hatasi)! Kod: %d\n", WSAGetLastError());
		closesocket(SunucuSoketi);
		WSACleanup();
		return 1;
	}
	printf("\nbasarili");
	

	if (listen(SunucuSoketi, 3) == SOCKET_ERROR) {
		printf("HATA: Dinleme moduna gecilemedi! Kod: %d\n", WSAGetLastError());
		closesocket(SunucuSoketi);
		WSACleanup();
		return 1;
	}
	printf("basarili sunucu 1453 portunda");


	printf("\n--- ADIM 5: Baglanti Kabul Ediliyor (Accept) ---\n");
	printf("Sunucu su an DONACAK ve Chrome gelene kadar bekleyecek...\n");

	SOCKET Gelensoketi;
	Gelensoketi = accept(SunucuSoketi, NULL, NULL);
	if (Gelensoketi == INVALID_SOCKET) {
		printf("HATA:iceri alinamadi! Kod: %d\n", WSAGetLastError());			closesocket(SunucuSoketi);
		WSACleanup();
		return 1;
	}


	printf("\n>>> giris algilandi<<<\n");

	char gelenIstek[4096];
	recv(Gelensoketi, gelenIstek, 4096, 0);
	printf("Tarayicidan gelen istek okundu/temizlendi.\n");
	

	char mesaj[] = "HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain; charset=utf-8\r\n"
		"Connection: close\r\n"
		"\r\n"
		"calisiyor.";

	send(Gelensoketi, mesaj, (int)strlen(mesaj), 0);
	printf("Cevap gonderildi.\n");

	
	Sleep(100);

	closesocket(Gelensoketi);
	closesocket(SunucuSoketi);
	WSACleanup();

	printf("\nIslem tamam");


	getchar();
	return 0;

}

