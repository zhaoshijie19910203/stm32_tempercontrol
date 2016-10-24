#include "tftlcd.h"

u16 lcd_id;
_lcd_dev lcddev;
u16 POINT_COLOR=0x0000;	//画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色

void opt_delay(u8 i)  //延时i个时钟周期
{
	while(i--);
}

void lcd_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
	FSMC_NORSRAMTimingInitTypeDef FSMC_ReadWriteTimingStruct;
	FSMC_NORSRAMTimingInitTypeDef FSMC_WriteTimingStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);  //打开FSMC时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	
	FSMC_ReadWriteTimingStruct.FSMC_AddressSetupTime = 0x01; //地址建立时间 2个HLCK=27ns 见开发指南P268 (ADDSET+1)个HLCK周期
	FSMC_ReadWriteTimingStruct.FSMC_AddressHoldTime = 0x00; //地址保持时间 模式A未用到
	FSMC_ReadWriteTimingStruct.FSMC_DataSetupTime = 0x0f; //数据保持时间
	FSMC_ReadWriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_ReadWriteTimingStruct.FSMC_CLKDivision = 0x00; //定义CLK时钟输出信号的周期，以HCLK周期数表示
	FSMC_ReadWriteTimingStruct.FSMC_DataLatency = 0x00; //成组模式下使用
	FSMC_ReadWriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A; //访问模式A
	
	FSMC_WriteTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;
	FSMC_WriteTimingStruct.FSMC_AddressSetupTime = 0x00;
	FSMC_WriteTimingStruct.FSMC_AddressHoldTime = 0x00;
	FSMC_WriteTimingStruct.FSMC_DataSetupTime = 0x03; //4个HCLK
	FSMC_WriteTimingStruct.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_WriteTimingStruct.FSMC_CLKDivision = 0x00;
	FSMC_WriteTimingStruct.FSMC_DataLatency = 0x00;
	
	FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; //不复用数据地址
	FSMC_NORSRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //是否进行成组模式访问
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable; //？？？具体功能暂不清楚
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; //等待信号有效极性
	FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable; //仅在成组模式下有效
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; //？？？不太明白作用
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable; //允许对FSMC寄存器的写操作
	FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable; //成组模式下使用
	FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; //允许使用FSMC_BWTR寄存器，即允许读和写使用不同的时序
	FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct = &FSMC_ReadWriteTimingStruct;
	FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct = &FSMC_WriteTimingStruct;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4 , ENABLE); //使能FSMC
	
	LCD_WR_REG(0XBF);		  //RM68042 (P120) device code read 命令		   
	LCD_RD_DATA(); 			//dummy read 	 
	LCD_RD_DATA();   	    //读回0X01	 MIPI Alliance code		 应该是没什么用   
	LCD_RD_DATA(); 			//读回0XD0 			MIPI Alliance code	  	
	lcddev.id=LCD_RD_DATA();//这里读回0X68 
	lcddev.id<<=8;
	lcddev.id|=LCD_RD_DATA();//这里读回0X04
	
	//6804的初始化   各种命令详见68042数据手册的P39
	LCD_WR_REG(0X11);  //exit sleep mode
	delay_ms(20);
	LCD_WR_REG(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
	LCD_WR_DATA(0X07); 
	LCD_WR_DATA(0X42); 
	LCD_WR_DATA(0X1D); 
	LCD_WR_REG(0XD1);//VCOMH VCOM_AC amplitude setting
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X1a);
	LCD_WR_DATA(0X09); 
	LCD_WR_REG(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
	LCD_WR_DATA(0X01);
	LCD_WR_DATA(0X22);
	LCD_WR_REG(0XC0);//REV SM GS 
	LCD_WR_DATA(0X10);
	LCD_WR_DATA(0X3B);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X02);
	LCD_WR_DATA(0X11);
	
	LCD_WR_REG(0XC5);// Frame rate setting = 72HZ  when setting 0x03
	LCD_WR_DATA(0X03);
	
	LCD_WR_REG(0XC8);//Gamma setting
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X25);
	LCD_WR_DATA(0X21);
	LCD_WR_DATA(0X05);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X0a);
	LCD_WR_DATA(0X65);
	LCD_WR_DATA(0X25);
	LCD_WR_DATA(0X77);
	LCD_WR_DATA(0X50);
	LCD_WR_DATA(0X0f);
	LCD_WR_DATA(0X00);	  
						
		LCD_WR_REG(0XF8);
	LCD_WR_DATA(0X01);	  

	LCD_WR_REG(0XFE);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X02);
	
	LCD_WR_REG(0X20);//Exit invert mode

	//b7:0 从上到下 b6:0 从左到右 b5:
	LCD_WR_REG(0X36);
	LCD_WR_DATA(0X08);//b3:1 BGR像素模式   b3:0 RGB模式   	
	
	LCD_WR_REG(0X3A);
	LCD_WR_DATA(0X55);//65536 colors  16bit 
	LCD_WR_REG(0X2B);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X01);
	LCD_WR_DATA(0X3F);
	
	LCD_WR_REG(0X2A);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X00);
	LCD_WR_DATA(0X01);
	LCD_WR_DATA(0XDF);
	delay_ms(120);
	LCD_WR_REG(0X29);
	
	//6804不支持横屏显示 320*480
	lcddev.dir = 0;
	lcddev.wramcmd = 0x2c; //准备写ram指令
	lcddev.setxcmd = 0x2a;
	lcddev.setycmd = 0x2b;
	lcddev.height = 480;
	lcddev.width = 320;
	
	LCD_Scan_Dir(DFT_SCAN_DIR);	
	//点亮背光
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
	LCD_Clear(WHITE);  //用白色清屏
}

void LCD_WR_REG(u16 regval)  
{ 
	LCD_TEMP->LCD_REG=regval;
}

void LCD_WR_DATA(u16 data)
{										    	   
	LCD_TEMP->LCD_RAM=data;		 
}

u16 LCD_RD_DATA(void)
{										    	   
	return LCD_TEMP->LCD_RAM;		 
}					   

void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_TEMP->LCD_REG = LCD_Reg;			 
	LCD_TEMP->LCD_RAM = LCD_RegValue;	    		 
}	   

u16 LCD_ReadReg(u8 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);	
	delay_us(5);		  
	return LCD_RD_DATA();		
}   
//lcd写GRAM RGB_CODE:颜色值 
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD_TEMP->LCD_RAM = RGB_Code;
}
//开始写GRAMs
void LCD_WriteRAM_Prepare(void)
{
 	LCD_TEMP->LCD_REG=lcddev.wramcmd;	  
}	
//开启显示
void LCD_DisplayOn(void)
{
	LCD_WR_REG(0x29);
}
//关闭显示
void LCD_DisplayOff(void)
{
	LCD_WR_REG(0x28);
}
//设置光标位置   不是很明白
void LCD_SetCursor(u16 x, u16 y)
{
	LCD_WR_REG(lcddev.setxcmd);
	LCD_WR_DATA(x>>8);
	LCD_WR_DATA(x&0xff);
	LCD_WR_REG(lcddev.setycmd);
	LCD_WR_DATA(y>>8);
	LCD_WR_DATA(y&0xff);
}
//
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u8 dirreg=0;
	u16 temp;  
	
	switch(dir)
		{
			case L2R_U2D:
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U:
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D:
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U:
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R:
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L:
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R:
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L:
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
		regval|=0X08;//BGR 
 		regval|=0X02;//BGR and 水平翻转    if(lcddev.id==0X6804)regval|=0x02;//6804的BIT6和9341的反了	 
		LCD_WriteReg(dirreg,regval);
 		if(regval&0X20)
		{
			if(lcddev.width<lcddev.height)
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}else  
		{
			if(lcddev.width>lcddev.height)
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}  
		//放置光标
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);
}
//清屏函数
//color:清屏的填充色
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 	//得到总点数
	LCD_SetCursor(0x00,0x00);	//设置光标位置
	LCD_WriteRAM_Prepare();     //开始写入GRAM  
	for(index=0;index<totalpoint;index++)
	{
		LCD_TEMP->LCD_RAM=color;	   
	}
} 

//画点
//x,y:坐标
//color:颜色
void LCD_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	LCD_WR_DATA(color);
}

//填充以(x1,y1)和(x2,y2)两点之间的矩形区域 x1<x2 y1<y2
void LCD_SquareFill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 row,column,temp;
	row = y2 - y1 + 1;
	column = x2 - x1 + 1;
	
	LCD_SetCursor(x1,y1);
	LCD_WriteRAM_Prepare(); 
	while(row>0)
	{
		temp = column;
		while(temp>0)
		{
			LCD_DrawPoint(temp+x1-1,row+y1-1,color);
			temp--;
		}
		row--;
	}
}

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //?????? 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //?????? 
	else if(delta_x==0)incx=0;//??? 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//??? 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //????????? 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//???? 
	{  
		LCD_DrawPoint(uRow,uCol,color);//?? 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //??????????
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b,color);             //5
 		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-a,y0+b,color);             //1       
 		LCD_DrawPoint(x0-b,y0+a,color);             
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
  	LCD_DrawPoint(x0-b,y0-a,color);             //7     	         
		a++;
		//??Bresenham????     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u16 colortemp=POINT_COLOR;      			     
	//????		   
	num=num-' ';//???????
	if(!mode) //?????
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //??1206??
			else temp=asc2_1608[num][t];		 //??1608?? 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y,POINT_COLOR);	
				temp<<=1;
				y++;
				if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//????
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//????
					break;
				}
			}  	 
	    }    
	}else//????
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //??1206??
			else temp=asc2_1608[num][t];		 //??1608?? 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y,POINT_COLOR); 
				temp<<=1;
				y++;
				if(x>=lcddev.height){POINT_COLOR=colortemp;return;}//????
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//????
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n??
//???:m^n??.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//????,???0,????
//x,y :????	 
//len :?????
//size:????
//color:?? 
//num:??(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//?????
//x,y:????
//width,height:????  
//size:????
//*p:???????		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//?????????!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//??
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}

void LCD_CentShowStr(u8 *str)
{
	LCD_ShowString(60,200,200,16,16,str);
}

u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//?????,????		   
	LCD_SetCursor(x,y);	    
	if(lcddev.id==0X9341||lcddev.id==0X6804)LCD_WR_REG(0X2E);//9341/6804 ???GRAM??
	else LCD_WR_REG(R34);      		 				//??IC???GRAM??
 	if(lcddev.id==0X9320)opt_delay(2);				//FOR 9320,??2us	    
	if(LCD_TEMP->LCD_RAM)r=0;							//dummy Read	   
	opt_delay(2);	  
 	r=LCD_TEMP->LCD_RAM;  		  						//??????
 	if(lcddev.id==0X9341)//9341??2???
 	{
		opt_delay(2);	  
		b=LCD_TEMP->LCD_RAM; 
		g=r&0XFF;//??9341,???????RG??,R??,G??,??8?
		g<<=8;
	}else if(lcddev.id==0X6804)r=LCD_TEMP->LCD_RAM;//6804???????????
	if(lcddev.id==0X9325||lcddev.id==0X4535||lcddev.id==0X4531||lcddev.id==0X8989||lcddev.id==0XB505)return r;//???IC???????
	else if(lcddev.id==0X9341)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));	//ILI9341????????
	else return LCD_BGR2RGB(r);												//??IC
}	

u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1       
		LCD_DrawPoint(x0-b,y0-a,color);             //7           
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b,color);
	}
}

