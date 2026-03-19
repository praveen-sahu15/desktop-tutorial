#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define MAX 100

// Node structure
struct Node
{
    char url[LEN];
    struct Node *next;
};

// Stack top pointers
struct Node *backStack = NULL;
struct Node *forwardStack = NULL;

char current[LEN] = "";
int totalPages = 0; // limit control

// PUSH
void push(struct Node **top, char url[])
{
    if (totalPages >= MAX)
    {
        printf("Limit reached (100 pages max)\n");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->url, url);
    newNode->next = *top;
    *top = newNode;

    totalPages++;
}

// POP
int pop(struct Node **top, char result[])
{
    if (*top == NULL)
        return 0;

    struct Node *temp = *top;
    strcpy(result, temp->url);
    *top = temp->next;
    free(temp);

    totalPages--;
    return 1;
}

// CLEAR STACK
void clearStack(struct Node **top)
{
    char temp[LEN];
    while (pop(top, temp))
        ;
}

// PRINT HISTORY
void printHistory(struct Node *back, char current[], struct Node *forward)
{
    printf("\nHISTORY ---\n");

    // back stack (reverse print)
    struct Node *temp = back;
    while (temp != NULL)
    {
        printf("%s\n", temp->url);
        temp = temp->next;
    }

    if (strlen(current) > 0)
        printf("%s (CURRENT)\n", current);

    temp = forward;
    while (temp != NULL)
    {
        printf("%s\n", temp->url);
        temp = temp->next;
    }
}

int main()
{
    char input[LEN];

    printf("NEW SESSION\n");

    while (1)
    {

        // show current
        if (strlen(current) == 0)
            printf("\nCURRENT: NEW SESSION\n");
        else
            printf("\nCURRENT: %s\n", current);

        // options
        if (backStack == NULL)
            printf("BACK (NO PREVIOUS PAGES)\n");
        else
            printf("Type BACK\n");

        if (forwardStack == NULL)
            printf("NEXT (NO FURTHER PAGES)\n");
        else
            printf("Type NEXT\n");

        printf("Enter URL / BACK / NEXT / PRINT HISTORY:\n");

        fgets(input, LEN, stdin);
        input[strcspn(input, "\n")] = 0;

        // BACK
        if (strcmp(input, "BACK") == 0)
        {
            if (backStack == NULL)
            {
                printf("No previous pages\n");
            }
            else
            {
                push(&forwardStack, current);
                pop(&backStack, current);
            }
        }

        // NEXT
        else if (strcmp(input, "NEXT") == 0)
        {
            if (forwardStack == NULL)
            {
                printf("No further pages\n");
            }
            else
            {
                push(&backStack, current);
                pop(&forwardStack, current);
            }
        }

        // PRINT
        else if (strcmp(input, "PRINT HISTORY") == 0)
        {
            printHistory(backStack, current, forwardStack);
        }

        // NEW URL
        else
        {
            if (strlen(current) > 0)
                push(&backStack, current);

            strcpy(current, input);
            clearStack(&forwardStack); // forward clear
        }
    }

    return 0;
}