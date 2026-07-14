#include <stdio.h>

#define MAX_LEN 51
#define HEADER_SIZE sizeof(unsigned long)
struct User {
  int id;
  char name[MAX_LEN];
  char password[MAX_LEN];
};
void add_user(FILE *, struct User, int *);
void list_all_users(FILE *file);
void search_by_id(FILE *file, int id);
void filter_users(FILE *file, const char *name);

