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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogRecord.h>

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_code)(const char * value)
{
  /*return provided_CatalogRecord_isValueValid_code(value);*/
  int isValid = 0;
  int i = 0;
    while(value[i]!='\0'){
      isValid=0;
      if(toLowerChar(value[i])>='a'&&toLowerChar(value[i])<='z')
        isValid=1;
      if(value[i]>='0'&&value[i]<='9')
        isValid=1;
      if(!isValid)
        return 0;
    i++;
  }
  return 1;

}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_positiveNumber)(const char * value)
{
  /*return provided_CatalogRecord_isValueValid_positiveNumber(value);*/
  double n=0;
  char *stopstring;
  n = strtod(value, &stopstring);
  if(n>0 && stringLength(stopstring)==0)
    return 1;
  return 0;
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_code)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_code(record, value);*/
  free(record->code);
  record->code = duplicateString(value);
}

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_designation)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_designation(record, value);*/
  free(record->designation);
  record->designation = duplicateString(value);
}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_unity)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_unity(record, value);*/
  free(record->unity);
  record->unity = duplicateString(value);
}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_basePrice)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_basePrice(record, value);*/
  char *stopstring;
  double d = strtod(value, &stopstring);
  record->basePrice = d;
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_sellingPrice)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_sellingPrice(record, value);*/
  char *stopstring;
  double d = strtod(value, &stopstring);
  record->sellingPrice = d;
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_rateOfVAT)(CatalogRecord * record, const char * value)
{
  /*provided_CatalogRecord_setValue_rateOfVAT(record, value);*/
  char *stopstring;
  double d = strtod(value, &stopstring);
  record->rateOfVAT = d;
}

/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_code)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_code(record);*/
  return duplicateString(record->code);
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_designation)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_designation(record);*/
  return duplicateString(record->designation);
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_unity)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_unity(record);*/
  return duplicateString(record->unity);
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_basePrice)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_basePrice(record);*/
  char *s = (char *) malloc(CATALOGRECORD_BASEPRICE_SIZE);
  if(s==NULL)
    fatalError("Allocation Error");
  sprintf(s, "%.2f", record->basePrice);
  return s;
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_sellingPrice)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_sellingPrice(record);*/
  char *s = (char *) malloc(CATALOGRECORD_SELLINGPRICE_SIZE);
  if(s==NULL)
    fatalError("Allocation Error");
  sprintf(s, "%.2f", record->sellingPrice);
  return s;
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_rateOfVAT)(CatalogRecord * record)
{
  /*return provided_CatalogRecord_getValue_rateOfVAT(record);*/
  char *s = (char *) malloc(CATALOGRECORD_RATEOFVAT_SIZE);
  if(s==NULL)
    fatalError("Allocation Error");
  sprintf(s, "%.2f", record->rateOfVAT);
  return s;
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void IMPLEMENT(CatalogRecord_init)(CatalogRecord * record)
{
  /*provided_CatalogRecord_init(record);*/
  record->basePrice = 0;
  record->sellingPrice = 0;
  record->rateOfVAT = 0;
  record->code = duplicateString("");
  record->designation = duplicateString("");
  record->unity = duplicateString("");
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void IMPLEMENT(CatalogRecord_finalize)(CatalogRecord * record)
{
  /*provided_CatalogRecord_finalize(record);*/
  if(record->code!=NULL)
    free(record->code);
  if(record->designation!=NULL)
    free(record->designation);
  if(record->unity!=NULL)
    free(record->unity);
}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void IMPLEMENT(CatalogRecord_read)(CatalogRecord * record, FILE * file)
{
  /*provided_CatalogRecord_read(record, file);*/
  char codeTab[CATALOGRECORD_CODE_SIZE];
  char designationTab[CATALOGRECORD_DESIGNATION_SIZE];
  char unityTab[CATALOGRECORD_UNITY_SIZE];


  if(fread(codeTab, sizeof(char)*CATALOGRECORD_CODE_SIZE, 1, file)!=1)
    fatalError("Writing Error");
  if(fread(designationTab, sizeof(char)*CATALOGRECORD_DESIGNATION_SIZE, 1, file)!=1)
    fatalError("Writing Error");
  if(fread(unityTab, sizeof(char)*CATALOGRECORD_UNITY_SIZE, 1, file)!=1)
    fatalError("Writing Error");
  if(fread(&record->basePrice, sizeof(double), 1, file)!=1)
    fatalError("Writing Error");
  if(fread(&record->sellingPrice, sizeof(double), 1, file)!=1)
    fatalError("Writing Error");
  if(fread(&record->rateOfVAT, sizeof(double), 1, file)!=1)
    fatalError("Writing Error");

  CatalogRecord_setValue_code(record, codeTab);
  CatalogRecord_setValue_designation(record, designationTab);
  CatalogRecord_setValue_unity(record, unityTab);
}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void IMPLEMENT(CatalogRecord_write)(CatalogRecord * record, FILE * file)
{
  /*provided_CatalogRecord_write(record, file);*/
  char codeTab[CATALOGRECORD_CODE_SIZE] = {0};
  char designationTab[CATALOGRECORD_DESIGNATION_SIZE] = {0};
  char unityTab[CATALOGRECORD_UNITY_SIZE] = {0};

  copyStringWithLength(codeTab, record->code, CATALOGRECORD_CODE_SIZE);
  copyStringWithLength(designationTab, record->designation, CATALOGRECORD_DESIGNATION_SIZE);
  copyStringWithLength(unityTab, record->unity, CATALOGRECORD_UNITY_SIZE);

  if(fwrite(codeTab, CATALOGRECORD_CODE_SIZE*sizeof(char), 1, file)!=1){
    fclose(file);
    exit(-1);
  }
  if(fwrite(designationTab, CATALOGRECORD_DESIGNATION_SIZE*sizeof(char), 1, file)!=1){
    fclose(file);
    exit(-1);
  }
  if(fwrite(unityTab, sizeof(char)*CATALOGRECORD_UNITY_SIZE, 1, file)!=1){
    fclose(file);
    exit(-1);
  }
  if(fwrite(&record->basePrice, sizeof(double), 1, file)!=1){
    fclose(file);
    exit(-1);
  }
  if(fwrite(&record->sellingPrice, sizeof(double), 1, file)!=1){
    fclose(file);
    exit(-1);
  }
  if(fwrite(&record->rateOfVAT, sizeof(double), 1, file)!=1){
    fclose(file);
    exit(-1);
  }
}

