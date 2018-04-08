# TimeSync
Simple program to sync client time with server time using Java and Java Native Interface

It works by sending a HTTP request to a server that just gives back the time in the following
format: dd.MM.YYYY HH:mm:ss. And then by using JNI I can set the date and time of Windows or 
GNU/Linux (Technically it should also work on other UNIX-derivates and \*nix likes).
The compiler will detect your OS and will then compile the right code for your OS.

## Before you start
- Edit the first three lines of the Makefile to set the correct include paths for JNI
- Edit line 17 with the absolute path to this repository + build/setdate.(dll / so)

## Build instructions
If you don't want to use the Makefile for whatever reason you can build the project like this:

- Compile setdate.c as a library
- Change line 17 in TimeSync.java to the absolute path to the compiled library
- Compile java code
- Run java class

## Dependencies
None except for GNU/Linux you'll need the kernel headers.
