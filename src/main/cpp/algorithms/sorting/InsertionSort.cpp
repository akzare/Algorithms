#include <iostream>
using namespace std;

//Function to print array.
void display(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
    cout<< arr[i]<<"\t"; 
    cout<<"\n"; 
} 

//Main function to run the program.
int main() 
{ 
    int array[] = {5, 3, 1, 9, 8, 2, 4,7}; 
    int size = sizeof(array)/sizeof(array[0]); 

    cout<<"Before Insertion sort: \n";
    display(array, size);//Using dispaly function to print unsorted array.

    int i, target, j;  
    for (i = 1; i < size; i++) 
    {  
        target = array[i];  
        j = i - 1;  

        /* Here the elements in b/w arrary[0 to i-1]
        which are greater than target are moved
        ahead by 1 position each*/
        while (j >= 0 && array[j] > target) 
        {  
            array[j + 1] = array[j];  
            j = j - 1;  
        }  
        array[j + 1] = target;  
    }
    cout<<"After Insertion sort: \n"; 
    display(array, size);//Using dispaly function to print sorted array. 
    return 0; 
}
