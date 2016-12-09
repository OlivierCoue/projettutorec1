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
 * $Id: Dictionary.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Dictionary.h>

/** Create an empty dictionary on the heap
 * @return a new dictionary
 * @warning the dictionary should be destroyed using Dictionary_destroy()
 */
Dictionary * IMPLEMENT(Dictionary_create)(void)
{
  /*return provided_Dictionary_create();*/
  Dictionary *dico;
  dico = (Dictionary*)malloc(sizeof(Dictionary));
  if(dico==NULL)
      fatalError("Allocation Error");
  dico->count = 0;
  dico->entries = NULL;
  return dico;
}

/** Destroy a dictionary
 * @param dictionary the dictionary
 */
void IMPLEMENT(Dictionary_destroy)(Dictionary * dictionary)
{
  /*provided_Dictionary_destroy(dictionary);*/
  int i;
  for(i=0; i<dictionary->count; i++){
    free(dictionary->entries[i].name);
    if(dictionary->entries[i].type == STRING_ENTRY)
      free(dictionary->entries[i].value.stringValue);
  }
  free(dictionary->entries);
  free(dictionary);
}

/** Get a pointer on the entry associated with the given entry name
 * @param dictionary the dictionary
 * @param name the name of the entry
 * @return a pointer on the entry or NULL if the entry was not found
 */
DictionaryEntry * IMPLEMENT(Dictionary_getEntry)(Dictionary * dictionary, const char * name)
{
  /*return provided_Dictionary_getEntry(dictionary, name);*/
  int i;
  for(i=0; i<dictionary->count; i++){
    if(icaseCompareString(dictionary->entries[i].name, name)==0)
      return &dictionary->entries[i];
  }
  return NULL;
}

/** Define or change a dictionary entry as a string
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setStringEntry)(Dictionary * dictionary, const char * name, const char * value)
{
  /*provided_Dictionary_setStringEntry(dictionary, name, value);*/
  DictionaryEntry *entry = Dictionary_getEntry(dictionary, name);
  if(entry == NULL){
    DictionaryEntry newEntry;
    newEntry.name = duplicateString(name);
    newEntry.type = STRING_ENTRY;
    newEntry.value.stringValue = duplicateString(value);
    dictionary->count++;
    dictionary->entries = (DictionaryEntry*)realloc(dictionary->entries, (size_t)dictionary->count*sizeof(DictionaryEntry));
    if(dictionary->entries == NULL)
      exit(-1);
    dictionary->entries[dictionary->count-1] = newEntry;
  }else{
    if(entry->type == STRING_ENTRY)
      free(entry->value.stringValue);

    entry->type = STRING_ENTRY;
    entry->value.stringValue = duplicateString(value);
  }
}

/** Define or change a dictionary entry as a number
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setNumberEntry)(Dictionary * dictionary, const char * name, double value)
{
  /*provided_Dictionary_setNumberEntry(dictionary, name, value);*/
  DictionaryEntry *entry = Dictionary_getEntry(dictionary, name);
  if(entry == NULL){
    DictionaryEntry newEntry;
    newEntry.name = duplicateString(name);
    newEntry.type = NUMBER_ENTRY;
    newEntry.value.numberValue = value;
    dictionary->count++;
    dictionary->entries = (DictionaryEntry*)realloc(dictionary->entries, (size_t)dictionary->count*sizeof(DictionaryEntry));
    if(dictionary->entries == NULL)
      exit(-1);
    dictionary->entries[dictionary->count-1] = newEntry;
  }else{
    if(entry->type == STRING_ENTRY)
      free(entry->value.stringValue);

    entry->type = NUMBER_ENTRY;
    entry->value.numberValue = value;
  }
}

/** Create a new string on the heap which is the result of the formatting of format according to the dictionary content
 * @param dictionary the dictionary
 * @param format the string to format
 * @return a new string created on the heap
 * @warning the user is responsible for freeing the returned string
 */
char * IMPLEMENT(Dictionary_format)(Dictionary * dictionary, const char * format)
{
  return provided_Dictionary_format(dictionary, format);
}
