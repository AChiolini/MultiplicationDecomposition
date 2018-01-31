CC := g++
CFLAGS := -std=c++11
TARGET := main
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SRCS := $(call rwildcard, , *.cpp) 

all:
	$(CC) -o main $(CFLAGS) $(SRCS)
