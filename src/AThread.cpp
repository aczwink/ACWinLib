//Class Header
#include "AThread.h"
//Namespaces
using namespace SJCWinLib;

//Internal
uint32 __stdcall SJCLibIntern::ThreadProc(void *pThreadParameter)
{
	return ((AThread *)pThreadParameter)->Procedure();
}

//Public Functions
void AThread::Create(bool createSuspended)
{
	this->hThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)SJCLibIntern::ThreadProc, this, (createSuspended ? CREATE_SUSPENDED : 0), NULL);
}