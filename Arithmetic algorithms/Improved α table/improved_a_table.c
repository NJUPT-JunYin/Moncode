#include "improved_a_table.h"
#include "stdio.h"
#include <stdlib.h> 
#include <malloc.h>

//
GFType gfmul(GFType a, GFType b);
GFType gfdiv(GFType a, GFType b);
//

GFType prim_poly[17] = 
{ 
/*	0 */	0x00000000,
/*  1 */    0x00000003, 
/*  2 */    0x00000007,
/*  3 */    0x0000000b,
/*  4 */    0x00000013,
/*  5 */    0x00000025,
/*  6 */    0x00000043,
/*  7 */    0x00000089,
/*  8 */    0x0000011d,
/*  9 */    0x00000211,
/* 10 */    0x00000409,
/* 11 */    0x00000805,
/* 12 */    0x00001053,
/* 13 */    0x0000201b,
/* 14 */    0x00004443,
/* 15 */    0x00008003,
/* 16 */    0x0001100b,
}; 

int gFieldSize;

//
GFType* table_alpha;
GFType* table_index;
GFType** table_mul;
GFType** table_div;

void gf_init(unsigned int m, unsigned int prim)// GF(2^m), primitive polymonial
{
	int i=0,j=0;
	
	if (m > 16)	// the field size is supported from GF(2^1) to GF(2^16). 
		return;

	gFieldSize = 1<<m;

	if (0 == prim)
		prim = prim_poly[m];


	table_alpha = (GFType*)malloc(sizeof(GFType)*(gFieldSize*4+1));
	table_index = (GFType*)malloc(sizeof(GFType)*(gFieldSize+1));
	

	table_alpha[0]=1;
	table_index[0]=gFieldSize*2;

	for (i=1; i<gFieldSize; i++)
	{
		table_alpha[i] = table_alpha[i-1]<<1;
		if (table_alpha[i]>=gFieldSize)
		{
			table_alpha[i]^=prim;
		}

		table_index[table_alpha[i]]=i;
	}

	for (i=gFieldSize; i<gFieldSize*2; i++)
	{
		table_alpha[i] = table_alpha[i%(gFieldSize-1)];
	}
	for (i=gFieldSize*2; i<=gFieldSize*4; i++)
	{
		table_alpha[i] = 0;
	}

	table_index[1]=0;

}

void gf_uninit()
{

	free(table_alpha);
	free(table_index);

}

// show  the contents of the array
void gf_print()
{
	int i;
	for (i=0; i<gFieldSize; i++)
	{
		printf("%d\t %d\t %d\n", i, table_alpha[i], table_index[i]);
	}
}


GFType gfmul(GFType a, GFType b)
{
	return table_alpha[(table_index[a]+table_index[b])];
}

GFType gfdiv(GFType a, GFType b)
{
	return table_alpha[(table_index[a]-table_index[b]+(gFieldSize-1))];
}


GFType gf_exp(GFType a, GFType n)
{
	return table_alpha[table_index[a]*n%(gFieldSize-1)];
}