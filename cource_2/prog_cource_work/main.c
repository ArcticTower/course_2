#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/stat.h>
#include <string.h>
#include <io.h>
#include <errno.h>
#include "getsign.h"
#include "scan.h"
#include "dirPort.h"

//C:\Users\OGm0N\CLionProjects\MakeSign\cmake-build-debug\sign.sig
//C:\Users\OGm0N\Documents\tools\ollydbg
int main()
{
	FILE* fsign;
	FILE* curretFile;
	wchar_t path[FILENAME_MAX];
	
	char c;
	int res;
	int cres;
	mfname* nameNode;
	signature* signa;
	DWORD atribs;
	

	unsigned long mov;
	unsigned long len;
	//unsigned char* c_sign[1000];

	do
	{
		if (printf("Enter path to the sign file\n") < 0) { return 1; }
		do
		{
			cres = wscanf(L"%[^\n]ls", path);
			while ((c = getchar()) != EOF && c != '\n');
		} while (cres != 1);
		
		//get sign
		fsign = _wfopen(path, L"rb");
		if (fsign == NULL) { return 2; }
		res = getSign(fsign, &mov, &len, &signa);//TODO: обработка ответа от getSign
		switch (res)
		{
		case  0:
			break;
		case 1:
			if (printf("\nERROR: Memory allocate\n") < 0) { return 1; }
			break;
		case 2:
			if (printf("\nERROR: Signature file read\n") < 0) { return 1; }
			break;
		case 3:
			if (printf("\nERROR: Violation of logical conditions\n") < 0) { return 1; }
			break;
		default:
			if (printf("\nERROR: Unsuspected error\n") < 0) { return 1; }
			break;
		}
		//*c_sign = signa->is;
		
	} while (res != 0);



	//чтение пути и получение атрибутов
	if (printf("Enter path to the file or directory\n") < 0) { return 1; }
	do
	{
		do
		{
			cres = wscanf(L"%[^\n]ls", path);
			while ((c = getchar()) != EOF && c != '\n');
		} while (cres != 1);
		
		atribs = GetFileAttributesW(path);
		if (printf("\nERROR: GetFileAttributes. Get Last Error reports %lu\n", GetLastError()) < 0) {//err
			return 1;
		}
	} while (atribs == INVALID_FILE_ATTRIBUTES);

	//ветвление на path и file
	if(!(atribs & FILE_ATTRIBUTE_DIRECTORY))//change to 16
	{
		nameNode = malloc(sizeof(mfname));
		if(nameNode==NULL)
		{
			return 3;
		}
		if (wcscpy(nameNode->name, path) != nameNode->name) { return 5; }//change wcscpy to swprint
		nameNode->next = NULL;
	}else
	{
		res = dirPort(path, &nameNode);
		switch (res)
		{
		case 0:
			break;
		case 1:
			if (printf("ERROR: Invalid File Handle. Get Last Error reports %lu\n", GetLastError()) < 0) { return 1; }
			break;
		case 2:
			if (printf("ERROR: Fragmentation error\n") < 0) { return 1; }
			break;
		case 3:
			if (printf("ERROR: Memory allocate error\n") < 0) { return 1; }
			break;
		case 4:
			if (printf("ERROR: Close handle. Get Last Error reports %lu\n", GetLastError()) < 0) { return 1; }
			break;
		default:
			if (printf("ERROR: Unsuspected error\n") < 0) { return 1; }
			break;
		}
	}

	//обработка структуры имён
	while(nameNode!=NULL)
	{
		curretFile = _wfopen(nameNode->name, L"rb");
		if (curretFile == NULL) {return 2; }
		res = signScan(curretFile, mov, len, &signa);

		//обработка signScan
		switch (res)
		{
		case 0:
			if (wprintf(L"\"%ls\" sign detected\n ", nameNode->name) < 0) { return 1; }
			break;
		case 1:
			if (wprintf(L"\"%ls\" clean\n", nameNode->name)) { return 1; }
			break;
		case 2:
			if (wprintf(L"\"%ls\" file format error (not executable)\n", nameNode->name) < 0) { return 1; }
			break;
		case 3:
			if (printf("\nERROR: File read error\n") < 0) { return 1; }
			break;
		case 4:
			if (printf("\nERROR: Fragmentation error .\n") < 0) { return 1; }
			break;
		case 5:
			if (printf("\nERROR: Violation of logical conditions\n") < 0) { return 1; }
			break;
		case 6:
			if (printf("\nERROR: Memory allocate error.\n") < 0) { return 1; }
			break;
		default:
			if (printf("\nERROR: Unsuspected error\n") < 0) { return 1; }
			return 4;
		}
		
		fclose(curretFile);
		nameNode = nameNode->next;
		
	}
	return 0;
}

//0 - ok
//1 - print error
//2 - file pointer error
//3 - struct pointer error
//4 - scan error
//5 - wr in str err
