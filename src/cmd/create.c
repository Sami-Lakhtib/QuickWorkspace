#include <stdio.h>
#include <string.h>
#include "qws_error.h"
#include "qws_command.h"



bool cmd_create(QWS_Flags flags, int argc, char **argv)
{
    FILE *F = fopen(argv[0], "w");
    if(!F)
    {
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FILE, argv[0]);
        return false;
    }

    if(flags['t']) fprintf(F, "This is a test message.");

    fclose(F);
    return true;
}