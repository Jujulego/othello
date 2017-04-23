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

perf.data: all
	sudo perf record -gj u -- ./$(EXEC)

analyse.txt: perf.data
	sudo perf script | c++filt > analyse.txt

call.png: analyse.txt
	python3 parse.py | gprof2dot -sf perf -n0 -e0 | sed -e "s/ *.n(*[0-9]*\.[0-9][0-9]%)*//g" | sed -e "s/[0-9]*\.[0-9][0-9]%//g" | sed -e "s/run.n//g" | dot -Tpng -o call.png

# Nettoyage
clean:
	$(RM) $(BUILD)

.PHONY: docs

# Dossier $(BUILD)
$(BUILD): src CMakeLists.txt
	echo "\033[35;01mConstruction du dossier $(BUILD)\033[m"
	[ -d "$(BUILD)" ] || mkdir $(BUILD)
	cd $(BUILD); $(CMAKE) $(CMAKE_OPTS) ../..
