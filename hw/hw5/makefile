CC = gcc
OBJ = main.o 
EXE = hw5

.PHONY : clean rebuild run

$(EXE) : $(OBJ)
		$(CC) -o $(EXE) $(OBJ) 

%.o : %.c
	$(CC) -c $^

clean : 
		@rm -rf *.o

rebuild : clean $(EXE)

run : rebuild
	 @./$(EXE) input.c
