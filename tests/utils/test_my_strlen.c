#include <criterion/criterion.h>
#include <stddef.h>

// Function to test
size_t my_strlen(char const *str);

/*  List of tests  */

Test(my_strlen, test_valid_string)
{
    char *str = "Testing my_strlen function";
    int result = my_strlen(str);

    cr_assert_eq(result, 26);
}

Test(my_strlen, test_empty_string)
{
    char *str = "";
    int result = my_strlen(str);

    cr_assert_eq(result, 0);
}

Test(my_strlen, test_null_string)
{
    char *str = NULL;
    int result = my_strlen(str);

    cr_assert_eq(result, 0);
}
