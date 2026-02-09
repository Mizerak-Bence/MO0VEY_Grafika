********************
Interpolációs görbék
********************

.. todo:: 2 és 3 dimenziós eseteket is megnézni!

Az interpolációs feladat
========================

Legyenek adottak a :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n \in \mathbb{R}^D, n, D \in \mathbb{N}, n > 0`! Keresünk egy olyan :math:`\textbf{r}(u)` függvényt, amely esetében találhatunk olyan :math:`u_0, u_1, \ldots, u_n \in \mathbb{R}` paraméterértékeket, amelyek esetében teljesül, hogy :math:`\textbf{r}(u_i) = \textbf{p}_i, \forall i \in [0, n]`.

.. note::

   * A :math:`D` a tér dimenzióját jelöli, amelyben a görbét keressük.
   * Az indexelést lehetne 1-től is kezdeni. Általánosságban nincs jelentősége. Itt azért 0 kezdőindex szerepelt, mert a továbbiakban is az lesz a jellemző.
   * Az interpolációs feladat általánosságban nem követeli meg, hogy paraméteres görbét keressünk. A következőkben is paraméteres görbékkel foglalkozunk, ez az oka, hogy így került felírásra az általános eset is.
   * A modellező szempontjából az interpoláció praktikusan azt jelenti, hogy a modellezendő alakzat néhány pontját adjuk meg, és azok alapján, az interpolációs függvény segítségével számíthatjuk ki a többit.

A szakirodalomban az interpoláló görbét, és az interpolációs pontokat elég gyakran egyaránt :math:`\textbf{p}`-vel jelölik. Félreértést abban az esetben nem okoz, hogy ha tudjuk, hogy

* a :math:`\textbf{p}_i` egy pontsorozat :math:`i` indexű elemét jelöli, míg
* a :math:`\textbf{p}(u)` egy vektor értékű függvény :math:`u` pontban felvett értéke.


Lagrange interpoláció
=====================

Ebben az esetben a :math:`\textbf{p}(u)` egy legfeljebb :math:`n`-ed fokú polinomként keressük, vagyis az alábbi alakban:

.. math::

  \textbf{p}(u) = \textbf{a}_n u^n + \textbf{a}_{n-1} u^{n-1} + \cdots + \textbf{a}_1 u + \textbf{a}_0,

vagy röviden:

.. math::

  \textbf{p}(u) = \sum_{i=0}^n \textbf{a}_i u^i.


.. admonition:: Tétel

  Mindig van egyértelmű megoldása a problémának, hogy ha az interpolációs pontokhoz különböző :math:`u_i` értékeket választunk.

.. admonition:: Bizonyítás (konstruktív)

  Adjunk meg a :math:`\textbf{p}_i` interpolációs pontokhoz egy-egy :math:`u_i` értéket! Ezen :math:`u_i` értékekből felírhatunk

  .. math::

    \textbf{u}_i = \begin{bmatrix}
    u_i^0 & u_i^1 & \cdots & u_i^n \\
    \end{bmatrix}    

  vektorokat. Vegyük észre, hogy :math:`\textbf{p}_i = \textbf{u}_i \cdot \textbf{a}` teljesül :math:`\forall i \in [0, n]`!

  Ezek alapján felírható a következő mátrixos alak:

  .. math::

    \begin{bmatrix}
    u_0^0 & u_0^1 & \cdots & u_0^n \\
    u_1^0 & u_1^1 & \cdots & u_1^n \\
    \vdots & \vdots & \ddots & \vdots \\
    u_n^0 & u_n^1 & \cdots & u_n^n \\
    \end{bmatrix}
    \cdot
    \begin{bmatrix}
    \textbf{a}_0 \\
    \textbf{a}_1 \\
    \vdots \\
    \textbf{a}_n \\
    \end{bmatrix}
    =
    \begin{bmatrix}
    \textbf{p}_0 \\
    \textbf{p}_1 \\
    \vdots \\
    \textbf{p}_n \\
    \end{bmatrix},

  ahol az együtthatómátrix sorai az :math:`\textbf{u}_i` vektorok.

  Ahhoz, hogy létezzen, és egyértelmű megoldásunk legyen, az együtthatómátrix determinánsa nem lehet nulla. Vegyük észre, hogy az együtthatómátrix egy Vandermonde mátrix, amelynek a determinánsa

  .. math::

    \prod_{j < i} (u_i - u_j)

  formában számítható!

  Abban az esetben, hogy ha minden interpolációshoz ponthoz választott :math:`u` értékünk különböző, akkor a determináns biztosan nem lesz 0, így van egyértelmű megoldásunk. :math:`\square`

.. seealso::

  * https://en.wikipedia.org/wiki/Vandermonde_matrix
  * https://hu.wikipedia.org/wiki/Vandermonde-determin%C3%A1ns

Lagrange féle interpolációs polinom
-----------------------------------

Legyenek adottak :math:`u_i, i \in [0, n]` egymástól különböző értékek! Az ezekből képzett

.. math::

  L_i^n (u) = \dfrac
  {\prod_{j=0,j\neq i}^n (u - u_j)}
  {\prod_{j=0,j\neq i}^n (u_i - u_j)}, \quad i = 0, 1, \ldots, n

polinomokat :math:`n`-ed fokú Lagrange féle interpolációs polinomoknak nevezzük.

Ezek segítségével a Lagrange interpolációs görbét a

.. math::

  \textbf{p}(u) = \sum_{i=0}^{n} \textbf{p}_i L_i^n(u)

formában is felírhatjuk.

Az :math:`L_i^n(u)` értékek így a pontok egy :math:`u` paraméter szerinti konvex kombinációját adják, vagyis teljesül, hogy

.. math::

  \sum_{i=0}^n L_i^n(u) = 1.

A paraméterezéshez használt :math:`u_i, i \in [0, n]` pontokban teljesül, hogy :math:`L_i^n(u_j) = \delta_{ij}` (Kronecker delta), vagyis

.. math::

  L_i^n(u_j) = \begin{cases}
  1, & \text{ha } i = j, \\
  0, & \text{egyébként}.
  \end{cases}

.. note::

   * Előnye, hogy aránylag könnyen számítható.
   * Tervezésnél problémát okozhat, hogy a görbe csak globálisan vezérelhető.
   * A Lagrange interpolációt ilyen formában nem túl gyakran használják, mert hajlamos oszcillálni.
   * A töröttvonalas közelítés a Lagrange interpoláció egy speciális eseteként is tekinthető.

Hermit ív
=========

Tegyük fel, hogy két pontot szeretnénk interpolálni úgy, hogy ismertek a görbe végpontjaihoz tartozó érintővektorok.

Jelölje :math:`\textbf{p}_0` és :math:`\textbf{p}_1` az érintővektorokat, a :math:`\textbf{t}_0` és :math:`\textbf{t}_1` pedig az ezekhez tartozó érintővektorokat!

A görbét az

.. math::

  \textbf{a}(u) = \textbf{a}_0 + \textbf{a}_1 u + \textbf{a}_2 u^2 + \textbf{a}_3 u^3,
  \quad a \in [0, 1]

alakban keressük, amelyre teljesül, hogy

.. math::

  \textbf{a}(0) = \textbf{p}_0,
  \textbf{a}(1) = \textbf{p}_1, 
  \dot{\textbf{a}}(0) = \textbf{t}_0,
  \dot{\textbf{a}}(1) = \textbf{t}_1.

Az ezen feltételek alapján létrejött egyenletrendszer megoldása az együtthatókra:

.. math::

  \begin{align}
  \textbf{a}_0 &= \textbf{p}_0, \\
  \textbf{a}_1 &= \textbf{t}_0, \\
  \textbf{a}_2 &= 3(\textbf{p}_1 - \textbf{p}_0) - 2\textbf{t}_0 - \textbf{t}_1, \\
  \textbf{a}_3 &= -2(\textbf{p}_1 - \textbf{p}_0) + \textbf{t}_0 + \textbf{t}_1. \\
  \end{align}

:math:`\rhd` Ellenőrízzük, hogy valóban ez az egyenletrendszer megoldása!

Behelyettesítve és átrendezve:

.. math::

  \textbf{a}(u) =
  (2u^3 - 3u^2 + 1)\textbf{p}_0 +
  (-2u^3 + 3u^2)\textbf{p}_1 +
  (u^3 - 2u^2 + u)\textbf{t}_0 +
  (u^3 - u^2)\textbf{t}_1.

A számítást átírhatjuk az

.. math::

  \textbf{a}(u) =
  \begin{bmatrix}
  u^3 & u^2 & u & 1
  \end{bmatrix}
  \begin{bmatrix}
  2 & -2 & 1 & 1 \\
  -3 & 3 & -2 & -1 \\
  0 & 0 & 1 & 0 \\
  1 & 0 & 0 & 0 \\
  \end{bmatrix}
  \begin{bmatrix}
  \textbf{p}_0 \\
  \textbf{p}_1 \\
  \textbf{t}_0 \\
  \textbf{t}_1 \\
  \end{bmatrix},
  u \in [0, 1].

Ennek az alaknak megvan az a nagy előnye, hogy általában a görbe kirajzolásához azonos végpontok és az irányvektorok mellett kell a számítást több különböző :math:`u` értékre meghatározni, amely így egy :math:`\mathbb{R}^{4 \times 4}` mátrixszal való szorzást eredményez az :math:`u` értékekből számított vektorral.

Az interpolációt felírhatjuk Hermite polinomok segítségével is az

.. math::

  \textbf{a}(u) =
  \textbf{p}_0 H_0^3(u) +
  \textbf{p}_1 H_1^3(u) +
  \textbf{t}_0 H_2^3(u) +
  \textbf{t}_1 H_3^3(u)

alakban, melyben a harmadfokú Hermite polinomok

.. math::

  \begin{align}
  H_0^3(u) &= 2u^3 - 3u^2 + 1, \\
  H_1^3(u) &= -2u^3 + 3u^2, \\
  H_2^3(u) &= u^3 - 2u^2 + u, \\
  H_3^3(u) &= u^3 - u^2. \\
  \end{align}

.. note::

  * Az érintővektorok mellett magasabb fokú deriváltakat is megadhatunk. Ekkor az interpolációs polinom fokszáma is nagyobb lesz.
  * Általánosságban Hermite ívnek neveznek minden olyan görbét, melyet a végpontok és az azokban adott valamilyen rendű deriváltak alapján határozunk meg.


Interpoláló spline-ok
=====================

A tervezéshez a Hermite ív esetében megadott 2 interpolációs pont kevés lehet, illetve a Lagrange interpolációnál tapasztalható oszcilláció és globális vezérelhetőség is problémát jelenthet. Érdemes tehát olyan módszereket használni, melynél

* tetszőleges számú interpolációs pontot használhatunk,
* meg tudunk maradni a polinomos interpolációnál,
* a fokszámot alacsonyan tudjuk tartani.

Erre a megoldást az interpoláló spline-ok, mint több, alacsonyabb fokszámú polinomiális ív összekapcsolása jelenti.

.. seealso::

  * https://en.wikipedia.org/wiki/Spline_interpolation


Hermite ívek összekapcsolása
----------------------------

Legyenek adottak a :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n` interpolációs pontok, a hozzájuk rendelt, egymástól különböző :math:`u_0, u_1, \ldots, u_n` pontok, továbbá a :math:`\textbf{t}_0, \textbf{t}_1, \ldots, \textbf{t}_n` érintővektorok.

Keressük azt a :math:`\textbf{c}` görbét, melyre teljesül, hogy

.. math::

  \textbf{c}(u_i) = \textbf{p}_i, \dot{\textbf{c}}(u_i) = \textbf{t}_i, \quad i = 1, 2, \ldots, n.

A görbe meghatározása harmadfokú Hermite ívek összekapcsolásával kézenfekvő módon megoldható.

Bessel-féle érintők
-------------------

Tegyük fel, hogy harmadfokú, egymáshoz folytonosan kapcsolódó ívekből szeretnénk egy spline-t létrehozni, viszont a pontokban az érintővektorokat nem szeretnénk megadni, hanem származtatnánk a csomópontokból. Ezt például a Bessel-féle érintők felhasználásával tehetjük meg.

Tegyük fel, hogy egy :math:`\textbf{p}_i` ponthoz tartozó érintőt szeretnénk meghatározni, ahol :math:`i \in [1, n - 1]`. Illesszünk egy másodfokú görbét ezekre, melynek általános alakja:

.. math::

  \textbf{c}_i(u) = \textbf{a}_0 + \textbf{a}_1 u + \textbf{a}_2 u^2.

Teljesülnie kell, hogy

.. math::

  \begin{align}
  \textbf{p}_{i-1} &= \textbf{c}_i(u_{i-1}) = \textbf{a}_0 + \textbf{a}_1 u_{i-1} + \textbf{a}_2 u_{i-1}^2, \\
  \textbf{p}_{i} &= \textbf{c}_i(u_{i}) = \textbf{a}_0 + \textbf{a}_1 u_{i} + \textbf{a}_2 u_{i}^2, \\
  \textbf{p}_{i+1} &= \textbf{c}_i(u_{i+1}) = \textbf{a}_0 + \textbf{a}_1 u_{i+1} + \textbf{a}_2 u_{i+1}^2. \\
  \end{align}

Az összefüggés mátrixos alakban felírva az alábbi:

.. math::

  \begin{bmatrix}
  1 & u_{i-1} & u_{i-1}^2 \\
  1 & u_{i} & u_{i}^2 \\
  1 & u_{i+1} & u_{i+1}^2 \\
  \end{bmatrix}
  \cdot
  \begin{bmatrix}
  \textbf{a}_0 \\
  \textbf{a}_1 \\
  \textbf{a}_2 \\
  \end{bmatrix}
  =
  \begin{bmatrix}
  \textbf{p}_{i-1} \\
  \textbf{p}_{i} \\
  \textbf{p}_{i+1} \\
  \end{bmatrix}.

Az :math:`\textbf{a}_0`, :math:`\textbf{a}_1` és :math:`\textbf{a}_2` együtthatókat így tehát a lineáris egyenletrendszer megoldásaként kapjuk.

Ezek alapján az :math:`u_i` paraméterhez tartozó érintőt a

.. math::

  \dot{\textbf{c}}(u_i) = \textbf{a}_1 + 2 \textbf{a}_2 u_i

számításból kapjuk.

Érintők számítása a szomszédos pontokból
----------------------------------------

Megtehetjük, hogy egy :math:`\textbf{p}_i` ponthoz tartozó érintőt kizárólag a :math:`\textbf{p}_{i-1}` és :math:`\textbf{p}_{i+1}` pontokból számítunk ki, például az

.. math::

  \textbf{t}_i = \dfrac{\textbf{p}_{i+1} - \textbf{p}_{i-1}}{\lVert \textbf{p}_{i+1} - \textbf{p}_{i-1} \rVert},
  \quad i = 1, 2, \ldots, n - 1

összefüggéssel. A :math:`\textbf{t}_0` és :math:`\textbf{t}_n` vektorok meghatározásához ekkor más módszert kell alkalmaznunk. (Lehet például Bessel parabola alapján számolni azokat.)

Catmull-Rom spline
------------------

A Catmull-Rom spline esetében a :math:`\textbf{t}_i, i \in [1, n-1]` érintővektorokat a

.. math::

  \textbf{t}_i = \tau (\textbf{p}_{i+1} - \textbf{p}_{i-1})

számíthatjuk, ahol :math:`\tau \in \mathbb{R}, \tau > 0`. A kezdő és a végpont esetében:

.. math::

  \textbf{t}_0 = \tau (\textbf{p}_{1} - \textbf{p}_{0}),
  \quad
  \textbf{t}_n = \tau (\textbf{p}_{n} - \textbf{p}_{n-1})

használható.

Leggyakrabban a :math:`\tau = 0.5` paramétert használják hozzá.

Overhauser spline
-----------------

Az Overhauser spline esetében is csak a :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n` pontokat, és a hozzájuk tartozó, egymástól különböző :math:`u_0, u_1, \ldots, u_n` paraméterértékeket tekintjük ismertnek.

Jelöljük :math:`\textbf{a}_i`-vel a :math:`\textbf{p}_0` és a :math:`\textbf{p}_1` pontok közé tartozó ívet. Ennek a meghatározásához számítsuk ki (az említett két ponthoz tartozó) :math:`\textbf{c}_i` és :math:`\textbf{c}_{i+1}` Bessel parabolaíveket.

A spline ez esetben tulajdonképpen a két görbe pontonkénti konvex kombinációját számolja :math:`u` függvényében változó súlyozással, vagyis:

.. math::

  \textbf{a}_i (u) =
  \left( 1 - \dfrac{u - u_i}{u_{i+1} - u_i} \right) \textbf{c}_i(u) +
  \dfrac{u - u_i}{u_{i+1} - u_i} \textbf{c}_{i+1}(u),

ahol :math:`u \in [u_i, u_{i+1}], i = 1, 2, \ldots, n - 2`.

A spline első és utolsó ívén közvetlenül a Bessel parabola kerül felhasználásra.


Ferguson spline
---------------

Tegyük fel, hogy egy olyan spline-t szeretnénk kapni, amelyik

* harmadrendű ívekből épül fel, és
* a csomópontokban másodrendben is folytonosan kapcsolódik (vagyis :math:`\ddot{\textbf{r}}_{i-1}(u_i) = \ddot{\textbf{r}}_{i}(u_i)`).

Ezt úgy érhetjük el, hogy ha kiszámítjuk, hogy Hermite ívek esetében milyen érintővektorok lehetnek megfelelőek.

.. A számítások áttekinthetőbbé tétele érdekében vezessük be a :math:`\Delta u_i = u_{i+1} - u_i` jelölést!

A Hermite ív második deriváltját az :math:`\ddot{\textbf{r}}(u) = 2 \textbf{a}_2 + 6 \textbf{a}_3(u)` alakban írhatjuk föl. Ennek az együtthatóit az ívet meghatározó vektorok függvényében ismerjük, vagyis

.. math::

  \begin{align}
  \textbf{a}_2 &= 3(\textbf{p}_1 - \textbf{p}_0) - 2\textbf{t}_0 - \textbf{t}_1, \\
  \textbf{a}_3 &= -2(\textbf{p}_1 - \textbf{p}_0) + \textbf{t}_0 + \textbf{t}_1. \\
  \end{align}

A 0 és az 1 itt egyetlen ívhez tartozó indexek, amelyekről ez esetben tudjuk, hogy

* az :math:`\ddot{\textbf{r}}_{i-1}(u)` ív esetében a 0 helyett :math:`(i-1)`, az 1 helyett pedig :math:`i` szerepel, míg
* az :math:`\ddot{\textbf{r}}_{i}(u)` ív esetében a 0 helyett :math:`i`, az 1 helyett pedig :math:`(i+1)`.

Az :math:`\ddot{\textbf{r}}_{i-1}(u_i) = \ddot{\textbf{r}}_{i}(u_i)` egyenletbe az előbbieket visszahelyettesítve, majd átrendezve kapjuk, hogy:

.. math::

  \textbf{t}_{i-1} + \textbf{t}_{i} + (1 - 3u_i)\textbf{t}_{i+1} =
  3\textbf{p}_{i-1} - 6\textbf{p}_{i} + 6\textbf{p}_{i+1} +
  (-6\textbf{p}_{i-1} + 12\textbf{p}_{i} - 6\textbf{p}_{i+1})u_i.

Vegyük észre, hogy a jobb oldalon csak ismert értékek szerepelnek!

Vezessük be a

.. math::

  \textbf{q}_i = 3\textbf{p}_{i-1} - 6\textbf{p}_{i} + 6\textbf{p}_{i+1} +
  (-6\textbf{p}_{i-1} + 12\textbf{p}_{i} - 6\textbf{p}_{i+1})u_i

jelölést!

Ezzel így egy :math:`(n+1)` darab egyenletet és ugyanennyi ismeretlent tartalmazó lineáris egyenletrendszert kapunk. Hiányoznak viszont belőle az első és utolsó pontra vonatkozó peremfeltételek. Ezek megadására például az alábbi lehetőségek állnak rendelkezésre.

* Rögzített (clamped): A végpontokban hiányzó érintőket mi magunk megadhatjuk.
* Természetes (natural): A kezdő és végpontban a görbületet nullának tekinthetjük.
* Kvadratikus (quadratic): Az első és utolsó ív esetében az ív kezdő és végpontjában a deriváltak megegyeznek.
* Harmadrendű folytonosság (not-a-knot): Az :math:`u_1` és :math:`u_{n-1}` paraméterekhez tartozó pontokban feltételezhetünk harmadrendű folytonosságot.
* Bessel: A kezdő és végpontban a Bessel-féle parabola érintőit használhatjuk.
* Parabola érintője: Az első és utolsó ívre azok ismert érintőit felhasználva szerkeszthetünk parabolát, melynek érintőjét használhatjuk a végpontok érintőjeként.

Paraméterezés
=============

A korábbiakban adottnak tekintettük, hogy ismertek az :math:`u_i` értékek (legegyszerűbb esetben például :math:`u_i = i` formában). Ezek megválasztására azonban különféle lehetőségek vannak, melyeket a következőkben tekintünk át.

Egyenközű paraméterezés
-----------------------

Egyenközű, vagy uniform paraméterezésről beszélünk, hogy ha az :math:`(u_{i+1} - u_i)` kifejezés egy konstans érték (bármilyen :math:`i` esetén).

* Legegyszerűbb esetben használhatjuk az :math:`u_i = i` összefüggést.
* Hogy ha a görbénkent :math:`n \in \mathbb{N}` egyenlő részre bontjuk fel, úgy a paraméterezést megadhatjuk az :math:`u \in [0, 1]` intervallumon az :math:`u_i = i / n, i = 0, 1, \ldots, n` választással.

A paraméterezési mód előnye, hogy

* egyszerű,
* invariáns a pontok affin transzformációjára.

Hátránya, hogy

* nem veszi számításba az egymást követő pontok távolságát, a távoli pontok között gyorsabban mozog a paraméter, ami kihat a görbület alakjára.

Húrhosszal arányos paraméterezés
--------------------------------

Az ívhossz szerinti paraméterezés közelítése. Számítása:

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert}{\sum_{j=1}^{n} \lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert},

ahol :math:`i = 1, 2, \ldots, n`.

Előnye, hogy egyenletesebb sebességű bejárást tesz lehetővé.

Centripetális paraméterezés
---------------------------

Arra törekszünk, hogy a görbe bejárása során a centripetális gyorsulás legyen minél kisebb. Számítása:

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\sqrt{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert}}{\sum_{j=1}^{n} \sqrt{\lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert}},

ahol :math:`i = 1, 2, \ldots, n`.

Exponenciális paraméterezés
---------------------------

Egy :math:`e`-vel jelölt kitevő segítségével az egyenközű, a húrhosszal arányos és a centripetális paraméterezést egy paraméterezési módban általánosíthatjuk. Számítása:

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert^e}{\sum_{j=1}^{n} \lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert^e},

ahol :math:`e \in [0, 1], i = 1, 2, \ldots, n`.

Láthatjuk, hogy

* az :math:`e = 0` az egyenközű paraméterezés,
* az :math:`e = 0.5` a centripetális paraméterezés,
* az :math:`e = 1` a húrhosszal arányos paraméterezés.


Kérdések, elméleti feladatok
============================

* Mi az interpolációs (alap)feladat?
* Hogyan számítható a Lagrange interpoláció? Melyek az előnyei és hátrányai?
* Mit nevezünk Hermite ívnek? Hogyan számítható?
* Melyek a harmadfokú Hermite polinomok?
* Melyek a spline-ok használatának az előnyei?
* Hogyan adhatunk meg spline-okat Hermite ívek segítségével?
* Mit nevezünk Bessel parabolának?
* Spline-ok esetében hogyan használhatjuk a Bessel parabolákat?
* Spline-ok esetében hogyan számolhatjuk az érintőket csak a szomszédos pontokat felhasználva?
* Mi az a Catmull-Rom spline? Hogyan számíthatjuk ki?
* Mi az az Overhauser spline? Milyen számítások tartoznak hozzá?
* Mit nevezünk Ferguson spline-nak? Milyen peremfeltételek tartoznak hozzá?
* Milyen paraméterezési módok állnak rendelkezésre interpolációs spline-ok esetében?

Számítási feladatok
===================

* Adott a térben 4 pont, és hozzá 4 paraméterérték. Írjuk fel azt a Lagrange interpolációs görbét, amely ezeken a pontokon áthalad!
* Adott a síkban 2 pont, és a hozzá tartozó érintővektorok. Írjuk fel az ezek által meghatározott Hermit ívet!
* Adott 4 pont a síkon. Spline interpolációhoz határozzuk meg Bessel parabolák segítségével az érintő vektorokat!
* Adott 6 pont a síkon. Határozzuk meg Catmull-Rom spline esetében az ezekhez tartozó érintővektorokat!
* Adott a síkon 4 pont. Írjuk fel az Overhauser spline-t!
* Adott a síkon 6 pont. Határozzuk meg a húrhosszal arányos paraméterezést!

Programozási feladatok
======================

Keretrendszer összerakása
-------------------------

* Vizsgáljuk meg, hogy milyen API-k jöhetnek szóba a preferált programozási nyelvhez!
* Készítsünk egy keretrendszert, amelyben a kontrollpontokat lehet mozgatni!
* Nézzük meg példaként a https://gitlab.com/imre-piller/me-courses repositoriban szereplő keretrendszereket!

Lagrange interpoláció
---------------------

* Írjuk fel a Lagrange interpolációs polinomokat másod- és harmadfokú polinomokra!
* Ábrázoljuk azokat :math:`u` paraméter függvényében!
* Készítsünk egy programot, amelyben 4 pontot lehet mozgatni, és kirajzolásra kerül a hozzájuk tartozó Lagrange interpolációs görbe!

Hermite ív
----------

* Ábrázoljuk a harmadfokú Hermite polinomokat!
* Készítsünk egy programot, amelyben meg lehet adni 2 pontot, a hozzájuk tartozó érintőket, és megjelenítésre kerül ezek alapján a Hermite ív!

Bessel parabola
---------------

* Készítsünk egy programot, amely 3 pontra meghatározza a hozzájuk tartozó Bessel parabolát!
* Jelenítsük is meg a parabolát!
* Jelenítessük meg a középső ponthoz tartozó érintőt!
* Készítsünk egy programot, amely a Bessel érintők alapján állít össze Hermite ívekből egy spline-t! (Használjunk hozzá legalább 4 pontot!)
* Definiáljunk egy spline-t, amely a Bessel-féle parabolák helyett a 3 pontra írható körök alapján számítja ki a pontbeli érintőket!

Érintők számítása a szomszédos pontokból
----------------------------------------

* Jelenítsük meg, hogy ilyen érintőket kapunk, hogy ha azokat a szomszédos pontok alapján határozzuk meg!
* Ezek alapján rajzoljuk meg Hermite ívekből a spline-t!

Catmull-Rom spline
------------------

* Számítsuk ki, és jeleníttessük meg a Catmull-Rom spline-t!
* Vizsgáljuk meg a :math:`\tau` paraméter hatását!

Overhauser spline
-----------------

* Egy spline pontjaihoz jeleníttessük meg a Bessel parabolákat!
* Ezek alapján rajzoljuk meg az Overhauser spline-t!

Paraméterezési módok
--------------------

* Implementáljuk a különféle paraméterezési módokat, és vizsgáljuk meg a hatásukat!

