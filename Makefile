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
OBJDIR=obj
BINDIR=bin
 
# Ici, vous pouvez exclure une liste de fichiers des sources.
# Ex. une acienne implémentation que vous ne voulez pas supprimer.
EXCLUDE=src/creer_monde.cpp src/cocixserv.cpp


# Ici, la liste de fichiers est construite
SRC  = $(wildcard src/include/class/Actions/*.cpp)
SRC  += $(wildcard src/include/class/*.cpp)
SRC  += $(wildcard src/include/*.cpp)
SRC  += $(wildcard src/*.cpp)

SRC := $(filter-out $(EXCLUDE),$(SRC))

OBJ = $(SRC:%.cpp=%.o)
OBJ := $(notdir $(OBJ))
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


# La cible par défaut est all
default: all
 
# La cible all construit l'exécutable
all: $(EXEC)

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
cocixserv: $(OBJDIR)/cocixserv.o $(OBJDIR)/JourNuit.o $(OBJDIR)/monde.o $(OBJDIR)/io.o
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
	makedepend $(SRC)
# DO NOT DELETE

obj/Boire.o: src/include/class/Actions/Boire.cpp src/include/class/Actions/Boire.h
obj/Boire.o: src/include/class/Actions/Actions.h
obj/Boire.o: src/include/class/Cocix.h
obj/Boire.o: src/include/constantes.h
obj/Boire.o: src/include/class/Gene.h
obj/Boire.o: src/include/class/Param_Etat.h
obj/Boire.o: src/include/class/Actions/Actions.h
obj/Boire.o: src/include/monde.h
obj/Boire.o: src/include/constantes.h src/include/io.h
obj/Boire.o: src/include/class/Actions/Cherche_Eau.h
obj/Dormir.o: src/include/class/Actions/Dormir.h
obj/Dormir.o: src/include/class/Actions/Actions.h

obj/Manger.o: src/include/monde.h