SOURCES+=./test.cc ./mera.cc
OBJECTS = $(SOURCES:.$(CXXSUFFIX)=.o)
DEPENDS = $(SOURCES:.$(CXXSUFFIX)=.d)

CXXSUFFIX=cc
CXX = clang++
CXXFLAGS = -g -W -Wall -Werror -std=c++11
LDFLAGS = -g

PROG=test-prog

$(PROG): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

test: $(PROG)
	./$(PROG)

clean::
	$(RM) $(PROG)
	$(RM) $(OBJECTS)
	$(RM) $(DEPENDS)

.cc.o:
	$(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<


-include $(DEPENDS)

%.d:
	@touch $@
