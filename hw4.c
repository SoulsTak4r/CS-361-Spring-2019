/*
    Hamza Amjad
    hamjad2
    Project 4


*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hw4.h"


typedef unsigned int bit20;
typedef unsigned int bit10;




// insert function
int insert_pte(uint32 p, uint32 f, uint32 read, uint32 write)
{

    bit10 frame1;
    bit10 L1;
    bit10 L2;
    bit20 vale = p;
   
     //------bitwise---------
    L1 = (p & 0xFFC00) >> 10;
    L2 = p & 0x3FF;
    //------endbitwise------
    frame1 = L1 + 1;
    
   
    

    // mapping 
    if(pageTable[frame1][L2] != 0)
    {
        return -4;
    }
     //check if read is 1 and write is 1 
    if(read == 1)
    {
        if (write == 1)
        {
            pageTable[0][L1] = frame1 * 4096 + 7;
            pageTable[frame1][L2] = f * 4096 + 7;
            return 1;
        }
        else
        {
            pageTable[0][L1] = frame1 * 4096 +7;
            pageTable[frame1][L2] = f * 4096 + 5;
            return 1;
        }

    }
    else
    {
        pageTable[0][L1] = frame1 * 4096 + 7;
        pageTable[frame1][L2] = f * 4096 + 3;
        return 1;
    }
   
    if (write != 1 && write != 0)
    {
        return -2;
    }

    if (read != 0 && read != 1)
    {
        return -1;
    }
    

}


//remove function
int remove_pte(uint32 p)
{
    bit20 vale = p;
    bit10 frame;
    bit10 L1;
    bit10 L2;
    //-----bitwise-----------
    L1 = (vale & 0xFFC00) >> 10;
    L2 = vale & 0x3FF;
    //-----end bitwise---------
    frame = L1 + 1;

    //error checking
    if(pageTable[frame][p] == 0)
    {
        return -3;
    }

    pageTable[0][L1] = 0;
    pageTable[frame][L2] = 0;

    return 1; 
}


// read function 
int read_vaddr(uint32 vaddr, char *c)
{   
    //declaring variables to be used in this functions
    uint32 pVal;
    uint32 val1;
    uint32 val2;
    bit10 L1;
    bit10 L2;
    bit20 frame1;
    uint32 pVal2;
    uint32 vale2;
    
    //-------bitwise--------------
    val1 = vaddr & 4095;
    pVal = (vaddr - val1) / 4096;
    val2 = pVal;


    L1 = (val2 & 0xFFC00) >> 10;
    L2 = val2 & 0x3FF;
    //--------end bitwise---------



    frame1 = L1 + 1;
    bit10 vale = pageTable[frame1][L2];
    vale2 = vale & 7;

    bit20 frame2 = (vale - vale2) / 4096;
    if(vale2 == 7 || vale2 == 5)
    {
        *c = userPages[frame2 * 4096 + val1];
        return 1;
    }
    //error checking 
    else
    {
        return -1;
    }
    
    



}

//write function 
int write_vaddr(uint32 vaddr, char c)
{
    // declaring variables to be used in this function
    uint32 pVal;
    uint32 val1;
    uint32 val2;
    bit10 L1;
    bit10 L2;
    bit20 frame1;
    uint32 pVal2;
    uint32 vale2;
    
    //------bitwise---------
    val1 = vaddr & 4095;
    pVal = (vaddr - val1) / 4096;
    val2 = pVal;


    L1 = (val2 & 0xFFC00) >> 10;
    L2 = val2 & 0x3FF;
    //------end bitwise-------


    frame1 = L1 + 1;
    bit10 vale = pageTable[frame1][L2];
    vale2 = vale & 7;

    bit20 frame2 = (vale - vale2) / 4096;

    if (vale2 == 3 ||  vale2 == 7 )
    {
        userPages[frame2 * 4096 + val1] = c;
        return 1;
    }

    // error chechking
    else 
    {
        return -2;
    }

}

// int main ()
// {
//     int  insert_res = insert_pte(4097,29,0,1);
 
// 	printf("The return value for 3 insert is:%d\n ", insert_res);



// }