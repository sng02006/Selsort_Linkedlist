#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/////////////////////////////////////////////
struct NODE {
    int val;
    struct NODE *next;
};

/////////////////////////////////////////////
void freelist(struct NODE *head)
{
    struct NODE *next;
    while ( head ) {
        next = head->next;
        free(head);
        head = next;
  }
}

/////////////////////////////////////////////
void printlist(struct NODE *head)
{
    int i = 0;
    while ( head ) {
        fprintf(stdout, "[%5d] : %d\n", i, head->val);
        head = head->next;
        i++;
  }
}

/////////////////////////////////////////////
// List SELECTION SORT
struct NODE* selectionsort_list(struct NODE *head)
{
    int i = 0;
    struct NODE *sorted = NULL;
    struct NODE *minimum = NULL;
    struct NODE *current = NULL;
	struct NODE *temp1 = NULL;
	struct NODE *temp2 = NULL;
	struct NODE *temp3 = NULL;

    while(head->next) {
        minimum = current = head;

        while(current->next){
            current = current->next;

            if ((minimum->val) > (current->val)) {
                minimum = current;
            }
        }

        current = head;
        head = minimum;

        temp1 = minimum->next;
        minimum->next = current;
        temp2 = current;

        while((temp2->next) != minimum) {
            temp2 = temp2->next;

            if ((temp2->next) == minimum) {
                temp2->next = current;
                minimum->next = current->next;
                break;
            }
        }
        current->next = temp1;

        head = minimum->next;

        if(i == 0){
            sorted = temp3 = minimum;
            i++;
        }
        else {
            temp3->next = minimum;
            temp3 = temp3->next;
        }
    }
    return sorted;
}

/////////////////////////////////////////////

int main()
{
    FILE *fp;//
    fp = fopen("input10000.txt", "r");//
    int i, N;
    int val;
    struct NODE *head, *tail, *cur;

    fprintf(stderr, "How many numbers? ");
    fscanf(fp, "%d", &N);//

    head = tail = NULL;

    for (i=0; i<N; i++) {
        if ( fscanf(fp, "%d", &val) != 1 ) {
            fprintf(stderr, "cannot read integer from standard input.\n");
            freelist(head);
            exit(0);
        }
        else {
            cur = (struct NODE*) malloc(sizeof(struct NODE));

            cur->val = val;
            cur->next = NULL;

            if ( !head ) {
                head = tail = cur;
            }
            else {
                tail->next = cur;
                tail = cur;
            }
        }
    }
    head = selectionsort_list(head);

    printlist(head);
    fclose(fp);

    // free memory
    freelist(head);

    return 0;
}
