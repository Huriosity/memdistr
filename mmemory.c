#include "mmemory.h"
#include <stdbool.h>
#include <stdlib.h>

struct {
    void*       data;			//pointer to real data
    size_t      dataSize;
    VA          userPointer;	//user pointer
} Block;

struct MemoryManager {
	//init flag
    bool 			isInited;	//TODO: make default=false
    //user data memory
    void*       	heap;
    size_t     		heapSize;
    //memory block marking
    struct Block*   blocks;
    size_t			blocksAmount;
};

struct MemoryManager manager;


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
	manager.heap = malloc(manager.heapSize);
	if(manager.heap == NULL)
		return 1;
	//create array of blocks with maximal length
	manager.blocks = (struct Block*) calloc(manager.heapSize, sizeof(Block));
	manager.blocksAmount = 0;
	//initializsation is completed
	manager.isInited = 1;
	return 0;
}

//searchFreeBlock(size_t)

//memset() in writing
