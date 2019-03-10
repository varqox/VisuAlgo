include Makefile.config

.PHONY: all
all: visualgo.a hierarchy.svg
	@printf "\033[32mBuild finished\033[0m\n"

VISUALGO_SRCS := \
	src/latex_presentation.cc \
	src/latex_element.cc \
	src/slide.cc \
	src/slide_builder.cc

$(eval $(call load_dependencies, $(VISUALGO_SRCS)))
VISUALGO_OBJS := $(call SRCS_TO_OBJS, $(VISUALGO_SRCS))

visualgo.a: $(VISUALGO_OBJS)
	$(MAKE_STATIC_LIB)

hierarchy.svg: hierarchy.dot
	$(Q)$(call P,DOT,$@) \
		$(call TIME_CMD,DOT) \
		dot -Tsvg -o $@ $^

.PHONY: clean
clean: OBJS := $(VISUALGO_OBJS)
clean:
	$(Q)$(RM) $(OBJS) $(OBJS:o=dwo)
	$(Q)find src test -type f -name '*.deps' | xargs rm -f

.PHONY: help
help:
	@echo "Nothing is here yet..."