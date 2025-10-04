def prim(x):
    if x<2:
        return 0
    if x==2:
        return 1
    else:
        for i in range(2,x//2+1):
            if x%i==0:
                return 0
        return 1

def det_Secv(l):
    v=[0]*len(l)
    if l[-1]%2==0:
        v[-1]=1
    for i in range(len(l)-2,-1,-1):
        if l[i]%2==0:
            v[i]=1
            for j in range(i+1,len(l)):
                if l[i]>=l[j] and v[i]<v[j]+1:
                    v[i]=v[j]+1

    max=0
    imax=0
    for i in range(len(l)):
        if v[i]>max:
            max=v[i]
            imax=i

    secv=[]
    secv.append(l[imax])
    i=imax+1
    while i<len(l):
        if l[i]<=l[imax] and v[i]+1==v[imax] and l[i]%2==0:
            secv.append(l[i])
            imax=i
        i=i+1
    return v,secv

def f(l):
    if l==None or l==[]: raise ValueError()
    aux=l[0]-1
    for e in l:
        if (aux-e)>=0:
            return False
        aux=e
    return True

def f(l):
    ind=[]
    for i in range(len(l)):
        ind.append(i)
    return ind

def produs(l,left,right):
   if left>right:
       return 1
   if left==right:
       if left%2==0:
            return l[right]
       else: return 1
   m=(left+right)//2
   prod_left=produs(l,left,m)
   prod_right=produs(l,m+1,right)
   return prod_left*prod_right

assert produs([1,2,3,4,5],0,4)==15


