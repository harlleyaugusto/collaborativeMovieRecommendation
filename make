SOURCE=main.c Item.cpp include/Item.h  Predictor.cpp include/Predictor.h Reader.cpp include/Reader.h Similarity.cpp include/Similarity.h User.cpp include/User.h
MYPROGRAM=main

CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)


$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)

