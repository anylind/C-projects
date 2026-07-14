#include "user.h"
#include <stdio.h>
#include <stdlib.h>

FILE *open_database(void) {
  FILE *file = fopen("users.db", "rb+");

  if (file == NULL) {
    perror("users.db");
    exit(EXIT_FAILURE);
  }

  return file;
}

int delete_user_id(int id) {
  FILE *src = fopen("users.db", "rb");
  FILE *tmp = fopen("users.tmp", "wb");

  if (!src || !tmp) {
    perror("file");
    return 0;
  }

  unsigned char header[HEADER_SIZE];
  fread(header, HEADER_SIZE, 1, src);
  fwrite(header, HEADER_SIZE, 1, tmp);

  struct User user;
  int found = 0;

  while (fread(&user, sizeof(user), 1, src) == 1) {
    if (user.id == id) {
      found = 1;
      continue;
    }

    fwrite(&user, sizeof(user), 1, tmp);
  }

  fclose(src);
  fclose(tmp);

  if (!found) {
    remove("users.tmp");
    printf("User not found.\n");
    return 0;
  }

  remove("users.db");

  if (rename("users.tmp", "users.db") != 0) {
    perror("rename");
    return 0;
  }

  printf("User deleted.\n");
  return 1;
}

void clear_input_buffer(void) {
  int ch;

  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
}
