#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int		id;
    char	name;
    int		order;
    struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    int num_of_elements;
    int capacity;
    struct RecordType** arr;
};

// Compute the hash function
int hash(int x, int cap)
{
    return x % cap;
}
void initializeHash(struct HashType* table, int cap)
{
    table->capacity = cap;
    table->num_of_elements = 0;
    table->arr = (struct RecordType**) malloc(sizeof(struct RecordType*)*table->capacity);
    for(int i= 0; i< cap; i++)
        table->arr[i] = NULL;
}
void insert(struct HashType* table, struct RecordType* record) {

    int key = hash(record->id,table->capacity);
    struct RecordType *temp = table->arr[key];

    if (temp == NULL) {
        table->arr[key] = record;
        record->next = NULL;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        record->next = NULL;
        temp->next = record;
    }
    table->num_of_elements++;
}
// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}
void print(struct RecordType *pData)
{

    printf("\t%d %c %d\n", pData->id, pData->name, pData->order);
    printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    struct RecordType* temp;

    for (i=0;i<hashSz;++i)
    {
        temp = pHashArray->arr[i];
        // if index is occupied with any records, print all
        while(temp != NULL){
            print(temp);
            temp = temp->next;
        }
    }

}

int main(void)
{
    struct RecordType *pRecords;
    struct HashType hash_table;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    // Your hash implementation
    initializeHash(&hash_table,recordSz);

    for(int i =0; i<recordSz; i++)
        insert(&hash_table, &pRecords[i]);


    displayRecordsInHash(&hash_table, hash_table.num_of_elements);


    for(int i =0; i < recordSz; i++) {
        free(hash_table.arr[i]);
    }
    free(hash_table.arr);

return 0;
}
