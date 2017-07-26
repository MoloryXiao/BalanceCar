/*
* Copyright (c) 2017, 电子科技大学中山学院
* ALL rights reserved
*
*文件名称: Menu.cpp
*文本标识：
*摘    要：使用OLED显示屏进入调试状态，对相关参数进行调整。
*          提供一二级菜单。
*
*当前版本：
*作    者：萧沐磊
*完成日期：2017-07-10
*
*取代版本号：
*作    者：萧沐磊
*版本描述：
*
*/
#include "Menu.h"

/* 相关参数 */
extern PARAM_ROM V_P_Param;
extern PARAM_ROM V_I_Param;
extern PARAM_ROM D_P_Param;
extern PARAM_ROM D_D_Param;
extern PARAM_ROM A_P_Param;
extern PARAM_ROM A_D_Param;

/* 相关标志位 */
u8 getAngleFlag = 0;    // 角度获取的Flag
u8 expMotorFlag = 0;    // 电机测试的Flag

/* 相关菜单箭头 */
u8 checkedRowNum = 1; //初始化选中行为第一行(第0行为Title)
u8 menuPoint = 1;     //滑动窗口头指针

/* 相关选项状态 */
/* 选项选中配置 1为选中 0位不选中 默认选择第1个选项 */
u8 checkedState[9]={0,1,0,0,0,0,0,0,0};
/* 选项居中配置 1为居中 0为左对齐 */
u8 middleState[9]={1,1,1,1,1,1,1,1,1}; 
/* 调整页面参数的增量和减量 */
#define ADD_VALUE 0.1
#define MINUS_VALUE 0.1

/****************************************************************************
* 名    称：OLED_FirstPrint()
* 功    能：OLED屏初始化启动后的显示
* 入口参数：MyOLED:OLED对象
* 出口参数：无
****************************************************************************/
void OLED_FirstPrint(OLED_SPI &MyOLED)
{
  u8 i;
  //初始化显示内容
  for(i=0;i<4;i++)
  {
    MyOLED.Print_ENString(0,i*2,EN_Menu[i].content,checkedState[i],middleState[i]);
  }
}

/****************************************************************************
* 名    称：OLED_ReturnPrint()
* 功    能：从子菜单返回主菜单后的显示
* 入口参数：MyOLED:OLED对象
* 出口参数：无
****************************************************************************/
void OLED_ReturnPrint(OLED_SPI &MyOLED)
{
  u8 i,row;
  MyOLED.Clear();
  MyOLED.Print_ENString(0,0,EN_Menu[0].content,checkedState[0],middleState[0]);
  for(i=0;i<3;i++)
  {
    row=menuPoint+i;
    MyOLED.Print_ENString(0,(i+1)*2,EN_Menu[row].content,checkedState[row],middleState[row]);
  }
}

/****************************************************************************
* 名    称：AdjParamFunc()
* 功    能：调整参数的二级页面
* 入口参数：MyOLED:OLED对象 par:需要调整的参数 title:二级菜单第0行显示的Title
* 出口参数：无
****************************************************************************/
void AdjParamFunc(OLED_SPI &MyOLED,PARAM_ROM &par,const char* title)
{
  u8  outFlag=0;
  u16 pointCount;

  float maxValue = par.range;
  float tempValue = par.param;

  pointCount = 48*tempValue/maxValue;

  MyOLED.Adjust_Page(title,tempValue,maxValue);
  do
  {
    if(UpKeyState() && tempValue+ADD_VALUE<=maxValue)
    {
      tempValue += ADD_VALUE;
      pointCount = 48*tempValue/maxValue;
      MyOLED.Print_ALine(16,3,pointCount,1);
      MyOLED.Print_FloatNum(0,6,tempValue);
    }
    if(DownKeyState() && tempValue-MINUS_VALUE>=0)
    {
      tempValue -= MINUS_VALUE;
      pointCount = 48*tempValue/maxValue;
      MyOLED.Print_ALine(16+2*pointCount,3,48-pointCount,0);
      MyOLED.Print_FloatNum(0,6,tempValue);
    }
    if(EnterKeyState())
    {
      if(tempValue != par.param)
      {
        par.param = tempValue;
        WriteShort(par.addr,par.param*100);
      }
      outFlag=1;
    }
    if(CancelKeyState()) outFlag = 1;
  }while(!outFlag);
}

/****************************************************************************
* 名    称：ComfrimFunc()
* 功    能：请求确认的二级页面
* 入口参数：MyOLED:OLED对象 flag:确认后置1
*           title:二级菜单第0行显示的Title print:进入状态后的显示内容
* 出口参数：无
****************************************************************************/
void ComfrimFunc(OLED_SPI &MyOLED,u8 &flag,const char *title,const char *print)
{
  u8 result;
  MyOLED.Comfirm_Page(title,"SURE TO ENTER?"); 
  if(EnterOrCancel())
  {
    MyOLED.ENStr_Page(print);
    flag = 1;
  }else
    OLED_ReturnPrint(MyOLED);
}

/****************************************************************************
* 名    称：SecondLevelMenu()
* 功    能：二级菜单
* 入口参数：MyOLED:OLED对象
* 出口参数：无
****************************************************************************/
void SecondLevelMenu(OLED_SPI &MyOLED)
{
  u8 result,maxValue=0,pointCount=0,tempValue,numLen;
  u8 outFlag=0;
  switch(checkedRowNum)   //根据选项不同 进入不同的界面
  {
    // MENU1:START EX
    case 1:         // 启动测试
      ComfrimFunc(MyOLED,expMotorFlag,EN_Menu[checkedRowNum].content,"EXP_ING...");
    break;

    // MENU2:Get The Angle
    case 2:
      ComfrimFunc(MyOLED,getAngleFlag,EN_Menu[checkedRowNum].content,"GET_ING...");
    break;

    // MENU3:Vel P Value
    case 3:
      AdjParamFunc(MyOLED,V_P_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;

    // MENU4:Vel I Value
    case 4:
      AdjParamFunc(MyOLED,V_I_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;

    // MENU5:Dir P Value
    case 5:
      AdjParamFunc(MyOLED,D_P_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;

    // MENU6:Dir D Value
    case 6:
      AdjParamFunc(MyOLED,D_D_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;

    // MENU7:Angle P Value
    case 7:
      AdjParamFunc(MyOLED,A_P_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;

    // MENU8:Angle D Value
    case 8:
      AdjParamFunc(MyOLED,A_D_Param,EN_Menu[checkedRowNum].content);
      OLED_ReturnPrint(MyOLED);
    break;
  }
}

/****************************************************************************
* 名    称：FirstLevelMenu()
* 功    能：一级菜单 滑动窗口式切换选项
* 入口参数：MyOLED:OLED对象
* 出口参数：无
****************************************************************************/
void FirstLevelMenu(OLED_SPI &MyOLED)
{
  u8 i,j;
  u8 selectRow,cancelRow;  //选中行,取消选中行
  if(DownKeyState() && checkedRowNum+1<=MAXROW)
  {
    checkedState[checkedRowNum]=0;  //原来项取消选中
    checkedRowNum++;
    checkedState[checkedRowNum]=1;  //新项选中

    if(menuPoint+2<checkedRowNum)
    {
      menuPoint++;
      for(i=menuPoint,j=1;i<menuPoint+3,j<4;i++,j++)
      {
        if(j!=3)  //减少不必要的刷新
          MyOLED.Dele_Row(j);
        MyOLED.Print_ENString(0,j*2,EN_Menu[i].content,checkedState[i],middleState[i]);
      }
    }else   // 选项窗口进行滑动
    {
        cancelRow=checkedRowNum-menuPoint;
        i=checkedRowNum-1;
        MyOLED.Dele_Row(cancelRow);
        MyOLED.Print_ENString(0,cancelRow*2,EN_Menu[i].content,checkedState[i],middleState[i]);
        
        selectRow=checkedRowNum-menuPoint+1;
        i=checkedRowNum;
        MyOLED.Print_ENString(0,selectRow*2,EN_Menu[i].content,checkedState[i],middleState[i]);
    }
  }

  if(UpKeyState() && checkedRowNum-1>=MINROW)
  {
    checkedState[checkedRowNum]=0;  //原来项取消选中
    checkedRowNum--;
    checkedState[checkedRowNum]=1;  //新项选中

    if(menuPoint>checkedRowNum) 
    {
      menuPoint--;
      for(i=menuPoint,j=1;i<menuPoint+3,j<4;i++,j++)
      {
        if(j!=1)  //减少不必要的刷新
          MyOLED.Dele_Row(j);
        MyOLED.Print_ENString(0,j*2,EN_Menu[i].content,checkedState[i],middleState[i]);
      }
    }else  // 选项窗口进行滑动
    {
        selectRow=checkedRowNum-menuPoint+1;
        i=checkedRowNum;
        MyOLED.Print_ENString(0,selectRow*2,EN_Menu[i].content,checkedState[i],middleState[i]);
        
        cancelRow=checkedRowNum-menuPoint+2;
        i=checkedRowNum+1;
        MyOLED.Dele_Row(cancelRow);
        MyOLED.Print_ENString(0,cancelRow*2,EN_Menu[i].content,checkedState[i],middleState[i]);
    }
  }

  if(EnterKeyState())   // 进入二级菜单
  {
    SecondLevelMenu(MyOLED);
  }
}