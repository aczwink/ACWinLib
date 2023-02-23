//Class Header
#include "CSocket.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;

//Public Functions
int32 CSocket::Connect(uint32 binaryIP, uint16 port) const
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.S_un.S_addr = binaryIP;

	return connect(this->socket, (const sockaddr *)&sa, sizeof(sa));
}

int32 CSocket::Send(const CString &refData) const
{
	return this->Send(refData.GetC_Str(), refData.GetLength());
}

/*
//Global
#include <map>
//Namespaces
using namespace std;
using namespace SJCLIB_NAMESPACE_INTERN;
using namespace SJCLib;
using namespace SJCLibString;
using namespace SJCLibWindows;

//Definitions
#define BUFFER_SIZE 512
#define SOCKET_MESSAGE WM_USER + 1

//Global Vars
map<SOCKET, CSocketMessageWindow *> g_SocketWindows;

//CSocketMessageWindow
void CSocketMessageWindow::OnUserMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == SOCKET_MESSAGE)
	{
		if(this->pSocket)
		{
			this->callbackPointer(this->pSocket, WSAGETSELECTEVENT(lParam), WSAGETSELECTERROR(lParam));
		}
		else
		{
			CSocket socket(wParam);

			this->callbackPointer(&socket, WSAGETSELECTEVENT(lParam), WSAGETSELECTERROR(lParam));
		}
	}
}

int CSocket::AsyncSelect(CApplication *pApp, void (*callbackFunction)(CSocket *pSocket, uint32 eventCode, uint32 errorCode), int32 desiredEvents)
{
	this->messageWindow = new SJCLIB_NAMESPACE_INTERN::CSocketMessageWindow;
	//this->messageWindow->Create(pApp->className, "", 0, 0, 0, 0, 0, pApp->pModule);
	this->messageWindow->pSocket = this;
	this->messageWindow->callbackPointer = callbackFunction;
	g_SocketWindows[this->socket] = this->messageWindow;
	return WSAAsyncSelect(this->socket, this->messageWindow->hWnd, SOCKET_MESSAGE, desiredEvents);
}

int CSocket::Bind(uint16 port)
{
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.S_un.S_addr = INADDR_ANY;

	return bind(this->socket, (const sockaddr *)&sa, sizeof(sa));
}

int CSocket::Connect(CString ipAddress, uint16 port)
{
	return this->Connect(inet_addr(ipAddress.c_str()), port);
}

CArray<CString> CSocket::GetInternalIPAddresses()
{
	CArray<CString> result;
	char hostName[255];

	memzero(&hostName, sizeof(hostName));

	if(gethostname(hostName, sizeof(hostName)) != SOCKET_ERROR)
	{
		SOCKADDR_IN socketAddress;
		hostent *pHost = NULL;

		pHost = gethostbyname(hostName);

		if(pHost)
		{
			for(int i = 0; pHost->h_addr_list[i] != NULL; i++)
			{
				memcpy(&socketAddress.sin_addr, pHost->h_addr_list[i], pHost->h_length);
				result.Push(inet_ntoa(socketAddress.sin_addr));
			}
		}
	}

	return result;
}

const int CSocket::GetLastError()
{
	return WSAGetLastError();
}
*/
