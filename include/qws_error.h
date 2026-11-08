#ifndef QWS_ERROR_H
#define QWS_ERROR_H

#include <stdbool.h>

typedef enum QWS_ErrorType {
    QWS_ERROR_NONE,
    QWS_ERROR_INVALID_COMMAND,
    QWS_ERROR_INVALID_FLAG,
    QWS_ERROR_INVALID_ARGUMENT,
    QWS_ERROR_INVALID_NUMBER_OF_ARGUMENTS,
    QWS_ERROR_FAILED_TO_CREATE_FILE,
    QWS_ERROR_FAILED_TO_CREATE_FOLDER,
    QWS_ERROR_COUNT
} QWS_ErrorType;


typedef struct QWS_Error {
    QWS_ErrorType type;
    char *message;
    struct QWS_Error *next;
} QWS_Error;





QWS_Error *QWS_ErrorCreate(QWS_ErrorType _type, const char* _message);

bool QWS_ErrorDestroy(QWS_Error *err);

bool QWS_ErrorPush(QWS_ErrorType _type, const char* _message);

QWS_Error *QWS_ErrorPop(void);

void QWS_ErrorDebug(void);

bool QWS_ErrorInit(void);


#endif