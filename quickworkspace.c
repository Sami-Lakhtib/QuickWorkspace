#include <stdbool.h>
#include <string.h>
#include "qws_error.h"
#include "qws_command.h"


bool findFlag(char f, char *flags)
{
    for(int i = 0; i < strlen(flags); ++i)
        if(flags[i] == f) return true;
    return false;
}


QWS_Command *findCommand(const char *name)
{
    for(int i = 0; i < QWS_COMMAND_COUNT; ++i)
        if(!strcmp(name, QWS_CommandMap[i].name))
            return &QWS_CommandMap[i];
    
    return NULL;
}


bool QWS_Parse(int argc, char **argv)
{
    if(argc < 2)    // no tokens aside from executable name.
    {
        QWS_ErrorPush(QWS_ERROR_INVALID_COMMAND, "Missing command.");
        return false;
    }

    int cursor = 1;     // cursor pointing at where the current reading point is.
    for(; cursor < argc && *argv[cursor] == '-'; ++cursor);     // global flags (currently not supported.)

    QWS_Command *command = findCommand(argv[cursor]);
    if(!command) // no command matching found
    {
        QWS_ErrorPush(QWS_ERROR_INVALID_COMMAND, argv[cursor]);
        return false;
    }

    ++cursor;   // move cursor after reading command name.

    QWS_Flags flags = {0};
    for(; cursor < argc && *argv[cursor] == '-'; ++cursor)   //  read flags
    {
        for(char *c = argv[cursor] + 1; *c; ++c)
        {
            if(!findFlag(*c, command->flags))   // if command doesn't support flag, halt the process.
            {
                char msg[3];
                snprintf(msg, 3, "-%c", *c);
                QWS_ErrorPush(QWS_ERROR_INVALID_FLAG, (const char*) msg);
                return false;
            }
            flags[*c] = true;   // if it does, activate it in the flag boolean array.
        }
    }

    int newArgc = argc - cursor;

    if(newArgc > command->maxArg || newArgc < command->minArg)
    {
        char msg[4];
        snprintf(msg, 3, "%d", newArgc);
        QWS_ErrorPush(QWS_ERROR_INVALID_NUMBER_OF_ARGUMENTS, (const char *) msg);
        return false;
    }

    return command->handler(flags, newArgc, argv + cursor);
}



int main(int argc, char **argv)
{   
    if(!QWS_ErrorInit()) return 1;

    if(!QWS_Parse(argc, argv))
    {
        QWS_ErrorDebug();
        return 1;
    }

    return 0;
}