#pragma once
#include <windows.h>
#include <list>
#include <sstream>
using namespace std;

class Pattern
{
	public:
		BYTE type;
		char title[100];
		int* data;
		int length;
		int findMatch(BYTE* inData);
};

class AddressLocator
{
public:
	typedef void _AddressFoundCallback(char* name, DWORD address, DWORD param);
	typedef void _ScanProgressCallback(DWORD readBytes, DWORD totalBytes, DWORD param);

	static void ClearPatterns();
	static void CreatePattern(char* title, char* pattern, BYTE type);
	static int GetPatternCount() { return patterns.size(); }
	static void LocateAddresses(HANDLE process, DWORD callbackProgressAddress, DWORD callbackFoundAddress, DWORD param);

private:
	static list<Pattern*> patterns;
	static void FindPatternMatch(HANDLE process, MEMORY_BASIC_INFORMATION meminfo, _AddressFoundCallback* foundCallback, DWORD param);

};
