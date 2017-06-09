/******************************************************************************
* 文件名称：Soft_Timer.c
* 文件标识：无
* 内容摘要：定时器相关处理
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

static T_LINKED_LIST_PARA  *sg_ptSoftTimer = {NULL};
static BYTE   sg_ucNodeNum = 0, sg_ucCycleTime = 0;
extern WORD16 g_wCount;
/******************************************************************************
* 函数名称: Soft_timer_Init(void)
* 功能说明: 软件定时器初始化
* 输入参数: 无
* 输出参数: 无
* 返 回 值: SW_OK   
*           SW_NONE_MEANING 
* 其他说明: 无
* 修改日期     版本号     修改人      修改内容
* ------------------------------------------------------------------------
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Soft_timer_Init(void)
{ 
    /* Init the address of Head point */
    Linked_List_Init(&sg_ptSoftTimer);
    sg_ptSoftTimer = Linked_List_Create(sg_ptSoftTimer,0,6,0,Board_PrgmLed_Off1);
    Linked_List_InsertHead(&sg_ptSoftTimer,0,3,5,Board_PrgmLed_On1);
    Linked_List_InsertLast(sg_ptSoftTimer,0,12,2,Linked_List_Process);
    Linked_List_InsertMiddle(sg_ptSoftTimer,3,0,9,1,Linked_List_Process);
    Linked_List_Count(sg_ptSoftTimer,&sg_ucNodeNum);
    sg_ucCycleTime = sg_ucNodeNum;
    return SW_OK;  
}

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
* 2017-02-14   V1.00      **         创建
******************************************************************************/
BYTE Soft_timer_Process(void)
{ 
    BYTE ucCount;
    static BYTE s_ucTimeFlag, s_ucUpdateNodeFlg, s_ucDeleteFlg[4] = {0};
    static BYTE s_ucExecuteFlag = NOT_EXECUTE_FUNC;
    T_LINKED_LIST_PARA  *sg_aptSoftTimerFunc;
    
    /* Update data struct */
    sg_aptSoftTimerFunc = sg_ptSoftTimer;
    /* Update the start time */
    for(ucCount = 0; ucCount < sg_ucNodeNum; ucCount++)
    {
        sg_aptSoftTimerFunc->ucElements1 = g_wCount / 1000;
        sg_aptSoftTimerFunc = sg_aptSoftTimerFunc->ptNext;
    }
    
    while(1)
    {
        /* The Node of Linked List has Changed */
        if(NODE_IS_UPDATE == s_ucUpdateNodeFlg)
        {
            /* Update data struct */
            sg_aptSoftTimerFunc = sg_ptSoftTimer;
            /* Delete The Node of Linked List */
            for(ucCount = 0; ucCount < sg_ucCycleTime; ucCount++)
            {
                if(DELETE_HEAD_NODE == s_ucDeleteFlg[ucCount])
                {
                    Linked_List_DeleteHead(&sg_ptSoftTimer);
                }
                else if(DELETE_LAST_NODE == s_ucDeleteFlg[ucCount])
                {
                    Linked_List_DeleteLast(sg_ptSoftTimer);
                }
                else if(DELETE_MIDDLE_NODE == s_ucDeleteFlg[ucCount])
                {
                    Linked_List_DeleteMiddle(sg_ptSoftTimer, ucCount+1);
                }
                /* Update the Delete Flag */
                s_ucDeleteFlg[ucCount] = DELETE_NULL_NODE;
                sg_aptSoftTimerFunc = sg_aptSoftTimerFunc->ptNext;
            }
            s_ucUpdateNodeFlg = NODE_IS_NOT_UPDATE;
        }
        
        /* Update data struct */
        sg_aptSoftTimerFunc = sg_ptSoftTimer;
        /* Update Node Num After Delete the Node */
        sg_ucCycleTime = sg_ucNodeNum;

        /* Cycle check if it is need to run the Func */
        for(ucCount = 0; ucCount < sg_ucCycleTime; ucCount++)
        {
            /* If the time is overflow */
            if(g_wCount/1000 < sg_aptSoftTimerFunc->ucElements1)
            {
                /* if delay time is up */
                if(((g_wCount + 65536)/1000 - sg_aptSoftTimerFunc->ucElements1) >= sg_aptSoftTimerFunc->ucElements2)
                {
                    s_ucTimeFlag = TIME_IS_UP;
                }
                else
                {
                    s_ucTimeFlag = TIME_IS_NOT_UP;
                }
            }
            /* If the time is not overflow */
            else
            {
                /* if delay time is up */
                if((g_wCount/1000 - sg_aptSoftTimerFunc->ucElements1) >= sg_aptSoftTimerFunc->ucElements2)
                {
                    s_ucTimeFlag = TIME_IS_UP;
                }
                else
                {
                    s_ucTimeFlag = TIME_IS_NOT_UP;
                }
            }
            /* if delay time is up */
            if(TIME_IS_UP == s_ucTimeFlag)
            {
                /* It is need to run the function */
                if(sg_aptSoftTimerFunc->ucCount != 1)
                {
                    s_ucExecuteFlag = EXECUTE_FUNC;
                    if(sg_aptSoftTimerFunc->ucCount != 0)
                    {
                        sg_aptSoftTimerFunc->ucCount--;
                    }
                }
                /* The last time to run the function */
                else
                {
                    s_ucExecuteFlag = EXECUTE_FUNC;
                    /* Delete the Head Node */
                    if(0 == ucCount)
                    {
                       s_ucDeleteFlg[ucCount] = DELETE_HEAD_NODE;
                    }
                    /* Delete the Last Node */
                    else if(sg_ucNodeNum == (ucCount + 1))
                    {
                       s_ucDeleteFlg[ucCount] = DELETE_LAST_NODE;
                    }
                    /* Delete the Middle Node */
                    else
                    {
                       s_ucDeleteFlg[ucCount] = DELETE_MIDDLE_NODE;
                    }
                    sg_ucNodeNum--;
                    s_ucUpdateNodeFlg = NODE_IS_UPDATE;
                }
            }
            /* Run the Function and Update the Start Time */
            if(EXECUTE_FUNC == s_ucExecuteFlag)
            {
                sg_aptSoftTimerFunc->pfSoftTimerFunc();
                sg_aptSoftTimerFunc->ucElements1 = g_wCount / 1000;
                s_ucExecuteFlag = NOT_EXECUTE_FUNC;
            }
            sg_aptSoftTimerFunc = sg_aptSoftTimerFunc->ptNext;
            if(g_wCount >= 65500)
            {
                g_wCount = 0;
            }
        } 
    }
    return SW_OK; 
}
