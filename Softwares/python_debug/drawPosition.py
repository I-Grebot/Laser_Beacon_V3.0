from graphics import *
from random import randrange
import serial
import serial.tools.list_ports
from math import sqrt
from math import acos
from math import asin
from math import cos
from math import sin
from math import atan2
import math


PI = math.pi
NB_HISTORY = 2
SCALE = 3
T_COLOR = "yellow"
TABLE_LEN = 3000
TABLE_HIGH = 2000
TABLE_COLOR = "green"
D_RADIUS = 2
D_COLOR = "red"
#grey from 0 (black) to 100 (white)

DX1=-22-17
DY1=TABLE_HIGH+22+35
DX2=-22-17
DY2=-22-80+35
DX3=TABLE_LEN+22+17
DY3=TABLE_HIGH/2+80/2-35

D1_POINT = Point(DX1, DY1)
D2_POINT = Point(DX2, DY2)
D3_POINT = Point(DX3, DY3)
HIST_COLORS = ["gray"+str(i*100//(NB_HISTORY-1)) for i in range(NB_HISTORY)]

#distances between photodiodes
diag12=sqrt((DX2-DX1)**2+(DY2-DY1)**2)
diag23=sqrt((DX3-DX2)**2+(DY3-DY2)**2)
diag31=sqrt((DX1-DX3)**2+(DY1-DY3)**2)

#input/output in rads 
def rangeAngle(A):
    while A<0:
        A += 2*PI
    while A >= 2*PI:
        A -= 2*PI
    
    if A < 0: #just to be sure beacause we work with floats ...
        A=0
        
    return A



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
    #print("SCI X Y ", x, y)
    
    #there is a 2nd solution
    if dist!=Ra+Rb:
        x=cxc-h*(cyb-cya)/dist
        y=cyc+h*(cxb-cxa)/dist
        res.append([x,y])
    
    return res


if __name__ == '__main__':
    print(HIST_COLORS)
    print("Starting program")
    win = GraphWin("drawPosition",(TABLE_LEN+2*(22+80))/SCALE,(TABLE_HIGH+2*(22+80))/SCALE)
    win.autoflush = False
    win.setCoords(-80-22,-80-22,TABLE_LEN+80+22,TABLE_HIGH+80+22)
    table = Rectangle(Point(0,0), Point(TABLE_LEN,TABLE_HIGH))
    table.setFill(TABLE_COLOR)
    table.draw(win)
    #haut gauche
    t1 = Rectangle(Point(-80-22,TABLE_HIGH+22), Point(-22,TABLE_HIGH+22+80))
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
    t3 = Rectangle(Point(TABLE_LEN+22,TABLE_HIGH/2-80/2), Point(TABLE_LEN+22+80,TABLE_HIGH/2+80/2))
    t3.setFill(T_COLOR)
    t3.draw(win)
    d3 = Circle(D3_POINT, D_RADIUS)
    d3.setFill(D_COLOR)
    d3.setOutline(D_COLOR)
    d3.draw(win)
    
    # dessiner les carreaux du sol
    for i in range(10):
        jv=Line(Point(300*i+190,0), Point(300*i+190,TABLE_HIGH))
        jv.setOutline("grey")
        jv.draw(win)
        jv.setWidth(2)
    
    for j in range(6):
        jh=Line(Point(0,300*j+190), Point(TABLE_LEN,300*j+190))
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
    dir0line = Line(Point(0,0), Point(1,1))
    pos4=Circle(Point(0,0),1)
    pos5=Circle(Point(0,0),1)
    pos6=Circle(Point(0,0),1)
    dir0line_emb = Line(Point(0,0), Point(1,1))
    pos_emb =Circle(Point(0,0),1)
    pos4_emb=Circle(Point(0,0),1)
    pos5_emb=Circle(Point(0,0),1)
    pos6_emb=Circle(Point(0,0),1)
    
    serList = serial.tools.list_ports.comports()
    
    #for s in serList:
    #    print("-",s.description,"-",s.vid, s.pid)
    
    serList = [s for s in serList if (s.vid==1027 and s.pid==24577)]	
    if len(serList) != 1:
        print("Error did not found serial interface to use")
    else :
        ser = serial.Serial(serList[0].device,baudrate=115200, timeout=0)
        ser.reset_input_buffer()
        
        S = b""
        turretInfos=[[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]    
            
        loopTime =0
        #for i in range(1000):
        while True:    
            print("loop", time.time()-loopTime)
            loopTime=time.time()
            
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
                    if len(Sp) == 64:
                        try:
                            turretInfos = [ [int(Sp[7]),  int(Sp[10]), int(Sp[13])], 
                                            [int(Sp[17]), int(Sp[20]), int(Sp[23])], 
                                            [int(Sp[27]), int(Sp[30]), int(Sp[33])], 
                                            [int(Sp[37]), int(Sp[40]), int(Sp[43])], 
                                            [int(Sp[47]), int(Sp[50]), int(Sp[53])], 
                                            [int(Sp[57]), int(Sp[60]), int(Sp[63])]]
                            for i in range(6):
                                print(turretInfos[i][0], turretInfos[i][1], turretInfos[i][2])
                        except:
                            print("unexpected exception")
                    elif len(Sp) == 100:
                        try:
                            turretInfos = [ [int(Sp[7]),  int(Sp[10]), int(Sp[13]), int(Sp[15]), int(Sp[17]), int(Sp[19])], 
                                            [int(Sp[17+6]), int(Sp[20+6]), int(Sp[23+6]), int(Sp[31]), int(Sp[33]), int(Sp[35])], 
                                            [int(Sp[27+12]), int(Sp[30+12]), int(Sp[33+12]), int(Sp[47]), int(Sp[49]), int(Sp[51])], 
                                            [int(Sp[37+18]), int(Sp[40+18]), int(Sp[43+18]), int(Sp[63]), int(Sp[65]), int(Sp[67])], 
                                            [int(Sp[47+24]), int(Sp[50+24]), int(Sp[53+24]), int(Sp[79]), int(Sp[81]), int(Sp[83])], 
                                            [int(Sp[57+30]), int(Sp[60+30]), int(Sp[63+30]), int(Sp[95]), int(Sp[97]), int(Sp[99])]]
                            for i in range(6):
                                print(turretInfos[i][0], turretInfos[i][1], turretInfos[i][2])
                        except:
                            print("unexpected exception")
                    else:
                        print("bad split ", len(Sp))
                       
        
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
            L12 = Line(Point(0,b12),Point(TABLE_LEN,b12))
            L23 = Line(Point(-b23/a23,0),Point((TABLE_HIGH-b23)/a23, TABLE_HIGH))
            L31 = Line(Point(-b31/a31,0),Point((TABLE_HIGH-b31)/a31, TABLE_HIGH))
            L12.draw(win)
            L23.draw(win)
            L31.draw(win)
            
            # position of BTX
            X = int(((b12-b31)/a31 + (b12-b23)/a23 - (b31-b23)/(a31-a23))/3)
            Y = int((2*b12+(b31-a31*(b31-b23)/(a31-a23)))/3)
            
            
            # drawing
            pos.undraw() 
            pos = Circle(Point(X,Y),40)
            pos.setOutline("yellow")
            pos.setFill("red")
            pos.draw(win)
            
            print("main X Y ", X, Y)
            
            
            
            #calculate BTX angle with mean of 3 BRX viewing angles
            A1_rel = turretInfos[0][1]/10*2*PI/360
            A2_rel = turretInfos[1][1]/10*2*PI/360
            A3_rel = turretInfos[2][1]/10*2*PI/360
            A1_abs = 0 #declare the vars  #is in rads
            A2_abs = 0
            A3_abs = 0
            
            if R1 !=0 :
                A1_ = acos((X - DX1)/R1)
                A1_abs = PI - A1_rel - A1_
                #print("Alpha",A1_)
                # TODO fail safe
            
            if R2 != 0:
                A2_ = acos((X - DX2)/R2)
                A2_abs = PI - A2_rel + A2_
                #print("Beta",A2_)
 
            if R3 != 0:
                A3_ = asin((Y - DY3)/R3)
                A3_abs = - A3_rel - A3_
                #print("Gama",A3_)
                
            
            A1_abs = rangeAngle(A1_abs)
            A2_abs = rangeAngle(A2_abs)
            A3_abs = rangeAngle(A3_abs)
            
            
            xa = (cos(A1_abs) + cos(A3_abs) + cos(A3_abs) )/3
            ya = (sin(A1_abs) + sin(A3_abs) + sin(A3_abs) )/3
            A_abs = atan2(ya, xa)
            
            # drawing
            print("Angles 1 2 3 mean ", int(A1_abs*360/2/PI), int(A2_abs*360/2/PI), int(A3_abs*360/2/PI), int(A_abs*360/2/PI))
            #TODO to be confirmed for all
            dir0line.undraw()
            dir0line = Line(Point(X,Y),Point(X+70*cos(A_abs),Y+70*sin(A_abs)))
            dir0line.setWidth(5)
            dir0line.setFill("yellow") #TODO check if this could be done only at init (not erased by undraw)
            dir0line.draw(win)
            
            
            A4_rel = turretInfos[3][1]/10*2*PI/360
            A5_rel = turretInfos[4][1]/10*2*PI/360
            A6_rel = turretInfos[5][1]/10*2*PI/360
            
            #calculate distance/angle to opponent, position of opponent
            A4_abs = A4_rel + A_abs 
            R4_dx = int(turretInfos[3][0] * cos(A4_abs))
            R4_dy = int(turretInfos[3][0] * sin(A4_abs))
            
            X4 = X + R4_dx
            Y4 = Y + R4_dy
            print("R4", R4_dx, R4_dy, X4, Y4)
            
            pos4.undraw() 
            pos4 = Circle(Point(X4,Y4),40)
            pos4.setOutline("yellow")
            pos4.setFill("blue")
            pos4.draw(win)
            
            #calculate distance/angle to opponent, position of opponent
            A5_abs = A5_rel + A_abs 
            R5_dx = int(turretInfos[4][0] * cos(A5_abs))
            R5_dy = int(turretInfos[4][0] * sin(A5_abs))
            
            X5 = X + R5_dx
            Y5 = Y + R5_dy
            
            pos5.undraw() 
            pos5 = Circle(Point(X5,Y5),40)
            pos5.setOutline("yellow")
            pos5.setFill("dodger blue")
            pos5.draw(win)
            
            #calculate distance/angle to opponent, position of opponent
            A6_abs = A6_rel + A_abs 
            R6_dx = int(turretInfos[5][0] * cos(A6_abs))
            R6_dy = int(turretInfos[5][0] * sin(A6_abs))
            
            X6 = X + R6_dx
            Y6 = Y + R6_dy
            
            pos6.undraw() 
            pos6 = Circle(Point(X6,Y6),40)
            pos6.setOutline("yellow")
            pos6.setFill("deep sky blue")
            pos6.draw(win)
            
            if len(turretInfos[0])>=6: #this is the embedded calculation
                X = turretInfos[0][4]
                Y = turretInfos[0][5]
                A_abs = turretInfos[0][3]*2*PI/360
                dir0line_emb.undraw()
                dir0line_emb = Line(Point(X,Y),Point(X+70*cos(A_abs),Y+70*sin(A_abs)))
                dir0line_emb.setWidth(2)
                dir0line_emb.setFill("red") #TODO check if this could be done only at init (not erased by undraw)
                dir0line_emb.draw(win)
            
                pos_emb.undraw() 
                pos_emb = Circle(Point(X,Y),50)
                pos_emb.setOutline("yellow")
                pos_emb.draw(win)
                
                X = turretInfos[3][4]
                Y = turretInfos[3][5]
                pos4_emb.undraw() 
                pos4_emb = Circle(Point(X,Y),50)
                pos4_emb.setOutline("yellow")
                pos4_emb.draw(win)
                
                X = turretInfos[4][4]
                Y = turretInfos[4][5]
                pos5_emb.undraw() 
                pos5_emb = Circle(Point(X,Y),50)
                pos5_emb.setOutline("yellow")
                pos5_emb.draw(win)
                
                X = turretInfos[5][4]
                Y = turretInfos[5][5]
                pos6_emb.undraw() 
                pos6_emb = Circle(Point(X,Y),50)
                pos6_emb.setOutline("yellow")
                pos6_emb.draw(win)
                
            #time.sleep(0.1) #100ms sleep between updates
            #win.flush()
            update()  # update the window as win.autoflush = False
            time.sleep(0.01)
        ser.close()
        print("Program ended, click into the window to close !!!")
        win.getMouse()
    
    
