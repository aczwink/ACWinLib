//Main Header
#include "SJCWinLib.h"
//Global
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
//Local
#include "__CWindows.h"
//Namespaces
using namespace std;
using namespace SJCLib;
using namespace SJCLibIntern;

//Intern
namespace SJCLibIntern
{
	void ReadDirectory(const CWString &refPath, const CWString &refFilter, CArray<CWString> &refResult, bool includeSubDirectories)
	{
		HANDLE fHandle;
		WIN32_FIND_DATAW wfd;

		fHandle = FindFirstFileW((refPath + refFilter).GetC_Str(), &wfd);
		if((CWString)wfd.cFileName != L'.') //. is unimportant
		{
			refResult.Push(refPath + wfd.cFileName);
		}

		if(FindNextFileW(fHandle, &wfd))
		{
			if((CWString)wfd.cFileName != L"..") //.. is also unimportant
			{
				refResult.Push(refPath + wfd.cFileName);
			}
			
			while(FindNextFileW(fHandle, &wfd))
			{
				if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if(includeSubDirectories)
						ReadDirectory((refPath + wfd.cFileName + L'\\').GetC_Str(), refFilter, refResult, includeSubDirectories);
				}
				else
				{
					refResult.Push(refPath + wfd.cFileName);
				}
			}
		}
		FindClose(fHandle);
	}
	
	bool URLIsUnreserved(byte b)
	{
		switch(b)
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
		case '-': case '.': case '_': case '~':
			return true;
		}
		return false;
	}
}

//Namespace Functions
void SJCWinLib::AllocateConsole()
{
	int consoleHandle;
	long stdHandle;
	FILE *stream;
	
	AllocConsole();
	
	stdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
	stream = _fdopen(consoleHandle, "w");
	*stdout = *stream;
	setvbuf(stdout, NULL, _IONBF, 0);
	
	stdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
	stream = _fdopen(consoleHandle, "r");
	*stdin = *stream;
	setvbuf(stdin, NULL, _IONBF, 0);
	
	stdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	consoleHandle = _open_osfhandle(stdHandle, _O_TEXT);
	stream = _fdopen(consoleHandle, "w");
	*stderr = *stream;
	setvbuf(stderr, NULL, _IONBF, 0);
	
	ios::sync_with_stdio();
}

bool SJCWinLib::Initialize(bool winsock)
{
	if(winsock)
		if(!CWindows::InitWinSock())
			return false;

	return true;
}

CArray<CWString> SJCWinLib::ListFiles(CWString path, const CWString &refFilter, bool includeSubDirectories)
{
	CArray<CWString> files;
	
	if(!path.GetLength())
		return files;
	
	if(path[path.GetLength()-1] != L'\\')
		path += L'\\';
	
	SJCLibIntern::ReadDirectory(path, refFilter, files, includeSubDirectories);
	
	for(uint32 i = 0; i < files.GetNoOfElements(); i++)
	{
		files[i] = files[i].SubString(path.GetLength(), files[i].GetLength()-path.GetLength());
	}
	
	return files;
}

CString SJCWinLib::URLEncode(CString url)
{
	CString result;
	byte b;
	
	repeat(url.GetLength(), i)
	{
		b = url[i];
		if(URLIsUnreserved(b))
		{
			result += b;
		}
		else
		{
			result += '%';
			result += CString((uint32)b, NS_HEX, false, 2);
		}
	}
	return result;
}