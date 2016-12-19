#ifndef _HVDEVICEDLL_H_
#define _HVDEVICEDLL_H_

#include <stdio.h>
#include <time.h>
#include <tchar.h>

#ifndef _INC_WINDOWS
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif // _INC_WINDOWS

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

// Դ����������ͷ�ļ�
#include "tinyxml.h"
#include "HvCameraLinkOpt.h"
#include "HvCameraLink.h"

// �������ڲ�ͷ�ļ�
//#include "HvDeviceUtils.h"  //temp
#include "HvDevice.h"

#endif // _HVDEVICEDLL_H_
