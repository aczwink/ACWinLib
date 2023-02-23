#pragma once
/*
Sources:
http://de.wikipedia.org/wiki/HTTP-Statuscode
http://en.wikipedia.org/wiki/HTTP_header
*/
//Local
#include "CSocket.h"

namespace SJCWinLib
{
	class SJCWINLIB_API CHTTPGet
	{
	private:
		//Variables
		CSocket socket;
		uint16 responseStatusCode;
		SJCLib::CString URL;
		SJCLib::CString host;
		SJCLib::CString data;
		//Functions
		bool Receive();
		void SetHostname();
	public:
		//Constructor
		CHTTPGet();
		//Functions
		bool Execute();
		const SJCLib::CString &GetReceivedData() const;
		bool SetURL(SJCLib::CString URL);
	};
}