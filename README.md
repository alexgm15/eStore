# eStore


Prin acest proiect dorim să implementam un sistem pentru o platforma online dedicata vanzarii de produse diverse. Entitatile principale sunt Produsele, Utilizatorii si Serverul care stocheaza detalii despre produse si utilizatori si unde se pot efectua diverse operatii asupra entitatilor, precum căutări de produse, de utilizatori sau modificări de diferite cantități (adăugare sau scoatere de produse din coș).

Mai jos detaliem clasele, cu scopul de a oferi o intelegere mai buna asupra proiectului. 
![producthierarchy](https://user-images.githubusercontent.com/104631782/180472690-db591361-139f-407d-a909-ac95cadeb215.jpg)


 Aceasta este cea mai complicata ierarhie de clase a intregului proiect - din motive evidente - cand intrati pe un site de retail, tipurile de produse pot fi deseori coplesitoare prin pura lor varietate. Numele Claselor (si implicit al tipurilor) sunt in engleza pentru consecventa (ca sa minimizam utilizarea romglezei in acest proiect).

Asadar, clasa Product (Produs) este abstracta din dorinta de a ramifica tipurile de produse de pe site. Niciodata nu o sa avem un produs (simplu), intotdeauna o sa apartina de o 'categorie' anume. Ea reprezinta o schita pentru restul tipurilor de produse ce se vor deriva din aceasta.

Mai departe, distingem 2 tipuri de produse: FoodProduct (Produs Alimentar) si NonFoodProduct (Produs Nealimentar) - ca in viata reala. Fiecare din aceste clase aduce dupa sine campuri/metode noi.

Pentru ca viata reala e deseori mai complicata decat am spera, in sectiunea produselor nealimentare avem de rezolvat o problema de tip 'Death Diamond', conform diagramei de mai sus. NonFood Product (Produsele Nealimentare) pot fi de 2 tipuri: Returned Products (Produse Returnate, care probabil aveau defecte) si Discounted Products (Produse Reduse, care au un pret scazut fata de cel normal).

Din cele 2 ia nastere Resealed Product (Produs Resigilat), care indeplineste atat proprietatea de a fi un produs returnat, cat si unul redus.

ID-ul unui produs este unic și respectă următoarea schemă: ![produs](https://user-images.githubusercontent.com/104631782/180472957-1c51ac40-55e3-47d3-8ab7-c345c8a9c3ad.png)


Ierarhia User


![userhierarchy](https://user-images.githubusercontent.com/104631782/180473094-9f17b12c-975d-4c13-b28e-9e70e7a894da.png)

 Urmatoarea ierarhie de clase are ca scop implementarea urmatoarei paradigme: “Dai un ban, dar stai in fata”.

Clasa User este una abstracta, care reprezinta schita celor 2 tipuri de Useri: Basic User si Premium User. Astfel, reusim sa distingem tipurile de Useri prin diferite campuri/metode, oferind posibilitatea particularizarilor (planuri de plata diferite, in functie de User).

Trebuie precizat că Userii Premium au un map de reduceri de tipul <int ProductID, int discount>, în care sunt stocate reduceri pentru diferite produse. Atenție: Map-ul poate conține și ID-uri ale produselor ce nu se mai află în acest moment în magazin (nu se află în lista cu produse de pe server)

Ca in ierarhia de clase Product, clasa User este abstracta, neputand sa avem un User simplu, ci doar Basic sau Premium.

Are loc, de asemenea, procesul de agregare printr-o clasa Address al carui scop este de a introduce campuri complexe de adresa Userilor.

ID-ul unui utilizator este unic și are următoarea schemă: ![user](https://user-images.githubusercontent.com/104631782/180473174-b8f26120-8f68-43b8-afab-3437658c792c.png)


Clasa ShoppingCart

Nevoia unei clase de Shopping Cart (Cos Produse) este evidenta pentru toata lumea, mai ales pentru cei care aleg sa nu ia un cos la intrarea in magazin si tin toate produsele in mana pana la casa.

Cel mai important aspect al acestei clase este reprezentat de campul “shoppingCart”, un map ce contine 2 numere intregi per intrare.

map <int, int> shoppingCart

Cheia (primul numar intreg) reprezinta Product ID, adica ID-ul unui produs din 'Baza de Date' a produselor. Valoarea (al doilea numar intreg) reprezinta Quantity, adica cantitatea unui produs din cos. Practic, per intrare in cosul nostru de produse, vom avea o pereche (ProdusID, Quantity).

e.g. (225200, 420) -> Produsul cu ID-ul 225200 are cantitatea de 420 in cosul nostru.

Cosul joaca un rol esential mai departe in integrarea lui pe Server, in concordanta cu UserID.
Clasa Server

Clasa Server este piesa ce leaga tot. Aici stocam toate datele legate de Useri si Produse (in liste neomogene). Astfel, ne-ar placea sa avem 'acces' la aceste date de 'oriunde'.

Analogia de mai sus se traduce prin implementarea unui Design Pattern numit Singleton. Concret, Singleton ne permite instantierea unui singur obiect de un anume tip (un singur obiect de tip Server, numit server), care poate fi accesat din multiple clase.

Pentru a construi o mai buna intuitie asupra Design Pattern-ului Singleton, click aici. Pentru un exemplu de cod, click aici.

Avem o instanta a clasei Server, pe care o numim server. Pentru a obtine lista de Produse prin instanta server, putem scrie ceva de genul:

server->getProductsList()

 Un camp important din clasa Server este reprezentat de map-ul:

  map<int, ShoppingCart*> __UserID__ProductsCart__

Cheia este un UserID (id-ul unui User/Utilizator). Valoarea este un pointer catre un obiect de tip ShoppingCart (Cos Produse). Practic, acest map reprezinta legatura dintre un User si cosul sau de produse, o functionalitate prevalenta in toate site-ul de retail.
Clasa QuerySolver

Aceasta clasa este pusa la dispozitia voastra pentru a implementa cerintele ce tin de Queries/Interogari. Fiecare subcerinta are o metoda aferenta.

Ea nu se afla in propriul folder fiindca nu reprezinta un 'tip' utilizat in proiectul nostru. Este doar o clasa ajutatoare, care speram ca va facilita abordarea cerintelor de Query (Cerinta 3).
Clasa LRU Cache

In general, cand vorbim despre resurse computationale si servicii oferite, mereu apare cuvantul “optimizare”. Motivul e simplu: Daca operatiile se efectueaza suficient de repede, avem clienti multumiti. De asemenea, reducand spatiul ocupat pe servere, ajungem sa platim mai putin pentru serviciile Cloud. Astfel, atunci cand rulam milioane de operatii zilnic, optimizarea unei operatii ce are loc des (de exemplu accesul la o resursa populara), poate avea un impact masiv asupra intregului serviciu oferit.

Intuitiv, produsele populare vor fi destul de des accesate, deci ne-ar placea sa oferim acces “privilegiat” acestora. Acesta paradigma se traduce intr-o modificare hardware.

Asadar, pentru implementarea paradigmei de mai sus, vom simula comportamentul unui 'Least Recently Used Cache', care va retine id-ul produselor ce reprezinta ultimele accesari ale utilizatorilor.
