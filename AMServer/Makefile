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
# * Chemin vers le compiler.
# * * * * * * * * * *
RPICOMP = /home/regnard/RPI/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/

# * * * * * * * * * *
# * Raspberry IP adress.
# * * * * * * * * * *
IP_ADRESS_RASPBERRY = 192.168.20.1

# * * * * * * * * * *
# * Organisation des sources.
# * * * * * * * * * *
export SRCDIR = src
export BINDIR = bin
export DOCDIR = doc

SUBDIRS = $(SRCDIR)

# * * * * * * * * * *
# * Manipulation de fichiers.
# * * * * * * * * * *
export RM = rm -f
export MV = mv
export CP = cp
export SCP = scp

# * * * * * * * * * *
# * Compilateur.
# * * * * * * * * * *

ifeq ($(TARGET), native)
	# pour le pc de dev.
	export CC =		gcc
	export CCDEFINE =	-DNATIVE
	export LDFLAGS =	
	export CCINCLUDE =	
else
	# pour la cible.
	export CC =		$(RPICOMP)bin/arm-linux-gnueabihf-gcc
	export CCDEFINE +=	
	export LDFLAGS +=	-L$(RPICOMP)arm-linux-gnueabihf/libc/usr/lib 
	export LDFLAGS +=	-L$(RPICOMP)arm-linux-gnueabihf/lib
	export CCINCLUDE += 	-I$(RPICOMP)arm-linux-gnueabihf/libc/usr/include/
endif

# * * * * * * * * * *
# * Dans tous les cas.
# * * * * * * * * * *
export CCOPTIM +=	-O0

export CCDEBUG +=	-g
export CCDEBUG +=	-DDEBUG # -DNDEBUG 

export CCDEFINE +=	-D_REENTRANT 
export CCDEFINE +=	-D_BSD_SOURCE
export CCDEFINE +=	-D_XOPEN_SOURCE_EXTENDED
export CCDEFINE +=	-D_XOPEN_SOURCE
export CCDEFINE +=	-D_GNU_SOURCE
#export CCDEFINE +=	$(DEFINE_TEST)

export CCFLAGS +=	$(CCOPTIM)
export CCFLAGS +=	$(CCDEBUG)
export CCFLAGS +=	$(CCDEFINE)
export CCFLAGS +=	-std=c99
export CCFLAGS +=	-Wall
export CCFLAGS +=	-pedantic

export LDFLAGS +=	-lm
export LDFLAGS +=	-lrt
export LDFLAGS +=	-lpthread
#export LDFLAGS +=	-lsqlite3
#export LDFLAGS +=	-lwiringPi

# * * * * * * * * * *
# * Définitions des binaires à générer.
# * * * * * * * * * *
ifeq ($(TARGET), native)
	# pour le pc de développement.
	export EXEC = raspberry_native
else
	# pour la cible.
	export EXEC = AMServer
endif

EXECUTABLE = $(EXEC)

#
# Règles du Makefile.
#

# Compilation.
all: 
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) $@); done
	@for i in $(EXECUTABLE); do ($(MAKE) $$i); done

$(EXEC):
	@$(MV) $(SRCDIR)/$(EXEC) $(BINDIR)/$(EXEC)

		
# Nettoyage.
clean:
	@for i in $(EXECUTABLE); do ($(RM) $(BINDIR)/$$i core* $(BINDIR)/core*); done
	@$(RM) -r $(DOC)
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) $@); done
	
send_to_cible:
	@for i in $(EXECUTABLE); do ($(SCP) ./$(BINDIR)/$$i pi@$(IP_ADRESS_RASPBERRY):/home/pi/ProSE); done
