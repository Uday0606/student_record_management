#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct student
{
    int roll_no;
    char name[50];
    char branch[10];
    float cgpa;
    struct student *next;
}student;
void menu();
int is_duplicate_rollno(student *head,int roll_no);
void add_student(student **head);
void display_students(student* head);
void delete_student(student **head);
void save_tofile(student *head);
void load_from_file(student **head);
void pause_screen();

int main()
{
    student *head=NULL;
    int choice;
    load_from_file(&head);
    while(1)
    {
        menu();
        printf("Enter your choice\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
            add_student(&head);
            pause_screen();
            break;

            case 2:
            display_students(head);
            pause_screen();
            break;
            case 3:
            delete_student(&head);
            pause_screen();
            break;
            case 4:
            save_tofile(head);
            pause_screen();
            break;
            case 5:
            printf("Exiting program\n");
            exit(0);

            default:
            printf("Invalid choice.Try again\n");
        }
    
    }
  return 0;
}
void menu()
{
    printf("\n    Student record management    \n");
    printf("1.Add student\n");
    printf("2.Display all studnets\n");
    printf("3.Delete student roll no\n");
    printf("4.Save record to file\n");
    printf("5.Exit\n");
}
void add_student(student **head){
    student *newnode=(student*)malloc(sizeof(student));
    if(newnode==NULL)
    {
        printf("Memory allocation failed\n");
        return ;
    }
    int roll_no;
    printf("Enter roll number\n");
    scanf("%d",&roll_no);
    getchar();
    if(is_duplicate_rollno(*head,roll_no))
    {
        printf("Error: Roll number %d already exists\n",roll_no);
        free(newnode);
        return;
    }
    newnode->roll_no=roll_no;

    printf("Enter name:\n");
    fgets(newnode->name,sizeof(newnode->name),stdin);
    newnode->name[strcspn(newnode->name,"\n")]='\0';

    printf("Enter branch\n");
    fgets(newnode->branch,sizeof(newnode->branch),stdin);
    newnode->branch[strcspn(newnode->branch,"\n")]='\0';

    printf("Enter CGPA\n");
    scanf("%f",&newnode->cgpa);
    getchar();

    //Insert at beginning
    newnode->next=*head;
    *head=newnode;
}
void display_students(student* head)
{
    if(head==NULL)
    {
        printf("No student records to display\n");
        return ;
    }
    printf("STUDENT RECORDS:\n");
    student *temp=head;
    int count=1;
    while(temp!=NULL)
    {
        printf("student %d\n",count++);
        printf("Roll number: %d\n",temp->roll_no);
        printf("Name:%s\n",temp->name);
        printf("Branch:%s\n",temp->branch);
        printf("CGPA:%.2f\n",temp->cgpa);
        printf("------------------\n");
        temp=temp->next;
    }
}
void delete_student(student **head)
{
    if(*head==NULL)
    {
        printf("No records to delete\n");
        return;
    }
    int roll_no;
    printf("Enter roll_no\n");
    scanf("%d",&roll_no);

    student *temp=*head;
    student *prev=NULL;

    if(temp!=NULL && temp->roll_no==roll_no)
    {
        *head=temp->next;
        free(temp);
        printf("Record with roll %d deleted\n",roll_no);
        return;
    }
    //Traverse the list to find node
    while(temp!=NULL && temp->roll_no!=roll_no)
    {
        prev=temp;
        temp=temp->next;
    }
    //if not found
    if(temp==NULL)
    {
        printf("Record with roll %d not found",roll_no);
        return;
    }
    prev->next=temp->next;
    free(temp);
    printf("Record wit roll: %d deleted\n",roll_no);
}
void save_tofile(student *head)
{
    FILE *fp=fopen("students.txt","w");
    if(fp==NULL)
    {
        printf("Error opening file for writing\n");
        return;
    }
    student *temp=head;
    while(temp!=NULL)
    {
        fprintf(fp,"%d,%s,%s,%.2f\n",temp->roll_no,temp->name,temp->branch,temp->cgpa);
        temp=temp->next;
    }
    fclose(fp);
    printf("Records saved to file successfully\n");
}
void load_from_file(student **head)
{
    FILE *fp=fopen("students.txt","r");
    if(fp==NULL)
    {
        printf("No saved file found\n");
        return;
    }
    char line[200];
    while(fgets(line,sizeof(line),fp))
    {
        line[strcspn(line,"\n")]='\0';
        student *newnode=(student*)malloc(sizeof(student));
        if(newnode==NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        //set deafults first
        newnode->roll_no=0;
        strcpy(newnode->name,"");
        strcpy(newnode->branch,"");
        newnode->cgpa=0.0;
        newnode->next=NULL;

        //split by comma
        char *token=strtok(line,",");
        
        if(token!=NULL)
        newnode->roll_no=atoi(token);

        token=strtok(NULL,",");
        if(token!=NULL)
        strcpy(newnode->name,token);

        token=strtok(NULL,",");
        if(token!=NULL)
        strcpy(newnode->branch,token);

        token=strtok(NULL,",");
        if(token!=NULL)
        newnode->cgpa=atof(token);
        
        //add node to list
        if(*head==NULL)
        {
            *head=newnode;
        }
        else{
            student *temp=*head;
            while(temp->next!=NULL)
            {
                temp=temp->next;
                
            }
            temp->next=newnode;
        }
    }

    
}
int is_duplicate_rollno(student *head,int roll_no)
{
    student *temp=head;
    while(temp!=NULL)
    {
        if(temp->roll_no==roll_no)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}
void pause_screen() {
    printf("\nPress Enter to continue...");
    getchar();//to consume newline
    getchar();//wait for user to press enter
}