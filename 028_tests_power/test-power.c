#include <stdlib.h>
#include <stdio.h>
extern unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
    if(power(x,y)==expected_ans)
	return;
    printf("Failed on input %d, %d: expected %d, got %d\n",x,y,expected_ans,power(x,y));
    exit(EXIT_FAILURE);
    return;
}

int main(void){
    run_check(0,0,1);
    run_check(100,0,1);
    run_check(0,100,0);
    run_check(1000,3,1000000000);
    return EXIT_SUCCESS;
}
