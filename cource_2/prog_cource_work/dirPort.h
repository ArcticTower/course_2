#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable: 4700)

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct mFileName
{
	wchar_t name[FILENAME_MAX];
	struct mFileName* next;

}mfname;


int dirPort(const wchar_t* const ford, mfname** top)
{
	WIN32_FIND_DATA fData;
	HANDLE hfile;
	wchar_t t_ford[FILENAME_MAX];
	wchar_t another_ford[FILENAME_MAX];
	mfname* curret;
	int res;

	if (swprintf(t_ford, wcslen(ford) + wcslen(L"\\*.*") + 1, L"%ls\\*.*", ford) < 0) { return 2; }
	hfile = FindFirstFileW(t_ford, &fData);
	if (hfile == INVALID_HANDLE_VALUE)
	{
		//printf("Invalid File Handle. Get Last Error reports %lu\n", GetLastError());//err
		return 1;
	}

	do
	{
		if (!(wcscmp((const unsigned short*)fData.cFileName, L".")) || !(wcscmp((const unsigned short*)fData.cFileName, L".."))) { continue; }
		if ((fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))//?
		{
			if (swprintf(another_ford, wcslen(ford) + wcslen(fData.cFileName) + wcslen(L"\\") + 1, L"%ls\\%ls", ford, fData.cFileName) < 0) { return 2; }
			res = dirPort(another_ford, top);
			if (res != 0) { return res; }
			continue;

		}

		curret = malloc(sizeof(mfname));
		if(curret==NULL)
		{
			return 3;
		}
		if (swprintf(curret->name, wcslen(fData.cFileName) + wcslen(t_ford) + wcslen(L"\\") + 1, L"%ls\\%ls", ford, fData.cFileName) < 0) { return 2; }
		curret->next = *top;
		*top = curret;


	} while (FindNextFile(hfile, &fData));
	if (FindClose(hfile) == 0) { return 4; }
	return 0;
}
//0 - ok
//1 - invalid file handle
//2 - swprint f
//3 - null pointer
//4 - close handle