#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE      (1024)
#define TRUE 1
#define FALSE 0

int match(const char* regexp, const char* text);

/*
 * Fill out your functions here
 */
/*-------------------------------------------------------------------*/
/* match: search for regexp anywhere in text. If a match is found,   */
/*   return TRUE and if not, return FALSE                            */
/*-------------------------------------------------------------------*/

int
match(const char *regexp, const char *text)
{
    /* fill out this function */
    
    
    /* integers i, n are used for indexing regexp and text. certain regular expressions will require          */
    /* searching for the subsequent character. therefore, integers z, x are used to mark positions in         */
    /* regex and text when hassearch is TRUE (when searching has been done). This provides a reference point  */
    /* which the algorithm will return to in order to find a matching expression that may exist after the     */
    /* first possible match.                                                                                  */
    int i, n, z = 0, x = 0, hassearch = FALSE;
    
    for (i = 0, n = 0; text[n] != '\0'; n++, i = 0 ) { 
        /* this loop searches for a matching regular expression in text.                    */
        /* if there is no matching expression, the loop will end and FALSE will be returned */
        
        
        if (regexp[0] == '^'){
            /* Here, we test if the text contains the regular expression containing the beginning of input string   */
            /* matching character. This case is seperated from the others since FALSE will be return immediately if */
            /* no match is found.                                                                                   */
            
            /*below is the basic algorithm which checks for a matching regular expression*/
            for (i = 1; text[n] != '\0'; i++, n++) {
                
                if (regexp[i] == '\0' || (regexp[i] == '$' && text[n] == '\0'))
                    return TRUE;
                if (regexp[i] == '$' && text[n] != '\0')
                    return FALSE;
                
                if (regexp[i] == '.'){
                    /* the combinations '.+' and '.*' matches any number of characters until the next corresponding  */
                    /* wildcard or string literal match is found. this requires a search algorithm as written below. */
                
                    
                    if (regexp[i+1] == '?'){
                        i++;
                        
                        if (regexp[i+1] == '\0')
                            return TRUE;
                        
                        if (regexp[i+1] == '\\'){
                            i += 2;
                            if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                                if (text[n] == regexp[i]){
                                    continue;
                                }
                                else if (text[n+1] == regexp[i]){
                                    n++;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'd'){
                                if (isdigit(text[n])){
                                    continue;
                                }
                                else if (isdigit(text[n+1])){
                                    n++;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'D'){
                                if (!isdigit(text[n])){
                                    continue;
                                }
                                else if (!isdigit(text[n+1])){
                                    n++;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 's') {
                                if (isspace(text[n])){
                                    continue;
                                }
                                else if (isspace(text[n+1])){
                                    n++;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'S') {
                                if (!isspace(text[n])){
                                    continue;
                                }
                                else if (!isspace(text[n+1])){
                                    n++;
                                    continue;
                                }
                            }
                            else if (hassearch){
                                hassearch = FALSE;
                                i = z;
                                n = x;
                                continue;
                            }
                            else{
                                return FALSE;
                            }
                        }
                        else if (regexp[i+1] == '.')
                            continue;
                        else if (text[n+1] == regexp[i+1]){
                            continue;
                        }
                        else if (text[n] == regexp[i+1]){
                            n--;
                            continue;
                        }
                        else if (regexp[i+1] == '$' && (text[n] == '\0' || text[n+1] == '\0'))
                            return TRUE;
                        else if (regexp[i+1] == '$'){
                            if (hassearch){
                                hassearch = FALSE;
                                i = z;
                                n = x;
                                continue;
                            }
                            else{
                                break;
                            }
                        }
                        else if (hassearch){
                            hassearch = FALSE;
                            i = z;
                            n = x;
                            continue;
                        }
                        else
                            return FALSE;
                    }
                   
                    /* Start search Algorithm */
                    
                    else if (regexp[i+1] == '*') {
                        z = i-1;
                        x = n;
                        i++;
                        if (regexp[i+1] == '$' || regexp[i+1] == '\0')
                            return TRUE;
                        while(regexp[i+1] == '.'){
                            i++, n++;
                        }
                        
                        if (regexp[i+1] == '\\') {
                            i += 2;
                            if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                                if (regexp[i] == text[n]){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if ((regexp[i+1] == '?' || regexp[i+1] == '*')){
                                        i-=2;
                                        n--;
                                        continue;
                                    }
                                    while (text[n] != regexp[i] && text[n] != '\0'){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                        
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'd')  {
                                if (isdigit(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (!isdigit(text[n] && text[n] != '\0')){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                        
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'D') {
                                if (!isdigit(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (isdigit(text[n]) && text[n] != '\0'){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 's'){
                                if (isspace(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (!isspace(text[n])){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'S') {
                                if (!isspace(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (isspace(text[n])){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else{
                                return FALSE;
                            }
                        }
                        else if (regexp[i] == text[n]){
                            x = n;
                            hassearch = TRUE;
                            continue;
                        }
                        else{
                            i++;
                            if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                i--;
                                n--;
                                continue;
                            }
                            while (text[n] != regexp[i]){
                                n++;
                            }
                            if (text[n] == '\0'){
                                if (hassearch){
                                    hassearch = FALSE;
                                    i = z;
                                    n = x;
                                    continue;
                                }
                                else
                                    return FALSE;
                            }
                            x = n;
                            hassearch = TRUE;
                            continue;
                        }
                    }
                    
                    /* end search algorithm */
                    /* repeat with second case */
                    
                    else if (regexp[i+i] == '+') {
                        z = i;
                        i++, n++;
                        if (regexp[i+1] == '$' || regexp[i+1] == '\0')
                            return TRUE;
                        else if (regexp[i+1] == '.')
                            continue;
                        
                        else if (regexp[i+1] == '\\') {
                            i += 2;
                            if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                                if (regexp[i] == text[n]){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if ((regexp[i+1] == '?' || regexp[i+1] == '*')){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (text[n] != regexp[i] && text[n] != '\0'){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                        
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'd')  {
                                if (isdigit(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (!isdigit(text[n] && text[n] != '\0')){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                        
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'D') {
                                if (!isdigit(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (isdigit(text[n]) && text[n] != '\0'){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 's'){
                                if (isspace(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (!isspace(text[n])){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else if (regexp[i] == 'S') {
                                if (!isspace(text[n])){
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                                else{
                                    if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                        i -= 2;
                                        n--;
                                        continue;
                                    }
                                    while (isspace(text[n])){
                                        n++;
                                    }
                                    if (text[n] == '\0'){
                                        if (hassearch){
                                            hassearch = FALSE;
                                            i = z;
                                            n = x;
                                            continue;
                                        }
                                        else
                                            return FALSE;
                                    }
                                    x = n;
                                    hassearch = TRUE;
                                    continue;
                                }
                            }
                            else{
                                return FALSE;
                            }
                        }
                        else if (regexp[i] == text[n]){
                            x = n;
                            hassearch = TRUE;
                            continue;
                        }
                        else{
                            i++;
                            if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                i--;
                                n--;
                                continue;
                            }
                            while (text[n] != regexp[i]){
                                n++;
                            }
                            if (text[n] == '\0'){
                                if (hassearch){
                                    hassearch = FALSE;
                                    i = z;
                                    n = x;
                                    continue;
                                }
                                else
                                    return FALSE;
                            }
                            x = n;
                            hassearch = TRUE;
                            continue;
                        }
                    }
                }
                /* code below searches for other regexp matches in the text */

                else if (regexp[i] == '\\') {
                    i++;
                    if (regexp[i+1] == '?') {
                        if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]){
                            i++;
                            continue;
                        }
                        else if (regexp[i] == 'd' && (isdigit(text[n]))){
                            i++;
                            continue;
                        }
                        else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                            i++;
                            continue;
                        }
                        else if (regexp[i] == 's' && (isspace(text[n]))){
                            i++;
                            continue;
                        }
                        else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                            i++;
                            continue;
                        }
                        else {
                            n--, i++;
                            continue;
                        }
                    }
                    
                    /* The search algorithm used below is different from above since we are able to check if any combination with '?'
                       and '*' exist. That is, it is not necessary to search for the subsequent character. */
                    
                    else if (regexp [i+1] == '*') {
                        z = i-1;
                        x = n-1;
                        if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]) {
                            while (text[n+1] == text[n]){
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        
                        else if (regexp[i] == 'd' && (isdigit(text[n]))){
                            while (isdigit(text[n+1])){
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                            while (!isdigit(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 's' && (isspace(text[n]))) {
                            while (isspace(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                            while (!isspace(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else {
                            n--;
                            i++;
                            continue;
                        }
                    }
                    
                    else if (regexp[i+1] == '+'){
                        z = i -1;
                        if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]) {
                            while (text[n+1] == text[n]){
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        
                        else if (regexp[i] == 'd' && (isdigit(text[n]))) {
                            while (isdigit(text[n+1])){
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                            while (!isdigit(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 's' && (isspace(text[n]))) {
                            while (isspace(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                            while (!isspace(text[n+1])) {
                                n++;
                            }
                            i++;
                            x=n;
                            hassearch = TRUE;
                            continue;
                        }
                        else
                            return FALSE;
                    }
    
                    else {
                        if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n])
                            continue;
                        else if (regexp[i] == 'd' && (isdigit(text[n])))
                            continue;
                        else if (regexp[i] == 'D' && (!isdigit(text[n])))
                            continue;
                        else if (regexp[i] == 's' && (isspace(text[n])))
                            continue;
                        else if (regexp[i] == 'S' && (!isspace(text[n])))
                            continue;
                        else {
                            return FALSE;
                        }
                    }
                }
                /* search for string literals*/
                
                else if (regexp[i+1] == '?'){
                    if (regexp[i] == text[n]){
                        i++;
                        continue;
                    }
                    else
                        n--, i++;
                }
                else if (regexp[i+1] == '*') {
                    if (regexp[i] == text[n]) {
                        while (text[n+1] == text[n]){
                            n++;
                        }
                        x = n;
                        i++;
                        hassearch = TRUE;
                        continue;
                    }
                    else
                        n--, i++;
                }
                else if (regexp[i+1] == '+'){
                    if (regexp[i] == text[n]) {
                        while (text[n+1] == text[n]){
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (hassearch){
                        hassearch = FALSE;
                        i = z;
                        n = x;
                        continue;
                    }
                    else
                        return FALSE;
                }
                else if (regexp[i] == text[n])
                    continue;
                
                /* This is a precautionary check. If the regexp is in the form _X_X_, where _ represents any character and X is either     */
                /* '*' or '?', the algorithm will check for _. However, searching needs to be done instead as defensively programmed below */
                
                else if (hassearch && (regexp[i-1] == '*' || regexp[i-1] == '?') && ((regexp[i-4] == '*' || regexp[i-4] == '?')|| (regexp[i-3] == '*' || regexp[i-3] == '?'))){
                    while (text[n] != regexp[i]){
                        if (text[n] == '\0')
                            return FALSE;
                        n++;
                    }
                }
                else if (hassearch){
                    hassearch = FALSE;
                    i = z;
                    n = x;
                    continue;
                }
                else
                    return FALSE;
            }
            return FALSE;
        }

        /* This marks the end of the basic algorithm used to find a matching regexp */
        /* The code below searches for a matching character then repeats the matching algorithm above */
        
        /* precautionary check */
        if (text[n] == '\0')
            return FALSE;
        
        /* general case: search for first matching character */
        
        while ((regexp[i] != '\\' &&(regexp[i+1] == '?' || regexp[i+1] == '*')) || (regexp[i] == '\\' && (regexp [i+2] == '*' || regexp[i+2] == '?'))){
            if (regexp[i+1] == '?' || regexp[i+1] == '*')
                i += 2;
            if (regexp[i] == '\\' && (regexp [i+2] == '*' || regexp[i+2] == '?'))
                i += 3;
        }

        
        if (regexp[i] == '.') {
            while (regexp[i] == '.') {
                if (text[n] == '\0')
                    return FALSE;
                else
                    i++, n++;
            }
            if (regexp[i] == '?'){
                n++;
            }
            else if (regexp[i] == '*'){
                i++;
                if (regexp[i] == '$')
                    return TRUE;
                while (regexp[i] =='.') {
                    if (text[n] == '\0')
                        return FALSE;
                    i++, n++;
                }
                
                if (regexp[i] == '\0')
                    return TRUE;
                
                else if (regexp[i] == '\\') {
                    i++;
                    if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                        while (regexp[i] != text[n]) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'd')  {
                        while (!isdigit(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'D') {
                        while (isdigit(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 's'){
                        while (!isspace(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'S') {
                        while (isspace(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else {
                        while (text[n] != regexp[i]) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                }
            }
            else if (regexp[i] == '+') {
                n++, i++;
                if (regexp[i] == '$')
                    return TRUE;
                while (regexp[i] =='.') {
                    if (text[n] == '\0')
                        return FALSE;
                    i++, n++;
                }
                
                if (regexp[i] == '\0')
                    return TRUE;
                
                else if (regexp[i] == '\\') {
                    i++;
                    if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                        while (regexp[i] != text[n]) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'd')  {
                        while (!isdigit(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'D') {
                        while (isdigit(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 's'){
                        while (!isspace(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                    else if (regexp[i] == 'S') {
                        while (isspace(text[n])) {
                            if (text[n] == '\0')
                                return FALSE;
                            n++;
                        }
                    }
                }
                else {
                    while (text[n] != regexp[i]) {
                        if (text[n] == '\0')
                            return FALSE;
                        n++;
                    }
                }
            }
        }
        
        /* search for other wildcard or string literal */
        if (regexp[i] == '$' || regexp[0] == '$' || regexp[0] == '\0')
            return TRUE;
        
        
        else if (regexp[i] == '\\') {
            i++;
            if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                while (regexp[i] != text[n]) {
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else if (regexp[i] == 'd')  {
                while (!isdigit(text[n])) {
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else if (regexp[i] == 'D') {
                while (isdigit(text[n])) {
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else if (regexp[i] == 's'){
                while (!isspace(text[n])) {
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else if (regexp[i] == 'S') {
                while (isspace(text[n])) {
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else {
                return FALSE;
            }
        }
        
        
        else if (regexp[i] != text[n]) {
            while (regexp[i] != text[n]) {
                if (text[n] == '\0')
                    return FALSE;
                n++;
            }
        }
        
        /* matching algorithm: this is exactly the same code for the special first character '^' case.   */
        /* However, return FALSE is replaced by break when the text is not the null character so that    */
        /* the function will return to the beginning of the loop in order to find other possible matches */
        
        do {
            i++; n++;
            if (regexp[i] == '\0' || (regexp[i] == '$' && text[n] == '\0'))
                return TRUE;
            if (regexp[i] == '$' && text[n] != '\0')
                return FALSE;
            
            if (regexp[i] == '.'){
                
                
                if (regexp[i+1] == '?'){
                    i++;
                    
                    if (regexp[i+1] == '\0')
                        return TRUE;
                    
                    if (regexp[i+1] == '\\'){
                        i += 2;
                        if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                            if (text[n] == regexp[i]){
                                continue;
                            }
                            else if (text[n+1] == regexp[i]){
                                n++;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'd'){
                            if (isdigit(text[n])){
                                continue;
                            }
                            else if (isdigit(text[n+1])){
                                n++;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'D'){
                            if (!isdigit(text[n])){
                                continue;
                            }
                            else if (!isdigit(text[n+1])){
                                n++;
                                continue;
                            }
                        }
                        else if (regexp[i] == 's') {
                            if (isspace(text[n])){
                                continue;
                            }
                            else if (isspace(text[n+1])){
                                n++;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'S') {
                            if (!isspace(text[n])){
                                continue;
                            }
                            else if (!isspace(text[n+1])){
                                n++;
                                continue;
                            }
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else if (regexp[i+1] == '.')
                        continue;
                    else if (text[n+1] == regexp[i+1]){
                        continue;
                    }
                    else if (text[n] == regexp[i+1]){
                        n--;
                        continue;
                    }
                    else if (regexp[i+1] == '$' && (text[n] == '\0' || text[n+1] == '\0'))
                        return TRUE;
                    else if (regexp[i+1] == '$'){
                        if (hassearch){
                            hassearch = FALSE;
                            i = z;
                            n = x;
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    else if (hassearch){
                        hassearch = FALSE;
                        i = z;
                        n = x;
                        continue;
                    }
                    else
                        break;
                }
                
                
                else if (regexp[i+1] == '*') {
                    z = i-1;
                    x = n;
                    i++;
                    if (regexp[i+1] == '$' || regexp[i+1] == '\0')
                        return TRUE;
                    while(regexp[i+1] == '.'){
                        i++, n++;
                    }
                    
                    if (regexp[i+1] == '\\') {
                        i += 2;
                        if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                            if (regexp[i] == text[n]){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if ((regexp[i+1] == '?' || regexp[i+1] == '*')){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (text[n] != regexp[i] && text[n] != '\0'){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                    
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'd')  {
                            if (isdigit(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (!isdigit(text[n] && text[n] != '\0')){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                    
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'D') {
                            if (!isdigit(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (isdigit(text[n]) && text[n] != '\0'){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 's'){
                            if (isspace(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (!isspace(text[n])){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'S') {
                            if (!isspace(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (isspace(text[n])){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else if (regexp[i] == text[n]){
                        x = n;
                        hassearch = TRUE;
                        continue;
                    }
                    else{
                        i++;
                        if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                            i--;
                            n--;
                            continue;
                        }
                        while (text[n] != regexp[i]){
                            n++;
                        }
                        if (text[n] == '\0'){
                            if (hassearch){
                                hassearch = FALSE;
                                i = z;
                                n = x;
                                continue;
                            }
                            else
                                return FALSE;
                        }
                        x = n;
                        hassearch = TRUE;
                        continue;
                    }
                }
                
                
                else if (regexp[i+1] == '+') {
                    z = i;
                    i++, n++;
                    if (regexp[i+1] == '$' || regexp[i+1] == '\0')
                        return TRUE;
                    else if (regexp[i+1] == '.')
                        continue;
                    
                    else if (regexp[i+1] == '\\') {
                        i += 2;
                        if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') {
                            if (regexp[i] == text[n]){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if ((regexp[i+1] == '?' || regexp[i+1] == '*')){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (text[n] != regexp[i] && text[n] != '\0'){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                    
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'd')  {
                            if (isdigit(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (!isdigit(text[n] && text[n] != '\0')){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                    
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'D') {
                            if (!isdigit(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (isdigit(text[n]) && text[n] != '\0'){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 's'){
                            if (isspace(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (!isspace(text[n])){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else if (regexp[i] == 'S') {
                            if (!isspace(text[n])){
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                            else{
                                if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                                    i -= 2;
                                    n--;
                                    continue;
                                }
                                while (isspace(text[n])){
                                    n++;
                                }
                                if (text[n] == '\0'){
                                    if (hassearch){
                                        hassearch = FALSE;
                                        i = z;
                                        n = x;
                                        continue;
                                    }
                                    else
                                        return FALSE;
                                }
                                x = n;
                                hassearch = TRUE;
                                continue;
                            }
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else if (regexp[i] == text[n]){
                        x = n;
                        hassearch = TRUE;
                        continue;
                    }
                    else{
                        i++;
                        if (regexp[i+1] == '?' || regexp[i+1] == '*'){
                            i--;
                            n--;
                            continue;
                        }
                        while (text[n] != regexp[i]){
                            n++;
                        }
                        if (text[n] == '\0'){
                            if (hassearch){
                                hassearch = FALSE;
                                i = z;
                                n = x;
                                continue;
                            }
                            else
                                return FALSE;
                        }
                        x = n;
                        hassearch = TRUE;
                        continue;
                    }
                }
            }
            
            else if (regexp[i] == '\\') {
                i++;
                if (regexp[i+1] == '?') {
                    if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]){
                        i++;
                        continue;
                    }
                    else if (regexp[i] == 'd' && (isdigit(text[n]))){
                        i++;
                        continue;
                    }
                    else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                        i++;
                        continue;
                    }
                    else if (regexp[i] == 's' && (isspace(text[n]))){
                        i++;
                        continue;
                    }
                    else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                        i++;
                        continue;
                    }
                    else {
                        n--, i++;
                        continue;
                    }
                }
                
                else if (regexp [i+1] == '*') {
                    z = i-1;
                    x = n-1;
                    if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]) {
                        while (text[n+1] == text[n]){
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    
                    else if (regexp[i] == 'd' && (isdigit(text[n]))){
                        while (isdigit(text[n+1])){
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                        while (!isdigit(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 's' && (isspace(text[n]))) {
                        while (isspace(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                        while (!isspace(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else {
                        n--;
                        i++;
                        continue;
                    }
                }
                
                else if (regexp[i+1] == '+'){
                    z = i -1;
                    if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n]) {
                        while (text[n+1] == text[n]){
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    
                    else if (regexp[i] == 'd' && (isdigit(text[n]))) {
                        while (isdigit(text[n+1])){
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 'D' && (!isdigit(text[n]))){
                        while (!isdigit(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 's' && (isspace(text[n]))) {
                        while (isspace(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (regexp[i] == 'S' && (!isspace(text[n]))) {
                        while (!isspace(text[n+1])) {
                            n++;
                        }
                        i++;
                        x=n;
                        hassearch = TRUE;
                        continue;
                    }
                    else if (hassearch){
                        hassearch = FALSE;
                        i = z;
                        n = x;
                        continue;
                    }
                    else
                        return FALSE;
                }
                
                else {
                    if ((regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '\\') && regexp[i] == text[n])
                        continue;
                    else if (regexp[i] == 'd' && (isdigit(text[n])))
                        continue;
                    else if (regexp[i] == 'D' && (!isdigit(text[n])))
                        continue;
                    else if (regexp[i] == 's' && (isspace(text[n])))
                        continue;
                    else if (regexp[i] == 'S' && (!isspace(text[n])))
                        continue;
                    else {
                        return FALSE;
                    }
                }
            }
            
            else if (regexp[i+1] == '?'){
                if (regexp[i] == text[n]){
                    i++;
                    continue;
                }
                else
                    n--, i++;
            }
            else if (regexp[i+1] == '*') {
                if (regexp[i] == text[n]) {
                    while (text[n+1] == text[n]){
                        n++;
                    }
                    x = n;
                    i++;
                    hassearch = TRUE;
                    continue;
                }
                else
                    n--, i++;
            }
            else if (regexp[i+1] == '+'){
                if (regexp[i] == text[n]) {
                    while (text[n+1] == text[n]){
                        n++;
                    }
                    i++;
                    x=n;
                    hassearch = TRUE;
                    continue;
                }
                else if (hassearch){
                    hassearch = FALSE;
                    i = z;
                    n = x;
                    continue;
                }
                else
                    break;
            }
            else if (regexp[i] == text[n]){
                continue;
            }
            else if (hassearch && (regexp[i-1] == '*' || regexp[i-1] == '?') && (regexp[i-2] == '.' || (regexp[i-4] == '.' && (regexp[i-3] == '*' || regexp[i-3] == '?')) || (regexp[i-5] == '.' && (regexp[i-4] == '?' || regexp[i-4] == '*') && regexp[i-3] == '\\'))){
                while (text[n] != regexp[i]){
                    if (text[n] == '\0')
                        return FALSE;
                    n++;
                }
            }
            else if (hassearch){
                hassearch = FALSE;
                i = z;
                n = x;
                continue;
            }
            else
                break;
        } while ((text[n] != '\0'));
    }
    return FALSE;
}
/*-------------------------------------------------------------------*/
/* is_valid_regexp: check whether regexp is in the correct format    */
/*-------------------------------------------------------------------*/
int
is_valid_regexp(const char* regexp)
{
    /* fill out this function */
    
    if (regexp[0] == '$' || regexp[strlen(regexp)-1] == '^'){
        return FALSE;
    }
    else if (regexp[0] == '+' || regexp[0] == '?' || regexp[0] == '*'){
        return FALSE;
    }
    else if (regexp[0] == '^' && (regexp[1] == '+' || regexp[1] == '?' || regexp[1] == '*')) {
        return FALSE;
    }

    for (int i = 1; i <= (strlen(regexp)); i++) {
    
        if (regexp[i] == '$' && regexp[i+1] == '\0')
            return TRUE;
        else if ((regexp[i] == '^' || regexp[i] == '$') && regexp[i-1] != '\\') {
            break;
        }
        else if ((regexp[i] == '+' || regexp[i] == '?' || regexp[i] == '*') && (regexp[i+1] == '+' || regexp[i+1] == '?' || regexp[i+1] == '*') && regexp[i-1] != '\\') {
            break;
        }
        else if (regexp[i] == '\\') {
            i++;
            if (regexp[i] == '^' || regexp[i] == '$' || regexp[i] == '.' || regexp[i] == '?' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == 'd' || regexp[i] == 'D' || regexp[i] == 's' || regexp[i] == 'S'){
                continue;
            }
            else {
                break;
            }
        }
        else if (regexp[i] == '\0')
            return TRUE;
        else
            continue;
    }
    return FALSE;
}
/*-------------------------------------------------------------------*/
/* grep: searches for regexp in the file 'f', prints each line that  */
/* matches regexp, and returns the number of maching lines           */
/*-------------------------------------------------------------------*/
int
grep(const char* regexp, FILE* f, const char* filename)
{
    char buf[BUFSIZE];
    int nmatch = 0;
    int n;
    
    while (fgets(buf, sizeof(buf), f)) {
        n = strlen(buf);
        /* terminate the input string */
        if (n > 0 && buf[n-1] == '\n')
            buf[n-1] = '\0';
        if (match(regexp, buf)) {
            nmatch++;
            printf("%s:%s\n", filename, buf);
        }
    }
    return(nmatch);
}
/*-------------------------------------------------------------------*/
int
main(int argc, char *argv[])
{
    int i;
    FILE *f;
    int nmatch = 0;
    
    if (argc < 2) {
        fprintf(stderr, "usage mygrep regexp [file ...]");
        return(EXIT_FAILURE);
    }
    
    /* if the regular expression in the wrong format, complain and stop
     here */
    if (!is_valid_regexp(argv[1])) {
        fprintf(stderr, "wrong regular expression format:%s", argv[1]);
        return(EXIT_FAILURE);
    }
    
    /* main grep */
    if (argc == 2) {
        /* we're getting the text from the standard input. Note that we
         use 'stdin' as the second parameter(FILE*). 'stdin' is a vaild
         pointer that points to the standard input. It is automatically
         opened before main() is called.
         */
        nmatch = grep(argv[1], stdin, "stdin");
    }
    else {
        /* reading one file at a time */
        for (i = 2; i < argc; i++) {
            f = fopen(argv[i], "r");
            if (f == NULL) {
                fprintf(stderr, "can't open %s:", argv[i]);
                continue;
            }
            nmatch += grep(argv[1], f, argv[i]);
            fclose(f);
        }
    }
    printf("Total # of matching lines: %d\n", nmatch);
    return(EXIT_SUCCESS);
}
