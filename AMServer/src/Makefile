# *******************************************************************************
# * @file	AquaMan C - Makefile principal
# *
# * @brief	Code of test
# * @version	0.01
# * @date	1 Fevrier 2017
# * @author	Arthur REGNARD
# * @copyright	copyright BSD 2-clauses
# *******************************************************************************

# * * * * * * * * * *
# * Organization of sources.
# * * * * * * * * * *

# Packages.
PACKAGES +=	test

# Three levels of packages are available
SRC += $(wildcard */*.c)	
SRC += $(wildcard */*/*.c)
SRC += $(wildcard */*/*/*.c)


OBJ = $(SRC:.c=.o)

# Program entry point
MAIN = Main.c

# Inclusion since the package level
CCINCLUDE += -I.

#
# Makefile rules
#

# Compiler
all:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done
	$(CC) $(CCFLAGS) $(CCINCLUDE) $(OBJ) $(MAIN) -o $(EXEC) $(LDFLAGS) $(CCDEBUG)

# Cleaning
clean:
	@for p in $(PACKAGES); do (cd $$p; $(MAKE) $@); done

