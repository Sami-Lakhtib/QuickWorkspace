#include <stdio.h>
#include <string.h>
#include "qws_error.h"
#include "qws_command.h"
#include "qws_dir.h"

#define PROJECT_NAME 0
#define TEST_MESSAGE "This is a test message"

bool cmd_create(QWS_Flags flags, int argc, char **argv)
{
    FILE *F = QWS_CreateFile(argv[PROJECT_NAME]);
    if(!F)
    {
        QWS_ErrorPush(QWS_ERROR_NONE, "Couldn't open file.");
        return false;
    }

    if(flags['t'])
        fwrite(TEST_MESSAGE, sizeof(char), strlen(TEST_MESSAGE), F);

    return true;
}