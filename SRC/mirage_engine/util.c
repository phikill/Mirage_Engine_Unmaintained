#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> 

#include"util.h"
#include"renderer/render.h"

char default_dialogue_text_when_restart[DIALOGUE_SIZE] = "Wandering The Woods";


void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;

    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

    // walk inwards from both ends of the string, 
    // swapping until we get to the middle
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

char *convert(int number, char *buff, int base, char digits[30])
{
    char *result = (buff == NULL || base > strlen(digits) || base < 2) ? NULL : buff;
    char sign = 0;

    if(number < 0)
    {
         sign = '-';
    }
    if(result != NULL)
    {
        do
        {
            *buff++ = digits[abs(number % (base ))];
            number /= base;
        } 
        while(number);
        if(sign) *buff++ = sign;
        if (!*result) *buff++ = '0';
        *buff = 0;
        inplace_reverse(result);
    }
    return result;
}

