# Makefile de compilation des sources LaTeX.
#
# Description :
# 	Ce makefile permet de compiler du code LaTeX de façon suffisamment générique
# 	pour être utilisé pour la production de documents.
#
# 	Options du Makefile :
#		- view			: Compilation, génération d'un pdf et visionnage du pdf.
# 		- pdf			: Génération du dvi et transformation en pdf.
#		- dvi			: Compilation des sources LaTeX et génération du dvi.
#		- clean 		: Nettoyage des sources sans le PDF.
# 		- cleanall		: Nettoyage des sources dont le PDF.
#		- cleanPlantUML	: Nettoyage des sources généré par PlantUML. 
#		- plantUMLeps	: Compilation des sources plantUML et génération d'image format ".eps". 
#		- plantUMLsvg	: Compilation des sources plantUML et génération d'image format ".svg".
# 		- new			: Combinaison de dvi pdf clean.
# 		- newView		: Combinaison de dvi pdf view clean.
# 		- all			: Combinaison de cleanall cleanPlantUML plantUMLeps dvi pdf view clean.
#
# Auteur      : Arthur REGNARD(arthur.regnard@reseau.eseo.fr)
#
# Version     : 1.0
# Date        : 01/03/2016
# Commentaire : Commande de base pour compiler les sources LaTeX et PlantUML.
#
# Nom du logiciel de visionnage de pdf
# Exemples Linux : acroread, evince.
# Exemples MacOs : open -a Preview
ifeq ($(OS),Windows_NT)
    UNAME := Windows
else
    UNAME := $(shell uname -s)
endif
ifeq ($(UNAME),Linux)
	VIEWER=pdfcube -n
endif
ifeq ($(UNAME),Darwin)
	VIEWER=open -a Preview
endif
ifeq ($(UNAME),Windows)
	VIEWER="C:\Program Files (x86)\Adobe\Acrobat Reader DC\Reader\AcroRd32.exe"
endif

CURRENTPATH=C:/Users/Arthur REGNARD/Documents/LaTex/FoxyLife
IMGSOURCEDIR=img/UML/img

MYDIR=./$(IMGSOURCEDIR)
# Repertoire ou est stoqué l'enssemble des fichier de compilation. 
TMPDIR=tmp
IMGDIR = img

# Manipulation de fichier
RM = rm -rf
CD = cd
CP = cp
MV = mv

# Nom du logiciel de génération de pdf a partir d'un fichier ".dvi"
DVI2PDF=dvipdfm
PDFLATEX=pdflatex

# Nom du document pdf généré.
FILE=Document
#FILE:= $(filter-out view pdf dvi clean cleanall cleanPlantUML plantUMLeps plantUMLsvg new newView all,$(MAKECMDGOALS))

# Fichiers concernés par la compilation.
TEX=$(FILE).tex
PDF=$(FILE).pdf

EXTcompilFILE = toc out log lof blg bbl aux glg glo gls glsdefs ist acn acr alg def nlg ntn

# Générer le pdf et l'ouvrir dans le visionneur pdf.
view: $(PDF)
	$(VIEWER) $(PDF) &

# Génération du dvi et transformation en pdf.
pdf: $(TEX) 
	$(CD) $(IMGDIR) && make;
	(pdflatex $(FILE) && makeglossaries $(FILE) && pdflatex $(FILE) && pdflatex $(FILE)) || ($(MAKE) clean; exit 1)
# -aux-directory=$(TMPDIR)
# && bibtex $(AUX)  - A integrer apres la premiere compilation latex, pour introduire une bibliographie. 
# && makeglossaries $(FILE)  - A integrer apres la premiere compilation latex, pour introduire un glossaire.

# Nettoyage des sources.
clean:
	$(foreach element, ${EXTcompilFILE}, $(MV) *.$(element) $(TMPDIR))

cleanall:
	$(RM) $(TMPDIR)\*.* $(PDF);
	$(CD) $(IMGDIR) && make clean

mrproper: cleanall
	$(RM) $(EXEC)


# Nettoyage des sources, génération d'un nouveau pdf et visionnage de celui-ci.
new : pdf clean

newView : pdf view clean

all : cleanall pdf view clean

.PHONY: clean cleanall