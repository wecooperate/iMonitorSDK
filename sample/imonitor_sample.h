//******************************************************************************
/*++
	FileName:		imonitor_sample.h
	Description:

--*/
//******************************************************************************
#ifndef __imonitor_sample_0E0533C1_62F5_4052_94C4_D07EF8A9AD82__
#define __imonitor_sample_0E0533C1_62F5_4052_94C4_D07EF8A9AD82__
//******************************************************************************
#include <iMonitorSDK.h>
#include <iMonitorProtocol.h>
#include <stdio.h>
//******************************************************************************
inline void WaitForExit(const char* message)
{
	printf("%s\n", message);

	system("PAUSE");
}
//******************************************************************************
#endif
