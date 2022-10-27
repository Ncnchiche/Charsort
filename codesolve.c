/* 
 * File name: codesolve.c
 * Author: Nathan Chiche
 * Date: 10/27/2022
 Program Description: 

 Adds strings to doubly link list and sorts them with no duplicates alphabetically: Standard output or output to text file
 Usage: codesolve [-o output_file_name] input_file_name

 -o outputs sorted doubly linked list with no duplicates to new file

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

FILE *infile, *outfile;// internal File Variable

/*-------------------------------------------------------------------------
Constructs backbone of Doubly Linked List
-------------------------------------------------------------------------*/
typedef struct node{
      struct node *next;
      char letter;
      struct node *prev;
}node;

// head node and last node
struct node* head = NULL;
struct node* last = NULL;

/*
-------------------------------------------------------------------------
Functions
---------
addnode() - Add a node to the list
sort() -- sorts in alphabetical order
removeDuplicates() -- remove duplicate letters
traverselist() -- Display list Starts at head then goes through
freeList() -- free's nodes at end of program
-------------------------------------------------------------------------
*/

void addnode(char charinfile){
   // Allocating memory to pointer and create new node
   struct node* newNode = (struct node*)malloc(sizeof(struct node));
   newNode->letter = charinfile;

   // Initiate the previous and next pointers to be NULL. 
   newNode->next = NULL;
   newNode->prev = NULL;

   if(head == NULL){//if empty continue
      //head and tail points new node in list
      head = last = newNode;
      //Both will point to null since either last node or first
      head->prev = NULL;
      last->next = NULL;
   }
   else{//else insert at end of dll
      last->next=newNode;
      //new node prev points to last
      newNode->prev=last;

      //newNode will be placed at back
      last = newNode;
      //since last the next should point to NULL
      last -> next = NULL;
   }
}
void sort(){
   //curent node
   struct node *current = head;
   //temp node
   struct node *temp = head;
   //store char
   char storeval;
   if(current == NULL){
      exit(1);
   }
   else{
      //Current Points to head
      for(current = head; current != NULL; current = current -> next){
         //temp Points to next of current
         for(temp = current->next; temp != NULL; temp = temp -> next){
            //sort alphabetically
            if(current->letter > temp->letter){
               storeval = current->letter;
               current->letter = temp->letter;
               temp->letter = storeval;
            }
         }
      }
   }
}
void removeDuplicates(){
   //current node
   struct node *current = head;
   //temp node to index
   struct node *temp = head;
   //to be deleted node
   struct node *del;

   //checking for errors if li
   if(head == NULL){
      return;
   }
   else{
      //almost same as begining of sort
      //traverse from start if [1] == [2]? [1] == [3]? etc
      //Current Points to head
      for(current = head; current != NULL; current =current -> next){
         //temp will points to next node after current
         for(temp = current->next; temp != NULL; temp = temp -> next){
            //if they are equal
            if(current->letter == temp->letter){
               del = temp;
               //have tmp previous node point to tmp next linking them
               temp->prev->next = temp->next;
               if(temp->next!=NULL){
                  temp ->next->prev = temp->prev;
               }
               del = NULL;

            }
         }
      }
   }
}
void traverselist(){
   //list to head node
   struct node* current = head;
   while(current != NULL){
      // Print data of the node
      printf("%c",current->letter);
      current = current->next;     
   }
   printf("\n");
}
//deallocate memory
void freeList(){
   struct node* tmp=head;
   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

/*
-------------------------------------------------------------------------
I/O Functions -- input and output files
inputfile();- opens file removes whitespaces, Capital letters and adds node to dll
outputfile();- writes doubly linked list to output file
-------------------------------------------------------------------------
*/
void inputfile(char* textfile){
   char letters;

   //OPENS FILE FOR READING
   infile = (fopen(textfile, "r"));
   if (infile == NULL){
      printf("\nError, Unable to open the file for reading\n");
      exit(1);
   }

   //Turn all letters into capital letters in file 
   letters = fgetc(infile);
   while (letters != EOF){
      //if charcter not a space add in node
      if(isgraph(letters)){
         //converting letters to uppercase
         letters = toupper(letters);
         addnode(letters);
         }
      letters = fgetc(infile);
   }
   //CLOSE INFILE
   if (fclose(infile) == EOF){
      printf("\aERROR closing file\n");
      exit (1);
   }
}
void outputfile(char* textfile){
   struct node* current = head;

   FILE *outfile = (fopen(textfile, "w"));
   if (outfile == NULL){
      printf("\nError, Unable to open the file for writing\n");
      exit(1);
   }
   while(current != NULL){
      fputc(current->letter, outfile);
      current = current->next;     
   }
   if (fclose(outfile) == EOF){
      printf("\aERROR closing file\n");
      exit (1);
   }
}

/*
-------------------------------------------------------------------------
Main Function
-------------------------------------------------------------------------
*/
int main(int argc, char **argv){
   /*-----------------------------------------------------------------------
   variables
   -------------------------------------------------------------------------*/
   char inName[50]; //input file name
   char outName[50]; //output file name

   extern char *optarg;
   extern int optind;
   int c, err = 0;
   int oflag=0;

   static char usage[] = "Usage: [-o output_file_name] input_file_name \n";
   /*-----------------------------------------------------------------------
   Get command Line Argument
   -------------------------------------------------------------------------*/
   while((c=getopt(argc, argv,":o:")) != -1){
      switch(c){
         case 'o':
            oflag = 1;
            //argument -o write mode
            //You can't assign to an array, only copy to it. so strcpy();
            strcpy(outName, optarg);
            break;
         case '?':
            err = 1;
            break;
         }
      }
      if ((optind+1) > argc) {  
         /* need at least one argument (change +1 to +2 for two, etc. as needeed) */
         fprintf(stderr, "%s: missing input file\n", argv[0]);
         fprintf(stderr, usage, argv[0]);
         exit(1);
      } 
      else if (err) {
      fprintf(stderr, usage, argv[0]);
      exit(1);
      }
   //You can't assign to an array, only copy to it. so strcpy();
   strcpy(inName, argv[optind]);
   /*-----------------------------------------------------------------------
   Start using functions
   -------------------------------------------------------------------------*/
   //opens file removes whitespaces, Capital letters and adds node to dll
   inputfile(inName);
   //sort linked list
   sort();
   //remove duplicate letters
   removeDuplicates();
   //writes doubly linked list to output file if oflag was called
   if(oflag == 1){
      outputfile(outName);
   }
   //standard output of doubly linked list after sorting, removing duplicates, and whitespaces
   traverselist();
   //deallocates the blocks of memory 
   freeList();
}
