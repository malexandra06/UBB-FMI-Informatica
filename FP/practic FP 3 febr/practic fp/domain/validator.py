class Validator:
    def valideaza(self,melodie):
        errors=[]
        data=melodie.get_data()
        if len(data)!=10:
            errors.append("Data nu este completa!")
        data = data.split(".")
        if len(data)!=3:
            errors.append("Data nu are formatul cerut!")
        if int(data[0])>31 or int(data[0])<=0:
            errors.append("Ziua nu poate avea mai mult de 31 de zile sau sa fie negativa!")
        if int(data[1])>12 or int(data[1])<=0:
            errors.append("Luna poate fi doar 1-12!")
        if int(data[2])<=0 or int(data[2])>2025:
            errors.append("An invalid!")
        if melodie.get_gen() not in ['Rock','Pop','Jazz']:
            errors.append("Genul nu poate fi decat Rock,Pop sau Jazz!")
        if len(errors)!=0:
            errors_message='\n'.join(errors)
            raise ValueError(errors_message)