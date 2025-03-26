def insertion_sort(lista,key=lambda x:x,reverse=False):
    for i in range(1, len(lista)):
        ind = i - 1
        a = lista[i]
        while ind >= 0 and ((not reverse and key(a)<key(lista[ind])) or (reverse and key(a)>key(lista[ind]))):
            lista[ind + 1] = lista[ind]
            ind -= 1
        lista[ind + 1] = a

def comb_sort(lista,key=lambda x:x,reverse=False):
    sm=0 #pozitia elementului cu care se compara cel curent
    shrink=1.3 #factorul de micsorare
    gap=len(lista) #distanta dintre elementele care se compara
    sorted=False
    while not sorted:
        gap=int(gap/shrink)
        if gap <=1:
            gap=1
            sorted=True
        for i in range(len(lista)-gap):
            sm=gap+i #pozitia elementului cu care se compara cel curent
            if ((not reverse and key(lista[i])>key(lista[sm])) or (reverse and key(lista[i])<key(lista[sm]))):
                lista[i],lista[sm]=lista[sm],lista[i]
                sorted=False

