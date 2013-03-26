SRCS=$(wildcard *.java)
OBJS=$(SRCS:.java=.class)

all: $(OBJS)

%.class: %.java
	javac $<

clean:
	 rm -f $(OBJS)
