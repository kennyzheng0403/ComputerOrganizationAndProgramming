#include "part1-functions.h"
#include <string.h>

/*
 * Name: Kenny Zheng
 * Collaborators:
 * Please list anyone you collaborated with on this file here.
 */

/** divide
 *
 * Calculates the quotient of two numbers.
 *
 * @param "a" the divident
 * @param "b" the divisor
 * @return if b is a valid divisor, the quotient a/b
 *         0 otherwise
 */
int divide(int a, int b) {
    int result ;
    if(b == 0){
        return 0;
    }else{
        result = a / b;
        return result;
    }
}

/** toLowercase
 * 
 * Converts a string in-place to lowercase.
 * In-place means that the inputted string will be modified itself.
 * You will NOT create a new string.
 *
 * @param "str" a NULL-terminated string to be converted to lowercase
 */
void toLowercase(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++){
        if(str[i] >= 65 && str[i] <= 90){
            str[i] += 32;
        }
    }
}

/** gcd
 *
 * Calculates the greatest common divisor (GCD) of two integers.
 * The GCD of a and b is the largest integer that divides both a and b without any remainder.
 *
 * @param "a" the first of the two integers whose GCD is to be computed.
 * @param "b" the second of the two integers whose GCD is to be computed.
 * @return the greatest common divisor of a and b.
 */
int gcd(int a, int b) {
    int answer;
    if (a == 0 || b == 0) {
        return 0;
    } else if (a == 1 || b == 1) {
        return 1;
    }
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    for (int i = 1; i <= a && i <= b; ++i) {
        if (a % i == 0 && b % i == 0) {
            answer = i;
            }
        }
    return answer;
}

/** fib
 * 
 * Computes the nth integer in the Fibonnacci sequence.
 * The Fibonacci sequence begins with F(0) = 0, F(1) = 1.
 * Successive elements are the sum of the previous two elements in the sequence.
 *
 * @param "n" the index of the Fibonacci number to calculate.
 * @return the nth Fibonacci number.
 */
int fib(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fib(n-2) + fib(n-1);
}

/** countOnes
 * 
 * Counts the number of bits set in the 2's complement binary representation of an integer.
 *
 * @param "num" the number whose bits are to be counted.
 * @return the number of bits set in num.
 */
int countOnes(int num) {
    int count = 0;
    while (num) {
        num &= (num - 1);
        count++;
    }
    return count;
}
