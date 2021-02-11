#pragma once
#include <string>
#include <wtypes.h>
class COMPort
{
private:
	HANDLE hSerial;
	DCB dcbSerialParams = {0};
public:
	COMPort(LPCTSTR Name);
	void SetSerialParams(DWORD BlaudRate, BYTE ByteSize, BYTE StopBits, BYTE Parity);
	std::string Read();
	BOOL Write(const char* Data, DWORD Size);
};

