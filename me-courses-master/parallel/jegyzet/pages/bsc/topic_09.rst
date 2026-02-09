9. Előadás - Tömbrangsorolás, vezetőválasztás, lekérdezések
===========================================================

* Adott egy láncolt lista, amelynek az elemeit egy tömbben helyezzük el.
* Minden elemnek tároljuk a következő elem tömbbeli indexét. (Az egyszerűség kedvéért tekintsünk el az adatrészről, és csak ezzel az indexszel/mutatóval foglalkozzunk.)
* Az utolsó elem a 0-ra mutat.
* A tömbrangsorolás során meg kell határozni minden elemre, hogy mennyi további elem követi a listában. (Az elem után lévő elem számát nevezzük itt rangnak.)

**Példa**

Tekintsünk az alábbi 8 elemű listát!

.. image:: images/ranking/list.png

Egy lehetséges tömbbös reprezentációja a tárolt kulcsoknak:

.. math::

    L = [1, 2, 3, 4, 5, 6, 7, 8]

A következő elemek indexszei:

.. math::

    A = [6, 0, 1, 7, 8, 4, 5, 2]

Az ehhez tartozó rangok a következők:

.. math::

    R = [6, 0, 7, 4, 2, 5, 3, 1]

Szekvenciális algoritmus
~~~~~~~~~~~~~~~~~~~~~~~~

* Tekintsünk egy :math:`n` elemű listát, amelyet egy :math:`n` elemű tömbben tárolunk.
* Feltételezzük, hogy ismerjük a lista első elemének indexét, amelyet :math:`h`-val (*head*) jelölünk.
* A fej elemtől indulva, indexről-indexre haladva sorban be lehet állítani a rangokat :math:`n-1, \ldots, 0` értékekre.

.. math::
   \begin{align*}
   &\text{RANKING}(@A, h, @R)\\
   &\text{// Input}: A, \text{a következő elemek indexei a tömbben}\\
   &\text{//}\quad\quad\quad h, \text{a lista első elemének indexe}\\
   &\text{// Output}: R, \text{az adott indexeken lévő elemek rangja}\\
   &i \leftarrow h\\
   &\text{FOR }c \leftarrow n - 1 \text{ DOWNTO }0\text{ DO}\\
   &\quad r_i \leftarrow c\\
   &\quad i \leftarrow a_i\\
   &\text{RETURN}(R)\\
   \end{align*}

Párhuzamos algoritmus
~~~~~~~~~~~~~~~~~~~~~

A problémára adható párhuzamos algoritmus a következő formában.

* Állítsuk be minden olyan elemnek a rangját kezdetben 1-re, amelynek van következő eleme.
* Az elemek rangját növeljük a következő elemük rangjával.
* A következő elem indexét állítsuk át a következő elem rákövetkezőjének indexére.
* Az így kapott indexszekkel folytassuk az algoritmust.

Látható, hogy a lépések minden elem esetében függetlenül végrehajthatók.

.. math::
   \begin{align*}
   &\text{DET_RANKING}(@A, @R)\\
   &\text{// Input}: A, \text{a következő elemek indexei a tömbben}\\
   &\text{// Output}: R, \text{az adott indexeken lévő elemek rangja}\\
   &\text{PARALLEL FOR }i \leftarrow 1 \text{ TO }n\text{ DO}\\
   &\quad \text{IF }a_i \neq 0\\
   &\quad\quad \text{THEN }r_i \leftarrow 1\\
   &\quad\quad \text{ELSE }r_i \leftarrow 0\\
   &\text{FOR }j \leftarrow 1 \text{ TO }\lceil \log_2 n \rceil\text{ DO}\\
   &\quad \text{PARALLEL FOR }i \leftarrow 1 \text{ TO }n\text{ DO}\\
   &\quad\quad \text{IF }a_i \neq 0\\
   &\quad\quad\quad \text{THEN }r_i \leftarrow r_i + r_{a_i}\\
   &\quad\quad\quad\quad\quad\quad a_i \leftarrow a_{a_i}\\
   &\text{RETURN}(R)\\
   \end{align*}

.. warning::

    Ez az algoritmus az eredeti :math:`A` tömb értékeit ki fogja nullázni!

Jól látható, hogy az algoritmus egy konstans idejű lépésből, és azt követően :math:`\lceil\log_2 n\rceil` számú, szintén konstans idejű lépésből áll.

A determinisztikus tömbrangsoroló algoritmussal a tömbrangsorolási probléma :math:`T(n) = \Theta (\log_2 n)` időben megoldható.

**Példa**

.. list-table::
   :header-rows: 1

   * - A
     - R
   * - [6, 0, 1, 7, 8, 4, 5, 2]
     - [1, 0, 1, 1, 1, 1, 1, 1]
   * - [4, 0, 6, 5, 2, 7, 8, 0]
     - [2, 0, 2, 2, 2, 2, 2, 1]
   * - [5, 0, 7, 2, 0, 8, 0, 0]
     - [4, 0, 4, 4, 2, 4, 3, 1]
   * - [0, 0, 0, 0, 0, 0, 0, 0]
     - [6, 0, 7, 4, 2, 5, 3, 1]

Vezetőválasztási probléma
-------------------------

* Adott egy :math:`p` számú csomópontból álló szinkronizált hálózat.

Minden csomópont

* egyedi azonosítóval rendelkezik,
* van egy logikai értéke, amely jelzi, hogy vezető-e vagy sem,
* üzenetet tud küldeni a hálózatban hozzá kapcsolódó csomópontoknak,
* üzenetet tud fogadni.

A feladat az, hogy döntsük el, hogy ki legyen a hálózat vezetője úgy, hogy minden csomópont csak a szomszédos elemekkel tud kommunikálni.

Vezetőnek választhatjuk például a legalacsonyabb vagy a legmagasabb azonosítójú processzort.

A feladatban az optimalizálás célja lehet például:

* a szükséges lépések száma,
* a küldött üzenetek száma,
* a küldött üzenetek mérete.

Gyűrűben
~~~~~~~~

*Leader Election in Rings*

**LeLann algoritmus**

* Feltételezzük, hogy egy egyirányú gyűrűben vagyunk.
* A processzorok egy részét kezdő processzoroknak tekintjük. Ezek indexeit egy :math:`K` halmazban adjuk meg.
* Nem feltételezzük, hogy a processzorok ismerik a hálózat méretét.

Jelölések:

* :math:`A \in \mathbb{N}^p`: a processzorok azonosítóit tartalmazó vektor
* :math:`S \in \{\text{TRUE}, \text{FALSE}, \text{NIL}\}^p`: a processzorok állapota (*state*) arra vonatkozóan, hogy vezetők-e.
* :math:`C_i \subset \mathbb{N}, 1 \leq i \leq p`: processzorok indexeit tartalmazó halmazok (jelöltek, *candidate*)
* SEND: üzenet küldése a gyűrűben következő processzornak
* RECEIVE: üzenet fogadása az gyűrűben előző processzortól

.. math::

	\begin{align*}
	&\text{ELECT_LELANN}(@A, @K, @l)\\
  &\text{// Input}: A \in \mathbb{N}^p,\text{ processzor azonosítók}\\
  &//\quad\quad\quad\, K \subset \mathbb{N},\text{ kezdő processzorok indexei}\\
  &\text{// Output}: l \in \mathbb{N},\text{ a vezető indexe}\\
  &\text{PARALLEL FOR }i \leftarrow 1\text{ TO }p\text{ DO}\\
  &\quad\text{IF }i \in K\\
  &\quad\quad\text{THEN }s_i \leftarrow \text{NIL}\\
  &\quad\quad\quad\quad\quad C_i \leftarrow \{a_i\}\\
  &\quad\quad\text{ELSE }s_i \leftarrow \text{FALSE}\\
  &\text{PARALLEL FOR }i \leftarrow 1\text{ TO }p\text{ DO}\\
  &\quad\text{IF }s_i = \text{NIL}\\
  &\quad\quad\text{THEN SEND}(a_i)\\
  &\quad\text{DO RECEIVE}(j)\\
  &\quad\quad\quad C_i \leftarrow C_i \cup \{j\}\\
  &\quad\quad\quad\text{IF }j \neq a_i\\
  &\quad\quad\quad\quad\text{THEN SEND}(j)\\
  &\quad\quad\quad\text{WHILE }j \neq a_i\\
  &\quad\text{IF }a_i = \min(C_i)\\
  &\quad\quad\text{THEN }s_i \leftarrow \text{TRUE}\\
  &\quad\quad\quad\quad\quad l \leftarrow i\\
  &\quad\quad\text{ELSE }s_i \leftarrow \text{FALSE}\\
  &\text{RETURN}(l)\\
	\end{align*}

A vezető indexét az algoritmus futását követően minden processzor ismeri:

.. math::

  l = \min(C_i)

*Komplexitás*

* A szükséges lépések száma: :math:`T(p) = \Theta(p)`
* A küldött (majd fogadott) üzenetek száma: :math:`M(p) = \mathcal{O}(p^2)`

Az algoritmus elvégzésekor a nem jelölt processzorok "beragadnak" az üzenet továbbítási állapotukba.

* Ez kiküszöbölhető úgy, hogy ha a kiválasztott vezető körbeküld egy üzenetet, jelezve, hogy véget ért a vezetőválasztás.
* A :math:`T(p)` és :math:`M(p)` komplexitásokra ez nincs hatással. (Mindkét függvény értéke természetesen nagyobb lesz.)

**Chang-Roberts algoritmus**

A LeLann algoritmus javítható azzal, hogy ha minden minden (kezdő) processzor csak a nála kisebb azonosítókat küldi tovább.

A processzoroknak elegendő csak az aktuális vezető jelölt indexét tárolni, így ebben az esetben :math:`C \in \mathbb{N}^p`.

.. math::

	\begin{align*}
	&\text{ELECT_CHANG_ROBERTS}(@A, @K, @l)\\
  &\text{// Input}: A \in \mathbb{N}^p,\text{ processzor azonosítók}\\
  &//\quad\quad\quad\, K \subset \mathbb{N},\text{ kezdő processzorok indexei}\\
  &\text{// Output}: l \in \mathbb{N},\text{ a vezető indexe}\\
  &\text{PARALLEL FOR }i \leftarrow 1\text{ TO }p\text{ DO}\\
  &\quad\text{IF }i \in K\\
  &\quad\quad\text{THEN }s_i \leftarrow \text{NIL}\\
  &\quad\quad\quad\quad\quad c_i \leftarrow a_i\\
  &\quad\quad\text{ELSE }s_i \leftarrow \text{FALSE}\\
  &\text{PARALLEL FOR }i \leftarrow 1\text{ TO }p\text{ DO}\\
  &\quad\text{IF }s_i = \text{NIL}\\
  &\quad\quad\text{THEN SEND}(a_i)\\
  &\quad\text{DO RECEIVE}(j)\\
  &\quad\quad\quad\text{IF }j < c_i\\
  &\quad\quad\quad\quad\text{THEN }c_i \leftarrow j\\
  &\quad\quad\quad\quad\quad\quad\quad\text{SEND}(j)\\
  &\quad\quad\quad\text{WHILE }j \neq a_i\\
  &\quad\text{IF }c_i = a_i\\
  &\quad\quad\text{THEN }s_i \leftarrow \text{TRUE}\\
  &\quad\quad\quad\quad\quad l \leftarrow i\\
  &\quad\quad\text{ELSE }s_i \leftarrow \text{FALSE}\\
  &\text{RETURN}(l)\\
	\end{align*}

*Komplexitás*

* A szükséges lépések száma: :math:`T(p) = \Theta(p)`
* A küldött (majd fogadott) üzenetek száma: :math:`M(p) = \mathcal{O}(p^2)`
* Átlagos esetben azonban: :math:`M(p) = \mathcal{O}(p \log p)`

:math:`\rhd` Mi az algoritmus szempontjából a legrosszabb eset?

**Hirschberg-Sinclair algoritmus**

* Kétirányú gyűrűt feltételez.
* Az üzenetszám minimalizálására törekszik.
* Mindkét irányba egyszerre keresi a vezetőt.
* Kettő hatvány szerint növelve :math:`1, 2, 4, 8, \ldots` távolságokra küld üzenetet.

*Komplexitás*

* A szükséges lépések száma: :math:`T(p) = \Theta(p)`
* A küldött (majd fogadott) üzenetek száma: :math:`M(p) = \mathcal{O}(p \log p)`

**Áttekintés**

.. list-table::
   :header-rows: 1

   * - Algoritmus
     - Év
     - Topológia
     - üzenetszám
   * - Le Lann
     - 1977
     - egyirányú gyűrű
     - :math:`M(p) = \mathcal{O}(p^2)`
   * - Chang-Roberts
     - 1979
     - egyirányú gyűrű
     - :math:`M(p) = \mathcal{O}(p^2)`, átlagosan :math:`M(p) = \mathcal{O}(p \log p)`
   * - Hirschberg-Sinclair
     - 1980
     - kétirányú gyűrű
     - :math:`M(p) = \mathcal{O}(p \log p)`

Fában
~~~~~

*Leader Election in Rings*

**Max-terjed algoritmus**

* Tekintsünk egy irányítatlan fa gráf topológiát!
* Minden csomópont tud üzenetet küldeni a szomszédjának vagy üzenetet fogadni tőle.
* Kezdetben minden csomópontról feltételezzük, hogy ő maga lehet a vezető:

.. math::

  s_i \leftarrow \text{NIL}, 1 \leq i \leq p.

* Minden csomópont először elküldi a saját azonosítóját az összes szomszédjának.
* Minden csomópont fogad egy üzenetet. Amennyiben az abban szereplő azonosító nagyobb, mint az addigi maximális érték, akkor (az üzenet küldőjét leszámítva) tovább küldi az összes szomszédjának.

.. warning::

  Az algoritmus természetesen az előzőekhez hasonlóan minimum kiválasztására is megfelelő.

Mivel a gráfban nincs kör, ezért az algoritmus véges lépésben le fog állni.

*Komplexitás*

* Lánc (busz) esetében :math:`p - 1` lépés lehet szükséges, tehát :math:`T(p) = \mathcal{O}(p)`.
* Csillag topológia esetében 2 lépés szükséges.

Keresés
-------

Logaritmikus keresés
~~~~~~~~~~~~~~~~~~~~

* Feltételezzük, hogy adott egy rendezett, :math:`n` elemű valós sorozat.
* Egy elem indexének visszakeresése :math:`T(n) = \mathcal{O}(\log n)` időben elvégezhető.
* A részintervallumokban való keresés párhuzamosítása nem praktikus.

Bináris keresés esetén a sorozatot minden lépésben 2 részre bontjuk. Ezt általánosíthatjuk :math:`k` számú részintervallum vizsgálatára.

* Jelölje :math:`x` a keresett elemet!
* Minél gyorsabban meg szeretnénk határozni, hogy :math:`x` melyik intervallumba esik.

CRCW modell és :math:`p` számú számítási egység esetén

* az intervallum visszakeresése konstans időben elvégezhető, vagyis
* a teljes keresés :math:`\log_p` idő alatt elvégezhető.

CREW modell esetén minden

* intervallum felosztásnál :math:`\log_p` idő szükséges a megfelelő intervallum visszakereséséhez, tehát
* a keresés időbonyolultsága :math:`T(p, n) = \mathcal{O}(\log_p n \cdot \log_p)`.
* Amennyiben :math:`p` értékét rögzítettnek tekintjük, így adódik, hogy a komplexitás ebben az esetben is :math:`T(n) = \mathcal{O}(\log n)`.
* A párhuzamosítással lineáris gyorsítást tudunk elérni.

Szövegek keresése
~~~~~~~~~~~~~~~~~

Tegyük fel, hogy adott egy :math:`S`-el jelölt :math:`n` hosszúságú szöveg, amelyben egy :math:`Z`-vel jelölt, :math:`m` hosszúságú szöveget szeretnénk megkeresni.

**Naiv algoritmus**

A naiv, *brute-force* algoritmus időigénye: :math:`T(n, m) = \mathcal{O}(n \cdot m)`.

* Az összehasonlítások jól párhuzamosíthatók.
* Rengeteg a felesleges számítás.

**Rabin-Karp algoritmus**

* Definiáljunk egy :math:`h` hasító függvényt, amelyik a szöveghez egy számértéket (jellemzően egész értéket) rendel.
* Számítsuk ki a keresett :math:`Z` mintához tartozó :math:`h(Z)` értéket!
* Haladjunk végig az :math:`S` :math:`m` hosszúságú részsztringjein!
* Számítsuk ki az ezekre vonatkozó hash értéket!
* Hasonlítsuk össze a minta hash értékével!
* Csak akkor vizsgáljunk teljes egyezést, hogy ha a hash értékek megegyeznek!

Az algoritmus hatékonyságának a kritikus pontja a :math:`h` függvény hatékony számítása.

* Amennyiben a :math:`h` számítása :math:`m`-mel arányos, úgy a keresés időigénye továbbra is: :math:`T(n, m) = \mathcal{O}(n \cdot m)`.
* A görgetett hash számítása konstans idejű, így (feltételezve, hogy nem szükséges túl gyakran teljes egyezést vizsgálni a részsztringre) az időbonyolultság: :math:`T(n, m) = \mathcal{O}(n)`.

:math:`\rhd` Adjunk példát görgetett hash számítására!

**Párhuzamosítás**

* Feltételezhetjük, hogy :math:`n` lényegesen nagyobb, mint :math:`m`.
* :math:`p` számítási egység esetén az :math:`S` szöveget :math:`p` részre bonthatjuk.
* A részsztringek elérésekor az intervallumok átlapolódnak. (Ez CREW modell esetében sem jelent általában problémát, mert a vizsgálatokat az alacsonyabbtól a magasabb indexek felé végzi minden számítási egység).

A keresés céljától függően további optimalizálási lehetőségek is adódnak.

*Első találat*

* Amennyiben csak az első találatot kell visszaadni, úgy a magasabb indexű számítási egységeknek be kell várniuk az alacsonyabbakat.
* Hogy ha egy magasabb indexű már talált szöveget, a hátra maradt elemzendő részek feloszthatók újra az összes számítási egység között.

*Összes találat*

* Minden számítási egység egy saját tömbbe/listába gyűjtheti az kapott indexeket, amelyeket a végén összesít az algoritmus.
* Lehet használni egy közös tömböt/listát, amelybe folyamatosan belekerülnek az újonnan talált elemek. (A kölcsönös hozzáférést ez esetben meg kell oldani.)

*Tetszőleges találat*

* Az algoritmusnak csak addig kell szöveget keresnie, amíg valamelyik számítási egység nem talált egyezést.
* Egy megosztott logikai érték tudja jelezni, hogy szükség van-e még a további keresésre.

Halmazok és műveleteik
----------------------

A halmaz reprezentációjára/implementációjára számos lehetőség adódik, például:

* bittömbös reprezentáció,
* tömb/lista,
* rendezett tömb/lista,
* bináris keresőfa (például piros-fekete fa),
* hasítótábla.

**Tartalmazás vizsgálata**

Azt szeretnénk megvizsgálni, hogy egy :math:`a \in A` teljesül-e.

Hogy ha :math:`p = |A|` és CRCW modellünk van, akkor a vizsgálat konstans időben elvégezhető.

Ez a gyakorlatban ritkán adódik, ezért az alábbi eseteket érdemes fontolóra venni.

* Bittömb esetében nincs értelme párhuzamosítani, mert a művelet eleve konstans idejű.
* Tömbös reprezentáció esetében a lineáris időt :math:`p`-szeresre lehet gyorsítani.
* Egyszeresen láncolt listás reprezentáció esetében csak segéd mutatótömb beiktatásával oldható meg a gyorsítás.
* Duplán láncolt lista esetében kereshetünk a lista 2 végéről kezdve.
* Listák tömbjével a lineáris idő :math:`p`-szeresre gyorsítható.
* Rendezett tömb esetében logaritmikus keresést használhatunk.
* Listák esetében a rendezettség nem segíti a hatékonyabb keresést.
* Hasítótábla esetében a hash függvényt és a kipróbálási sorozat vizsgálatát lehet gyorsítani.
* Bináris keresőfák esetében lineáris gyorsítás érhető el, hogy ha az :math:`|A|` számú elemet :math:`p` számú fába tároljuk el, amelyekben párhuzamosan tudunk keresni.

Alapvetően a szekvenciális esetben hatékony struktúrák :math:`p` számú párhuzamos használata, majd az eredmények összegzése tud hatékony megoldást adni párhuzamos esetben.

* A beszúrás és törlés műveletek kézenfekvő módon adódnak.
* A párhuzamosítás a szekvenciális algoritmusok ismeretében könnyen elvégezhető.

:math:`\rhd` Hogyan párhuzamosítható az unió és a metszet művelet végrehajtása?

Kérdések
--------

* Hogyan nézne ki a LeLann algoritmust egy processzor szemszögéből?

Feladatok
---------

Tömbrangsolorás
~~~~~~~~~~~~~~~

* Oldjuk meg a tömbrangsorolási problémát, hogy ha a lista elemei az 5, 1, 3, 2, 7, 4, 2 sorrendben követik egymást!

Vezetőválasztás
~~~~~~~~~~~~~~~

* Készítsünk szimulációt :math:`p` elemű gyűrűben, és ellenőrízzük a vezetőválasztáshoz szükséges lépés és üzenet számot a LeLann és a Chang-Roberts algoritmusok esetében!
