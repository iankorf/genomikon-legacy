######################
# Makefile for Geney #
######################

LIB = -L.. -lgenomikon -lm -lsqlite3
INC = -I..
CC = gcc
CFLAGS = -O2 -Wall -Werror

#OBJECTS = \

APP = geney
SRC = geney.c
OBJ = geney.o

###########
# Targets #
###########

default:
	make gcc

$(APP): $(OBJ) $(OBJECTS)
	$(CC) -o $(APP) $(OBJ) $(OBJECTS) $(LIB)

test: $(APP)
	perl test.pl

clean:
	rm -f *.o $(APP)

#################
# Architectures #
#################

gcc:
	make $(APP)


###################
# Inference Rules #
###################

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<



