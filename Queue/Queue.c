/******************************************************************************
* 文件名称：Queue.c
* 文件标识：无
* 内容摘要：队列相关处理
* 其他说明：
* 当前版本：V1.00
* 作    者：**
* 完成日期：2017年1月9日
*    
* 修改记录：1
* 修改日期：2017年1月9日
* 版 本 号：V1.00
* 修 改 人：**
* 修改内容：无
******************************************************************************/

#include "type_def.h"
#include "pub.h"
#include "sw_common.h"
#include "boardctrl.h"
#include "hardware.h"
#include "App_Intern1.h"
#include "Api.h"
#include "Application.h"
#include "app_common.h" 
#include "Queue.h"

/************************ struct pointer array define ******************************/
static T_QUEUE_PARA *sg_aptQueuePara[QUEUE_CHANNEL_MAX_NO] = {NULL}; /* Parameters data struct pointer table */

/******************************************************************************
* 函数名称: BYTE Queue_Init(T_QUEUE_PARA *ptQueuePara)
* 功能说明: 队列初始化
* 输入参数: T_QUEUE_PARA *ptQueuePara  队列参数
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-01-09   V1.00      **         创建
******************************************************************************/
BYTE Queue_Init(T_QUEUE_PARA *ptQueuePara)
{
    BYTE   ucIndex;

    /* Check if it is a NULL pointer */
    if (NULL == ptQueuePara)
    {
        return SW_NONE_MEANING;
    }

    /* Check if it is a wrong channel number */
    if ((ptQueuePara->ucChnNo > QUEUE_CHANNEL_MAX_NO)||(0 == ptQueuePara->ucChnNo))
    {
        return SW_NONE_MEANING;
    }
    
    /* Get the channel number */
    ucIndex = ptQueuePara->ucChnNo - 1;
    /* Get the Queue data structure pointer */
    sg_aptQueuePara[ucIndex] = ptQueuePara;
    
    /* Allocation sapce for Queue */
    ptQueuePara->pucBase  = (BYTE *)malloc(sizeof(BYTE) * ptQueuePara->ucElements); 
    /* Init the Front and Rear of Queue */
    ptQueuePara->ucFront  = 0; 
    ptQueuePara->ucRear   = 0;  
    return SW_OK;  
}

/******************************************************************************
* 函数名称: BYTE Queue_Full(BYTE ucChnlNo)
* 功能说明: 队列是否已满
* 输入参数: BYTE     ucChnlNo     队列通道号
* 输出参数: 无
* 返 回 值: QUEUE_IS_FULL   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-01-09   V1.00      **         创建
******************************************************************************/
BYTE Queue_Full(BYTE ucChnlNo)
{
    T_QUEUE_PARA *ptQueue;

    /* Check if it is a wrong channel number */
    if ((ucChnlNo > QUEUE_CHANNEL_MAX_NO)||(0 == ucChnlNo))
    {
        return SW_NONE_MEANING;
    }

    /* Get parameter data structure pointer */
    ptQueue   =  sg_aptQueuePara[ucChnlNo - 1];

    /* If Queue is Full */
    if((ptQueue->ucRear+1) % ptQueue->ucElements == ptQueue->ucFront) 
    {
        return QUEUE_IS_FULL;  
    }
    else  
    {
        return SW_NONE_MEANING; 
    }
}

/******************************************************************************
* 函数名称: BYTE Queue_Empty(BYTE ucChnlNo)
* 功能说明: 队列是否为空
* 输入参数: BYTE     ucChnlNo     队列通道号
* 输出参数: 无
* 返 回 值: QUEUE_IS_EMPTY   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-01-09   V1.00      **         创建
******************************************************************************/
BYTE Queue_Empty(BYTE ucChnlNo)
{
    T_QUEUE_PARA *ptQueue;

    /* Check if it is a wrong channel number */
    if ((ucChnlNo > QUEUE_CHANNEL_MAX_NO)||(0 == ucChnlNo))
    {
        return SW_NONE_MEANING;
    }

    /* Get parameter data structure pointer */
    ptQueue   =  sg_aptQueuePara[ucChnlNo - 1];
    
    /* If Queue is Empty */
    if(ptQueue->ucFront == ptQueue->ucRear) 
    {
        return QUEUE_IS_EMPTY;  
    } 
    else  
    {
        return SW_NONE_MEANING; 
    }
}

/******************************************************************************
* 函数名称: BYTE Queue_In(BYTE ucChnlNo, BYTE ucValue)
* 功能说明: 队列尾结点增加数据
* 输入参数: BYTE     ucChnlNo     队列通道号
            BYTE     ucValue      进入队列的值
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-01-09   V1.00      **         创建
******************************************************************************/
BYTE Queue_In(BYTE ucChnlNo, BYTE ucValue)
{
    T_QUEUE_PARA *ptQueue;
    BYTE ucTemp;
    
    /* Check if it is a wrong channel number */
    if ((ucChnlNo > QUEUE_CHANNEL_MAX_NO)||(0 == ucChnlNo))
    {
        return SW_NONE_MEANING;
    }
    
    /* Get parameter data structure pointer */
    ptQueue   =  sg_aptQueuePara[ucChnlNo - 1];
    
    /* Call Queue Full */
    ucTemp = Queue_Full(ucChnlNo);
    /* If Queue is Full */
    if(QUEUE_IS_FULL == ucTemp)  
    {  
        return SW_NONE_MEANING;  
    }  
    else  
    {  
        /* Add new Elements */ 
        ptQueue->pucBase[ptQueue->ucRear] = ucValue;  
        /* Update new Rear number */  
        ptQueue->ucRear = (ptQueue->ucRear+1) % ptQueue->ucElements;  
        return SW_OK;  
    }
}

/******************************************************************************
* 函数名称: BYTE Queue_Out(BYTE ucChnlNo, BYTE *pucValue)
* 功能说明: 队列头结点减少数据
* 输入参数: BYTE     ucChnlNo     队列通道号
            BYTE    *pucValue     离开队列的值
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-01-09   V1.00      **         创建
******************************************************************************/
BYTE Queue_Out(BYTE ucChnlNo, BYTE *pucValue)
{
    T_QUEUE_PARA *ptQueue;
    BYTE ucTemp;
    
    /* Check if it is a wrong channel number */
    if ((ucChnlNo > QUEUE_CHANNEL_MAX_NO)||(0 == ucChnlNo))
    {
        return SW_NONE_MEANING;
    }
    
    /* Get parameter data structure pointer */
    ptQueue   =  sg_aptQueuePara[ucChnlNo - 1];
    
    /* Call Queue Empty */
    ucTemp = Queue_Empty(ucChnlNo);

    /* If Queue is Empty */
    if(QUEUE_IS_EMPTY == ucTemp)  
    {  
        return SW_NONE_MEANING;  
    }   
    else  
    {  
        /* Delect the front Elements */
        *pucValue = ptQueue->pucBase[ptQueue->ucFront];  
        /* Update new Front number */  
        ptQueue->ucFront = (ptQueue->ucFront+1) % ptQueue->ucElements;  
        return SW_OK;  
    } 
}

/* End of file */
