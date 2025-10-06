#include "produs.h"
#include "RepoProduse.h"
#include <assert.h>
#include "teste.h"
#include "validator.h"
#include "exception.h"
#include "RepoCos.h"
#include "service.h"
#include <cassert>
#include <iostream>
//testam functiile din clasa Produs
void Tests::testDomain()
{
    Produs p1 = Produs("lapte", "aliment", "albalact", 10);
    assert(p1.getNume() == "lapte");
    assert(p1.getTip() == "aliment");
    assert(p1.getProducator() == "albalact");
    assert(p1.getPret() == 10);
    Produs p2 = Produs("lapte", "aliment", "albalact", 10);
    assert(p1.equal(p2) == true);
    Produs p3 = Produs("lapte", "aliment2", "albalact", 10);
    assert(p1.equal(p3) == false);

    p1.setNume("branza");
    assert(p1.getNume() == "branza");
    p1.setTip("lichid");
    assert(p1.getTip() == "lichid");
    p1.setProducator("covalact");
    assert(p1.getProducator() == "covalact");
    p1.setPret(30);
    assert(p1.getPret() == 30);
}

void Tests::testValidator()
{
    Validator validator;

    // Test valid
    validator.valideaza("Laptop", "Electronics", "Dell", 2500);
    std::cout << "Test valid trecut.\n";

    // Test nume invalid
    try {
        validator.valideaza("", "Tip", "Producator", 100);assert(false); // nu ar trebui să ajungă aici
    }
    catch (const ValidatorException& e) {
        std::string mesaj = e.what();
        assert(mesaj.find("Denumirea trebuie") != std::string::npos);
    }

    // Test tip invalid
    try {
        validator.valideaza("Nume", "", "Producator", 100); assert(false);
    }
    catch (const ValidatorException& e) {
        std::string mesaj = e.what();
        assert(mesaj.find("Tipul trebuie") != std::string::npos);
    }

    // Test producator invalid
    try {
        validator.valideaza("Nume", "Tip", "", 100);assert(false);
    }
    catch (const ValidatorException& e) {
        std::string mesaj = e.what();
        assert(mesaj.find("Producatorul trebuie") != std::string::npos);
    }

    // Test pret invalid
    try {
        validator.valideaza("Nume", "Tip", "Producator", -10);assert(false);
    }
    catch (const ValidatorException& e) {
        std::string mesaj = e.what();
        assert(mesaj.find("Pret invalid") != std::string::npos);
    }

    // Test toate invalide
    try {
        validator.valideaza("", "", "", -5); assert(false);
    }
    catch (const ValidatorException& e) {
        std::string mesaj = e.what();
        assert(mesaj.find("Denumirea") != std::string::npos);
        assert(mesaj.find("Tipul") != std::string::npos);
        assert(mesaj.find("Producatorul") != std::string::npos);
        assert(mesaj.find("Pret invalid") != std::string::npos);
    }

    std::cout << "Toate testele pentru Validator au trecut cu succes.\n";
}

void Tests::testRepoProduse() {
    RepoProduse repo;
    repo.adauga("t1", "t1", "t1", 10);
    repo.adauga("t2", "t2", "t2", 10);
    repo.adauga("t3", "t3", "t3", 10);

    assert(repo.len() == 3);

    vector<Produs> list = repo.getAll();
    assert(list.size() == 3);
    assert(repo.find("t1") == 0);
    assert(repo.find("t6") == -1);

    try {
        repo.adauga("t1", "t6", "t7", 90);
    }
    catch (RepoProduseException) {
        assert(true);
    }
    repo.sterge("t2");
    assert(repo.len() == 2);
    try {
        repo.sterge("t100");assert(false);
    }
    catch (RepoProduseException) {
        assert(true); //ar trebui sa arunce exceptie
    }

    repo.modifica("t1_mod", "t1_mod", 20, "t1");
    try {
        repo.modifica("t1_mod", "t1_mod", 20, "t100");assert(false);
    }
    catch (RepoProduseException) {
        assert(true); //ar trebui sa arunce exceptie
    }
    assert(repo.getAll()[0].getNume() == "t1");
    assert(repo.getAll()[0].getTip() == "t1_mod");
    assert(repo.getAll()[0].getProducator() == "t1_mod");
    assert(repo.getAll()[0].getPret() == 20);
}
void Tests::testRepoCos() {
    // Testează constructorul și cosul gol
    RepoCos cos;
    assert(cos.getAll().size() == 0);

    // Testează adăugarea de produse
    cos.adaugaCos(Produs("laptop", "electronice", "Dell", 3000));
    cos.adaugaCos(Produs("telefon", "electronice", "Samsung", 2000));
    assert(cos.getAll().size() == 2);
    assert(cos.getAll()[0].getNume() == "laptop");
    assert(cos.getAll()[1].getPret() == 2000);
    assert(cos.getSuma() == 5000);
    try {
        cos.adaugaCos(Produs("laptop", "electronice", "Dell", 3000));
    }
    catch (const RepoCosException& e){
        std::string mesaj = e.what();
        assert(mesaj.find("Produs deja existent") != std::string::npos);
    }
    // Testează găsirea produselor
    assert(cos.find("laptop") == 0);
    assert(cos.find("telefon") == 1);
    assert(cos.find("inexistent") == -1);

    // Testează golirea coșului
    cos.golesteCos();
    assert(cos.getAll().size() == 0);
    assert(cos.getSuma() == 0);
    // Testează adăugarea aleatoare
    vector<Produs> produseDisponibile = {
        Produs("pix", "birotica", "Bic", 5),
        Produs("caiet", "birotica", "Oxford", 10),
        Produs("stilou", "birotica", "Parker", 500)
    };

    cos.adaugaRandom(5, produseDisponibile);
    assert(cos.getAll().size() == 5); // Verifică că s-au adăugat exact 2 produse
}
void Tests::testService()
{
    RepoFileProduse repo("test.txt");
    RepoCos cos;
    ServiceProd service(repo,cos);
    service.adauga("t1_mod", "Electronic", "Dell", 3000);
    service.adauga("Telefon", "Electronic", "Samsung", 2000);
    service.adauga("Frigider", "Electrocasnic", "LG", 2500);
    service.adauga("Laptop2", "Electronic", "HP", 3200);
    assert(service.len() == 4);
    vector<Produs>list = service.getAll();
    assert(list.size() == 4);
    assert(service.find("Telefon") == 1);
    try {
        int p = service.find("scn"); assert(false);
    }
    
        catch (ServiceException& e){assert(true);}
        
    service.sterge("Laptop2");
    assert(service.len() == 3);
    service.modifica("t1_mod", "t1_mod", 3000, "t1_mod");
    Produs test = service.getAll()[0];
    assert(test.getNume() == "t1_mod");
    assert(test.getTip() == "t1_mod");
    assert(test.getProducator() == "t1_mod");
    assert(test.getPret() == 3000);

    vector<Produs> rezultat2 = service.filtrare(Criteriu::NUME,"t1_mod");

    assert(rezultat2.size() == 1);

    rezultat2 = service.filtrare(Criteriu::TIP, "Electronic");
    assert(rezultat2.size() == 1);

    rezultat2 = service.filtrare(Criteriu::PRODUCATOR, "LG");
    assert(rezultat2.size() == 1);

    rezultat2 = service.filtrarePret(3000);
    assert(rezultat2.size() == 1);

    vector<Produs> rezultat3 = service.sortare(CriteriuSortare::NUME_S);
    
    assert(rezultat3[0].getNume() == "Frigider");
    assert(rezultat3[1].getNume() == "Telefon");
    assert(rezultat3[2].getNume() == "t1_mod");

    rezultat3 = service.sortare(CriteriuSortare::PRET);

    assert(rezultat3[0].getPret() == 2000);
    assert(rezultat3[1].getPret() == 2500);
    assert(rezultat3[2].getPret() == 3000);

    rezultat3 = service.sortare(CriteriuSortare::NUME_TIP);
    assert(rezultat3[0].getNume() == "Frigider");
    assert(rezultat3[1].getNume() == "Telefon");
    assert(rezultat3[2].getTip() == "t1_mod");
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testServiceCos()
{
    // Pregătim testele
    RepoFileProduse repo("test.txt");
    RepoCos cos;
    ServiceProd service(repo, cos);

    // Adăugăm produse pentru teste
    repo.adauga("laptop", "electronice", "Dell", 3000);
    repo.adauga("telefon", "electronice", "Samsung", 2000);
    repo.adauga("carte", "biblioteca", "Humanitas", 50);
    repo.adauga("frigider", "electrocasnice", "Samsung", 1000);
    repo.adauga("DEX", "biblioteca", "Humanitas", 80);
    // Test 1: Adăugare produs în coș
    service.adaugaCos("laptop");
    assert(service.getAllCos().size() == 1);
    assert(service.getAllCos()[0].getNume() == "laptop");
    assert(service.sumaTotala() == 3000);
    // Test 3: Adăugare alt produs
    service.adaugaCos("telefon");
    assert(service.getAllCos().size() == 2);
    assert(service.sumaTotala() == 5000);

    // Test 5: Adăugare aleatoare
    service.adaugaRandom(2);
    assert(service.getAllCos().size() == 2);

    // Test 6: Adăugare prea multe produse (ar trebui să arunce excepție)
    try {
        service.adaugaRandom(100);
    }
    catch (const ServiceException) {
        assert(true);
    }

    // Test 7: Adăugare produs inexistent (ar trebui să arunce excepție)
    try {
        service.adaugaCos("inexistent");
    }
    catch (const ServiceException) {
        assert(true);
    }

    // Curățare după teste
    service.golesteCos();
    assert(service.sumaTotala() == 0);
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testMap()
{
    // Pregătim testele
    RepoFileProduse repo("test.txt");
    RepoCos cos;
    ServiceProd service(repo, cos);

    // Adăugăm produse pentru teste
    repo.adauga("laptop", "electronice", "Dell", 3000);
    repo.adauga("telefon", "electronice", "Samsung", 2000);
    repo.adauga("carte", "biblioteca", "Humanitas", 50);
    repo.adauga("frigider", "electrocasnice", "Samsung", 1000);
    repo.adauga("DEX", "biblioteca", "Humanitas", 80);
    service.adaugaCos("laptop");
    service.adaugaCos("telefon");
    service.adaugaCos("carte");
    service.adaugaCos("frigider");
    service.adaugaCos("DEX");
    map <string, int> raport = service.raportTip();
    assert(raport["electronice"] == 2);
    assert(raport["biblioteca"] == 2);
    assert(raport["electrocasnice"] == 1);
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testMap2()
{
    RepoFileProduse repo("test.txt");
    RepoCos cos;
    ServiceProd service(repo, cos);

    // Adăugăm produse pentru teste
    repo.adauga("laptop", "electronice", "Dell", 3000);
    repo.adauga("telefon", "electronice", "Samsung", 2000);
    repo.adauga("carte", "biblioteca", "Humanitas", 50);
    repo.adauga("frigider", "electrocasnice", "Samsung", 1000);
    repo.adauga("DEX", "biblioteca", "Humanitas", 80);
    map <string, int> raport = service.raportTipProduse();
    assert(raport["electronice"] == 2);
    assert(raport["biblioteca"] == 2);
    assert(raport["electrocasnice"] == 1);
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testReadAllFromFile() {
    std::ofstream fout("test.txt");
    fout << "test1,test11,test111,12\n";
    fout << "test2,test22,test222,10\n";
    fout.close();

    RepoFileProduse repositoryFile{ "test.txt" };
    assert(repositoryFile.getAll().size() == 2);
    assert(repositoryFile.getAll()[0].getNume() == "test1");
    assert(repositoryFile.getAll()[0].getTip() == "test11");
    assert(repositoryFile.getAll()[0].getProducator() == "test111");
    assert(repositoryFile.getAll()[0].getPret() == 12);

    assert(repositoryFile.getAll()[1].getNume() == "test2");
    assert(repositoryFile.getAll()[1].getTip() == "test22");
    assert(repositoryFile.getAll()[1].getProducator() == "test222");
    assert(repositoryFile.getAll()[1].getPret() == 10);

    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testWriteToFile() {
    std::ofstream fout("test.txt");
    fout << "test1,test11,test111,12\n";
    fout << "test2,test22,test222,10\n";
    fout.close();

    RepoFileProduse repositoryFile{ "test.txt" };
    repositoryFile.adauga("test3", "test33", "test333", 30);

    assert(repositoryFile.getAll().size() == 3);
    assert(repositoryFile.getAll()[2].getNume() == "test3");
    assert(repositoryFile.getAll()[2].getTip() == "test33");
    assert(repositoryFile.getAll()[2].getProducator() == "test333");
    assert(repositoryFile.getAll()[2].getPret() == 30);

    repositoryFile.sterge("test2");
    assert(repositoryFile.getAll().size() == 2);
    assert(repositoryFile.find("test2") == -1);

    repositoryFile.modifica("test331", "test3331", 20, "test3");
    assert(repositoryFile.getAll()[1].getNume() == "test3");
    assert(repositoryFile.getAll()[1].getTip() == "test331");
    assert(repositoryFile.getAll()[1].getProducator() == "test3331");
    assert(repositoryFile.getAll()[1].getPret() == 20);
    std::ofstream out("test.txt", std::ios::trunc);
    out.close();
}

void Tests::testUndo() {
    RepoFileProduse repositoryFile{ "test.txt" };
    RepoCos cos;
    ServiceProd service{ repositoryFile, cos };

    service.adauga("test1", "test1", "test1", 10);
    assert(repositoryFile.getAll().size() == 1);
    service.modifica("test1_mod", "test1_mod", 200, "test1");
    assert(repositoryFile.getAll().size() == 1);
    service.sterge("test1");
    assert(repositoryFile.getAll().size() == 0);

    service.undo();
    assert(repositoryFile.getAll().size() == 1);
    assert(repositoryFile.getAll()[0].getNume() == "test1");
    assert(repositoryFile.getAll()[0].getTip() == "test1_mod");
    assert(repositoryFile.getAll()[0].getProducator() == "test1_mod");
    assert(repositoryFile.getAll()[0].getPret() == 200);

    service.undo();
    assert(repositoryFile.getAll().size() == 1);
    assert(repositoryFile.getAll()[0].getNume() == "test1");
    assert(repositoryFile.getAll()[0].getTip() == "test1");
    assert(repositoryFile.getAll()[0].getProducator() == "test1");
    assert(repositoryFile.getAll()[0].getPret() == 10);

    service.undo();
    assert(repositoryFile.getAll().size() == 0);
}