// COMP2521 20T2 Assignment 1
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "Dict.h"
#include "WFreq.h"
#include "stemmer.h"

#define STOPWORDS "stopwords"
#define MAXLINE 1000
#define MAXWORD 100

#define STARTING "*** START OF"
#define ENDING   "*** END OF"

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

int main( int argc, char *argv[])
{
   // TODO ... add any variables you need
	WFreq *match;	// To check whether stopword matches word extracted from file
   Dict stopwordDict = newDict();  // dictionary of stopwords
	Dict gutenburgDict = newDict();
	int j = 0;	// word len interator

   FILE  *in;         // currently open file
   Dict   wfreqs;     // dictionary of words from book
   WFreq *results;    // array of top N (word,freq) pairs
                      // (dynamically allocated)

   char *fileName;    // name of file containing book text
   int   nWords;      // number of top frequency words to show

   char   line[MAXLINE] = "";  // current input line
   char   word[MAXWORD] = "";  // current word

   // process command-line args
   switch (argc) {
	case 1:
		fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
		exit(EXIT_FAILURE);
   case 2:
      nWords = 10;
      fileName = argv[1];
      break;
   case 3:
      nWords = atoi(argv[1]);
      if (nWords < 10) nWords = 10;
      fileName = argv[2];
      break;
   default:
      fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   // build stopword dictionary
	in = fopen("stopwords", "r");
	if(in == NULL)	
	{	
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}	
	while(fscanf(in, "%s", word) != EOF)	DictInsert(stopwordDict, word);
	fclose(in);
  

   // scan File, up to start of text
	in = fopen(fileName, "r");
	assert(in != NULL);
	while(fgets(line, MAXLINE, in) != NULL)
	{
		if(strncmp(line, "*** START OF", 12) == 0)	break;
	}
	///////// IF COULDNT FIND START OF LINE //////////
	if(strncmp(line, "*** START OF", 12) != 0)
	{
		fprintf(stderr, "Not a Project Gutenberg book\n");
		exit(EXIT_FAILURE);
	}


   // scan File reading words and accumualting counts
	while(fgets(line, MAXLINE, in) != NULL && strncmp(line, "*** END OF", 10) != 0))
	{
		for(int i = 0; i < strlen(line); i++)
		{
			if(line[i] != ' ' && isWordChar(line[i]))
			{
				if(line[i] >= 65 && line[i] <= 90)	
				{				
					word[j] = line[i] + 32;
				}
				else 
				{		
					word[j] = line[i];
				}
				j++;
			}
			if(line[i] == ' ' || !isWordChar(line[i]))
			{
				// Got the word here
				match = DictFind(stopwordDict, word);
				if(match == NULL) int stem(word, 0, (strlen(word)+1));
				WFreq *DictInsert(gutenburgDict, word);
				
				for (int k = 0; k < j; k++) word[k] = '\0';
				j = 0;
			}

		}

	}
   // TODO

   // compute and display the top N words

   // TODO

   // done
   return EXIT_SUCCESS;
}
