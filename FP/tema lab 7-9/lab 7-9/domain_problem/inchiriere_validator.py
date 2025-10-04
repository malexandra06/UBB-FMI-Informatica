from exceptions.exceptions import ValidationException
class InchiriereValidator:
    def validare(self, id_client,id_film, inchiriat,repo_client,repo_f,repo_i):
        errors=[]
        ok=0
        for i in repo_client.get_all():
            if i.get_id()==id_client:
                ok=1
        if ok==0:
            errors.append("Clientul introdus nu exista!")
        ok=0
        for i in repo_f.get_all():
            if i.get_id()==id_film:
                ok=1
        if ok==0:
            errors.append("Filmul introdus nu exista!")
        ok=0
        for i in repo_i.get_all():
            if i.get_id_client()==id_client and i.get_id_film()==id_film:
                ok=1
        if ok==1:
            errors.append("Inchirierea cu id-urile date se afla deja in lista!")
        if inchiriat!='True' and inchiriat!='False':
            errors.append("Inchirierea trebuie sa fie True sau False!")
        if len(errors)>0:
            error_message='\n'.join(errors)
            raise ValidationException(error_message)
