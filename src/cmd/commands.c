#include "qws_command.h"


QWS_Command QWS_CommandMap[QWS_COMMAND_COUNT] = 
{
    {"create", "t", 1, 1, cmd_create},
    {"new", "d", 2, 2, cmd_new}
};