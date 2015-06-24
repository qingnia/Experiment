#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	BLOCK_SIZE	64
#define INODE_SIZE	4
#define INDEX_PER_BLOCK	(BLOCK_SIZE / INODE_SIZE)
#define D_BLOCK_COUNT	2
#define	I_S_BLOCK_COUNT	2
#define I_D_BLOCK_COUNT	2

typedef struct INODE
{
	int direct_block[D_BLOCK_COUNT][INDEX_PER_BLOCK];
	int* indirect_block_S[I_S_BLOCK_COUNT][INDEX_PER_BLOCK];
	int** indirect_block_D[I_D_BLOCK_COUNT][INDEX_PER_BLOCK];
}inode;

void getD_Data(int block_index)
{
	int ret = random() % INDEX_PER_BLOCK;
	printf("phy_block:%d", ret);
}

void getI_S_Data(int* block, int offset)
{
	block[offset] = random() % INDEX_PER_BLOCK;
	printf("block:%d\n", block[offset]);
}

void getI_D_Data(int** block, int s_offset, int offset)
{
	block[s_offset][offset] = random() % INDEX_PER_BLOCK;
	printf("block:%d\n", block[s_offset][offset]);
}

int getBlock(inode* inode, int log_dir)
{
	int consult = log_dir / INDEX_PER_BLOCK;
	int remainder = log_dir % INDEX_PER_BLOCK;
	printf("der:%d\n", remainder);
	if(consult < D_BLOCK_COUNT)
	{
		printf("directi block:%d, offset:%d\n", consult, remainder);
		getD_Data(inode->direct_block[consult][remainder]);
		return 0;
	}
	log_dir = consult - D_BLOCK_COUNT;
	consult = log_dir / INDEX_PER_BLOCK;
	int s_remainder = log_dir % INDEX_PER_BLOCK;
	if(I_S_BLOCK_COUNT > consult)
	{
		printf("indirecti S_block:%d\n", consult);
		getI_S_Data(inode->indirect_block_S[consult][s_remainder], remainder);
		return 0;
	}
	log_dir = consult - I_S_BLOCK_COUNT * INDEX_PER_BLOCK;
	consult = log_dir / INDEX_PER_BLOCK;
	int d_remainder = log_dir % INDEX_PER_BLOCK;
	if(I_D_BLOCK_COUNT > consult)
	{
		printf("indirecti D_block:%d\n", consult);
		getI_D_Data(inode->indirect_block_D[consult][d_remainder], s_remainder, remainder);
		return 0;
	}
	printf("overflow!\n");
	return 1;
}
/*
void setBlockValue(int* block)
{
	int i = 0;
	for(int i = 0; i < INDEX_PER_COUNT; i++)
	{

}
*/
void initInode(inode* node)
{
	int i = 0;
	int j = 0;
	for(; i < I_S_BLOCK_COUNT; i++)
	{
		for(; j < INDEX_PER_BLOCK; j++)
		{
			node->indirect_block_S[i][j] = (int*)malloc(INDEX_PER_BLOCK * sizeof(int));
			memset(node->direct_block[i], 0, INDEX_PER_BLOCK * sizeof(int));
		}
	}
	for(i = 0; i < I_D_BLOCK_COUNT; i++)
	{
		for(; j < INDEX_PER_BLOCK; j++)
		{
			int k = 0;
			node->indirect_block_D[i][j] = (int**)malloc(INDEX_PER_BLOCK * sizeof(int));
			memset(node->indirect_block_D, 0, INDEX_PER_BLOCK * sizeof(int));
			for(; k < INDEX_PER_BLOCK; k++)
			{
				node->indirect_block_D[i][j][k] = (int*)malloc(INDEX_PER_BLOCK* sizeof(int));
				memset(node->indirect_block_D[i][j][k], 0 , INDEX_PER_BLOCK * sizeof(int));
			}
		}
	}
}

int main(int argc, char* argv[])
{
	inode* node = (inode*)malloc(sizeof(inode));
	memset(node, 0, sizeof(inode));
	initInode(node);
	int log_dir = 0;
	printf("input log_dir:");
	scanf("%d", &log_dir);
	getBlock(node, log_dir);
	return 0;
}
