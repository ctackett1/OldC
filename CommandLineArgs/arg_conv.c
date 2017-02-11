/** include necessary header files ONLY */
/*Author: Bobby Purcell
 * Desc: Self teaching C based on provided template,
 * exploring command line arguments
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /** define arg_list as an array of C strings */
    const char *arg_list[argc];
    int i;
    float x;

    /** print each argument and length */
    for (i = 0; i < argc; i++) {
        printf("%s %d\n", argv[i], strlen(argv[i]));
    }

    /** use malloc() to allocate sufficient space to hold all */
    /** command-line arguments */
    /** I spent over two hours online trying to find out the correct syntax to do this.
     * I was sadly unsuccessful and need this explained to me. -BP*/

    /** arg_list points to the command-line arguments in the */
    /** 	reversed order */
    int j = 0;
    for (i = argc; i >= 0; i--) {
        arg_list[j] = argv[i - 1];
        j++;
    }

    /** print the content of arg_list */
    for (i = 0; i < argc; i++) {
        printf("%s\n", arg_list[i]);
    }

    /** convert the 2nd argument the user provided into a float */
    /** 	and assign the value to x */
    x = atof(argv[1]);
    /** print x */
    printf("x= %f", x);
    return 0;
}
