cc=gcc
jni=C:\\Program\ Files\\Java\\jdk-9.0.1\\include
jniextra=C:\\Program\ Files\\Java\\jdk-9.0.1\\include\\win32

all:
	mkdir build
	@echo "Remember to set library location in line 17 in TimeSync.java!!! (It needs an absolute path)"
	@echo "Press any key to continue..."
	@read temp
	$(cc) -I $(jni) -I $(jniextra) -o build/setdate src/de/failex/timesync/setdate.c
	javac -d build/ src/de/failex/timesync/setdate.c
	mv build/de/failex/timesync/setdate.class build/
	rm -rf build/de
