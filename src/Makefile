include ../Rules.mk

.PHONY: all clean distclean

EXEC := a.out
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf $(OBJS)

distclean: clean
	rm -rf $(EXEC)
