//Makeish Raveendran
//T00772393
//COMP 2131
//Programming Assignment 2
//OL Faculty Member: Dr. Kumka
//January 2nd 2025

#include <stdio.h>
#include <string.h>

//create global file pointer
FILE *file = NULL;

//function prototypes
char* error_menu(char value[5]); //error check function for menu
void create();  //create binary file
void display(); //display all contents of the file
void seek();    //seek a specific record by student ID
void update();  //update the contents of a record by referencing student ID
void delete();  //delete a record for the specific name


//defined a structure to be used  in our file
typedef struct{
        char student_ID[15];
        char name[30];
        char email_ID[30];
        char course_ID[15];
        char grade[15];
}Rec;
Rec students[10]; //set to size of 10

void main()
{
        int i = 0;
        char value[5];
        //run a while loop until the number entered is 6, in which the program ends
        while(i != 6){
                printf("\n\n       M A I N  M E N U\n");
                printf("1. Create the Binary File\n");
                printf("2. Display the contents of the file\n");
                printf("3. Seek a specific record\n");
                printf("4. Update the contents of a record\n");
                printf("5. Delete a record for the specific name\n");
                printf("6. Exit\n\n");
                printf("       Please enter your choice ... ");
                //reads the input and checks to see if the input is valid
                scanf("%s",&value);

                char * val = error_menu(value);

                //stores the value into i, in case the user wishes to leave
                sscanf(val,"%d",&i);
                //set of if statements if integer 1 to 5 is chosen)
                if(i == 1){
                        create();
                }
                if(i == 2){
                        display();
                }
                if(i == 3){
                        seek();
                }
                if(i == 4){
                        update();
                }
                if(i == 5){
                        delete();
                }
        }
}
//function to check error
char* error_menu(char value[5]){
        int val1;

        //checks to see if the array is larger then size of 1 or if it isnt an integer
        if(strlen(value) > 1 || sscanf(value, "%d", &val1) != 1 || val1 > 6 ||  val1 < 1){
                //prompts the user to put in the correct value/desired
                printf("\n\nThe value entered is not an integer between 1-6, please enter an appropriate integer...");
                scanf("%s", value);
                //recursion to check to see if input is still valid
                return error_menu(value);
        }
        //returns the value if in proper format
        return value;
}

//function to create Binary File
void create(){
        //opens the file as a read only
        file = fopen("Records.dat","r");
        //if the file exists, it will exit the function early
        if (file != NULL){
                printf("\nFile already exists, please select a different option.\n");
                //closes file
                fclose(file);
                return;
        }
        else{
                printf("\nDetermine the number student entries to be entered\n");

                int j, k;
                k=0;
                scanf("%d",&j);
                //while loop allowing the user to enter in data
                while(k < j){
                        printf("Enter Student #%d's ID\n",(k+1));
                        scanf("%s",students[k].student_ID);
                        printf("Enter Student #%d's Name\n",(k+1));
                        scanf("%s",students[k].name);
                        printf("Enter Student #%d's Email ID\n",(k+1));
                        scanf("%s",students[k].email_ID);
                        printf("Enter Student #%d's Course ID\n",(k+1));
                        scanf("%s",students[k].course_ID);
                        printf("Enter Student #%d's Grade\n",(k+1));
                        scanf("%s",students[k].grade);
                        k++;
                }
                //if file does not exist, create a file and set a simple template with all the required information
                file = fopen("Records.dat", "w");
                fprintf(file, "Student ID, Student Name, Email ID, Course ID, Grade\n");
                //close the file and print a statement saying a file has been made

                //add the input data into the file using a while loop
                k = 0;
                while(k<j){
                        fprintf(file,"%s,%s,%s,%s,%s\n",students[k].student_ID,students[k].name,students[k].email_ID,students[k].course_ID,students[k].grade);
                        k++;
                }
                fclose(file);
                printf("\nFile has been made, what would you like to do next?.\n");
        }
}

void display(){
        //opens the file in read only
        FILE *file = fopen("Records.dat","r");
        //if the file does not exist it will prompt the user to create one
        if (file == NULL){
                printf("\nFile does not exist, Please create one.\n");
                return;
        }
        //whilte loop that prints out the entire file using feof(file)
        char ch;
        while(1){
                ch = getc(file);
                printf("%c",ch);

                if (feof(file)){
                        fclose(file);
                        return;
                }
        }
}

void seek(){
        char id[15];  //place holder for the desired ID we will search for
        char line[256]; //stores the number of characters in each line in our file
        char original_line[256];
        char* word; // points to first word

        //opens the file in read only and runs a while loop through each line, searching for the word
        FILE *file = fopen("Records.dat","r");

        if (file == NULL){
                printf("\nFile does not exist, Please create one.\n");
                return;
        }
        //prints a statement to ask the user to write the id they want to search for
        printf("\nEnter the student ID of the student you would like information on.\n");
        scanf("%s",id);
        //while loop that itterates through each line in the file till it is empty
        while(fgets(line, sizeof(line), file) != NULL){
                //place holder variable to allow printing later
                strcpy(original_line,line);
                word = strtok(line, ","); //separates the string into the first  word by the comma
                //printf("\n\n%s\n\n", word);
                //uses strcmp to compare strings and if they are the same, print a statement with the record's information
                if (strcmp(word, id) == 0){
                        fclose(file);
                        printf("\nThe Record found is: %s\n",original_line);
                        return;
                }
        }
        //closes the file and prints a statement saying id isnt in tthe file
        fclose(file);
        printf("The requested Student ID is not in our records, sorry.");
}

void update(){
        char id[15];  //place holder for the desired ID we will search for
        char line[256]; //stores the number of characters in each line in our file
        int l = 0;
        //opens the file in read only and runs a while loop through each line, searching for the word
        FILE *file = fopen("Records.dat","r");

        if (file == NULL){
                printf("\nFile does not exist, Please create one.\n");
                return;
        }

        //prints a statement to ask the user to write the id they want to search for
        printf("\nEnter the student ID of the student you would like to update.\n");
        scanf("%s",id);
        //while loop to separate the line to be able to store them into the structure
        while(fgets(line, sizeof(line), file) != NULL){
                strcpy(students[l].student_ID,strtok(line, ","));
                strcpy(students[l].name,strtok(NULL, ","));
                strcpy(students[l].email_ID,strtok(NULL, ","));
                strcpy(students[l].course_ID,strtok(NULL, ","));
                strcpy(students[l].grade,strtok(NULL, "\n"));

                l++;
        }
        fclose(file);
        int a;
        for(a = 0; a < 10; a++){
                //compares our string ID with the files id and if they are the same, allow the user to update their values
                if(strcmp(students[a].student_ID,id)==0){
                        printf("Update Student's ID\n");
                        scanf("%s",students[a].student_ID);
                        printf("Update Student's Name\n");
                        scanf("%s",students[a].name);
                        printf("Update Student's Email ID\n");
                        scanf("%s",students[a].email_ID);
                        printf("Update Student's Course ID\n");
                        scanf("%s",students[a].course_ID);
                        printf("Update Student's Grade\n");
                        scanf("%s",students[a].grade);

                        //delete old file and replace with new file
                        remove("Records.dat");
                        //creates a new file to be written into
                        file = fopen("Records.dat", "w");

                         //add the input data into the file
                         int b = 0;
                         //while loop that write file, based on our structure
                         while(b<l){
                                fprintf(file,"%s,%s,%s,%s,%s\n",students[b].student_ID,students[b].name,students[b].email_ID,students[b].course_ID,students[b].grade);
                                b++;
                         }
                        //closes the file
                        fclose(file);
                        //exits function early
                         printf("\nFile has been updated, what would you like to do next?.\n");
                         return;
                }
        }
        //if the updated id does not exist
        printf("The requested Student ID is not in our records, sorry.");
}
void delete(){
        char id[30];  //place holder for the desired name we will search for
        char line[256]; //stores the number of characters in each line in our file
        int l = 0;
        //opens the file in read only and runs a while loop through each line, searching for the word
        FILE *file = fopen("Records.dat","r");

        if (file == NULL){
                printf("\nFile does not exist, Please create one.\n");
                return;
        }

        //prints a statement to ask the user to write the id they want to search for
        printf("\nEnter the student's name that you would like to remove from the database.\n");
        scanf("%s",id);
        //while loop to separate the line to be able to store them into the structure
        while(fgets(line, sizeof(line), file) != NULL){
                strcpy(students[l].student_ID,strtok(line, ","));
                strcpy(students[l].name,strtok(NULL, ","));
                strcpy(students[l].email_ID,strtok(NULL, ","));
                strcpy(students[l].course_ID,strtok(NULL, ","));
                strcpy(students[l].grade,strtok(NULL, "\n"));

                l++;
        }
        fclose(file);
        int a;
        //for loop that will run for the maximum size of our structure
        for(a = 0; a < 10; a++){
                //compares our string ID with the files id and if they are the same, allow the user to create a new file excluding their the compared student name
                if(strcmp(students[a].name,id)==0){
                        //delete old file and replace with new file
                        remove("Records.dat");
                        //creates a new file to be written into
                        file = fopen("Records.dat", "w");

                         //add the input data into the file
                         int b = 0;
                         //while loop that write file, based on our structure and an if statement to exclude the condition when they were the same
                         while(b<l){
                               if(strcmp(students[b].name,id)!=0){
                                         fprintf(file,"%s,%s,%s,%s,%s\n",students[b].student_ID,students[b].name,students[b].email_ID,students[b].course_ID,students[b].grade);
                               }
                                b++;
                         }
                        //closes the file
                        fclose(file);
                        //exits function early
                         printf("\nFile has been updated, what would you like to do next?.\n");
                         return;
                }
        }
        //if the id needed to be deleted does not exist
        printf("The requested Student's Name is not in our records, sorry.");
}

