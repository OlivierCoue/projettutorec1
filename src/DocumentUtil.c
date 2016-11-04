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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(computeDocumentNumber)(long id) {
    /*return provided_computeDocumentNumber(id);*/
   char buf[8];
   char* pt = buf;
   int i;
   size_t nb;
   char tmp;
   do
   {
      if(id%36<10)
        *pt++ = (char)(id%36+'0');
      else
        *pt++ = (char)(id%36+'A'-10);
   }while( id/=36 );
   *pt = '\0';
   nb=stringLength(buf);
   for(i=0;i<(int)nb/2;i++)
   {
       tmp = buf[i];
       buf[i] = buf[(int)nb-i-1];
       buf[(int)nb-i-1] = tmp;
   }
   return duplicateString(buf);
}

/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(formatDate)(int day, int month, int year) {
    /*return provided_formatDate(day, month, year);*/
    char *res;
    res = (char*)malloc(20*sizeof(char));
    if(res==NULL)
        fatalError("Allocation error");
    sprintf(res,"%02i/%02i/%02i",day,month,year);
    return res;
}


/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */
void IMPLEMENT(writeString)(const char * str, FILE * file) {
    provided_writeString(str,file);
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * IMPLEMENT(readString)(FILE * file) {
    return provided_readString(file);
}
