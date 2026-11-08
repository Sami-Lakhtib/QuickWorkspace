#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#include "qws_error.h"
#include "qws_command.h"
#include "qws_dir.h"

#define PROJECT_NAME 0
#define PROJECT_TYPE 1
#define C_MAKEFILE_TEMPLATE   "FLAGS := -I include -L lib\n"\
                            "SRC := $(wildcard *.c src/*.c)\n"\
                            "OUTPUT := output\n\n"\
                            "RUN: BUILD\n"\
	                        "\t@$(OUTPUT)\n"\
                            "BUILD:\n"\
	                        "\t@gcc $(SRC) $(FLAGS) -o $(OUTPUT)\n"
#define C_GITIGNORE_TEMPLATE  "*.txt\n"\
                            "makefile"

const char *CPP_DIRS[] = {"include", "src", "lib"};
const char *CPP_FILES[] = {"makefile", ".gitignore", "README.md"};
const char *WEB_DIRS[] = {"assets\\css", "assets\\js", "assets\\img", "includes", "api", "sql"};
const char *WEB_FILES[] = {"index.php", "config.php", ".gitignore", "README.md", "includes\\header.php", "includes\\footer.php"};


bool createFolders(const char *path, int dirc, const char **dirv)
{
    for(int i = 0; i < dirc; ++i)
    {
        char pathBuffer[BUFFER_SIZE_MAX];
        snprintf(pathBuffer,
            BUFFER_SIZE_MAX,
            "%s%s%s",
            path, QWS_PATH_DELIMITER, dirv[i]
        );
        if(!QWS_CreateDirectory(pathBuffer)) return false;
    }

    return true;
}

bool createFiles(const char *path, int filec, const char **filev)
{
    for(int i = 0; i < filec; ++i)
    {
        char pathBuffer[BUFFER_SIZE_MAX];
        snprintf(pathBuffer,
            BUFFER_SIZE_MAX,
            "%s%s%s",
            path, QWS_PATH_DELIMITER, filev[i]
        );
        if(!QWS_CreateFile(pathBuffer)) return false;
    }

    return true;
}


bool cmd_new(QWS_Flags flags, int argc, char **argv)
{
    if(!QWS_CreateFolder(argv[PROJECT_NAME])) return false;

    char pathBuffer[BUFFER_SIZE_MAX];

    if(!strcmp(argv[PROJECT_TYPE], "c") || !strcmp(argv[PROJECT_TYPE], "c++") || !strcmp(argv[PROJECT_TYPE], "cpp"))
    {
        if(!createFolders(argv[PROJECT_NAME], sizeof(CPP_DIRS) / sizeof(*CPP_DIRS), CPP_DIRS)) return false;

        if(flags['d'])
        {   
            snprintf(pathBuffer, BUFFER_SIZE_MAX, "%s%s%s", argv[PROJECT_NAME], QWS_PATH_DELIMITER, CPP_FILES[0]);
            FILE *makefile = QWS_CreateFile(pathBuffer);
            if(!makefile) return false;
                fwrite(C_MAKEFILE_TEMPLATE, sizeof(char), strlen(C_MAKEFILE_TEMPLATE), makefile);
            fclose(makefile);

            snprintf(pathBuffer, BUFFER_SIZE_MAX, "%s%s%s", argv[PROJECT_NAME], QWS_PATH_DELIMITER, CPP_FILES[1]);
            FILE *gitignore = QWS_CreateFile(pathBuffer);
            if(!gitignore) return false;
                fwrite(C_GITIGNORE_TEMPLATE, sizeof(char), strlen(C_GITIGNORE_TEMPLATE), gitignore);
            fclose(gitignore);
        }
        else
            if(!createFiles(argv[PROJECT_NAME], sizeof(CPP_FILES) / sizeof(*CPP_FILES), CPP_FILES))
                return false;

        return true;
    }

    if(!strcmp(argv[PROJECT_TYPE], "web"))
    {
        if(!createFolders(argv[PROJECT_NAME], sizeof(WEB_DIRS) / sizeof(*WEB_DIRS), WEB_DIRS)) return false;
        if(!createFiles(argv[PROJECT_NAME], sizeof(WEB_FILES) / sizeof(*WEB_FILES), WEB_FILES)) return false;
        return true;
    }




    QWS_ErrorPush(QWS_ERROR_INVALID_ARGUMENT, argv[0]);
    return false;
}