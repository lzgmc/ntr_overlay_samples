#define IS_PLUGIN 1
#define USE_SOCKET 0

#include "main.h"
#include "memory.h"
#include "math.h"
#include "3dstypes.h"
#include "constants.h"
#include "xprintf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctr/types.h>
#include <ctr/srv.h>
#include <ctr/APT.h>
#include <ctr/GSP.h>
#include <ctr/GX.h>
#include <ctr/HID.h>
#include <ctr/FS.h>
#include <ctr/svc.h>
#include <ctr/soc.h>

#include "func.h"
#include "sharedfunc.h"
#include "ns/ns.h"
#include <sys/socket.h>
#include "ui.h"

enum 
{
    CLOCK_ONLY = 1,
    CLOCK_BATTERY = 1 << 2,
    CLOCK_BOTTOM = 1 << 3,
};