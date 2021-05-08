#CHIFFREMENT
chiff: chiffrement
	./chiff 000000 000000

chiffrement: common.o chiffrement.o main_chiff.o
	gcc -g -o chiff common.o chiffrement.o main_chiff.o

common.o: common.c common.h
	gcc -g -o common.o -c common.c

chiffrement.o: chiffrement.c common.h chiffrement.h
	gcc -g -o chiffrement.o -c chiffrement.c

main_chiff.o: main_chiff.c chiffrement.h common.h
	gcc -g -o main_chiff.o -c main_chiff.c


#DECHIFFREMENT
dechiff: dechiffrement
	./dechiff bb57e6 000000

dechiffrement: common.o chiffrement.o dechiffrement.o main_dechiff.o
	gcc -g -o dechiff common.o chiffrement.o dechiffrement.o main_dechiff.o

dechiffrement.o: dechiffrement.c common.h chiffrement.h dechiffrement.h 
	gcc -g -o dechiffrement.o -c dechiffrement.c

main_dechiff.o: main_dechiff.c chiffrement.h dechiffrement.h common.h
	gcc -g -o main_dechiff.o -c main_dechiff.c



#ATTAQUE
att: attaque
	#valgrind -s --track-origins=yes ./att 8c8a4f a780e8
	./att 8c8a4f a780e8
	#./att 1f65f6 04caf6

attaque: common.o attaque.o chiffrement.o dechiffrement.o main_att.o
	gcc -g -o att common.o dechiffrement.o chiffrement.o attaque.o main_att.o

attaque.o: common.h chiffrement.h dechiffrement.h attaque.c 
	gcc -g -o attaque.o -c attaque.c

main_att.o: main_att.c attaque.h common.h
	gcc -g -o main_att.o -c main_att.c



clean :
	rm *.o 

zip : 
	zip DM_COLNOT.zip -r *.c *.h *.docx Makefile README.md