#include "std_lib.h"

int div(int a, int b) {
  int quotient = 0;
  int sign = 1;

  if (b == 0) return 0;
  if (a < 0) {
    a = -a;
    sign *= -1;
  }
  if (b < 0) {
    b = -b;
    sign *= -1;
  }
  while (a >= b) {
    a -= b;
    quotient++;
  }
  return sign * quotient;
}

int mod(int a, int b) {
    int n_abs;

    if (b == 0) {
        return 0;
    }

    n_abs = b;
    if (n_abs < 0) {
        n_abs = -n_abs;
    }

    while (a >= n_abs) {
        a = a - n_abs;
    }

    while (a < 0) {
        a = a + n_abs;
    }
    return a;
}


bool strcmp(char *str1, char *str2)
{
  while (*str1 != '\0' && *str2 != '\0') {
    if (*str1 != *str2) {
      return false;
    }
    str1++;
    str2++;
  }
  return *str1 == '\0' && *str2 == '\0';
}

void strcpy(char *dst, char *src)
{
  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
}

void clear(byte *buf, unsigned int size) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  int i = 0;
  int result = 0;
  int sign = 1;

  if (str[0] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }

  *num = result * sign;
}

void itoa(int num, char *str) {
  int i = 0;
  int j, temp;
  int isNegative = 0;
  char swap;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    str[i++] = mod(num, 10) + '0';
    num /= 10;
  }

  if (isNegative) {
    str[i++] = '-';
  }

  str[i] = '\0';

  for (j = 0; j < i / 2; j++) {
    swap = str[j];
    str[j] = str[i - j - 1];
    str[i - j - 1] = swap;
  }
}