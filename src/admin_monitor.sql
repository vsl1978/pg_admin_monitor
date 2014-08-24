create or replace function pg_catalog.admin_diskfreebytes(cstring) returns bigint as 'admin_monitor', 'admin_diskfreebytes' LANGUAGE C VOLATILE STRICT;
create or replace function pg_catalog.admin_diskfree(cstring) returns bigint as 'admin_monitor', 'admin_diskfree' LANGUAGE C VOLATILE STRICT;
create or replace function pg_catalog.admin_loadavg(integer) returns real as 'admin_monitor', 'admin_loadavg' LANGUAGE C VOLATILE STRICT;
