EXT = cpp
CC = g++
DEBUG = no
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -g

ifeq ($(DEBUG),yes)
	CXXFLAGS := -g $(CXXFLAGS) -DDEBUG
endif
 
#Option de lien
LDFLAGS=

# Le nom de l'exécutable final
EXEC=CoCiX
 
# Les fichiers sont séparés dans des répertoires distincts.
SRCDIR=src
INCLUDEDIR=$(SRCDIR)/include
CLASSDIR=$(INCLUDEDIR)/class
ACTIONSDIR=$(CLASSDIR)/Actions
CORTEXDIR=$(CLASSDIR)/Cortex
OBJDIR=obj
BINDIR=bin
 
# Ici, vous pouvez exclure une liste de fichiers des sources.
# Ex. une acienne implémentation que vous ne voulez pas supprimer.
EXCLUDE=src/creer_monde.cpp src/cocixserv.cpp


# Ici, la liste de fichiers est construite
SRC  = $(wildcard src/include/class/Actions/*.cpp)
SRC  += $(wildcard src/include/class/Cortex/*.cpp)
SRC  += $(wildcard src/include/class/*.cpp)
SRC  += $(wildcard src/include/*.cpp)
SRC  += $(wildcard src/*.cpp)

SRC := $(filter-out $(EXCLUDE),$(SRC))

OBJ = $(SRC:%.cpp=%.o)
OBJ := $(notdir $(OBJ))
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


# La cible par défaut est all
default: $(EXEC)
 
# La cible all construit l'exécutable
all: $(EXEC) cocixserv creer_monde

# Ici, on indique les cibles qui ne génèrent pas de fichier
# et qui, par conséquent, doivent toujours être exécutées
.PHONY: help clean mrproper


# Affichage de l'aide
help:
	@ echo 'Makefile for ISIN project `CoCiX`'
	@ echo ''
	@ echo 'Usage :'
	@ echo 'make           Build project executable'
	@ echo 'make all       Build project executable'
	@ echo 'make clean     Clean objects directory'
	@ echo 'make mrproper  Remove objects and binaries directory'
	@ echo 'make help      Show this help message'
	@ echo ''
	@ echo '$(SRC)'
	@ echo '$(OBJ)'

#compilation src/
obj/%.o: src/%.cpp src/%.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

#compilation /src/include
obj/%.o: src/include/%.cpp src/include/%.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

#compilation /src/include/class/Cortex
obj/%.o: src/include/class/Cortex/%.cpp src/include/class/Cortex/%.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)


#compilation /src/include/class
obj/%.o: src/include/class/%.cpp src/include/class/%.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

#compilation /src/include/class/action
obj/%.o: src/include/class/Actions/%.cpp src/include/class/Actions/%.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)


#compilation src/main.cpp
obj/main.o: src/main.cpp
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

# Cible de construction de l'exécutable
$(EXEC): $(OBJ)
	@ [ -d $(BINDIR) ] || mkdir $(BINDIR)
	@ $(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
	@ [ -h $@ ] || ln -s $(BINDIR)/$@ $@

# Déclaration de a règle générique
# Si tous vos fichiers c/cpp n'ont pas de .h correspondant,
# vous pouvez enlever $(SRCDIR)/%.h des dépendances.
#$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
#	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
#	@ $(CC) -o $@ -c $< $(CFLAGS)

##Pour cocixserv
cocixserv: $(OBJDIR)/cocixserv.o $(OBJDIR)/JourNuit.o $(OBJDIR)/io.o
	@ [ -d $(BINDIR) ] || mkdir $(BINDIR)
	@ $(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
	@ [ -h $@ ] || ln -s $(BINDIR)/$@ $@

$(OBJDIR)/cocixserv.o: $(SRCDIR)/cocixserv.cpp
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

$(OBJDIR)/JourNuit.o: $(SRCDIR)/include/class/JourNuit.cpp
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

$(OBJDIR)/monde.o: $(SRCDIR)/include/monde.cpp
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

## Pour creer_monde
creer_monde: $(OBJDIR)/creer_monde.o $(OBJDIR)/io.o
	@ [ -d $(BINDIR) ] || mkdir $(BINDIR)
	@ $(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
	@ [ -h $@ ] || ln -s $(BINDIR)/$@ $@

$(OBJDIR)/creer_monde.o:  $(SRCDIR)/creer_monde.cpp
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

$(OBJDIR)/io.o: $(SRCDIR)/include/io.cpp $(SRCDIR)/include/constantes.h
	@ [ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	@$(CC) -o $@ -c $<  $(CXXFLAGS)

# Nettoyage du répertoire des objets
clean:
	@ rm -f $(OBJDIR)/*.o

# Suppression des répertoires des objets et des binaires
mrproper: clean
	@ rm -rf $(EXEC) $(OBJDIR) $(BINDIR)

depend:
	makedepend $(SRC) src/cocixserv.cpp src/creer_monde.cpp

# DO NOT DELETE

src/include/class/Actions/Cherche_Recolte.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Recolte.o: src/include/constantes.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Recolte.o: src/include/constantes.h
src/include/class/Actions/Cherche_Recolte.o: src/include/monde.h
src/include/class/Actions/Cherche_Recolte.o: src/include/constantes.h
src/include/class/Actions/Cherche_Recolte.o: src/include/io.h
src/include/class/Actions/Cherche_Recolte.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Actions/Cherche_Nourriture.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/constantes.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/constantes.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/monde.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/constantes.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/io.h
src/include/class/Actions/Cherche_Nourriture.o: src/include/class/Cocix.h
src/include/class/Actions/Recolter.o: src/include/class/Actions/Recolter.h
src/include/class/Actions/Recolter.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Recolter.o: src/include/monde.h
src/include/class/Actions/Recolter.o: src/include/constantes.h
src/include/class/Actions/Recolter.o: src/include/io.h
src/include/class/Actions/Recolter.o: src/include/class/Cocix.h
src/include/class/Actions/Recolter.o: src/include/class/Cocix.h
src/include/class/Actions/Recolter.o: src/include/constantes.h
src/include/class/Actions/Recolter.o: src/include/class/Gene.h
src/include/class/Actions/Recolter.o: src/include/class/Param_Etat.h
src/include/class/Actions/Recolter.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Recolter.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Recolter.o: src/include/constantes.h
src/include/class/Actions/Recolter.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Actions/Rentrer.o: src/include/class/Actions/Rentrer.h
src/include/class/Actions/Rentrer.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Rentrer.o: src/include/class/Cocix.h
src/include/class/Actions/Rentrer.o: src/include/constantes.h
src/include/class/Actions/Rentrer.o: src/include/class/Gene.h
src/include/class/Actions/Rentrer.o: src/include/class/Param_Etat.h
src/include/class/Actions/Rentrer.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Rentrer.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Rentrer.o: src/include/constantes.h
src/include/class/Actions/Rentrer.o: src/include/monde.h
src/include/class/Actions/Rentrer.o: src/include/constantes.h
src/include/class/Actions/Rentrer.o: src/include/io.h
src/include/class/Actions/Rentrer.o: src/include/class/Cocix.h
src/include/class/Actions/Pondre.o: src/include/class/Actions/Pondre.h
src/include/class/Actions/Pondre.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Pondre.o: /usr/include/stdio.h
src/include/class/Actions/Pondre.o: /usr/include/features.h
src/include/class/Actions/Pondre.o: /usr/include/stdc-predef.h
src/include/class/Actions/Pondre.o: /usr/include/libio.h
src/include/class/Actions/Pondre.o: /usr/include/_G_config.h
src/include/class/Actions/Pondre.o: /usr/include/wchar.h
src/include/class/Actions/Pondre.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Actions/Pondre.o: src/include/class/Cocix.h
src/include/class/Actions/Pondre.o: src/include/constantes.h
src/include/class/Actions/Pondre.o: src/include/class/Gene.h
src/include/class/Actions/Pondre.o: src/include/class/Param_Etat.h
src/include/class/Actions/Pondre.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Pondre.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Pondre.o: src/include/constantes.h
src/include/class/Actions/Pondre.o: src/include/class/JourNuit.h
src/include/class/Actions/Pondre.o: src/include/monde.h
src/include/class/Actions/Pondre.o: src/include/constantes.h src/include/io.h
src/include/class/Actions/Pondre.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Eau.o: src/include/constantes.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Eau.o: src/include/constantes.h
src/include/class/Actions/Cherche_Eau.o: src/include/monde.h
src/include/class/Actions/Cherche_Eau.o: src/include/constantes.h
src/include/class/Actions/Cherche_Eau.o: src/include/io.h
src/include/class/Actions/Cherche_Eau.o: src/include/class/Cocix.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Actions/Se_Soigner.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Actions/Rentrer.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Cocix.h
src/include/class/Actions/Se_Soigner.o: src/include/constantes.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Gene.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Param_Etat.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Se_Soigner.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Se_Soigner.o: src/include/constantes.h
src/include/class/Actions/Actions.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Actions.o: src/include/constantes.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Actions/Cherche_Malade.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Malade.o: src/include/constantes.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Malade.o: src/include/constantes.h
src/include/class/Actions/Cherche_Malade.o: src/include/monde.h
src/include/class/Actions/Cherche_Malade.o: src/include/constantes.h
src/include/class/Actions/Cherche_Malade.o: src/include/io.h
src/include/class/Actions/Cherche_Malade.o: src/include/class/Cocix.h
src/include/class/Actions/Manger.o: src/include/class/Actions/Manger.h
src/include/class/Actions/Manger.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Manger.o: src/include/monde.h
src/include/class/Actions/Manger.o: src/include/constantes.h src/include/io.h
src/include/class/Actions/Manger.o: src/include/class/Cocix.h
src/include/class/Actions/Manger.o: src/include/class/Actions/Cherche_Nourriture.h
src/include/class/Actions/Manger.o: src/include/class/Cocix.h
src/include/class/Actions/Manger.o: src/include/constantes.h
src/include/class/Actions/Manger.o: src/include/class/Gene.h
src/include/class/Actions/Manger.o: src/include/class/Param_Etat.h
src/include/class/Actions/Manger.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Manger.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Manger.o: src/include/constantes.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Actions/Se_Reproduire.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Se_Reproduire.o: src/include/monde.h
src/include/class/Actions/Se_Reproduire.o: src/include/constantes.h
src/include/class/Actions/Se_Reproduire.o: src/include/io.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Cocix.h
src/include/class/Actions/Se_Reproduire.o: src/include/reproduction.h
src/include/class/Actions/Se_Reproduire.o: src/include/reproduction.h
src/include/class/Actions/Se_Reproduire.o: src/include/monde.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Cocix.h
src/include/class/Actions/Se_Reproduire.o: src/include/constantes.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Gene.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Param_Etat.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Se_Reproduire.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Se_Reproduire.o: src/include/constantes.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/constantes.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/constantes.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/reproduction.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/reproduction.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/constantes.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/monde.h
src/include/class/Actions/Cherche_Partenaire.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Cocix.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/constantes.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Gene.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Param_Etat.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/constantes.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/monde.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/constantes.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/io.h
src/include/class/Actions/Cherche_Case_Libre.o: src/include/class/Cocix.h
src/include/class/Actions/Boire.o: src/include/class/Actions/Boire.h
src/include/class/Actions/Boire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Boire.o: src/include/class/Cocix.h
src/include/class/Actions/Boire.o: src/include/constantes.h
src/include/class/Actions/Boire.o: src/include/class/Gene.h
src/include/class/Actions/Boire.o: src/include/class/Param_Etat.h
src/include/class/Actions/Boire.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Boire.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Boire.o: src/include/constantes.h
src/include/class/Actions/Boire.o: src/include/monde.h
src/include/class/Actions/Boire.o: src/include/constantes.h src/include/io.h
src/include/class/Actions/Boire.o: src/include/class/Cocix.h
src/include/class/Actions/Boire.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Actions/Dormir.o: src/include/class/Actions/Dormir.h
src/include/class/Actions/Dormir.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Soigner.o: src/include/class/Actions/Soigner.h
src/include/class/Actions/Soigner.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Soigner.o: src/include/monde.h
src/include/class/Actions/Soigner.o: src/include/constantes.h
src/include/class/Actions/Soigner.o: src/include/io.h
src/include/class/Actions/Soigner.o: src/include/class/Cocix.h
src/include/class/Actions/Soigner.o: src/include/class/Actions/Cherche_Malade.h
src/include/class/Actions/Soigner.o: src/include/class/Cocix.h
src/include/class/Actions/Soigner.o: src/include/constantes.h
src/include/class/Actions/Soigner.o: src/include/class/Gene.h
src/include/class/Actions/Soigner.o: src/include/class/Param_Etat.h
src/include/class/Actions/Soigner.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Soigner.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Soigner.o: src/include/constantes.h
src/include/class/Actions/Deposer.o: src/include/class/Actions/Deposer.h
src/include/class/Actions/Deposer.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Deposer.o: src/include/class/Actions/Rentrer.h
src/include/class/Actions/Deposer.o: src/include/class/Cocix.h
src/include/class/Actions/Deposer.o: src/include/constantes.h
src/include/class/Actions/Deposer.o: src/include/class/Gene.h
src/include/class/Actions/Deposer.o: src/include/class/Param_Etat.h
src/include/class/Actions/Deposer.o: src/include/class/Actions/Actions.h
src/include/class/Actions/Deposer.o: src/include/class/Cortex/Cortex.h
src/include/class/Actions/Deposer.o: src/include/constantes.h
src/include/class/Actions/Deposer.o: src/include/monde.h
src/include/class/Actions/Deposer.o: src/include/constantes.h
src/include/class/Actions/Deposer.o: src/include/io.h
src/include/class/Actions/Deposer.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Cortex/Cortex_Oeuf.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Oeuf.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Cortex/Cortex_Adulte_Femelle.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Cortex/Cortex_Adulte.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: /usr/include/math.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: /usr/include/features.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: /usr/include/stdc-predef.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Boire.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Deposer.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Dormir.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Manger.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Pondre.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Recolter.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Rentrer.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Se_Reproduire.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Se_Soigner.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Soigner.h
src/include/class/Cortex/Cortex_Adulte_Femelle.o: src/include/class/Actions/Cherche_Malade.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Cortex/Cortex_Adulte_Male.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Cortex/Cortex_Adulte.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte_Male.o: /usr/include/math.h
src/include/class/Cortex/Cortex_Adulte_Male.o: /usr/include/features.h
src/include/class/Cortex/Cortex_Adulte_Male.o: /usr/include/stdc-predef.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Boire.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Deposer.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Dormir.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Manger.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Pondre.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Recolter.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Rentrer.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Se_Reproduire.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Se_Soigner.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Soigner.h
src/include/class/Cortex/Cortex_Adulte_Male.o: src/include/class/Actions/Cherche_Malade.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Cortex/Cortex_Bebe.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Bebe.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Cortex/Cortex_Adulte.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/constantes.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Actions/Dormir.h
src/include/class/Cortex/Cortex_Adulte.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex.o: src/include/constantes.h
src/include/class/Cortex/Cortex.o: src/include/class/Cocix.h
src/include/class/Cortex/Cortex.o: src/include/constantes.h
src/include/class/Cortex/Cortex.o: src/include/class/Gene.h
src/include/class/Cortex/Cortex.o: src/include/class/Param_Etat.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex.o: src/include/class/Cortex/Cortex.h
src/include/class/Cortex/Cortex.o: src/include/class/JourNuit.h
src/include/class/Cortex/Cortex.o: /usr/include/math.h
src/include/class/Cortex/Cortex.o: /usr/include/features.h
src/include/class/Cortex/Cortex.o: /usr/include/stdc-predef.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Boire.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Actions.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Deposer.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Dormir.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Manger.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Pondre.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Recolter.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Rentrer.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Se_Reproduire.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Se_Soigner.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Soigner.h
src/include/class/Cortex/Cortex.o: src/include/class/Actions/Cherche_Malade.h
src/include/class/Param_Etat.o: src/include/class/Param_Etat.h
src/include/class/Param_Etat.o: src/include/constantes.h
src/include/class/Param_Etat.o: src/include/class/Gene.h
src/include/class/Gene.o: src/include/class/Gene.h src/include/constantes.h
src/include/class/JourNuit.o: /usr/include/time.h /usr/include/features.h
src/include/class/JourNuit.o: /usr/include/stdc-predef.h
src/include/class/JourNuit.o: /usr/include/xlocale.h src/include/constantes.h
src/include/class/JourNuit.o: src/include/class/JourNuit.h
src/include/class/Cocix.o: src/include/class/Gene.h src/include/class/Cocix.h
src/include/class/Cocix.o: src/include/constantes.h
src/include/class/Cocix.o: src/include/class/Param_Etat.h
src/include/class/Cocix.o: src/include/class/Actions/Actions.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex.h
src/include/class/Cocix.o: src/include/constantes.h src/include/class/Cocix.h
src/include/class/Cocix.o: src/include/class/JourNuit.h src/include/monde.h
src/include/class/Cocix.o: src/include/constantes.h src/include/io.h
src/include/class/Cocix.o: src/include/class/Cocix.h
src/include/class/Cocix.o: src/include/reproduction.h
src/include/class/Cocix.o: src/include/reproduction.h src/include/monde.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex_Adulte_Male.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex_Adulte.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex_Adulte_Femelle.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex_Oeuf.h
src/include/class/Cocix.o: src/include/class/Cortex/Cortex_Bebe.h
src/include/class/Cocix.o: src/include/class/Actions/Boire.h
src/include/class/Cocix.o: src/include/class/Actions/Actions.h
src/include/class/Cocix.o: src/include/class/Actions/Cherche_Eau.h
src/include/class/Cocix.o: src/include/class/Actions/Deposer.h
src/include/class/Cocix.o: src/include/class/Actions/Dormir.h
src/include/class/Cocix.o: src/include/class/Actions/Manger.h
src/include/class/Cocix.o: src/include/class/Actions/Pondre.h
src/include/class/Cocix.o: src/include/class/Actions/Recolter.h
src/include/class/Cocix.o: src/include/class/Actions/Cherche_Recolte.h
src/include/class/Cocix.o: src/include/class/Actions/Rentrer.h
src/include/class/Cocix.o: src/include/class/Actions/Se_Reproduire.h
src/include/class/Cocix.o: src/include/class/Actions/Se_Soigner.h
src/include/class/Cocix.o: src/include/class/Actions/Cherche_Partenaire.h
src/include/class/Cocix.o: src/include/class/Actions/Cherche_Case_Libre.h
src/include/class/Cocix.o: src/include/class/Actions/Soigner.h
src/include/class/Cocix.o: src/include/class/Actions/Cherche_Malade.h
src/include/reproduction.o: src/include/reproduction.h
src/include/reproduction.o: src/include/constantes.h src/include/monde.h
src/include/reproduction.o: src/include/io.h src/include/class/Cocix.h
src/include/reproduction.o: src/include/class/JourNuit.h
src/include/reproduction.o: src/include/class/Actions/Dormir.h
src/include/reproduction.o: src/include/class/Actions/Actions.h
src/include/io.o: /usr/include/stdio.h /usr/include/features.h
src/include/io.o: /usr/include/stdc-predef.h /usr/include/libio.h
src/include/io.o: /usr/include/_G_config.h /usr/include/wchar.h
src/include/io.o: /usr/include/stdlib.h /usr/include/alloca.h
src/include/io.o: /usr/include/time.h /usr/include/xlocale.h
src/include/io.o: /usr/include/math.h /usr/include/dirent.h src/include/io.h
src/include/io.o: src/include/constantes.h
src/include/monde.o: src/include/constantes.h src/include/monde.h
src/include/monde.o: src/include/io.h src/include/class/Cocix.h
src/main.o: src/include/class/Cocix.h src/include/constantes.h
src/main.o: src/include/class/Gene.h src/include/class/Param_Etat.h
src/main.o: src/include/class/Actions/Actions.h
src/main.o: src/include/class/Cortex/Cortex.h src/include/constantes.h
src/main.o: src/include/class/Cocix.h src/include/class/JourNuit.h
src/main.o: src/include/class/Actions/Actions.h
src/main.o: src/include/class/Actions/Dormir.h
src/main.o: src/include/class/Actions/Actions.h
src/main.o: src/include/class/Actions/Manger.h
src/main.o: src/include/class/Actions/Boire.h
src/main.o: src/include/class/Actions/Cherche_Eau.h
src/main.o: src/include/class/Actions/Cherche_Nourriture.h
src/main.o: src/include/class/Actions/Rentrer.h
src/main.o: src/include/class/Actions/Se_Soigner.h
src/main.o: src/include/class/Actions/Recolter.h
src/main.o: src/include/class/Actions/Cherche_Recolte.h
src/main.o: src/include/class/Actions/Deposer.h
src/main.o: src/include/class/Actions/Se_Reproduire.h
src/main.o: src/include/class/Actions/Cherche_Partenaire.h
src/main.o: src/include/class/Actions/Cherche_Case_Libre.h
src/main.o: src/include/class/Actions/Pondre.h
src/main.o: src/include/class/Actions/Soigner.h
src/main.o: src/include/class/Actions/Cherche_Malade.h
src/main.o: src/include/constantes.h src/include/io.h
src/main.o: src/include/constantes.h src/include/monde.h src/include/io.h
src/main.o: src/include/class/Cocix.h
src/cocixserv.o: src/include/constantes.h src/include/class/JourNuit.h
src/creer_monde.o: /usr/include/time.h /usr/include/features.h
src/creer_monde.o: /usr/include/stdc-predef.h /usr/include/xlocale.h
src/creer_monde.o: /usr/include/math.h src/include/constantes.h
src/creer_monde.o: src/include/io.h src/include/constantes.h
src/creer_monde.o: src/include/monde.h src/include/io.h
src/creer_monde.o: src/include/class/Cocix.h
