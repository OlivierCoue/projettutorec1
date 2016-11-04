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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerRecord.h>

void IMPLEMENT(CustomerRecord_setValue_name)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_name(record, value);*/
  copyStringWithLength(record->name, value, CUSTOMERRECORD_NAME_SIZE);
}

void IMPLEMENT(CustomerRecord_setValue_address)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_address(record, value);*/
  copyStringWithLength(record->address, value, CUSTOMERRECORD_ADDRESS_SIZE);
}

void IMPLEMENT(CustomerRecord_setValue_postalCode)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_postalCode(record, value);*/
  copyStringWithLength(record->postalCode, value, CUSTOMERRECORD_POSTALCODE_SIZE);
}

void IMPLEMENT(CustomerRecord_setValue_town)(CustomerRecord * record, const char * value)
{
  /*provided_CustomerRecord_setValue_town(record, value);*/
  copyStringWithLength(record->town, value, CUSTOMERRECORD_TOWN_SIZE);
}

char * IMPLEMENT(CustomerRecord_getValue_name)(CustomerRecord * record)
{
  /*return provided_CustomerRecord_getValue_name(record);*/
  return duplicateString(record->name);
}

char * IMPLEMENT(CustomerRecord_getValue_address)(CustomerRecord * record)
{
  /*return provided_CustomerRecord_getValue_address(record);*/
  return duplicateString(record->address);
}

char * IMPLEMENT(CustomerRecord_getValue_postalCode)(CustomerRecord * record)
{
  /*return provided_CustomerRecord_getValue_postalCode(record);*/
  return duplicateString(record->postalCode);
}

char * IMPLEMENT(CustomerRecord_getValue_town)(CustomerRecord * record)
{
  /*return provided_CustomerRecord_getValue_town(record);*/
  return duplicateString(record->town);
}

void IMPLEMENT(CustomerRecord_init)(CustomerRecord * record)
{
  /*provided_CustomerRecord_init(record);*/
  int i;
  for(i=0;i<(int)CUSTOMERRECORD_NAME_SIZE;i++){
      record->name[i]='\0';
  }
  for(i=0;i<(int)CUSTOMERRECORD_ADDRESS_SIZE;i++){
      record->address[i]='\0';
  }
  for(i=0;i<(int)CUSTOMERRECORD_POSTALCODE_SIZE;i++){
      record->postalCode[i]='\0';
  }
  for(i=0;i<(int)CUSTOMERRECORD_TOWN_SIZE;i++){
      record->town[i]='\0';
  }
}

void IMPLEMENT(CustomerRecord_finalize)(CustomerRecord * record)
{
  provided_CustomerRecord_finalize(record);
}

void IMPLEMENT(CustomerRecord_read)(CustomerRecord * record, FILE * file)
{
  /*provided_CustomerRecord_read(record, file);*/
  fread(record->name, sizeof(char), CUSTOMERRECORD_NAME_SIZE, file);
  fread(record->address, sizeof(char), CUSTOMERRECORD_ADDRESS_SIZE, file);
  fread(record->postalCode, sizeof(char), CUSTOMERRECORD_POSTALCODE_SIZE, file);
  fread(record->town, sizeof(char), CUSTOMERRECORD_TOWN_SIZE, file);
}

void IMPLEMENT(CustomerRecord_write)(CustomerRecord * record, FILE * file)
{
  /*provided_CustomerRecord_write(record, file);*/
  fwrite(record->name, sizeof(char), CUSTOMERRECORD_NAME_SIZE, file);
  fwrite(record->address, sizeof(char), CUSTOMERRECORD_ADDRESS_SIZE, file);
  fwrite(record->postalCode, sizeof(char), CUSTOMERRECORD_POSTALCODE_SIZE, file);
  fwrite(record->town, sizeof(char), CUSTOMERRECORD_TOWN_SIZE, file);
}

