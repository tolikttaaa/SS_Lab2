//
// Created by ttaaa on 4/22/21.
//

#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include <dirent.h>
#include <argp.h>

int error(const char *msg) {
    fprintf(stderr,"Error: %s\n", msg);

    return -1;
}

int parse(const char *cmd, char **args) {
    const char *p = cmd;
    int count = 0;

    for (;;) {
        while (isspace(*p)) p++;
        if (count >= 3) {
            return count;
        }
        if (*p == '\0') break;

        if (*p == '"' || *p == '\'') {
            int quote = *p++;
            const char *begin = p;

            while (*p && *p != quote) p++;
            if (*p == '\0') return error("Unmatched quote");
            strncpy(args[count], begin, p-begin);
            count++;
            p++;
            continue;
        }

        if (strchr("<>()|", *p)) {
            args[count] = calloc(1, 256);
            strncpy(args[count], p, 1);
            count++;
            p++;
            continue;
        }

        if (isalnum(*p) || *p == '.' || *p == '/') {
            const char *begin = p;

            while (isalnum(*p) || *p == '.' || *p == '/') p++;
            strncpy(args[count], begin, p-begin);
            count++;
            continue;
        }

        return error("Illegal character");
    }

    return count;
}

int check_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir) return 1;
    else return 0;
}

int startsWith(const char *str, const char *pre) {
    size_t lenpre = strlen(pre),
            lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

void append_path_part(char *path, const char *part) {
    strcat(path, "/");
    strcat(path, part);
}

char *get_line(void) {
    char *line = malloc(100);
    char *linep = line;
    size_t lenmax = 100;
    size_t len = lenmax;
    int c;

    if (line == NULL)
        return NULL;

    for (;;) {
        c = fgetc(stdin);
        if (c == EOF)
            break;

        if (--len == 0) {
            len = lenmax;
            char *linen = realloc(linep, lenmax *= 2);

            if (linen == NULL) {
                free(linep);
                return NULL;
            }

            line = linen + (line - linep);
            linep = linen;
        }

        if ((*line++ = c) == '\n') {
            break;
        }
    }

    *line = '\0';

    return linep;
}

void remove_ending_symbol(char *str, char sym) {
    for (int i = 0;; i++) {
        if (str[i] == sym)
            str[i] = 0;
        if (str[i] == 0)
            break;
    }
}

char *substr(const char *src, int m, int n) {
    // get the length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char*)malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

char *get_before(char *str, char sym) {
    int i = 0;
    for (; i < strlen(str); i++) {
        if (str[i] == sym) {
            char *res = substr(str, 0, i);
            return res;
        }
    }

    return str;
}


void remove_before(char *str, char sym) {
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == sym) {
            strncpy(str, str + i + 1, strlen(str) - i);

            for (int j = len - 1; j > len - i; j--) {
                str[j] = 0;
                str[j] = 0;
            }

            return;
        }
    }

    for (int i = len; i >= 0; i--) {
        str[i] = 0;
    }
}

void remove_until(char *str, char sym) {
    int len = strlen(str);
    for (int i = len; i >= 0; i--) {
        if (str[i] != sym)
            str[i] = 0;
        else {
            str[i] = 0;
            break;
        }
    }
}

char* concat(char *s1, char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char *result = malloc(len1 + len2 + 1);

    if (!result) {
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);

    return result;
}
