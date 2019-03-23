include Makefile.config

.PHONY: all
all: visualgo.a hierarchy.svg foo dijkstra arrays sieve binsearch graph
	@printf "\033[32mBuild finished\033[0m\n"

VISUALGO_SRCS := \
	src/block.cc \
	src/color.cc \
	src/itemize.cc \
	src/latex.cc \
	src/latex_presentation.cc \
	src/slide.cc \
	src/slide_builder.cc \
	src/source_code.cc

$(eval $(call load_dependencies, $(VISUALGO_SRCS)))
VISUALGO_OBJS := $(call SRCS_TO_OBJS, $(VISUALGO_SRCS))

visualgo.a: $(VISUALGO_OBJS)
	$(MAKE_STATIC_LIB)

hierarchy.svg: hierarchy.dot
	$(Q)$(call P,DOT,$@) \
		$(call TIME_CMD,DOT) \
		dot -Tsvg -o $@ $^

$(eval $(call load_dependencies, src/foo.cc))
foo: src/foo.o visualgo.a
	$(LINK)

$(eval $(call load_dependencies, src/dijkstra.cc))
dijkstra: src/dijkstra.o visualgo.a
	$(LINK)

$(eval $(call load_dependencies, src/binsearch.cc))
binsearch: src/binsearch.o visualgo.a
	$(LINK)

$(eval $(call load_dependencies, src/arrays.cc))
arrays: src/arrays.o visualgo.a
	$(LINK)

$(eval $(call load_dependencies, src/sieve.cc))
sieve: src/sieve.o visualgo.a
	$(LINK)

$(eval $(call load_dependencies, src/graph.cc))
graph: src/graph.o visualgo.a
	$(LINK)

.PHONY: clean
clean: OBJS := $(VISUALGO_OBJS) src/foo.o src/dijkstra.o src/binsearch.o src/arrays.o src/sieve.o src/graph.o
clean:
	$(Q)$(RM) $(OBJS) $(OBJS:o=dwo) visualgo.a foo dijkstra tablice binsearch sieve graph
	$(Q)find src -type f -name '*.deps' | xargs rm -f

.PHONY: help
help:
	@echo "Nothing is here yet..."
