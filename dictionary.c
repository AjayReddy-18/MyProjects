// Reading a word and printing its meaning and playing the pronunciation of the word

#include <stdio.h>
#include <string.h>

#define VLC_PATH "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\""

void playAudio(char *wordInfo)
{
	char *audioLink;
	char audio[150];
	audioLink = strstr(wordInfo, "https");
	audioLink = strtok(audioLink, "\"");
	sprintf(audio, "%s %s", VLC_PATH, audioLink);
	system(audio);
	system("cls");
}

void showMeaning(char *wordInfo)
{
	char *ptrMeaning = strtok(wordInfo, "\"");

	while (ptrMeaning != NULL)
	{
		if (!strcmp("partOfSpeech", ptrMeaning) || !strcmp("definition", ptrMeaning))
		{
			if (!strcmp("partOfSpeech", ptrMeaning))
			{
				printf("\n_____________________________________________________________________________________________________________________\n\n");
			}
			while (strcmp(ptrMeaning, ","))
			{
				printf("%s ", ptrMeaning);
				ptrMeaning = strtok(NULL, "\"");
			}
			printf("\n");
		}else
		{
			ptrMeaning = strtok(NULL, "\"");
		}
	}
}

void main()
{
	char word[20];
	char api[100];

	printf("\nEnter a word to know it's meaning: ");
	scanf(" %[^\n]s", word);

	sprintf(api, "%s%s%s", "curl \"https://api.dictionaryapi.dev/api/v2/entries/en/", word, "\" > dictionary.txt");
	system(api);
	system("cls");

	FILE *fpDictionary = fopen("dictionary.txt", "r");
	fseek(fpDictionary, 0, SEEK_END);
	char wordInfo[ftell(fpDictionary)];
	rewind(fpDictionary);
	fread(wordInfo, sizeof(wordInfo), 1, fpDictionary);
	fclose(fpDictionary);

	if (strstr(wordInfo, "No Definitions Found"))
	{
		printf("\nNo Definitions Found for the word %s\n", word);
	}else
	{
		int choice;

		printf("\nWord: %s\n", word);

		printf("\n 1. Show meaning of the word \"%s\"\n 2. Listen to pronunciation of the word \"%s\"\n", word, word);
		printf("\nEnter your choice: ");
		scanf("%d", &choice);

		if (choice == 1)
		{
			showMeaning(wordInfo);
		}else if (choice == 2)
		{
			playAudio(wordInfo);
		}else
		{
			printf("\nInvalid input.\n");
		}
	}
}