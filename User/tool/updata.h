
#ifndef _UPDATA_H
#define _UPDATA_H


#define		READ_FLAG		1
#define		WRITE_FLAG		0


#define		HEAD_HIGH		0x4C
#define		HEAD_LOW		0x50
#define		TAIL_HIGH		0x0D
#define		TAIL_LOW		0x0A


#define		CMD_TYPE_TEST				0x01		/*  ? ? , ? ?  */ 
#define		CMD_TYPE_COMP				0x02		/*  ? ?  */ 
#define		CMD_TYPE_WORK				0x03		/*  ? ? ? ?  */  


#define		SLAVE_TYPE_ACK				0x10
#define		SLAVE_TYPE_SUCCESS			0x11	
#define		SLAVE_TYPE_FAIL				0x12
#define		SLAVE_TYPE_ALERM			0x13
#define		SLAVE_TYPE_SIGNAL			0x14
#define		SLAVE_TYPE_START			0x15
#define		SLAVE_TYPE_DETEC_VAL		0x16



#define	CMD_COLD_HOT_GET_TMP	0x90		
#define	CMD_COLD_HOT_SET_TMP	0x91		


#define		WAIT_TIME_NO_DATA			1000	//us



union Comp{
	int data;		//4????
	short para[2];	//?????????????????????????????????????
};

union Ftoi{
	int i_val;
	float f_val;
};

union Ftoc{
	char c_val[4];
	float f_val;
};



typedef struct	_Ctrl_Data_L{
	char head_H;		/*  ? ?  0x4C  */
	char head_L;		/*  ? ?  0x50  */
	char mod_addr;	/*  ? ? ? ? ?  */
	char cmd;		/*  ? ? ?  */
	char para_pos;	/*  ? ? ? ? ,? ? ? ?   */
	char para_num;	/*  ? ? ? ?   */
	char para1[4] ; 	/* ? ?  1 */
	char para2[4] ;	/* ? ?  2 */
	char para3[4] ;	/* ? ?  3 */
	char para4[4] ;	/* ? ?  4 */
	char para5[4] ;	/* ? ?  5 */
	char res[2];		/* ? ?   */
	char cmd_type;	/* ? ? ? ?   */
	char sum;		/* ? ? ?   */
	char tail_H;		/* ? ?  0x0d */
	char tail_L;		/* ? ?  0x0a */
	
}Ctrl_Data;




typedef struct _Ack_Data{
	char head_H;		/*  ? ?  0x4C  */
	char head_L;		/*  ? ?  0x50  */
	//char master_addr;		/*  ? ? ? ? ?  */
	char mod_addr;		/*  ? ? ? ? ?  */
	char cmd;			/*  ? ? ?  */
	char pack_type;		/*  ? ? ?  */
	char data[4];			/*  ? ?  */
	char tmp[4];			/* ? ?  */
	char sum;			/*  ? ? ?  */
	char tail_H;			/*  ? ? 0x0d */
	char tail_L;			/*  ? ? 0x0a */
}Ack_Data;   




char Check_Sum(char* data,int len);
int sum_check(char* data,int len,char sum);
int Check_Ack(char* buff,int len);
int Make_Ack_Data(Ack_Data* sdata,char mod_addr,char cmd,char pack_type,unsigned int para1);

#endif
