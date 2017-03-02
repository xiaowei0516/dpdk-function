#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
rte_strsplit(char *string, int stringlen,  char **tokens, int maxtokens, char delim)
{
	int i, tok = 0;
	int tokstart = 1; /* first token is right at start of string */

	if (string == NULL || tokens == NULL)
		goto einval_error;

	for (i = 0; i < stringlen; i++) {
		if (string[i] == '\0' || tok >= maxtokens)
			break;
		if (tokstart) {
			tokstart = 0;
			tokens[tok++] = &string[i];
		}
		if (string[i] == delim) {
			string[i] = '\0';
			tokstart = 1;
		}
	}
	return tok;

einval_error:
	errno = EINVAL;
	return -1;
}


int main(){
    char buf[100] = "012 123 234 456 789";
    char *arr[5];
    char delim = ' ';
    int i=0;
    rte_strsplit(buf, sizeof(buf),  arr,  5, delim);
    for(; i<5; i++){
       printf("%s\n", arr[i]);
    }
}
