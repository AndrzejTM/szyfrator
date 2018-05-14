ATM_Vigenere : ATM_Vigenere.o tabulaRecta.o silnikSzyfrujacy.o
	gcc -o ATM_Vigenere ATM_Vigenere.o tabulaRecta.o silnikSzyfrujacy.o
    
ATM_Vigenere.o : ATM_Vigenere.c tabulaRecta.h silnikSzyfrujacy.h
	gcc -c ATM_Vigenere.c
    
tabulaRecta.o : tabulaRecta.c
	gcc -c tabulaRecta.c
    
silnikSzyfrujacy.o : silnikSzyfrujacy.c tabulaRecta.h
	gcc -c silnikSzyfrujacy.c
    
clean :
	rm ATM_Vigenere ATM_Vigenere.o tabulaRecta.o silnikSzyfrujacy.o
