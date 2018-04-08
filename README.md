# TimeSync
Simple program to sync client time with server time using Java and Java Native Interface

It works by sending a HTTP request to a server that just gives back the time in the following
format: dd.MM.YYYY HH:mm:ss. And then by using JNI I can set the date and time of the
operating system platform independently.

## Before you start
- Edit the first three lines of the Makefile to set the correct include paths for JNI
- Edit line 17 with the absolute path to this repository + build/setdate.(dll / so)

