#include <stdio.h>
#include <math.h>
extern int var_2;
int foo();
int bar();

static int var_5= 10;
int var_3;
int my_int[3] = {1, 2, 3};

int foo()
{
	static int var_3;	
	int a =6;
	var_2=3;
	
}
int bar(){
	
	var_3 = 8;
	int r = 10;
	int x = sqrt(r);
		
	//return var_5;
}
int foo_bar()
{
	foo();
	bar();
}
