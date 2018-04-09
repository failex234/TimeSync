cc=gcc
jniwin=C:\\Program\ Files\\Java\\jdk-9.0.1\\include
jniextrawin=C:\\Program\ Files\\Java\\jdk-9.0.1\\include\\win32
jnilinux=/usr/lib/jvm/java-8-openjdk/include
jniextralinux=/usr/lib/jvm/java-8-openjdk/include/linux

all:
	@echo "please run \"make windows\" or \"make linux\""

windows:
	make clean
	mkdir build
	@echo "Remember to set library location in line 17 in TimeSync.java!!! (It needs an absolute path)"
	@echo "Press any key to continue..."
	@read temp
	$(cc) -I $(jniwin) -I $(jniextrawin) -shared -W -o build/setdate.dll src/de/failex/timesync/setdate.c
	javac -d build/ src/de/failex/timesync/TimeSync.java
	mv build/de/failex/timesync/TimeSync.class build/
	rm -rf build/de
linux:
	make clean
	mkdir build
	@echo "Remember to set library location in line 17 in TimeSync.java!!! (It needs an absolute path)"
	@echo "Press any key to continue..."
	@read temp
	$(cc) -I $(jnilinux) -I $(jniextralinux) -shared -W -o build/setdate.so src/de/failex/timesync/setdate.c
	javac -d build src/de/failex/timesync/TimeSync.java
	mv build/de/failex/timesync/TimeSync.class build/
	rm -rf build/de

clean:
	rm -rf build/
