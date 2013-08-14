#include "stdafx.h"




long pPlayerDlgHandle = 0;

long getPlayerDlgHandle()
{
	return pPlayerDlgHandle;
}
void setPlayDlgHandle(long handlePointer)
{
	pPlayerDlgHandle = handlePointer;
}
