#include "COMPort.h"


COMPort::COMPort(LPCTSTR Name)
{

	hSerial = ::CreateFile(Name,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hSerial==INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			throw "Serial port does not exist";
		throw "Some other error occurred";
	}
}

void COMPort::SetSerialParams(DWORD BaudRate, BYTE ByteSize, BYTE StopBits, BYTE Parity)
{
	dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
		throw "Getting state error";
	dcbSerialParams.BaudRate = BaudRate;
	dcbSerialParams.ByteSize = ByteSize;
	dcbSerialParams.StopBits = StopBits;
	dcbSerialParams.Parity = Parity;
	if(!SetCommState(hSerial, &dcbSerialParams))
		throw "Error setting serial port state";
}

std::string COMPort::Read()
{
	DWORD iSize = 0;
	std::string string;
    char sReceivedChar;
	// —читываем строку(посимвольно)
	do
	{
		ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);
		string += sReceivedChar;
	} while (sReceivedChar != '\0');
	return string;
}

BOOL COMPort::Write(const char* Data, DWORD Size)
{
    return  WriteFile (hSerial,Data,Size,0,NULL);
}
