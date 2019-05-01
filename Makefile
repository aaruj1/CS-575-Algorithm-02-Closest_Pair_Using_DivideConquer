# The c++ compiler
CPP = gcc
CFLAGS = -lm 

# The filename
FILENAME = submission

# The build target executable:
BINARY = submission

all: $(BINARY)

$(BINARY): $(BINARY).c
	$(CPP)  $(CFLAGS) -o $(BINARY) $(FILENAME).c

clean: 
	rm $(BINARY)
