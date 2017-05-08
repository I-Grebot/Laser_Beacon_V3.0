/*
 * File:   trilateration.c
 * Author: Julien
 *
 * Created on 30 avril 2017, 19:36
 */


#include "xc.h"
#include "trilateration.h"
#include "board_cfg.h"
#include "beacon_system.h"
#include <math.h>
#include <stddef.h> //for NULL
#include <dsp.h>

#define TABLE_LEN   3000
#define TABLE_HIGH  2000

//TODO these need to be setted using registers
#define DX1         (sint16_t)(-22-17)
#define DY1         (sint16_t)(TABLE_HIGH+22+35)
#define DX2         (sint16_t)(-22-17)
#define DY2         (sint16_t)(-22-80+35)
#define DX3         (sint16_t)(TABLE_LEN+22+17)
#define DY3         (sint16_t)(TABLE_HIGH/2+80/2-35)

static uint16_t diag12;
static uint16_t diag23;
static uint16_t diag31;

//input/output in rads
static float rangeAngle(float A)
{
    while(A<0)
    {
        A += 2*PI;
    }
    while(A >= 2*PI)
    {
        A -= 2*PI;
    }    
    if(A<0) //just because we work with float
    {
        A=0;
    }
    
    return A;
}
// T is turret number (1,2,3)
// R is distance to turret
// returns the number of intersections found
// the first intersection coordinates found is returned through X, Y
static uint8_t SCI(uint8_t Ta, uint32_t Ra, uint8_t Tb, uint32_t Rb, sint32_t *X, sint32_t *Y)
{
    sint32_t cxa;
    sint32_t cya;
    sint32_t cxb;
    sint32_t cyb;
    sint32_t dist;
    uint8_t res = 0;
    
    //wrong argument
    if(!((Ta==1 && Tb==2)||
         (Ta==2 && Tb==3)||
         (Ta==3 && Tb==1) ))
    
    {
        return 0;
    }
        
    if(Ta==1 && Tb==2)
    {
        if(Ra+Rb<diag12)
        {
            //print("too short12",Ra,Rb,diag12)
            return 0;
        }
        else
        {
            cxa=DX1;
            cya=DY1;
            cxb=DX2;
            cyb=DY2;
            dist=diag12;
        }
    }
    else if(Ta==2 && Tb==3)
    {
        if(Ra+Rb<diag23)
        {
            //print("too short23",Ra,Rb,diag23)
            return 0;
        }
        else
        {
            cxa=DX2;
            cya=DY2;
            cxb=DX3;
            cyb=DY3;
            dist=diag23;
        }
    }
    else if(Ta==3 && Tb==1)
    {
        if(Ra+Rb<diag31)
        {
            //print("too short13",Ra,Rb,diag31)
            return 0;
        }
        else
        {
            cxa=DX3;
            cya=DY3;
            cxb=DX1;
            cyb=DY1;
            dist=diag31;
        }
    }
    else
    {
        //print("unexpected error")
        return 0;
    }
    sint32_t a=(Ra*Ra-Rb*Rb+dist*dist)/(2*dist); //TODO potential rounding error to evaluate
    sint32_t h;
    if((Ra*Ra-a*a)<0) //and (Ra**2-a**2)>-2:  #rounding errors are accepted
    {
        h = 0;
    }
    else
    {
        h = sqrt(Ra*Ra-a*a);
    }
    
    sint32_t cxc = cxa+(a*(cxb-cxa))/dist; //TODO check type AND potential rounding error
    sint32_t cyc = cya+(a*(cyb-cya))/dist;
    
    if(X != NULL)
    {
        *X = cxc+(h*(cyb-cya))/dist; //TODO potential rounding error here
    }
    if(Y != NULL)
    {
        *Y = cyc-(h*(cxb-cxa))/dist;
    }
    res++;
    
    //there is a 2nd solution
    if(dist != Ra+Rb)
    {
        //x=cxc-h*(cyb-cya)/dist;
        //y=cyc+h*(cxb-cxa)/dist;
        res++;
    }
    return res;
}

// must be called when a parameter is written by SPI
void init_trilateration(void)
{
    diag12 = sqrt((sint32_t)(DX2-DX1)*(DX2-DX1)+(sint32_t)(DY2-DY1)*(DY2-DY1));
    diag23 = sqrt((sint32_t)(DX3-DX2)*(DX3-DX2)+(sint32_t)(DY3-DY2)*(DY3-DY2));
    diag31 = sqrt((sint32_t)(DX1-DX3)*(DX1-DX3)+(sint32_t)(DY1-DY3)*(DY1-DY3));
}

extern volatile beacon_info_t beacon_infos[BEACON_COM_NB_SLAVE];

//TODO recompute only the parts that are needed not all 6 position at each Rx
// all these calculations are done for only one photodiode per turret.
void compute_position(void)
{
    uint32_t R1 = beacon_infos[0].distance;
    uint32_t R2 = beacon_infos[1].distance;
    uint32_t R3 = beacon_infos[2].distance;

    float a12;
    sint32_t b12;
    float a23;
    sint32_t b23;
    float a31;
    sint32_t b31;
    // equation for L12
    // Y = 0*X + b
    // where b = 
    //    if R1+R2<diag12:
    //           R1=R1/(R1+R2)*diag12
    //           R2=R2/(R1+R2)*diag12
    //    solve circle intersection SCI(1,R1, 2,R2)
    // and draw line with X=0  and X=3000
    // {0,b}
    // {3000,b}

    if((R1+R2)<diag12)
    {
        if((R1+R2)==0)
        {
            R1=1;
        }
        uint16_t r = R1;
        R1 = (R1*(diag12+1))/(R1+R2);
        R2 = (R2*(diag12+1))/(r+R2);
    }
    uint8_t nbSol = SCI(1,R1, 2,R2, NULL, &b12);
    if(nbSol != 0)
    {
        a12=0; //TODO thi sequation is incorect if 1 and 2 are not vertically aligned (and we want to be able tu fine tune ...)
    }
    else
    {
        b12=1;
        a12=1;
    }


    // equation for L23
    // Y = a*X + b
    // where a = -(1000+22+45+5)/(3000+2*22+2*17)
    // where b = 
    //    if R2+R3<diag23:
    //           R2=R2/(R2+R3)*diag23
    //           R3=R3/(R2+R3)*diag23
    //    solve circle intersection SCI(2,R2, 3,R3)
    // solve a and b
    // and draw line with Y=0  and Y=2000
    // {-b/a,0}
    // {(2000-b)/a,2000}

    if((R2+R3)<diag23)
    {
        if((R2+R3)==0)
        {
            R2=1;
        }
        uint16_t r=R2;
        R2 = (R2*(diag23+1))/(R2+R3);
        R3 = (R3*(diag23+1))/(r+R3);
    }
    sint32_t x,y;
    nbSol = SCI(2,R2, 3,R3, &x, &y);
    if(nbSol!=0)
    {
        a23 = -(float)(DX3-DX2)/(DY3-DY2);
        b23 = y-a23*x;
    }
    else
    {        
        a23 = 1;
        b23 = 1;
    }

    // equation for L31
    // Y = a*X + b
    // where a =
    // where b = 
    //    if R3+R1<diag31:
    //           R3=R3/(R3+R1)*diag31
    //           R1=R1/(R3+R1)*diag31
    //    solve circle intersection SCI(3,R3, 1,R1)
    // solve a and b
    // and draw line with Y=0  and Y=2000
    // {-b/a,0}
    // {(2000-b)/a,2000}

    if((R1+R3)<diag31)
    {
        if((R1+R3)==0)
        {
            R1 = 1;
        }
        uint16_t r = R1;
        R1 = (R1*(diag31+1))/(R1+R3); //TODO bit precision loss ! 
        R3 = (R3*(diag31+1))/(r+R3);
    }
    nbSol = SCI(3,R3, 1,R1, &x, &y);
    if(nbSol!=0)
    {
        a31 = (float)(DX3-DX1)/(DY1-DY3);
        b31 = y-a31*x;
    }
    else
    {
        a31 = 1;
        b31 = 1;
    }

    // drawing
    //L12 = Line(Point(0,b12),Point(TABLE_LEN,b12))
    //L23 = Line(Point(-b23/a23,0),Point((TABLE_HIGH-b23)/a23, TABLE_HIGH))
    //L31 = Line(Point(-b31/a31,0),Point((TABLE_HIGH-b31)/a31, TABLE_HIGH))


    // position of BTX
    beacon_infos[0].X = ((b12-b31)/a31 + (b12-b23)/a23 - (b31-b23)/(a31-a23))/3;
    beacon_infos[0].Y = (2*b12+(b31-a31*(b31-b23)/(a31-a23)))/3;
    //TODO this is turret 1 containing Btx position

    //calculate BTX angle with mean of 3 BRX viewing angles
    float A1_rel = beacon_infos[0].angle*2*PI/3600;  //TODO all angles in rad (except prints) because it's needed
    float A2_rel = beacon_infos[1].angle*2*PI/3600;
    float A3_rel = beacon_infos[2].angle*2*PI/3600;
    float A1_abs, A2_abs, A3_abs;

    if(R1 !=0)
    {
        sint16_t A1_ = acos((beacon_infos[0].X - DX1)/(float)R1); //10th degrees
        A1_abs = PI - A1_rel - A1_;
        //print("Alpha",A1_)
        // TODO fail safe
    }

    if(R2 != 0)
    {
        sint16_t A2_ = acos((beacon_infos[0].X - DX2)/(float)R2);
        A2_abs = PI - A2_rel + A2_;
        //print("Beta",A2_)
    }

    if(R3 != 0)
    {
        sint16_t A3_ = asin((beacon_infos[0].Y - DY3)/(float)R3);
        A3_abs = - A3_rel - A3_;
        //print("Gama",A3_)
    }

    A1_abs = rangeAngle(A1_abs);
    A2_abs = rangeAngle(A2_abs);
    A3_abs = rangeAngle(A3_abs);


    sint16_t xa = (cos(A1_abs) + cos(A3_abs) + cos(A3_abs) )/3;
    sint16_t ya = (sin(A1_abs) + sin(A3_abs) + sin(A3_abs) )/3;
    A1_abs =  atan2(ya, xa); //in rads
    beacon_infos[0].absAngle = A1_abs*360/(2*PI);
    
    float A4 = beacon_infos[3].angle*2*PI/3600 + A1_abs; //TODO rangeAngle this
    float A5 = beacon_infos[4].angle*2*PI/3600 + A1_abs;
    float A6 = beacon_infos[5].angle*2*PI/3600 + A1_abs;

    //calculate distance/angle to opponent, position of opponent
    beacon_infos[3].absAngle = A4*360/(2*PI);
    beacon_infos[3].X = beacon_infos[0].X + beacon_infos[3].distance * cos(A4);
    beacon_infos[3].Y = beacon_infos[0].Y + beacon_infos[3].distance * sin(A4);

    //calculate distance/angle to opponent, position of opponent
    beacon_infos[4].absAngle = A5*360/(2*PI);
    beacon_infos[4].X = beacon_infos[0].X + beacon_infos[4].distance * cos(A5);
    beacon_infos[4].Y = beacon_infos[0].Y + beacon_infos[4].distance * sin(A5);

    //calculate distance/angle to opponent, position of opponent
    beacon_infos[5].absAngle = A6*360/(2*PI);
    beacon_infos[5].X = beacon_infos[0].X + beacon_infos[5].distance * cos(A6);
    beacon_infos[5].Y = beacon_infos[0].Y + beacon_infos[5].distance * sin(A6);
}
/*    
    0b0001, // Static TOP    beacon
    0b0010, // Static BOTTOM beacon (same side than Top)
    0b0011, // Static MIDDLE beacon (other side than Top)
    0b0100, // friend secondary
    0b0101, // Opponent main      robot
    0b0110, // Opponent secondary robot
 */
/*
    uint8_t id           : 4 ; // Equivalent to the board ID
    beacon_state_t state : 4 ; // Beacon current state
    uint16_t timestamp       ; // Last activity timestamp
    uint16_t distance        ; // Relative distance in mm from the turret
    sint16_t angle           ; // Relative angle in 10th of degree relative to the turret
    sint16_t X               ; // Position in mm
    sint16_t Y               ; // Position in mm
    sint16_t absAngle        ; // Absolute angle in 10th of degree*/