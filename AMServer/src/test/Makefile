# *******************************************************************************
# * @file	AquaMan C - Makefile principal
# *
# * @brief	Code of test
# * @version	0.01
# * @date	1 Fevrier 2017
# * @author	Arthur REGNARD
# * @copyright	copyright BSD 2-clauses
# *******************************************************************************

#
# Organization of sources
#

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

# Inclusion since the package level
CCINCLUDE += -I../

#
# Makefile rules
#

# Compiler
all: $(OBJ)

.c.o:
	$(CC) -c $(CCFLAGS) $(CCINCLUDE) $(CCDEBUG) $< -o $@
	
# Cleaning
clean:
	@$(RM) $(OBJ)
