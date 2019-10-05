#include "mmemory.h"
#include <stdlib.h>

struct Block {
    VA       	data;			//pointer to real data
    size_t      dataSize;
};

/**
info structure
**/
struct MemoryManager {
	//init flag
    int 			isInited;	//TODO: make isInited=0
    //user data memory
    VA       		heap;
    size_t     		heapSize;	//why by default ==1?TODO: make heapSize=0
    //memory block marking
    struct Block*   blocks;
    size_t			blocksAmount;
};

struct MemoryManager manager;

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
	/*
	TODO: undefined behaviour if size_t<0 (return -2)
	*/
	//printf("\t[init=%d,szBlock=%d,blocks(%d)]\n",manager.isInited,szBlock,manager.blocksAmount);//log

	//check initialisation
	if(!manager.isInited)
		return 1;
	//check arguments
	if(szBlock==0)
	//if(szBlock<=0)
		return -1;
	if(!ptr)
		return -1;
	//search free space with required size
	*ptr=0;
	if(!manager.blocksAmount) {
		//no blocks yet
		if(szBlock<manager.heapSize)
			*ptr=manager.heap;
		else//{
			//printf("\t[szBlock(%d)>manager.heapSize(%d)]\n",szBlock,manager.heapSize);	//log
			return -2;
			//}
	} else {
		//calculate free space between blocks
		for(int i=0;i<manager.blocksAmount-1;i++) {
			VA prev_end = manager.blocks[i].data+manager.blocks[i].dataSize;
			VA next_start = manager.blocks[i+1].data;
			if(prev_end+szBlock<next_start) {
				//required space found
				*ptr=prev_end;
				break;
			}
		}
		//calculate free space after block(s)
		if((*ptr)==0) {
			//if(szBlock<0) printf("[SZBLOCK<0]");	//log
			VA last_end = manager.blocks[manager.blocksAmount-1].data-manager.heap+
							manager.blocks[manager.blocksAmount-1].dataSize;
			VA memory_end = manager.heapSize;
			if(last_end+szBlock<memory_end) {
				//required space found
				*ptr=last_end;
			} else //{	//log
				//printf("\t[required space not found (need end %d real %d]\n",last_end+szBlock,memory_end);
				
				//required space not found
				return -2;
				//}
		}
	}
	//create space block
	manager.blocks[manager.blocksAmount].data=*ptr;
	manager.blocks[manager.blocksAmount].dataSize=szBlock;
	manager.blocksAmount++;
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
int initialize (int n, int szPage) {
	//check input values
	if(n<=0||szPage<=0)
		return -1;
	//allocate data heap
	manager.heapSize = n*szPage;
	manager.heap = malloc(manager.heapSize*sizeof(VA));
	if(manager.heap == NULL)
		return 1;
	//create array of blocks with maximal length
	manager.blocks = (struct Block*) calloc(manager.heapSize, sizeof(struct Block));
	manager.blocksAmount = 0;
	//initializsation is completed
	manager.isInited = 1;
	return 0;
}

//searchFreeBlock(size_t)

//memset() in writing
