2. Ordo szimbolika
==================

Maximális méretű bemenetek számítása
------------------------------------

Van egy számítógépünk, amely 1s alatt :math:`10^6` műveletet végez el. Mekkora a maximális méretű input, amelyre az algoritmus még adott idő alatt lefut?

* A sorokban szerepeljen az algoritmus bonyolultsága: :math:`\log(n), \sqrt{n}, n, n \cdot \log(n), n^2, n^3, 2^n, n!`.
* Az oszlopokban legyenek a vizsgált időtávok: 1s, 1 perc, 1 óra, 1 nap, 1 hónap, 1 év, 100 év.


Számjegyek számáról szóló tétel alkalmazása
-------------------------------------------

Számítsuk ki, hogy :math:`2^{10^6}` mennyi számjegyből fog állni 10-es számrendszerben!


Idő- és tárkapacitás bonyolultsága
----------------------------------

Definiáljuk az algoritmus idő- és tárkapacitás bonyolultságát!

.. math::

   T_A(n) = \sup_{x \in D, |x| \leq n} t_A(x),
   \quad
   S_A(n) = \sup_{x \in D, |x| \leq n} s_A(x)


* Értelmezzük a definíciókat!
* Mi a különbség a szuprémum és a maximum között?
* Lehet-e olyan algoritmust készíteni, amelyik hosszabb inputra rövidebb idő alatt fut le?


Szimbólumok
-----------

* Soroljuk fel az ordo szimbólumokat és mondjuk ki a definícióikat!

:math:`f(n) = \mathcal{O}(g(n))`, ha :math:`\exists c > 0` és :math:`n_0 > 0`, hogy ha :math:`n \geq n_0`, akkor :math:`0 \leq f(n) \leq c \cdot g(n)`.

:math:`f(n) = \Omega(g(n))`, ha :math:`\exists c > 0` és :math:`n_0 > 0`, hogy ha :math:`n \geq n_0`, akkor :math:`0 \leq c \cdot g(n) \leq f(n)`.

:math:`f(n) = \Theta(g(n))`, ha :math:`\exists c_1, c_2 > 0` és :math:`n_0 > 0`, hogy ha :math:`n \geq n_0`, akkor :math:`0 \leq c_1 \cdot g(n) \leq f(n) \leq c_2 \cdot g(n)`.

:math:`f(n) = \mathcal{o}(g(n))`, ha :math:`\forall c > 0`-ra :math:`\exists n_0 > 0`, hogy ha :math:`n \geq n_0`, akkor :math:`0 \leq f(n) < c \cdot g(n)`.

:math:`f(n) = \omega(g(n))`, ha :math:`\forall c > 0`-ra :math:`\exists n_0 > 0`, hogy ha :math:`n \geq n_0`, akkor :math:`0 \leq c \cdot g(n) < f(n)`.

* Egy-egy példán ábrázoljuk, hogy az adott szimbólumok milyen kapcsolatot adnak meg a bonyolultságot leíró függvény, és a segédfüggvények között!


.. note::

   Vizsgáljuk meg, hogy az egyes szimbólumok milyen kapcsolatban vannak egymással!

.. math::

   f(n) = O(g(n)) \wedge f(n) = \Omega (g(n))
   \quad \Leftrightarrow \quad
   f(n) = \Theta (g(n))

.. math::

   o(g(n)) \Rightarrow O(g(n)),
   \quad
   \omega(g(n)) \Rightarrow \Omega(g(n))

.. math::

   f(n) = O(g(n))
   \quad \Leftrightarrow \quad
   g(n) = \Omega(f(n))

.. math::

   f(n) = o(g(n))
   \quad \Leftrightarrow \quad
   \lim_{n \rightarrow \infty} \dfrac{f(n)}{g(n)} = 0

.. math::

   f(n) = \omega(g(n))
   \quad \Leftrightarrow \quad
   \lim_{n \rightarrow \infty} \dfrac{f(n)}{g(n)} = +\infty


Bonyolultság bizonyítása
------------------------

Bizonyítsuk be, hogy a következő összefüggések teljesülnek!

a) :math:`3n + 2 = O(n)`
b) :math:`\dfrac{n^2}{4} - 5n = O(n^2)`
c) :math:`2^{n+3} = O(2^n)`
d) :math:`2^{2n} \neq O(2^n)`
e) :math:`n^2 + 7n = \Theta(n^2)`
f) :math:`6n^3 \neq \Theta(n^2)`
g) :math:`\dfrac{n^2}{5} - n - 4 = \Theta(n^2)`
h) :math:`\log (n + 3) + 1 = O(\log n)`
i) :math:`n^3 - 2n = \Omega(n^2)`
j) :math:`\dfrac{n^3}{2} - 3n = o(n^4)`
k) :math:`n^3 - 3n \neq o(n^2)`
l) :math:`n^3 - 3n = \omega(n^2)`
m) :math:`n^3 - 3n \neq \omega(n^3)`

