8. Előadás - Statisztikai algoritmusok
======================================

Tartomány
~~~~~~~~~

* A mintában szereplő minimum és maximum érték kiválasztására van szükség.

Kiválasztás
~~~~~~~~~~~

Adott :math:`n` darab kulcsunk, és meg szeretnénk határozni az :math:`i`-edik legkisebb elemet (:math:`1 \leq i \leq n`).

A kiválasztás egy speciális esete a maximum érték meghatározása, vagyis amikor :math:`i = n`.

**tétel**

:math:`n` elem esetében :math:`n^2` számú processzor használatával egy PRAM CRCW gépen a kiválasztás konstans időben (:math:`\Theta (1)` lépésben) megoldható.

Feltételezzük, hogy minden kulcs különböző értékű.

* Legyen egy :math:`Q \in \{0, 1\}^{n \times n}` mátrix.
* Az :math:`n^2` számú processzoron (párhuzamosan) határozzuk meg a :math:`q_{ij} = x_i < x_j` logikai értékeket.
* Képezzünk soronként csoportokat: :math:`G_1, \ldots, G_n`.
* Minden :math:`G_i` csoporton belül a :math:`Q` értékeken *vagy* műveletet végrehajtva kapunk :math:`n` darab logikai értéket.
* Azon :math:`x_i` elem lesz a maximális érték, ahol a csoportokhoz tartozó logikai érték 0-ra adódik.

.. warning::

    Az értékek egyediségére vonatkozó megkötés ez esetben csak egyszerűsítés. Amennyiben előfordulhatnak ismétlődő értékek, az indexekkel párokat alkotva :math:`(x_i, i)` egyszerűen egyedivé tehetők.

Az algoritmus jellemzői:

.. math::

    \begin{align*}
    &T_{\text{seq}}(n) = \Theta (n)\\
    &T_{\text{par}}(n) = \Theta (1)\\
    &W_{\text{seq}}(n) = \Theta (n)\\
    &W_{\text{par}}(n) = \Theta (n^2)\\
    &C_{\text{seq}}(n) = \Theta (n)\\
    &C_{\text{par}}(n) = \Theta (n^2)\\
    &S(n) = \dfrac{T_{\text{seq}}(n)}{T_{\text{par}}(n)} = \Theta (n)\\
    \end{align*}

A hatékonyságot ebben az esetben érdemes a szekvenciális és a párhuzamos végrehajtáshoz használt költség hányadosaként megadni:

.. math::

    E(n) = \dfrac{n}{n^2} = \dfrac{1}{n}

Átlag
~~~~~

.. math::

    \overline{x} = \dfrac{1}{n} \displaystyle \sum_{i=1}^n x_i

* A számítás nyilvánvalóan az elemek összeadásával és egy plusz lépéssel megoldható.
* A gyakorlatban problémát jelenthet az, hogy ha az összeg átlépheti a számábrázolási tartományt.

Szórás
~~~~~~

**Tapasztalati szórásnégyzet**

.. math::

    s^2 = \dfrac{1}{n} \displaystyle\sum_{i=1}^{n} (x_i - \overline{x})^2

**Korrigált tapasztalati szórásnégyzet**

.. math::

    s^2 = \dfrac{1}{n - 1} \displaystyle\sum_{i=1}^{n} (x_i - \overline{x})^2

* A számítások az átlag számításhoz hasonlóan jól párhuzamosíthatók.
* Közel 1 hatékonyságú algoritmus adható a problémára (:math:`S_p \approx p`).

Medián
~~~~~~

A rendezett minta középső eleme.

* :math:`2k + 1` számú elem esetében a rendezett minta :math:`(k + 1)`-edik eleme.
* :math:`2k` elem esetén a rendezett minta :math:`k`-adik elemét alsó-, a :math:`(k + 1)`-edik elemét felső mediánnak nevezzük.

A számítására különböző alternatívák adódnak.

* Rendezést követően a medián értéke konstans időben kiolvasható.
* Gyorsrendezés esetében elegendő csak azon az ágon folytatnunk a rendezést, amely intervallum tartalmazza a :math:`(k + 1)` (vagy a :math:`k`) indexet.

**Párhuzamosítás**

* A gyorsrendezés esetében problémát jelent a felosztáshoz használt elem (pivot elem) kiválasztása.
* Rendezett mintát és a részintervallumok első elemének választását feltételezve a rendezésnél a számítási idő :math:`n^2`-re adódik. A négyzetes jelleg így a medián számításánál is megmaradna.

A medián keresése gyorsítható, hogy ha törekszünk arra, hogy a tömbünket közel egyenlő részekre osszuk fel. Ezt elérhetjük például úgy, hogy

* a tömböt :math:`\left\lceil \dfrac{n}{K} \right\rceil` részre osztjuk fel, és
* mindegyikben külön megkeressük a medián értéket, majd
* a kapott :math:`\left\lceil \dfrac{n}{K} \right\rceil` számú mediánnak ismét vesszük a mediánját.
* A mediánok mediánjának a számítását rekurzívan végezhetjük.
* A felosztáshoz pivot elemnek a mediánok mediánját választhatjuk.

Irodalmi ajánlás a :math:`K = 5` érték.

A párhuzamosításhoz a részintervallumokban a medián értékek függetlenül, időben egyszerre számolhatók.

Hisztogram
~~~~~~~~~~

* Egy adott intervallum felett vizsgáljuk az elemek intervallumba esésének gyakoriságát (vagy valószínűségét).
* Megkülönböztetünk gyakoriság és sűrűség hisztogramokat.
* Általában egyenközű felbontást alkalmazunk.

Tekintsük az :math:`[a, b)` valós intervallumot, ami felett vizsgálni szeretnénk a mintában szereplő értékek gyakoriságát! Osszuk ezt fel :math:`k` egyenlő részre. Ekkor az intervallumokba eső gyakoriságok a következő formában számíthatók.

.. math::

	\begin{align*}
	&\text{CALC_HISTOGRAM}(@X, a, b, k, @C)\\
	&\text{// Input}: X \in \mathrm{R}^{n}, \text{a minta}\\
    &\text{//}\quad\quad\quad [a, b), \text{a vizsgált intervallum}\\
    &\text{//}\quad\quad\quad k \in \mathbb{N}, \text{az intervallumok száma}\\
	&\text{// Output}: C \in \mathrm{Z}^k, \text{a kapott gyakoriságok}\\
    &\text{FOR }j \leftarrow 1\text{ TO }k\text{ DO}\\
    &\quad c_j \leftarrow 0\\
    &\text{FOR }i \leftarrow 1\text{ TO }n\text{ DO}\\
    &\quad j \leftarrow \left\lfloor \dfrac{x_i - a}{b - a} \cdot n \right\rfloor + 1\\
    &\quad \text{INC}(c_j)\\
	&\text{RETURN}(C) \\
	\end{align*}

**Párhuzamosítás**

* Mindkét FOR ciklus párhuzamosan, PARALLEL FOR-ként is kezelhető.
* A számítási egységek számával közel lineáris gyorsítás elérhető.
* A :math:`C` eredménytömb elemeinek növeléséhez PRAM CREW modell esetében zárolás szükséges.

:math:`\rhd` Nem ekvidisztáns felbontás esetén milyen lehetőségek vannak a gyorsabb, hatékonyabb számítások érdekében?

Sztochasztikus integrálás
~~~~~~~~~~~~~~~~~~~~~~~~~

Egy határozott integrál értékét közelíthetjük véletlenszerűen választott pontok alapján a görbe "alatti" pontok számának, és az összes pontnak az arányával.

* A számítás egyszerűen és hatékonyan párhuzamosítható.
* Jól alkalmazható magasabb dimenziókban is, ahol az intervallum felosztásos integrálás körülményes.

:math:`\rhd` Adjunk példát más, hasonlóképpen párhuzamosítható szimulációkra!

Kérdések
--------

Feladatok
---------

Átlag
~~~~~

* Készítsen egy példát olyan esetre, amelyben az átlag számítása során az összeg átlépi a számábrázolási tartományt! Adjon rá megoldást!

Medián
~~~~~~

* Vizsgáljuk meg, hogy mennyire tud hatékony lenni a medián számítása, hogy ha a felosztáshoz mindig a résztömb átlagát használjuk!
* Mérések segítségével próbáljuk meg optimalizálni az algoritmusban szereplő :math:`K` értékét!

Hisztogram
~~~~~~~~~~

* Írjuk fel a hisztogram számításának a pszeudó kódját arra az esetre, hogy ha egy :math:`[0, 9]` egészes intervallum felett szeretnénk összeszámolni az értékeket!

Sztochasztikus integrálás
~~~~~~~~~~~~~~~~~~~~~~~~~

#. Hasonlítsa össze a numerikus és a sztochasztikus integrálást!

* Készítse el mindkettőnek a párhuzamos implementációját!
* Konkrét példa esetében nézze meg, hogy adott idő alatt melyik ad pontosabb eredményt!
* Hasonlóképpen vizsgálja meg, hogy az adott pontosság eléréséhez szükséges számítási időknek milyen az eloszlása!
* A sztochasztikus integrál esetében ábrázolja az iterációnkénti közelítéseket. (Paraméterként lehessen megadni, hogy egy iterációban mennyi új pontot generáljon az algoritmus!)

.. korreláció számítása
