#pragma once

#include <fstream>
#include <windows.h>

class FileReader
{
public:
	FileReader(char* fileName);
	~FileReader(void);
	bool openFile();
	bool initBuffer();
	int read();
	char* getData();
	void resetFile();
	void closeFile();
	void setMaxBufferSize(int maxBufferSize);
	int getMaxBufferSize();
	int getCurrentBufferSize();
	int getHowManyParts();
	DWORD getLastError();
	__int64 getSize();

private:
	FILE* file;
	DWORD lastError;
	HANDLE hFile;
	char* fileName;
	static int  MAX_BUFFER_SIZE;
	int currentBufferSize;
	char* fileBuffer;
	int howManyParts;
	__int64 size;
	__int64 GetFileSizeWA();
};