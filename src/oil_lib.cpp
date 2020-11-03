/* 
 * File:   oil.h
 * Author: Kenneth Bastian
 *
 */


#include "oil_lib.h"
/* Accepts size of char array to be created and return pointer to it */
char* alloc(size_t size)
{	char* ret;

	if ( (ret = (char*) calloc(size, sizeof(char))) == NULL )
	{
   		std::cout<<"Not enough memory.";
		exit(-1);
	}
	return ret;
}

/* Accepts size of char pointer array to be created and return pointer to it */
char** palloc(size_t size)
{
	char** ret;

	if ( (ret = (char**) calloc(size, sizeof(char*))) == NULL )
	{
   		std::cout<<"Not enough memory.";
		exit(-1);
	}
	return ret;
}

/*int** palloc_int(size_t size)
{
	int** ret;

	if ( (ret = (int**) calloc(size, sizeof(int*))) == NULL )
	{
   		std::cout<<"Not enough memory.";
		exit(-1);
	}
	return ret;
}*/
