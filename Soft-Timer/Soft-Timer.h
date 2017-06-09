/******************************************************************************
* 文件名称：soft_timer.h
* 文件标识：无
* 内容摘要：本文件为应用链表创建软件定时器有关操作的头文件。
* 其他说明：
* 当前版本：V1.00
* 作    者：**
* 完成日期：2017年4月14日
*    
* 修改记录：1
* 修改日期：2017年4月14日
* 版 本 号：V1.00
* 修 改 人：**
* 修改内容：无
******************************************************************************/

#ifndef _SOFT_TIMER_H_
#define _SOFT_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                         软件定时器相关参数宏定义                           */
/******************************************************************************/
#define EXECUTE_FUNC                   (0)      /* 执行功能函数       */
#define NOT_EXECUTE_FUNC               (1)      /* 不执行功能函数     */

#define TIME_IS_UP                     (0)      /* 延时时间到         */
#define TIME_IS_NOT_UP                 (1)      /* 延时时间未到       */

#define DELETE_NULL_NODE               (0)      /* 不删除结点         */
#define DELETE_HEAD_NODE               (1)      /* 删除头结点         */
#define DELETE_MIDDLE_NODE             (2)      /* 删除中间结点       */
#define DELETE_LAST_NODE               (3)      /* 删除尾结点         */

#define NODE_IS_UPDATE                 (0)      /* 节点有更新         */
#define NODE_IS_NOT_UPDATE             (1)      /* 节点不更新         */

/******************************************************************************/
/*                             链表相关函数声明                               */
/******************************************************************************/
/******************************************************************************
* 函数名称: Soft_timer_Init(void)
* 功能说明: 软件定时器初始化
* 输入参数: 无
* 输出参数: 无
* 返 回 值: SW_OK   
*          SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-04-14   V1.00      **         创建
******************************************************************************/
BYTE Soft_timer_Init(void);

/******************************************************************************
* 函数名称: Soft_timer_Process(void)
* 功能说明: 软件定时器执行
* 输入参数: 无
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-04-14   V1.00      **         创建
******************************************************************************/
BYTE Soft_timer_Process(void);

#ifdef __cplusplus
}
#endif

#endif /* _SOFT_TIMER_H_ */
