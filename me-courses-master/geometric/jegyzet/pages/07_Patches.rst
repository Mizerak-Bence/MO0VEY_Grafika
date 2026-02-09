***********************
További felület típusok
***********************

Coons foltok
============

A spline-okhoz hasonlóan a felületek esetében is adódik a lehetőség, hogy a teljes felület leírását kisebb részek összekapcsolásával oldjuk meg. Ezeket foltoknak nevezzük, amelyek jellemzően egy téglalap vagy háromszög alakú paramétertartományból kerülnek leképzésre, így végeredményben görbe ívekből összeállított négyszöget vagy háromszöget kaphatunk.

A Coons foltok esetében görbe oldalú négyszögeket szeretnénk előállítani. Ehhez tekintsük az :math:`u \in [0, 1]` és :math:`v \in [0, 1]` tartományokat. (Ezt jelölhetjük az :math:`(u, v) \in [0, 1] \times [0, 1]`, vagy rövidebben az :math:`(u, v) \in [0, 1]^2` formában.)

Tekintsük az :math:`\textbf{a}_1(u), \textbf{a}_2(u), \textbf{b}_1(v), \textbf{b}_2(v)` görbéket! Keressük azt az :math:`\textbf{s}(u, v)` felületet, amelyre teljesülnek az alábbi feltételek:

.. math::

  \begin{align}
  \textbf{s}(u, 0) &= \textbf{a}_1(u), \\
  \textbf{s}(u, 1) &= \textbf{a}_2(u), \\
  \textbf{s}(0, v) &= \textbf{b}_1(v), \\
  \textbf{s}(1, v) &= \textbf{b}_2(v). \\
  \end{align}

Bilineárisan súlyozott Coons folt
---------------------------------

Az :math:`\textbf{a}_1` és :math:`\textbf{a}_2` görbékkel, illetve a :math:`\textbf{b}_1` és :math:`\textbf{b}_2` görbékkel két vonalfelületet is elő tudunk állítani:

.. math::

  \begin{align}
  \textbf{l}_{a}(u, v) &= (1 - v)\textbf{a}_1(u) + v \textbf{a}_2(u), \\
  \textbf{l}_{b}(u, v) &= (1 - u)\textbf{b}_1(v) + u \textbf{b}_2(v). \\
  \end{align}

Egyszerűen látható, hogy az :math:`\textbf{l}_{a}(u, v)` felület csak az :math:`\textbf{a}_1(u)` és :math:`\textbf{a}_2(u)` görbékre fog biztosan illeszkedni, míg az :math:`\textbf{l}_{b}(u, v)` felület csak a :math:`\textbf{b}_1(v)` és :math:`\textbf{b}_2(v)` görbékre.

Tekintsük a csúcspontok bilineáris kombinációját, amelyet például az alábbi formában számolhatunk:

.. math::

  \textbf{l}_{ab}(u, v) =
  \begin{bmatrix}
  (1 - u) & u \\
  \end{bmatrix}
  \begin{bmatrix}
  \textbf{s}(0, 0) & \textbf{s}(0, 1) \\
  \textbf{s}(1, 0) & \textbf{s}(1, 1) \\
  \end{bmatrix}
  \begin{bmatrix}
  1 - v \\
  v \\
  \end{bmatrix}.

Ennek a segítségével a Coons foltot az alábbi formában kapjuk:

.. math::

  \textbf{s}(u, v) = \textbf{l}_{a}(u, v) + \textbf{l}_{b}(u, v) - \textbf{l}_{ab}(u, v).

.. note::

  A bilineárisan súlyozott Coons folt esetében a bilineáris az előállítási módra vonatkozik. Maga az :math:`\textbf{l}_{ab}(u, v)` az, ami a csúcspontok bilineáris súlyozásával áll elő, mint felület. Egyszerűen látható, hogy így a bilineáris felületek a Coons foltok egyenes szakaszokkal leírt speciális esetei.

.. seealso::

  * https://www.mathcurve.com/surfaces.gb/patchcoons/patchcoons.shtml

Bikubikus Coons folt
--------------------

A bilineáris súlyozás esetében a folthoz a határoló görbéket adtuk meg. Előfordulhat azonban, hogy (például más felületdarabokhoz való illesztés miatt) a görbék mentén az érintővektorokat is rögzíteni szeretnénk. Ez a határoló görbéken a keresztirányú deriváltak megadását jelenti.

A folt szélein az érintőket, mint függvényt adhatjuk meg. Legyenek adottak

* az :math:`\textbf{a}_1(u)`, :math:`\textbf{a}_2(u)`, :math:`\textbf{b}_1(v)`, :math:`\textbf{b}_2(v)` határoló görbék,
* az :math:`\textbf{a}_{1v}(u)`, :math:`\textbf{a}_{2v}(u)`, :math:`\textbf{b}_{1u}(v)`, :math:`\textbf{b}_{2u}(v)` keresztirányú deriváltakat leíró függvények,
* az :math:`\textbf{s}_{uv}(0, 0)`, :math:`\textbf{s}_{uv}(0, 1)`, :math:`\textbf{s}_{uv}(1, 0)`, :math:`\textbf{s}_{uv}(1, 1)` twist vektorok.

A megoldandó feladat, hogy találjunk egy olyan :math:`\textbf{s}(u, v)` felületet, amely teljesíti az alábbiakat:

* :math:`\textbf{s}(u, 0) = \textbf{a}_1(u)`, :math:`\textbf{s}(u, 1) = \textbf{a}_2(u)`, :math:`\textbf{s}(0, v) = \textbf{b}_1(v)`, :math:`\textbf{s}(1, v) = \textbf{b}_2(v)`,
* :math:`\textbf{s}_v(u, 0) = \textbf{a}_{1v}(u)`, :math:`\textbf{s}_v(u, 1) = \textbf{a}_{2v}(u)`, :math:`\textbf{s}_u(0, v) = \textbf{b}_{1u}(v)`, :math:`\textbf{s}_u(1, v) = \textbf{b}_{2u}(v)`,

bármely :math:`u, v \in [0, 1]` esetén.

A probléma megoldása annyiban különbözik a bilineáris súlyozásos foltokétól, hogy itt nem egyenes szakaszokat használunk, hanem Hermit íveket, így a folt széleinél figyelembe tudjuk venni a keresztirányú érintőket.

Hermite-féle bikubikus folt
---------------------------

A bikubikus foltoknak egy speciális eseteként tekinthetjük a Hermite-féle bikubikus foltokat. Ennél a határoló görbéket Hermite íveknek válasszuk meg. A folttal kapcsolatos elvárások megegyeznek. Tulajdonképpen a konkrét görbe ismeretében adódnak lehetőségek a számítások konkretizálására, egyszerűsítésére.

.. note::

  Foltok összekapcsolása esetén külön problémát jelent a twist vektorok meghatározása úgy, hogy azok az illeszkedési pontokban megegyezzenek.


Bézier-felület
==============

A felületek görbék tenzori szorzataként való előállításánál nem konkretizáltuk, hogy milyen típusú görbékről van szó. Amennyiben ezek Bézier-görbék, akkor Bézier-felületeket kapunk.

Definíció
---------

Legyenek adottak a :math:`\{\textbf{b}_{ij}\}_{i=0,j=0}^{n,m}` kontrollpontok (összességében a belőlük alkotott kontrollháló). Az :math:`(n, m)`-fokú Bézier-felületet az alábbi felírással kapjuk:

.. math::

  \textbf{s}(u, v) = \sum_{i=0}^{n} \sum_{j=0}^m \textbf{b}_{ij} B_i^n(u) B_j^m(v), \quad (u, v) \in [0, 1]^2.

Tulajdonságok
-------------

* Mindegy, hogy a kontrollháló poligonjain milyen irányból haladunk végig, ugyanazt a Bézier-felületet fogjuk kapni. (*Szimmetria tulajdonság*)
* A határoló görbék illeszkednek a felületre, de a kontrollháló többi pontja általában nem. (*Approximációs jelleg*)
* A felület bármely pontjához tartozó paramétervonalak Bézier-görbék (:math:`n`-ed és :math:`m`-ed fokúak).
* A felület pontját a de Casteljau algoritmussal számíthatjuk. Sorrendet tekintve mindegy, hogy az :math:`u` vagy a :math:`v` paraméterű görbéből indulunk ki, ugyanazt a felületi pontot fogjuk kapni. A számítási igény viszont különbözni fog (hogy ha :math:`n \neq m`).
* A felületet a de Casteljau algoritmus segítségével a paramétervonalainál kettévághatjuk.
* A felület a kontrollhálójának affin transzformációjával szemben invariáns.
* A felület a kontrollháló pontjainak (egyszerűbben a kontrollpontoknak) a konvex burkában van. Ez tekinthető annak a következményének, hogy a felület pontjait a kontrollpontok konvex kombinációjaként kaphatjuk meg.
* A felület invariáns a paramétertartomány affin transzformációjára.

A Bézier-felület esetében is tudjuk alkalmazni a Bézier-görbéknél megismert fokszámnövelési módszert.

A de Casteljau algoritmus térben
--------------------------------

A szakaszok esetében egy paraméterünk van, így az arányos osztást egyszerűen az :math:`u : (1 - u)` felosztással meg tudtuk tenni.

Térben, háromszög esetében baricentrikus koordinátákat tudunk használni. Így, az eredeti de Casteljau algoritmust felületekre is tudjuk általánosítani, amellyel Bézier háromszögeket tudunk leírni.

.. todo:: Saját példával, számításokkal is részletesen kidolgozni!

.. seealso::

  * https://blog.demofox.org/2019/12/07/bezier-triangles/
  * https://en.wikipedia.org/wiki/B%C3%A9zier_triangle

B-spline felületek
==================

Felületeket tenzori szorzatként B-spline görbék felhasználásával is létre tudunk hozni.

Definíció
---------

Legyenek adottak

* a :math:`\{\textbf{d}_{ij}\}_{i=0,j=0}^{n,m}` kontrollpontok (de Boor-pontok),
* az :math:`N_i^k` (:math:`i`-edik :math:`(k-1)`-edfokú) és az :math:`N_j^L` (:math:`j`-edik :math:`(l-1)`-edfokú) normalizált B-spline alapfüggvények,
* az :math:`u_0 \leq u_1 \leq \cdots \leq u_{n+k}` és :math:`v_0 \leq v_1 \leq \cdots v_{m+l}` csomóértékek, ahol :math:`1 < k \leq (n + 1)` és :math:`1 < l \leq (m + 1)`.

A B-spline felületet az 

.. math::

  \textbf{s}(u, v) = \sum_{i=0}^{n} \sum_{j=0}^m \textbf{d}_{ij} N_i^n(u) N_j^m(v)

alakban definiálhatjuk, ahol :math:`(u, v) \in [u_{k-1}, u_{n+1}] \times [v_{l-1}, v_{m+1}]`.

Tulajdonságok
-------------

* A felület paramétervonalai B-spline görbék.
* A felület lokálisan módosítható. A :math:`\textbf{d}_{ij}` kontrollpont elmozdítása csak az :math:`(u, v) \in [u_i, u_{i+k}] \times [v_j, v_{j+l}]` tartomány feletti felületrészre van hatással.
* A felület egy :math:`(u, v) \in [u_i, u_{i+1}) \times [v_j, v_{j+1})` pontja a :math:`[\textbf{d}_{rs}]_{r=i-k+1,s=j-l+1}^{i,j}` kontrollpontjainak konvex burkában van.
* A felület pontjait a de Boor algoritmus segítségével is meghatározhatjuk. Az iránytól függetlenül ugyanazt a pontot fogjuk kapni, viszont a számítási lépések száma különbözhet.

Racionális felületek
====================

A felület tenzori szorzatként való előállításához racionális görbéket is használhatunk.

* Racionális Bézier-görbék alkalmazása esetén racionális Bézier-felületet kapunk.
* Racionális B-spline görbék alkalmazása esetén racionális B-spline felületet kapunk.


Kérdések, elméleti feladatok
============================

* Mit nevezünk Coons foltnak? Hogyan számítható ennek a bilineáris esete?
* Definiálja a Bézier felületeket, és adja meg a jellegzetes tulajdonságaikat!
* Definiálja a B-spline felületeket, és adja meg a jellegzetes tulajdonságaikat!

Számítási feladatok
===================

Egy bilineárisan súlyozott Coons foltnak adott a 4 határoló görbéje.

* Vizsgálja meg, hogy a 4 görbe megfelelően illeszkedik-e egymáshoz!
* Határozza meg a felület pontját egy adott :math:`(u, v)` paraméternél!

Programozási feladatok
======================

Coons foltok
------------

* Implementáljon egy programot, amely segítségével vizsgálhatók a 4 darab Hermit-ívvel körülhatárolt, bilineáris Coons foltok!

Bézier felületek
----------------

* Készítsen egy programot, amely egy :math:`4 \times 4`-es kontrollháló alapján megjelenít egy Bézier felületet!
* Oldja meg, hogy a kontrollháló megjelenítését be- és ki lehessen kapcsolni!
* Készítsen a programba két csúszkát, amellyel meg lehet adni egy :math:`(u, v)` párt, és jelenítse meg az ezekhez tartozó paramétervonalakat!
* Jelenítse meg az :math:`(u, v)` paraméterekhez tartozó iránymenti deriváltakat és a normálvektort!
* Adjon közelítést a felület felszínére!
* Implementálja a fokszámnövelést!

További feladatok
=================

* Adjon közelítést Bézier felületek segítségével gömbre!
* Mutassa be a gömbfelület megadásának néhány lehetséges módját racionális B-spline felületek esetében!
* Vizsgálja meg a Bézier görbék alkalmazásának lehetőségeit hengeres koordinátarendszer esetében!
* Vizsgálja meg a B-spline görbék alkalmazásának lehetőségeit gömbi koordinátarendszerben!
* Tegyük fel, hogy a térben adott nagy mennyiségű pontunk! Készítsen egy algoritmust, amely egy adott :math:`(n, m)`-edfokú Bézier-felület segítségével közelíti a pontok elhelyezkedését! Végezzen hibabecslést az :math:`n` és az :math:`m` paraméterek függvényében!
* Tegyük fel, hogy adott egy :math:`(n, m)`-edfokú Bézier-felület! Vizsgálja meg, hogy a felület metszi-e önmagát, és jelenítse meg azt a ponthalmazt (a felülettel megjelenítésével együtt), amely a metszetbe tartozik!

.. todo:: Nem négyzetes és háromszöges foltok esete

.. todo:: Metaballs

