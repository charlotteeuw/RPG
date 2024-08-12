#include <criterion/criterion.h>

// Function to test
char *my_itoa(int nbr);

/* List of tests */

Test(my_itoa, positive_number)
{
    int number = 12345;
    char *result = my_itoa(number);

    cr_assert_str_eq(result, "12345");
    free(result);
}

Test(my_itoa, negative_number)
{
    int number = -9876;
    char *result = my_itoa(number);

    cr_assert_str_eq(result, "-9876");
    free(result);
}

Test(my_itoa, zero)
{
    int number = 0;
    char *result = my_itoa(number);

    cr_assert_str_eq(result, "0");
    free(result);
}
