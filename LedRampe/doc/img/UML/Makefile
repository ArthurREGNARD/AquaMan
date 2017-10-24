# Manipulation de fichier
RM = rm -rf
CP = cp
MV = mv
CD = cd

# Definition des repertoire de travail
SRCDIR = src
BUILDDIR = img

# Definition des extentions de fichier compile
EXTFILE = png svg

PLANTUML=plantuml

VIEWER=eog

EXEC=convert view

all: $(EXEC)

convert: plantUML
	$(CD) $(BUILDDIR) && make

plantUML: clean
	$(foreach element, $(EXTFILE), (($(PLANTUML) -t$(element) $(SRCDIR)/*.txt -o ../$(BUILDDIR)) || ($(MAKE) cleanAll; exit 1));)

view:
	$(VIEWER) $(BUILDDIR)/*.jpg &


.PHONY: clean mrproper

clean:
	$(foreach element, $(EXTFILE), $(RM) $(BUILDDIR)/*.$(element));
	$(CD) $(BUILDDIR) && make clean

mrproper: clean
	rm -rf $(EXEC)