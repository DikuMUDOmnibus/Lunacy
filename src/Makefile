CC      = gcc
PROF    =
C_FLAGS = -O -g -Wall $(PROF)
L_FLAGS = -O $(PROF) -lcrypt -llua

SRC_FILES := $(wildcard *.c)
O_DIR = o
O_FILES := $(patsubst %.c,$(O_DIR)/%.o,$(SRC_FILES))

merc: $(O_FILES)
	rm -f merc
	$(CC) -o merc $(O_FILES) $(L_FLAGS)
	cp merc ../area
	ctags --c++-kinds=+cdefgmnpstuv --fields=+iaS --extra=+q *.h *.c	
clean:
	$(RM) -f $(O_FILES) merc  *~ *.bak *.orig *.rej

$(O_DIR)/%.o: %.c
	$(CC) $(C_FLAGS) -c -o $@ $<

