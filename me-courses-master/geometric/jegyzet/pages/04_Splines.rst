***************
B-Spline görbék
***************

*Bases Spline*

.. seealso::

   * https://en.wikipedia.org/wiki/B-spline
   * https://en.wikipedia.org/wiki/Spline_(mathematics)
   * https://en.wikipedia.org/wiki/Flat_spline
   * https://en.wikipedia.org/wiki/Isaac_Jacob_Schoenberg

Normalizált B-spline alapfüggvény
=================================

Tekintsük az :math:`u_i \in \mathbb{R}, i \in \mathbb{Z}` értékeket, amelyekre teljesül, hogy :math:`u_i \leq u_{i+1}`! A B-spline alapfüggvényt az alábbi rekurzív formában definiálhatjuk:

.. math::

  N_i^1(u) = \begin{cases}
  1, & \text{ha } u_i \leq u < u_{i+1}, \\
  0, & \text{egyébként},
  \end{cases}
  
.. math::

  N_i^k(u) = \dfrac{u - u_i}{u_{i+k-1} - u_i} N_i^{k-1}(u) + \dfrac{u_{i+k} - u}{u_{i+k} - u_{i+1}} N_{i+1}^{k-1}(u).

* Az :math:`\{u_i\}_{i \in \mathbb{Z}}` értékeket csomóértékeknek (*knot values*) hívjuk.
* A komponenseikből képzett vektor a csomóvektor (*knot vector*).
* Ahol 0-val való osztás fordulna elő, ott az eredményt 0-nak tekintjük.

:math:`\rhd` Írjuk fel és ábrázoljuk a másod- és harmadfokú B-spline alapfüggvényeket!

Az :math:`u_i` értékek megválasztására itt is alkalmazhatunk egyenközű (vagy másnéven uniform) felosztást, például :math:`u_i = i`.

Az azonos fokszámú görbék eltolással származtathatók egymásból, vagyis

.. math::

  N_i^k(u) = N_0^k(u - i), \quad \forall i \in \mathbb{Z}.

.. note::

  * A :math:`k`-adrendű B-spline alapfüggvények (legfeljebb) :math:`(k-1)`-edfokú polinomokat tartalmaznak.
  * Az :math:`N_i^k` csak az :math:`(u_i, u_{i+k})` intervallumon lehet 0-tól különböző.
  * Tekintsük az :math:`[u_i, u_{i+1})` intervallumot! Ennek azon :math:`N_j^k` normalizált B-spline alapfüggvényekre van hatása, ahol :math:`(i - k + 1) \leq j \leq i`.

Lokalitási tétel
----------------

.. math::

  N_i^k(u) = 0, \text{ha } u \notin [u_i, u_{i+k}).

.. admonition:: Bizonyítás (indukciós)

  :math:`k = 1` esetén az állítás definíció szerint teljesül.

  Helyettesítsük vissza a :math:`(k-1)` értéket, és vegyük észre, hogy

  .. math::

    \begin{align}
    &N_i^{k-1}(u) = 0, \text{ha } u \notin [u_i, u_{i+k-1}), \\
    &N_{i+1}^{k-1}(u) = 0, \text{ha } u \notin [u_{i+1}, u_{i+k}). \\
    \end{align}

  Mivel :math:`u \notin [u_i, u_{i+k})` esetén ezeknek a lineáris kombinációját kellene venni (az :math:`u` érték és a csomóértékek függvényében), ezért biztosan 0 lesz az értéke. :math:`\square`


Nemnegativitási tétel
---------------------

A normalizált B-spline alapfüggvények nemnegatívak, vagyis

.. math::

  N_i^k(u) \geq 0, \forall u \in \mathbb{R}, i \in \mathbb{Z}, k \geq 1.


Egységfelbontási tétel
----------------------

A :math:`k`-adrendű normalizált B-spline alapfüggvények egységfelbontást alkotnak, azaz

.. math::

  \sum_j N_j^k (u) = 1, \quad \forall u \in \mathbb{R}, \forall k \geq 1.


Többszörös csomóértékek
-----------------------

A definíció lehetővé teszi, hogy ugyanazon :math:`u_i` értékeket többször is szerepeltessünk. Vizsgáljuk meg harmadfokú B-spline alapfüggvény esetén a hatását!

A harmadfokú B-spline alapfüggvény a következőképpen írható föl:

.. math::

  N_i^3(u) =
  \begin{cases}
  \dfrac{(u-u_i)^2}{(u_{i+2}-u_i)(u_{i+1}-u_i)},
  & \text{ha } u \in [u_i, u_{i+1}), \\
  \dfrac{(u-u_i)(u_{i+2}-u)}{(u_{i+2}-u_i)(u_{i+2}-u_{i+1})}
  + \dfrac{(u_{i+3}-u)(u-u_{i+1})}{(u_{i+3}-u_{i+1})(u_{i+2}-u_{i+1})},
  & \text{ha } u \in [u_{i+1}, u_{i+2}), \\
  \dfrac{(u_{i+3}-u)^2}{(u_{i+3}-u_{i+1})(u_{i+3}-u_{i+2})},
  & \text{ha } u \in [u_{i+2}, u_{i+3}), \\
  0, & \text{egyébként}.
  \end{cases}

Tegyük fel, hogy :math:`u_{i+1} = u_{i+2}` teljesül! Ekkor azt kapjuk, hogy

.. math::

  N_i^3(u) = \begin{cases}
  \dfrac{(u - u_i)^2}{(u_{i+1} - u_i)^2},
  & \text{ha } u \in [u_i, u_{i+1}), \\
  \dfrac{(u_{i+3} - u)^2}{(u_{i+3} - u_{i+1})^2},
  & \text{ha } u \in [u_{i+1}, u_{i+3}), \\
  0, & \text{egyébként}.
  \end{cases}

Szemléletesen tulajdonképpen egymáshoz toltuk az :math:`u_{i+1}` és :math:`u_{i+2}` értékeket. Az alapfüggvény így az adott pontban folytonos maradt, viszont már nem differenciálható.

Több csomóérték egybeesését mint csomóérték multiplicitást definiálhatjuk.

Egy csomóérték multiplicitása :math:`m`, hogy ha :math:`m` darab egymás utáni csomóérték esik egybe, vagyis

.. math::

  u_{i-1} < u_i = u_{i+1} = \cdots = u_{i+m-1} < u_{i+m}.

Kapcsolat a Bernstein polinomokkal
----------------------------------

Az

.. math::

  u_0, u_1 = u_2 = \ldots = u_{k-1}, u_k = u_{k+1} = \ldots = u_{2k-2} = 1, u_{2k-1}

csomóértékek esetében teljesül, hogy

.. math::

  N_i^{k-j}(u) = B_{i-j}^{k-1-j}(u), \forall u \in [u_{k-1}, u_k], i = 0, 1, \ldots, k - 1, j = 0, 1, \ldots, i.

Multiplicitásra vonatkozó tétel
-------------------------------

Hogy ha az :math:`u_i` csomóérték multiplicitása :math:`k`, akkor :math:`N_i^k(u_i) = 1`.

Derivált
--------

Az :math:`N_i^k(u)` normalizált B-spline alapfüggvény deriváltja:

.. math::

  \dfrac{\mathrm{d}}{\mathrm{d}u}
  N_i^k(u) = (k - 1)
  \left(
  \dfrac{1}{u_{i+k-1}-u_i}N_i^{k-1}(u)
  - \dfrac{1}{u_{i+k} - u_{i+1}}N_{i+1}^{k-1}(u)
  \right),

ahol :math:`[u_i, u_{i+k})`.

Lineáris függetlenség
---------------------

Az :math:`\{N_j^k\}_{j=i-k+1}^i` normalizált B-spline alapfüggvények lineárisan függetlenek az :math:`[u_i, u_{i+1})` intervallumon, hogy ha :math:`u_i < u_{i+1}`.


B-spline görbe
==============

Legyenek adottak a :math:`\textbf{d}_0, \textbf{d}_1, \ldots, \textbf{d}_n` kontrollpontok és az :math:`\{u_j\}_{j=0}^{n+k}` csomóértékek!
Az

.. math::

  \textbf{s}(u) = \sum_{i=0}^n N_i^k(u) \textbf{d}_i,
  u \in [u_{k-1}, u_{n+1}], 1 < k < n + 1

formában definiált görbét :math:`k`-adrendű (vagy :math:`(k-1)`-edfokú) B-spline görbének nevezzük.

* A :math:`\textbf{d}_i` pontokat kontrollpontoknak (vagy de Boor pontoknak) nevezzük.
* Az :math:`N_i^k` az :math:`i`-edik :math:`(k-1)`-edfokú normalizált B-spline görbét jelöli.

A B-spline görbe általános esetben approximációs görbe. Kivételt képezhetnek például az alábbi esetek.

* Hogy ha :math:`k = 2`, akkor a kontrollpoligont kapjuk vissza.
* Áthaladhat a kontrollpontokon, hogy ha a pontok  kollineárisak.
* Hogy ha a kezdő és a végpontban a multiplicitás :math:`k`, akkor a Bézier görbéhez hasonlóan interpolál a végpontokban.

.. note::

  Utóbbit egyszerűen beláthatjuk. Tegyük fel, hogy :math:`u_1 = u_2 = \cdots = u_{k-1}`! A görbe pontját az :math:`u_{k-1}` paraméternél a következőképpen számíthatjuk ki:

  .. math::

    \textbf{s}(u_{k-1}) =
    \sum_{i=0}^{k-1} N_i^k(u_{k-1}) \textbf{d}_i.

  Tudjuk, hogy :math:`N_i^k(u_{k-1}) = 0`, hogy ha :math:`i \in [1, k-2]`. A tétel alapján az :math:`N_0^k(u_{k-1}) = 1` összefüggést kihasználva adódik, hogy

  .. math::

    \textbf{s}(u_{k-1}) = \textbf{d}_0.

  Hasonlóképpen kikövetkeztethető, hogy a :math:`\textbf{d}_n` pontban szintén interpolálni fog a görbe a megfelelő multiplicitást megadva.


A görbe tulajdonságai
---------------------

A B-spline görbe lokálisan változtatható, vagyis egy kontrollpont megváltoztatása csak a görbe egy adott részére van hatással, nem az egészre.

Egy :math:`(k-1)`-edfokú B-spline görbe bármely íve a :math:`k` darab egymást követő kontrollpontjának konvex burkában van.

A de Boor-algoritmus
--------------------

A de Boor-algoritmus, egy, a de Castejau algoritmushoz hasonló rekurzív eljárást segítségével is képes meghatározni a B-spline görbe egy adott, :math:`u` paraméterhez tartozó pontját. Egy numerikusan stabil eljárásról van szó.

Vezessük be a következő jelöléseket:

.. math::

  \alpha_j^l(u) = \begin{cases}
  1, & \text{ha } l = 0, \\
  \dfrac{u - u_j}{u_{j+k-l} - u_j}, & \text{ha } l > 0,
  \end{cases}

.. math::

  \textbf{d}_j^l(u) = \begin{cases}
  \textbf{d}_j, & \text{ha } l = 0, \\
  \alpha_j^l(u)\textbf{d}_j^{l-1}(u) + (1 - \alpha_j^l(u)) \textbf{d}_{j-1}^{l-1}(u), & \text{ha } l > 0,
  \end{cases}

ahol

.. math::

  l = 0, 1, \ldots, k - 1, j = i - k + 1 + l, \ldots, i.

Az :math:`l` érték a kitevőben az iteráció számát jelöli. Segédpontokat számolunk az :math:`\alpha` értékekből számolt arányokkal.

Az :math:`l < (k - 1)` lépésekben:

.. math::

  \textbf{s}(u) = \sum_{j=i-k+l+1}^i \textbf{d}_j^l(u) N_j^{k-l}(u),

az :math:`l = (k - 1)` lépésben:

.. math::

  \textbf{s}(u) = \textbf{d}_i^{k-1},

mivel

.. math::

  N_i^1(u) = \begin{cases}
  1, & \text{ha } u \in [u_i, u_{i+1}), \\
  0, & \text{egyébként}.
  \end{cases}

.. todo:: A pontok származtatási viszonyait ábrázolni!

Az algoritmus ugyan hasonló a de Casteljau algoritmushoz, de van néhány lényegi különbség ahhoz képest.

* A felosztás során nem :math:`u:(1-u)` arányban osztjuk fel a szakaszt.
* Egy pont előállításához nincs szükség az összes kontrollpontra. (Ebből adódik a görbe lokális vezérelhetősége.)
* Az algoritmus nem alkalmas a görbe kettévágására.

.. seealso::

   * https://en.wikipedia.org/wiki/De_Boor%27s_algorithm
   * https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/de-Boor.html

A görbe deriváltja
------------------

A B-spline görbe deriváltja az :math:`u \in [u_i, u_{i+1})` helyen az alábbi alakban írható föl:

.. math::

  \dfrac{\mathrm{d}}{\mathrm{d}u} \textbf{s}(u) =
  (k - 1)\sum_{j=i-k+2}^i
  \dfrac{\textbf{d}_j - \textbf{d}_{j-1}}{u_{j+k-1} - u_j} N_j^{k-1}(u).

Ez tehát azt jelenti, hogy egy :math:`(k - 1)`-edfokú B-spline görbe hodográfja egy :math:`(k - 2)`-edfokú B-spline görbe.

A derivált a de Boor algoritmus pontjai segítségével is felírható:

.. math::

  \dfrac{k-1}{u_{i+1} - u_i}
  (\textbf{d}_i^{k-2}(u) - \textbf{d}_{i-1}^{k-2}(u)).


Kérdések
========

* Hogyan definiáljuk a normalizált B-spline alapfüggvényt?
* Mondja ki a normalizált B-spline alapfüggvényre vonatkozó lokalitási tételt!
* Mondja ki a normalizált B-spline alapfüggvényre vonatkozó nemnegativitási tételt!
* Mondja ki a normalizált B-spline alapfüggvényre vonatkozó egységfelbontási tételt!
* Definiálja a B-spline görbét!
* Milyen tulajdonságai vannak a B-spline görbének?

Programozási feladatok
======================

Görbe megjelenítése, vizsgálata
-------------------------------

* Készítsünk egy programot, amely 8 kontrollpontra képes megjeleníteni a B-spline görbét!
* Oldjuk meg, hogy a görbe rendjét lehessen változtatni!
* Jelenítsük meg egy mozgatott kontrollpont esetén, hogy annak hatására a görbe mely része tud csak változni!
* Oldjuk meg, hogy meg lehessen adni a kontrollpontok multiplicitását!
* Jelenítsük meg a görbék szakaszait és a hozzájuk tartozó konvex burkokat (például váltogatva közöttük), amelyek esetében a görbe semmiképpen sem léphet ki azokon.
* Implementálja a de Boor algoritmust!
* Számítsa ki és jelenítse meg a görbe adott pontjához tartozó irányvektort és normálvektort!

Elérhető implementációk
-----------------------

Vizsgáljuk meg, hogy milyen elérhető implementáció vannak a B-spline függvényeknek és görbéknek! Például:

* https://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.BSpline.html

További feladatok
=================

* Implementálja a B-spline görbével történő interpolációt!
* Vizsgálja meg, hogy nagy számú (enyhén zajos) ponthalmaz esetén hogyan lehet közelítést adni egy :math:`k`-adrendű B-spline görbével!
* Vizsgálja meg és hasonlítsa össze azokat az algoritmusokat, amelyre (azonos megjelenítési pontosságot feltételezve) minimializálni lehet a kirajzolandó szakaszok számát!
* Határozza meg tetszőleges görbe esetén azon különböző :math:`u_i` értékeket, amelyeknél a görbe saját magát metszi!
* Adjon közelítést egy zárt, B-spline görbékkel határolt alakzat területére!
* Dolgozzon ki egy eljárást, amellyel adott B-spline görbéhez alacsonyabb rendű B-spline görbe közelítést lehet adni! Vizsgálja meg a közelítés pontosságát!

