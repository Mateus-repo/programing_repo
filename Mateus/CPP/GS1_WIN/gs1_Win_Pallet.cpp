/*<-------------------------------------- Libraries -------------------------------------->*/

#pragma comment(lib, "ole32")
#pragma comment(lib, "uuid")
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
#include <shobjidl.h>
#include <shlguid.h>
#include <objbase.h>
#include <wchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cctype>

/*<-------------------------------------- Defines -------------------------------------->*/

#define LABELS_FOLDER "C:\\Labels-Pallets"  // Pallets
#define LABELS_FILE_NAME "csv\\labels_Pallet.csv"  // Pallets
#define LABELS_BOXES_FILE "csv\\labels_Pallet_Boxes.csv" // Boxes
#define X_DIMENSION 190
#define Y_DIMENSION 148
#define BOX_X_DIMENSION 116 
#define BOX_Y_DIMENSION 85 

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

struct boxStruct
{
	char labelNum[DEFAULT_SIZE], boxNum[DEFAULT_SIZE], companyName[DEFAULT_SIZE], companyAddress[DESC_SIZE], productDescription[DESC_SIZE], gtin14[GTIN14_SIZE], batchNum[BATCH_SIZE], amount[DEFAULT_SIZE], expirationDate[DATE_SIZE], netWeight[DEFAULT_SIZE];
};

struct dataStruct
{
	char labelNum[DEFAULT_SIZE], sscc[SSCC_SIZE], companyName[DEFAULT_SIZE], companyDescription[DESC_SIZE], netWeight[DEFAULT_SIZE], origin[DEFAULT_SIZE];
};

/*<-------------------------------------- Functions Declaration Area -------------------------------------->*/

void runMain();

void lineCheckF(int line);

void specialCharacters_Portuguese();

void delay(int milli_seconds);

void gotoxy(int x, int y);

void removeNewline(char *str);

int countLines(FILE *file);

void removeSpaces(char *s);

void dataReadf(FILE *fileData, struct dataStruct *ptr, int maxRecords);

void boxReadf(FILE *fileBox, struct boxStruct *ptrBox, int fileBSize);

void tempoCal(char *timePtr);

void programaLoad(loGng percentageBox, long percentagePallet);

void abrirPasta(const char *caminho);

void guardarData(struct dataStruct *ptr, int dataSize, struct boxStruct *ptrBox, int boxSize);

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

void runMain() {
    specialCharacters_Portuguese();
    programaLoad(0, 0);
    FILE *fileData = fopen(LABELS_FILE_NAME, "r");
    if (fileData == NULL) {
        gotoxy(1, 9);
        printf("Error: On file reading - file name is \"%s\"!", LABELS_FILE_NAME);
        getch();
        fileData = fopen(LABELS_FILE_NAME, "w");
        if (fileData) {
            fprintf(fileData, "Label Number;SSCC;Company;Company Description;Origin;Net weight\n");
            fclose(fileData);
            gotoxy(1, 9);
            printf("File created successfully, please insert the data!");
            getch();
            exit(0);
        } else {
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
        exit(-1);
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
    fclose(fileData);
    FILE *fileBox = fopen(LABELS_BOXES_FILE, "r");
    if (fileBox == NULL) {
        printf("Error reading boxes file! Skipping\n");
    }else{
	    int boxCount = countLines(fileBox);
	    printf("\nLines of boxes data found: %d\n", boxCount);
	    struct boxStruct *boxes = (struct boxStruct*)malloc(boxCount * sizeof(struct boxStruct));
	    if (!boxes) {
	        printf("Error: On memory allocation.\n");
	        fclose(fileBox);
	        free(data);
	        getch();
	        exit(-1);
	    }
	    boxReadf(fileBox, boxes, boxCount);
	    fclose(fileBox);
	    guardarData(data, dataCount, boxes, boxCount);
	}
	struct boxStruct *boxes;
    programaLoad(0, 0);
    guardarData(data, dataCount, boxes, -1);
    free(data);
    free(boxes);
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
	if (!fileData || !ptr) return;
    
    rewind(fileData);
    int i = 0;
    char buffer[BUFFER_SIZE];
    char *dataRead;
    char *spacePtr;
    char temp[DEFAULT_SIZE];
    
    if (!fgets(buffer, sizeof(buffer), fileData)) {
        printf("Error: File either empty, corrupted or incorrect! (%s)\n", LABELS_FILE_NAME);
        getch();exit(-1);
    }
    
    printf("Fields: %s\n", buffer);

    while (fgets(buffer, sizeof(buffer), fileData) && i < maxRecords) {
        if (strlen(buffer) <= 1) continue;
        printf("Processing line %d: %.50s...\n", i+1, buffer);
        removeNewline(buffer);
        dataRead = strtok(buffer, ";");
        if (!dataRead) {
            printf("Error: Line %d is incorrect!! (%s)\n", i+1, LABELS_FILE_NAME);
            getch();exit(-1);
        }
        strncpy(temp, dataRead, DEFAULT_SIZE - 1);
        temp[DEFAULT_SIZE - 1] = '\0';
        strcpy(ptr[i].labelNum, temp);
        removeSpaces(ptr[i].labelNum);
        dataRead = strtok(NULL, ";");
        if (dataRead) {
            strncpy(ptr[i].sscc, dataRead, SSCC_SIZE - 1);
            ptr[i].sscc[SSCC_SIZE - 1] = '\0';
            removeSpaces(ptr[i].sscc);
        } else {
            strcpy(ptr[i].sscc, "");
        }
        dataRead = strtok(NULL, ";");
        if (dataRead) {
            strncpy(ptr[i].companyName, dataRead, DEFAULT_SIZE - 1);
            ptr[i].companyName[DEFAULT_SIZE - 1] = '\0';
        } else {
            strcpy(ptr[i].companyName, "");
        }
        dataRead = strtok(NULL, ";");
        if (dataRead) {
            strncpy(ptr[i].companyDescription, dataRead, DESC_SIZE-1);
            ptr[i].companyDescription[DESC_SIZE-1] = '\0';
        } else {
            strcpy(ptr[i].companyDescription, "");
        }
        dataRead = strtok(NULL, ";");
        if (dataRead) {
            strncpy(ptr[i].origin, dataRead, DEFAULT_SIZE - 1);
            ptr[i].origin[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptr[i].origin);
        } else {
            strcpy(ptr[i].origin, "");
        }
        dataRead = strtok(NULL, ";");
        if (dataRead) {
            strncpy(ptr[i].netWeight, dataRead, DEFAULT_SIZE - 1);
            ptr[i].netWeight[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptr[i].netWeight);
        } else {
            strcpy(ptr[i].netWeight, "");
        }
        i++;
    }
    
    printf("\nTotal data lines read: %d\n", i);
};

void boxReadf(FILE *fileBox, struct boxStruct *ptrBox, int fileBSize) {
    if (!fileBox || !ptrBox) return;

    rewind(fileBox);
    int i = 0;
    char buffer[BUFFER_SIZE];
    char *boxRead;
    char temp[DEFAULT_SIZE];
    if (!fgets(buffer, sizeof(buffer), fileBox)) {
        printf("Error: File either empty, corrupted or incorrect! (%s)\n", LABELS_BOXES_FILE);
        return;
    }
    printf("Fields: %s\n", buffer);
    while (fgets(buffer, sizeof(buffer), fileBox) && i < fileBSize) {
        if (strlen(buffer) <= 1) 
            continue;

        printf("Processing linha %d: %.50s...\n", i + 1, buffer);
        removeNewline(buffer);

        /* campo 1: labelNum */
        boxRead = strtok(buffer, ";");
        if (!boxRead) {
            printf("Error: Linha %d is incorrect! (%s)\n", i + 1, LABELS_BOXES_FILE);
            continue;
        }
        strncpy(temp, boxRead, DEFAULT_SIZE - 1);
        temp[DEFAULT_SIZE - 1] = '\0';
        strcpy(ptrBox[i].labelNum, temp);
        removeSpaces(ptrBox[i].labelNum);

        /* campo 2: boxNum */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].boxNum, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].boxNum[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].boxNum); 
        } else {
            ptrBox[i].boxNum[0] = '\0';
        }

        /* campo 3: companyName */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].companyName, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].companyName[DEFAULT_SIZE - 1] = '\0';
        } else {
            ptrBox[i].companyName[0] = '\0';
        }

        /* campo 4: companyAddress */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].companyAddress, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].companyAddress[DEFAULT_SIZE - 1] = '\0';
        } else {
            ptrBox[i].companyAddress[0] = '\0';
        }

        /* campo 5: productDescription */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].productDescription, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].productDescription[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].productDescription);
        } else {
            ptrBox[i].productDescription[0] = '\0';
        }

        /* campo 6: gtin14 */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].gtin14, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].gtin14[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].gtin14);
        } else {
            ptrBox[i].gtin14[0] = '\0';
        }

        /* campo 7: batchNum */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].batchNum, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].batchNum[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].batchNum);
        } else {
            ptrBox[i].batchNum[0] = '\0';
        }

        /* campo 8: amount */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].amount, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].amount[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].amount);
        } else {
            ptrBox[i].amount[0] = '\0';
        }

        /* campo 9: expirationDate */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].expirationDate, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].expirationDate[DEFAULT_SIZE - 1] = '\0';
            removeSpaces(ptrBox[i].expirationDate);
        } else {
            ptrBox[i].expirationDate[0] = '\0';
        }

        /* campo 10: netWeight */
        boxRead = strtok(NULL, ";");
        if (boxRead) {
            strncpy(ptrBox[i].netWeight, boxRead, DEFAULT_SIZE - 1);
            ptrBox[i].netWeight[DEFAULT_SIZE - 1] = '\0';
            removeNewline(ptrBox[i].netWeight);
        } else {
            ptrBox[i].netWeight[0] = '\0';
        }

        i++;
    }

    printf("\nTotal box lines read: %d\n", i);
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

void programaLoad(long percentageBox, long percentagePallet)
{	
	static int firstLoad = 2;
	long percentage = percentageBox + percentagePallet;
	static long percentageOld;
	if(firstLoad){
		if(firstLoad==2){
			percentageOld=0;
		}
		gotoxy(0,0);
		system("cls");       //10        20        30        40        50        60        70 
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
	if((int)percentage>(int)percentageOld||(int)percentage >= 100){
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

void guardarData(struct dataStruct *ptr, int dataSize, struct boxStruct *ptrBox, int boxSize)
{
	
	int folderCheck;
	char folderDpmm[255];
	strcpy(folderDpmm, LABELS_FOLDER);
	folderCheck = mkdir(folderDpmm);
	strcat(folderDpmm, "\\Labels-dpmm-");
	switch(DPMM){
		case 6:
			strcat(folderDpmm, "6---dpi-152");
			break;
		case 8:
			strcat(folderDpmm, "8---dpi-203");
			break;
		case 12:
			strcat(folderDpmm, "12---dpi-300");
			break;
		case 24:
			strcat(folderDpmm, "24---dpi-600");
			break;
		default:
			gotoxy(1, 7);
			printf("                                                                              ");
			gotoxy(1, 8);
			printf("                                                                              ");
			gotoxy(1, 7);
			printf("%sError: %s- DPMM Number has to be one of these 4 formats - 6 dpmm = 152 dpi; 8 dpmm = 203 dpi; 12 dpmm = 300 dpi; 24 dpmm = 600 dpi", AC_RED, AC_NORMAL);
			gotoxy(1, 10);
			printf("Press any key to finish the process...");
			gotoxy(72, 11);
			getch();exit(0);
			break;
	}
	
	folderCheck = mkdir(folderDpmm);
	strcat(folderDpmm, "\\");
	int i = 0, ij = 0;
	char tempoAtual[25];
	strcpy(tempoAtual, TIME_DEFAULT);
	char *timePtr = tempoAtual;
	char fileName[DEFAULT_SIZE + strlen(tempoAtual)];
	long percentage = 0;
	long percentageOld[2] = {0,0};
	int productAmount=0;char productFolder[MAX_PATH_LEN];
	if(boxSize>0){
		for(i=0; i<dataSize;i){
			for(ij=0; ij<boxSize;ij++){
				if(strcmp((ptrBox + ij)->labelNum,(ptr + i)->labelNum)==0){
					productAmount++;
					strcpy(productFolder, folderDpmm);
					strcat(productFolder,"Pallet-");
					strcat(productFolder,(ptr + i)->labelNum);
					strcat(productFolder,"-Boxes-Labels");
					folderCheck = mkdir(productFolder);
					strcat(productFolder,"\\");
					strcat(productFolder,"Box-");
					strcat(productFolder,(ptrBox + ij)->boxNum);
					strcat(productFolder,".prn");
					FILE *productData = fopen(productFolder, "r"); // r = read
					productData = fopen(productFolder, "w");		// w = write
					fprintf(productData, "^XA\n~TA000\n~JSN\n^LT0\n^MNW\n^MTT\n^PON\n^PMN\n^LH0,0\n^JMA\n^PR5,5\n~SD15\n^JUS\n^LRN\n^CI27\n^PA0,1,1,0\n^XZ\n^XA\n^MMT\n^PW%d\n^LL%d\n^LS0\n", BOX_X_DIMENSION*DPMM, BOX_Y_DIMENSION*DPMM);
					if (strlen(ptrBox[ij].companyName) <= 18)
			        {
			            fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, ptrBox[ij].companyName);
			       	} else {
					    char bufferG[BUFFER_SIZE];
					    strncpy(bufferG, ptrBox[ij].companyName, BUFFER_SIZE-1);
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
						fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken[0]);  
						fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (37*DPMM)/6, (80*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken[1]);  
					}
					if (strlen(ptrBox[ij].companyAddress) <= 24)
			        {
			            fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, ptrBox[ij].companyAddress);
			        } else {
					    char bufferG2[BUFFER_SIZE];
					    strncpy(bufferG2, ptrBox[ij].companyAddress, BUFFER_SIZE-1);
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
						fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (43*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken2[0]);  
						fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (390*DPMM)/6, (80*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, strTaken2[1]);  
					}
					fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDProduct: %s^FS^CI27\n", (37*DPMM)/6, (140*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptrBox + ij)->productDescription); // Product Description
					fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDNet weight: %s^FS^CI27\n", (390*DPMM)/6, (140*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptrBox + ij)->netWeight);	// Net weight 																						  
					fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDBatch Number: %s^FS^CI27\n", (37*DPMM)/6, (177*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptrBox + ij)->batchNum); // Batch Number
					if (
					    strlen((ptrBox + ij)->expirationDate) == 10 &&
					    (ptrBox + ij)->expirationDate[2] == '/' &&
					    (ptrBox + ij)->expirationDate[5] == '/' &&
					    isdigit((ptrBox + ij)->expirationDate[0]) &&
					    isdigit((ptrBox + ij)->expirationDate[1]) &&
					    isdigit((ptrBox + ij)->expirationDate[3]) &&
					    isdigit((ptrBox + ij)->expirationDate[4]) &&
					    isdigit((ptrBox + ij)->expirationDate[6]) &&
					    isdigit((ptrBox + ij)->expirationDate[7]) &&
					    isdigit((ptrBox + ij)->expirationDate[8]) &&
					    isdigit((ptrBox + ij)->expirationDate[9])
					) 
					{
					    fprintf(productData,"^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDExpiration date: %s^FS^CI27\n", (390 * DPMM) / 6, (177 * DPMM) / 6, (42 * DPMM) / 12, (43 * DPMM) / 12, (ptrBox + ij)->expirationDate); //Expiration Date
					}
					fprintf(productData, "^FT%d,%d^A0N,%d,%d^FH\\^CI28^FDAmount: %s^FS^CI27\n", (37*DPMM)/6, (214*DPMM)/6, (42*DPMM)/12, (43*DPMM)/12, (ptrBox + ij)->amount); // Amount	
					fprintf(productData, "^FO0,%d^GB%d,%d,%d^FS\n", (97*DPMM)/6, X_DIMENSION*DPMM, (3*DPMM)/6, (3*DPMM)/6);
					fprintf(productData, "^FO0,%d^GB%d,%d,%d^FS\n", (250*DPMM)/6, X_DIMENSION*DPMM, (2*DPMM)/6, (2*DPMM)/6);
					if(DPMM<24){
						if(DPMM<12){
							fprintf(productData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, 5*DPMM, 75*DPMM); // 6 - 8 dpmm
						}else{
							fprintf(productData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, 5*DPMM, 75*DPMM); // 12 dpmm
						}
					}else{
						fprintf(productData, "^BY5,3,%d^FT%d,%d^BCN,,Y,N\n", 27*DPMM, (50*DPMM)/6, 75*DPMM); // 24 dpmm
					}
					fprintf(productData, "^FH\\^FD01%s^FS\n", (ptrBox + ij)->gtin14);
					fprintf(productData, "^PQ1,0,1,Y\n");
					fprintf(productData, "^XZ"); // label End
					fflush(productData);
					fclose(productData);
				}
			}
			i++;
			percentage = (i * 50) / dataSize;
			/*if((percentage/4)>(percentageOld[0]/4)){
				percentageOld[0]=percentage;
				programaLoad(percentageOld[0], percentageOld[1]);
			}*/
			programaLoad(percentage, 0);
		}
	}
	strcpy(fileName, "");
	programaLoad(50, 0);
	delay(100);
	i=0;
	do
	{
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
		fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (40*DPMM)/6, (40*DPMM)/6, (55*DPMM)/6, (55*DPMM)/6, (ptr + i)->companyName);  // Company Name
		fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", (40*DPMM)/6, (115*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptr + i)->companyDescription);	   // Company Description printf("\n%d\n%d\n", strlen((ptr + i)->companyDescription), ((628-(6*strlen((ptr + i)->companyDescription)))*DPMM)/12);getch();
		fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDSSCC: %s^FS^CI27\n", (40*DPMM)/6, (220*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptr + i)->sscc);		   // SSCC
		fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDOrigin: %s^FS^CI27\n", (40*DPMM)/6, (340*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptr + i)->origin); // Origin
		fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDNet weight: %s^FS^CI27\n", (40*DPMM)/6, (460*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptr + i)->netWeight); // Expiration Date
		productAmount=0;
		ij=0;
		do{
			if(strcmp((ptrBox + ij)->labelNum,(ptr + i)->labelNum)==0){
				productAmount++;
			}
			ij++;
		}while(ij<boxSize);
		if(productAmount)
		{
			fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", 30*DPMM, (520*DPMM)/6, (7*DPMM)/12, (7*DPMM)/12);
			fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", 100*DPMM, X_DIMENSION*DPMM, (7*DPMM)/12, (7*DPMM)/12);
			fprintf(labelData, "^FO%d,0^GB%d,%d,%d^FS\n", (520*DPMM)/6 , (3*DPMM)/6, 100*DPMM, (3*DPMM)/6);
		}else{
			fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", 30*DPMM, X_DIMENSION*DPMM, (7*DPMM)/12, (7*DPMM)/12);
			fprintf(labelData, "^FO0,%d^GB%d,%d,%d^FS\n", 100*DPMM, X_DIMENSION*DPMM, (7*DPMM)/12, (7*DPMM)/12);
		};
		if(DPMM<24){
			if(DPMM<12){
				fprintf(labelData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 32*DPMM, 5*DPMM, (830*DPMM)/6); 
			}else{
				fprintf(labelData, "^BY3,3,%d^FT%d,%d^BCN,,Y,N\n", 32*DPMM, 5*DPMM, (830*DPMM)/6); 
			}
		}else{
			fprintf(labelData, "^BY6,3,%d^FT%d,%d^BCN,,Y,N\n", 32*DPMM, (50*DPMM)/6, (830*DPMM)/6); 
		}
		fprintf(labelData, "^FH\\^FD%s^FS\n", (ptr + i)->sscc);ij=0;
		
		if(productAmount==1)
		{
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", ((560)*DPMM)/6, (40*DPMM)/6, (44*DPMM)/6, (44*DPMM)/6, (ptrBox + 0)->companyName);
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FD%s^FS^CI27\n", ((560)*DPMM)/6, (110*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->companyAddress);
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDProduct: %s^FS^CI27\n", ((560)*DPMM)/6, (190*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->productDescription);
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDGTIN-14: %s^FS^CI27\n", ((560)*DPMM)/6, (250*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->gtin14);
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDBatch Number; %s^FS^CI27\n", ((560)*DPMM)/6, (310*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->batchNum);
			fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDAmount: %s^FS^CI27\n", ((560)*DPMM)/6, (370*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->amount);
			if (
			    strlen((ptrBox + ij)->expirationDate) == 10 &&
			    (ptrBox + ij)->expirationDate[2] == '/' &&
			    (ptrBox + ij)->expirationDate[5] == '/' &&
			    isdigit((ptrBox + ij)->expirationDate[0]) &&
			    isdigit((ptrBox + ij)->expirationDate[1]) &&
			    isdigit((ptrBox + ij)->expirationDate[3]) &&
			    isdigit((ptrBox + ij)->expirationDate[4]) &&
			    isdigit((ptrBox + ij)->expirationDate[6]) &&
			    isdigit((ptrBox + ij)->expirationDate[7]) &&
			    isdigit((ptrBox + ij)->expirationDate[8]) &&
			    isdigit((ptrBox + ij)->expirationDate[9])
			){
				fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDExpiration Date: %s^FS^CI27\n", ((560)*DPMM)/6, (430*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->expirationDate);
				fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDNet Weight: %s^FS^CI27\n", ((560)*DPMM)/6, (490*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->netWeight);
			}else{
				fprintf(labelData, "^FO%d,%d^A0N,%d,%d^FH\\^CI28^FDNet Weight: %s^FS^CI27\n", ((560)*DPMM)/6, (430*DPMM)/6, (36*DPMM)/6, (36*DPMM)/6, (ptrBox + 0)->netWeight);
			}
			
		}else if(productAmount){
			switch(DPMM){
				case 6:
					if(productAmount<=3){
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,5\n", (40*DPMM)/6, (565*DPMM)/6); 
					}else{
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,3\n", (40*DPMM)/6, (565*DPMM)/6); 
					}
					break;
				case 8:
					if(productAmount<=7){
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,5\n", (40*DPMM)/6, (565*DPMM)/6); 
					}else{
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,4\n", (40*DPMM)/6, (565*DPMM)/6); 
					}
					break;
				case 12:
					if(productAmount<=8){
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,7\n", (40*DPMM)/6, (565*DPMM)/6);
					}else{
						fprintf(labelData, "^BY3,3,%d\n^FO%d,0\n^BQN,2,5\n", (40*DPMM)/6, (565*DPMM)/6);
					}
					break;
				case 24:
					if(productAmount<=9){
						fprintf(labelData, "^BY6,3,%d\n^FO%d,0\n^BQN,2,12\n", (40*DPMM)/6, (565*DPMM)/6);
					}else{
						fprintf(labelData, "^BY6,3,%d\n^FO%d,0\n^BQN,2,9\n", (40*DPMM)/6, (565*DPMM)/6);
					}
					break;
			}
			fprintf(labelData, "^FDLA,");
			ij=0;productAmount=0;
			do{
				if(strcmp((ptrBox + ij)->labelNum,(ptr + i)->labelNum)==0){
					if(productAmount<11){
						fprintf(labelData,"Product%s:\n   Product Description: %s,\n   GTIN-14: %s,\n   Batch: %s,\n   Amount: %s,\n", (ptrBox + ij)->boxNum, (ptrBox + ij)->productDescription, (ptrBox + ij)->gtin14, (ptrBox + ij)->batchNum, (ptrBox + ij)->amount);
						if (
						    strlen((ptrBox + ij)->expirationDate) == 10 &&
						    (ptrBox + ij)->expirationDate[2] == '/' &&
						    (ptrBox + ij)->expirationDate[5] == '/' &&
						    isdigit((ptrBox + ij)->expirationDate[0]) &&
						    isdigit((ptrBox + ij)->expirationDate[1]) &&
						    isdigit((ptrBox + ij)->expirationDate[3]) &&
						    isdigit((ptrBox + ij)->expirationDate[4]) &&
						    isdigit((ptrBox + ij)->expirationDate[6]) &&
						    isdigit((ptrBox + ij)->expirationDate[7]) &&
						    isdigit((ptrBox + ij)->expirationDate[8]) &&
						    isdigit((ptrBox + ij)->expirationDate[9])
						){
							fprintf(labelData, "   Expiration Date: %s,\n", (ptrBox + ij)->expirationDate);
						}
						fprintf(labelData,"   Net weight: %s;    \n\n", (ptrBox + ij)->netWeight);
					}
					productAmount++;
				}
				ij++;
			}while(ij<boxSize);
			if(productAmount>=11)
			{
				fprintf(labelData,"<--Product data limit reached, no further data about the products.-->\n");
			}
		}
		fprintf(labelData, "^PQ1,0,1,Y\n");
		fprintf(labelData, "^XZ"); // label End                                  
		fflush(labelData);
		fclose(labelData);
		i++;
		percentage = (i * 50) / dataSize;
		/*if((percentage/4)>(percentageOld[1]/4)){
			percentageOld[1]=percentage;
			programaLoad(percentageOld[0], percentageOld[1]);
		}*/
		programaLoad(50, percentage);
	} while (i < dataSize);
	programaLoad(50, 50);
    gotoxy(1, 9);
    printf("Process completed successfully! Press any key to finish...");
    gotoxy(72, 11);
    getch();
    exit(0);
};
