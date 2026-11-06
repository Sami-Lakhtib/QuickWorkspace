#include <stdio.h>
#include <string.h>
#include "qws_error.h"
#include "qws_command.h"

#define ARGUMENT_COUNT 1


bool create(int argc, char **argv)
{
    int i = 1;

    bool testMessage = false;

    if(argc < ARGUMENT_COUNT)
    {
        QWS_ErrorPush(QWS_ERROR_INVALID_NUMBER_OF_ARGUMENTS, "Missing arguments");
        return false;
    }

    if(*argv[1] == '-')
    {
        for(; i < argc; ++i)
        {
            char *token = argv[i];
            if(*token == '-')
            {
                for(char *c = token + 1; c - token < strlen(token); ++c)
                    switch(*c)
                    {
                        case 't':
                            testMessage = true;
                            break;
                        default:
                            char msg[3] = "-";
                            strncat(msg, c, 1);
                            QWS_ErrorPush(QWS_ERROR_INVALID_FLAG, (const char*) msg);
                            return false;
                    }   
            }
            else break;
        }
    }

    if(argc - i != ARGUMENT_COUNT)
    {   
        char buf[2];
        snprintf(buf, 1, "%d", argc - i);
        QWS_ErrorPush(QWS_ERROR_INVALID_NUMBER_OF_ARGUMENTS, (const char*) buf);
        return false;
    }

    FILE *f = fopen(argv[i], "w");
    if(!f)
    {
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FILE, argv[i]);
        return false;
    }

    if(testMessage) fprintf(f, "This is a test message.");
    
    fclose(f);

    return true;
}