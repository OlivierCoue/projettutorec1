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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <CustomerRecordEditor.h>

const char * CUSTOMERDB_FILENAME = BASEPATH "/data/Customer.db";

CustomerDB * IMPLEMENT(CustomerDB_create)(const char * filename) {
    /*return provided_CustomerDB_create(filename);*/
    CustomerDB *newCustomerDB;

    newCustomerDB = (CustomerDB*) malloc(sizeof(CustomerDB));
    if(newCustomerDB==NULL)
        fatalError("Allocation Error");

    newCustomerDB->file = fopen(filename, "wb+");
    if(newCustomerDB->file==NULL)
        return NULL;

    newCustomerDB->recordCount=0;
    return newCustomerDB;
}

CustomerDB * IMPLEMENT(CustomerDB_open)(const char * filename) {
    /*return provided_CustomerDB_open(filename);*/
    CustomerDB *openedCustomerDB;

    openedCustomerDB = (CustomerDB*) malloc(sizeof(CustomerDB));
    if(openedCustomerDB==NULL)
        fatalError("Allocation Error");

    openedCustomerDB->file = fopen(filename, "rb+");
    if(openedCustomerDB->file==NULL){
        free(openedCustomerDB);
        return NULL;
    }

    if(fread(&openedCustomerDB->recordCount, sizeof(int), 1, openedCustomerDB->file)!=1)
        fatalError("Read Error");
    return openedCustomerDB;
}

CustomerDB * IMPLEMENT(CustomerDB_openOrCreate)(const char * filename) {
    /*return provided_CustomerDB_openOrCreate(filename);*/
    CustomerDB *customerDB;
    customerDB = CustomerDB_open(filename);
    if(customerDB==NULL){
        customerDB = CustomerDB_create(filename);
    }
    return customerDB;
}

void IMPLEMENT(CustomerDB_close)(CustomerDB * customerDB) {
    /*provided_CustomerDB_close(customerDB);*/
    fseek(customerDB->file, 0, SEEK_SET );
    if(fwrite(&customerDB->recordCount, sizeof(int), 1,customerDB->file)!=1)
        fatalError("Write Error");
    fclose(customerDB->file);
    free(customerDB);
}

int IMPLEMENT(CustomerDB_getRecordCount)(CustomerDB * customerDB) {
    /*return provided_CustomerDB_getRecordCount(customerDB);*/
    return customerDB->recordCount;
}

char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}

void IMPLEMENT(CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record) {
    /*provided_CustomerDB_appendRecord(customerDB, record);*/
    CustomerDB_writeRecord(customerDB, customerDB->recordCount, record);
}

void IMPLEMENT(CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    /*provided_CustomerDB_insertRecord(customerDB, recordIndex, record);*/
    int indx;
    CustomerRecord currentRec;
    CustomerRecord_init(&currentRec);
    for(indx=customerDB->recordCount-1;indx>=recordIndex;indx--)
    {
        CustomerDB_readRecord(customerDB,indx,&currentRec);
        CustomerDB_writeRecord(customerDB,indx+1,&currentRec);
    }
    CustomerRecord_finalize(&currentRec);
    CustomerDB_writeRecord(customerDB,recordIndex,record);
}

void IMPLEMENT(CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex) {
    /*provided_CustomerDB_removeRecord(customerDB, recordIndex);*/
    int indx;
    CustomerRecord currentRec;
    CustomerRecord_init(&currentRec);
    for(indx=recordIndex;indx<customerDB->recordCount-1;indx++)
    {
        CustomerDB_readRecord(customerDB,indx+1,&currentRec);
        CustomerDB_writeRecord(customerDB,indx,&currentRec);
    }
    CustomerRecord_finalize(&currentRec);
}

void IMPLEMENT(CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    /*provided_CustomerDB_readRecord(customerDB, recordIndex, record);*/
    if(recordIndex > customerDB->recordCount || recordIndex<0){
        printf("Index out of bound");
        exit(-1);
    }
    fseek(customerDB->file, (long)(sizeof(int))+(recordIndex*(long)(sizeof(CustomerRecord))), SEEK_SET);
    CustomerRecord_read(record, customerDB->file);
}

void IMPLEMENT(CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    /*provided_CustomerDB_writeRecord(customerDB, recordIndex, record);*/
    if(recordIndex > customerDB->recordCount || recordIndex<0){
        printf("Index out of bound");
        exit(-1);
    }
    fseek(customerDB->file, (long)(sizeof(int))+(recordIndex*(long)(sizeof(CustomerRecord))), SEEK_SET);
    CustomerRecord_write(record, customerDB->file);
    if(recordIndex == customerDB->recordCount){
        customerDB->recordCount++;
    }
}
