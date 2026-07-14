#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    int c;
    while ((c = getchar()) != EOF)
      putchar(c);
    return 1;
  }
  //  if (argc > 2)
  //  if (argv[2] == "-n") {
  //  fprintf(stderr, "Error bad option: '%s'!\n", argv[2]);
  // return 1;
  //    }

  FILE *file = fopen(argv[1], "rb");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }
  size_t word_len = 32, words_len = 8;
  char **words_arr = malloc(words_len * sizeof(unsigned char *));
  //  for (size_t i = 0; i < words_len; ++i)
  //  words_arr[i] = calloc(word_len, sizeof(*words_arr[i]));

  unsigned char *word = calloc(word_len, sizeof(*word)), c;
  unsigned int lines, words, bytes, count;
  lines = words = bytes = count = 0;

  while (fread(&c, sizeof c, 1, file) == 1) {
    if (count == word_len)
      word = realloc(word, word_len += 16);
    if (words == words_len)
      words_arr = realloc(words_arr, words_len += 4);

    words_arr[words] = calloc(word_len, sizeof(unsigned char));
    if (word == NULL || words_arr == NULL || words_arr[words] == NULL) {
      fprintf(stderr, "Error allocating space! try again.\n");
      free(word);
      free(words_arr);
      fclose(file);
      return 1;
    }

    if (c != ' ' && c != '\n' && c != '\0')
      word[count] = c;
    ++count;

    if (c == '\n')
      ++lines;
    if (c == ' ' || c == '\0' || c == '\n') {

      printf("%s\n", word);
      count = 0;
      ++words;
      memset(word, 0, word_len);
    }
    ++bytes;
  }

  for (unsigned i = 0; i < words; ++i)
    printf("%p\n", words_arr[i]);

  printf("Lines: %u\n", lines);
  printf("Words: %u\n", words);
  printf("Bytes: %u\n", bytes);

  fclose(file);
  return 0;
}
