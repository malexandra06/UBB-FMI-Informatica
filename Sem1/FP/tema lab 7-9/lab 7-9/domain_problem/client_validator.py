from domain_problem.clients import Client
from exceptions.exceptions import ValidationException

class ClientValidator:
    """
    Clasa care verifica daca datele introduse pentru a forma un obiect de tip Client sunt valide
    """
    def validate(self, client: Client):
        errors = []
        if len(client.get_name()) <2:
            errors.append("Numele clientului trebuie sa aiba cel putin 2 caractere!")
        if len(client.get_cnp())!=13:
            errors.append("CNP invalid. CNP-ul clientului trebuie sa aiba 13 caractere!")
        ok=1
        i=0
        while ok and i<len(client.get_cnp()):
            if client.get_cnp()[i]<'0' or client.get_cnp()[i]>'9':
                ok=0
            i+=1
        if ok==0:
            errors.append("CNP invalid! CNP-ul contine doar cifre!")
        if len(errors)>0:
            error_message = '\n'.join(errors)
            raise ValidationException(error_message)