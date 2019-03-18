include Makefile.config

.PHONY: all
all: visualgo.a hierarchy.svg foo
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

.PHONY: clean
clean: OBJS := $(VISUALGO_OBJS) src/foo.o
clean:
	$(Q)$(RM) $(OBJS) $(OBJS:o=dwo) visualgo.a foo
	$(Q)find src -type f -name '*.deps' | xargs rm -f

.PHONY: help
help:
	@echo "Nothing is here yet..."
