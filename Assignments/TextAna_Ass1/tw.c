// COMP2521 20T2 Assignment 1
// by Ahsan Muhammad (z5188798)
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
   // Variables declarations
   Dict stopwordDict = newDict();  	// dictionary of stopwords
	Dict gutenburg = newDict();		// dictionary of words from gutenburg project
	int j = 0;								// word len interator
	int k = 0;								// catch return from stemming algorithm

   FILE  *in;         // currently open file
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

   ///////////////////////////////////////////////
	////////// build stopword dictionary //////////
	//////////////////////////////////////////////
  
	stopwordDict = newDict();
	in = fopen(STOPWORDS, "r");
	if(in == NULL)	
	{	
		fprintf(stderr, "Can't open stopwords\n");
		exit(EXIT_FAILURE);
	}	
	while(fgets(line, MAXWORD, in) != NULL)
	{
		for(int i = 0; i < strlen(line)-1; i++)	word[i] = line[i];
		DictInsert(stopwordDict, word);
		for(int i = 0; i < MAXWORD; i++)	word[i] = '\0';
	}
	fclose(in);

	///////////////////////////////////////////////
	////////// SCAN UPTO THE START OF TEXT //////////
	//////////////////////////////////////////////

	gutenburg = newDict();	
	in = fopen(fileName, "r");
	if(in == NULL)
	{
		fprintf(stderr, "Can't open %s\n", fileName);
		exit(EXIT_FAILURE);
	}

	while(fgets(line, MAXLINE, in) != NULL)
	{
		if(strncmp(line, STARTING, strlen(STARTING)) == 0)	break;
	}
 
	//////////////////////////////////////////////////////////////////////
	////////// SCAN FILE READING WORDS AND ACCUMULATING COUNTS //////////
	////////////////////////////////////////////////////////////////////

	while(fgets(line, MAXLINE, in) != NULL)
	{
		if(strcmp(line,"\n"  ) != 0 && strcmp(line,"\r\n") != 0 && strcmp(line,"\0"  ) != 0 && 1)
		{
			if(strncmp(line, ENDING, strlen(ENDING)) == 0)	break;
			
			for(int i = 0; i < strlen(line)-1; i++)
			{
				if(line[i] != ' ' && isWordChar(line[i]))
				{
					if(line[i] >= 65 && line[i] <= 90)	word[j] = line[i] + 32;
					else	word[j] = line[i];
					j++;
				}
				else if( ( line[i] == ' ' || !isWordChar(line[i]) ) && j > 1)
				{
					if(DictFind(stopwordDict, word) == NULL) 
					{
						k = stem(word, 0, (strlen(word)-1));
						word[k+1] = '\0';
						DictInsert(gutenburg, word);
					}			
					for(j = 0; j < MAXWORD; j++)	word[j] = '\0';
					j = 0;
				}
				else	j = 0;
			}
		}	
		else continue;
	}

	fclose(in);
	
	//////////////////////////////////////////////////////////////////////
	////////// COMPUTE AND DISPLAY THE TOP N WORDS //////////
	////////////////////////////////////////////////////////////////////

	results = (WFreq *)malloc(nWords*sizeof(WFreq));
	for(int i = 0; i < nWords; i++)
	{
		results[i].word = NULL; results[i].freq = -1;
	}

	int topN = findTopN(gutenburg, results, nWords);
	for(int i = 0; i < topN; i++)	printf("%7d %s\n", (*(results+i)).freq, (*(results+i)).word);


   return EXIT_SUCCESS;
}
