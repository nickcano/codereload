#include "AddressLocator.h"

#define READABLE_MEM (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE | PAGE_EXECUTE_READ)

list<Pattern*> AddressLocator::patterns;

int Pattern::findMatch(BYTE* inData)
{
	for (int p = 0; p < this->length; p++)
	{
		BYTE compareType = (this->data[p] & 0xFF00) / 0x100;
		BYTE compareValue = this->data[p] & 0xFF;

		bool valid = false;

		if (compareType == 0xFF)
			valid = true;
		else if (compareType == 0xFE && inData[p] < compareValue)
			valid = true;
		else if (compareType == 0xFD && inData[p] > compareValue)
			valid = true;
		else if (compareType == 0x00 && inData[p] == compareValue)
			valid = true;

		if (!valid)
			return -1;
		
		if (p == this->length - 1)
		{
			int offset = 0;
			for (int sl = 0; sl < this->length; sl++)
			{
				if (this->data[sl] == 0xFF00)
				{
					offset = sl;
					break;
				}
			}
			return offset;
		}
	}

	return -1;
}

void AddressLocator::ClearPatterns()
{
	list<Pattern*>::iterator p;
	for (p = patterns.begin(); p != patterns.end(); p++)
	{
		delete [] (*p)->data;
		delete [] (*p);
	}
	patterns.clear();
}

void AddressLocator::CreatePattern(char* title, char* pattern, BYTE type)
{
	Pattern* p = new Pattern;
	strcpy(p->title, title);
	p->type = type;

	string patternString = string(pattern);
	int end = patternString.find(",");
	list<int> tempPattern;

	while (end != string::npos)
	{
		string value = patternString.substr(0, end).append("\0");
		patternString = patternString.substr(end + 1);

		int intvalue = strtol(value.c_str(), NULL, 16);
		tempPattern.push_back(intvalue);

		end = patternString.find(",");
	}

	int intvalue = strtol(patternString.c_str(), NULL, 16);
	tempPattern.push_back(intvalue);

	p->length = tempPattern.size();
	p->data = new int[p->length];

	int patternValue, patternIndex = 0;
	list<int>::iterator patternit;
	for (patternit = tempPattern.begin(); patternit != tempPattern.end(); patternit++)
	{
		patternValue = (*patternit);
		p->data[patternIndex] = patternValue;
		patternIndex++;
	}

	patterns.push_back(p);
}

void AddressLocator::LocateAddresses(HANDLE process, DWORD callbackProgressAddress, DWORD callbackFoundAddress, DWORD param)
{
	MEMORY_BASIC_INFORMATION meminfo;
    unsigned char *addr = 0;
	DWORD totalBytes = 0;
	list<MEMORY_BASIC_INFORMATION> memoryBlocks;

    while (true)
    {
        if (!VirtualQueryEx(process, addr, &meminfo, sizeof(meminfo)))
            break;
		
		bool Commited = meminfo.State & MEM_COMMIT;
		bool Readable = meminfo.Protect & READABLE_MEM;
		bool Guarded = meminfo.Protect & PAGE_GUARD;


		if (Commited && Readable && !Guarded)
		{
			totalBytes += (DWORD)meminfo.RegionSize;
			memoryBlocks.push_back(meminfo);
		}

        addr = (unsigned char*)meminfo.BaseAddress + meminfo.RegionSize;
    }

	_ScanProgressCallback* progressCallback = (_ScanProgressCallback*)callbackProgressAddress;

	DWORD readBytes = 0;
	list<MEMORY_BASIC_INFORMATION>::iterator b;
	for (b = memoryBlocks.begin(); b != memoryBlocks.end(); b++)
	{
		FindPatternMatch(process, (*b), (_AddressFoundCallback*)callbackFoundAddress, param);
		readBytes += (DWORD)(*b).RegionSize;
		progressCallback(readBytes, totalBytes, param);
	}

	progressCallback(0, 0, param);
}

void AddressLocator::FindPatternMatch(HANDLE process, MEMORY_BASIC_INFORMATION meminfo, _AddressFoundCallback* foundCallback, DWORD param)
{

	#define size (1024)
	static BYTE chunk[size];
	DWORD bytesRead = 0;

	while (bytesRead < meminfo.RegionSize)
	{
		DWORD read;
		DWORD readSize = ((DWORD)meminfo.RegionSize < size) ? meminfo.RegionSize : size;

		if (ReadProcessMemory(process, meminfo.BaseAddress, &chunk, readSize, &read))
		{
			if (readSize != read)
			{
				break;
				//throw std::exception("Full size not read");
			}
			else
			{
				Pattern* pattern;
				list<Pattern*>::iterator p;
				for (p = patterns.begin(); p != patterns.end(); p++)
				{
					if (!(*p)) break;

					pattern = (*p);

					for (int r = 0; r < ((int)readSize - pattern->length); r++)
					{
						BYTE* data = chunk + r;
						int match = pattern->findMatch(data);

						if (match >= 0)
						{
							DWORD matchLocation = (DWORD)meminfo.BaseAddress + r + match;
							DWORD matchedValue = matchLocation; 
							
							if (pattern->type == 1)
								memcpy(&matchedValue, &data[match], 4);

							foundCallback(pattern->title, matchedValue, param);
						}
					}
				}

				bytesRead += (readSize - 128);
				meminfo.BaseAddress = (PVOID)((DWORD)meminfo.BaseAddress + (readSize - 128));
			}
		}
		else
		{
			break;
			//throw std::exception("ReadProcessMemory() Failed");
		}
	}
}
