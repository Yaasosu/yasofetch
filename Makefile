CC = gcc
CFLAGS = -Iinc -Wall
VPATH = src
OBJDIR = obj

SOURCES = main.c distro_logo.c system_info.c packetManagerDefinder.c
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = yasofetch

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

.PHONY: all clean
