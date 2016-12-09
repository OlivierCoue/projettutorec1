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
 * $Id: CatalogDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogDB.h>
#include <CatalogRecord.h>
#include <CatalogRecordEditor.h>

/** The catalog file name */
const char * CATALOGDB_FILENAME = BASEPATH "/data/Catalog.db";

/** Create a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_create)(const char * filename) {
    /*return provided_CatalogDB_create(filename);*/
    CatalogDB *newCatalogDB;

    newCatalogDB = (CatalogDB*) malloc(sizeof(CatalogDB));
    if(newCatalogDB==NULL)
        exit(-1);

    newCatalogDB->file = fopen(filename, "wb+");
    if(newCatalogDB->file==NULL){
        free(newCatalogDB);
        return NULL;
    }

    newCatalogDB->recordCount=0;
    if(fwrite(&newCatalogDB->recordCount, sizeof(int), 1 ,newCatalogDB->file)==1){
        return newCatalogDB;
    }else{
        fclose(newCatalogDB->file);
        free(newCatalogDB);
        exit(-1);
    }
}

/** Open an existing database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_open)(const char * filename) {
    /*return provided_CatalogDB_open(filename);*/
    CatalogDB *openedCatalogDB;

    openedCatalogDB = (CatalogDB*) malloc(sizeof(CatalogDB));
    if(openedCatalogDB==NULL)
        exit(-1);

    openedCatalogDB->file = fopen(filename, "rb+");
    if(openedCatalogDB->file==NULL){
        free(openedCatalogDB);
        return NULL;
    }

    if(fread(&openedCatalogDB->recordCount, sizeof(int), 1, openedCatalogDB->file) == 1){
        return openedCatalogDB;
    }else{
        free(openedCatalogDB);
        exit(-1);
    }
}

/** Open if exists or create otherwise a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_openOrCreate)(const char * filename) {
    /*return provided_CatalogDB_openOrCreate(filename);*/
    CatalogDB * DB = CatalogDB_open(filename);
    if(DB == NULL)
        DB = CatalogDB_create(filename);
    return DB;
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param catalogDB a pointer on a CatalogDB representing the opened database
 */
void IMPLEMENT(CatalogDB_close)(CatalogDB * catalogDB) {
    /*provided_CatalogDB_close(catalogDB);*/
    fseek(catalogDB->file,0,SEEK_SET);
    if(fwrite(&catalogDB->recordCount,sizeof(int),1,catalogDB->file)!=1)
        fatalError("Write Error");
    fclose(catalogDB->file);
    free(catalogDB);
}

/** Get the number of records of the database
 * @param catalogDB the database
 * @return the number of records
 */
int IMPLEMENT(CatalogDB_getRecordCount)(CatalogDB * catalogDB) {
    /*return provided_CatalogDB_getRecordCount(catalogDB);*/
    return catalogDB->recordCount;
}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param catalogDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogDB_getFieldValueAsString(CatalogDB * catalogDB, int recordIndex, int field) {
    char * content = NULL;
    if (catalogDB != NULL) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(field);
        CatalogRecord record;
        CatalogRecord_init(&record);
        CatalogDB_readRecord(catalogDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CatalogRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param catalogDB the database
 * @param record the record
 */
void IMPLEMENT(CatalogDB_appendRecord)(CatalogDB * catalogDB, CatalogRecord *record) {
    /*provided_CatalogDB_appendRecord(catalogDB, record);*/
    CatalogDB_writeRecord(catalogDB,catalogDB->recordCount,record);
}

/** Insert the specified record at the given position in the database
 * @param catalogDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void IMPLEMENT(CatalogDB_insertRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    /*provided_CatalogDB_insertRecord(catalogDB, recordIndex, record);*/
    int indx;
    CatalogRecord currentRec;
    CatalogRecord_init(&currentRec);
    for(indx=catalogDB->recordCount-1;indx>=recordIndex;indx--)
    {
        CatalogDB_readRecord(catalogDB,indx,&currentRec);
        CatalogDB_writeRecord(catalogDB,indx+1,&currentRec);
    }
    CatalogRecord_finalize(&currentRec);
    CatalogDB_writeRecord(catalogDB,recordIndex,record);
}

/** Remove a record at a given position from the database
 * @param catalogDB the database
 * @param recordIndex the removal position
 */
void IMPLEMENT(CatalogDB_removeRecord)(CatalogDB * catalogDB, int recordIndex) {
    /*provided_CatalogDB_removeRecord(catalogDB, recordIndex);*/
    int indx;
    CatalogRecord currentRec;
    CatalogRecord_init(&currentRec);
    for(indx=recordIndex;indx<catalogDB->recordCount-1;indx++)
    {
        CatalogDB_readRecord(catalogDB,indx+1,&currentRec);
        CatalogDB_writeRecord(catalogDB,indx,&currentRec);
    }
    CatalogRecord_finalize(&currentRec);
}

/** Read a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void IMPLEMENT(CatalogDB_readRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    /*provided_CatalogDB_readRecord(catalogDB, recordIndex, record);*/
    fseek(catalogDB->file,(long)sizeof(int)+recordIndex*(long)CATALOGRECORD_SIZE,SEEK_SET);
    CatalogRecord_read(record,catalogDB->file);
}

/** Write a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void IMPLEMENT(CatalogDB_writeRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {
    /*provided_CatalogDB_writeRecord(catalogDB, recordIndex, record);*/
    fseek(catalogDB->file,(long)sizeof(int)+recordIndex*(long)CATALOGRECORD_SIZE,SEEK_SET);
    CatalogRecord_write(record,catalogDB->file);
    if(recordIndex == catalogDB->recordCount)
        catalogDB->recordCount=catalogDB->recordCount+1;
}

