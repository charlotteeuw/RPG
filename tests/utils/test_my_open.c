#include <criterion/criterion.h>
#include <sys/stat.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

// Function to test
char *my_open(char const *filepath);

/*  List of tests  */

Test(my_open, test_valid_filepath)
{
    char *expected_content = "This is the file content.";
    char *filepath = "test_my_open.txt";
    int fd = open(filepath, O_CREAT | O_WRONLY, 0644);
    char *content = NULL;

    if (fd != -1) {
        write(fd, expected_content, strlen(expected_content));
        content = my_open(filepath);
        if (content != NULL) {
            cr_assert_str_eq(content, expected_content);
            free(content);
        }
        close(fd);
        remove(filepath);
    }
}

Test(my_open, test_invalid_filepath)
{
    char *filepath = "nonexistent_file.txt";
    char *content = my_open(filepath);

    cr_assert_null(content);
}
