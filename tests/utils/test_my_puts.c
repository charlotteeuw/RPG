#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <unistd.h>

// Function to test
size_t my_puts(int fd, char const *str);

/* List of tests */

Test(my_puts, test_valid_string)
{
    char *str = "Testing my_putstr function";
    int status = 0;

    cr_redirect_stdout();
    status = my_puts(STDOUT_FILENO, str);
    cr_assert_stdout_eq_str(str);
    cr_assert_eq(status, 26);
}

Test(my_puts, test_empty_string)
{
    char *str = "";
    int status = 0;

    cr_redirect_stdout();
    status = my_puts(STDOUT_FILENO, str);
    cr_assert_stdout_eq_str("");
    cr_assert_eq(status, 0);
}

Test(my_puts, test_null_string)
{
    char *str = NULL;
    int status = 0;

    cr_redirect_stdout();
    status = my_puts(STDOUT_FILENO, str);
    cr_assert_stdout_eq_str("");
    cr_assert_eq(status, 0);
}

Test(my_puts, test_stderr)
{
    char *str = "Testing my_puts function in stderr.";
    int status = 0;

    cr_redirect_stderr();
    status = my_puts(STDERR_FILENO, str);
    cr_assert_stderr_eq_str(str);
    cr_assert_eq(status, 35);
}
