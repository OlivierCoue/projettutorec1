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
 * $Id: DocumentRowList.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentRowList.h>
#include <DocumentUtil.h>

/** Initialize a row
 * @param row the row
 * @warning an initialized row must be finalized by DocumentRow_finalize() to free all resources
 */
void IMPLEMENT(DocumentRow_init)(DocumentRow * row) {
    /*provided_DocumentRow_init(row);*/
    row->code = duplicateString("");
    row->designation = duplicateString("");
    row->unity = duplicateString("");
    row->quantity = 0;
    row->basePrice = 0;
    row->sellingPrice = 0;
    row->discount = 0;
    row->rateOfVAT = 0;
    row->next = NULL;
}

/** Finalize a row
 * @param row the row
 * @warning document must have been initialized
 */
void IMPLEMENT(DocumentRow_finalize)(DocumentRow * row) {
    /*provided_DocumentRow_finalize(row);*/
    free(row->code);
    free(row->designation);
    free(row->unity);
    row->next = NULL;
}

/** Create a new row on the heap and initialize it
 * @return the new row
 */
DocumentRow * IMPLEMENT(DocumentRow_create)(void) {
    /*return provided_DocumentRow_create();*/
    DocumentRow * row = (DocumentRow *) malloc(sizeof(DocumentRow));
    if(row == NULL)
        fatalError("Allocation Error");
    DocumentRow_init(row);
    return row;
}

/** Finalize and destroy a row previously created on the heap
 * @param row the row
 */
void IMPLEMENT(DocumentRow_destroy)(DocumentRow * row) {
    /*provided_DocumentRow_destroy(row);*/
    DocumentRow_finalize(row);
    free(row);
}

/** Initialize a list of rows
 * @param list the address of the pointer on the first cell of the list
 */
void IMPLEMENT(DocumentRowList_init)(DocumentRow ** list) {
    /*provided_DocumentRowList_init(list);*/
    *list = NULL;
}

/** Finalize a list of rows
 * @param list the address of the pointer on the first cell of the list
 * @note Each row of the list are destroyer using DocumentRow_destroy()
 */
void IMPLEMENT(DocumentRowList_finalize)(DocumentRow ** list) {
    /*provided_DocumentRowList_finalize(list);*/
    DocumentRow * tmpRow;
    while (*list != NULL)
    {
        tmpRow = *list;
        *list = (*list)->next;
        DocumentRow_destroy(tmpRow);
    }
}

/** Get a pointer on the rowIndex-th row of the list
 * @param list the pointer on the first cell of the list
 * @param rowIndex the index of the requested row
 * @return a pointer on the rowIndex-th row of the list or NULL if the list contains less rows than the requested one
 */
DocumentRow * IMPLEMENT(DocumentRowList_get)(DocumentRow * list, int rowIndex) {
    /*return provided_DocumentRowList_get(list, rowIndex);*/
    int i;
    for(i=0;i<rowIndex;i++){
        if(list->next==NULL)
            return NULL;
        list=list->next;
    }
    return list;
}

/**
 * Get the number of rows in the list
 * @param list the pointer on the first cell of the list
 */
int IMPLEMENT(DocumentRowList_getRowCount)(DocumentRow * list) {
    /*return provided_DocumentRowList_getRowCount(list);*/
    int rowsNumber=0;
    while(list!=NULL){
        list=list->next;
        rowsNumber++;
    }
    return rowsNumber;

}

/** Add a row at the end of the list
 * @param list the address of the pointer on the first cell of the list
 * @param row the row to add
 */
void IMPLEMENT(DocumentRowList_pushBack)(DocumentRow ** list, DocumentRow * row) {
    /*provided_DocumentRowList_pushBack(list, row);*/
    DocumentRow *listPtr = *list;
    if(*list!=NULL){
        while(listPtr->next!=NULL){
            listPtr=listPtr->next;
        }
        listPtr->next=row;
    }else{
        *list=row;
    }
    row->next=NULL;
}

/** Insert a row before a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertBefore)(DocumentRow ** list, DocumentRow * position, DocumentRow * row) {
    /*provided_DocumentRowList_insertBefore(list, position, row);*/
    DocumentRow *listPtr = *list;
    if (*list==position){
        *list=row;
    }else{
        while (listPtr->next!=position){
            listPtr=listPtr->next;
        }
        listPtr->next=row;
    }
    row->next = position;
}

/** Insert a row after a given row
 * @param list the address of the pointer on the first cell of the list
 * @param position a pointer on the positioning row
 * @param row the row to insert
 */
void IMPLEMENT(DocumentRowList_insertAfter)(DocumentRow ** UNUSED(list), DocumentRow * position, DocumentRow * row) {
    /*provided_DocumentRowList_insertAfter(list, position, row);*/
    DocumentRow *next = position->next;
    position->next=row;
    row->next=next;
}

/** Remove a row from the list
 * @param list the address of the pointer on the first cell of the list
 * @param position the row to remove
 */
void IMPLEMENT(DocumentRowList_removeRow)(DocumentRow ** list, DocumentRow * position) {
    /*provided_DocumentRowList_removeRow(list, position);*/
    DocumentRow *listPtr=*list;
    if(listPtr==position){
        *list=position->next;
    }else{
        while(listPtr->next!=position){
            listPtr=listPtr->next;
        }
        listPtr->next=position->next;
    }
    DocumentRow_destroy(position);
}

/** Write a row in a binary file
 * @param row the row
 * @param file the opened file
 */
void IMPLEMENT(DocumentRow_writeRow)(DocumentRow * row, FILE * file) {
    /*provided_DocumentRow_writeRow(row, file);*/
    char buffer[1024];

    writeString(row->code, file);

    writeString(row->designation, file);

    sprintf(buffer, "%f", row->quantity);
    writeString(buffer, file);

    writeString(row->unity, file);

    sprintf(buffer, "%f", row->basePrice);
    writeString(buffer, file);

    sprintf(buffer, "%f", row->sellingPrice);
    writeString(buffer, file);

    sprintf(buffer, "%f", row->discount);
    writeString(buffer, file);

    sprintf(buffer, "%f", row->rateOfVAT);
    writeString(buffer, file);
}

/** Read a row from a file
 * @param file the opened file
 * @return a new row created on the heap filled with the data
 */
DocumentRow * IMPLEMENT(DocumentRow_readRow)(FILE * file) {
    /*return provided_DocumentRow_readRow(file);*/
    char *buffer;
    DocumentRow *row = DocumentRow_create();
    free(row->designation);
    free(row->code);
    free(row->unity);
    row->code = readString(file);
    row->designation = readString(file);

    buffer=readString(file);
    row->quantity = strtod(buffer, NULL);
    free(buffer);

    row->unity = readString(file);

    buffer=readString(file);
    row->basePrice = strtod(buffer, NULL);
    free(buffer);

    buffer=readString(file);
    row->sellingPrice = strtod(buffer, NULL);
    free(buffer);

    buffer=readString(file);
    row->discount = strtod(buffer, NULL);
    free(buffer);

    buffer=readString(file);
    row->rateOfVAT = strtod(buffer, NULL);
    free(buffer);
    return row;
}
