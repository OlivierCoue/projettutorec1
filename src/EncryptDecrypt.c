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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>

static char encode(char key, char decoded);
static char decode(char key, char encoded);

void IMPLEMENT(encrypt)(const char * key, char * str) {
    int i=0, j=0;
    while(str[i]!='\0'){
        if(toLowerChar(str[i])>='a' && toLowerChar(str[i])<='z'){
            str[i]=encode(toLowerChar(key[j]), toLowerChar(str[i]));
            if(key[j+1]!='\0')
                j++;
            else
                j=0;
        }
        i++;
    }
}
void IMPLEMENT(decrypt)(const char * key, char * str) {
    int i=0, j=0;
    while(str[i]!='\0'){
        if(toLowerChar(str[i])>='a' && toLowerChar(str[i])<='z'){
            str[i]=decode(toLowerChar(key[j]), toLowerChar(str[i]));
            if(key[j+1]!='\0')
                j++;
            else
                j=0;
        }
        i++;
    }
}

static char encode(char key, char decoded){
    if( ((decoded)+(key-'a')) > 'z' )
        return (char)((decoded)+(key-'a')-26);
    else
        return (char)((decoded)+(key-'a'));
}


static char decode(char key, char encoded){
    if( ((encoded)-(key-'a')) < 'a' )
        return (char)((encoded)-(key-'a')+26);
    else
        return (char)((encoded)-(key-'a'));
}
