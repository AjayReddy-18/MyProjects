// File handling using linked Lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATAFILE "itemsList.dat"
#define NOTFOUND "\nItem with ID %s not found.\n"

FILE *fpDatafile;
char ID[20];

struct ItemInfo
{
	char itemId[20];
	char itemDescription[30];
	float price;
}Item;

typedef struct LinkedList
{
	struct ItemInfo item;
	struct LinkedList *nextNode;
}Node;

Node *start;

void loadList();
Node* createNode(Node*);
void create();
void showNode();
void showList();
void saveList();
char* readId();
Node* getNodeAddress(char*);
void search();
void update();
void delete();
void sort();
void showMenu();

Node* createNode(Node* newNode)
{
	newNode = (Node*)malloc(sizeof(Node));
	newNode->nextNode = NULL;
	return newNode;
}

void loadList()
{
	Node *lastNode;
	start = lastNode = NULL;
	fpDatafile = fopen(DATAFILE, "r");

	while (fread(&Item, sizeof(Item), 1, fpDatafile))
    {
		Node *newNode = createNode(newNode);
		newNode->item = Item;

		if (start == NULL)
		{
			start = newNode;
		}else
		{
			lastNode->nextNode = newNode;
		}
		lastNode = newNode;
    }
}

void showNode()
{
	printf("\nItem id: %s", Item.itemId);
	printf("\nItem Description: %s", Item.itemDescription);
	printf("\n%s price: %.2f\n", Item.itemDescription, Item.price);
}

void showList()
{
	Node *current = start;

	if (start == NULL)
	{
		printf("\nNo items found.\n");
	}

	while (current != NULL)
	{
		Item = current->item;
		showNode();
		current = current->nextNode;
	}
}

void saveList()
{
	Node *current = start;

	fpDatafile = fopen(DATAFILE, "w");
	while (current != NULL)
	{
		fwrite(&current->item, sizeof(Item), 1, fpDatafile);
		current = current->nextNode;
	}
	fclose(fpDatafile);	
}

void create()
{
	Node **lastNode = &start;
	Node *newNode = createNode(newNode);

	printf("\nEnter item id: ");
	scanf(" %[^\n]s", newNode->item.itemId);
	printf("Enter item Description: ");
	scanf(" %[^\n]s", newNode->item.itemDescription);
	printf("Enter price of %s: ", newNode->item.itemDescription);
	scanf("%f", &newNode->item.price);

	while ((*lastNode) != NULL)
	{
		lastNode = &(*lastNode)->nextNode;
	}

	*lastNode = newNode;
	saveList();
	printf("\nItem with ID %s added successfully\n", newNode->item.itemId);
}

char* readId()
{
	printf("\nEnter ID: ");
	scanf(" %[^\n]s", ID);

	return ID;
}

Node* getNodeAddress(char *Id)
{
	Node *current = start;

	while (current != NULL)
	{
		if (!strcmp(current->item.itemId, Id))
		{
			return current;
		}
		current = current->nextNode;
	}
	return NULL;
}

void search(char *Id)
{
	Node *searchedNode = getNodeAddress(Id);

	if (searchedNode != NULL)
	{
		Item = searchedNode->item;
		showNode();
	}else
	{
		printf(NOTFOUND, Id);
	}
}

void update(char *Id)
{
	Node *updateNode = getNodeAddress(Id);

	if (updateNode != NULL)
	{
		printf("\nEnter price of %s: ", updateNode->item.itemDescription);
		scanf("%f", &updateNode->item.price);
		saveList();
		printf("\nItem with ID %s updated successfully\n", updateNode->item.itemId);
	}else
	{
		printf(NOTFOUND, Id);
	}
}

void delete(Node* deleteNode)
{
	Node **deleteNodePointer;
	char confirmation;

	if (deleteNode != NULL)
	{
		Item = deleteNode->item;
		showNode();
		printf("\nAre you sure do you want to delete Item with ID %s (Press 'Y' to delete / Any key to cancel) ", deleteNode->item.itemId);
		confirmation = getch();

		if (confirmation == 'Y' || confirmation == 'y')
		{
			deleteNodePointer = &start;

			while ((*deleteNodePointer) != deleteNode)
			{
				deleteNodePointer = &(*deleteNodePointer)->nextNode;
			}

			*deleteNodePointer = deleteNode->nextNode;

			printf("\nItem with ID %s deleted successfully\n", deleteNode->item.itemId);
			free(deleteNode);
			saveList();
		}else
		{
			printf("\nDelete operation cancelled.\n");
		}
	}
}

void sort()
{
	int choice;

	printf("\nSort by\n");
	printf(" 1. ID\n 2. Description\n 3. Price\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	if (choice > 0 && choice < 4)
	{
		Node **smallNodePointer = &start;
		Node **compareNodePointer;

		while ((*smallNodePointer) != NULL)
		{
			compareNodePointer = &start->nextNode;
			while ((*compareNodePointer) != NULL)
			{
				if ((choice == 1 || choice == 2) ? ((choice == 1) ? strcmp((*smallNodePointer)->item.itemId, (*compareNodePointer)->item.itemId) > 0 : strcmp((*smallNodePointer)->item.itemDescription, (*compareNodePointer)->item.itemDescription) > 0) : (*smallNodePointer)->item.price > (*compareNodePointer)->item.price)
				{
					smallNodePointer = compareNodePointer;
				}		
				compareNodePointer = &(*compareNodePointer)->nextNode;
			}
			Item = (*smallNodePointer)->item;
			showNode();
			
			*smallNodePointer = (*smallNodePointer)->nextNode;
			smallNodePointer = &start;
		}
		loadList();
	}else
	{
		printf("\nInvalid choice\n");
	}
}

void showMenu()
{
	int choice;

	system("cls");

	printf("\n  A-Mart  \n----------\n");
	printf("\n 1. Add Item");
	printf("\n 2. Show Items");
	printf("\n 3. Update Item");
	printf("\n 4. Delete Item");
	printf("\n 5. Search Item");
	printf("\n 6. Sort Items");
	printf("\n\nEnter 0 to exit\n");

	printf("\nEnter your choice: ");
	scanf("%d", &choice);

	printf("\n-------------------------------------------------------------\n");

	switch (choice)
	{
		case 0 : 	printf("\nBye Bye...\n");
					exit(1);

		case 1 :	create();
					break;

		case 2 :	showList();
					break;

		case 3 :	update(readId());
					break;

		case 4 :	delete(getNodeAddress(readId()));
					break;

		case 5 :	search(readId());
					break;

		case 6 :	sort();
					break;

		default :	printf("\nInvalid input, Try again.\n");
					break;
	}
	printf("\n");
	system("pause");
}

void main()
{
	loadList();

	while (1)
	{
		showMenu();
	}
}
