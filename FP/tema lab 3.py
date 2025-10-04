def print_menu():
    """
    Functia afiseaza optiunile disponibile utilizatorului
    input: -
    output: -
    """
    print("1. Citire lista")
    print("2. Afisarea secventei de lungime maxima care are toate elementele egale")
    print("3. Afisarea secventei de lungime maxima in care oricare doua elemente consecutive difera printr-un numar prim")
    print("4. Afisarea secventei de lungime maxima in care sunt toate distincte intre ele")
    print("5. Iesirea din aplicatie")

def citire_lista():
    """
    Functia citeste de la tastatura un numar n si o lista de n numere intregi
    input: -
    output: n=numarul de numere din lista , numbers=lista de numere
    """
    print()
    print("Introduceti lungimea listei pe care doriti sa o cititi:")
    n = int(input("n = "))
    numbers = []
    print("Introduceti lista:")
    for i in range(n):
        number = int(input(f"numbers[{i}] = "))
        numbers.append(number)
    return n, numbers


def sunt_egale(a: int, b: int):
    """
    Functia verifica daca 2 numere oarecare sunt egale
    input: a si b numerele care se compara
    output: True daca sunt egale, False in caz contrar
    """
    if a==b:
        return True
    else:
        return False


def determina_secventa_egale(numbers: list, n: int):
    """
    Functia determina si afiseaza secventa de lungime maxima in care toate elementele sunt egale
    input: numbers=lista de numere citita, n=lungimea listei
    output: secventa maxima sau None in cazul in care nu exista
    """
    p1=p2=0     #p1=pozitia primului numar din secventa maxima si p2 este pozitia primului numar din secventa curenta
    lgmax=0  #lungimea secventei maxime
    lg=1    #lungimea secventei curente
    secventa_nr_egale=[]
    for i in range(1,n):
        if sunt_egale(numbers[i],numbers[i-1])==True:
            lg+=1
        else:
            if lg>lgmax:
                lgmax=lg
                p1=p2
            p2=i
            lg=1
    if lg>lgmax:#verific daca nu cumva ultima secventa este cea maxima
        lgmax=lg
        p1=p2
    if lgmax==1:
        return None
    else:
        secventa_nr_egale=numbers[p1:p1+lgmax]
        return secventa_nr_egale
            

def prim(x: int):
    """
    Functia determina daca un numar este prim
    input: x
    output: 0 daca nu este prim, 1 daca este prim
    """
    if x<2:
        return False
    elif x==2:
        return True
    for i in range(2,x//2+1):
        if x%i==0:
            return False
    return True


def diferenta(a,b:int):
    """
    Functia determina modulul diferentei a doua numere
    input: a,b
    output: diferenta in modul a celor 2 numere
    """
    if a>b:
        return a-b
    else:
        return b-a


def determina_secventa_prim(numbers: list, n: int):
    """
    Functia determina si afiseaza secventa de lungime maxima in care oricare doua elemente consecutive difera printr-un numar prim
    input: numbers=lista de numere citita, n=lungimea listei
    output: secventa maxima sau None in cazul in care nu exista
    """
    p1=p2=0  #p1=pozitia primului numar din secventa maxima, p2= pozitia primului element din secventa curenta
    lgmax=0  #lungimea secventei maxime
    lg=1   #lungimea secventei curente
    for i in range(1,n):
        dif=diferenta(numbers[i-1],numbers[i])
        if prim(dif)==True:
            lg+=1
        else:#s-a incheiat secventa curenta
            if lg>lgmax:
                lgmax=lg
                p1=p2
            p2=i
            lg=1
    if lg>lgmax:#verific daca nu cumva ultima secventa este cea maxima
        lgmax=lg
        p1=p2
    if lgmax==1:
        return None
    else:
        secventa_difP=numbers[p1:p1+lgmax]
        return secventa_difP



def determina_secventa_distincte(numbers: list, n: int):
    """
    Functia determina si afiseaza secventa de lungime maxima in care toate elementele sunt distincte intre ele
    input: numbers=lista de numere citita, n=lungimea listei
    output: secventa maxima sau None in cazul in care nu exista
    """
    p1=p2=0  #p1=pozitia primului numar din secventa maxima, p2=pozitia primului nr din secv curenta
    lgmax=0
    lg=1
    v=[]
    v.append(numbers[0])
    for i in range(1,n):
        if numbers[i] not in v:
            lg+=1
            v.append(numbers[i])
        else:#s-a incheiat secventa curenta
            if lg>lgmax:
                lgmax=lg
                p1=p2#se modifica pozitia primului element din secventa
            v=[]
            v.append(numbers[i])
            p2=i
            lg=1
    if lg>lgmax:#se verifica daca ultima secventa este cea maxima
            lgmax=lg
            p1=p2
    if lgmax==1:
        return None
    else:
        secventa_distincte=numbers[p1:p1+lgmax]
        return secventa_distincte


 
class InvalidCommand(BaseException):
    """
    clasa folosita pentru a atentiona utilizatorul
    aplicatiei ca optiunea aleasa nu este disponibila
    """
    pass


def primeste_comanda(option,numbers,n):
    """
    Functia retine comanda introdusa de utilizator si apeleaza functia corespunzatoare
    input: option
    output: True daca programul s-a incheiat, False daca nu
    raises: InvalidCommand cand optiunea introdusa>5
    """
    match option:
        case 1:
            n,numbers = citire_lista()     #Citeste lungimea listei si lista de numere
            print("Lista a fost citita cu succes!")
            print("Lista citita:", numbers)

        case 2:
            if numbers==[]:
                print("Mai intai trebuie sa cititi lista. Introduceti optiunea 1!")
            else:
                x=determina_secventa_egale(numbers, n)
                print()
                if x!=None:
                    print("Secventa de lungime maxima cu toate elementele egale este:")
                    print(x)
                else:
                    print("Nu exista o astfel de secventa!")

        case 3:
            if numbers==[]:
                print("Mai intai trebuie sa cititi lista. Introduceti optiunea 1!")
            else:
                x=determina_secventa_prim(numbers,n)
                print()
                if x!=None:
                    print("Secventa de lungime maxima cu diferenta a oricaror doua elemente consecutive un numar prim este:")
                    print(x)
                else:
                    print("Nu exista o astfel de secventa!")

        case 4:
            if numbers==[]:
                print("Mai intai trebuie sa cititi lista. Introduceti optiunea 1!")
            else:
                x=determina_secventa_distincte(numbers,n)
                print()
                if x!=None:
                    print("Secventa de lungime maxima in care toate elementele sunt distincte intre ele este:")
                    print(x)
                else:
                    print("Nu exista o astfel de secventa!")

        case 5:
            print("Programul s-a incheiat cu succes!")
            return True,numbers,n

        case _:
            raise InvalidCommand(f"Comanda {option} nu este valabila! Incercati o comanda dintre cele prezente.")
    return False,numbers,n


def start_ui():
    """
    porneste interfata grafica cu utilizatorul
    input: -
    output: -
    """
    numbers = []  # Lista de numere initiala, goala
    n = 0  # Lungimea listei initial, zero
    while True:
        print_menu()
        print()
        try:
            option = int(input("Introduceti optiunea: "))
            ok,numbers,n=primeste_comanda(option,numbers,n)
            if ok:
                break
        except ValueError: #Prinde exceptia in care s-a introdus un string in loc de un numar 
            print("Introduceti un numar intreg!")
            print()
        except InvalidCommand as ex:  #Prinde exceptia in care utilizatorul a introdus o optiune care nu este disponibila
            print(ex)
            print()


def testeaza_secv_egale():
    """
    Functia contine teste ale functiei care determina si afiseaza secventa de lungime maxima cu toate elementele egale
    """
    assert(determina_secventa_egale([1,1,7,8,2,2,2,9,2,6],10)==[2,2,2])
    assert(determina_secventa_egale([1,1,1,1,9,8,6,3,3,3,7,5],12)==[1,1,1,1])
    assert(determina_secventa_egale([1,1,1,2,5,3,3,3,3,9,10,4,4,4,4,4,4],17)==[4,4,4,4,4,4])
    assert(determina_secventa_egale([1,2,3,4,5],5)==None)

def testeaza_secv_difP():
    """
    Functia contine teste ale functiei care determina si afiseaza secventa de lungime maxima unde diferenta oricaror 2 numere consecutive este un numar prim
    """
    assert(determina_secventa_prim([5,8,9,7,14,37,35,9,1],9)==[9,7,14,37,35])
    assert(determina_secventa_prim([7,9,6,4,3,9,13],7)==[7,9,6,4])
    assert(determina_secventa_prim([1,2,3,7,5,8,13,18],8)==[7,5,8,13,18])
    assert(determina_secventa_prim([1,2,3,4,5],5)==None)


def testeaza_secv_distincte():
    """
    Functia contine teste ale functiei care determina si afiseaza secventa de lungime maxima unde toate numerele sunt distincte
    """
    assert(determina_secventa_distincte([1,2,3,2,4,4,6,8,9,9,1,1],12)==[4,6,8,9])
    assert(determina_secventa_distincte([1,1,1,4,3,3,9,6,5],9)==[3,9,6,5])
    assert(determina_secventa_distincte([1,3,8,7,7,8,13,7,7],9)==[1,3,8,7])
    assert(determina_secventa_distincte([1,1,1,1],4)==None)

def test():
    """
    Functia verifica daca programul trece de testele functiilor principale din program
    """
    testeaza_secv_egale()
    testeaza_secv_difP()
    testeaza_secv_distincte()
    
def main():
    test()
    start_ui()

if __name__=="__main__":
    main()
