import datetime

from consola.consola import Consola
from domain.validator import Validator
from repository.repository import Repository
from service.service import Service


def main():
    repo=Repository('date_intrare/date.txt')
    validator=Validator()
    service=Service(repo,validator)
    consola=Consola(service)
    consola.start()

if __name__ == '__main__':
    main()


