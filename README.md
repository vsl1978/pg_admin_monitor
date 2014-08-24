pg_admin_monitor
================

**How to install:**

1. Copy .so file to pkglibdir:  
   cp admin_monitor.so $(pg_config --pkglibdir)
2. Create PostgreSQL functions using admin_monitor--1.0.sql


**How to use:**

- select admin_diskfree('/') as root_free_space_kb;
- select admin_diskfreebytes('/var/lib/pgsql/bigdata') as mounted_free_space;
- select admin_loadavg(0) as la_1minute, admin_loadavg(1) as la_5minutes, admin_loadavg(2) as la_15minutes;
```
 la_1minute | la_5minutes | la_15minutes
------------+-------------+--------------
        2.1 |        1.77 |          1.5
(1 row)
```