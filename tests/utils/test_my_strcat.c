#include <criterion/criterion.h>

// Function to test
char *my_strcat(char *restrict dst, char const *restrict src);

/*  List of tests  */

Test(my_strcat, concatenate_strings) {
    char dst[20] = "Hello, ";
    char *result = my_strcat(dst, "world!");

    cr_assert_str_eq(result, "Hello, world!", "Concatenate strings test failed");
}

Test(my_strcat, empty_source_string) {
    char dst[20] = "Hello, ";
    char *result = my_strcat(dst, "");

    cr_assert_str_eq(result, "Hello, ", "Empty source string test failed");
}

Test(my_strcat, empty_destination_string) {
    char dst[20] = "";
    char *result = my_strcat(dst, "world!");

    cr_assert_str_eq(result, "world!", "Empty destination string test failed");
}

Test(my_strcat, null_destination_string) {
    char *dst = NULL;
    char *result = my_strcat(dst, "world!");

    cr_assert_null(result, "Null destination string test failed");
}

Test(my_strcat, null_source_string) {
    char dst[20] = "Hello, ";
    char *result = my_strcat(dst, NULL);

    cr_assert_null(result, "Null source string test failed");
}
