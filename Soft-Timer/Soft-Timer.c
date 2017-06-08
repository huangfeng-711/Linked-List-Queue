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

static T_LINKED_LIST_PARA  *sg_aptSoftTimer = {NULL};
extern WORD16 wCount;
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
    Linked_List_Init(&sg_aptSoftTimer);
    sg_aptSoftTimer = Linked_List_Create(sg_aptSoftTimer,0,6,0,Board_PrgmLed_Off1);
    Linked_List_InsertHead(&sg_aptSoftTimer,0,3,5,Board_PrgmLed_On1);
    Linked_List_InsertLast(sg_aptSoftTimer,0,12,2,Linked_List_Process);
    Linked_List_InsertMiddle(sg_aptSoftTimer,3,0,9,1,Linked_List_Process);
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
    BYTE i;
    static BYTE ucExecuteFlag, ucTimeFlag, ucUpdateNodeFlg;
    static BYTE ucCountRcd[4], ucNodeNum = 4, ucCycleTime = 4;
    T_LINKED_LIST_PARA  *sg_aptSoftTimerFunc;
    T_LINKED_LIST_PARA  *sg_aptSoftTimerPara;
    
    sg_aptSoftTimerFunc = sg_aptSoftTimer;
    for(i = 0; i < 4; i++)
    {
        sg_aptSoftTimerFunc->ucElements1 = wCount / 1000;
        if(0 == sg_aptSoftTimerFunc->ucCount)
        {
            ucCountRcd[i] = ORIGINAL_COUNT_ZERO;
        }
        else
        {
            ucCountRcd[i] = ORIGINAL_COUNT_NOT_ZERO;
        }
        sg_aptSoftTimerFunc = sg_aptSoftTimerFunc->ptNext;
    }
        while(1)
    {
        if(NODE_IS_UPDATE == ucUpdateNodeFlg)
        {
            ucExecuteFlag   = EXECUTE_FUNC;
            ucUpdateNodeFlg = NODE_IS_NOT_UPDATE;
        }
        sg_aptSoftTimerFunc = sg_aptSoftTimer;
        for(i = 0; i < ucCycleTime; i++)
        {
            if(wCount < sg_aptSoftTimerFunc->ucElements1)
            {
                if(((wCount + 65536)/1000 - sg_aptSoftTimerFunc->ucElements1) >= sg_aptSoftTimerFunc->ucElements2)
                {
                    ucTimeFlag = TIME_IS_UP;
                }/* else do nothing */
            }
            else if((wCount/1000 - sg_aptSoftTimerFunc->ucElements1) >= sg_aptSoftTimerFunc->ucElements2)
            {
                    ucTimeFlag = TIME_IS_UP;
            }
            else
            {
                    ucTimeFlag = TIME_IS_NOT_UP;
            }
                        if(TIME_IS_UP == ucTimeFlag)
            {
                if(sg_aptSoftTimerFunc->ucCount != 0)
                {
                    ucExecuteFlag = EXECUTE_FUNC;
                    sg_aptSoftTimerFunc->ucCount--;
                }
                else
                {
                    if(ORIGINAL_COUNT_ZERO == ucCountRcd[i])
                    {
                        ucExecuteFlag = EXECUTE_FUNC;
                    }
                                        else
                    {
                        ucExecuteFlag = NOT_EXECUTE_FUNC;
                        if(0 == i)
                        {
                            Linked_List_DeleteHead(&sg_aptSoftTimerFunc);
                        }
                        else if(ucNodeNum == (i + 1))
                        {
                            Linked_List_DeleteLast(sg_aptSoftTimerFunc);
                        }
                        else
                        {
                            Linked_List_DeleteMiddle(sg_aptSoftTimerFunc, i+1);
                        }
                        ucNodeNum--;
                    }
                }
                                if(EXECUTE_FUNC == ucExecuteFlag)
                {
                    sg_aptSoftTimerFunc->pfSoftTimerFunc();
                    sg_aptSoftTimerFunc->ucElements1 = wCount / 1000;
                }
            }
            sg_aptSoftTimerFunc = sg_aptSoftTimerFunc->ptNext;
            if(wCount >= 65500)
            {
                wCount = 0;
            }
        }
        ucCycleTime = ucNodeNum;
                for(i = 0; i < ucNodeNum; i++)
        {
            if((ORIGINAL_COUNT_NOT_ZERO == ucCountRcd[i]) && (0 == sg_aptSoftTimerFunc->ucCount))
            {
                
            }
        }
    }
    return SW_OK;  
}
