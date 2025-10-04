import random
import string

def genereaza_titlu():
    """
    Functia alege din lista de titluri un titlu random
    """
    titluri=['Titanic','Singur acasa','Morometii','Barbie','Oppenheimer','Crima in Orient Express']
    return random.choice(titluri)

def genereaza_descriere():
    """
    Functia alege din lista de descriere o descriere random
    """
    descriere=["O poveste de dragoste","Povestea destramarii unei familii de tarani","Crearea unei bombe atomice",
               "Rezolvarea unui caz de crima","Un copil ramas singur de sarbatori"]
    return random.choice(descriere)

def genereaza_gen():
    """
    Functia alege din lista de genuri un gen random
    """
    genuri=["romantic","actiune","drama","comedie","istoric","thriller","politist"]
    return random.choice(genuri)

def genereaza_nume():
    """
    Functia alege din lista de nume un nume random
    """
    nume=["Pop Maria","Ionescu Ion","Popescu Ion","Popescu Maria","Popescu Vasile"]
    return random.choice(nume)

#def genereaza_cnp():
    #cnp=['1234567890123','1123456789012','3456789012345','2234567890123','6789012345678']
    #return random.choice(cnp)

def genereaza_cnp():
    """
    Functia genereaza un cnp random
    """
    cnp=[]
    for i in range(13):
        cnp.append(random.choice(string.digits))
    return ''.join(cnp)
