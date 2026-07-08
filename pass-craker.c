#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long poss_ways(int len, int n);

int main(void) {
  char characters[40];

  printf("Enter allowed characters: ");
  fgets(characters, sizeof(characters), stdin);
  characters[strcspn(characters, "\n")] = '\0';

  int charset_len = strlen(characters);

  if (charset_len == 0) {
    printf("No characters entered.\n");
    return 1;
  }

  int password_len;

  printf("Enter password length: ");
  scanf("%d", &password_len);

  if (password_len <= 0) {
    printf("Invalid password length.\n");
    return 1;
  }

  char array[password_len + 1];
  array[password_len] = '\0';

  int *counters = calloc(password_len, sizeof(int));
  if (counters == NULL) {
    printf("Allocation failed.\n");
    return 1;
  }

  unsigned long total = poss_ways(password_len, charset_len);

  for (unsigned long i = 0; i < total; i++) {

    for (int j = 0; j < password_len; j++) {
      array[j] = characters[counters[j]];
    }

//    printf("%s\n", array);

    /* increment base-charset_len counter */
    counters[0]++;

    for (int j = 0; j < password_len - 1; j++) {

      if (counters[j] == charset_len) {
        counters[j] = 0;
        counters[j + 1]++;
      } else {
        break;
      }
    }
  }

  free(counters);
  return 0;
}

unsigned long poss_ways(int len, int n) {
  unsigned long res = 1;

  for (int i = 0; i < len; i++) {
    res *= n;
  }

  return res;
}
