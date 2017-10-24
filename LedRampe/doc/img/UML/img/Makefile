# Manipulation de fichier
RM = rm -rf

EXT_FILE_SRC = png
EXT_FILE_BUI = jpg

EXEC=convert

all: $(EXEC)

convert: clean
	$(foreach element, $(EXT_FILE_SRC), -mogrify -format $(EXT_FILE_BUI) *.$(element); )

clean:
	$(RM) *.$(EXT_FILE_BUI)