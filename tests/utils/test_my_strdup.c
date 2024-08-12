#include <criterion/criterion.h>

// Function to test
char *my_strdup(char const *str);

/*  List of tests  */

Test(my_strdup, basic_test) {
    char *input = "Hello, world!";
    char *result = my_strdup(input);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, input);
    free(result);
}

Test(my_strdup, null_input) {
    char *input = NULL;
    char *result = my_strdup(input);

    cr_assert_null(result);
}

Test(my_strdup, empty_string) {
    char *input = "";
    char *result = my_strdup(input);

    cr_assert_not_null(result);
    cr_assert_str_empty(result);
    free(result);
}
