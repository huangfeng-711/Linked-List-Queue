/******************************************************************************
* 文件名称：Linked_List.c
* 文件标识：无
* 内容摘要：链表相关处理
* 其他说明：
* 当前版本：V1.00
* 作    者：**
* 完成日期：2017年2月14日
*    
* 修改记录：1
* 修改日期：2017年2月14日
* 版 本 号：V1.00
* 修 改 人：**
* 修改内容：无
******************************************************************************/

#include "type_def.h"
#include "Linked_List.h"
#include "Soft_timer.h"

/******************************************************************************
* 函数名称: BYTE Linked_List_Init(T_LINKED_LIST_PARA **ptLinkedListInit)
* 功能说明: 链表初始化
* 输入参数: 无
* 输出参数: T_LINKED_LIST_PARA **ptLinkedListInit  链表表头地址为NULL
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_Init(T_LINKED_LIST_PARA **o_ptLinkedListInit)
{
    /* Init the address of Head point */
    (*o_ptLinkedListInit) = NULL;
    return SW_OK;  
}


/******************************************************************************
* 函数名称: T_LINKED_LIST_PARA* Linked_List_Create(T_LINKED_LIST_PARA *ptLinkedListHead, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
* 功能说明: 创建链表
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListHead 链表头指针
*           BYTE ucData1              链表数据1,用作起始时间
*                                     1~256s
*           BYTE ucData2              链表数据2,用作延时时间
*                                     1~256s
*           BYTE ucFreCount           链表数据3,用作功能函数执行次数
*                                     0:无限次执行
*                                     1-256:对应执行次数
*           WORD32 (*pfFunc)(void)    链表数据4,用作功能函数调用
* 输出参数: 无
* 返 回 值: 头指针地址
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
T_LINKED_LIST_PARA* Linked_List_Create(T_LINKED_LIST_PARA *ptLinkedListHead, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
{
    T_LINKED_LIST_PARA *ptLinkedListCreat;

    /* Alloc Linked List Date Struct */
    ptLinkedListCreat = (T_LINKED_LIST_PARA *)malloc(sizeof(T_LINKED_LIST_PARA));
    /* If malloc is failed, then return */
    if(NULL == ptLinkedListCreat)
    {   
        return NULL;
    }
    /* If Linked List contain Node, then return */
    if(NULL != ptLinkedListHead)
    {
        return NULL;
    }
    
    /* The Linked List contain One Node */
    ptLinkedListHead                   = ptLinkedListCreat;
    ptLinkedListCreat->ucElements1     = ucData1;
    ptLinkedListCreat->ucElements2     = ucData2; 
    ptLinkedListCreat->ucCount         = ucFreCount;
    ptLinkedListCreat->pfSoftTimerFunc = pfFunc;       
    ptLinkedListCreat->ptNext          = NULL;
    return ptLinkedListHead;
}


/******************************************************************************
* 函数名称: BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **ptLinkedListInsert, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
* 功能说明: 在表头添加节点
* 输入参数: BYTE ucData1              链表数据1,用作起始时间
*                                     1~256s
*           BYTE ucData2              链表数据2,用作延时时间
*                                     1~256s
*           BYTE ucFreCount           链表数据3,用作功能函数执行次数
*                                     0:无限次执行
*                                     1-256:对应执行次数
*           WORD32 (*pfFunc)(void)    链表数据4,用作功能函数调用
* 输出参数: T_LINKED_LIST_PARA **ptLinkedListInsert 链表头指针地址
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **o_ptLinkedListInsert, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
{
    T_LINKED_LIST_PARA *ptInsertHead;

    /* Alloc Linked List Date Struct */
    ptInsertHead = (T_LINKED_LIST_PARA *)malloc(sizeof(T_LINKED_LIST_PARA));
    /* If malloc is failed, then return */
    if(NULL == ptInsertHead)
    {   
        return SW_NONE_MEANING;
    }
    
    /* The Linked List Add One Node */
    ptInsertHead->ucElements1     = ucData1;
    ptInsertHead->ucElements2     = ucData2;
    ptInsertHead->ucCount         = ucFreCount;
    ptInsertHead->pfSoftTimerFunc = pfFunc;  
    /* Linked to the behind Node */
    ptInsertHead->ptNext          = (*o_ptLinkedListInsert);
    /* Upadte new Head Pointer */
    (*o_ptLinkedListInsert)       = ptInsertHead;
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertLast(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
* 功能说明: 在表尾添加节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListInsert 链表最后一个节点的头指针
*           BYTE ucData1              链表数据1,用作起始时间
*                                     1~256s
*           BYTE ucData2              链表数据2,用作延时时间
*                                     1~256s
*           BYTE ucFreCount           链表数据3,用作功能函数执行次数
*                                     0:无限次执行
*                                     1-256:对应执行次数
*           WORD32 (*pfFunc)(void)    链表数据4,用作功能函数调用
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_InsertLast(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
{
    T_LINKED_LIST_PARA *ptInsertLast;

    /* Alloc Linked List Date Struct */
    ptInsertLast = (T_LINKED_LIST_PARA *)malloc(sizeof(T_LINKED_LIST_PARA));
    /* If malloc is failed, then return */
    if(NULL == ptInsertLast)
    {   
        return SW_NONE_MEANING;
    }
    
    /* The Linked List Add One Node */
    ptInsertLast->ucElements1      = ucData1;
    ptInsertLast->ucElements2      = ucData2; 
    ptInsertLast->ucCount          = ucFreCount;
    ptInsertLast->pfSoftTimerFunc  = pfFunc; 
    ptInsertLast->ptNext           = NULL;
    
    /* Find The Laste Node */    
    while(NULL != ptLinkedListInsert->ptNext)
    {
        ptLinkedListInsert     = ptLinkedListInsert->ptNext;
    }
    /* Linked to the Last Node */
    ptLinkedListInsert->ptNext = ptInsertLast;
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertMiddle(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucInsertNum, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
* 功能说明: 在表中添加节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListInsert 链表插入节点的头指针
*           BYTE ucInsertNum 插入节点号
*           BYTE ucData1              链表数据1,用作起始时间
*                                     1~256s
*           BYTE ucData2              链表数据2,用作延时时间
*                                     1~256s
*           BYTE ucFreCount           链表数据3,用作功能函数执行次数
*                                     0:无限次执行
*                                     1-256:对应执行次数
*           WORD32 (*pfFunc)(void)    链表数据4,用作功能函数调用
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_InsertMiddle(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucInsertNum, BYTE ucData1, BYTE ucData2, BYTE ucFreCount, WORD32 (*pfFunc)(void))
{
    T_LINKED_LIST_PARA *ptInsertMiddle, *ptInsertTpm;
    BYTE ucCount = 0;
    /* Linked List contain zero Node */    
    if(NULL == ptLinkedListInsert)
    {
        return SW_NONE_MEANING;
    }
    /* Insert number is error */
    if(0 == ucInsertNum)
    {
        return SW_NONE_MEANING;
    }

    /* Find The Insert Node */    
    while(NULL != ptLinkedListInsert)
    {
        ucCount = ucCount + 1;
        if(ucCount == ucInsertNum)
        {
            break;
        }
        ptInsertTpm        = ptLinkedListInsert;
        ptLinkedListInsert = ptLinkedListInsert->ptNext;
    }
    /* Exceed the Linked List */
    if(ucCount != ucInsertNum)
    {
        return SW_NONE_MEANING;
    }
    
    /* Alloc Linked List Date Struct */
    ptInsertMiddle = (T_LINKED_LIST_PARA *)malloc(sizeof(T_LINKED_LIST_PARA));
    /* If malloc is failed, then return */
    if(NULL == ptInsertMiddle)
    {   
        return SW_NONE_MEANING;
    }
    
    /* Update the Insert Node Next point */
    ptInsertMiddle->ptNext          = ptInsertTpm->ptNext;
    /* Update the front of Insert Node Next point */
    ptInsertTpm->ptNext             = ptInsertMiddle;
    ptInsertMiddle->ucElements1     = ucData1;
    ptInsertMiddle->ucElements2     = ucData2;
    ptInsertMiddle->ucCount         = ucFreCount;
    ptInsertMiddle->pfSoftTimerFunc = pfFunc; 
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_DeleteHead(T_LINKED_LIST_PARA **o_ptLinkedListDelete)
* 功能说明: 在表头删除节点
* 输入参数: 
* 输出参数: T_LINKED_LIST_PARA **o_ptLinkedListDelete 链表头指针地址
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_DeleteHead(T_LINKED_LIST_PARA **o_ptLinkedListDelete)
{
    T_LINKED_LIST_PARA *ptDeleteHead;

    /* Delete Linked List Date Struct */
    ptDeleteHead = *o_ptLinkedListDelete;
    /* Linked List contain zero Node */
    if(NULL == ptDeleteHead)  
    {
        return SW_NONE_MEANING;
    }
    else
    {
        /* Upadte new Head Pointer */
        (*o_ptLinkedListDelete) = ptDeleteHead->ptNext;
        free(ptDeleteHead);
        return SW_OK;
    }
}

/******************************************************************************
* 函数名称: BYTE Linked_List_DeleteLast(T_LINKED_LIST_PARA *ptLinkedListDelete)
* 功能说明: 在表尾删除节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListDelete 链表尾指针地址
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_DeleteLast(T_LINKED_LIST_PARA *ptLinkedListDelete)
{
    T_LINKED_LIST_PARA *ptDeleteLast, *ptDeleteTpm;

    /* Delete Linked List Date Struct */
    ptDeleteLast = ptLinkedListDelete;
    /* Linked List contain zero Node */
    if(NULL == ptDeleteLast)  
    {
        return SW_NONE_MEANING;
    }

    while(NULL != ptDeleteLast->ptNext)
    {
        ptDeleteTpm  = ptDeleteLast;
        ptDeleteLast = ptDeleteLast->ptNext;
    }
    free(ptDeleteLast);
    /* Upadte new Last Node Pointer */
    ptDeleteTpm->ptNext = NULL;
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_DeleteMiddle(T_LINKED_LIST_PARA *ptLinkedListDelete, BYTE ucDeleteNum)
* 功能说明: 在表中删除节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListDelete 删除链表指针地址
*           BYTE ucDeleteNum 删除节点号
* 输出参数: 
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_DeleteMiddle(T_LINKED_LIST_PARA *ptLinkedListDelete, BYTE ucDeleteNum)
{
    T_LINKED_LIST_PARA *ptDeleteMiddle;
    BYTE ucCount = 0;
    
    /* Linked List contain zero Node */
    if(NULL == ptLinkedListDelete)  
    {
        return SW_NONE_MEANING;
    }
    /* Delete number is error */    
    if(0 == ucDeleteNum)
    {
        return SW_NONE_MEANING;
    }
        
    /* Find The Delete Node */    
    while(NULL != ptLinkedListDelete)
    {
        ucCount = ucCount + 1;
        if(ucCount == ucDeleteNum)
        {
            break;
        }
        ptDeleteMiddle     = ptLinkedListDelete;
        ptLinkedListDelete = ptLinkedListDelete->ptNext;
    }
    /* Exceed the Linked List */
    if(ucCount != ucDeleteNum)
    {
        return SW_NONE_MEANING;
    }
    ptDeleteMiddle->ptNext = ptLinkedListDelete->ptNext;
    free(ptLinkedListDelete);
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_Count(T_LINKED_LIST_PARA *ptLinkedListCount, BYTE *o_pucLinkedListSize)
* 功能说明: 链表节点计数
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListDelete 链表头指针地址
* 输出参数: BYTE *o_pucLinkedListSize 链表长度
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_Count(T_LINKED_LIST_PARA *ptLinkedListCount, BYTE *o_pucLinkedListSize)
{
    BYTE ucCount;
    /* Linked List contain zero Node*/
    if(NULL == ptLinkedListCount)  
    {
        ucCount = 0;
    }
    else
    {
        ucCount = 1;
        while(NULL != ptLinkedListCount->ptNext)
        {
            ucCount = ucCount + 1;
            ptLinkedListCount = ptLinkedListCount->ptNext;
        }
    }
    (*o_pucLinkedListSize) = ucCount;

    return SW_OK;
}

/******************************************************************************
* 函数名称: T_LINKED_LIST_PARA* Linked_List_Find(T_LINKED_LIST_PARA *ptLinkedListFind, BYTE ucFindNum, BYTE *o_pucData1, BYTE *o_pucData2)
* 功能说明: 在表中查找节点，返回节点的地址与数据
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListFind 查找链表指针地址
*           BYTE ucFindNum 查找节点号
* 输出参数: BYTE *o_pucData1 链表数据1
*           BYTE *o_pucData2 链表数据2
* 返 回 值: 查找节点的地址 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
T_LINKED_LIST_PARA* Linked_List_Find(T_LINKED_LIST_PARA *ptLinkedListFind, BYTE ucFindNum, BYTE *o_pucData1, BYTE *o_pucData2)
{
    BYTE ucCount = 0;
    /* Linked List contain zero Node */
    if(NULL == ptLinkedListFind)  
    {
        return NULL;
    }
    /* Find number is error */
    if(0 == ucFindNum)
    {
        return NULL;
    }
    
    /* Find The Node */    
    while(NULL != ptLinkedListFind)
    {
        ucCount = ucCount + 1;
        if(ucCount == ucFindNum)
        {
            break;
        }
        ptLinkedListFind = ptLinkedListFind->ptNext;
    }
    /* Exceed the Linked List */
    if(ucCount != ucFindNum)
    {
        return NULL;
    }
    (*o_pucData1) = ptLinkedListFind->ucElements1;
    (*o_pucData2) = ptLinkedListFind->ucElements2;
    
    return ptLinkedListFind;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_Exchange(T_LINKED_LIST_PARA *ptLinkedListExchange, BYTE ucExchangeNum, BYTE ucData1, BYTE ucData2)
* 功能说明: 在表中替换节点元素
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListExchange 链表指针地址
*           BYTE ucExchangeNum 替换节点号
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_Exchange(T_LINKED_LIST_PARA *ptLinkedListExchange, BYTE ucExchangeNum, BYTE ucData1, BYTE ucData2)
{
    T_LINKED_LIST_PARA *ptExchange;
    BYTE ucTpm1,ucTpm2;

    /* Linked List contain zero Node */
    if(NULL == ptLinkedListExchange)  
    {
        return SW_NONE_MEANING;
    }
    /* Find number is error */
    if(0 == ucExchangeNum)
    {
        return SW_NONE_MEANING;
    }

    ptExchange = Linked_List_Find(ptLinkedListExchange, ucExchangeNum, &ucTpm1, &ucTpm2);
    ptExchange->ucElements1 = ucData1;
    ptExchange->ucElements2 = ucData2;

    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_Process()
* 功能说明: 链表的应用
* 输入参数: 无
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_Process()
{
    T_LINKED_LIST_PARA *pNode,*pNodeFind;
    static BYTE ucSize = 0;
    BYTE ucDataTpm1, ucDataTpm2;
    
    Linked_List_Init(&pNode);
    pNode = Linked_List_Create(pNode,5,6);
    Linked_List_InsertHead(&pNode,3,4);
    Linked_List_InsertHead(&pNode,1,2);
    Linked_List_InsertLast(pNode,7,8);
    Linked_List_InsertLast(pNode,9,10);
    Linked_List_InsertMiddle(pNode,3,11,22);
    Linked_List_InsertMiddle(pNode,5,33,44);
    Linked_List_Count(pNode,&ucSize);
    Linked_List_Exchange(pNode,3,0,0); 
    Linked_List_Exchange(pNode,5,0,0);     
    Linked_List_DeleteMiddle(pNode,5);
    Linked_List_DeleteMiddle(pNode,3);
    Linked_List_DeleteHead(pNode);    
    Linked_List_DeleteLast(pNode);       
    return SW_OK;
}

/* End of file */
