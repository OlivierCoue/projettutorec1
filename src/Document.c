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
 * $Id: Document.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Document.h>
#include <DocumentUtil.h>
#include <DocumentRowList.h>

/** Initialize a document
 * @param document a pointer to a document
 * @warning An initialized document must be finalized by Document_finalize() to free all resources
 */
void IMPLEMENT(Document_init)(Document * document) {
    /*provided_Document_init(document);*/
    CustomerRecord_init(&document->customer);
    document->editDate = duplicateString("");
    document->expiryDate = duplicateString("");
    document->docNumber = duplicateString("");
    document->object = duplicateString("");
    document->operator = duplicateString("");
    document->rows = NULL;
    document->typeDocument = QUOTATION;
}

/** Finalize a document
 * @param document the document to finalize
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_finalize)(Document * document) {
    /*provided_Document_finalize(document);*/
    CustomerRecord_finalize(&document->customer);
    free(document->editDate);
    free(document->expiryDate);
    free(document->docNumber);
    free(document->object);
    free(document->operator);
    DocumentRowList_finalize(&document->rows);
}

/** Save the content of a document to a file
 * @param document the document
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_saveToFile)(Document * document, const char * filename) {
    /*provided_Document_saveToFile(document,filename);*/
    int i;
    int rowsNb;
    rowsNb = DocumentRowList_getRowCount(document->rows);
    FILE * file = fopen(filename, "wb+");

    if (file == NULL)
        fatalError("Cannot open file");

    CustomerRecord_write(&document->customer, file);
    writeString(document->editDate, file);
    writeString(document->expiryDate, file);
    writeString(document->docNumber, file);
    writeString(document->object, file);
    writeString(document->operator, file);
    if(fwrite(&rowsNb, sizeof(int),1,file)!=1)
        fatalError("Write Error");

    for(i=0;i<rowsNb;i++){
        DocumentRow_writeRow(DocumentRowList_get(document->rows, i), file);
    }
    fclose(file);
}

/** Load the content of a document from a file
 * @param document the document to fill
 * @param filename the file name
 * @warning document must have been initialized
 */
void IMPLEMENT(Document_loadFromFile)(Document * document, const char * filename) {
    /*provided_Document_loadFromFile(document,filename);*/
    int i,rowsNb;
    FILE * file = fopen(filename, "rb");
    if (file == NULL)
        fatalError("Cannot open file");

    Document_finalize(document);
    CustomerRecord_read(&document->customer, file);
    document->editDate = readString(file);
    document->expiryDate = readString(file);
    document->docNumber = readString(file);
    document->object = readString(file);
    document->operator = readString(file);
    if(fread(&rowsNb, sizeof(int), 1, file)!=1)
        fatalError("Read Error");

    for(i=0;i<rowsNb;i++){
        DocumentRowList_pushBack(&document->rows, DocumentRow_readRow(file));
    }
    fclose(file);
}

