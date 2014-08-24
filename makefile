cc=cc
VERSION=`sed -nr 's/^.*default_version.*=[^0-9]*([0-9.]++).*/\1/p' src/admin_monitor.control`
ARCH=`uname -i`

all : target/admin_monitor.so target/admin_monitor.control
	cd target; tar -czf pg_admin_monitor_linux_$(ARCH).tgz admin_monitor.so *.sql *.control
	cd target; zip pg_admin_monitor_linux_$(ARCH).zip admin_monitor.so *.sql *.control

target/admin_monitor.control :
	cp src/admin_monitor.sql target/admin_monitor--$(VERSION).sql
	cp src/admin_monitor.control target/admin_monitor.control

target/admin_monitor.so : target/admin_monitor.o
	$(cc) -shared -L`pg_config --pkglibdir` -lpq -o target/admin_monitor.so target/admin_monitor.o
    
target/admin_monitor.o :
	mkdir target 2>/dev/null
	$(cc) -I`pg_config --includedir-server` -fpic -c src/admin_monitor.c -o target/admin_monitor.o
    
clean :
	rm -f target/* 2>/dev/null
	rmdir target

    