


#ifndef _PID_H
#define _PID_H


#define	SET_PID_CHANNEL_INCUBATE		1
#define	SET_PID_CHANNEL_REAGENT			2
#define	SET_PID_CHANNEL_SYSLIQUID		3
#define	SET_PID_CHANNEL_TRIGLIQUID		4
#define	SET_PID_CHANNEL_MAGCLEAN		5

typedef struct _POSpid
{
	float SetVal;   		//目标值
	float ActualVal;		//当前值
	float err;              //偏差值
	float err_last;         //上次偏差值
	float err_last_last; 	//上上次偏差
	float Kp,Ki,Kd;         //比例系数,积分系数,微分系数
	float OutVal;          	//控制器执行的变量
	float integral;         //积分值
	float Umax;				//输出最大值
	float Umin;				//输出最小值

}POSpid;


extern POSpid  PID_Incubate;
extern POSpid  PID_Reagent;
extern POSpid  PID_SysLiquid;
extern POSpid  PID_TrigLiquid;
extern POSpid  PID_MagClean;
extern POSpid  PID_Env;
extern POSpid  PID_Scan_Window;

void PID_DeInit(POSpid* PIDx);
void PID_Init(void);
float PostionPIDCalc(POSpid *ppid);
float IncrementalPIDCalc(POSpid *Sptr, float actual_val);
#endif
