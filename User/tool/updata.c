#include <stdio.h>
#include <stdlib.h>
#include "updata.h"





char Check_Sum(char* data,int len)
{
	int i;
	char sum=0;

	for(i=0;i<len;i++)
		sum += data[i];

	return sum;
}

int sum_check(char* data,int len,char sum)
{
	int i;
	char cal_sum=0;

	for(i=0;i<len;i++)
		cal_sum += data[i];

	if(cal_sum==sum)		
		return 1;
	else
		return -1;
}




int Check_Ack(char* buff,int len)
{
	if(len!=sizeof(Ctrl_Data)||buff[0]!=0x4c||buff[1]!=0x50)
		return -1;
	if(sum_check(buff+2,len-5,buff[len-3])<0)
		return -2;
	return 1;
}



int Make_Ack_Data(Ack_Data* sdata,char mod_addr,char cmd,char pack_type,unsigned int para1)
{


	sdata->head_H	=	HEAD_HIGH;
	sdata->head_L	=	HEAD_LOW;
	sdata->mod_addr	=	mod_addr;
	sdata->cmd		=	cmd;
	sdata->pack_type	=	pack_type;
	
	sdata->data[0]		=	para1&0xff;//htonl(para1)&0xff;
	sdata->data[1]		=	(para1&0xff00)>>8;//(htonl(para1)&0xff00)>>8;
	sdata->data[2]		=	(para1&0xff0000)>>16;//(htonl(para1)&0xff0000)>>16;
	sdata->data[3]		=	(para1&0xff000000)>>24;//(htonl(para1)&0xff000000)>>24;
	
	sdata->tmp[0]			=	0;
	sdata->tmp[1]			=	0;
	sdata->tmp[2]			=	0;
	sdata->tmp[3]			=	0;
	sdata->sum		=	Check_Sum(((char*)sdata)+2,(sizeof(Ack_Data)-5));
	sdata->tail_H		=	TAIL_HIGH;
	sdata->tail_L		=	TAIL_LOW;

	return 1;
}






/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

