# This makefile is intended to build the nine programs for
# computer dating application.
#
# Created by Jiajia      Bai   	     (Jia)    ID 63070503404
#	     Sonia       Gautam      (Sonia)  ID 63070503410
#	     Tamonwan    Boonpa      (Nice)   ID 63070503418
#            Theeranont  Ruchiyakorn (Peak)   ID 63070503420
#
# 18 April 2021
#

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES = datingApp

all : $(EXECUTABLES)

tree.o : tree.c datingApp.h
	gcc -c tree.c

findMatch.o : findMatch.c datingApp.h 
	gcc -c findMatch.c

addProfile.o : addProfile.c datingApp.h abstractHashTable.h
	gcc -c addProfile.c

editProfile.o : editProfile.c datingApp.h abstractHashTable.h
	gcc -c editProfile.c

validateData.o : validateData.c datingApp.h
	gcc -c validateData.c

userInterface.o : userInterface.c datingApp.h
	gcc -c userInterface.c

readWriteData.o : readWriteData.c datingApp.h abstractHashTable.h
	gcc -c readWriteData.c

loginRegister.o : loginRegister.c datingApp.h abstractHashTable.h
	gcc -c loginRegister.c

chainedHashTableMod.o :	chainedHashTableMod.c abstractHashTable.h
	gcc -c chainedHashTableMod.c

datingApp : tree.o findMatch.o addProfile.o editProfile.o validateData.o userInterface.o readWriteData.o loginRegister.o chainedHashTableMod.o
	gcc -o datingApp userInterface.o readWriteData.o loginRegister.o chainedHashTableMod.o \
			 validateData.o tree.o addProfile.o editProfile.o findMatch.o

clean :
	-rm *.o
	-rm datingApp
