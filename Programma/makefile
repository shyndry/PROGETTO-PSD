OBJS = main.o noleggio.o gestione_file.o storico_utente.o utils.o list.o veicolo.o prenotazione.o utente.o

TEST_OBJS = test.o utili_per_test.o noleggio.o gestione_file.o storico_utente.o utils.o list.o veicolo.o prenotazione.o utente.o

all: main.exe test.exe

main.exe: $(OBJS)
	gcc $(OBJS) -o main.exe

test.exe: $(TEST_OBJS)
	gcc $(TEST_OBJS) -o test.exe

list.o: list.c list.h
	gcc -c list.c

veicolo.o: veicolo.c veicolo.h
	gcc -c veicolo.c

prenotazione.o: prenotazione.c veicolo.h
	gcc -c prenotazione.c

utils.o: utils.c utils.h
	gcc -c utils.c

utente.o: utente.c utils.h
	gcc -c utente.c

storico_utente.o: storico_utente.c list.h utils.h veicolo.h prenotazione.h
	gcc -c storico_utente.c

gestione_file.o: gestione_file.c storico_utente.h utils.h list.h veicolo.h prenotazione.h
	gcc -c gestione_file.c

noleggio.o: noleggio.c veicolo.h list.h utils.h gestione_file.h prenotazione.h
	gcc -c noleggio.c

main.o: main.c noleggio.h gestione_file.h storico_utente.h utils.h list.h veicolo.h prenotazione.h
	gcc -c main.c

utili_per_test.o: utili_per_test.c utili_per_test.h
	gcc -c utili_per_test.c

test.o: test.c noleggio.h gestione_file.h storico_utente.h utils.h list.h veicolo.h prenotazione.h utili_per_test.h
	gcc -c test.c

clean:
	rm -f *.o main.exe test.exe

.PHONY: clean
