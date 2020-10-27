#define MAX_MOV LONG_MAX
#define MIN_MOV 0
#define MAX_LEN 1000
#define MIN_LEN 1


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int signScan(FILE* file, const unsigned long mov, const unsigned long sz_sign, signature** sign)
{
	
	unsigned char* t_sign;
	size_t i;
	char mz[3];

	//MZ check
	if ((fseek(file, 0, SEEK_SET)) != 0) { return 3; }
	if (fread(mz, sizeof(mz), 1, file) != 1) { return 4; }
	mz[2] = '\0';
	if (strcmp("MZ\0", mz) != 0) { return 2; }
	
	//check MOV
	if (mov > MAX_MOV || mov < MIN_MOV) { return 5; }

	//check len
	if (sz_sign > MAX_LEN || sz_sign < MIN_LEN) { return 5; }

	//allocate mem for this sign
	t_sign = (unsigned char*)malloc(sz_sign);
	if (t_sign == NULL) { return 6; }

	//go to sign location
	if ((fseek(file, mov, SEEK_SET)) != 0) { return 3; }

	//take current sign
	if (fread(t_sign, sizeof(byte), sz_sign, file) != sz_sign){return 4;}

	//сравнение
	for (i = 0; i < sz_sign; i++)
	{
		if (((*sign)->is[i] ^ t_sign[i]) != 0)
		{
			return 1;
		}
	}
	return 0;
}
//1 - не совпали
//0 - совпали
//2 - mz err
//3 - seek ошибка
//4 - fread ошибка
//5 - невозм смещение
//6 - allocate