id=[]
at=[]
bt=[]
ct=[]
tat=[]
wt=[]
u_bt=[]

n=int(input("Enter the no. of process"))
for i in range(n):
    id.append(i)
    at.append(int(input("Enter arrival time")))
    bt.append(int(input("Enter bust time")))
    u_bt.append(bt[i])
    ct.append(0)
    tat.append(0)
    wt.append(0)

tq=int(input("Enter Time Quantum"))
rq=[]
cur=0
a_tat=0
a_wt=0
c=0
c_id=0
if(at[0]>=cur):
    cur=at[0]
    rq.append(id[0])
    print(id[0],"-> ",end='')
while(c!=n):
    c_id=rq[0]
    if(bt[c_id]<=tq):
        rq.pop(0)
        c+=1
        cur+=bt[c_id]
        for i in range(c_id+1,n):
            if(at[i]>cur-bt[c_id] and at[i]<=cur):
                rq.append(i)
                print(id[i], "-> ", end='')
        ct[c_id]=cur
        tat[c_id]=ct[c_id]-at[c_id]
        wt[c_id]=tat[c_id]-u_bt[c_id]
        bt[c_id]=0
        a_tat += tat[c_id]
        a_wt += wt[c_id]
    else:
        rq.pop(0)
        bt[c_id]-=tq
        cur+=tq
        for i in range(c_id+1,n):
            if(at[i]>cur-tq and at[i]<=cur):
                rq.append(i)
                print(i, "-> ", end='')
        rq.append(c_id)
        print(c_id, "-> ", end='')
print(id,at,bt,u_bt,ct,tat,wt)
