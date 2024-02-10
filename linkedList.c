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

Node *start, *lastNode, *dummy, *temp;

Node* createNode(Node* newNode)
{
	newNode = (Node*)malloc(sizeof(Node));
	newNode->nextNode = NULL;
	return newNode;
}

void loadList()
{
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
	Node *newNode = createNode(newNode);

	printf("\nEnter item id: ");
	scanf(" %[^\n]s", newNode->item.itemId);
	printf("Enter item Description: ");
	scanf(" %[^\n]s", newNode->item.itemDescription);
	printf("Enter price of %s: ", newNode->item.itemDescription);
	scanf("%f", &newNode->item.price);

	if (start == NULL)
	{
		start = newNode;
	}else
	{
		lastNode->nextNode = newNode;
	}
	lastNode = newNode;
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
	dummy = temp;
	dummy->nextNode = start;

	while (dummy->nextNode != NULL)
	{
		if (!strcmp(dummy->nextNode->item.itemId, Id))
		{
			return dummy;
		}
		dummy = dummy->nextNode;
	}
	return NULL;
}

void search(char *Id)
{
	Node *searchedNode = getNodeAddress(Id);

	if (searchedNode != NULL)
	{
		Item = searchedNode->nextNode->item;
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
		printf("\nEnter price of %s: ", updateNode->nextNode->item.itemDescription);
		scanf("%f", &updateNode->nextNode->item.price);
		saveList();
		printf("\nItem with ID %s updated successfully\n", updateNode->nextNode->item.itemId);
	}else
	{
		printf(NOTFOUND, Id);
	}
}

void delete(char *Id)
{
	Node *deleteNode = getNodeAddress(Id);

	if (deleteNode != NULL)
	{
		printf("\nItem with ID %s deleted successfully\n", deleteNode->nextNode->item.itemId);
		if (deleteNode->nextNode == start)
		{
			// deleteNode = start;
			start = start->nextNode;
		}else if (deleteNode->nextNode == lastNode)
		{
			lastNode = deleteNode;
			// deleteNode = deleteNode->nextNode;
			lastNode->nextNode = NULL;
		}else
		{
			deleteNode->nextNode = deleteNode->nextNode->nextNode;
		}
		saveList();
	}else
	{
		printf(NOTFOUND, Id);
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
		Node *small = temp, *compare = start;

		while (compare != NULL)
		{
			small->nextNode = start;
			while (compare->nextNode != NULL)
			{
				if ((choice == 1 || choice == 2) ? ((choice == 1) ? strcmp(small->nextNode->item.itemId, compare->nextNode->item.itemId) > 0 : strcmp(small->nextNode->item.itemDescription, compare->nextNode->item.itemDescription) > 0) : small->nextNode->item.price > compare->nextNode->item.price)
				{
					small = compare;
				}		
				compare = compare->nextNode;
			}
			Item = small->nextNode->item;
			showNode();
			if (small->nextNode == start)
			{
				start = start->nextNode;
			}else
			{
				small->nextNode = small->nextNode->nextNode;
			}
			compare = start;
			small = temp;
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

	printf("\n------------------------------------------------------------------------\n");

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

		case 4 :	delete(readId());
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
	dummy = (Node*)malloc(sizeof(Node));
	temp = dummy;

	loadList();

	while (1)
	{
		showMenu();
	}
}