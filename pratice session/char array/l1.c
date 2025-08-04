#include <stdio.h> // For printf(), fprintf(), etc.
#include <string.h> // For string functions like strlen(), strcpy(), etc.
#include <stdlib.h> // For malloc(), calloc(), realloc(), free()
#include <time.h>   // For time() and ctime() to log timestamps
#include <stdlib.h>  // For atoi() and atof()
#include <ctype.h>   // For toupper() and tolower()
// #include <time.h>    // For time() if needed
#include <stddef.h>  // For size_t
// #include <stdarg.h>  // For variable argument functions if needed example: printf(),
//  fprintf(), etc.
// #include <limits.h>  // For INT_MAX, etc. if needed example: INT_MAX, LONG_MAX, etc.
// #include <assert.h>  // For assert() if needed example: assert(condition)
// #include <math.h>    // For math functions if needed example: sqrt(), pow(), etc.
// #include <stdbool.h> // For boolean type if needed example: bool, true, false
#include <stdint.h>  // For fixed-width integer types if needed example: int32_t, 
// uint64_t, etc.


 int main(){
    //Method 1: scanf and printf
    // char arr[100];
    // scanf("%s", arr); //it take input till space, after seeing space it got terminate
    // printf("%s",arr);

    // Method 2: gets and puts (Avoid gets)
    // char str1[100];
    // fgets(str1, sizeof(str1), stdin);  // Safe for multi-word input
    // puts(str1);
    // printf("Length:%zu\n", strlen(str1));  // Output: Length: 14 (including newline)
    // // Note: fgets includes the newline character, so you may want to remove it
    // // if you want to remove the newline character:
    // str1[strcspn(str1, "\n")] = 0;
    // puts(str1);  // Output: hello world (without newline)
    // // printf("Length:%zu\n", strlen(str1));  // Output: Length: 12 (without newline)

    //  2. Length of a string → strlen()
    // char str[] = "hello";
    // printf("Length: %zu\n", strlen(str));  // Output: 5

    // 3. Copy one string to another → strcpy()

    // char src[] = "C programming";
    // char dest[50];
    // strcpy(dest, src);
    // printf("Source String: %s\n", src);  // Output: C programming
    // printf("Copied String: %s\n", dest);  // Output: C programming

    //  5. Compare two strings → strcmp()

    // char a[] = "apple";
    // char b[] = "banana";
    // if (strcmp(a, b) == 0) {
    //     printf("Strings are equal\n");
    // } else {
    //     printf("Strings are not equal\n");
    // }


    // 6. Convert to uppercase/lowercase → strupr() / strlwr()
    // (These are not standard C functions, but many compilers like Turbo C or 
    // Windows provide them)
    // Include header:

    // #include <ctype.h>
    // char str[] = "Hello";
    // printf("Original: %s\n", str);  // Output: Hello
    // for (int i = 0; str[i]; i++) {
    //     str[i] = toupper(str[i]);  // or tolower(str[i])
    // }
    // printf("Uppercase: %s\n", str);  // Output: HELLO


    // 7. Reverse a string

    // char str[] = "hello";
    // int n = strlen(str);
    // for (int i = 0; i < n / 2; i++) {
    //     char temp = str[i];
    //     str[i] = str[n - i - 1];
    //     str[n - i - 1] = temp;
    // }
    // printf("Reversed: %s\n", str);


    //  8. Find substring → strstr()

    // char str[] = "Learn C programming";
    // char *sub = strstr(str, "C");
    // if (sub)
    //     printf("Found: %s\n", sub);  // Outputs: C programming
    // else
    //     printf("Not found\n");
    // Note: strstr() returns a pointer to the first occurrence of the substring
    // or NULL if not found.    

    //  9. Find a character → strchr() / strrchr()
    // strchr() finds the first occurrence, strrchr() finds the last occurrence
    // char str[] = "banana";
    // char *first = strchr(str, 'a');    // First 'a'
    // char *last = strrchr(str, 'a');    // Last 'a'
    // printf("First 'a': %s\n", first ? first : "Not found");  //First 'a': anana
    // printf("Last 'a': %s\n", last ? last : "Not found");      //Last 'a': a

    // 10. Compare first N characters → strncmp()
    // strcmp is used to compare two strings, but you can also specify how many
    //  characters to compare.
    // if (strncmp("abcdef", "abcxyz", 3) == 0)
    //     printf("First 3 characters match!\n");
    // else
    //     printf("First 3 characters do not match!\n");
    // Output: First 3 characters match!

    // 11. Copy first N characters → strncpy()
    // strncpy() is used to copy a specified number of characters from one string
    // to another. It is safer than strcpy() as it prevents buffer overflow.
    // char src[] = "world";
    // char dest[10];
    // strncpy(dest, src, 3);  // dest = "wor"
    // dest[3] = '\0';
    // printf("Copied first 3 characters: %s\n", dest);  // Output: Copied first 3 characters: wor


    // 12. Concatenate N characters → strncat()
    // strncat() is used to concatenate a specified number of characters from one
    // string to another. It appends the characters to the end of the destination string.
    // char a[20] = "Hi";
    // char b[] = "There";
    // strncat(a, b, 3);  // a = "HiThe"
    // // why at strncat(a, b, 3) is used?
    // // It appends the first 3 characters of string b to string a.
    // // So, "Hi" + "The" = "HiThe"
    // // Note: strncat() does not null-terminate the result if the destination string
    // // is not large enough to hold the concatenated result.
    // // Note: Ensure the destination string has enough space to hold the concatenated result.
    // // strncat() does not null-terminate the result if the source string is longer than N.
    // // So, you may need to manually null-terminate it if necessary.
    // a[5] = '\0';  // Manually null-terminate
    // printf("Concatenated string: %s\n", a);  // Output: Concatenated string: HiThe


    // 13. String to int → atoi(), float → atof()
    // These functions convert a string to an integer or float.
    // They are useful for parsing numbers from strings.
    // Note: These functions do not handle errors, so ensure the input is valid.
    // #include <stdlib.h>  // For atoi() and atof()
    // char str[] = "123";
    // int num = atoi(str);    // num = 123
    // float pi = atof("3.14");  // pi = 3.14
    // printf("String to int: %d\n", num);  // Output: String to int: 123
    // printf("String to float: %.2f\n", pi);  // Output: String to float: 3.14



    //  Int to string → sprintf()
    // This function converts an integer to a string.
    // It is similar to printf() but writes to a string instead of standard output.
    // #include <stdio.h>  // For sprintf()
    // int n = 42;
    // char str[10];
    // sprintf(str, "%d", n);  // str = "42"
    // printf("Integer to string: %s\n", str);  // Output: Integer to string: 42

    // Note: sprintf() can lead to buffer overflow if the destination string is not large enough.
    // Use snprintf() for safer string formatting:
    // snprintf(str, sizeof(str), "%d", n);  // Safer version
    // printf("Integer to string (snprintf): %s\n", str);  // Output: Integer to string (snprintf): 42
    // Note: snprintf() is safer as it limits the number of characters written to the destination string.

    // 15. String to uppercase/lowercase → toupper() / tolower()
    // These functions convert a character to uppercase or lowercase.
    // They are useful for case-insensitive comparisons.
    // #include <ctype.h>  // For toupper() and tolower()
    // char ch = 'a';
    // char upper = toupper(ch);  // upper = 'A'
    // char lower = tolower(upper);  // lower = 'a'
    // printf("Character to uppercase: %c\n", upper);  // Output: Character to uppercase: A
    // printf("Character to lowercase: %c\n", lower);  // Output: Character to lowercase: a
    // Note: toupper() and tolower() work on single characters, not strings.

    // 16. String to integer with error checking → strtol() 
    // strtol() converts a string to a long integer with error checking.
    // It allows you to handle invalid input gracefully.
    // #include <stdlib.h>  // For strtol()
    // char *endptr;
    // long value = strtol("123abc", &endptr, 10);  // Converts "123" to long
    // if (endptr == "123abc") {
    //     printf("Conversion failed\n");
    // } else {
    //     printf("Converted value: %ld\n", value);  // Output: Converted value: 123
    // }
    // Note: strtol() can handle different bases (e.g., base 10, base 16) by specifying the base parameter. 
    // It also provides error checking by allowing you to check if the conversion was successful.
    return 0;      
}