6. Előadás - Rendező algoritmusok
=================================

Rendező algoritmusok
--------------------

A :math:`\rho` (részben) rendezési reláció tulajdonságai:

* reflexív: :math:`a \rho a, \forall a \in A`
* antiszimmetrikus: :math:`a \rho b` és :math:`b \rho a` esetén :math:`a = b`
* tranzitív: :math:`a \rho b` és :math:`b \rho c` esetén :math:`a \rho c`

A teljes rendezés esetében elvárjuk azt is, hogy a halmaz bármely két kiválasztott eleme között legyen reláció.

Beszúrásos rendezés
~~~~~~~~~~~~~~~~~~~

*Az algoritmus működése*

* Kiindulunk egy üres eredmény sorozatból.
* Az eredeti tömb elemeit sorban beszúrjuk úgy, hogy mindig rendezett sorozatot kapjunk.
* A beszúrás mindig a tömb végétől kezdve történik. (A tömb elejétől kezdve költségesebb lenne.)

:math:`\rhd` Egy 9 elemű példán nézzük meg az algoritmus működését!

*Párhuzamosítás*

Megpróbálhatunk beszúrni úgy elemeket, hogy a korábbi beszúrások még tartanak.

* A beszúrást végző iterátorok között megfelelő távolságnak kell lenni.
* A beszúrandó elemeket rendezni kell, és a kisebb értékeket kell először beszúrni. (Ez egy független rendezési feladat, melyhez szintén használható például a beszúró rendezés.)
* Elvi szinten a megoldás működik, de szinkron működést feltételez.
* Szálak szintjén a szinkronizációs költség aránytalanul nagy.

:math:`\rhd` Egy 9 elemű példán vizsgáljuk meg 3 iterátorral az algoritmus működését!

:math:`\rhd` Rajzoljuk fel a Gantt diagramot az összehasonlítás és csere műveletekkel!

Minimumkiválasztásos rendezés
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*Az algoritmus működése*

* Kiindulunk egy üres eredmény sorozatból.
* A bemeneti sorozatunknak megkeressük a minimumát.
* Ezt beszúrjuk az eredménysorozat végére.
* Az előző két lépést addig ismételjük, amíg el nem fogynak az elemek a bemeneti sorozatból.

:math:`\rhd` Egy 5 elemű példán nézzük meg az algoritmus működését!

*Párhuzamosítás*

(I.) A minimum keresést párhuzamosíthatjuk.

* Tetszőlegesen sok számítási egység esetében a keresés :math:`\log_2 (n)` időre csökkenthető.
* A teljes számítási idő így:

.. math::

	T(n) = \displaystyle \sum_{i=1}^{n} \log_2(i).

* Ez ugyan gyorsabb lesz, mint az eredeti :math:`T(n) = \Theta(n^2)` időbonyolultság, de nem elég hatékony így sem (a következőkben bemutatásra kerülő algoritmusokhoz képest).

:math:`\rhd` Egy 5 elemű példán nézzük meg az algoritmus működését!

:math:`\rhd` Rajzoljuk fel a Gantt diagramot az összehasonlításokra nézve, és számítsuk ki a költség, munka, gyorsítás és hatékonyság értékét! (Feltételezzük, hogy tetszőleges sok számítási egységünk lehet!)

(II.) Csoportokat képezhetünk

A négyzetes rendezés analógiájára elképzelhető a következő algoritmus.

* Tegyük fel, hogy van :math:`p` darab számítási egységünk.
* Osszuk fel a rendezendő tömbünket :math:`p - 1` részre.
* A :math:`p - 1` számú számítási egységgel határozzuk meg minden résztömbnek a saját minimumát.
* A :math:`p.` számítási egységnek allokáljunk egy :math:`p - 1` méretű segédtömböt, amelybe belekerülnek a csoportonkénti minimumok.
* Kezdjük el kiszámolni a résztömbökben maradt következő minimumot. Közben számítsuk ki a segédtömb minimumát.
* A kapott minimumot írjuk az eredménytömb végére.
* Amint egy minimumot kivettünk a segédtömbből, írjuk be a helyére a hozzá tartozó csoport következő minimum értékét. (Itt előfordulhat, hogy a :math:`p.` számítási egységnek várni kell a minimumérték meghatározására.)
* Folytassuk addig az eljárást, amíg minden érték el nem fogy a csoportokból.

A számítás akkor tud hatékony lenni, hogy ha a minimumértékek mindig más csoportokból kerülnek ki. Az algoritmus egyik legrosszabb esete a rendezett tömb.

Összefésülés
~~~~~~~~~~~~

**Két bemeneti tömbös változat**

.. math::

	\begin{align*}
	&\text{MERGE_ARRAYS}(@A, @B, @C) \\
	&\text{// Input}: A \in \mathrm{R}^n \\
	&//\quad\quad\quad\, B \in \mathrm{R}^m \\
	&\text{// Output}: C \in \mathrm{R}^{n+m} \\
	&i \leftarrow 1, j \leftarrow 1, k \leftarrow 1\\
	&\text{WHILE }i \leq n\text{ AND }j \leq m\text{ DO}\\
	&\quad \text{IF }a_i \leq b_j\\
	&\quad\quad \text{THEN }c_k \leftarrow a_i\\
	&\quad\quad\quad\quad\quad i \leftarrow i + 1\\
	&\quad\quad \text{ELSE }c_k \leftarrow b_j\\
	&\quad\quad\quad\quad\quad j \leftarrow j + 1\\
	&\quad k \leftarrow k + 1\\
	&\text{WHILE }i \leq n\text{ DO}\\
	&\quad\quad\quad c_k \leftarrow a_i\\
	&\quad\quad\quad i \leftarrow i + 1\\
	&\quad\quad\quad k \leftarrow k + 1\\
	&\text{WHILE }j \leq m\text{ DO}\\
	&\quad\quad\quad c_k \leftarrow b_j\\
	&\quad\quad\quad j \leftarrow j + 1\\
	&\quad\quad\quad k \leftarrow k + 1\\
	&\text{RETURN}(C) \\
	\end{align*}

**Egy bemeneti tömbös változat**

.. math::

	\begin{align*}
	&\text{MERGE}(@A, p, q, r) \\
	&\text{// Input}: A, \text{sorozat} \\
	&//\quad\quad\quad\, p, q, r \in \mathrm{N}, p \leq q \leq r \\
	&\text{// Output}: A, \text{rendezett sorozat} \\
	&X \leftarrow \text{COPY}(A)\\
	&i \leftarrow 1, j \leftarrow q + 1, k \leftarrow 1\\
	&\text{WHILE }i \leq q\text{ AND }j \leq r\text{ DO}\\
	&\quad \text{IF }x_i \leq x_j\\
	&\quad\quad \text{THEN }a_k \leftarrow x_i\\
	&\quad\quad\quad\quad\quad i \leftarrow i + 1\\
	&\quad\quad \text{ELSE }a_k \leftarrow x_j\\
	&\quad\quad\quad\quad\quad j \leftarrow j + 1\\
	&\quad k \leftarrow k + 1\\
	&\text{WHILE }i \leq q\text{ DO}\\
	&\quad\quad\quad a_k \leftarrow x_i\\
	&\quad\quad\quad i \leftarrow i + 1\\
	&\quad\quad\quad k \leftarrow k + 1\\
	&\text{WHILE }j \leq r\text{ DO}\\
	&\quad\quad\quad a_k \leftarrow x_j\\
	&\quad\quad\quad j \leftarrow j + 1\\
	&\quad\quad\quad k \leftarrow k + 1\\
	&\text{RETURN}(A) \\
	\end{align*}

:math:`\rhd` Vizsgáljuk meg az algoritmus működését egy 12 elemű példán!

:math:`\rhd` Határozzuk meg az elvégzett összehasonlítások számát!

**Batcher-féle páros-páratlan összefésülés**

Tegyük fel, hogy adott egy :math:`A` és egy :math:`B` sorozat, amit össze szeretnénk fésülni.

.. math::

	\begin{align*}
	A &= \{a_1, a_2, a_3, \ldots\}\\
	B &= \{b_1, b_2, b_3, \ldots\}\\
	\end{align*}

Bontsuk fel ezeket külön tömbökre az indexek paritása szerint!

.. math::

	\begin{align*}
	A_1 &= \{a_1, a_3, a_5, \ldots\}\\
	A_2 &= \{a_2, a_4, a_6, \ldots\}\\
	B_1 &= \{b_1, b_3, b_5, \ldots\}\\
	B_2 &= \{b_2, b_4, b_6, \ldots\}\\
	\end{align*}

Fésüljük össze ezeket az :math:`U` és :math:`V` sorozatokba:

.. math::

	\begin{align*}
	&A_1, B_2 \rightarrow U \\
	&A_2, B_1 \rightarrow V \\
	\end{align*}

A :math:`C` eredménysorozatot az :math:`U` és :math:`V` sorozatok összefésülésével kapjuk.

Összefésülő rendezés
~~~~~~~~~~~~~~~~~~~~

.. math::

	\begin{align*}
	&\text{MERGE_SORT}(@A, p, r) \\
	&\text{// Input}: A, \text{sorozat} \\
	&//\quad\quad\quad\, p, r \in \mathrm{N}, p \leq r \\
	&\text{// Output}: A, \text{rendezett sorozat} \\
	&\text{IF }p < r\\
	&\quad \text{THEN }q \leftarrow \left\lfloor\dfrac{p + r}{2}\right\rfloor\\
	&\quad\quad\quad\quad \text{MERGE_SORT}(A, p, q)\\
	&\quad\quad\quad\quad \text{MERGE_SORT}(A, q + 1, r)\\
	&\quad\quad\quad\quad \text{MERGE}(A, p, q, r)\\
	&\text{RETURN}(A) \\
	\end{align*}

:math:`\rhd` Egy 10 elemű példán vizsgáljuk meg az algoritmus működését!

.. math::

  A = [9, 2, 1, 7, 3, 4, 10, 6, 5, 8]

:math:`\rhd` Feltételezve, hogy a rekurzívan felbontott részek párhuzamosan is végrehajthatók, ábrázolja az előző számításhoz tartozó Gantt diagramot!

* Feltételezzük, hogy tetszőleges sok számítási egység rendelkezésünkre áll!
* Csak az összehasonlítási műveleteket vegyük figyelembe!

:math:`\rhd` Határozzuk meg a költség, munka, gyorsítás és hatékonyság értékeket!

:math:`\rhd` Mutassuk meg, hogy kisebb gyorsítással adható hatékonyabb megoldás!

Buborék rendezés
~~~~~~~~~~~~~~~~

Az alapötlete az, hogy

* elegendő a szomszédos elemeket páronként ellenőrízni, hogy a sorozat rendezett-e, és
* ha nem megfelelő a pár sorrendje, akkor meg kell cserélni a két elemet.

Az algoritmusnak (szekvenciális esetben is) több változata elképzelhető. A sorozat bejárása történhet

* az alacsonyabb indexektől a magasabbak felé, vagy
* a magasabbaktól az alacsonyabbak felé.

:math:`\rhd` Nézzük meg az algoritmus működését a következő sorozat rendezésével!

.. math::

  A = [8, 6, 3, 1, 5, 4]

*Párhuzamosítás*

Az algoritmus párhuzamosítása problémás.

* A rendezési mód nehezen fogalmazható meg rekurzív formában.
* Az elem mozgatása az egész tömbre értendő (tehát a problématér felosztása is körülményes). Ez zárolást tenne szükségessé.

Szinkron rendszert feltételezve indíthatunk párhuzamosan több rendező iterátort.

* A közöttük lévő különbségnek legalább 1-nek kell lennie.
* Az utolsónak kell tudni megállapítani, hogy a rendezés során történt-e csere.
* Egy iterációt követően :math:`p`-vel nő a már rendezett elemek száma.
* Erősen szinkron működést igényel, hogy az iterátorok ne akadjanak össze.
* A gyakori szinkronizáció költsége nagyobb lehet, mint az összehasonlításé és a cseréjé.

:math:`\rhd` Vizsgáljuk meg az előbbi példára a párhuzamos változatot!

:math:`\rhd` Rajzoljuk fel a Gantt diagramot!

:math:`\rhd` Határozzuk meg a költség, munka, gyorsítás és hatékonyság értékeket!

Shell rendezés
~~~~~~~~~~~~~~

.. math::
   \begin{align*}
   &\text{SHELL_SORT}(@A) \\
   &\text{// Input}: A, \text{sorozat} \\
   &\text{// Output}: A, \text{a rendezett sorozat}\\
   &\text{FOREACH }d \in H\text{ DO}\\
   &\quad\text{FOR }j \leftarrow d + 1\text{ TO }n\text{ DO}\\
   &\quad\quad x \leftarrow a_j\\
   &\quad\quad i \leftarrow j - d\\
   &\quad\quad \text{WHILE }i > 0\text{ AND }a_i > x\text{ DO}\\
   &\quad\quad\quad a_{i+d} \leftarrow a_i\\
   &\quad\quad\quad i \leftarrow i - d\\
   &\quad\quad a_{i+d} \leftarrow x\\
   &\text{RETURN}(A)\\
   \end{align*}

:math:`\rhd` Rendezzük az

.. math::

  A = [4, 7, 8, 6, 3, 1, 2, 5]

tömböt a :math:`H = [4, 2, 1]` növekmények felhasználásával!

*Párhuzamosítás*

Az azonos távolságokra lévő elemek az egyes iterációkban párhuzamosan rendezhetők.

:math:`\rhd` Vizsgáljuk meg az előbbi példára a párhuzamos változatot!

* Jelezzük külön az összehasonlítás és a csere műveleteket!
* Feltételezzük, hogy a kettő műveleti ideje azonos!

:math:`\rhd` Rajzoljuk fel a Gantt diagramot!

:math:`\rhd` Határozzuk meg a költség, munka, gyorsítás és hatékonyság értékeket!

Gyorsrendezés
~~~~~~~~~~~~~

A felosztáshoz használt algoritmus pszeudó kódja:

.. math::
   \begin{align*}
   &\text{PARTITION}(@A, p, r, x, @q) \\
   &\text{// Input}: A, \text{sorozat} \\
   &//\quad\quad\quad\, p, r \in \mathrm{N}, p \leq r \\
   &//\quad\quad\quad\, x, \text{a felosztáshoz használt elem} \\
   &\text{// Output}: A, \text{a felosztott sorozat}\\
   &//\quad\quad\quad\, q \in \mathrm{N}, \text{a felosztás határa}, p \leq q \leq r\\
   &i \leftarrow p - 1 \\
   &j \leftarrow r + 1 \\
   &\text{WHILE IGAZ DO} \\
   &\quad \text{REPEAT } j \leftarrow j - 1 \\
   &\quad \quad \text{UNTIL } a_j \leq x \\
   &\quad \text{REPEAT } i \leftarrow i + 1 \\
   &\quad \quad \text{UNTIL } a_i \geq x \\
   &\quad \text{IF } i < j \\
   &\quad \quad \text{THEN } a_i \leftrightarrow a_j \\
   &\quad \quad \text{ELSE } q \leftarrow j \\
   &\quad \quad \quad \quad \quad \text{RETURN}(A, q) \\
   \end{align*}

A gyorsrendezés algoritmusa:

.. math::
   \begin{align*}
   &\text{QUICKSORT}(@A, p, r) \\
   &\text{// Input}: A, \text{sorozat} \\
   &//\quad\quad\quad\, p, r \in \mathrm{N}, p \leq r \\
   &\text{// Output}: A, \text{a rendezett sorozat}\\
   &\text{IF }p < r\text{ THEN}\\
   &\quad\text{PARTITION}(A, p, r, a_p, q)\\
   &\quad\text{QUICKSORT}(A, p, q)\\
   &\quad\text{QUICKSORT}(A, q + 1, r)\\
   &\text{RETURN}(A)\\
   \end{align*}

*Párhuzamosítás*

A felosztást követően a résztömbök függetlenül rendezhetők.

:math:`\rhd` Nézzük meg az algoritmus működését a következő sorozat rendezése kapcsán!

.. math::

  A = [5, 4, 2, 6, 1, 3]

:math:`\rhd` Számoljuk meg, hogy mennyi kulcsokra vonatkozó összehasonlítás és csere történt!

:math:`\rhd` Rajzoljuk fel a Gantt diagramot!

:math:`\rhd` Határozzuk meg a költség, munka, gyorsítás és hatékonyság értékeket!

Leszámláló rendezés
~~~~~~~~~~~~~~~~~~~

.. math::
   \begin{align*}
   &\text{COUNTING_SORT}(@A, k, @B) \\
   &\text{// Input}: A, \text{a rendezendő sorozat} \\
   &\text{// Output}: B, \text{a rendezett sorozat}\\
   &\text{FOR }i \leftarrow 1 \text{ TO }k\text{ DO}\\
   &\quad c_i \leftarrow 0\\
   &\text{FOR }j \leftarrow 1\text{ TO }n\text{ DO}\\
   &\quad \text{INC}(c_{a_j})\\
   &\text{FOR }i \leftarrow 2\text{ TO }k\text{ DO}\\
   &\quad c_i \leftarrow c_i + c_{i-1}\\
   &\text{FOR }j \leftarrow n\text{ DOWNTO }1\text{ DO}\\
   &\quad b_{c_{a_j}} \leftarrow a_j\\
   &\quad \text{DEC}(c_{a_j})\\
   &\text{RETURN}(B)\\
   \end{align*}

A :math:`k` felső korlátként megjelölhető az :math:`A` sorozat maximális értéke.

*Párhuzamosítás*

A 4 lépésnek egymás után kell következnie. Párhuzamosításra azokon belül van lehetőség.

#. Teljesen párhuzamosítható.
#. A :math:`C` segédtömbhöz való hozzáférés miatt ilyen formában zárolásra van szükség.
#. Prefix számítási problémaként kezelhető.
#. Szekvenciálisan hajtandó végre.

:math:`\rhd` Egy 8 elemű sorozaton vizsgáljuk meg az algoritmus működését!

Kérdések
--------

* Adjon példát egy véges (kis elemszámú) halmazon részben rendezésre!
* Milyen a beszúrásos rendezés időbonyolultsága?
* Milyen a minimumkiválasztásos rendezés időbonyolultsága?
* Milyen az összefésülés időbonyolultsága :math:`n` és :math:`m` méretű bemenetek esetében?
* Miért előnyös az összefésülő rendezés esetében a :math:`q` érték ilyesfajta megválasztási módja? Működne-e az algoritmus tetszőleges :math:`q \in [p, r]` esetében?
* Milyen a buborékrendezés időbonyolultsága?
* A Shell rendezés esetében mi az elvárás a növekmények sorozatára vonatkozóan?
* Mi a legrosszabb esete a gyorsrendezésnek (feltéve, hogy mindig az első elemet választjuk pivót elemnek)?
* Egy 32 elemű tömb rendezése esetében mennyi az optimális rekurzív hívási fa magassága?

Feladatok
---------

Beszúró rendezés
~~~~~~~~~~~~~~~~

* Írja fel a beszúró rendezés pszeudó kódját!
* Mérje le és ábrázolja a kapott eredményeket a beszúró rendezés időbonyolultságára vonatkozóan!
* Vizsgáljuk meg egy 10 elemű minta rendezése esetében, hogy két beszúró iterátor használatával milyen gyorsítás érhető el! (Feltételezzük, hogy a számítások várakoztatás nélkül párhuzamosan futnak!)

Minimumkiválasztásos rendezés
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Írja fel a minimumkiválasztásos rendezés pszeudó kódját!
* Végezzen méréseket az algoritmus időbonyolultságára vonatkozóan!
* Írjon egy rekurzív felbontásra épülő párhuzamos algoritmust a rendezési feladat megoldására!
* Hasonlítsa össze azonos bemenetek esetén a szekvenciális és a párhuzamos futási időket!

Összefésülő rendezés
~~~~~~~~~~~~~~~~~~~~

* Írja fel annak az algoritmusnak a pszeudó kódját, amelyik párhuzamosan fésüli össze a két bemeneti tömb elejét és végét!
* Írja át a ``COPY`` műveletet egy procedúrára úgy, hogy szerepeljenek benne a másoláshoz használt indexek! (Feltételezzük, hogy az eredmény tömb allokálása automatikusan megtörténik.)
* Írja fel a 2. és 3. ``WHILE`` ciklust a ``COPY`` eljárás meghívásával!
* Végezzen becsléseket arra vonatkozóan, hogy milyen gyorsítás lenne elérhető, hogy ha a ``COPY`` műveleteket teljesen párhuzamosítva lehetne végrehajtani! (Ehhez készítsen véletlenszerű bemenetekkel futtatásokat, amelyekkel az eredeti összefésülő algoritmust felhasználva meghatározhatja a konkrét összehasonlítások és értékbeállítások számát!)
