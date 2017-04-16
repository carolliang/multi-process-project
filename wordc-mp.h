#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct list {
	char *str;
	int frequency;
	struct list *next;
} WordList ;

WordList *head;
void print(WordList *pwc, FILE *out);
void insert (char* pWord);
WordList *createNode(char *word);



void print(WordList *pwc, FILE *out)
{
	fprintf(out, "%-30s   %5d\n",pwc->str,pwc->frequency);
}




WordList *createNode(char *word)
{
	WordList *newNode= NULL;
	newNode=(WordList*)malloc(sizeof(WordList));
	newNode->str=(char*)malloc(strlen(word)+1);
	strcpy(newNode->str,word);
	newNode->frequency=1;
	newNode->next=NULL;
	return newNode;
}

void insert(char *word)
{

  WordList *current =NULL;
  WordList *newNode =NULL;

  current = head;
  if(current == NULL || strcmp(word,current->str) < 0)
  {
    newNode=createNode(word);
    newNode->next=current;
    head=newNode;
  }

  else
  {
      WordList *nextWord=current->next;
      WordList *previous =current;

      if (nextWord!= NULL && strcmp(word,current->str) == 0){
          current->frequency++;
      }
      else {
        while (nextWord !=NULL && strcmp(word,nextWord->str)>0)
        {
            previous=nextWord;
            nextWord=nextWord->next;
        }
        if (nextWord!=NULL && strcmp(word,nextWord->str)==0)
        {
            nextWord->frequency++;
        } 
        else{
          newNode=createNode(word);
          newNode->next=nextWord;
          previous->next=newNode;
        }
      }
  }
}

