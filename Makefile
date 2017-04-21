# Variables
BUILD = build/cmake
EXEC  = run

VALGRIND_SUPPS = $(patsubst %,--suppressions=$(shell pwd)/%,$(wildcard valgrind/*.supp))

CMAKE_OPTS =

# Commandes
RM    = rm -rf
CMAKE = /usr/bin/cmake
VALGRIND = valgrind

# Options
$(VERBOSE).SILENT:
.NOTPARALLEL:

# Compilation !
all: $(BUILD)
	$(MAKE) -C $(BUILD)
	cp $(BUILD)/$(EXEC) .

.PHONY: all

valgrind: all
	$(VALGRIND) $(VALGRIND_SUPPS) ./$(EXEC)

.PHONY: valgrind

helgrind: all
	$(VALGRIND) --tool=helgrind $(VALGRIND_SUPPS) ./$(EXEC)

.PHONY: helgrind

# Nettoyage
clean:
	$(RM) $(BUILD)

.PHONY: docs

# Dossier $(BUILD)
$(BUILD): src CMakeLists.txt
	echo "\033[35;01mConstruction du dossier $(BUILD)\033[m"
	[ -d "$(BUILD)" ] || mkdir $(BUILD)
	cd $(BUILD); $(CMAKE) $(CMAKE_OPTS) ../..
