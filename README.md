# 2048ECOS
Jocul 2048, implementat in C pentru a functiona in terminal, folosind biblioteca NCURSES
Joc 2048, realizat de Eugen Costin, Ianuarie 2018.

Timp alocat temei: 7 zile

Functionalitatea jocului:

	La pornirea jocului, utilizatorul este intampinat cu fereastra de meniu.

	MENIU:
	Optiunea "INCEPERE JOC NOU" porneste un joc de la inceput.
	Optiunea "REVENIRE" revine la jocul intrerupt sau incepe un joc nou daca nu era niciunul in desfasurare.
	Optiunea "IESIRE" inchide jocul si iese in terminal.
	Optiunea "DESPRE" reprezinta detalii despre producerea jocului.
	Optiunea "SCORURI" reprezinta o lista cu cele mai bune 10 scoruri din sesiunea curenta de joc.
	Optiunea "INTRODUCETI NUME" reprezinta o caseta in care utilizatorul poate introduce numele, pentru a fi memorat cu acest nume in tabela de scoruri, daca este cazul.

	JOCUL PROPRIU-ZIS:
	In afara de regulile de joc descrise in enuntul temei, am implementat o regula de automove care se realizeaza daca nu se apasa nicio tasta timp de 10 secunde ( Timerul este afisat deasupra scorului ) sau daca se apasa tasta "z";
	Miscarea casutelor se face cu tastele "w,a,s,d";
	Deasupra Timerului sunt afisate, pentru informatia utilizatorului, dimensiunile ecranului ( x,y ). 
	Fereastrele de joc si meniu se vor rescala in functie de aceste dimensiuni si vor aparea mereu pe mijlocul ecranului.
	Revenirea la starea anterioara a tablei ( UNDO ) se face cu tasta "u";
	Revenirea la fereastra de meniu se face cu tasta "q";
	Cand nu mai exista mutari posibile se va afisa in fereastra de SCOR meajul "FARA MUTARI!", dupa care jocul asteapta 3 secunde si intra in fereastra de meniu.
	Analog se intampa si in cazul victoriei, dar este afisat mesajul "BRAVO!";
	Sub tabla de joc este o fereastra in care se afiseaza implicit "HELLO user", iar cuvantul "user" se inlocuieste cu numele introdus de jucator, daca exista.
	Deasupra tablei de joc este o fereastra in care se afiseaza data si ora, si este modificata in fiecare secunda. ( A prins trecerea dintre ani )

Enumerarea optiunilor suplimentare:

	Timer Automove 10 secunde;
	Design placut al jocului si al ferestrelor, meniu si tabla colorata, culori specifice pentru casutele ce contin acelasi numar;
	Optiunea de a introduce nume;
	Tabela cu 10 scoruri maxime;
	Red

Explicarea pe scurt a implementarii:

	Functia meniu afiseaza fereastra de meniu si returneaza indicele optiunii selectate de catre utilizator. In functie de acesta, programul executa actiunile descrise mai sus, la sectiunea Functionalitatea jocului/MENIU.
	Motorul matematic al jocului consta in memorarea valorilor intr-un vector de 16 elemente, care se modifica in functie de tasta apasata si se incarca intr-un vector de ferestre, fiecare valoare in fereastra care ii corespunde. 
	Pentru a nu face mai multe imbinari la o singura mutare, am abordat mutarile in felul urmator: O mutare consta in mutarea casutelor de pe toate liniile sau coloanele in directia ceruta, apoi adunarea elementelor imediat alaturate care au aceeasi valoare, daca exista, si apoi mutarea casutelor inca o data. 
	Daca miscarea nu este valida, scorul nu se va incrementa. 
	Caracterul "ch" memoreaza tasta apasata. Functia getch() este non-blocking ( nodelay(STDSCR,TRUE) ). Daca ch este ERR, adica nu a fost apasata nicio tasta, se porneste timerul de automove, care dureaza 10 secunde, si este intrerupt daca se apasa o tasta care are o comanda atasata, nu orice tasta. 
	La fiecare miscare, valorile din vectorul principal sunt copiate intr-un vector secundar, pentru a face posibila optiunea de UNDO. Automove-ul realizeaza miscarea care elibereaza cele mai multe casute. Implementarea automove-ului s-a facut cu ajutorul unui vector auxiliar,  in care se copiaza elementele celui principal, si caruia i se aplica toate cele 4 miscari posibile.
	Se determina numarul de casute nule rezultate in fiecare din cele 4 cazuri, si se determina mutarea care rezulta in cele mai multe casute goale.
	Aceasta mutare este executata pentru vectorul principal.
	Daca se apasa q, se apeleaza functia de meniu si se sterge fereastra de joc.
	Se verifica mereu castigarea sau pierderea jocului, si se afiseaza mesajele aferente. Dupa 3 secunde de la victorie sau pierdere se revine la meniu prin apelarea functiei.
	Pentru memorarea scorurilor si ale numelor care le corespund am folosit un vector de structuri cu 2 elemente: username si userscore.
	Username-urile sunt initializate cu "user", si se modifica daca jucatorul introduce un nume.
	Daca scorul obtinut la finalul unui joc este mai mare decat cel mai mic scor din top 10, userscore-ul respectiv va lua valoarea scorului, si lista de scoruri se va sorta din nou.
