include makefile-utils/Makefile.config

.PHONY: all
all: visualgo.a io_stuff examples/examples.pdf presentation check-examples-in-readme
	@printf "\033[32mBuild finished\033[0m\n"

define GOOGLETEST_FLAGS =
INTERNAL_EXTRA_CXX_FLAGS = -isystem '$(CURDIR)/googletest/googletest/include' -I '$(CURDIR)/googletest/googletest'
INTERNAL_EXTRA_LD_FLAGS = -pthread
endef

$(eval $(call add_static_library, gtest_main.a, $(GOOGLETEST_FLAGS), \
	googletest/googletest/src/gtest-all.cc \
	googletest/googletest/src/gtest_main.cc \
))

$(eval $(call add_static_library, visualgo.a, , \
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
	src/polygon.cc \
))

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
EXAMPLES_EXECS := $(patsubst %.cc, %, $(EXAMPLES_SRCS))

BUILD_ARTIFACTS += $(call SRCS_TO_BUILD_ARTIFACTS, $(EXAMPLES_SRCS)) $(EXAMPLES_EXECS)
$(EXAMPLES_EXECS): %: %.o visualgo.a
	$(LINK)

EXAMPLES_PDFS := $(patsubst %, %.pdf, $(EXAMPLES_EXECS))
BUILD_ARTIFACTS += $(EXAMPLES_PDFS)

.PHONY: compile_examples
compile_examples: $(EXAMPLES_EXECS)

.PHONY: examples
examples: $(EXAMPLES_PDFS)

.PHONY: check-examples-in-readme
check-examples-in-readme:
	bash -c "diff <(echo $(EXAMPLES_EXECS) | sed 's/ /\n/g' | sed 's@.*/@@' | sort) <(grep '^| [a-z]' README.md | cut -d ' ' -f 2 | sort) || echo Above examples are missing in README.md or are missing in examples/"

$(eval $(call add_executable, presentation/presentation, , \
	presentation/presentation.cc \
	visualgo.a \
))

.PHONY: presentation
presentation: presentation/presentation.pdf
BUILD_ARTIFACTS += presentation/presentation.pdf

.ONESHELL:
%.pdf: %
	DEST_DIR="$(dir $(abspath $@))"
	TMP_DIR=$$(mktemp -d)
	NAME=$(notdir $*)
	$(Q)cp -rL "$$DEST_DIR" -T "$$TMP_DIR"
	$(Q)cd "$$TMP_DIR"
	$(Q)"$$DEST_DIR$$NAME" > "$$NAME.tex"
	# Need to run latex twice to get the correct page numbers
	$(Q)echo | pdflatex --shell-escape "$$NAME.tex" && \
		$(Q)echo | pdflatex --shell-escape "$$NAME.tex"
	RET=$$?
	$(Q)if [ "$$RET" = "0" ]; then cp "$$NAME.pdf" "$$DEST_DIR"; fi
	$(Q)rm -rf "$$TMP_DIR"
	$(Q)exit $$RET

BUILD_ARTIFACTS += examples/examples.pdf
examples/examples.pdf: $(EXAMPLES_PDFS)
	$(Q)pdfunite $(EXAMPLES_PDFS) $@
	@printf "\033[32mCombined generated pdfs into \033[1;32m$@\033[0m\n"

define VISUALGO_TEST_FLAGS =
INTERNAL_EXTRA_CXX_FLAGS = -isystem '$(CURDIR)/googletest/googletest/include'
INTERNAL_EXTRA_LD_FLAGS = -pthread
endef

$(eval $(call add_executable, test/exec, $(VISUALGO_TEST_FLAGS), \
	gtest_main.a \
	test/array_1d.cc \
	test/block.cc \
	test/graphs.cc \
	test/image.cc \
	test/latex.cc \
	test/source_code.cc \
	test/variable.cc \
	visualgo.a \
))

.PHONY: test
test: test/exec
	test/exec

.PHONY: format
format: $(shell ls | grep -vE '^(googletest|html|latex)$$' | xargs find | grep -E '\.(cc?|h)$$' | sed 's/$$/-make-format/')
