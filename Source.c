#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#pragma warning (disable: 4996)

void setcolor(int ForgC);
void mainMenu();
void adminPage();
int adminIdCheck(char idEntry[10]);
void logIn();
void signUp();
void adminAccess();
void manageAccount();
void addMedicine();
int medIdCheck(char medIdEntry[10]);
void deleteMedicine();
void modifyMedicine();
void searchMedicine();
void findID();
void findName();
void listExpire();
void customerPage();
void viewAll();
void purchasePortal();
void readReceipts();

int main()
{
	setcolor(90);
	mainMenu();
}

void setcolor(int ForgC)
{
	WORD windowColor;
	HANDLE outSTD = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ICSBI;

	if (GetConsoleScreenBufferInfo(outSTD, &ICSBI))
	{
		windowColor = (ICSBI.wAttributes & (int)176) + (ForgC & (int)11);
		SetConsoleTextAttribute(outSTD, windowColor);
	}
}

struct admin
{
	char adminID[10];
	char adminName[30];
	char phoneNumber[20];
}ad;

struct medicine
{
	char medicineID[10];
	char medicineName[30];
	char manufacturer[30];
	float price;
	int quantity;
	char productionDate[10];
	char expiryDate[10];
}md;

void mainMenu()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System                      \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Log in as Admin\n");      // the main menu of the system
	printf("2. Customer page\n");
	printf("3. Exit\n");
	printf("\n________________________________________________________________\n");
	printf("\n\xB2 Select one option: ");

	switch (getche())
	{
	case '1':
		adminPage();
		break;
	case '2':
		customerPage();
		break;
	case '3':
		exit(1);
	default:
		printf("\nInvalid Entry!\n\n");
		system("PAUSE");
		system("CLS");
		mainMenu();
	}
}

void adminPage()
{
	char password[5];
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                   Pharmacy Admin Access                        \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Log in\n");
	printf("2. Add an admin\n");
	printf("3. Go back to Main menu\n");
	printf("\n________________________________________________________________\n");
	printf("\n\xB2 Select one option: ");

	switch (getche())
	{
	case '1':
		logIn();
		break;
	case '2':
		printf("\nPASSWORD ('pass')----------- This is the password by the manager to add admins");
		printf("\nEnter password: ");
		scanf("%s", &password);
		if (strcmp(password, "pass") == 0)
			signUp();
		else
		{
			printf("\nWrong password\n");
			system("PAUSE");
			system("CLS");
			adminPage();
		}
		break;
	case '3':
		mainMenu();
	default:
		printf("\nInvalid Entry!\n\n");
		system("PAUSE");
		system("CLS");
		adminPage();
	}
}

int adminIdCheck(char idEntry[10])
{
	FILE* fav;
	fav = fopen("admin.txt", "r");
	while (!feof(fav))
	{
		fread(&ad, sizeof(ad), 1, fav);
		if (strcmp(idEntry, ad.adminID) == 0)
		{
			fclose(fav);
			return 1;
		}
	}
	fclose(fav);
	return 0;
}

void logIn()
{
	char idEntry[10];
	int checkId;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System                      \n");
	printf("\n________________________________________________________________\n\n");
	printf("\xB2 Type admin ID: ");
	scanf("%s", &idEntry);
	checkId = adminIdCheck(idEntry);
	if (checkId == 0)
	{
		printf("\n\xB2 This ID is not available!\n");
		system("PAUSE");
		system("CLS");
		adminPage();
	}
	else
		adminAccess();
}

void signUp()
{
	int idCheck3;
	char adminRead[10];
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Admin sign up                             \n");
	printf("\n________________________________________________________________\n\n");
	FILE* fAdmin;
	fAdmin = fopen("admin.txt", "a+");
	printf("\n\xB2 Assign admin ID: ");
	scanf("%s", &adminRead);
	idCheck3 = adminIdCheck(adminRead);
	if (idCheck3 == 1)
		printf("\nThis ID already exists\n");
	else
	{
		strcpy(ad.adminID, adminRead);
		printf("\n\xB2 Enter name: ");
		scanf("%s", &ad.adminName);
		printf("\n\xB2 Enter phone number: ");
		scanf("%s", &ad.phoneNumber);
		fwrite(&ad, sizeof(ad), 1, fAdmin);
		fclose(fAdmin);
		printf("\n\n\xB2 Admin registered successfully, ");
	}
	system("PAUSE");
	system("CLS");
	adminPage();
}

void adminAccess()
{
	system("CLS");
	printf("\xB2 Welcome back, %s", ad.adminName);
	printf("\n________________________________________________________________\n");
	printf("\n                     Admin Access Page                          \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Manage accounts\n");
	printf("2. Add a new medicine\n");
	printf("3. Delete an existing medicine\n");
	printf("4. Modify an existing medicine\n");
	printf("5. Search for an existing medicine\n");
	printf("6. View all receipts and invoice data\n");
	printf("7. List out expiry dates of the medicines\n");
	printf("8. Back to the main menu\n");
	printf("\n\xB2 Enter an option: ");
	switch (getche())
	{
	case '1':
		manageAccount();
		break;
	case '2':
		addMedicine();
		break;
	case '3':
		deleteMedicine();
		break;
	case '4':
		modifyMedicine();
		break;
	case '5':
		searchMedicine();
		break;
	case '6':
		readReceipts();
		break;
	case '7':
		listExpire();
		break;
	case '8':
		mainMenu();
		break;
	default:
		printf("\n\xB2 Invalid Entry\n");
		system("PAUSE");
		system("CLS");
	}
	adminAccess();
}

void manageAccount()
{
	char idRead[10];
	int idAva;
	FILE* updateAdmin;
	FILE* tempAdmin;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Update Account Information                      \n");
	printf("\n________________________________________________________________\n\n");
	printf("Enter admin ID: ");
	scanf("%s", &idRead);
	idAva = adminIdCheck(idRead);
	if (idAva == 0)
	{
		printf("This ID is not available, ");
		system("PAUSE");
		system("CLS");
		adminPage();
	}
	else
	{
		updateAdmin = fopen("admin.txt", "r");
		tempAdmin = fopen("admin temp.txt", "w");
		while (fread(&ad, sizeof(ad), 1, updateAdmin))
		{
			if (strcmp(ad.adminID, idRead) != 0)
			{
				fwrite(&ad, sizeof(ad), tempAdmin, 1);
			}
				
			else
			{
				strcpy(ad.adminID, idRead);
				printf("\nFill up the information below");
				printf("\nAdmin Name: ");
				scanf("%s", &ad.adminName);
				printf("\nPhone Number: ");
				scanf("%s", &ad.phoneNumber);
				fwrite(&ad, sizeof(ad), 1, tempAdmin);
			}
			fclose(tempAdmin);
			fclose(updateAdmin);
			updateAdmin = fopen("admin.txt", "w");
			tempAdmin = fopen("admin temp.txt", "r");
			while (fread(&ad, sizeof(ad), 1, tempAdmin))
				fwrite(&ad, sizeof(ad), 1, updateAdmin);
			fclose(updateAdmin);
			fclose(tempAdmin);
		}
	}
	printf("\n\xB2 Admin inofrmation updated successfully\n");
	system("PAUSE");
	system("CLS");
	adminAccess();
}

void addMedicine()
{
	int medCheck;
	char idChecking[10];
	FILE* addMed;
	addMed = fopen("medicine.txt", "a+");
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                       Add Medicine                             \n");
	printf("\n________________________________________________________________\n\n");
	printf("\nAssign a medicine ID: ");
	scanf("%s", &idChecking);
	medCheck = medIdCheck(idChecking);
	if (medCheck == 1)
		printf("\n\xB2This ID is already assigned\n");
	else
	{
		strcpy(md.medicineID, idChecking);
		printf("\nEnter medicine name: ");
		scanf("%s", &md.medicineName);
		printf("\nEnter manufacturer name: ");
		scanf("%s", &md.manufacturer);
		printf("\nEnter price per unit: ");
		scanf("%f", &md.price);
		printf("\nEnter quantity received (in unit): ");
		scanf("%i", &md.quantity);
		printf("\n(i.e.): 2019-09");
		printf("\nEnter production date (as the example above): ");
		scanf("%s", &md.productionDate);
		printf("\nEnter expiry date (as the example above): ");
		scanf("%s", &md.expiryDate);
		fwrite(&md, sizeof(md), 1, addMed);
		fclose(addMed);
		printf("\n\xB2 Medicine Added successfully\n");
	}
	system("PAUSE");
	system("CLS");
	adminAccess();
}

int medIdCheck(char medIdEntry[10])
{
	FILE* fav1;
	fav1 = fopen("medicine.txt", "r");
	while (!feof(fav1))
	{
		fread(&md, sizeof(md), 1, fav1);
		if (strcmp(medIdEntry, md.medicineID) == 0)
		{
			fclose(fav1);
			return 1;
		}
	}
	fclose(fav1);
	return 0;
}

void deleteMedicine()
{
	int returnedValue;
	char readMed[10];
	FILE* deleteMed;
	FILE* tempDMed;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Delete Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("Enter Medicine ID: ");
	scanf("%s", &readMed);
	returnedValue = medIdCheck(readMed);
	if (returnedValue == 0)
	{
		printf("\nThe entered ID is not available\n");
		system("PAUSE");
		system("CLS");
		adminAccess();
	}
	else
	{
		deleteMed = fopen("medicine.txt", "r");
		tempDMed = fopen("medicine temp.txt", "w");
		while (fread(&md, sizeof(md), 1, deleteMed))
			if (strcmp(md.medicineID, readMed) != 0)
				fwrite(&md, sizeof(md), 1, tempDMed);
		fclose(deleteMed);
		fclose(tempDMed);
		deleteMed = fopen("medicine.txt", "w");
		tempDMed = fopen("medicine temp.txt", "r");
		while (fread(&md, sizeof(md), 1, tempDMed))
			fwrite(&md, sizeof(md), 1, deleteMed);
		printf("\n\xB2 Medicine record deleted successfully\n");
		system("PAUSE");
		system("CLS");
		adminAccess();
	}
}

void modifyMedicine()
{
	char medIdRead1[10];
	int medIdCheck1;
	FILE* mainFile;
	FILE* tempFile;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Modify Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("Enter medicine ID: ");
	scanf("%s", medIdRead1);
	medIdCheck1 = medIdCheck(medIdRead1);
	if (medIdCheck1 == 0)
	{
		printf("No record of this medicine ID found\n");
		system("PAUSE");
		system("CLS");
		adminAccess();
	}
	else
	{
		mainFile = fopen("medicine.txt", "r");
		tempFile = fopen("medicine temp.txt", "w");
		while (fread(&md, sizeof(md), 1, mainFile))
		{
			if (strcmp(md.medicineID, medIdRead1) != 0)
				fwrite(&md, sizeof(md), 1, tempFile);
			else
			{
				printf("\nEnter the updated information below\n\n");
				printf("\nEnter medicine name: ");
				scanf("%s", &md.medicineName);
				printf("\nEnter manufacturer name: ");
				scanf("%s", &md.manufacturer);
				printf("\nEnter price per unit: ");
				scanf("%f", &md.price);
				printf("\nEnter quantity received (in unit): ");
				scanf("%i", &md.quantity);
				printf("\n(i.e.): 2019-09");
				printf("\nEnter production date (as the example above): ");
				scanf("%s", &md.productionDate);
				printf("\nEnter expiry date (as the example above): ");
				scanf("%s", &md.expiryDate);
				fwrite(&md, sizeof(md), 1, tempFile);
			}
		}
		fclose(mainFile);
		fclose(tempFile);
		mainFile = fopen("medicine.txt", "w");
		tempFile = fopen("medicine temp.txt", "r");
		while (fread(&md, sizeof(md), 1, tempFile))
			fwrite(&md, sizeof(md), 1, mainFile);
		fclose(mainFile);
		fclose(tempFile);
	}
	printf("\nMedicine record modified successfully\n");
	system("PAUSE");
	system("CLS");
	adminAccess();
}

void searchMedicine()
{
	char searchId, searchName;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                      Search Medicine                           \n");
	printf("\n________________________________________________________________\n\n");
	printf("1. Search by ID\n");
	printf("2. Search by name\n");
	printf("Enter your preference: ");
	switch (getche())
	{
	case '1':
		findID();
		break;
	case '2':
		findName();
		break;
	default:
	{
		printf("\nInvalid Entry!\n");
		system("PAUSE");
		system("CLS");
		searchMedicine();
	}
	}
	return;
}

void findID()
{
	FILE* searchId;
	char seaMedId[10];
	int seaMedCheck;
	printf("\n________________________________________________________________\n");
	printf("Enter medicine ID: ");
	scanf("%s", seaMedId);
	seaMedCheck = medIdCheck(seaMedId);
	if (seaMedCheck == 0)
	{
		printf("\nNo record found of the ID provided\n");
		system("PAUSE");
		system("CLS");
		return;
	}
	else
	{
		searchId = fopen("medicine.txt", "r");
		while (fread(&md, sizeof(md), 1, searchId))
		{
			if (stricmp(md.medicineID, seaMedId) == 0)
			{
				printf("\nMedicine ID=\t\t\t%s", md.medicineID);
				printf("\nMedicine Name=\t\t\t%s", md.medicineName);
				printf("\nManufacturer Name=\t\t%s", md.manufacturer);
				printf("\nMedicine price=\t\t\tRM %0.2f", md.price);
				printf("\nQuantity in stock=\t\t%d", md.quantity);
				printf("\nProduction Date=\t\t%s", md.productionDate);
				printf("\nExpiry Date=\t\t\t%s", md.expiryDate);
				fclose(searchId);
				printf("\n\n");
				system("PAUSE");
				system("CLS");
				return;
			}
		}
	}
}

void findName()
{
	FILE* searchName;
	char seaMedName[30];
	int seaMedCheck1;
	printf("\n________________________________________________________________\n");
	printf("Enter medicine name: ");
	scanf("%s", &seaMedName);
	searchName = fopen("medicine.txt", "r");
	while (fread(&md, sizeof(md), 1, searchName))
	{
		if (stricmp(md.medicineName, seaMedName) == 0)
		{
			printf("\nMedicine ID=\t\t\t%s", md.medicineID);
			printf("\nMedicine Name=\t\t\t%s", md.medicineName);
			printf("\nManufacturer Name=\t\t%s", md.manufacturer);
			printf("\nMedicine price=\t\t\tRM %0.2f", md.price);
			printf("\nQuantity in stock=\t\t%d", md.quantity);
			printf("\nProduction Date=\t\t%s", md.productionDate);
			printf("\nExpiry Date=\t\t\t%s", md.expiryDate);
			fclose(searchName);
			printf("\n\n");
			system("PAUSE");
			system("CLS");
			adminAccess();
		}
	}
	printf("\nNo record found of the NAME provided\n");
	system("PAUSE");
	system("CLS");
	adminAccess();
}

void listExpire()
{
	FILE* list;
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                        Expiry Dates                            \n");
	printf("\n________________________________________________________________\n\n");
	list = fopen("medicine.txt", "r");
	if (list == 0)
		printf("\n\nNo record of medicines found\n");
	else
	{
		printf("Medicine ID\t\tMedicine Name\t\tExpiry Date");
		printf("\n________________________________________________________________\n\n");
		while (fread(&md, sizeof(md), 1, list))
			printf("\n%s\t\t\t%s\t\t%s", md.medicineID, md.medicineName, md.expiryDate);
		fclose(list);
		printf("\n________________________________________________________________\n\n");
	}
	system("PAUSE");
	system("CLS");
	adminAccess();
}

void customerPage()
{
	system("CLS");
	printf("\n________________________________________________________________\n");
	printf("\n                Pharmacy Management System             |Customer\n");
	printf("\n________________________________________________________________\n\n");
	printf("1. View all medicines\n");
	printf("2. Search for a medicine\n");
	printf("3. Buy products\n");
	printf("4. Back to the main menu.\n");
	printf("\n________________________________________________________________\n");
	printf("\n\xB2 Select one option: ");
	switch (getche())
	{
	case '1':
		viewAll();
		break;
	case '2':
		searchMedicine();
		break;
	case '3':
		purchasePortal();
		break;
	case '4':
		mainMenu();
		break;
	default:
		printf("\n\xB2 Invalid choice\n");
	}
	system("PAUSE");
	system("CLS");
	customerPage();
}

void viewAll()
{
	FILE* view;
	system("CLS");
	printf("\n_________________________________________________________________________________\n");
	printf("\n                               View all products                        |Customer\n");
	printf("\n_________________________________________________________________________________\n");
	view = fopen("medicine.txt", "r");
	if (view == 0)
		printf("\n\nNo record of medicines found\n");
	else
	{
		printf("Medicine ID\tMedicine Name\tPrice (RM)\tIn-Stock\tExpiry Date");
		printf("\n_________________________________________________________________________________\n");
		while (fread(&md, sizeof(md), 1, view))
			printf("\n%s\t\t%s\t%.2f\t\t%i\t\t%s", md.medicineID, md.medicineName, md.price, md.quantity, md.expiryDate);
		printf("\n_________________________________________________________________________________\n\n");

	}
	return;
}

void purchasePortal()
{
	time_t timer;
	struct tm* tm_info;
	char idRead4[10], receipt[200] = "", buffer[10] = "", buffer1[26];
	int count = 0, quantityWanted, returnedValue2;
	float total, total1 = 0;
	viewAll();
	strcat(receipt, "\n\nProduct\t\tPrice\t\tQuantity\tTotal\n");
	while (1)
	{
		printf("\nEnter the ID of the product you want to buy or 0 to cancel: ");
		scanf("%s", &idRead4);
		returnedValue2 = medIdCheck(idRead4);
		if ((strcmp(idRead4, "0") == 0) && count > 0)
			break;
		else if ((strcmp(idRead4, "0") == 0) && count == 0)
		{
			printf("\nYou haven't chosen any products\n");
			system("PAUSE");
			system("CLS");
			customerPage();
		}
		else
		{
			if (returnedValue2 == 1)
			{
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer1, 26, "%Y-%m-%d %H:%M:%S", tm_info);
			printf("\nEnter the quantity of this product you want: ");
			scanf("%d", &quantityWanted);
			total = md.price * quantityWanted;
			total1 += total;
			strcat(receipt, md.medicineName);
			strcat(receipt, "\t");
			gcvt(md.price, 5, buffer);
			strcat(receipt, buffer);
			strcat(receipt, "\t\t");
			itoa(quantityWanted, buffer, 10);
			strcat(receipt, buffer);
			strcat(receipt, "\t\t");
			gcvt(total, 5, buffer);
			strcat(receipt, buffer);
			strcat(receipt, "\n");
			}
		}
		count++;
	}
	strcat(receipt, "\nTime: ");
	strcat(receipt, buffer1);
	strcat(receipt, "\n");
	printf("%s", receipt);
	printf("\nTotal price = RM %.2f\n\n", total1);
	FILE* saveReceipt;
	saveReceipt = fopen("receipts.txt", "a+");
	fwrite(receipt, sizeof(receipt), 1, saveReceipt);
	fclose(saveReceipt);
	system("PAUSE");
	system("CLS");
	customerPage();
}

void readReceipts()
{
	char receipt[200];
	FILE* readReceipts;
	readReceipts = fopen("receipts.txt", "r");
	if (readReceipts == 0)
		printf("\nThere is no record of any purchase yet\n");
	else
	{
		while (fread(&receipt, sizeof(receipt), 1, readReceipts))
			printf("%s\n__________________________________________________________________\n\n", receipt);
	}
	system("PAUSE");
	system("CLS");
	adminAccess();
}
