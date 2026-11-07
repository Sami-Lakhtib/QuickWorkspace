#ifndef QWS_COMMAND_H
#define QWS_COMMAND_H
#include <stdio.h>
#include <stdbool.h>

#define QWS_COMMAND_COUNT 1

typedef bool QWS_Flags[256];
typedef bool (*QWS_CommandHandler)(QWS_Flags flags, int argc, char **argv);

typedef struct QWS_Command {
    const char *name;
    char *flags;
    int minArg, maxArg;
    QWS_CommandHandler handler;

} QWS_Command;



extern QWS_Command QWS_CommandMap[QWS_COMMAND_COUNT];


extern bool cmd_create(QWS_Flags flags, int argc, char **argv);



#endif