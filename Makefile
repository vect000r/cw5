.SUFFIXES: .c .h .x .o

CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = fifomaker
NAME2 = consumer
NAME3 = producer

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

.PHONY: help
help:
	@echo "make all		Kompiluje wszystkie programy"
	@echo "make run-all	Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make run-$(NAME2)    Uruchamia program $(NAME2)"
	@echo "make run-$(NAME3)	Uruchamia program $(NAME3)"
	@echo "make clean	Usuwa pliki *.o oraz *.x"

.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) 

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC3): $(OBJS3)
	$(LD) $(LFLAGS) -o $@ $^

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) run-$(EXEC2) run-$(EXEC3) 

run-$(NAME1): $(EXEC1)
	./$(EXEC1) $(ARGS)

run-$(NAME2): $(EXEC2)
	./$(EXEC2) $(ARGS)

run-$(NAME3): $(EXEC3)
	./$(EXEC3) $(ARGS)

.PHONY: clean

clean:
	rm *.o *.x

.PHONY: run-all
run-all: $(EXEC1) $(EXEC2) $(EXEC3) 
	./$(EXEC1) 
	./$(EXEC2)
	./$(EXEC3)
.PHONY: create-pipe
create-pipe:
	mkfifo mypipe

.PHONY: start-producer
start-programs:
	xterm -hold -title PRODUCENT -e ./producer.x mypipe producer.txt &
	xterm -hold -title KONSUMENT -e ./consumer.x mypipe consumer.txt

.PHONY: delete-pipe
delete-pipe:
	rm mypipe

	