#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "growing_arrays.h"

struct Table amisha_table;

// returns the index of the item added  
int add_record(Record new_record) {
    if (amisha_table.nval == amisha_table.max) {
        // The array should grow to two times the existing size
        int new_size = amisha_table.max *= GROW_SIZE;
        Record *new_records = realloc(amisha_table.record, new_size * sizeof(Record));
        if (!new_records) return -1;
        amisha_table.record = new_records;
        amisha_table.max = new_size;
    }
    amisha_table.record[amisha_table.nval] = new_record;
    amisha_table.nval++;
    return amisha_table.nval - 1;
}

// return 0 if there is no matching record
// return 1 if there is a matching record and deletes it and 
// moves records
int del_record(const char *name) {
    for (int i = 0; i < amisha_table.nval; i++) {
        if (strcmp(amisha_table.record[i].name, name) == 0) {
            memmove(&amisha_table.record[i], &amisha_table.record[i + 1], (amisha_table.nval - i - 1) * sizeof(Record));
            amisha_table.nval--;
            return 1;
        }
    }
    return 0; // No matching record found
}  

// returns id of student record of the first matching record
int get_id(const char *name) {
    for (int i = 0; i < amisha_table.nval; i++) {
        if (strcmp(amisha_table.record[i].name, name) == 0) {
	    return amisha_table.record[i].id;
        }
    }
    return 0;
}

// returns record with a valid index, 0 to max-1 
Record get_record(int index) {
    if (index >= 0 && index < amisha_table.nval) {
        return amisha_table.record[index];
    }
    // If the index is invalid, return a default Record
Record empty_record = {0};
    return empty_record;
}


// Testing code. You can modify this and check your own test cases.
/*
int main() {
    amisha_table.nval = 0;
    amisha_table.max = INIT_SIZE;
    amisha_table.record = malloc(sizeof(Record) * amisha_table.max);

    // test add_record
    Record r1 = {"Alice", 1};
    Record r2 = {"Bob", 2};
    Record r3 = {"Charlie", 3};
    int i1 = add_record(r1);
    int i2 = add_record(r2);
    int i3 = add_record(r3);
    printf("added records at indices %d, %d, %d\n", i1, i2, i3);

    // test get_id and get_record
    int id = get_id("Bob");
    Record r = get_record(i1);
    printf("record at index %d: name=%s, id=%d\n", i1, r.name, r.id);
    printf("record with name 'Bob': id=%d\n", id);

    // test del_record
    int success = del_record("Bob");
    printf("deleted record with name 'Bob': %d\n", success);
    id = get_id("Bob");
    printf("record with name 'Bob': id=%d\n", id);

    free(amisha_table.record);
    return 0;
}
*/

/*
Output for the above testing code:

added records at indices 0, 1, 2
record at index 0: name=Alice, id=1
record with name 'Bob': id=2
deleted record with name 'Bob': 1
record with name 'Bob': id=0


*/

