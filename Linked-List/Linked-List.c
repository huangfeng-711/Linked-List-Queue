/******************************************************************************
* 文件名称：Linked_List.c
* 文件标识：无
* 内容摘要：KNX产品链表相关处理
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
#include "pub.h"
#include "sw_common.h"
#include "boardctrl.h"
#include "hardware.h"
#include "KnxFlash.h"
#include "KnxAl.h"
#include "App_Intern1.h"
#include "Api.h"
#include "Application.h"
#include "app_common.h" 
#include "Linked_List.h"

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
* 函数名称: T_LINKED_LIST_PARA* Linked_List_Create(T_LINKED_LIST_PARA *ptLinkedListHead, BYTE ucData1, BYTE ucData2)
* 功能说明: 创建链表
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListHead 链表头指针
*           BYTE ucData1 链表数据1
*           BYTE ucData2 链表数据2
* 输出参数: 无
* 返 回 值: 头指针地址
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
T_LINKED_LIST_PARA* Linked_List_Create(T_LINKED_LIST_PARA *ptLinkedListHead, BYTE ucData1, BYTE ucData2)
{
    T_LINKED_LIST_PARA *ptLinkedListCreat;

    /* Alloc Linked List Date Struct */
    ptLinkedListCreat = (T_LINKED_LIST_PARA *)malloc(sizeof(T_LINKED_LIST_PARA));
    /* If malloc is failed, then return */
    if(NULL == ptLinkedListCreat)
    {   
        return;
    }
    
    /* The Linked List contain One Node */
    ptLinkedListHead               = ptLinkedListCreat;
    ptLinkedListCreat->ucElements1 = ucData1;
    ptLinkedListCreat->ucElements2 = ucData2;    
    ptLinkedListCreat->ptNext      = NULL;
    return ptLinkedListHead;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **ptLinkedListInsert, BYTE ucData1, BYTE ucData2)
* 功能说明: 在表头添加节点
* 输入参数: BYTE ucData1 链表数据1
*           BYTE ucData2 链表数据2
* 输出参数: T_LINKED_LIST_PARA **ptLinkedListInsert 链表头指针地址
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **o_ptLinkedListInsert, BYTE ucData1, BYTE ucData2)
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
    ptInsertHead->ucElements1 = ucData1;
    ptInsertHead->ucElements2 = ucData2;    
    /* Linked to the behind Node */
    ptInsertHead->ptNext      = (*o_ptLinkedListInsert);
    /* Upadte new Head Pointer */
    (*o_ptLinkedListInsert)   = ptInsertHead;
    return SW_OK;
}

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertLast(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucData1, BYTE ucData2)
* 功能说明: 在表尾添加节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListInsert 链表最后一个节点的头指针
*           BYTE ucData1 链表数据1
*           BYTE ucData2 链表数据2
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_InsertLast(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucData1, BYTE ucData2)
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
    ptInsertLast->ucElements1  = ucData1;
    ptInsertLast->ucElements2  = ucData2;    
    ptInsertLast->ptNext       = NULL;
    
    /* Find The Laste Node */    
    while(NULL != ptLinkedListInsert->ptNext)
    {
        ptLinkedListInsert     = ptLinkedListInsert->ptNext;
    }
    /* Linked to the Last Node */
    ptLinkedListInsert->ptNext = ptInsertLast;
    return SW_OK;
}
