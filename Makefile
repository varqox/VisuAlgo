include Makefile.config

.PHONY: all
all: visualgo.a io_stuff examples presentation
	@printf "\033[32mBuild finished\033[0m\n"

GOOGLETEST_SRCS := \
	$(PREFIX)googletest/googletest/src/gtest-all.cc \
	$(PREFIX)googletest/googletest/src/gtest_main.cc

$(eval $(call load_dependencies, $(GOOGLETEST_SRCS)))
GOOGLETEST_OBJS := $(call SRCS_TO_OBJS, $(GOOGLETEST_SRCS))

gtest_main.a: $(GOOGLETEST_OBJS)
	$(MAKE_STATIC_LIB)

$(GOOGLETEST_OBJS): override EXTRA_CXX_FLAGS += -isystem '$(CURDIR)/googletest/googletest/include' -I '$(CURDIR)/googletest/googletest' -pthread

VISUALGO_SRCS := \
	src/block.cc \
	src/color.cc \
	src/image.cc \
	src/image_set.cc \
	src/itemize.cc \
	src/latex.cc \
	src/latex_presentation.cc \
	src/slide.cc \
	src/slide_builder.cc \
	src/source_code.cc \
	src/geometry.cc \
	src/point.cc \
	src/line.cc \
	src/rectangle.cc \
	src/geometry_element.cc \
	src/circle.cc \
	src/vector.cc \
	src/polygon.cc

$(eval $(call load_dependencies, $(VISUALGO_SRCS)))
VISUALGO_OBJS := $(call SRCS_TO_OBJS, $(VISUALGO_SRCS))

visualgo.a: $(VISUALGO_OBJS)
	$(MAKE_STATIC_LIB)

.PHONY: io_stuff
io_stuff: io_stuff/hierarchy.svg

%.svg: %.dot
	$(Q)$(call P,DOT,$@) \
		$(call TIME_CMD,DOT) \
		dot -Tsvg -o $@ $^

EXAMPLES_SRCS := \
	examples/arrays.cc \
	examples/binsearch.cc \
	examples/containers.cc \
	examples/dijkstra.cc \
	examples/geometry.cc \
	examples/graph.cc \
	examples/matrix.cc \
	examples/pictures.cc \
	examples/sieve.cc

$(eval $(call load_dependencies, $(EXAMPLES_SRCS)))
EXAMPLES_OBJS := $(call SRCS_TO_OBJS, $(EXAMPLES_SRCS))
EXAMPLES_EXECS := $(patsubst %.o, %, $(EXAMPLES_OBJS))

$(EXAMPLES_EXECS): %: %.o visualgo.a
	$(LINK)

.PHONY:
examples: $(EXAMPLES_EXECS)

EXAMPLES_PDFS := $(patsubst %, %.pdf, $(EXAMPLES_EXECS))

PRESENTATION_SRCS := \
	presentation/presentation.cc

$(eval $(call load_dependencies, $(PRESENTATION_SRCS)))
PRESENTATION_OBJS := $(call SRCS_TO_OBJS, $(PRESENTATION_SRCS))
PRESENTATION_EXECS := presentation/presentation

$(PRESENTATION_EXECS): $(PRESENTATION_OBJS) visualgo.a
	$(LINK)

PRESENTATION_PDFS := $(patsubst %, %.pdf, $(PRESENTATION_EXECS))

.PHONY:
presentation: $(PRESENTATION_PDFS)

.ONESHELL:
%.pdf: %
	DEST_DIR="$(dir $(abspath $@))"
	TMP_DIR=$$(mktemp -d)
	NAME=$(notdir $*)
	$(Q)cp -r "$$DEST_DIR" -T "$$TMP_DIR"
	$(Q)cd "$$TMP_DIR"
	$(Q)"$$DEST_DIR$$NAME" > "$$NAME.tex"
	# Need to run latex twice to get the correct page numbers
	$(Q)echo | pdflatex --shell-escape "$$NAME.tex" && \
		$(Q)echo | pdflatex --shell-escape "$$NAME.tex"
	RET=$$?
	$(Q)if [ "$$RET" = "0" ]; then cp "$$NAME.pdf" "$$DEST_DIR"; fi
# 	$(Q)rm -rf "$$TMP_DIR"
	$(Q)exit $$RET

examples/examples.pdf: $(EXAMPLES_PDFS)
	$(Q)pdfunite $(EXAMPLES_PDFS) $@
	@printf "\033[32mCombined generated pdfs into \033[1;32m$@\033[0m\n"

VISUALGO_TEST_SRCS := \
	test/array_1d.cc \
	test/block.cc \
	test/graphs.cc \
	test/image.cc \
	test/latex.cc \
	test/source_code.cc \
	test/variable.cc

$(eval $(call load_dependencies, $(VISUALGO_TEST_SRCS)))
VISUALGO_TEST_OBJS := $(call SRCS_TO_OBJS, $(VISUALGO_TEST_SRCS))
VISUALGO_TEST_EXECS := test/exec

$(VISUALGO_TEST_OBJS): override EXTRA_CXX_FLAGS += -isystem '$(CURDIR)/googletest/googletest/include'

test/exec: $(VISUALGO_TEST_OBJS) visualgo.a gtest_main.a
	$(LINK) -pthread

.PHONY: test
test: $(VISUALGO_TEST_EXECS)
	test/exec

.PHONY: clean
clean: OBJS := $(GOOGLETEST_OBJS) $(VISUALGO_OBJS) $(EXAMPLES_OBJS) $(VISUALGO_TEST_OBJS) $(PRESENTATION_OBJS)
clean:
	$(Q)$(RM) $(OBJS) $(OBJS:o=dwo) gtest_main.a visualgo.a $(EXAMPLES_EXECS) $(EXAMPLES_PDFS) $(VISUALGO_TEST_EXECS) $(PRESENTATION_EXECS) examples/examples.pdf
	$(Q)find examples -type f -name '*.tex' | xargs rm -f
	$(Q)find src googletest test examples io_stuff presentation -type f -name '*.deps' | xargs rm -f

.PHONY: help
help:
	@echo "Nothing is here yet..."
