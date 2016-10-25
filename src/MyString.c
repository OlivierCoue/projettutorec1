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
 * $Id: MyString.c 293 2011-10-02 15:05:44Z sebtic $
 */

#include <MyString.h>
#include <limits.h>

/** Like the tolower() function. It converts the letter c to lower case, if possible.
 * @param c the letter to convert
 * @return the lower case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toLowerChar)(char c) {
    if(c>='A' && c<='Z')
        return (char) (c+'a'-'A');
    else
        return c;
}

/** Like the toupper() function. It converts the letter c to upper case, if possible.
 * @param c the letter to convert
 * @return the upper case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toUpperChar)(char c) {
    if(c>='a' && c<='z')
        return (char) (c+'A'-'a');
    else
        return c;
}

/** Like the strcmp() function. It compares the two strings str1 and str2.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(compareString)(const char * str1, const char * str2) {
    int i;
    int str1Size = (int) stringLength(str1);
    int str2Size = (int) stringLength(str2);
    int size = (str1Size > str2Size) ? str1Size : str2Size;

    for(i=0; i<size; i++){
        if(str1[i] > str2[i])
            return 1;
        if(str1[i] < str2[i])
            return -1;
    }

    return 0;
}

/** Like the strcasecmp() function. It compares the two strings str1 and str2, ignoring the case of the characters.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(icaseCompareString)(const char * str1, const char * str2) {
    /*return provided_icaseCompareString(str1, str2);*/
    int i;
    int str1Size = (int) stringLength(str1);
    int str2Size = (int) stringLength(str2);
    int size = (str1Size > str2Size) ? str1Size : str2Size;

    for(i=0; i<size; i++){
        if(toLowerChar(str1[i]) > toLowerChar(str2[i]))
            return 1;
        if(toLowerChar(str1[i]) < toLowerChar(str2[i]))
            return -1;
    }

    return 0;
}

/** Like the strlen() function. It calculates the length of the string str, not including the terminating '\\0' character.
 * @param str the string
 * @return the number of characters in str.
 */
size_t IMPLEMENT(stringLength)(const char * str) {
    int i=0;
    while(*str!='\0'){
        str++;
        i++;
    }
    return (size_t)i;
}

/** Copy the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 *
 * @param dest the destination string
 * @param src the source string
 */
void IMPLEMENT(copyString)(char * dest, const char * src) {
    fprintf(stderr,
            "You should avoid strcpy and copyString. Use strncpy or copyStringWithLength instead\n");
    copyStringWithLength(dest, src, INT_MAX);
}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize) {
    int i;
    for(i=0; i<(int)destSize-1; i++){
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * IMPLEMENT(duplicateString)(const char * str) {
    char * dest;

    dest = (char *)malloc((stringLength(str)+1)*sizeof(char));
    if(dest == NULL)
        fatalError("Allocation error");

    copyStringWithLength(dest, str, (size_t)stringLength(str)+1);
    return dest;
}

/** Test if the string str begins by the string start, ignoring the case of the characters.
 * @param start the string which should be at the beginning of str
 * @param str the string to test
 * @return a non null number (true) if the str begins with the string start, false otherwise
 */
int IMPLEMENT(icaseStartWith)(const char * start, const char * str) {
    int i=0;
    while(start[i]!='\0'){
        if(toLowerChar(str[i])!=toLowerChar(start[i]))
            return 0;
        i++;
    }
    return 1;
}

/** Test if the string str ends by the string start, ignoring the case of the characters.
 * @param end the string which should be at the end of str
 * @param str the string to test
 * @return a non null number (true) if the str ends with the string end, false otherwise
 */
int IMPLEMENT(icaseEndWith)(const char * end, const char * str) {
    int i;
    int endLength = (int)stringLength(end);
    int strLength = (int)stringLength(str);
    int startOfEndIndex = strLength-endLength;

    if(startOfEndIndex<0)
        return 0;

    for(i=startOfEndIndex; i<strLength; i++){
        if(toLowerChar(end[i-startOfEndIndex])!=toLowerChar(str[i]))
            return 0;
    }

    return 1;
}

/** Create a new string on the heap which is the result of the concatenation of the two strings.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str1 the first string
 * @param str2 the second string
 * @return the new string
 */
char * IMPLEMENT(concatenateString)(const char * str1, const char * str2) {
    int i;
    char *result;
    int size1 = (int)stringLength(str1);
    int size2 = (int)stringLength(str2);
    result = (char *)malloc(((long unsigned int)size1+(long unsigned int)size2+1)*sizeof(char));
    if(result == NULL)
        exit(-1);

    for(i=0; i<size1; i++){
        result[i] = str1[i];
    }

    for(i=0; i<size2+1; i++){
        result[size1+i] = str2[i];
    }

    result[size1+i] = '\0';
    return result;
}

/** Like the index() function. It returns a pointer to the first occurrence of the character c in the string str.
 * @param str the string to search in
 * @param c the character to find
 * @return a pointer to the first occurrence of the character c in the string str if c is in str, NULL otherwise
 */
const char * IMPLEMENT(indexOfChar)(const char *str, char c) {
    return provided_indexOfChar(str, c);
}

/** Create a copy on the heap of part of a string. The new string contains the characters pointed from start (inclusive) to end (exclusive).
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param start a pointer to the first character of the new string
 * @param end a pointer to the next character of the new string (the pointed character is not part of the new string)
 * @return the new string
 *
 * @code
 * char * str = "abcdef";
 * char * s1 = subString(str,str);
 * char * s2 = subString(str,str+strlen(str));
 * char * s3 = subString(str+1,str+2);
 *
 * We get:
 *    s1: "";
 *    s2: "abcdef";
 *    s3: "b";
 * @endcode
 */
char * IMPLEMENT(subString)(const char * start, const char * end) {
    return provided_subString(start, end);
}

/** Like the strstr() function. It returns a pointer to the first occurrence of the string aiguille in the string meule_de_foin.
 * @param meule_de_foin the string to search in
 * @param aiguille the string to find
 * @return a pointer to the first occurrence of the string aiguille in the string meule_de_foin if aiguille is in meule_de_foin, NULL otherwise
 */
const char * IMPLEMENT(indexOfString)(const char *meule_de_foin, const char *aiguille) {
    int testedLength = 0, aiguilleLength;
    aiguilleLength = (int)stringLength(aiguille);

    while(*meule_de_foin!='\0' && testedLength<aiguilleLength){
        if(*meule_de_foin == aiguille[testedLength]){
            testedLength++;
        }else if(*meule_de_foin == aiguille[0]){
            testedLength = 1;
        }else{
            testedLength=0;
        }
        meule_de_foin++;
    }

    return (aiguilleLength == testedLength) ? meule_de_foin-aiguilleLength : NULL;
}

/** Convert a string to upper case.
 * @param str the string to convert
 */
void IMPLEMENT(makeUpperCaseString)(char * str) {
    int i;
    for(i=0; str[i]!='\0'; i++){
        str[i] = toUpperChar(str[i]);
    }
}

/** Convert a string to lower case.
 * @param str the string to convert
 */
void IMPLEMENT(makeLowerCaseString)(char * str) {
    int i;
    for(i=0; str[i]!='\0'; i++){
        str[i] = toLowerChar(str[i]);
    }
}

/** Create a new string on the heap which contents is the result of the insertion in src of insertLength characters from  toBeInserted at position insertPosition.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param src the string in which the insertion is done
 * @param insertPosition the position where the insertion is done
 * @param toBeInserted a pointer on the first character to insert
 * @param insertLength the number of character to insert
 * @return the new string
 */
char * IMPLEMENT(insertString)(const char * src, int insertPosition, const char * toBeInserted,
        int insertLength) {
    return provided_insertString(src, insertPosition, toBeInserted, insertLength);
}
