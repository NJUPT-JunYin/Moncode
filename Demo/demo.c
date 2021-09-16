#include<stdio.h>
#include"gf_lookuptable.h"
void main()
{

	int i;
	int j;
	GFType a = 6, b = 15;
	GFType c,d,e,f;
	gf_init(12, 0);
	//printf("\n%d\n",table_alpha);
	c = gf_mul(a, b);
	d = gf_div(a, b);
	e = gf_add(a,b);
	printf("加法结果%d\n", e);
	printf("乘法结果%d\n", c);
	printf("除法结果%d\n", d);

/*	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			f=gf_mul(i,j);
			printf("%d  ",f);
		}
		printf("\n");
	}
*/
//	gf_print();
//	printf("%d\n",table_alpha);
	gf_uninit();

//	getchar();
}