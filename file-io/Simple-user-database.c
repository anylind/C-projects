#include <stdio.h>
#include <string.h>

void simple_encryption(char *, size_t, char);

struct User {
  int id;
  char name[51];
  int age;
};

int main(void) {
  FILE *file = fopen("users.db", "ab+");
  if (file == NULL) {
    perror("fopen");
    return 1;
  }

  int option = 1;
  struct User user = {.id = 0};
  while (option) {
    printf("1 - Add new user.\n");
    printf("2 - List users.\n");
    printf("0 - Quit.\n");
    printf("Select an option: ");
    scanf("%d", &option);
    int c, last_id = 0;
    while ((c = getchar()) != '\n')
      ;

    while (fread(&user, sizeof(struct User), 1, file) == 1)
      last_id = user.id;

    rewind(file);
    switch (option) {
    case 1:
      user.id = last_id + 1;
      printf("Enter user name '50 char': ");
      fgets(user.name, sizeof(user.name), stdin);
      printf("Enter user age: ");
      scanf("%d", &user.age);
      simple_encryption(user.name, strlen(user.name), 'c');
      fwrite(&user, sizeof(struct User), 1, file);
      fflush(file);
      break;

    case 2:
      while (fread(&user, sizeof(struct User), 1, file) == 1) {
        printf("\n");
        printf("User ID: %d\n", user.id);
        simple_encryption(user.name, strlen(user.name), 'o');
        printf("User Name: %s", user.name);
        printf("User Age: %d\n", user.age);
        printf("\n");
      }
      break;

    case 0:
      fclose(file);
      return 0;

    default:
      printf("\n -- Enter valid option. -- \n\n");
      break;
    }
  }

  fclose(file);
  return 0;
}

void simple_encryption(char *str, size_t len, char option) {
  int n = 30;
  if (option == 'o')
    n = -30;
  for (size_t i = 0; i < len; ++i) {
    str[i] = str[i] + n;
  }
}
