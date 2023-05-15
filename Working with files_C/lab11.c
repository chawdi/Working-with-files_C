#include "impl.h"

int main(int argc, char* argv[])
{
	char in_name[FN_LEN];
	char out_name[FN_LEN];
	if(argc > 1) {
		if(!get_f_name_args(argc, argv, in_name, out_name, FN_LEN)) {
			//printf("%s\n%s\n", in_name,out_name);
			lab11_solve(in_name, out_name);
		} else {
			die("Invalid filename specified.", ARG_ERR);
		}
	} else {
		printf("Enter input filename: ");
		if(get_f_name_stdin(in_name, FN_LEN))
			die("Filename is incorrect.", READ_ERR);

		printf("Enter output filename: ");
		if(get_f_name_stdin(out_name, FN_LEN))
			die("Filename is incorrect.", READ_ERR);

		lab11_solve(in_name, out_name);
	}
	puts("Done.");
	return 0;
}
