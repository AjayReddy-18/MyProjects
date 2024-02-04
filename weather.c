#include <stdio.h>
#include <string.h>

void main()
{
	char city[20];
	char api[150];

	printf("Enter city name: ");
	scanf(" %[^\n]s", city);

	sprintf(api, "%s%s%s", "curl \"https://api.openweathermap.org/data/2.5/weather?q=", city, "&appid=abe3a0f4d0b6cebfbe7393b4b4e3aa28&units=metric\" > weather.txt");
	system(api);


	FILE *fpWeather = fopen("weather.txt", "r");
	fseek(fpWeather, 0, SEEK_END);
	char weatherReport[ftell(fpWeather)];
	rewind(fpWeather);
	fread(weatherReport, sizeof(weatherReport), 1, fpWeather);

	char *temperature = strstr(weatherReport, "temp");

	temperature = strtok(temperature, ":");
	temperature = strtok(NULL, ",");

	if (temperature != NULL)
	{
		printf("\nCurrent Temperature in %s is %s degree celsius.\n", city, temperature);
	}else
	{
		printf("\n%s city not found.\n", city);
	}
}