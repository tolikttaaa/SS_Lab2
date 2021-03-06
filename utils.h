//
// Created by ttaaa on 4/22/21.
//

#ifndef SYSTEM_SOFTWARE_UTILS_H
#define SYSTEM_SOFTWARE_UTILS_H

int parse(char *cmd, char **args);
void append_path_part(char *path, char *part);
char *get_line(void);
void remove_ending_symbol(char *str, char sym);
void remove_until(char *str, char sym);
void remove_before(char *str, char sym);
int check_directory(char *path);
int startsWith(char *str, char *pre);
char *get_before(char *str, char sym);
char *concat(char *first, char * second);

#endif //SYSTEM_SOFTWARE_UTILS_H
