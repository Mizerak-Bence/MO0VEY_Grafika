3. Rekurzív egyenletek, Binet formula
=====================================

Lineáris keresés
----------------

Készítsünk algoritmust, amely egy elemet megkeres egy adott tömbben!

.. note::

    Hogyan lehetne az algoritmust gyorsítani?


Binet formula
-------------

Mire szolgál a Binet formula, és hogyan néz ki?

.. math::

    F_n = \dfrac{1}{\sqrt{5}}\left( \Phi^n - \overline{\Phi}^n \right),
    \quad
    F_n = \text{Round} \left( \dfrac{1}{\sqrt{5}} \Phi^n \right),
    \quad
    \Phi = \dfrac{1 + \sqrt{5}}{2},
    \quad
    \overline{\Phi} = \dfrac{1 - \sqrt{5}}{2}.


* A Binet formula segítségével határozzuk meg a Fibonacci sorozat 37-edik, és 38-adik elemét!
* A Binet formula gyorsabb számítást eredményez-e, mint az iterációs/rekurzív?
* Ha igen, akkor mennyivel gyorsabb a számítási mód?


Rekurzív egyenletek
-------------------

Legyen :math:`T(1) = 1` mindegyik esetben!

a) :math:`T(n) = T(n - 1) + 2`, számtani sorozat
b) :math:`T(n) = 3T(n - 1)`, mértani sorozat
c) :math:`T(n) = 2T(n - 1) + 3`
d) :math:`T(n) = T(n - 1) + 2n`
e) :math:`T(n) = T\left( \dfrac{n}{2} \right) + 1`


Mester tétel
------------

Mondjuk ki a mester tételt, és határozzuk meg a növekedési rendjét az alábbi :math:`T` függvényeknek!

a) :math:`T(n) = T\left( \dfrac{n}{2} \right) + 1`
b) :math:`T(n) = 4T\left( \dfrac{n}{2} \right) + n`
c) :math:`T(n) = 4T\left( \dfrac{n}{2} \right) + n^2`
d) :math:`T(n) = 4T\left( \dfrac{n}{2} \right) + n^3`
e) :math:`T(n) = 8T\left( \dfrac{n}{2} \right) + 2^n`
f) :math:`T(n) = 3T\left( \dfrac{n}{3} \right) + n`
g) :math:`T(n) = T\left( \left\lfloor \dfrac{2n}{3} \right\rfloor \right) + \sqrt{n}`
h) :math:`T(n) = 25T\left( \left\lceil \dfrac{n}{5} \right\rceil \right) + \log n`
