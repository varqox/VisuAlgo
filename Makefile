include Makefile.config

.PHONY: all
all: visualgo.a hierarchy.svg examples
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

EXAMPLES_SRCS := \
	examples/arrays.cc \
	examples/binsearch.cc \
	examples/dijkstra.cc \
	examples/graph.cc \
	examples/sieve.cc

$(eval $(call load_dependencies, $(EXAMPLES_SRCS)))
EXAMPLES_OBJS := $(call SRCS_TO_OBJS, $(EXAMPLES_SRCS))
EXAMPLES_EXECS := $(patsubst %.o, %, $(EXAMPLES_OBJS))

$(EXAMPLES_EXECS): %: %.o visualgo.a
	$(LINK)

.PHONY:
examples: $(EXAMPLES_EXECS)

EXAMPLES_PDFS := $(patsubst %, %.pdf, $(EXAMPLES_EXECS))

.ONESHELL:
$(EXAMPLES_PDFS): %.pdf: %
	DEST_DIR=$$(pwd)/examples/
	TMP_DIR=$$(mktemp -d)
	NAME=$(patsubst examples/%,%, $*)
	$(Q)cd "$$TMP_DIR"
	$(Q)"$$DEST_DIR$$NAME" > "$$NAME.tex"
	# Need to run latex twice to get the correct page numbers
	$(Q)echo | pdflatex --shell-escape "$$NAME.tex" && \
		$(Q)echo | pdflatex --shell-escape "$$NAME.tex"
	RET=$$?
	$(Q)if [ "$$RET" = "0" ]; then cp "$$NAME.pdf" "$$DEST_DIR"; fi
	$(Q)rm -rf "$$TMP_DIR"
	$(Q)exit $$RET

examples/examples.pdf: $(EXAMPLES_PDFS)
	$(Q)pdfunite $(EXAMPLES_PDFS) $@
	@printf "\033[32mCombined generated pdfs into \033[1;32m$@\033[0m\n"

.PHONY: clean
clean: OBJS := $(VISUALGO_OBJS) $(EXAMPLES_OBJS)
clean:
	$(Q)$(RM) $(OBJS) $(OBJS:o=dwo) visualgo.a $(EXAMPLES_EXECS) $(EXAMPLES_PDFS) examples/examples.pdf
	$(Q)find examples -type f -name '*.tex' | xargs rm -f
	$(Q)find src -type f -name '*.deps' | xargs rm -f

.PHONY: help
help:
	@echo "Nothing is here yet..."
