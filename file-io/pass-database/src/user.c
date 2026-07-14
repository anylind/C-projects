#include "user.h"
#include <stdio.h>
#include <string.h>

void add_user(FILE *file, struct User user, int *last_id) {
  fseek(file, 0, SEEK_END);

  user.id = ++(*last_id);

  if (fwrite(&user, sizeof(user), 1, file) != 1) {
    perror("fwrite");
    return;
  }

  fflush(file);

  printf("User added. ID = %d\n", user.id);
}

void list_all_users(FILE *file) {
  struct User user;

  fseek(file, HEADER_SIZE, SEEK_SET);

  while (fread(&user, sizeof(user), 1, file) == 1) {
    printf("ID: %d\n", user.id);
    printf("Name: %s\n", user.name);
    printf("Password: %s\n", user.password);
    printf("-------------------\n");
  }
}

void search_by_id(FILE *file, int id) {
  struct User user;

  fseek(file, HEADER_SIZE, SEEK_SET);

  while (fread(&user, sizeof(user), 1, file) == 1) {
    if (user.id == id) {
      printf("ID: %d\n", user.id);
      printf("Name: %s\n", user.name);
      printf("Password: %s\n", user.password);
      return;
    }
  }

  printf("User not found.\n");
}

void filter_users(FILE *file, const char *name) {
  struct User user;
  int found = 0;

  fseek(file, HEADER_SIZE, SEEK_SET);

  while (fread(&user, sizeof(user), 1, file) == 1) {
    if (strcmp(user.name, name) == 0) {
      found = 1;

      printf("ID: %d\n", user.id);
      printf("Name: %s\n", user.name);
      printf("Password: %s\n", user.password);
      printf("-------------------\n");
    }
  }

  if (!found)
    printf("No user found.\n");
}
