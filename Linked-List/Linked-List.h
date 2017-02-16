/******************************************************************************
* 文件名称：Linked_List.h
* 文件标识：无
* 内容摘要：本文件为链表有关操作的头文件。
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

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                            链表相关参数宏定义                              */
/******************************************************************************/
#define LINKED_LIST_IS_NOT_FULL_OR_EMPTY     (1)     /* 链表有数据但不满 */
#define LINKED_LIST_IS_FULL                  (2)     /* 链表为满的状态   */
#define LINKED_LIST_IS_EMPTY                 (3)     /* 链表为空的状态   */

#define LINKED_LIST_INSERT_HEAD              (1)     /* 链表插入表头     */
#define LINKED_LIST_CREATE                   (2)     /* 链表新建         */

/******************************************************************************/
/*                              链表结构体声明                                */
/******************************************************************************/
/****************************************************
* 结 构 名：T_QUEUE_PARA 
* 描    述：队列地址与数据的数据结构
* 参    数：BYTE    ucElements1             链表元素1
            BYTE    ucElements2             链表元素2               
            T_LINKED_LIST_PARA   *ptNext;   下个节点地址
* 修改记录：
* 2017-01-09   **   新增结构；
****************************************************/
typedef struct
{
    BYTE    ucElements1;                   /* 链表元素1      */ 
    BYTE    ucElements2;                   /* 链表元素2      */
    T_LINKED_LIST_PARA   *ptNext;          /* 下个节点地址   */
}T_LINKED_LIST_PARA; 

/******************************************************************************/
/*                             链表相关函数声明                               */
/******************************************************************************/
/******************************************************************************
* 函数名称: BYTE Linked_List_Init(T_LINKED_LIST_PARA **ptLinkedListInit)
* 功能说明: 链表初始化
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListPara  链表参数
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Linked_List_Init(T_LINKED_LIST_PARA **ptLinkedListInit);

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
T_LINKED_LIST_PARA* Linked_List_Create(T_LINKED_LIST_PARA *ptLinkedListHead, BYTE ucData1, BYTE ucData2);

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **ptLinkedListInsert, BYTE ucData1, BYTE ucData2)
* 功能说明: 在表头添加节点
* 输入参数: T_LINKED_LIST_PARA **ptLinkedListInsert 链表头指针
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
BYTE Linked_List_InsertHead(T_LINKED_LIST_PARA **ptLinkedListInsert, BYTE ucData1, BYTE ucData2);

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
BYTE Linked_List_InsertLast(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucData1, BYTE ucData2);

/******************************************************************************
* 函数名称: BYTE Linked_List_InsertMiddle(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucInsertNum, BYTE ucData1, BYTE ucData2)
* 功能说明: 在表中添加节点
* 输入参数: T_LINKED_LIST_PARA *ptLinkedListInsert 链表插入节点的头指针
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
BYTE Linked_List_InsertMiddle(T_LINKED_LIST_PARA *ptLinkedListInsert, BYTE ucInsertNum, BYTE ucData1, BYTE ucData2);


#ifdef __cplusplus
}
#endif

#endif /* _LINKED_LIST_H_ */

