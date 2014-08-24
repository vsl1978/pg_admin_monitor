#include "postgres.h"
#include "fmgr.h"
#include <sys/statvfs.h>
#include <stdio.h>

PG_MODULE_MAGIC;

Datum admin_diskfree(PG_FUNCTION_ARGS);
Datum admin_diskfreebytes(PG_FUNCTION_ARGS);
Datum admin_loadavg(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(admin_diskfree);
PG_FUNCTION_INFO_V1(admin_diskfreebytes);
PG_FUNCTION_INFO_V1(admin_loadavg);

Datum admin_diskfree(PG_FUNCTION_ARGS) 
{
    struct statvfs sb;
    char *path = PG_GETARG_CSTRING(0);
    int64 avail = -1;
    if (statvfs(path, &sb) != -1) {
	avail  = sb.f_bavail;
	avail *= sb.f_frsize;
	avail /= 1024;
    }
    PG_RETURN_INT64(avail);
}

Datum admin_diskfreebytes(PG_FUNCTION_ARGS) 
{
    struct statvfs sb;
    char *path = PG_GETARG_CSTRING(0);
    int64 avail = -1;
    if (statvfs(path, &sb) != -1) {
	avail  = sb.f_bavail;
	avail *= sb.f_frsize;
    }
    PG_RETURN_INT64(avail);
}

Datum admin_loadavg(PG_FUNCTION_ARGS) 
{
    FILE *f;
    float4 la1;
    float4 la5;
    float4 la15;

    f = fopen("/proc/loadavg", "r");
    fscanf(f, "%f\t%f\t%f", &la1, &la5, &la15);
    fclose(f);

    int4 n = PG_GETARG_INT32(0);

    if (n == 0)
	PG_RETURN_FLOAT4(la1);
    if (n == 1)
	PG_RETURN_FLOAT4(la5);
    if (n == 2)
	PG_RETURN_FLOAT4(la15);
    PG_RETURN_NULL();
}
