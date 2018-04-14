SOURCE=main.cpp Item.cpp  Predictor.cpp Reader.cpp  Similarity.cpp  User.cpp 
MYPROGRAM=recommender
ARGS = ratings.csv target.csv
CC=g++
RATINGS = ratings.csv
TARGETS = targets.csv

#------------------------------------------------------------------------------

all: $(MYPROGRAM)


$(MYPROGRAM): $(SOURCE)

	$(CC) $(CFLAGS) $(SOURCE) -o$(MYPROGRAM)

clean:

	rm -f $(MYPROGRAM) 

run: recommender
	./recommender ratings.csv targets.csv > submission.csv