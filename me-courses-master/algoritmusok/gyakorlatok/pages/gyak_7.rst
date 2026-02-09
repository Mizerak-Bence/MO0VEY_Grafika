7. Hasítótáblák
===============

Kérdések
--------

* Milyen számítási idejű a tömb és a lista esetében egy adott kulcsú elem beszúrása, keresése és törlése?
* Mi lenne számítási időre vonatkozóan az ideális eset?
* Milyen előnyökkel és hátrányokkal járna egy kulcstér méretével megegyező méretű tömb használata?

Jelölések
---------

* *k*: key, kulcs
* *h*: hash function, hasító függvény
* *m*: a tábla mérete
* *n*: a táblába beszúrt kulcsok száma
* :math:`\alpha`: telítettségi arány, kitöltési arány

Közvetlen címzés
----------------

Készítsünk egy 7 méretű hasítótáblát, amelynél a következő hasítófüggvényt használjuk:

.. math::

	h(k) = k \mod 7

Végezzük el a következő műveleteket!

.. math::

	10, 15, 6, 40, 24

A közbülső állapotok követéséhez készítsünk táblázatot!

.. csv-table::
   :header-rows: 1
   
   index, kulcs
   0,
   1,
   2,
   3,
   4,
   5,
   6,

* Hogyan tudjuk kezelni az ütközési problémát?
* Mi jellemez egy jó hasítófüggvényt?

Láncolt listás hasítótábla
--------------------------

A kulcsok helyére egy láncolt fej elemét tesszük. Ezekben a listákban tároljuk magukat a kulcsokat.

Egy 5 méretű láncolt listás hasító táblába végezzük el a következő műveleteket!

.. math::

	12, 8, 58, 25, T8, 72, 14, 47, T25, 30, 23

.. csv-table::
   :header-rows: 1
   
   i, fej[:math:`L_i`]
   0, NIL
   1, NIL
   2, NIL
   3, NIL
   4, NIL

* Mennyi a kitöltési arány?
* Van-e jelentősége annak, hogy a lista elejére vagy a végére szúrunk be egy elemet?
* Egy ideális hasítófüggvény esetén egy :math:`m` méretű táblával milyen gyorsítást tudunk elérni a lineáris kereséshez képest?

Összenövő listás hasítótábla
----------------------------

Készítsünk egy 11 méretű összenövő listás hasító táblát, és végezzük el az alábbi műveleteket!

.. math::

	20, 37, 27, 89, 31, 16, 59, 76

.. csv-table::
   :header-rows: 1
   
   i, kulcs, köv
   0, NIL, NIL
   1, NIL, NIL
   2, NIL, NIL
   3, NIL, NIL
   4, NIL, NIL
   5, NIL, NIL
   6, NIL, NIL
   7, NIL, NIL
   8, NIL, NIL
   9, NIL, NIL
   10, NIL, NIL

* Mennyi az :math:`\alpha` értéke?
* Keressük vissza a 16-os és 76-os értéket!
* Hogyan valósítható meg a törlés művelet?

Nyílt címzések
--------------

* Mindent a táblában tárolunk.
* A :math:`h(k)` helyett a :math:`h(k, i)` függvényt fogjuk használni, ami a :math:`h(k)` kiterjesztése próbálkozási sorozattal.
* Bevezetünk egy foglaltságot jelző mezőt, amelynek *szabad*, *foglalt* vagy *törölt* lehet az értéke. (Ezeket *sz*, *f* és *t* formában jelöljük.)

.. csv-table::
   :header-rows: 1
   
   i, foglaltság, kulcs
   0, sz, 
   1, sz,
   2, sz,
   3, sz,
   4, sz,
   5, sz,
   6, sz,

Lineáris kipróbálás
-------------------

.. math::

	\begin{align*}
	h_0(k) &= k \mod m, \\
	h(k, i) &= (h_0(k) + i) \mod m
	\end{align*}

Példa:

Egy 11 méretű táblára végezzük el a következő műveleteket!

.. math::

	503, 176, 117, 624, T117, 591, T503, 757, K757

* Mennyi a telítettségi arány?
* Mi volt a kipróbálási sorozat maximális indexe?

Négyzetes kipróbálás
--------------------

.. math::

	\begin{align*}
	h_0(k) &= k \mod m, \\
	h(k, i) &= \left(h_0(k) + \dfrac{i \cdot (i + 1)}{2}\right) \mod m
	\end{align*}

Példa:

Egy 7 méretű táblára végezzük el a következő műveleteket!

.. math::

	549, 970, 615, 348, T615, 902, T549, 614, K348

* Mennyi a telítettségi arány?
* Mi volt a kipróbálási sorozat maximális indexe?

Dupla hasítás
-------------

.. math::

	\begin{align*}
	h_0(k) &= k \mod m, \\
	h_1(k) &= 1 + (k \mod (m - 1)), \\
	h(k, i) &= (h_0(k) + i \cdot h_1(k)) \mod m
	\end{align*}

Példa:

Egy 7 méretű táblára végezzük el a következő műveleteket!

.. math::

	428, 331, 555, 888, T555, 722, T428, 138, K888

* Mennyi a telítettségi arány?
* Mi volt a kipróbálási sorozat maximális indexe?

Fibonacci keresés
-----------------

Tekintsük az alábbi 143 elemű tömböt!

.. csv-table::
   :header-rows: 1

	,**0**,**1**,**2**,**3**,**4**,**5**,**6**,**7**,**8**,**9**
	**0**,,121,122,125,132,136,144,150,156,163
	**1**,166,168,169,176,182,190,197,200,203,204
	**2**,208,210,213,214,217,218,226,228,229,237
	**3**,244,252,257,262,270,278,285,286,289,291
	**4**,299,300,301,307,313,317,324,325,332,335
	**5**,341,347,348,349,350,358,360,366,374,376
	**6**,380,388,396,398,400,405,413,420,422,426
	**7**,431,438,440,448,456,463,465,471,474,477
	**8**,481,482,486,494,502,509,517,523,526,528
	**9**,535,539,542,547,554,562,567,573,578,586
	**10**,593,594,602,606,609,614,620,625,630,634
	**11**,640,643,650,655,656,663,669,677,679,685
	**12**,688,696,698,699,705,707,712,716,721,727
	**13**,734,740,744,746,749,752,760,762,767,770
	**14**,774,780,788,796,,,,,,

Az értékekről tudjuk, hogy különbözőek, és monoton növekvő sorozatot alkotnak.

Fibonacci keresés segítségével határozzuk meg a 400 kulcsú elemet a tömbben!

.. csv-table::
   :header-rows: 1
   
   :math:`i`,:math:`p`,:math:`q`,:math:`a_i`
   89,55,34,:math:`\ldots`

Interpolációs keresés
---------------------

Jelölje :math:`x` a keresett elemet, a keresési intervallumunkat pedig :math:`[i, j]`.
Egy elem helyét a tömbben közelítsük a következő összefüggéssel!

.. math::

	k = \text{Round}\left( i + (j - i) \cdot \dfrac{x - a_i}{a_j - a_i} \right)

A keresést a kapott :math:`k` értéktől függően folytassuk az :math:`[i, k - 1]` vagy a :math:`[k + 1, j]` intervallumban!

Keressük meg az :math:`x = 400` kulcsú elem helyét a tömbben!

.. csv-table::
   :header-rows: 1
   
   :math:`i`,:math:`j`,:math:`k`,:math:`a_k`
   1,143,:math:`\ldots`,

* Milyen leállási feltételt tudom adni az algoritmusnak arra az esetre, hogy ha a keresett :math:`x` elem nem lenne benne az :math:`A` tömbben?

Bináris keresés
---------------

Vizsgáljuk meg az előbbi keresési feladatot bináris keresés esetében is!
