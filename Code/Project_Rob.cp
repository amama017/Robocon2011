#line 1 "D:/Uni/Others/Compitions & Interships/Robocon/Robocon 2011/Base/Code/Movement of Robot/final/Project_Rob.c"
#line 86 "D:/Uni/Others/Compitions & Interships/Robocon/Robocon 2011/Base/Code/Movement of Robot/final/Project_Rob.c"
void PWM_C1(const unsigned short duty_Percent)
{



 if(duty_Percent == 100)
 {
 CCPR2L = 0b00111111;

 CCP2CON = 0b00111100;

 }
 else if(duty_Percent == 75)
 {
 CCPR2L = 0b00101111;

 CCP2CON = 0b00111100;

 }
 else if(duty_Percent == 50)
 {
 CCPR2L = 0b00011111;

 CCP2CON = 0b00111100;

 }
 else if(duty_Percent == 25)
 {
 CCPR2L = 0b00001111;

 CCP2CON = 0b00111100;

 }
 else
 {
 CCPR2L = 0b00000000;

 CCP2CON = 0b00001100;

 }
}

void PWM_C2(const unsigned short duty_Percent)
{



 if(duty_Percent == 100)
 {
 CCPR1L = 0b00111111;

 CCP1CON = 0b00111100;

 }
 else if(duty_Percent == 75)
 {
 CCPR1L = 0b00101111;

 CCP1CON = 0b00111100;

 }
 else if(duty_Percent == 50)
 {
 CCPR1L = 0b00011111;

 CCP1CON = 0b00111100;

 }
 else if(duty_Percent == 25)
 {
 CCPR1L = 0b00001111;

 CCP1CON = 0b00111100;

 }
 else
 {
 CCPR1L = 0b00000000;

 CCP1CON = 0b00001100;

 }
}

void Init_PWM()
{



 PR2 = 0b00111111;

 T2CON = 0b00000100;


 PIE1 = 0;
 PIR1 = 0;
 PIE2 = 0;
 PIR2 = 0;

 PIE1.TMR1IE = 1;
 delay_ms(100);
}

void Reset_PWM()
{



 T2CON = 0;

 TMR2 = 0;

 delay_ms(100);
 Init_PWM();

}



void Track_Line_forward(const unsigned short Lines)
{
#line 215 "D:/Uni/Others/Compitions & Interships/Robocon/Robocon 2011/Base/Code/Movement of Robot/final/Project_Rob.c"
unsigned short r_Lines = 0;
 while(r_Lines < Lines)
 {
 Reset_PWM();



 if( PORTB.f1  == 0 &&  PORTB.f2  == 0 &&  PORTB.f3  == 0)
 {
 delay_ms(50);

  PORTC.f0  = 1;
 PWM_C1(50);

  PORTC.f3  = 1;
 PWM_C2(50);

 delay_ms(100);
 while( PORTB.f1  == 0 &&  PORTB.f2  == 0 &&  PORTB.f3  == 0)
 {
 }
 }



 else if( PORTB.f2  == 1)
 {
 delay_ms(50);

  PORTC.f0  = 0;
 PWM_C1(100);

  PORTC.f3  = 0;
 PWM_C2(100);

 delay_ms(100);
 while( PORTB.f2  == 1)
 {
 }
 }



 else if( PORTB.f1  == 1 &&  PORTB.f2  == 0 &&  PORTB.f3  == 0)
 {
 delay_ms(50);

  PORTC.f0  = 0;
 PWM_C1(50);

  PORTC.f3  = 0;
 PWM_C2(100);

 delay_ms(100);
 while( PORTB.f1  == 1 &&  PORTB.f2  == 0 &&  PORTB.f3  == 0)
 {
 }
 }



 else if( PORTB.f1  == 0 &&  PORTB.f2  == 0 &&  PORTB.f3  == 1)
 {
 delay_ms(50);

  PORTC.f0  = 0;
 PWM_C1(100);

  PORTC.f3  = 0;
 PWM_C2(50);

 delay_ms(100);
 while( PORTB.f1  == 0 &&  PORTB.f2  == 0 &&  PORTB.f3  == 1)
 {
 }
 }



 else if( PORTB.f1  == 1 &&  PORTB.f2  == 1 &&  PORTB.f3  == 1)
 {
 delay_ms(200);

 if( PORTB.f1  == 1 &&  PORTB.f2  == 1 &&  PORTB.f3  == 1)
 {

 r_Lines++;
 if(r_Lines == Lines)
 {
 Reset_PWM();
 delay_ms(50);
  PORTC.f1  = 1;
  PORTC.f0  = 1;
  PORTC.f2  = 1;
  PORTC.f3  = 1;
 delay_ms(5000);

 return;
 }
 else
 {

 delay_ms(500);
 }
 }
 }
 }
}

void Rotate_Right()
{




 Init_PWM();
 PWM_C1(75);
  PORTC.f0  = 0;
 PWM_C2(25);
  PORTC.f3  = 1;


 delay_ms(1000);



 while( PORTB.f2  == 0)
 {
 }


 Reset_PWM();
 delay_ms(50);
  PORTC.f1  = 1;
  PORTC.f0  = 1;
  PORTC.f2  = 1;
  PORTC.f3  = 1;
 delay_ms(5000);
}

void Rotate_Left()
{




 Init_PWM();
 PWM_C2(75);
  PORTC.f3  = 0;
 PWM_C1(25);
  PORTC.f0  = 1;


 delay_ms(1000);



 while( PORTB.f2  == 0)
 {
 }


 Reset_PWM();
 delay_ms(50);
  PORTC.f1  = 1;
  PORTC.f0  = 1;
  PORTC.f2  = 1;
  PORTC.f3  = 1;
 delay_ms(5000);
}



void Lifter_upward()
{



 while(1)
 {

 if( PORTB.F6  == 0)
 {
 delay_ms(50);

  PORTC.F5  = 0;
  PORTC.F4  = 1;
 delay_ms(100);

 while( PORTB.F6  == 0)
 {
 }


 delay_ms(50);
  PORTC.F5  = 1;
  PORTC.F4  = 1;
 delay_ms(100);
 }

 else
 {
 delay_ms(50);

  PORTC.F5  = 1;
  PORTC.F4  = 1;
 delay_ms(100);
 }
 }
}

void Lifter_downward()
{



 while(1)
 {

 if( PORTB.F7  == 0)
 {
 delay_ms(50);

  PORTC.F5  = 1;
  PORTC.F4  = 0;
 delay_ms(100);

 while( PORTB.F7  == 0)
 {
 }


 delay_ms(50);
  PORTC.F5  = 1;
  PORTC.F4  = 1;
 delay_ms(100);
 }

 else
 {
 delay_ms(50);

  PORTC.F5  = 1;
  PORTC.F4  = 1;
 delay_ms(100);
 }
 }
}



void horizontal_forward()
{



 while(1)
 {

 if( PORTB.F4  == 0)
 {
 delay_ms(50);

  PORTC.F7  = 0;
  PORTC.F6  = 1;
 delay_ms(100);

 while( PORTB.F4  == 0)
 {
 }


 delay_ms(50);
  PORTC.F7  = 1;
  PORTC.F6  = 1;
 delay_ms(100);
 }

 else
 {
 delay_ms(50);

  PORTC.F7  = 1;
  PORTC.F6  = 1;
 delay_ms(100);
 }
 }
}

void horizontal_backward()
{



 while(1)
 {

 if( PORTB.F5  == 0)
 {
 delay_ms(50);

  PORTC.F7  = 1;
  PORTC.F6  = 0;
 delay_ms(100);

 while( PORTB.F5  == 0)
 {
 }


 delay_ms(50);
  PORTC.F7  = 1;
  PORTC.F6  = 1;
 delay_ms(100);
 }

 else
 {
 delay_ms(50);

  PORTC.F7  = 1;
  PORTC.F6  = 1;
 delay_ms(100);
 }
 }
}



void Init_Main()
{



 delay_ms(200);
 TRISB=0xff;


 TRISC=0x00;



  PORTC.f0  = 0;
  PORTC.f3  = 0;
  PORTC.f1  = 0;
  PORTC.f2  = 0;

 Init_PWM();
 delay_ms(200);
}

void main()
{
 Init_Main();

 while(1)
 {
 Track_Line_forward(4);
 Lifter_upward();
 Rotate_Right();
 Track_Line_forward(3);
 Lifter_downward();
 }
}
