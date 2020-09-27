'''
 * @file   KMPSubStringSearch.py
 * @author Abhinav Koul, abhinav2scientist@gmail.com
 * @date   27 Sep 2020
 * @version 0.1
 * @brief   Knuth–Morris–Pratt algorithm implementation
'''


def computeLPS(substr,lps):
    '''
    LPS Array : lps indicates longest proper prefix which is also suffix.
    lps is passed as reference thus we dont return
    '''
    len_substr = len(substr)

    lps[0] = 0  # since there is no proper prefix or suffix for a single character 
    length = 0  # to keep track of how many characters proper prefix == suffix
    i = 1 

    while( i < len_substr):
        if(substr[i] == substr[length]):
            length += 1
            lps[i] = length
            i += 1
        else:
            if(length != 0):
                #check just preceding character
                length = lps[length - 1]
            else:    # if length == 0 then we cant go back, thus it doesnt repeat
                lps[i] = 0
                i += 1
    
def KMPSearch(string,substr):
    '''
    Worst case : O(N) ==> N is length of text(string where we need to search)
    Space : O(M) ==> M is the length of pattern(Substring which we need to search)
    '''
    m = len(substr)
    n = len(string)

    #create lps
    lps = [0]*m
    computeLPS(substr,lps)

    #pointers to check for string and substr
    i = 0 #for string
    j = 0 #for substr

    while i<n:
        if(substr[j] == string[i]):
            i += 1
            j += 1
        if(j == m):
            print("Pattern found at index : ",str(i-j))
            #update j for next matching
            j = lps[j-1]    
        elif (i<n and substr[j]!=string[i]):
            if j != 0:
                #keep checking previous possible positions
                j = lps[j-1]
            else:
                #we cant find it thus increment character
                i += 1


string = "ababcabcabababd"
substr = "ababd"
KMPSearch(string,substr)