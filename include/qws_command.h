#ifndef QWS_COMMAND_H
#define QWS_COMMAND_H

#include <stdio.h>
#include <stdbool.h>

#define QWS_COMMAND_COUNT 2

typedef bool QWS_Flags[256];

typedef struct QWS_Command {
    const char *name;
    char *flags;
    int minArg, maxArg;
    bool (*handler)(QWS_Flags, int, char**);

} QWS_Command;



extern QWS_Command QWS_CommandMap[QWS_COMMAND_COUNT];


extern bool cmd_create(QWS_Flags flags, int argc, char **argv);
extern bool cmd_new(QWS_Flags flags, int argc, char **argv);



#endif