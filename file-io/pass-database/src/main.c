#include <stdio.h>
#include <string.h>
#include "user.h"
#include "storage.h"

int main(void) {
  unsigned long secret = 0x9911882277336644UL;
  unsigned long check_secret = 0;

  FILE *file = fopen("users.db", "rb+");

  if (file == NULL) {
    file = fopen("users.db", "wb+");
    if (file == NULL) {
      perror("users.db");
      return 1;
    }

    fwrite(&secret, sizeof(secret), 1, file);
    fseek(file, HEADER_SIZE, SEEK_SET);
  } else {
    rewind(file);

    if (fread(&check_secret, sizeof(check_secret), 1, file) != 1 ||
        check_secret != secret) {
      fclose(file);

      file = fopen("users.db", "wb+");
      if (file == NULL) {
        perror("users.db");
        return 1;
      }

      fwrite(&secret, sizeof(secret), 1, file);
      fseek(file, HEADER_SIZE, SEEK_SET);
    }
  }

  struct User user;
  int last_id = 0;

  fseek(file, HEADER_SIZE, SEEK_SET);
  while (fread(&user, sizeof(user), 1, file) == 1) {
    if (user.id > last_id)
      last_id = user.id;
  }

  int option = 0;

  while (option != 6) {
    printf("\n");
    printf("1) Add user\n");
    printf("2) Delete user\n");
    printf("3) Search user by id\n");
    printf("4) Filter users by name\n");
    printf("5) List all users\n");
    printf("6) Quit\n");
    printf("Select: ");

    if (scanf("%d", &option) != 1) {
      clear_input_buffer();
      continue;
    }

    clear_input_buffer();

    switch (option) {
    case 1:
      printf("Name: ");
      fgets(user.name, MAX_LEN, stdin);

      printf("Password: ");
      fgets(user.password, MAX_LEN, stdin);

      user.name[strcspn(user.name, "\n")] = '\0';
      user.password[strcspn(user.password, "\n")] = '\0';

      add_user(file, user, &last_id);
      break;

    case 2: {
      int id;

      printf("ID: ");
      if (scanf("%d", &id) == 1)
        delete_user_id(id);

      clear_input_buffer();

      fclose(file);
      file = open_database();
      break;
    }

    case 3: {
      int id;

      printf("ID: ");
      if (scanf("%d", &id) == 1) {
        clear_input_buffer();
        search_by_id(file, id);
      }
      break;
    }

    case 4: {
      char name[MAX_LEN];

      printf("Name: ");
      fgets(name, MAX_LEN, stdin);
      name[strcspn(name, "\n")] = '\0';

      filter_users(file, name);
      break;
    }

    case 5:
      list_all_users(file);
      break;

    case 6:
      break;

    default:
      printf("Invalid option.\n");
    }
  }

  fclose(file);
  return 0;
}

