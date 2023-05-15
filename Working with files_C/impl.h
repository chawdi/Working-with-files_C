#ifndef IMPL_H_
#define IMPL_H_

#define FN_LEN 256
#define ARG_ERR  1
#define READ_ERR 2
#define FILE_ERR 3
#define MEM_ERR  4
#define SUCCESS  0

#include <stdlib.h>
#include <stdio.h>

int get_f_name_stdin(char* filename, size_t const capacity);
int get_f_name_args(int cmd_argc,char* cmd_argv[],char* in_name,char* out_name,size_t const capacity);
void lab11_solve(char const* in_name, char const* out_name);
void die(char const* msg, int ecode);
int get_int(FILE* stream, int* ret);

#endif
