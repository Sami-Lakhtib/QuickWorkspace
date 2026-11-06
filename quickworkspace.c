#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "qws_error.h"
#include "qws_command.h"


bool QWS_Route(int argc, char **argv)
{
    if(argc < 2)
    {
        QWS_ErrorPush(QWS_ERROR_INVALID_COMMAND, "Missing command.");
        return false;
    }
    if(*argv[1] != '-')
    {
        for(int i = 0; i < QWS_COMMAND_COUNT; ++i)
            if(!strcmp(argv[1], QWS_CommandMap[i].name))
                return QWS_CommandMap[i].handler(argc - 1, ++argv);

        QWS_ErrorPush(QWS_ERROR_INVALID_COMMAND, "No such command.");
        return false;
    }

    return true;
}



int main(int argc, char **argv)
{   
    if(!QWS_ErrorInit()) return 1;

    //for(int i = 0; i < argc; ++i) printf("%s\t", argv[i]);

    if(!QWS_Route(argc, argv))
    {
        QWS_ErrorDebug();
        return 1;
    }

    return 0;
}