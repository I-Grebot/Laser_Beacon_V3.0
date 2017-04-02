from graphics import *
from random import randrange
import serial
import serial.tools.list_ports
from math import sqrt
from math import acos
from math import asin
import math


PI = math.pi
NB_HISTORY = 2
SCALE = 3
T_COLOR = "yellow"
T_LEN = 3000
T_HIGH = 2000
TABLE_COLOR = "green"
D_RADIUS = 2
D_COLOR = "red"
#grey from 0 (black) to 100 (white)

DX1=-22-17
DY1=T_HIGH+22+35
DX2=-22-17
DY2=-22-80+35
DX3=T_LEN+22+17
DY3=T_HIGH/2+80/2-35

D1_POINT = Point(DX1, DY1)
D2_POINT = Point(DX2, DY2)
D3_POINT = Point(DX3, DY3)
HIST_COLORS = ["gray"+str(i*100//(NB_HISTORY-1)) for i in range(NB_HISTORY)]

#distances between photodiodes
diag12=sqrt((DX2-DX1)**2+(DY2-DY1)**2)
diag23=sqrt((DX3-DX2)**2+(DY3-DY2)**2)
diag31=sqrt((DX1-DX3)**2+(DY1-DY3)**2)





#return 0, 1 or 2 intersection coordinates
def SCI(Ta, Ra, Tb, Rb):
    res =[]
    #wrong argument
    if [Ta,Tb] not in [[1,2],[2,3],[3,1]]:
        print("wrong argument")
        return []
        
    if Ta==1 and Tb==2:
        if Ra+Rb<diag12:
            print("too short12",Ra,Rb,diag12)
            return []
        else:
            cxa=DX1
            cya=DY1
            cxb=DX2
            cyb=DY2
            dist=diag12
    elif Ta==2 and Tb==3:
        if Ra+Rb<diag23:
            print("too short23",Ra,Rb,diag23)
            return []
        else:
            cxa=DX2
            cya=DY2
            cxb=DX3
            cyb=DY3
            dist=diag23
    elif Ta==3 and Tb==1:
        if Ra+Rb<diag31:
            print("too short13",Ra,Rb,diag31)
            return []
        else:
            cxa=DX3
            cya=DY3
            cxb=DX1
            cyb=DY1
            dist=diag31
    else:
        print("unexpected error")
        return []
    
    a=(Ra**2-Rb**2+dist**2)/(2*dist)
    if (Ra**2-a**2)<0 :#and (Ra**2-a**2)>-2:  #rounding errors are accepted
        h=0
    else:  
        h=sqrt(Ra**2-a**2)
    
    cxc=cxa+a*(cxb-cxa)/dist
    cyc=cya+a*(cyb-cya)/dist
      
    x=cxc+h*(cyb-cya)/dist
    y=cyc-h*(cxb-cxa)/dist
    res.append([x,y])
    
    #there is a 2nd solution
    if dist!=Ra+Rb:
        x=cxc-h*(cyb-cya)/dist
        y=cyc+h*(cxb-cxa)/dist
        res.append([x,y])
    
    return res


if __name__ == '__main__':
    print(HIST_COLORS)
    print("Starting program")
    win = GraphWin("drawPosition",(T_LEN+2*(22+80))/SCALE,(T_HIGH+2*(22+80))/SCALE)
    win.autoflush = False
    win.setCoords(-80-22,-80-22,T_LEN+80+22,T_HIGH+80+22)
    table = Rectangle(Point(0,0), Point(T_LEN,T_HIGH))
    table.setFill(TABLE_COLOR)
    table.draw(win)
    #haut gauche
    t1 = Rectangle(Point(-80-22,T_HIGH+22), Point(-22,T_HIGH+22+80))
    t1.setFill(T_COLOR)
    t1.draw(win)
    d1 = Circle(D1_POINT, D_RADIUS)
    d1.setFill(D_COLOR)
    d1.setOutline(D_COLOR)
    d1.draw(win)
    #bas gauche
    t2 = Rectangle(Point(-80-22,-80-22), Point(-22,-22))
    t2.setFill(T_COLOR)
    t2.draw(win)
    d2 = Circle(D2_POINT, D_RADIUS)
    d2.setFill(D_COLOR)
    d2.setOutline(D_COLOR)
    d2.draw(win)
    #droite milieu
    t3 = Rectangle(Point(T_LEN+22,T_HIGH/2-80/2), Point(T_LEN+22+80,T_HIGH/2+80/2))
    t3.setFill(T_COLOR)
    t3.draw(win)
    d3 = Circle(D3_POINT, D_RADIUS)
    d3.setFill(D_COLOR)
    d3.setOutline(D_COLOR)
    d3.draw(win)
    
    # dessiner les carreaux du sol
    for i in range(10):
        jv=Line(Point(300*i+190,0), Point(300*i+190,T_HIGH))
        jv.setOutline("grey")
        jv.draw(win)
        jv.setWidth(2)
    
    for j in range(6):
        jh=Line(Point(0,300*j+190), Point(T_LEN,300*j+190))
        jh.setOutline("grey")
        jh.draw(win)
        jh.setWidth(2)
    
    #prepare the list of history circles
    cList=[]
    for i in range(NB_HISTORY+1):
        c1 = Circle(D1_POINT, 0)
        c2 = Circle(D2_POINT, 0)
        c3 = Circle(D3_POINT, 0)
        c1.draw(win)
        c2.draw(win)
        c3.draw(win)
        cList.append([c1,c2,c3])
    
    win.flush()
    print("Click into the window !!!")
    win.getMouse()
    
    #   1
    #
    #
    #
    #                                 3
    #
    #
    #
    #   2
    
    L12 = Line(Point(0,0), Point(1,1))
    L23 = Line(Point(0,0), Point(1,1))
    L31 = Line(Point(0,0), Point(1,1))
    
    pos=Circle(Point(0,0),1)
    
    serList = serial.tools.list_ports.comports()
    serList = [s for s in serList if s.description=="TTL232R-3V3"]	
    if len(serList) != 1:
        print("Error did not found serial interface to use")
    else :
        ser = serial.Serial(serList[0].device,baudrate=115200, timeout=0)
        ser.reset_input_buffer()
        
        S = b""
        turretInfos=[[0,0,0],[0,0,0],[0,0,0]]    
            
        #for i in range(1000):
        while True:    
            
            Sp_bloc = []
            while len(Sp_bloc)<2:
                s = ser.read(100)
                if s:
                    S += s
                else:
                    time.sleep(0.001)
                Sp_bloc = S.split(b"\r\nSpeed",1)
                if len(Sp_bloc) >= 2:
                    S = Sp_bloc[1]
                    Sp = Sp_bloc[0].split()
                    if len(Sp) == 34:
                        try:
                            turretInfos = [[int(Sp[7]), int(Sp[10]), int(Sp[13])], [int(Sp[17]), int(Sp[20]), int(Sp[23])], [int(Sp[27]), int(Sp[30]), int(Sp[33])]]
                            #print(turretInfos[0][0])
                            #print(turretInfos[1][0])
                            #print(turretInfos[2][0])
                        except:
                            print("unexpected exception")
        
            c1,c2,c3 = cList.pop(0)
            c1.undraw()
            c2.undraw()
            c3.undraw()
       
            for j,v in enumerate(cList):
                for c in v:
                    c.setOutline(HIST_COLORS[j])
            
            R1 = turretInfos[0][0]
            R2 = turretInfos[1][0]
            R3 = turretInfos[2][0]
            
            c1 = Circle(D1_POINT, R1)
            c2 = Circle(D2_POINT, R2)
            c3 = Circle(D3_POINT, R3)
            c1.setOutline("red")
            c2.setOutline("red")
            c3.setOutline("red")
            c1.draw(win)
            c2.draw(win)
            c3.draw(win)
            cList.append([c1,c2,c3])
           
            pos.undraw() 
            L12.undraw()
            L23.undraw()
            L31.undraw()
            
            
            # equation for L12
            # Y = 0*X + b
            # where b = 
            #    if R1+R2<diag12:
            #           R1=R1/(R1+R2)*diag12
            #           R2=R2/(R1+R2)*diag12
            #    solve circle intersection SCI(1,R1, 2,R2)
            # and draw line with X=0  and X=3000
            # {0,b}
            # {3000,b}
                
            if (R1+R2)<diag12:
                if (R1+R2)==0:
                    R1=1
                r=R1
                R1=R1/(R1+R2)*(diag12+1)
                R2=R2/(r+R2)*(diag12+1)
            res = SCI(1,R1, 2,R2)
            if len(res)!=0:
                b12 = res[0][1]
                a12=0
            else:
                b12=1
                a12=1
            
            
            # equation for L23
            # Y = a*X + b
            # where a = -(1000+22+45+5)/(3000+2*22+2*17)
            # where b = 
            #    if R2+R3<diag23:
            #           R2=R2/(R2+R3)*diag23
            #           R3=R3/(R2+R3)*diag23
            #    solve circle intersection SCI(2,R2, 3,R3)
            # solve a and b
            # and draw line with Y=0  and Y=2000
            # {-b/a,0}
            # {(2000-b)/a,2000}
                
            if (R2+R3)<diag23:
                if (R2+R3)==0:
                    R2=1
                r=R2
                R2=R2/(R2+R3)*(diag23+1)
                R3=R3/(r+R3)*(diag23+1)
            res = SCI(2,R2, 3,R3)
            if len(res)!=0:
                a23 = -(DX3-DX2)/(DY3-DY2)
                x,y = res[0]
                b23=y-a23*x
            else:
                a23=1
                b23=1

            # equation for L31
            # Y = a*X + b
            # where a =
            # where b = 
            #    if R3+R1<diag31:
            #           R3=R3/(R3+R1)*diag31
            #           R1=R1/(R3+R1)*diag31
            #    solve circle intersection SCI(3,R3, 1,R1)
            # solve a and b
            # and draw line with Y=0  and Y=2000
            # {-b/a,0}
            # {(2000-b)/a,2000}
                
            if (R1+R3)<diag31:
                if (R1+R3)==0:
                    R1=1
                r=R1
                R1=R1/(R1+R3)*(diag31+1) 
                R3=R3/(r+R3)*(diag31+1)
            res = SCI(3,R3, 1,R1)
            if len(res)!=0:
                a31 = (DX3-DX1)/(DY1-DY3)
                x,y = res[0]
                b31=y-a31*x
            else:
                a31=1
                b31=1
            
            # drawing
            L12 = Line(Point(0,b12),Point(T_LEN,b12))
            L23 = Line(Point(-b23/a23,0),Point((T_HIGH-b23)/a23, T_HIGH))
            L31 = Line(Point(-b31/a31,0),Point((T_HIGH-b31)/a31, T_HIGH))
            L12.draw(win)
            L23.draw(win)
            L31.draw(win)
            
            # position of BTX
            X = ((b12-b31)/a31 + (b12-b23)/a23 - (b31-b23)/(a31-a23))/3
            Y = (2*b12+(b31-a31*(b31-b23)/(a31-a23)))/3
            
            
            # drawing
            pos = Circle(Point(X,Y),40)
            pos.setOutline("yellow")
            pos.setFill("red")
            pos.draw(win)
            
            
            
            #calculate BTX angle with mean of 3 BRX viewing angles
            A1 = turretInfos[0][1]
            A2 = turretInfos[1][1]
            A3 = turretInfos[2][1]
            
            if R1 !=0 :
                A1_ = acos((X - DX1)/R1)*360/2/PI
                A1_ = int(A1_*10) #10th Degrees
                A1 = A1 + A1_ + 1800
            
            if R2 != 0:
                A2_ = acos((X - DX2)/R2)*360/2/PI
                A2_ = int(A2_*10) #10th Degrees
                A2 = A2 - A2_ + 1800
 
            if R3 != 0:
                A3_ = asin((Y - DY3)/R3)*360/2/PI
                A3_ = int(A3_*10) #10th Degrees
                A3 = A3 - A3_
                
            
            #TODO all angles must be positive    
            A = (A1 + A2 + A3) /3    
            # drawing
            print("Angles ", A1, A2, A3, A)
            #TODO to be confirmed for all
            
            #calculate distance/angle to opponent, position of opponent
            
            
            
            
            
            
            #time.sleep(0.1) #100ms sleep between updates
            win.flush()
        ser.close()
        print("Program ended, click into the window to close !!!")
        win.getMouse()
    
    
