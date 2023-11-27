import tkinter as tk
import serial
import threading



#ser=serial.Serial("COM10",9600)
import tkinter.messagebox
ser=0

i=1
root=tk.Tk()
root.geometry('398x240')

cbn="0"
cled="关"

cpwm="关"
var=tk.StringVar()

l1=tk.Label(root,textvariable=var)
l1.pack(side="bottom")
var.set("台灯亮度 : "+cbn+"    "+"台灯颜色 : "+cled+"    "+"呼吸颜色 : "+cpwm)


    
l2=tk.Label(root,text="状态 : 未连接")
l2.place(x=12,y=10)

on_hit=False
def open_ser():
    global on_hit
    global ser
    if on_hit==False:
        on_hit=True
        ser=serial.Serial("COM13",9600)
        l2.config(text="状态 : 连接成功" )
        ser.open()

    else:
        on_hit=False
         
        l2.config(text="状态 : 连接断开" )
        ser.close()
       

b1 = tk.Button(root,text='总开关',
              font=("Arial,15"),width=6,height=2,
              command=open_ser)   
b1.place(x=15,y=50)

########################################计时器 start
timer_num=1
var_button=tk.StringVar()
var_button.set("计时开启")
def timer_on():
    var_button.set("计时开启")


    
def timer_1 (time):
    print("success"+str(time))
    threading.Timer(1*time,timer_on,args=[]).start()
    timer_num=+1

e0=tk.Entry(root)
e0.place(x=10,y=120)  

def cib( b):
    c=list('ABNCEF')
    if(b<10):
        return b
    else :
        d=b-10
        return c[d]
        

on_hit1=False
def counter():
    global on_hit1
    if ser==0:
        tkinter.messagebox.showerror(title="错误", message="还没有连接喔")

    if on_hit1==False:
        a=int(str(e0.get()))   

        if a <60 :
            b='0'
            if a>0 and a<=12:
                b="C"+str(cib(a+2))    
            elif a<28:
                b="D"+str(cib(a-12))
            elif a<44:
                b="E"+str(cib(a-28))
            elif a<60:
                b="F"+str(cib(a-44))
            if a==10:
                b="AF"
            timer_1(a)
            ser.write(bytes([int(b,16)]))

            var_button.set("计时暂停")   
            on_hit1=True
        else:
            tkinter.messagebox.showerror(title="计时错误", message="要输入小于60的数字哦")
            
  

    else:
        on_hit1=False
        ser.write(b"\xC0")
        var_button.set("计时开启")
   
 

b2 = tk.Button(root,textvariable=var_button,
              width=7,height=1,font="1",
              command=counter)   
b2.place(x=15,y=145)

########################################计时器end

coloes=list("关红绿蓝白青紫黄")

def ccbn(v):
    global cled
    global cpwm
    global cbn
    a=int(v)
    cbn=str(v)
    var.set("台灯亮度 : "+cbn+"    "+"台灯颜色 : "+cled+"    "+"呼吸颜色 : "+cpwm)
    if(a==100):
        a=99
    ser.write(bytes([int(str(a),16)]))

    
def ccled(v):
    global cled
    cled = coloes[int(v)]
    global cbn
    global cpwm
    var.set("台灯亮度 : "+cbn+"    "+"台灯颜色 : "+cled+"    "+"呼吸颜色 : "+cpwm)
    ser.write(bytes([int("B"+str(v),16)]))

def ccpwm(v):
    global cpwm
    cpwm = coloes[int(v)]
    global cbn
    global cled
    var.set("台灯亮度 : "+cbn+"    "+"台灯颜色 : "+cled+"    "+"呼吸颜色 : "+cpwm)
    ser.write(bytes([int("A"+str(v),16)]))


sc0 = tk.Scale(root,label='台灯颜色',from_=0,to=7,
              orient=tk.VERTICAL,length=200,
              showvalue=0,tickinterval=0,resolution=1,
              command=ccled)
sc0.place(x=210)



sc1 = tk.Scale(root,label='呼吸颜色',from_=0,to=7,
              orient=tk.VERTICAL,length=200,
              showvalue=0,tickinterval=0,resolution=1,
              command=ccpwm)
sc1.place(x=300)



sc2 = tk.Scale(root,label='台灯亮度',from_=0,to=99,
              orient=tk.VERTICAL,length=200,
              showvalue=0,tickinterval=33,resolution=1,
              command=ccbn)
sc2.place(x=100)


print("finish")#检查 UI是否彻底执行

root.mainloop()


