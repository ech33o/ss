// Check the structure of the card number and Luhn's Algorithm checksum

#include <cs50.h>
#include <math.h>
#include <stdio.h>

long card_number;
int sum = 0;

bool check_type(int prefix, int length);
void sum_of_digits(int place_value, int multiple);

int main(void)
{
    // Get the card number input by the user
    card_number = get_long("Number: ");

    // Check the card issuer
    string card_issuer = "INVALID";
    if (check_type(34, 13) || check_type(37, 13))
    {
        card_issuer = "AMEX";
    }
    else if (check_type(51, 14) || check_type(52, 14) || check_type(53, 14) ||
             check_type(54, 14) || check_type(55, 14))
    {
        card_issuer = "MASTERCARD";
    }
    else if (check_type(4, 12) || check_type(4, 15))
    {
        card_issuer = "VISA";
    }
    else
    {
        printf("%s\n", card_issuer);
        return 0;
    }

    // Perform Luhn's Algorithm checksum in two steps
    sum_of_digits(2, 2);
    sum_of_digits(1, 1);

    // When the checksum fails
    if (sum % 10 != 0)
    {
        card_issuer = "INVALID";
    }

    // Print test result
    printf("%s\n", card_issuer);
}

// Calculate the sum of every other digit(starting from which digit from the end)
void sum_of_digits(int place_value, int multiple)
{
    long a;
    long b;
    int other_digit;
    do
    {
        a = (long) pow(10, place_value);
        b = (long) pow(10, place_value - 1);
        place_value += 2;
        other_digit = ((card_number % a) / b) * multiple;
        int tens_digit = other_digit / 10;
        int ones_digit = other_digit % 10;
        sum = sum + tens_digit + ones_digit;
    }
    while ((a / card_number) < 10);
}

// Check the card number length and prefix range
bool check_type(int prefix, int length)
{
    return ((card_number >= prefix * pow(10, length)) &&
            (card_number < (prefix + 1) * pow(10, length)));
}
