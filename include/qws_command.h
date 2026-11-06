#ifndef QWS_COMMAND_H
#define QWS_COMMAND_H
#include <stdbool.h>

#define QWS_COMMAND_COUNT 1

typedef bool (*QWS_CommandHandler)(int, char**);


typedef struct QWS_Command {
    const char *name;
    QWS_CommandHandler handler;

} QWS_Command;



extern QWS_Command QWS_CommandMap[QWS_COMMAND_COUNT];


extern bool create(int argc, char **argv);



#endif