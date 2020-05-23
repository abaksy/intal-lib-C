# Integer library
A C library consisting of basic functions for integers of arbitrary length
This library was implemented as a part of Design and Analysis of Algorithms (UE18CS251) course at PES University

To run, use
```
$gcc -Wall -std=c99 intal.c tests/intal_sampletest.c 
$./a.out
```

1. Introduction

An intal (integer of arbitrary length) is a representation of a number in base 10 system in which each digit is represented as a character. The digits are represented in big endian format, meaning that the digit with the highest place value is at the leftmost position of the string, while the digit with the lowest place value is at the rightmost position. 
NOTE: All numbers are at most 1000 digits long

An intal is different from a regular integer in C in that it is stored as an array of characters (each character being a digit) as against a regular integer stored in binary. This implies that an intal does not inherently carry any information about the real value of the number it represents. But an integer, being represented in binary. encodes information about the place values of each digit. 

2. Approach
intal_add: Starting from the unit's digit (the rightmost digit) the digits at each position are added one at a time. The carry is propagated from right to left. 
If anyone of the numbers has extra digits left then they are added (with the carry) to the result. 

intal_compare: First the lengths of the two numbers are checked, with the larger number (ie. the one with more digits) being returned. 
If both numbers are of the same length, then they are compared digit wise, starting from the highest place-value position. Whichever number has a larger digit at any position is returned

intal_subtract: Starting from the unit's digit (the rightmost digit) the digits at each position are subtracted one at a time. The borrow from higher place-value digits is propagated from right to left. 
If anyone of the numbers has extra digits left then they are added (with the carry) to the result ( as subtraction from 0 is equivalent to addition from 0)

intal_multiply: The first number is multiplied by each digit of the second number. This generates a series of partial products (as many partial products as there are digits in the second number). These partial products are added, after 
multiplying by the appropriate power of 10 (ie. shifting to the left as many places and filling 0 at the end). 
The sum of these partial products is the final product

intal_mod: The algorithm uses an approach similar to long division, as done using pen and paper. The result is initialized to 0 and the algorithm loops through every digit in the dividend, multiplies the current result by 10 (shift by one place and append 10) and 
adds the new digit of the intal to the mod value, then subtracts the divisor from it until the final result is lesser than the divisor. After passing over all the digits in dividend, the result is intal1 % intal2

intal_pow: The formula a^n = (a^2)^(n/2) is used to calculate the first number raised to the power of the second number. This involves log2(n) multiplications

intal_gcd: The Euclidean algorithm to find the GCD of two intals reduces the number of comparisions to log(n). The algorithm uses the relation gcd(a,b) = gcd(b, a%b)

intal_fibonacci: The Fibonacci recurrence relation F(n) = F(n-1)+F(n-2) is used to compute the value of F(n). The given solution is implemented in O(n) time and O(1) extra space. 

intal_factorial: The value of n! is calculated using the formula n! = n*(n-1)! 
This is implemented using n intal multiplications

intal_bincoeff: The Binomial coefficient C(n, k) is calculated using Pascal's Identity C(n, k) = C(n-1, k) + C(n-1, k-1)
At each step the computation is paused if the value of C(n, k) is more than 10^1000

intal_max: The pointer max is initialized to the first intal in the array. The algorithm loops through the entire array, and if an intal is found that is larger than the current value of max, then the max pointer is changed to that and the offset value is changed to the index of that intal. 

intal_min: The pointer max is initialized to the first intal in the array. The algorithm loops through the entire array, and if an intal is found that is smaller than the current value of max, then the max pointer is changed to that and the offset value is changed to the index of that intal. 

intal_search: Uses a simple linear search to find the index of the first intal that exactly matches with the key. If no matches are found even after going through the entire array, then -1 is returned.

intal_binsearch: Implements a binary search algorithm on the array of intals. The algorithm splits the array into 2 parts recursively until the index of the key is found. 

intal_sort: The given implementation uses a heapsort algorithm on the array of intals. The given array is converted recursively into a max-heap and the top element of the heap is removed at each iteration. The remaining data is once again converted to a heap and this process is repeated until all the elements of the heap are covered.

coin_row_problem: Given a coin, the alternatives at each step are either to select it or not, based on whether picking it results in a greater total value or not. 
Hence the value at the nth coin, F(n) can be calculated using the recurrence relation F(n) = max(arr(n)+F(n-2), F(n-1))
This basically implies that picking the nth coin (arr(n)) forces us to skip the (n-1)th coin which covers the given constraint (ie. no two adjacent coins to be selected)

The given recurrence can be formuled as a dynamic programming problem, in O(n) space and O(1) time (As the recurrence involves n-2 terms it can be implemented using 3 intals)


3. 
a) Future Work:

Additional functionalities like division, square roots and conversion of base 10 to other number systems (hexadecimal, octal, binary) can be implemented using these function

b) I would probably wrap the string inside a structure that stores, along with the actual string, some additional information such as the string length. This removes the need for several calls to strlen() function, hence increasing real-world performance

