# Manipulation de fichier
RM = rm -rf
CD = cd

EXT_FILE_SRC = png eps
EXT_FILE_BUI = jpg

UMLDIR = UML

EXEC=convert plantUML

all: $(EXEC)

plantUML:
	$(CD) $(UMLDIR) && make

convert:
	$(foreach element, $(EXT_FILE_SRC), -mogrify -format $(EXT_FILE_BUI) *.$(element); )

clean:
	$(CD) $(UMLDIR) && make clean