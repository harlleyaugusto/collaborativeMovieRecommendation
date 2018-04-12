SOURCE=main.cpp Item.cpp Item.h  Predictor.cpp Predictor.h Reader.cpp Reader.h Similarity.cpp Similarity.h User.cpp User.h
MYPROGRAM=CMR

CC=g++

#------------------------------------------------------------------------------

all: $(MYPROGRAM)


$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM)

run : ./$(MYPROGRAM)
