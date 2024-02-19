// Program on binary tree using double linked list.

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
	struct LinkedList *leftNode;
	struct LinkedList *rightNode;
}Node;

Node *start;
int id_found = 0;
Node *matchingNode;

void showList(Node *root);

void showNode()
{
	printf("\nItem id: %s", Item.itemId);
	printf("\nItem Description: %s", Item.itemDescription);
	printf("\n%s price: %.2f\n", Item.itemDescription, Item.price);
}

void saveList(Node* root)
{
	if (root != NULL)
	{
        saveList(root->leftNode);
        Item = root->item;
        fwrite(&Item, sizeof(Item), 1, fpDatafile);
        saveList(root->rightNode);
    }
}

void save()
{
	fpDatafile = fopen(DATAFILE, "w");
	saveList(start);
    fclose(fpDatafile);
}

Node* createNode(Node* newNode)
{
	newNode = (Node*)malloc(sizeof(Node));
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;
	return newNode;
}

Node* insertNode(Node* root, Node* newNode)
{
	if (root == NULL)
	{
		root = newNode;
	}else if (strcmp(newNode->item.itemId,root->item.itemId) <= 0)
	{
		root->leftNode = insertNode(root->leftNode, newNode);
	}else
	{
		root->rightNode = insertNode(root->rightNode, newNode);
	}
	return root;
}

void loadList()
{
	start = NULL;
	fpDatafile = fopen(DATAFILE, "r");

	while (fread(&Item, sizeof(Item), 1, fpDatafile))
	{
		Node **current = &start;
		Node *newNode = createNode(newNode);
		newNode->item = Item;

		start = insertNode(start, newNode);
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

	start = insertNode(start, newNode);
	showList(start);
	save();
}

void showList(Node *root)
{
	if (root != NULL)
	{
        showList(root->leftNode);
        Item = root->item;
        showNode();
        showList(root->rightNode);
    }
}

char* readId()
{
	printf("\nEnter ID: ");
	scanf(" %[^\n]s", ID);

	return ID;
}

Node* getMatchingNode(Node* root, char *Id)
{
	if (root != NULL)
	{
		if (!strcmp(root->item.itemId, Id))
		{
			id_found = 1;
			matchingNode = root;
		}else if (strcmp(Id, root->item.itemId) <= 0)
		{
			getMatchingNode(root->leftNode, Id);
		}else
		{
			getMatchingNode(root->rightNode, Id);
		}	
	}

	if(id_found)
	{
		return matchingNode;
	}else
	{
		return NULL;
	}
}

void update(char *Id)
{
	Node *updateNode = getMatchingNode(start, Id);

	if (updateNode != NULL)
	{
		printf("\nEnter price of %s: ", updateNode->item.itemDescription);
		scanf("%f", &updateNode->item.price);
		save();
		printf("\nItem with ID %s updated successfully\n", updateNode->item.itemId);
	}else
	{
		printf(NOTFOUND, Id);
	}
}

Node* findMinimum(Node* root)
{
    if (root == NULL) 
    {
        return NULL;
    }
    else if (root->leftNode != NULL) 
    {
        return findMinimum(root->leftNode);
    }
    return root;
}


Node* delete(Node* root, struct ItemInfo item)
{
	if (root == NULL)
        return NULL;
 
    if (strcmp(item.itemId, root->item.itemId) > 0)
    {
        root -> rightNode = delete (root->rightNode, item);
    }
    else if (strcmp(item.itemId, root->item.itemId) < 0)
    {
        root->leftNode = delete (root->leftNode, item);
    }
    else 
    {
		if (root -> leftNode == NULL && root -> rightNode == NULL)
			{
			    free(root);
			    return NULL;
			}
			else if (root -> leftNode == NULL || root -> rightNode == NULL) 
			{
			    Node* temp;
			    if (root -> leftNode == NULL) 
			    {
			        temp = root -> rightNode;
			    }
			    else 
			    {
			        temp = root -> leftNode;
			    }
			    free(root);
			    return temp;
			}
			else
			{
			    Node* temp = findMinimum(root -> rightNode);
			    root -> item = temp -> item;
			    root -> rightNode = delete (root -> rightNode, temp -> item);
			}
	}
    return root;
}

void search(char* Id)
{
	id_found = 0;
	matchingNode = NULL;
	Node *searchNode = getMatchingNode(start, Id);

	if (searchNode != NULL)
	{
		Item = searchNode->item;
		showNode();
	}else
	{
		printf(NOTFOUND, Id);
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

		case 2 :	showList(start);
					break;

		case 3 :	update(readId());
					break;

		case 4 :	if(getMatchingNode(start, readId()) != NULL)
					{
						delete(start, Item);
						save();
					}
					break;	

		case 5 :	search(readId());
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