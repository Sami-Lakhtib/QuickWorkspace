
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qws_error.h"


static const char *QWS_ErrorMessages[QWS_ERROR_COUNT];

static QWS_Error *errorStack;

QWS_Error *QWS_ErrorCreate(QWS_ErrorType _type, const char* _message)
{
    QWS_Error *err = (QWS_Error *) calloc(1, sizeof(QWS_Error));
    if(!err) return NULL;

    err->type = _type;
    err->message = strdup(_message);

    return err;
}

bool QWS_ErrorDestroy(QWS_Error *err)
{
    if(!err) return false;

    free(err->message);
    free(err);

    return true;
}

bool QWS_ErrorPush(QWS_ErrorType _type, const char* _message)
{   
    QWS_Error *err = QWS_ErrorCreate(_type, _message);
    if(!err) return false;
    
    if(!errorStack)
    {
        errorStack = err;
        return true;
    }

    err->next = errorStack;
    errorStack = err;
    return true;
}


QWS_Error *QWS_ErrorPop(void)
{
    if(!errorStack) return NULL;

    QWS_Error *err = errorStack;
    errorStack = err->next;

    err->next = NULL;
    return err;
}


void QWS_ErrorDebug(void)
{
    int count = 1;

    while(errorStack)
    {
        printf("|\n ");
        for(int i = 0; i < count; ++i) printf("-");

        QWS_Error *err = QWS_ErrorPop();

        printf("ERROR: %s: %s\n",
            QWS_ErrorMessages[err->type],
            err->message
        );

        QWS_ErrorDestroy(err);

        ++count;
    }
}


bool QWS_ErrorInit(void)
{
    errorStack = NULL;

    QWS_ErrorMessages[QWS_ERROR_NONE] = "";
    QWS_ErrorMessages[QWS_ERROR_INVALID_FLAG] = "Invalid flag";
    QWS_ErrorMessages[QWS_ERROR_INVALID_COMMAND] = "Invalid command";
    QWS_ErrorMessages[QWS_ERROR_INVALID_ARGUMENT] = "Invalid argument";
    QWS_ErrorMessages[QWS_ERROR_INVALID_NUMBER_OF_ARGUMENTS] = "Invalid number of arguments";
    QWS_ErrorMessages[QWS_ERROR_FAILED_TO_CREATE_FILE] = "Failed to create file.";
    QWS_ErrorMessages[QWS_ERROR_FAILED_TO_CREATE_FOLDER] = "Failed to create folder";

    return true;
}