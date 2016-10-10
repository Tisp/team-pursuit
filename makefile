BIN_SIMULADOR = team_pursuit
SRCS_SIMULADOR = $(wildcard src/*.c) $(wildcard src/*.c)

INCS = -Isrc/
LIBS = -ansi -pedantic -O2 -O3 -Wall -lrt -lm -lpthread -pthread 

CFLAGS = $(INCS) -c -g
LDFLAGS = $(LIBS)
OUTFLAG = -o
INFLAG =

CC = gcc
DEPGEN = gcc $(INCS) -MM -MP -MT $(patsubst %$(SRCEXT),%$(OBJEXT),$<)
RM = rm -f
TOUCH = touch

OBJEXT = .o
DEPEXT = .d
SRCEXT = .c
OBJS_SIMULADOR = $(SRCS_SIMULADOR:$(SRCEXT)=$(OBJEXT))
DEPS = $(SRCS_EP1:$(SRCEXT)=$(DEPEXT)) $(SRCS_SIMULADOR:$(SRCEXT)=$(DEPEXT))

all: $(BIN_SIMULADOR)

$(BIN_SIMULADOR): $(OBJS_SIMULADOR)
	$(CC) $(INFLAG)$^ $(OUTFLAG)$@ $(LDFLAGS)

clean: clean_team_pursuit

clean_team_pursuit:
	$(RM) $(BIN_SIMULADOR) $(OBJS_SIMULADOR) $(DEPS)

%$(OBJEXT): %$(SRCEXT)
	$(DEPGEN) $< $(OUTFLAG)$(patsubst %$(OBJEXT),%$(DEPEXT),$@)
	$(CC) $(CFLAGS) $(INFLAG)$< $(OUTFLAG)$@

%$(DEPEXT): %$(SRCEXT)
	@$(TOUCH) $@

-include $(DEPS)
