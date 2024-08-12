#include <criterion/criterion.h>

// Function to test
char *my_strcpy(char *restrict dst, char const *restrict src);

/*  List of tests  */

Test(my_strcpy, test_valid_src_and_dst)
{
    char dst[5] = "";
    char *src = "Test";
    char *cpy = my_strcpy(dst, src);

    cr_assert_str_eq(dst, src);
    cr_assert_str_eq(cpy, src);
}

Test(my_strcpy, test_invalid_dst)
{
    char *src = "Test";
    char *cpy = my_strcpy(NULL, src);

    cr_assert_null(cpy);
}

Test(my_strcpy, test_invalid_src)
{
    char *dst = "Test";
    char *cpy = my_strcpy(dst, NULL);

    cr_assert_null(cpy);
}
