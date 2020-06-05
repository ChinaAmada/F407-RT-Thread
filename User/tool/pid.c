

#include "pid.h"

POSpid  PID_Incubate;
POSpid  PID_Reagent;
POSpid  PID_SysLiquid;
POSpid  PID_TrigLiquid;
POSpid  PID_MagClean;
POSpid  PID_Env;
POSpid  PID_Scan_Window;

void PID_Init(void)
{
	/*incubate*/
	PID_DeInit(&PID_Incubate);
	PID_Incubate.SetVal			=39.65;
	PID_Incubate.Kp				=10000;
	PID_Incubate.Ki				=0;
	PID_Incubate.Kd				=0;
	PID_Incubate.Umax			=8400;	//TIM 
	PID_Incubate.Umin			=0;		//TIM
	
	/*PID_Reagent*/
	PID_DeInit(&PID_Reagent);
	PID_Reagent.SetVal			=2.5;;
	PID_Reagent.Kp				=25000;
	PID_Reagent.Ki				=0;
	PID_Reagent.Kd				=0;
	PID_Reagent.Umax			=0;//8400;	//TIM 
	PID_Reagent.Umin			=-8400;		//TIM
	
	/*PID_SysLiquid*/
	PID_DeInit(&PID_SysLiquid);
	PID_SysLiquid.SetVal			=37.0;
	PID_SysLiquid.Kp				=10000;
	PID_SysLiquid.Ki				=0;
	PID_SysLiquid.Kd				=0;
	PID_SysLiquid.Umax				=8400;	//TIM 
	PID_SysLiquid.Umin				=0;		//TIM
	
	/*PID_TrigLiquid*/
	PID_DeInit(&PID_TrigLiquid);
	PID_TrigLiquid.SetVal			=37.0;
	PID_TrigLiquid.Kp				=10000;
	PID_TrigLiquid.Ki				=0;
	PID_TrigLiquid.Kd				=0;
	PID_TrigLiquid.Umax				=8400;	//TIM 
	PID_TrigLiquid.Umin				=0;		//TIM
	
	/*PID_MagClean*/
	PID_DeInit(&PID_MagClean);
	PID_MagClean.SetVal			=37.0;
	PID_MagClean.Kp				=10000;
	PID_MagClean.Ki				=0;
	PID_MagClean.Kd				=0;
	PID_MagClean.Umax			=8400;	//TIM 
	PID_MagClean.Umin			=0;		//TIM
	
	PID_DeInit(&PID_Env);
	PID_DeInit(&PID_Scan_Window);
}


void PID_DeInit(POSpid* PIDx)
{
	PIDx->SetVal=0;
	PIDx->ActualVal=0;
	PIDx->err=0;
	PIDx->err_last=0;
	PIDx->err_last_last=0;
	PIDx->Kp=0;
	PIDx->Ki=0;
	PIDx->Kd=0;
	PIDx->OutVal=0;
	PIDx->integral=0;
	PIDx->Umax=0;
	PIDx->Umin=0;
	
}

/*位置式PID*/
float PostionPIDCalc(POSpid *ppid)
{

	ppid->err=ppid->SetVal-ppid->ActualVal;
	ppid->integral+=ppid->err;
	

	ppid->OutVal=ppid->Kp*ppid->err+ppid->Ki*ppid->integral+ppid->Kd*(ppid->err-ppid->err_last);
	ppid->err_last=ppid->err;

	ppid->OutVal=(ppid->OutVal>ppid->Umax)?ppid->Umax:ppid->OutVal;
	ppid->OutVal=(ppid->OutVal<ppid->Umin)?ppid->Umin:ppid->OutVal;
	return ppid->OutVal;
}



/*增量式PID*/
float IncrementalPIDCalc(POSpid *Sptr, float actual_val)
{		
	Sptr->err =Sptr->SetVal - actual_val;
 
	Sptr->OutVal = Sptr->Kp * (Sptr->err - Sptr->err_last) + Sptr->Ki * Sptr->err + Sptr->Kd*(Sptr->err - 2*Sptr->err_last + Sptr->err_last_last); //(?1-2)
	
	Sptr->err_last_last = Sptr->err_last;
	Sptr->err_last = Sptr->err;
	
	Sptr->OutVal=(Sptr->OutVal>Sptr->Umax)?Sptr->Umax:Sptr->OutVal;
	Sptr->OutVal=(Sptr->OutVal<Sptr->Umin)?Sptr->Umin:Sptr->OutVal;
	return (Sptr->OutVal);
}

///////////////////////////////////////////////////////////////////////////////////////

