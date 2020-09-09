/*
    can be used as a good starting point for the ready queue needed to be created for the assignment
*/

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h> 
#include<math.h>

struct test_struct
{
    //int val;
	/////////
	int first;
	int second;
	/////////
    struct test_struct *next;
};

struct test_struct *head = NULL;
struct test_struct *curr = NULL;

struct test_struct* create_list(int first, int second)
{
    printf("\n creating list with headnode as [%d, %d]\n",first, second);
    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->first = first;
	ptr->second = second;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}

struct test_struct* add_to_list(int first, int second, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(first, second));
    }

    if(add_to_end)
        printf("\n Adding node to end of list with value [%d, %d]\n",first, second);
    else
        printf("\n Adding node to beginning of list with value [%d,%d]\n",first, second);

    struct test_struct *ptr = (struct test_struct*)malloc(sizeof(struct test_struct));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    ptr->first = first;
    ptr->second = second;
    ptr->next = NULL;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}

struct test_struct* search_in_list(int first, int second, struct test_struct **prev)
{
    struct test_struct *ptr = head;
    struct test_struct *tmp = NULL;
    bool found = false;

    printf("\n Searching the list for value [%d, %d] \n",first, second);

    while(ptr != NULL)
    {
        if(ptr->first == first && ptr->second == second)
        {
            found = true;
            break;
        }
        else
        {
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}

int delete_from_list(int first, int second)
{
    struct test_struct *prev = NULL;
    struct test_struct *del = NULL;

    printf("\n Deleting value [%d, %d] from list\n",first, second);

    del = search_in_list(first, second,&prev);
    if(del == NULL)
    {
        return -1;
    }
    else
    {
        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = NULL;

    return 0;
}

void print_list(void)
{
    struct test_struct *ptr = head;

    printf("\n -------Printing list Start------- \n");
    while(ptr != NULL)
    {
        printf("\n [%d, %d] \n",ptr->first, ptr->second);
        ptr = ptr->next;
    }
    printf("\n -------Printing list End------- \n");

    return;
}

int main(int argc, char *argv[])
{
    //////////////////////////////
    FILE * fp;
    char * line = NULL;
 	char *filename;
	size_t len = 0;
	ssize_t read;
	
    if (argc < 2)
    {
        printf("./structListExt filename\n");
        return(1);
    }
    else
   {
        filename = argv[1];
   }

	fp = fopen(filename,"r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
	///////////////////////////////
	
    int ret;
    struct test_struct *ptr = NULL;

    print_list();

	//////////////////////
	while ((read = getline(&line, &len, fp)) != -1) {
		char *tok=strtok(line," ");
		int f = atoi(tok);
		int s;
		
		 printf("s4=%d \n",f);
		
        while(tok!=NULL)
        {
		
			printf("s3=%d \n",f);
            tok=strtok(NULL," \r\n"); // NULL instead of pointer
			printf("s1=%d \n",f);
			if(tok==NULL)break;
			s = atoi(tok);
			printf("s2=%d \n",s);
		}
		printf("f=%d, s=%d \n",f,s);			
		add_to_list(f,s,true);
		print_list();
		printf("pppppppppppppppppppppp");
		
	}
	/////////////////////
	
    //for(i = 5; i<10; i++)
    //    add_to_list(i,true);

    //print_list();

    //for(i = 4; i>0; i--)
    //    add_to_list(i,false);

    print_list();
	
	ptr = search_in_list(1, 6, NULL);
	if(NULL == ptr)
	{
		printf("\n Search failed, no such element found\n");
	}
	else
	{
		printf("\n Search passed [val = %d, %d]\n",ptr->first,ptr->second);
	}

	print_list();

	ret = delete_from_list(2, 4);
	if(ret != 0)
	{
		printf("\n delete failed, no such element found\n");
	}
	else
	{
		printf("\n deleted\n");
	}
	
	print_list();

    return 0;
}