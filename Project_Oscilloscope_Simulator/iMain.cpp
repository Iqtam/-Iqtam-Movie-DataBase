/********CONTRIBUTORS********/

/*** Md.Tamim Iqbal      *     Md.Minhajul Islam Fuad
     ID:2005028          *     ID:2005029             ***/


/********** Presenting OSCILLOSCPE SIMULATOR ************/


# include "iGraphics.h"
#include<math.h>
#include<string.h>

#define  white iSetColor(255,255,255)
#define greenish iSetColor(102,255,0)

#define box1(a,b,c,d,e,f,s) {                                          \
                                iRectangle(a,b,c,d);                   \
                                iText(e, f, #s);                       \
                            }
#define box2(a,b,c,d,e,f,s1,g,h,s2){                                   \
                                      iRectangle(a,b,c,d);             \
                                      iText(e, f, #s1);                \
                                      iText(g, h, #s2);                \
                                   }
#define box3(a,b,c,d,e,f,s1)       {                                   \
                                      iSetColor(10,209,176);           \
                                      iFilledRectangle(a,b,c,d);       \
                                      iSetColor(255,255,255);          \
                                      iText(e, f, #s1);                \
                                   }
double width = 10;
int  height = 10;
int t=-5000;                       /*** for starting representation***/
int x1=490,x2=510;
int l1=70,l2=70;

int mode;
char dynamic_mode[1];
char dynamic_mode_str[1];
int dynamic_pixel[2];

void starting();
void swapp(int *x,int *y);
void mainscreen();
void wavetracing();
void input();
void output();
void amplitude();
void timeperiod();
void dynamic();

typedef struct channelmode
{
    char str1[20];
    char str2[20];
    int state;
};
channelmode submode[6];

typedef struct wave
{
    int amp;
    int omega;
    int totalp;                 //total pixel in x direction;
    int extra_counter;          //extra pixel for completing the wave
    double xp[100000];         //pixel in x direction
    double yp[200000];         //pixel in y direction

}wave;

wave ch1,ch2;                   //global declaration of ch1 and ch2;


void wavedraw(wave *w)
{
    double x=0,y;
    int i=0;

    while((x*(w->omega)+80)<565)
    {
        w->xp[i]=x*(w->omega)+80;
        y=(w->amp)*sin(x);
        w->yp[i]=y*5+305;
        x+=.001;
        i++;
    }
    w->totalp=i;

    i=0;
    while(w->yp[i]>=305)
    {
        i++;
        w->extra_counter=i;
    }
    for(i=w->totalp;i<(w->totalp-1+2*(w->extra_counter));i++)
    {
        w->yp[i]=(w->amp)*sin(x)*5+305;
        x+=.001;
    }

}

void dynamic()
{

    if(dynamic_mode_str[0]=='1' || dynamic_mode_str[0]=='b')
    {
        if(dynamic_pixel[0]<=2*(ch1.extra_counter))
        {
            dynamic_pixel[0]+=75;
        }
        else
        {
            dynamic_pixel[0]=0;
        }
    }
    if(dynamic_mode_str[0]=='2' || dynamic_mode_str[0]=='b')
    {
        if(dynamic_pixel[1]<=2*ch2.extra_counter)
        {
            dynamic_pixel[1]+=75;
        }
        else
        {
            dynamic_pixel[1]=0;
        }
    }
}
void amplitude()
{
    int i=0;
    switch(mode)
    {
        case 3: if(ch1.amp>=0)
                {
                    ch1.amp++;
                    wavedraw(&ch1);
                }
                else
                {
                    ch1.amp--;
                    wavedraw(&ch1);
                }
                break;

        case 5: if(ch1.amp<0)
                {
                    ch1.amp++;
                    wavedraw(&ch1);
                }
                else if(ch1.amp>0)
                {
                    ch1.amp--;
                    wavedraw(&ch1);
                }
                break;

        case 4: if(ch2.amp>=0)
                {
                    ch2.amp++;
                    wavedraw(&ch2);
                }
                else
                {
                    ch2.amp--;
                    wavedraw(&ch2);
                }
                break;

        case 6: if(ch2.amp<0)
                {
                    ch2.amp++;
                    wavedraw(&ch2);
                }
                else if(ch2.amp>0)
                {
                    ch2.amp--;
                    wavedraw(&ch2);
                }
                break;
    }
}
void timeperiod()
{
    switch(mode)
    {
        case 7: ch1.omega--;
                wavedraw(&ch1);
                break;
        case 9: ch1.omega++;
                wavedraw(&ch1);
                break;
        case 8: ch2.omega--;
                wavedraw(&ch2);
                break;
        case 10:ch2.omega++;
                wavedraw(&ch2);
                break;
    }

}
void iDraw()
{
    iClear();

    if(t<0)
    {
        starting();                         /*** starting representation***/
    }
    else
    {
        mainscreen();                      /*** main representation***/
        wavetracing();
    }
}
void starting()
{
    iSetColor(255,0,0);
    iFilledRectangle(x1,320,50,50);
    iSetColor(0,0,255);
    iFilledRectangle(x2,320,50,50);
    if(t%500==0)
    {
        swapp(&x1,&x2);
    }
    iSetColor(10,209,176);
    iText(450,300,"<<<OSCILLOSCOPE>>>");
    iSetColor(80,240,12);
    iFilledRectangle(400,280,width,height);
    if(width<250)
    {
        width+=.05;
    }
    t++;
}

void swapp(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;

}

void mainscreen()
{
    iShowBMP(65, 58, "SCREEN3.bmp");                         /*** pixel size of SCREEN3.bmp= 512 * 512***/
    iSetColor(10,209,176);
    iText(65,30,"Press END for closing the simulator!");

    if(mode==1)
    {
        switch(submode[0].state)
        {
            case 0: greenish;
                    box1(665,475,120,25,666,480,AMP:);
                    iText(700,480,submode[0].str2);
                    break;

            case 1: box3(665,475,120,25,666,480,AMP:);
                    iText(700,480,submode[0].str2);
                    break;
        }
        switch(submode[1].state)
        {
            case 0: greenish;
                    box1(665,449,120,26,666,454,T.PERIOD:);
                    iText(740,454,submode[1].str2);
                    break;

            case 1: box3(665,449,120,26,666,454,T.PERIOD:);
                    iText(740,454,submode[1].str2);
                    break;
        }
        switch(submode[2].state)
        {
            case 0: greenish;
                    box1(665,420,120,29,666,425,SHAPE:);
                    iText(715,425,submode[2].str2);
                    break;

            case 1: box3(665,420,120,29,666,425,SHAPE:);
                    iText(715,425,submode[2].str2);
                    break;
        }

    }
    else white;
    box1(665,420,120,80,670,400,LEFT for Ch_1);        //iRectangle(665,420,120,80);
                                                       //iText(670, 400, "LEFT for Ch_1");

    if(mode==2)
    {
        switch(submode[3].state)
        {
            case 0: greenish;
                    box1(805,475,120,25,806,480,AMP:);
                    iText(840,480,submode[3].str2);
                    break;

            case 1: box3(805,475,120,25,806,480,AMP:);
                    iText(840,480,submode[3].str2);
                    break;
        }
        switch(submode[4].state)
        {
            case 0: greenish;
                    box1(805,449,120,26,806,454,T.PERIOD:);
                    iText(880,454,submode[4].str2);
                    break;

            case 1: box3(805,449,120,26,806,454,T.PERIOD:);
                    iText(880,454,submode[4].str2);
                    break;
        }
        switch(submode[5].state)
        {
            case 0: greenish;
                    box1(805,420,120,29,806,425,SHAPE:);
                    iText(855,425,submode[5].str2);
                    break;

            case 1: box3(805,420,120,29,806,425,SHAPE:);
                    iText(855,425,submode[5].str2);
                    break;
        }
    }
    else white;
    box1(805,420,120,80,800,400,RIGHT for Ch_2);           //iRectangle(805,420,120,80);
                                                           //iText(800, 400, "RIGHT for Ch_2");

    if(mode==3)
    {
        greenish;
        if(ch1.amp<=45 && ch1.amp>=-45)
        amplitude();
    }
    else white;
    box2(665,340,125,40,670,365,ARISE,670,350,AMPLITUDE_1);          //iRectangle(665,340,125,40);
                                                                     //iText(670, 365, "ARISE ");
                                                                     //iText(670, 350, "AMPLITUDE_1");
    if(mode==4)
    {
        greenish;
        if(ch2.amp<=45 && ch2.amp>=-45)
        amplitude();
    }
    else white;
    box2(800,340,125,40,805,365,ARISE,805,350,AMPLITUDE_2);

    if(mode==5)
    {
        greenish;
        if(ch1.amp!=0)
        amplitude();
    }
    else white;
    box2(665,290,125,40,670,315,LOWER,670,300,AMPLITUDE_1);

    if(mode==6)
    {
        greenish;
        if(ch2.amp!=0)
        amplitude();
    }
    else white;
    box2(800,290,125,40,805,315,LOWER,805,300,AMPLITUDE_2);

    if(mode==7)
    {
        greenish;
        if(ch1.omega>5)
        timeperiod();
    }
    else white;
    box2(665,230,125,40,670,255,INCREASE,670,240,FREQUENCY_1);

    if(mode==8)
    {
        greenish;
        if(ch2.omega>5)
        timeperiod();
    }
    else white;
    box2(800,230,125,40,805,255,INCREASE,805,240,FREQUENCY_2);

    if(mode==9)
    {
        greenish;
        if(ch1.omega<=150)
        timeperiod();
    }
    else white;
    box2(665,180,125,40,670,205,DECREASE,670,190,FREQUENCY_1);

    if(mode==10)
    {
        greenish;
        if(ch2.omega<=150)
        timeperiod();
    }
    else white;
    box2(800,180,125,40,805,205,DECREASE,805,190,FREQUENCY_2);

    if(mode==11)
    {
        greenish;
        iText(665,80,"Press 1 for Ch_1 and 2 for Ch_2");
        iText(665,50,"Press b for both");
    }
    else white;
    box1(665,120,260,40,755,135,DYNAMIC);

    if(mode!=1)
    {
        iSetColor(255,0,0);
        iFilledCircle(725, 460, 30);
    }
    if(mode!=2)
    {
        iSetColor(0,0,255);
        iFilledCircle(860,460,30);
    }

}

void wavetracing()
{
    int j=0;

    iSetColor(255,0,0);

    if((mode%2)!=0 || mode==0 || mode==11)
    {
        if(mode!=11)
        {
            while(j<(ch1.totalp))                                      /*** wave tracing of ch1 without dynamism***/
            {
                iPoint(ch1.xp[j],ch1.yp[j],1);
                j++;
            }
        }
        else if(dynamic_mode_str[0]=='1' || dynamic_mode_str[0]=='b')
        {
            while(j<(ch1.totalp))                                      /**** dynamic wave tracing for ch1****/
            {
                iPoint(ch1.xp[j],ch1.yp[j+dynamic_pixel[0]],1);
                j++;
            }
        }

    }

    j=0;
    iSetColor(0,0,255);

    if(mode%2==0 || mode==0 || mode==11 )
    {
        if(mode!=11)
        {
            while(j<ch2.totalp)                                        /*** wave tracing of ch2 without dynamism***/
            {
                iPoint(ch2.xp[j],ch2.yp[j],1);
                j++;
            }
        }
        else if(dynamic_mode_str[0]=='2' || dynamic_mode_str[0]=='b')
        {
            while(j<ch2.totalp)                                        /**** dynamic wave tracing for ch2****/
            {
                iPoint(ch2.xp[j],ch2.yp[j+dynamic_pixel[1]],1);
                j++;
            }
        }

    }
}

void iMouseMove(int mx, int my)
{


}

void iMouse(int button, int state, int mx, int my)
{
    int i,j;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if(mx >= 665 && mx <= 785 && my >= 420 && my <= 500)
		{
			mode = 1;
			if(my>=475)
            {
                j=0;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
			else if(my>=449)
            {
                j=1;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
			else if(my>=420)
            {
                j=2;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
		}

		if(mx >= 805 && mx <= 925 && my >= 420 && my <= 500)
		{
			mode = 2;
            if(my>=475)
            {
                j=3;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
			else if(my>=449)
            {
                j=4;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
			else if(my>=420)
            {
                j=5;
                submode[j].state=1;
                for(i=0;i<6;i++)
                {
                    if(i!=j)submode[i].state=0;
                }
            }
		}

		if(mx >= 665 && mx <= 790 && my >= 340 && my <= 380) mode = 3;

		if(mx >= 800 && mx <= 925 && my >= 340 && my <= 380) mode = 4;

		if(mx >= 665 && mx <= 790 && my >= 290 && my <= 330) mode = 5;

		if(mx >= 800 && mx <= 925 && my >= 290 && my <= 330) mode = 6;

		if(mx >= 665 && mx <= 790 && my >= 230 && my <= 270) mode = 7;

		if(mx >= 800 && mx <= 925 && my >= 230 && my <= 270) mode = 8;

		if(mx >= 665 && mx <= 790 && my >= 180 && my <= 220) mode = 9;

		if(mx >= 800 && mx <= 925 && my >= 180 && my <= 220) mode = 10;

		if(mx >= 665 && mx <= 925 && my >= 120 && my <= 160)
        {
            mode = 11;
            dynamic_pixel[0]=0;
            dynamic_pixel[1]=0;
            iSetTimer(50,dynamic);
        }

    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if(mx >= 665 && mx <= 785 && my >= 420 && my <= 500)
		{
			mode = 0;
			submode[0].state=0;
			submode[1].state=0;
			submode[2].state=0;
		}

		if(mx >= 805 && mx <= 925 && my >= 420 && my <= 500)
		{
			mode = 0;
			submode[3].state=0;
			submode[4].state=0;
			submode[5].state=0;
		}

		if(mx >= 665 && mx <= 790 && my >= 340 && my <= 380) mode=0;

		if(mx >= 800 && mx <= 925 && my >= 340 && my <= 380) mode = 0;

		if(mx >= 665 && mx <= 790 && my >= 290 && my <= 330) mode = 0;

		if(mx >= 800 && mx <= 925 && my >= 290 && my <= 330) mode = 0;

		if(mx >= 665 && mx <= 790 && my >= 230 && my <= 270) mode = 0;

		if(mx >= 800 && mx <= 925 && my >= 230 && my <= 270) mode = 0;

		if(mx >= 665 && mx <= 790 && my >= 180 && my <= 220) mode = 0;

		if(mx >= 800 && mx <= 925 && my >= 180 && my <= 220) mode = 0;

		if(mx >= 665 && mx <= 925 && my >= 120 && my <= 160)
        {
            mode = 0;
            iPauseTimer(0);
            dynamic_pixel[0]=0;
            dynamic_pixel[1]=0;
            dynamic_mode_str[0]='0';
        }
    }
}

int len;
void iKeyboard(unsigned char key)
{
    int i;

    if(key == 'q')
    {
        exit(0);
    }
    if(mode==1)
    {
        if(key == '\r')
		{
            if(submode[0].state==1)
            {
                strcat(submode[0].str2," V");
            }
            else if(submode[1].state==1)
            {
                strcat(submode[1].str2," s");
            }
            for(i=0;i<=len;i++)
            {
                if(submode[0].state==1)
                {
                    submode[0].str1[i] = 0;
                }
                else if(submode[1].state==1)
                {
                    submode[1].str1[i]=0;
                }
                else if(submode[2].state==1)
                {
                    submode[2].str1[i]=0;
                }
            }
            len = 0;
            if(submode[0].state==1 || submode[1].state==1)
            {
                output();
            }
		}
		else
		{
		    if(submode[0].state==1)
            {
                submode[0].str1[len] = key;
                strcpy(submode[0].str2,submode[0].str1);
                len++;
                input();
            }
            else if(submode[1].state==1)
            {
                submode[1].str1[len] = key;
                strcpy(submode[1].str2,submode[1].str1);
                len++;
                input();
            }
            else if(submode[2].state==1)
            {
                submode[2].str1[len] = key;
                strcpy(submode[2].str2,submode[2].str1);
                len++;
                input();
            }
		}
    }

    if(mode==2)
    {
        if(key == '\r')
		{
            if(submode[3].state==1)
            {
                strcat(submode[3].str2," V");
            }
            else if(submode[4].state==1)
            {
                strcat(submode[4].str2," s");
            }
            for(i=0;i<=len;i++)
            {
                if(submode[3].state==1)
                {
                    submode[3].str1[i] = 0;
                }
                else if(submode[4].state==1)
                {
                    submode[4].str1[i]=0;
                }
                else if(submode[5].state==1)
                {
                    submode[5].str1[i]=0;
                }
            }
            len = 0;
            if(submode[3].state==1 || submode[4].state==1)
            {
                output();
            }
		}
		else
		{
		    if(submode[3].state==1)
            {
                submode[3].str1[len] = key;
                strcpy(submode[3].str2,submode[3].str1);
                len++;
                input();
            }
            else if(submode[4].state==1)
            {
                submode[4].str1[len] = key;
                strcpy(submode[4].str2,submode[4].str1);
                len++;
                input();
            }
            else if(submode[5].state==1)
            {
                submode[5].str1[len] = key;
                strcpy(submode[5].str2,submode[5].str1);
                len++;
                input();
            }
		}
    }

    if(mode==11)
    {
        if(key == '\r')
		{
            strcpy(dynamic_mode_str,dynamic_mode);
            dynamic_mode[0]=0;
		}
		else
		{
            dynamic_mode[0]=key;
		}

    }

}
void output()
{
    FILE *out=fopen("input.txt","r");

    if(submode[0].state==1)
    {
        fscanf(out,"%d",&ch1.amp);
        wavedraw(&ch1);
    }
    else if(submode[1].state==1)
    {
        fscanf(out,"%d",&ch1.omega);
        wavedraw(&ch1);
    }
    else if(submode[3].state==1)
    {
        fscanf(out,"%d",&ch2.amp);
        wavedraw(&ch2);
    }
    else if(submode[4].state==1)
    {
        fscanf(out,"%d",&ch2.omega);
        wavedraw(&ch2);
    }

    fclose(out);
}
void input()
{
    FILE *in=fopen("input.txt","w");

    if(submode[0].state==1)
    {
        fprintf(in,"%s",submode[0].str1);
    }
    else if(submode[1].state==1)
    {
        fprintf(in,"%s",submode[1].str1);
    }
    else if(submode[2].state==1)
    {
        fprintf(in,"%s",submode[2].str1);
    }
    else if(submode[3].state==1)
    {
        fprintf(in,"%s",submode[3].str1);
    }
    else if(submode[4].state==1)
    {
        fprintf(in,"%s",submode[4].str1);
    }
    else if(submode[5].state==1)
    {
        fprintf(in,"%s",submode[5].str1);
    }

    fclose(in);

}

void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
}

int main()
{

    int i;

    ch1.amp=10;
    ch1.omega=20;
    ch1.extra_counter=0;
    wavedraw(&ch1);

    ch2.amp=20;
    ch2.omega=20;
    ch2.extra_counter=0;
    wavedraw(&ch2);

    for(i=0;i<6;i++)
    {
        submode[i].state=0;
    }

    iInitialize(1000, 600, "Oscilloscope Simulator!");
    return 0;
}
