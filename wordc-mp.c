#include "wordc-mp.h"




int main(int argc, char *argv[]){
	
	//Timer
	clock_t start_t, end_t;
    double spend_t;
    start_t=clock();
    FILE *runtime;
    runtime=fopen(argv[3],"w");

	int i, j, k;

	// File's total word
	FILE *infile;
	infile=fopen(argv[1],"r");
	if (infile == NULL){
		printf("Couldn't open file: ");
	}

	int totalWords=0,t=0;
	char w[32];

	rewind(infile);
	while(fscanf(infile,"%s",w)!=EOF)
	{
		totalWords++;
	}

	fprintf(runtime, "Total words are: %d\n", totalWords);

	// fclose(infile);
	// infile=fopen(argv[1],"r");
	// if (infile == NULL){
	// 	printf("Couldn't open file again: ");
	// }
	//char strFile[totalWords][32];


	char **strFile;

	rewind(infile);
	//char *tempString = malloc(sizeof(char) *32);
	strFile = malloc(totalWords * sizeof(char*));
	*strFile = malloc(32 * sizeof(char*));
	while(fscanf(infile,"%s",strFile[t])!=EOF)
	{
		//sscanf(tempString, "%s", strFile[t]);
		printf("%s\n", strFile[t]);
		t++;
		strFile[t] = malloc(32 * sizeof(char*));
		
	}

	//free(tempString);
    // Cover to lower case
    //char finalString[totalWords][32];
    char **finalString;
    finalString = malloc(totalWords * sizeof(char*));
	*finalString = malloc(32 * sizeof(char*));
    char *word;
    word=malloc(sizeof(char*)*32);

    printf("I am done with reading\n");

    /////////////////////////////////////////////////////check this loop condition
	for(i=0;i<=totalWords;i++)
	{
		k=0;
		finalString[i] = malloc(32 * sizeof(char*));	
		for(j=0;j<=strlen(strFile[i]);j++)
		{
			if(isalnum(strFile[i][j]))
			{
				finalString[i][k]=tolower(strFile[i][j]);
				k++;
			}

			finalString[i][k]='\0';
		}
		free(strFile[i]);
		
	}
	// Sort


	//MergeSort(finalString, 0, totalWords-1);


      for (i = 0;  i< totalWords+1; i++) 
	  {
           for (j = 0; j < totalWords ; j++) 
            {
                 if (strcmp(finalString[j], finalString[j + 1]) > 0) 
                   {
                     strcpy(word, finalString[j]);
                     strcpy(finalString[j], finalString[j + 1]);
                     strcpy(finalString[j + 1], word);
                   }
            }
       }




    //int l=0;
	//while(l<=totalWords)
	//{
		//printf(" %s \n",finalString[l]);
		//l++;
	//}





// Multiple Processe
	int degree=atoi(argv[4]);
	int numChild=degree-1;
	int fd[2*numChild];
	pid_t child;
	

	//Words for child and parent
	int wordChild=(totalWords-(totalWords%degree))/degree;
	int wordParent=totalWords-wordChild*numChild;
	char wFC[totalWords][32];
	char wFP[totalWords*2][32];
	int a,b,c;
	//printf("word for child: %d\n",wordChild);
	//printf("word for parent: %d\n",wordParent);
	//printf("Total words: %d",totalWords);



	// Check if user has inputed correct amount of arguments
	if (argc < 4){
		printf("Arugments are not correct\n. ");
		exit(0);
	}

	// If user has inputed correct amount of arguments, continue with execution
	else {
		for (i = 0; i < numChild; i++){
			// Create a new pipe and fork one child per argument passed in by user

			printf("Here trying to make babies\n");
			pipe(fd+2*i);
			child = fork();


			if (child < 0){
				perror("Error");
				exit(1);
			}
			// Child process send sort string array to parent
			else if (child == 0){

				//printf("I'm child.");
				//char temp[wordChild][32];
				char **temp;
				temp = malloc(wordChild * sizeof(char*));
				*temp = malloc(32 * sizeof(char*));
				int a,b,c=0,d,e=0;
			// Creat string array for child part
				for(a=i*wordChild;a<wordChild*(i+1);a++)
				{
					temp[a] = malloc(32 * sizeof(char*));
					for(b=0;b<strlen(finalString[a]);b++)
					{
						temp[c][b]=finalString[a][b];
					}
					temp[c][b]='\0';
					c++;
				}
				//printf("Child word: %s %s %s %s\n",temp[0],temp[1],temp[2],temp[67]);
			
				close(fd[2*i]);
				write(fd[2*i+1], temp, sizeof(temp)*10);
				close(fd[2*i+1]);	
				exit(0);
			}
			


		}
		//Wait for children to return to parent
		for(k = 0; k < numChild; k++){

			//printf("I'm waiting.\n");
			wait(NULL);
		}


				
        //printf("I'm parent.\n");
        char buffer[32];
        FILE *pf;
        pf=fopen("pf.txt","w");

		// Parent process reads from child process and prints out results
        c=0;
		for(a=numChild*wordChild;a<=totalWords;a++)
	    {
			for(b=0;b<strlen(finalString[a]);b++)
		    {
				wFP[c][b]=finalString[a][b];
			}
			wFP[c][b]='\0';
			fprintf(pf,"%s \n",wFP[c]);
			c++;
		}
		//printf("Word for parent: %s %s %s\n",wFP[0],wFP[1],wFP[67]);

	for(j = 0; j <numChild; j++){

		close(fd[2*j+1]);
		read(fd[2*j],wFC,sizeof(wFC)+1);
		close(fd[2*j]);
		for(i=0;i<wordChild;i++)
		{
			fprintf(pf,"%s\n",wFC[i]);
		}
	    //printf("I'm here. %d %s\n",nbits,wFC[67]);
	}
		}

	fclose(pf);
	pf=fopen("pf.txt","r");
	rewind(pf);

	while(fscanf(pf,"%s",buffer)!=EOF)
	{
		insert(buffer);
	}


    FILE *outputfile;
	outputfile=fopen(argv[2],"w");
	while(head!=NULL)
	{
		print(head,outputfile);
		head=head->next;
	}
	
  

    end_t=clock();
    spend_t=(double)(end_t-start_t)/10000;
    fprintf(runtime, "%G\n", spend_t);	
   
	return 0;
}