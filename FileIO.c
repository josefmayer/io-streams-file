#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10



struct address {
	char name[16];
	char street[16];
	char city[16];
	//char state[3];
	unsigned long int zip;
} address_list[MAX];



void init_list();

char *datafile;


void save(char *datafile)
{
	FILE *fp;
	register int i;

	if ((fp = fopen(datafile, "wb")) == NULL)
	{
		printf("Error in opening file..!!\n");
		return;
	}

	for (i = 0; i<MAX; i++)
	{
		if (*address_list[i].name)
		{
			if (fwrite(&address_list[i], sizeof(struct address), 1, fp) != 1)
			{
				printf("Error in writing to file..!!\n");
			}
		}
	}

	fclose(fp);
}

void load(char *datafile)
{
	FILE *fp;
	register int i;

	if ((fp = fopen(datafile, "rb")) == NULL)
	{
		printf("Error in opening the file..!!\n");
		return;
	}

	init_list();

	for (i = 0; i<MAX; i++)
	{
		if (fread(&address_list[i], sizeof(struct address), 1, fp) != 1)
			{
			if (feof(fp))
			{
				break;
			}
			printf("Error in reading the file..!!\n");
		}
	}
	fclose(fp);
}


void list()
{
	register int i;

	for (i = 0; i<MAX; i++)
	{
		if (address_list[i].name[0])
			{
			printf("%s\n", address_list[i].name);
			printf("%s\n", address_list[i].street);
			printf("%s\n", address_list[i].city);
			//printf("%s\n", address_list[i].state);
			printf("%lu\n\n", address_list[i].zip);
		}
	}
	printf("\n\n");
}


void data_init() {

	init_list();

	strcpy(address_list[0].name, "name1");
	strcpy(address_list[0].street, "street1");
	strcpy(address_list[0].city, "city1");
	address_list[0].zip = 1234;

	strcpy(address_list[1].name, "name2");
	strcpy(address_list[1].street, "street2");
	strcpy(address_list[1].city, "city2");
	address_list[1].zip = 3456;

	strcpy(address_list[2].name, "name3");
	strcpy(address_list[2].street, "street3");
	strcpy(address_list[2].city, "city3");
	address_list[2].zip = 5678;

}


void init_list()
{
	register int i;

	for (i = 0; i<MAX; i++)
	{
		address_list[i].name[0] = '\0';
	}
}


void init_data_in_mem() {
	datafile = "data_in";
	data_init();

	save(datafile);
	load(datafile);

	list();

}

void load_data_file() {
	datafile = "data_in1";

	//data_init();

	//save();
	load(datafile);
	list();
}



int menu_select(void)
{
	char str[80];
	int i;

	printf("1. init data in memory\n");
	printf("2. load data from file\n");
	printf("5. end\n");
	do
	{
		printf("\nEnter your choice: ");
		fgets(str, 80, stdin);
		i = atoi(str);
	} while (i<0 || i>6);

	return i;
}

void user_dialog() {
	char choice;

	for (;;)
	{
		choice = menu_select();
		switch (choice)
		{
		case 1:
			init_data_in_mem();
			break;
		case 2:
			load_data_file();
			break;
		case 5:
			return;
			break;
		}
	}


}

void main()
{
	user_dialog();
	
	//init_data_in_mem();
	//load_data_file();

}