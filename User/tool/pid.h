


#ifndef _PID_H
#define _PID_H


#define	SET_PID_CHANNEL_INCUBATE		1
#define	SET_PID_CHANNEL_REAGENT			2
#define	SET_PID_CHANNEL_SYSLIQUID		3
#define	SET_PID_CHANNEL_TRIGLIQUID		4
#define	SET_PID_CHANNEL_MAGCLEAN		5

typedef struct _POSpid
{
	float SetVal;   		//Ŀ��ֵ
	float ActualVal;		//��ǰֵ
	float err;              //ƫ��ֵ
	float err_last;         //�ϴ�ƫ��ֵ
	float err_last_last; 	//���ϴ�ƫ��
	float Kp,Ki,Kd;         //����ϵ��,����ϵ��,΢��ϵ��
	float OutVal;          	//������ִ�еı���
	float integral;         //����ֵ
	float Umax;				//������ֵ
	float Umin;				//�����Сֵ

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
