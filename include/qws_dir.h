#ifndef QWS_DIR_H
#define QWS_DIR_H

#include <stdio.h>

#define QWS_PATH_DELIMITER "\\"
#define BUFFER_SIZE_MAX 256


bool QWS_CreateFolder(const char *name);
bool QWS_CreateDirectory(const char *path);
FILE *QWS_CreateFile(const char *path);



#endif