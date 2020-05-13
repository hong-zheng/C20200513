#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * 算法效率：时间复杂度 空间复杂度
 * 渐进复杂度 大O表示法
 * 时间：基本操作次数
 * 空间：变量个数
 * 常数: 1
 * 最高次项: 忽略次数
 * 线性表：顺序表，链表，栈，队列
 * 	顺序表：静态
 * 		动态：堆
 */
typedef int DataType ;
typedef struct seqList{
	DataType* _array ;
	size_t  _size ;
	unsigned int _capacity ;	
	// 大小确定,静态数据表，静态数据开在栈上
//	int _array[100] ;
//	int _size ;	
}seqList;

void seqListInit( seqList* sl ){
	sl->_capacity = 4;
	sl->_array = (DataType*)malloc(sizeof(DataType)*sl->_capacity) ;
	sl->_size = 0 ;
}

void checkCapacity( seqList* sl ){
	// 增容
	if( sl->_size == sl->_capacity ){
		sl->_capacity *= 2 ;
		// 开空间
		DataType* newArray = (DataType*)malloc(sizeof(DataType)*sl->_capacity) ;
		// 拷贝
		memcpy( newArray , sl->_array , sizeof(DataType)*sl->_size ) ;
		// 释放
		free( sl->_array ) ;
		sl->_array = newArray ;
	}
} 
	
// pushBack : 尾插
void seqListPushBack( seqList* sl , DataType value ){
	checkCapacity( sl ) ;
	sl->_array[sl->_size++] = value ;
}

/*
 * 尾删
 */
void seqListPopBack( seqList* sl ){
	// 不释放空间
	if( sl->_size )
		--sl->_size ;
}

/*
 * 头插
 */
void seqListPushFront( seqList* sl , DataType value ){
	checkCapacity( sl ) ;
	//元素移动需要从后向前移动，防止元素覆盖
	// 用无符号类型时注意变量横大于0,边界条件就是大于0
	size_t end = sl->_size ;
	while( end > 0 ){
		sl->_array[end] = sl->_array[end - 1] ;
		end-- ;
	}
	sl->_array[0] = value ;
	sl->_size++ ;
}

/*
 * 头删
 * 
 */
void seqListPopFront( seqList* sl ){
	// 将后面的元素向前移动一个位置	
	// 从前向后
	if( sl->_size ){
		size_t start = 1 ;
		while( start < sl->_size ){
			sl->_array[start - 1] = sl->_array[start] ;
			++start ;
		}
		--sl->_size ;
	}
}

// 在 pos 位置前面插入一个数据value
void seqListInsert( seqList* sl , size_t pos , DataType value){
	// 判断位置是否合法
	if( pos <= sl->_size ){
		checkCapacity( sl ) ;
		size_t end = sl->_size ;
		while( end > pos ){
			sl->_array[end] = sl->_array[end-1] ;
			--end ;
		}
		sl->_array[pos] = value ;
		++sl->_size ;
	}
}

//删除pos位置的数据
void seqListErase( seqList* sl , size_t pos ){
	if( pos < sl->_size ){
		size_t start = pos ;
		while( start < sl->_size-1 ){
			sl->_array[start] = sl->_array[start+1] ;
			++start ;
		}
		--sl->_size ;
	}
}

/*
 * 顺序表的查找
 */
int seqListFind( seqList* sl , DataType value ){
	int i = 0 ;
	for( ; i<sl->_size;i++){
		if( sl->_array[i] == value )
			return i ;
	}
	return -1 ;
/*
	if( sl->_size ){
		int i = 0 ;
		for( ;i<sl->_size;i++){
			if( sl->_array[i] == value ){
				return i ;
			}
		}
		return -1 ;
	}
	return -2 ;
*/
}

void seqListPrint( seqList* sl ){
	int i = 0 ;
	for( ; i<sl->_size ; i++){
		printf("%d ",sl->_array[i] ) ;
	}
	printf("\n") ;
}

void test(){
	seqList sl ;
	seqListInit( &sl ) ;
	int i = 0 ;
	printf("验证尾插:>\n") ;
	for( i = 0 ;i<10; i++ ){
		seqListPushBack( &sl , i ) ;
	}
	seqListPrint( &sl ) ;
	printf("验证头插:>\n") ;
	for( ;i<15;i++)
		seqListPushFront( &sl , i ) ;
	seqListPrint( &sl ) ;
	printf("头删测试:>\n") ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	printf("检验指定位置插入操作:>\n") ;
	seqListInsert( &sl , 3 , 30 ) ;
	seqListPrint( &sl ) ;
	seqListInsert( &sl , 0 , 130 ) ;
	seqListPrint( &sl ) ;
	
/*
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
	seqListPopFront( &sl ) ;
	seqListPrint( &sl ) ;
*/
}

int main(){
	test() ;
	return 0 ;
}
int mainb(){
/*
 * malloc 申请空间失败返回NULL
 */
	int* ret = malloc(40);
	int* ret1 = realloc( NULL  , 400 ) ;
//	free( ret ) ;
	free( ret1 ) ;
	return 0 ;
}
