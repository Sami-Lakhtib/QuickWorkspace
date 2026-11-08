#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <errno.h>
#include "qws_error.h"
#include "qws_dir.h"


bool QWS_CreateFolder(const char *name)
{
    if(_mkdir(name) == -1)
    {
        char msgBuffer[BUFFER_SIZE_MAX];                
        if(errno == EEXIST)
        {
            snprintf(msgBuffer, BUFFER_SIZE_MAX, "%s already exists.", name);
            QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msgBuffer);

            return false;
        }

        if(errno == ENOENT)
        {
            snprintf(msgBuffer, BUFFER_SIZE_MAX, "%s doesn't exist.", name);
            QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msgBuffer);

            return false;
        }

        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, "unknown error.");
        return false;
    }
    return true;
}

bool QWS_CreateDirectory(const char *path)
{
    if(!path) return false;
    char *pathClone = strdup(path);

    char pathBuffer[BUFFER_SIZE_MAX] = "";

    char *token = strtok(pathClone, QWS_PATH_DELIMITER);
    while(token)
    {
        if(token == pathClone)
            snprintf(pathBuffer, BUFFER_SIZE_MAX, "%s", token);
        else
            snprintf(pathBuffer, BUFFER_SIZE_MAX, "%s%s%s", pathBuffer, QWS_PATH_DELIMITER, token);

        if(_mkdir(pathBuffer) == -1 && errno == ENOENT)
        {
            char msgBuffer[BUFFER_SIZE_MAX];                
            snprintf(msgBuffer, BUFFER_SIZE_MAX, "%s doesn't exist.", pathBuffer);
            QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msgBuffer);
            free(pathClone);
            return false;
        }

        token = strtok(NULL, QWS_PATH_DELIMITER);
    }

    free(pathClone);
    return true;
}



FILE *QWS_CreateFile(const char *path)
{
    if(!path) return NULL;
    char *pathClone = strdup(path);
    char pathBuffer[BUFFER_SIZE_MAX] = "";

    char *token = strtok(pathClone, QWS_PATH_DELIMITER);
    char *lastToken = NULL;
    while(token)
    {   
        if(!lastToken)
        {
            lastToken = token;
            token = strtok(NULL, QWS_PATH_DELIMITER);
            continue;
        }

        if(lastToken == pathClone)
            snprintf(pathBuffer, BUFFER_SIZE_MAX, "%s", lastToken);

        if(_mkdir(pathBuffer) == -1 && errno == ENOENT)
        {
            char msgBuffer[BUFFER_SIZE_MAX];                
            snprintf(msgBuffer, BUFFER_SIZE_MAX, "%s doesn't exist.", pathBuffer);
            QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msgBuffer);
            free(pathClone);
            return false;
        }

        lastToken = token;
        token = strtok(NULL, QWS_PATH_DELIMITER);
    }

    FILE *F = fopen(path, "w");
    if(!F)
    {
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FILE, path);
        free(pathClone);
        return NULL;
    }

    free(pathClone);
    return F;
}
