#include "mmemory.h"
#include <stdlib.h>

/**
info structure
**/
struct Block {
    VA       	data;			//pointer to real data
    size_t      dataSize;
};

/**
data structure
**/
struct MemoryManager {
    //user data memory
    VA       		heap;
    size_t     		heapSize;	//why by default ==1?TODO: make heapSize=0
    //memory block marking
    struct Block*   blocks;
    size_t			blocksAmount;
};

//init flag
int 			isInited=0;	//TODO: make isInited=0

struct MemoryManager* manager=0;	//{0,0,0,0,0};
//max memory size
const long MAX_MEM_SIZE = (long)INT_MAX*INT_MAX;

/**
 	@func	_malloc
 	@brief	Выделяет блок памяти определенного размера

	@param	[out] ptr		адресс блока
	@param	[in]  szBlock	размер блока

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	-2	нехватка памяти
	@retval	1	неизвестная ошибка
 **/
int _malloc (VA* ptr, size_t szBlock) {
////	printf("\t[init=%d],manager=%p\n",isInited,manager);
	//check initialisation
	if(!isInited)
		return 1;
	//check arguments
	if(szBlock>=LONG_MAX)
		return -1;		//bigger than max memory
	else {
		//check if negative
		long lng_szBlock = (long)szBlock;	//size_t is unsigned
		if(lng_szBlock<=0)
			return -1;
	}
	if(!ptr)
		return -1;
	//search free space with required size
	*ptr=0;
	if(!manager->blocksAmount) {
		//no blocks yet
		if(szBlock<manager->heapSize)
			*ptr=manager->heap;
		else {
////			printf("\t[szBlock(%ld)>manager->heapSize(%ld)]\n",szBlock,manager->heapSize);
			return -2;
		}
	} else {
		//calculate free space between blocks
		for(int i=0;i<manager->blocksAmount-1;i++) {
			VA prev_end = manager->blocks[i].data+manager->blocks[i].dataSize;
			VA next_start = manager->blocks[i+1].data;
			if(prev_end+szBlock<next_start) {
				//required space found
				*ptr=prev_end;
				break;
			}
		}
		//calculate free space after block(s)
		if((*ptr)==0) {
			if(manager->blocks[manager->blocksAmount-1].data-manager->heap<0) {
////				printf("\t&heap>&blocks[last]\n");
				return 1;
			}
			VA last_end = manager->blocks[manager->blocksAmount-1].data+
				manager->blocks[manager->blocksAmount-1].dataSize;
			VA memory_end = manager->heap+manager->heapSize;
			if(last_end+szBlock<=memory_end) {
				//required space found
				*ptr=last_end;
			} else {
				//required space not found
////				printf("\t[required space not found (mem on %ld,need %ld]\n",
////												last_end+szBlock,memory_end);
				return -2;
			}
		}
	}
	//create space block
////	printf("\tblock:%p-%p\n",*ptr,*ptr+szBlock);
	manager->blocks[manager->blocksAmount].data=*ptr;
	manager->blocks[manager->blocksAmount].dataSize=szBlock;
	manager->blocksAmount++;
	//memory allocation is completed
	return 0;
}

/**
 	@func	initialize
 	@brief	Инициализация модели менеджера памяти

	@param	[in] n		количество страниц
	@param	[in] szPage	размер страницы

	В варианте 1 и 2 общий объем памяти расчитывается как n*szPage

	@return	код ошибки
	@retval	0	успешное выполнение
	@retval	-1	неверные параметры
	@retval	1	неизвестная ошибка
 **/
int initialise (int n, int szPage) {
	isInited=0;
	//check input values
	if(n<=0||szPage<=0)
		return -1;
	//if manager exists, free it
	if(manager) {
////		printf("free manager\n");
		free(manager->blocks);
		manager->blocksAmount=0;
		free(manager->heap);
		manager->heapSize=0;
		free(manager);
		manager=0;
	}
	//create manager
	manager = (struct MemoryManager*) malloc(sizeof(struct MemoryManager));
	if(!manager) {
////		printf("manager's memory was not allocated\n");
		return 1;
	}
	//allocate data heap
	manager->heapSize = (long)n*szPage;			//max==INT_MAX^2<LONG_MAX
	manager->heap = malloc(sizeof(VA)*manager->heapSize);
	if(manager->heap==0) {
////		printf("heap's memory was not allocated\n");
		free(manager);
		manager=0;
		return 1;
	}
	//create array of blocks with maximal length
	manager->blocks = (struct Block*) calloc(manager->heapSize, sizeof(struct Block));
	manager->blocksAmount = 0;
	//initialisation is completed
	isInited = 1;
////	printf("heap:%p,allocated:%ld\n",manager->heap,manager->heapSize);
	return 0;
}

//searchFreeBlock(size_t)

//memset() in writing
