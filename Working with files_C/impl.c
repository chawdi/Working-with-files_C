#include <string.h>
#include "impl.h"

inline int get_f_name_stdin(char* filename, size_t const capacity)
{
	if (fgets(filename, capacity, stdin) == NULL)
		return READ_ERR;

	char* end;
	if ((end = strchr(filename, '\n')) != NULL)
		*end = '\0';

	return SUCCESS;
}

int get_f_name_args(int cmd_argc,
		  char* cmd_argv[],
                  char* in_name,
                  char* out_name,
		  size_t const capacity)
{
	size_t fn_size = 0;
        strcpy(in_name, "");
        strcpy(out_name, "");

	char* current = NULL;
	for(int i = 1; i < cmd_argc; i++) {
		if(!strcmp(cmd_argv[i], "-f")) {
                        current = in_name;
		} else if(!strcmp(cmd_argv[i], "-o")) {
                        current = out_name;
		} else if(current) {
			if((fn_size += strlen(cmd_argv[i])) < capacity)
				strcat(current, cmd_argv[i]);
			else
				goto err;
			
			if(i != (cmd_argc - 1)
			   && strcmp(cmd_argv[i+1], "-f")
			   && strcmp(cmd_argv[i+1], "-o")) {
				if(++fn_size < capacity)
					strcat(current, " ");
				else
					goto err;
			}
		}
	}
        if(!strcmp(in_name, "") || !strcmp(out_name, ""))
		goto err;
	
	return SUCCESS;
err:
	return ARG_ERR;
}

void lab11_solve(char const* in_name, char const* out_name)
{
	if(!strcmp(in_name, out_name))
		die("Filenames are the same. Aborting.", FILE_ERR);
		
	FILE* in, *out;
	if((in = fopen(in_name, "r")) == NULL
	    || (out = fopen(out_name, "w")) == NULL)
		die("Couldn't open the file(s).", FILE_ERR);
	int lines, cols;
	if(get_int(in, &lines) || get_int(in, &cols))
		die("Invalid file format", FILE_ERR);
	
	int* tmp_line;
	if((tmp_line = malloc(cols * sizeof(int))) == NULL)
		die("Low on memory.", MEM_ERR);
	
	int copy;
	for(int i = 0; i < lines; i++) {
		copy = 1;
		for(int j = 0; j < cols; j++) {
			if(get_int(in, tmp_line + j))
				die("Invalid matrix format", FILE_ERR);
			if(*(tmp_line + j) < 0)
				copy = 0;
		}
		if(copy) {
			for(int j = 0; j < cols; j++) {
				fprintf(out, (j != cols - 1) ? "%d " : "%d",
					*(tmp_line + j));
			}
			if(i != lines - 1)
				fprintf(out, "\n");
		}
	}
	fclose(in);
	fclose(out);
}

inline void die(char const* msg, int ecode)
{
	FILE *out = ecode ? stderr : stdout;
	if (msg)
		fprintf(out, "%s\n", msg);
	exit(ecode);
}

inline int get_int(FILE* stream, int* ret)
{
	if(ret && stream && fscanf(stream, "%d", ret) == 1)
		return SUCCESS;
	else
		return READ_ERR;
}
