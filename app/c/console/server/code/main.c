//===============================================
#include <stdio.h>
#include <sqlite3.h>
//===============================================
static int onExec(void* params, int colCount, char** colValue, char** colName);
//===============================================
int main(int argc, char** argv) {
    sqlite3* lDb;
    char* lError;
    int lHeader = 1;
    char lSql[256] = ""
    "select * from config_data\n"
    "";
    sqlite3_open("database.dat", &lDb);
    sqlite3_exec(lDb, lSql, onExec, &lHeader, &lError);
    sqlite3_close(lDb);
    return 0;
}
//===============================================
static int onExec(void* params, int colCount, char** colValue, char** colName) {
    int* lHeader = (int*)params;
    // header
    if((*lHeader) == 1) {
        for(int i = 0; i < colCount; i++) {
            const char* lName = colName[i];
            if(i != 0) {printf(" | ");}
            printf("%*s", -20, lName);
        }
        printf("\n");
        // sep
        for(int i = 0; i < colCount; i++) {
            if(i != 0) {printf("-|-");}
            for(int j = 0; j < 20; j++) {
                printf("-");
            }
        }
        (*lHeader) = 0;
        printf("\n");
    }
    // data
    for(int i = 0; i < colCount; i++) {
        const char* lValue = colValue[i];
        if(i != 0) {printf(" | ");}
        printf("%*s", -20, lValue);
    }
    printf("\n");
    return 0;
}
//===============================================
