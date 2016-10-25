/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <EncryptDecrypt.h>
#include <MyString.h>

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_create)(void) {
    /*return provided_OperatorTable_create();*/
    OperatorTable *newOpTable;
    newOpTable = (OperatorTable *) malloc(sizeof(OperatorTable));
    if(newOpTable==NULL)
        fatalError("Allocation error");
    newOpTable->recordCount = 0;
    newOpTable->records = NULL;
    return newOpTable;
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_destroy)(OperatorTable * table) {
    /*provided_OperatorTable_destroy(table);*/
    int i;
    for(i=0;i<table->recordCount;i++){
        free(table->records[i][0]);
        free(table->records[i][1]);
        free(table->records[i]);
    }
    free(table->records);
    free(table);
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_loadFromFile)(const char * filename) {
    return provided_OperatorTable_loadFromFile(filename);
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_saveToFile)(OperatorTable * table, const char * filename) {
    provided_OperatorTable_saveToFile(table, filename);
}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_getRecordCount)(OperatorTable * table) {
    /*return provided_OperatorTable_getRecordCount(table);*/
    return table->recordCount;
}

/** Get the name of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getName)(OperatorTable * table, int recordIndex) {
    /*return provided_OperatorTable_getName(table, recordIndex);*/
    if(recordIndex>=table->recordCount)
        fatalError("Record index out of array");
    return table->records[recordIndex][0];
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the paswword of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getPassword)(OperatorTable * table, int recordIndex) {
    return provided_OperatorTable_getPassword(table, recordIndex);
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_findOperator)(OperatorTable * table, const char * name) {
    /*return provided_OperatorTable_findOperator(table, name);*/
    int i;
    for(i=0;i<table->recordCount;i++){
        if(icaseCompareString(table->records[i][0], name)==0)
            return i;
    }
    return -1;
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_setOperator)(OperatorTable * table, const char * name, const char * password) {
    /*return provided_OperatorTable_setOperator(table, name, password);*/
    int operatorPosition = OperatorTable_findOperator(table, name);
    if(operatorPosition!=-1){
        free(table->records[operatorPosition][1]);
        table->records[operatorPosition][1] = duplicateString(password);
        return operatorPosition;
    }

    table->recordCount++;
    table->records = (char***) realloc(table->records, (long unsigned int)(table->recordCount)*sizeof(char**));
    if(table->records==NULL)
        fatalError("Allocation error");

    table->records[table->recordCount-1] = (char**) malloc(2*sizeof(char*));
    if(table->records[table->recordCount-1]==NULL)
        fatalError("Allocation error");

    table->records[table->recordCount-1][0] = duplicateString(name);
    table->records[table->recordCount-1][1] = duplicateString(password);
    return table->recordCount-1;
}

/** Remove an operator from the table.
 * @param table the table of operators
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_removeRecord)(OperatorTable * table, int recordIndex) {
    /*provided_OperatorTable_removeRecord(table, recordIndex);*/
    int i;
    for(i=recordIndex;i<table->recordCount-1;i++){
        table->records[i][0] = table->records[i+1][0];
        table->records[i][1] = table->records[i+1][1];
    }
    table->recordCount--;
}

