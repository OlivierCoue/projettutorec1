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
 * $Id: PrintFormat.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <PrintFormat.h>
#include <Dictionary.h>

char *readLine(FILE*file);

/** Initialize a print format
 * @param format a print format
 * @warning initialized print format should be finalized with PrintFormat_finalize()
 */
void IMPLEMENT(PrintFormat_init)(PrintFormat * format)
{
  /*provided_PrintFormat_init(format);*/
  format->name = duplicateString("");
  format->header = duplicateString("");
  format->row = duplicateString("");
  format->footer = duplicateString("");
}

/** Finalize a print format
 * @param format the print format
 */
void IMPLEMENT(PrintFormat_finalize)(PrintFormat * format)
{
  /*provided_PrintFormat_finalize(format);*/
  free(format->name);
  free(format->header);
  free(format->row);
  free(format->footer);
}

/** Load a print format from a file
 * @param format an initialized print format to fill
 * @param filename the file name
 */
void IMPLEMENT(PrintFormat_loadFromFile)(PrintFormat * format, const char * filename)
{
  provided_PrintFormat_loadFromFile(format, filename);
}

char *readLine(FILE*file){
    char * newLine;
    char buffer[100];
    char * tmpLineToFree;
    newLine =  duplicateString("");

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        tmpLineToFree = newLine;
        newLine = concatenateString(newLine, buffer);
        free(tmpLineToFree);

        if (buffer[stringLength(buffer) - 1] == '\n')
            return newLine;
    }
    return newLine;
}
