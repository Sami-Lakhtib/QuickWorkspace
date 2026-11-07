#include <stdio.h>
#include <direct.h>
#include "qws_error.h"
#include "qws_command.h"

#define BUFFER_MAX_SIZE 256
#define PROJECT_NAME 0
#define PROJECT_TYPE 1
#define C_MAKEFILE_TEMPLATE   "FLAGS := -I include -L lib\n"\
                            "SRC := $(wildcard *.c src/*.c)\n"\
                            "OUTPUT := output\n\n"\
                            "RUN: BUILD\n"\
	                        "\t@$(OUTPUT)\n"\
                            "BUILD:\n"\
	                        "\t@gcc $(SRC) $(FLAGS) -o $(OUTPUT)\n"
#define C_GITIGNORE_TEMPlATE  "*.txt\n"\
                            "makefile"

const char *CPP_DIRS[] = {"include", "src", "lib"};
const char *CPP_FILES[] = {"makefile", ".gitignore", "README.md"};
const char *WEB_DIRS[] = {"assets", "includes", "api", "sql"};
const char *WEB_FILES[] = {"config.php", ".gitignore", "README.md"};


bool createFolder(char *name)
{
    if(_mkdir(name) == -1)
    {
        size_t len = strlen(name);
        char msg[len + 17];
        snprintf(msg, len + 17, "%s already exists.", name);
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msg);
        return false;
    }
    return true;
}

FILE *createFile(char *name)
{
    FILE *F = fopen(name, "r");
    if(F)
    {
        size_t len = strlen(name);
        char msg[len + 17];
        snprintf(msg, len + 17, "%s already exists.", name);
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FILE, msg);
        fclose(F);
        return NULL;
    }
    fclose(F);
    F = fopen(name, "w");
    if(!F)
    {
        size_t len = strlen(name);
        char msg[len + 16];
        snprintf(msg, len + 16, "%s unknown error.", name);
        QWS_ErrorPush(QWS_ERROR_FAILED_TO_CREATE_FOLDER, msg);
        fclose(F);
        return NULL;
    }
    return F;
}

bool createFolders(const char *dir, const char **folders, int count)
{
    char pathBuffer[BUFFER_MAX_SIZE];
    for(int i = 0; i < count; ++i)
    {
        int n = snprintf(pathBuffer,
            sizeof(pathBuffer),
            "%s/%s",
            dir,
            folders[i]
        );

        if(n >= sizeof(pathBuffer)) return false;
        if(!createFolder(pathBuffer)) return false;
    }
    return true;
}

bool createFiles(const char *dir, const char **files, int count)
{
    char pathBuffer[BUFFER_MAX_SIZE];
    for(int i = 0; i < count; ++i)
    {
        snprintf(pathBuffer, sizeof(pathBuffer), "%s/%s", dir, files[i]);

        FILE *file = createFile(pathBuffer);
        if(!file) return false;
        fclose(file);
    }
    return true;
}

bool writeToFile(const char *file, const char *content)
{
    FILE *F = fopen(file, "a");
    if(!F) return false;

    fprintf(F, "%s", content);
    fclose(F);

    return true;
}




bool cmd_new(QWS_Flags flags, int argc, char **argv)
{
    if(!createFolder(argv[PROJECT_NAME])) return false;

    char pathBuffer[BUFFER_MAX_SIZE];
    if(!strcmp(argv[PROJECT_TYPE], "c") || !strcmp(argv[PROJECT_TYPE], "c++") || !strcmp(argv[PROJECT_TYPE], "cpp"))
    {
        if(!createFolders(
            argv[PROJECT_NAME],
            CPP_DIRS,
            sizeof(CPP_DIRS) / sizeof(*CPP_DIRS))
        ) return false;

        if(!createFiles(
            argv[PROJECT_NAME],
            CPP_FILES,
            sizeof(CPP_FILES) / sizeof(*CPP_FILES))
        ) return false;

        if(flags['d'])
        {
            snprintf(pathBuffer, sizeof(pathBuffer), "%s/%s", argv[PROJECT_NAME], CPP_FILES[0]);
            if(!writeToFile(
                pathBuffer,
                C_MAKEFILE_TEMPLATE)
            ) return false;

            snprintf(pathBuffer, sizeof(pathBuffer), "%s/%s", argv[PROJECT_NAME], CPP_FILES[1]);
            if(!writeToFile(
                pathBuffer,
                C_GITIGNORE_TEMPlATE)
            ) return false;
        }

        return true;
    }

    if(!strcmp(argv[PROJECT_TYPE], "web"))
    {
        if(!createFolders(
            argv[PROJECT_NAME],
            WEB_DIRS,
            sizeof(WEB_DIRS) / sizeof(*WEB_DIRS))
        ) return false;

        if(!createFiles(
            argv[PROJECT_NAME],
            WEB_FILES,
            sizeof(WEB_FILES) / sizeof(*WEB_FILES))
        ) return false;

        return true;
    }




    QWS_ErrorPush(QWS_ERROR_INVALID_ARGUMENT, argv[0]);
    return false;
}