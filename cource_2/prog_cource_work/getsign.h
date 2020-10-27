#define MAX_MOV LONG_MAX
#define MIN_MOV 0
#define MAX_LEN 1000
#define MIN_LEN 1

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

typedef struct signature{
	byte is[1000];
}signature;



int getSign(FILE* const file, unsigned long* t_mov, unsigned long* t_len , signature** signa)
{
	unsigned long mov;
	unsigned long len;
	char prefix[5];
	

	//check if filetype == sign
	if (fread(&prefix, sizeof(prefix), 1, file) != 1) { return 2; }
	prefix[4]='\0';
	if (strcmp("SIGN\0", prefix) != 0) { return 3; }

	//read mov
	if (fread(&mov, sizeof(mov), 1, file) != 1) { return 2; }

	//check MOV
	if (mov > MAX_MOV || mov < MIN_MOV) { return 3; }
	
	//read len
	if (fread(&len, sizeof(len), 1, file) != 1) { return 2; }

	//check len
	if (len > MAX_LEN || len < MIN_LEN) { return 3; }

	//allocate memory for sign
	signature* sign = malloc(sizeof(signature));
	if (sign == NULL) { return 1; }
	
	//C6029 check см ms docs
	if (sizeof(sign->is)<len) { return 3; }
		
	//read sign
	if (fread(&sign->is, sizeof(byte), len, file) != len) { return 2; }
	
	//set value
	*t_mov = mov;
	*t_len = len;
	*signa = sign;
	
	return 0;
}
//SIGN, смещение, длина сигны, сигна

//0 - ok
//1 - cant make sign
//2 - fread error
//3 - ошибка логических условий