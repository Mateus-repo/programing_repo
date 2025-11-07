/*<-------------------------------------- Libraries -------------------------------------->*/

#include "config_dpmm.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cctype>

/*<-------------------------------------- Defines -------------------------------------->*/

#define LABELS_FILE_NAME "csv\\labels_Products.csv" // Products
#define LABELS_FOLDER "C:\\Labels-Products"  // Products
#define X_DIMENSION 116
#define Y_DIMENSION 85

/*<-------------------------------------- Variables Structures -------------------------------------->*/

struct tempoVal
{
	char second[3];
	char minute[3];
	char hour[3];
	char day[3];
	char month[3];
	char year[5];
};

struct dataStruct
{
	char labelNum[DEFAULT_SIZE], companyName[DEFAULT_SIZE], companyAddress[DESC_SIZE], productDescription[DESC_SIZE], netWeight[DEFAULT_SIZE], batchNum[BATCH_SIZE],  originCountry[DEFAULT_SIZE], sn[SERIAL_NUMBER_SIZE], expirationDate[DATE_SIZE], gtin14[GTIN14_SIZE];
};

/*<-------------------------------------- Functions Declaration Area -------------------------------------->*/

void runMain();

void lineCheckF(int line);

void delay(int milli_seconds);

void specialCharacters_Portuguese();

void gotoxy(int x, int y);

void removeNewline(char *str);

int countLines(FILE *file);

void removeSpaces(char *s);

void dataReadf(FILE *fileData, struct dataStruct *ptr, int maxRecords);

void tempoCal(char *timePtr);

void programaLoad(long percentage);

void abrirPasta(const char *caminho);

void guardarData(struct dataStruct *ptr, int dataSize);

/*<-------------------------------------- MAIN -------------------------------------->*/

clock_t startTime;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    startTime = clock();
    runMain();
	return 0;
}


void runMain()
{
	specialCharacters_Portuguese();
	programaLoad(0);
	int i = 0;
	FILE *fileData = fopen(LABELS_FILE_NAME, "r"); // r = read
	if (fileData == NULL)
	{
		gotoxy(1, 9);
		printf("Error on file reading - file name is \"%s\"!", LABELS_FILE_NAME);getch();
		gotoxy(72, 11);
		fileData = fopen(LABELS_FILE_NAME, "w"); // w = write
		if(fileData){
			gotoxy(1, 9);
			printf("                                                              ");
			gotoxy(1, 9);
			printf("File created successfully, please insert the data on the file!");
			gotoxy(72, 11);
			fprintf(fileData, "Label Number;Company Name;Company Address;Product Description;Net weight;Batch Number;Country of origin;SN - Serial Number;Expiration Date;GTIN-14\n");
			fileData = fopen(LABELS_FILE_NAME, "r");
			fclose(fileData);
			getch();exit(0);
		}else{
			gotoxy(1, 9);printf("                                                              ");
			gotoxy(1, 9);
			printf("Error on file creation, create the file yourself with these parameters - \"Label Number;Company Name;Company Address;Product Description;SN - Serial Number;SSCC;Batch Number;GTIN-14;Net weight;Country of origin\"");
			getch();exit(-1);
		}
	}
	int dataCount = countLines(fileData);gotoxy(0,13);
    printf("Lines of data found: %d\n", dataCount);    
    if (dataCount == 0) {
        printf("The files does not have valid data!\n");
        fclose(fileData);
        getch();
        exit(0);
    }
    if (dataCount > MAX_RECORDS) {
        printf("The limit is %d, (the file has %d)\n", MAX_RECORDS, dataCount);
        dataCount = MAX_RECORDS;
    }
    struct dataStruct *data = (struct dataStruct*)malloc(dataCount * sizeof(struct dataStruct));
    if (!data) {
        printf("Error: %d were not allocated in the memory\n", dataCount);
        fclose(fileData);
        getch();
        exit(-1);
    }
    dataReadf(fileData, data, dataCount);
    //lineCheckF(__LINE__);
    programaLoad(0);
    fclose(fileData);
	guardarData(data, dataCount);
	free(data);
};



/*<-------------------------------------- Functions -------------------------------------->*/

void lineCheckF(int line)
{
	printf("Line: %d", line);getch();
};

void delay(int milli_seconds)
{
	clock_t start_time = clock();
	
	while (clock() < start_time + milli_seconds)
		;
};

void specialCharacters_Portuguese()
{
	setlocale(LC_ALL, "Portuguese");
	if (setlocale(LC_ALL, "Portuguese") == NULL) {
		setlocale(LC_ALL, "Portuguese_Portugal.1252");
	}
};

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x; 
	coord.Y = y; 
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void removeNewline(char *str){
    char *p = str;
    while (*p) {
        if (*p == '\n' || *p == '\r') {
            *p = '\0';
            break;
        }
        p++;
    }
};

int countLines(FILE *file) {
    if (!file) return 0;
    rewind(file);
    int count = 0;
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, sizeof(buffer), file)) {
        while (fgets(buffer, sizeof(buffer), file)) {
            if (strlen(buffer) > 1) {
                count++;
            }
        }
    }
    rewind(file);
    return count;
};

void removeSpaces(char *s) 
{
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
};

void dataReadf(FILE *fileData, struct dataStruct *ptr, int maxRecords) {
    gotoxy(0,15);
    if (!fileData || !ptr){
    	return;
	}
	rewind(fileData);
    char buffer[BUFFER_SIZE];
    if (!fgets(buffer, sizeof(buffer), fileData)) {
        printf("Error: File either empty, corrupted or incorrect!\n");
        getch();exit(-1);
    }
    printf("Fields: %s\n", buffer);
    int i = 0;
    while (i < maxRecords && fgets(buffer, sizeof(buffer), fileData)) {
        if (strlen(buffer) <= 1) continue;
        printf("Processing line %d: %.50s...\n", i+1, buffer);
        removeNewline(buffer);
        char *tok = strtok(buffer, ";");
        if (!tok) {
            printf("Error: Line %d is incorrect!!\n", i+1);
            getch();exit(-1);
        }
        // 1) Label Number
        strncpy(ptr[i].labelNum, tok, DEFAULT_SIZE-1);
        ptr[i].labelNum[DEFAULT_SIZE-1] = '\0';
        removeSpaces(ptr[i].labelNum);

        // 2) Company Name
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].companyName, tok, DEFAULT_SIZE-1);
            ptr[i].companyName[DEFAULT_SIZE-1] = '\0';
        } else {
            ptr[i].companyName[0] = '\0';
        }

        // 3) Company Address
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].companyAddress, tok, DESC_SIZE-1);
            ptr[i].companyAddress[DESC_SIZE-1] = '\0';
        } else {
            ptr[i].companyAddress[0] = '\0';
        }

        // 4) Product Description
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].productDescription, tok, DESC_SIZE-1);
            ptr[i].productDescription[DESC_SIZE-1] = '\0';
        } else {
            ptr[i].productDescription[0] = '\0';
        }

        // 5) Net weight
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].netWeight, tok, DEFAULT_SIZE-1);
            ptr[i].netWeight[DEFAULT_SIZE-1] = '\0';
            removeSpaces(ptr[i].netWeight);
        } else {
            ptr[i].netWeight[0] = '\0';
        }

        // 6) Batch Number
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].batchNum, tok, BATCH_SIZE-1);
            ptr[i].batchNum[DEFAULT_SIZE-1] = '\0';
            removeSpaces(ptr[i].batchNum);
        } else {
            ptr[i].batchNum[0] = '\0';
        }

        // 7) Country of origin
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].originCountry, tok, DEFAULT_SIZE-1);
            ptr[i].originCountry[DEFAULT_SIZE-1] = '\0';
        } else {
            ptr[i].originCountry[0] = '\0';
        }

        // 8) SN - Serial Number
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].sn, tok, DEFAULT_SIZE-1);
            ptr[i].sn[DEFAULT_SIZE-1] = '\0';
            removeSpaces(ptr[i].sn);
        } else {
            ptr[i].sn[0] = '\0';
        }

        // 9) Expiration Date (formato dd/mm/yyyy)
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].expirationDate, tok, DATE_SIZE-1);
            ptr[i].expirationDate[DATE_SIZE-1] = '\0';
            removeSpaces(ptr[i].expirationDate);
            if (ptr[i].expirationDate[2] != '/' && ptr[i].expirationDate[2] != '-') {
                ptr[i].expirationDate[0] = '\0';
            }
        } else {
            ptr[i].expirationDate[0] = '\0';
        }

        // 10) GTIN-14
        tok = strtok(NULL, ";");
        if (tok) {
            strncpy(ptr[i].gtin14, tok, GTIN14_SIZE-1);
            ptr[i].gtin14[GTIN14_SIZE-1] = '\0';
            removeSpaces(ptr[i].gtin14);
        } else {
            ptr[i].gtin14[0] = '\0';
        }

        i++;
    }

    printf("Total data lines read: %d\n", i);
    gotoxy(0,0);
};

void tempoCal(char *timePtr)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	struct tempoVal time;
	strcpy(timePtr, TIME_DEFAULT);
	if (tm.tm_sec < 10)
	{
		time.second[0] = ASCII_0;
		time.second[1] = tm.tm_sec + ASCII_0;
	}
	else
	{
		itoa(tm.tm_sec, time.second, 10);
	}
	if (tm.tm_min < 10)
	{
		time.minute[0] = ASCII_0;
		time.minute[1] = tm.tm_min + ASCII_0;
	}
	else
	{
		itoa(tm.tm_min, time.minute, 10); 
	}
	if (tm.tm_hour < 10)
	{
		time.hour[0] = ASCII_0;
		time.hour[1] = tm.tm_hour + ASCII_0;
	}
	else
	{
		itoa(tm.tm_hour, time.hour, 10);
	}
	if (tm.tm_mday < 10)
	{
		time.day[0] = ASCII_0;
		time.day[1] = tm.tm_mday + ASCII_0;
	}
	else
	{
		itoa(tm.tm_mday, time.day, 10); 
	}
	if (tm.tm_mon < 10)
	{
		time.month[0] = ASCII_0;
		time.month[1] = tm.tm_mon + ASCII_0 + 1;
	}
	else
	{
		itoa(tm.tm_mon + 1, time.month, 10);
	}
	itoa(tm.tm_year + 1900, time.year, 10);
	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
		{
			*(timePtr + i) = time.day[i];		 
			*(timePtr + i + 3) = time.month[i];	
			*(timePtr + i + 16) = time.hour[i];	  
			*(timePtr + i + 19) = time.minute[i]; 
			*(timePtr + i + 22) = time.second[i]; 
		}
		*(timePtr + i + 6) = time.year[i];
		;
	}
};

void programaLoad(long percentage)
{	
	static int firstLoad = 2;
	static long percentageOld;
	if(firstLoad){
		if(firstLoad==2){
			percentageOld=0;
		}
		gotoxy(0,0);
		system("cls");        //10       20        30        40        50        60        70 
		           /*012345678901234567890123456789012345678901234567890123456789012345678901  
		/*0*/printf("<--------------------- .csv to .prn style GS1-128 --------------------->\n");
		/*1*/printf("                                                                        \n");
		/*2*/printf("                                                                        \n");
		/*3*/printf("                                                                        \n");
		/*4*/printf(" Running Process                                                        \n");
		/*5*/printf("   ->  0   %s<0%%%s-------------------------%s100%%>%s      ~N\\A min left                      \n", AC_GREEN, AC_NORMAL, AC_GREEN, AC_NORMAL);
		/*6*/printf("                                                                        \n");
		/*7*/printf("                                                                        \n");
		/*8*/printf("                                                                        \n");
		/*9*/printf("                                                                        \n");
	   /*10*/printf("                                                                        \n");
	   /*11*/printf("<---------------------------------------------------------------------->");	
		firstLoad--;
	}
	if((int)percentage> (int)percentageOld|| (int)percentage >= 100){
		clock_t midTime = clock();
		double passTime = (double)(midTime - startTime) / CLOCKS_PER_SEC;
		double timePercent = passTime/percentage;
		double timeLeft = timePercent * (100-percentage);
		int minutesLeft = (int)(timeLeft / 60);
		percentageOld=percentage;
		gotoxy(6, 5);
		printf("%lu%%", percentage);
		gotoxy(50, 5);
		printf("                              ");
		gotoxy(50, 5);
		printf("~%d min left", minutesLeft);
		gotoxy(14, 5);
		int progress = percentage / 4;
		int tempColor=1;
		for(int i = 0; i<25; i++){
			if(i<progress){
				printf("%s=", AC_GREEN);
			}else{
				if(tempColor){ 
					printf("%s-", AC_NORMAL);tempColor=0; 
				}else{ 
					if(i==24){
						printf("-%s", AC_GREEN); 
					}else{
						printf("-"); 
					}
				}
			}
		}
		gotoxy(0, 6);
		printf("%s",AC_NORMAL);
		gotoxy(72, 11);
	}
	if((int)percentage >= 100){
		char folderOP[255];
		strcpy(folderOP, LABELS_FOLDER);
		strcat(folderOP, "\\Labels-dpmm-");
		switch(DPMM){
			case 6:
				strcat(folderOP, "6---dpi-152");
				break;
			case 8:
				strcat(folderOP, "8---dpi-203");
				break;
			case 12:
				strcat(folderOP, "12---dpi-300");
				break;
			case 24:
				strcat(folderOP, "24---dpi-600");
				break;
		}
		gotoxy(49, 5);
		printf("                                 ");
		gotoxy(0, 8);printf("                                                                   ");
		gotoxy(1, 8);
		clock_t endTime = clock();
		double passado = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("Process finished in %.3f seconds.", passado);
		gotoxy(0, 9);printf("                                                                   ");
		gotoxy(1, 9);
		printf("Press any key to finish the process...");abrirPasta(folderOP);
		gotoxy(72, 11);
		getch();exit(0);
	}
	//delay(DELAY);
};

void abrirPasta(const char *caminho)
{
    char comando[512];
    snprintf(comando, sizeof(comando), "start %s", caminho);
    system(comando);
};

void guardarData(struct dataStruct *ptr, int dataSize)
{
	int folderCheck;
	char folderDpmm[MAX_PATH_LEN];
	strcpy(folderDpmm, LABELS_FOLDER);
    folderCheck = mkdir(folderDpmm);
    if (folderCheck != 0 && errno != EEXIST) 
	{ 
		exit(1); 
	}
    strcat(folderDpmm, "\\Labels-dpmm-");
    switch(DPMM){
        case 6:  strcat(folderDpmm, "6---dpi-152"); break;
        case 8:  strcat(folderDpmm, "8---dpi-203"); break;
        case 12: strcat(folderDpmm, "12---dpi-300"); break;
        case 24: strcat(folderDpmm, "24---dpi-600"); break;
    	default:
    		gotoxy(1,7);printf("                                                                              ");
    		gotoxy(1,8);printf("                                                                              ");
	        gotoxy(1,8);printf("Error: Format DPMM incorret! Only 6, 8, 12 or 24 are allowed.");
	        gotoxy(72,11);getch();
	        exit(-1);
    		break;
	}
    folderCheck = mkdir(folderDpmm);
    if (folderCheck != 0 && errno != EEXIST)
	{ 
	 	gotoxy(1,8); printf("                                                                              ");
		gotoxy(1,8);printf("Error: Creation of labels folder on \"C:\", try opening the .exe with admin permissions.");
		getch();exit(-1); 
	}
	strcat(folderDpmm, "\\");
	struct tempoVal dateLabel;
	int i = 0;
	char tempoAtual[25];
	strcpy(tempoAtual, TIME_DEFAULT);
	char *timePtr = tempoAtual;
    char fileName[MAX_PATH_LEN];	
	char barcode1[188];
	long percentage = (i * 100) / dataSize;
	long percentageOld = 0;
	do
	{
		strcpy(barcode1, "");
		strcpy(dateLabel.day, "");strcpy(dateLabel.month, "");strcpy(dateLabel.year, "");
		strcpy(fileName, folderDpmm);
		strcat(fileName, LABEL_PRN_FILE);
		strcat(fileName, (ptr + i)->labelNum);
		strcat(fileName, "__");
		tempoCal(timePtr);
        strcat(fileName, timePtr);
		strcat(fileName, ".prn");
		FILE *labelData = fopen(fileName, "r"); // r = read
		labelData = fopen(fileName, "w");		// w = write
		fprintf(labelData, "^XA\n~TA000\n~JSN\n^LT0\n^MNW\n^MTT\n^PON\n^PMN\n^LH0,0\n^JMA\n^PR5,5\n~SD15\n^JUS\n^LRN\n^CI27\n^PA0,1,1,0\n^XZ\n^XA\n^MMT\n^PW%d\n^LL%d\n^LS0\n", X_DIMENSION*DPMM, Y_DIMENSION*DPMM); // Label Start
		if (strlen(ptr[i].companyName) <= 18)
        {
            fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, ptr[i].companyName);
       	} else {
		    char bufferG[BUFFER_SIZE];
		    strncpy(bufferG, ptr[i].companyName, BUFFER_SIZE-1);
		    bufferG[BUFFER_SIZE-1] = '\0';
		    char strTaken[2][DEFAULT_SIZE+20] = {{0}};
		    char tempTaken[DEFAULT_SIZE] = "";
		    int line1Len = 0, line2Len = 0;
		    int finished = 0;
		    
		    char* token = strtok(bufferG, " ");
		    
		    while (token != NULL && !finished) {
		        int tokenLen = strlen(token);
		        if (line1Len == 0) 
				{
		            if (tokenLen <= 18) 
					{
		                strcpy(strTaken[0], token);
		                line1Len = tokenLen;
		            } else {
		                strncpy(strTaken[0], token, 15);
		                strcat(strTaken[0], "...");
		                line1Len = 18;
		                finished = 1;
		            }
		        } else if (line1Len + 1 + tokenLen <= 18) {
		            strcat(strTaken[0], " ");
		            strcat(strTaken[0], token);
		            line1Len += 1 + tokenLen;
		        } else {
		            if (line2Len == 0) 
					{
		                if (tokenLen <= 18) 
						{
		                    strcpy(strTaken[1], token);
		                    line2Len = tokenLen;
		                } else {
		                    strncpy(strTaken[1], token, 15);
		                    strcat(strTaken[1], "...");
		                    line2Len = 18;
		                    finished = 1;
		                }
		            } else if (line2Len + 1 + tokenLen <= 18) {
		                strcat(strTaken[1], " ");
		                strcat(strTaken[1], token);
		                line2Len += 1 + tokenLen;
		            } else {
		                if (line2Len <= 15) {
		                    strcat(strTaken[1], "...");
		                } else {
		                    strTaken[1][15] = '.';
		                    strTaken[1][16] = '.';
		                    strTaken[1][17] = '.';
		                    strTaken[1][18] = '\0';
		                }
		                finished = 1;
		            }
		        }
		        
		        token = strtok(NULL, " ");
		    }
			fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken[0]);  
			fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (80*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken[1]);  
		}
		if (strlen(ptr[i].companyAddress) <= 24)
        {
            fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, ptr[i].companyAddress);
        } else {
		    char bufferG2[BUFFER_SIZE];
		    strncpy(bufferG2, ptr[i].companyAddress, BUFFER_SIZE-1);
		    bufferG2[BUFFER_SIZE-1] = '\0';
		    char strTaken2[2][DEFAULT_SIZE+20] = {{0}};
		    char tempTaken2[DEFAULT_SIZE] = "";
		    int line1Len = 0, line2Len = 0;
		    int finished = 0;
		    char* token = strtok(bufferG2, " ");
		    while (token != NULL && !finished) {
		        int tokenLen = strlen(token);
		        if (line1Len == 0) 
				{
		            if (tokenLen <= 24) 
					{
		                strcpy(strTaken2[0], token);
		                line1Len = tokenLen;
		            } else {
		                strncpy(strTaken2[0], token, 21);
		                strcat(strTaken2[0], "...");
		                line1Len = 24;
		                finished = 1;
		            }
		        } else if (line1Len + 1 + tokenLen <= 24) {
		            strcat(strTaken2[0], " ");
		            strcat(strTaken2[0], token);
		            line1Len += 1 + tokenLen;
		        } else {
		            if (line2Len == 0) 
					{
		                if (tokenLen <= 24) 
						{
		                    strcpy(strTaken2[1], token);
		                    line2Len = tokenLen;
		                } else {
		                    strncpy(strTaken2[1], token, 21);
		                    strcat(strTaken2[1], "...");
		                    line2Len = 24;
		                    finished = 1;
		                }
		            } else if (line2Len + 1 + tokenLen <= 24) {
		                strcat(strTaken2[1], " ");
		                strcat(strTaken2[1], token);
		                line2Len += 1 + tokenLen;
		            } else {
		                if (line2Len <= 21) 
						{
		                    strcat(strTaken2[1], "...");
		                } else {
		                    strTaken2[1][21] = '.';
		                    strTaken2[1][22] = '.';
		                    strTaken2[1][23] = '.';
		                    strTaken2[1][24] = '\0';
		                }
		                finished = 1;
		            }
		        }
		        
		        token = strtok(NULL, " ");
		    }
			fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken2[0]);  
			fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (80*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken2[1]);  
		}
		fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDProduct: %s^FS^CI27\n", (37*DPMM)/6, (140*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptr + i)->productDescription); // Product Description
		fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDNet weight: %s^FS^CI27\n", (390*DPMM)/6, (140*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptr + i)->netWeight);	// Net weight 																						  
		fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDBatch Number: %s^FS^CI27\n", (37*DPMM)/6, (177*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptr + i)->batchNum); // Batch Number
		fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDCountry of origin: %s^FS^CI27\n", (390*DPMM)/6, (177*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptr + i)->originCountry);  // Country of origin
		fprintf(labelData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDSN: %s^FS^CI27\n", (37*DPMM)/6, (214*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptr + i)->sn); // Serial Number	
		if (
		    strlen((ptr + i)->expirationDate) == 10 &&
		    (ptr + i)->expirationDate[2] == '/' &&
		    (ptr + i)->expirationDate[5] == '/' &&
		    isdigit((ptr + i)->expirationDate[0]) &&
		    isdigit((ptr + i)->expirationDate[1]) &&
		    isdigit((ptr + i)->expirationDate[3]) &&
		    isdigit((ptr + i)->expirationDate[4]) &&
		    isdigit((ptr + i)->expirationDate[6]) &&
		    isdigit((ptr + i)->expirationDate[7]) &&
		    isdigit((ptr + i)->expirationDate[8]) &&
		    isdigit((ptr + i)->expirationDate[9])
		) 
		{
		    fprintf(labelData,"^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDExpiration date: %s^FS^CI27\n", (390 * DPMM) / 6, (214 * DPMM) / 6, (42 * DPMM) / 12, (43 * DPMM) / 12, (ptr + i)->expirationDate);
		    dateLabel.day[0]   = (ptr + i)->expirationDate[0];
		    dateLabel.day[1]   = (ptr + i)->expirationDate[1];
		    dateLabel.month[0] = (ptr + i)->expirationDate[3];
		    dateLabel.month[1] = (ptr + i)->expirationDate[4];
		    dateLabel.year[0]  = (ptr + i)->expirationDate[8];
		    dateLabel.year[1]  = (ptr + i)->expirationDate[9];
		}
		fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", (97*DPMM)/6, X_DIMENSION*DPMM, (3*DPMM)/6, (3*DPMM)/6);
		fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", (250*DPMM)/6, X_DIMENSION*DPMM, (2*DPMM)/6, (2*DPMM)/6);
		if(DPMM<24){
			if(DPMM<12){
				fprintf(labelData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, 5*DPMM, 75*DPMM); // 6 - 8 dpmm
			}else{
				fprintf(labelData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, 5*DPMM, 75*DPMM); // 12 dpmm
			}
		}else{
			fprintf(labelData, "^BY5,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, (50*DPMM)/6, 75*DPMM); // 24 dpmm
		}
		fprintf(labelData, "^FH\\^FD01%s^FS\n", (ptr + i)->gtin14);
		fprintf(labelData, "^PQ1,0,1,Y\n");
		fprintf(labelData, "^XZ"); // label End
		i++;
		percentage = (i * 100) / dataSize;
		/*if((percentage/4)>(percentageOld/4)){
			percentageOld=percentage;
			programaLoad(percentageOld);
		}*/
		programaLoad(percentage);
		fflush(labelData);
		fclose(labelData);
	} while (i < dataSize);
};
