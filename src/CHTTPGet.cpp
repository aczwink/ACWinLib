//Class Header
#include "CHTTPGet.h"
//Namespaces
using namespace SJCLib;
using namespace SJCWinLib;
//Definitions
#define HTTP_HEADER_BLANK '\r'
#define HTTP_PORT 80
#define HTTP_PREFIX "http://"
#define HTTP_PREFIXLENGTH 7
#define HTTP_PROTOVERSION "HTTP/1.1"
#define HTTP_PROTOVERSIONLENGTH 8
#define RECEIVEBUFFER_SIZE 1024

//Constructor
CHTTPGet::CHTTPGet()
{
	this->socket.Init();
}

//Private Functions
bool CHTTPGet::Receive()
{
	CString buffer, tmp;
	CStringStream stream;
	char receiveBuffer[RECEIVEBUFFER_SIZE];
	int32 bytesPlacedIntoBuffer;

	while((bytesPlacedIntoBuffer = this->socket.Receive(receiveBuffer, RECEIVEBUFFER_SIZE, 0)))
	{
		buffer.Append(receiveBuffer, bytesPlacedIntoBuffer);
	}
	stream.SetString(buffer);
	tmp = stream.GetString(HTTP_PROTOVERSIONLENGTH);
	if(tmp != HTTP_PROTOVERSION)
		return false;
	stream.GetByte(); //Space
	this->responseStatusCode = (uint16)stream.GetString(3).ToUInt64();
	stream.GetLine(); //Status Message
	
	while((tmp = stream.GetLine()) != HTTP_HEADER_BLANK) //Headers
	{
	}
	
	this->data = stream.GetRest();

	return true;
}

void CHTTPGet::SetHostname()
{
	int32 pos = this->URL.Find('/');
	
	if(pos == STRING_NOMATCH)
	{
		this->host = this->URL;
		this->URL = "/";
	}
	else
	{
		this->host = this->URL.SubString(0, pos);
		this->URL = this->URL.SubString(pos, this->URL.GetLength() - pos);
	}
}

//Public Functions
bool CHTTPGet::Execute()
{
	CString request;
	hostent *pHostEntities;
	
	pHostEntities = gethostbyname(this->host.GetC_Str());
	if(!pHostEntities)
		return false;
	for(uint32 i = 0; pHostEntities->h_addr_list[i]; i++)
		this->socket.Connect(*(uint32 *)pHostEntities->h_addr_list[i], HTTP_PORT);
	
	request = "GET " + this->URL + " " + HTTP_PROTOVERSION + "\nHost: " + this->host + "\nConnection: close\n\n";
	this->socket.Send(request);

	return this->Receive();
}

const CString &CHTTPGet::GetReceivedData() const
{
	return this->data;
}

bool CHTTPGet::SetURL(CString URL)
{
	int32 pos;

	pos = URL.Find(HTTP_PREFIX);
	if(pos == STRING_NOMATCH)
		this->URL = URL;
	else if(pos == 0)
		this->URL = URL.SubString(HTTP_PREFIXLENGTH, URL.GetLength() - HTTP_PREFIXLENGTH);
	else
		return false;
	this->SetHostname();
	
	return true;
}