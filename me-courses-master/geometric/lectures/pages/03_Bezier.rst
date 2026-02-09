************
Bézier curve
************

The de Casteljau algorithm
==========================

For the understanding of the de Casteljau algorithm, let consider the points :math:`\textbf{b}_0`, :math:`\textbf{b}_1` and :math:`\textbf{b}_2`! Let choose an arbitrary real value :math:`t \in [0, 1]`!

* Let divide the segment between the points :math:`\textbf{b}_0` and :math:`\textbf{b}_1` in the ratio of :math:`t : (1 - t)`! Let denote the resulted point by :math:`\textbf{b}_0^1(t)`!
* Similarly, let divide the segment of :math:`\textbf{b}_1` and :math:`\textbf{b}_2`! Let denote the resulted point by :math:`\textbf{b}_1^1(t)`!
* Let divide the segment of :math:`\textbf{b}_0^1(t)` and :math:`\textbf{b}_1^1(t)`! Let the resulted point :math:`\textbf{b}_0^2(t)`!

By using this method, we can obtain a curve. The calculation of the auxiliary points:

.. math::

  \begin{align}
  \textbf{b}_0^1(t) &= (1 - t) \textbf{b}_0 + t \textbf{b}_1, \\
  \textbf{b}_1^1(t) &= (1 - t) \textbf{b}_1 + t \textbf{b}_2. \\
  \end{align}

Calculation of the curve by using these points:

.. math::

  \textbf{b}_0^2(t) = (1 - t)\textbf{b}_0^1(t) + t \textbf{b}_1^1(t).

Calculation of the curve directly from the original points:

.. math::

  \textbf{b}_0^2(t) = (1 - t)^2 \textbf{b}_0 + 2t (1 - t)\textbf{b}_1 + t^2 \textbf{b}_2.

.. todo:: Érdemes egy ábrát készíteni hozzá!

:math:`\rhd` Let examine the case of :math:`t \notin [0, 1]`!

Let notice, that the introduced method can be applied

* in arbitrary number of points,
* in arbitrary number of dimensions.

We call this recursive method as the *de Casteljau algorithm*.

:math:`\rhd` Let draw the calculation of the curve point in the case of 4 controll points (for an arbitrary parameter :math:`t`)!

:math:`\rhd` Show the calculation dependencies of the previous case!

.. note::

  * Paul de Faget de Casteljau, Citroën
  * https://en.wikipedia.org/wiki/Paul_de_Casteljau


Bernstein polynomial
====================

The definition of the :math:`i^{\text{th}}` Bernstein polynomial of degree :math:`n`:

.. math::

  B_i^n(t) = \binom{n}{i} t^i (1 - t)^{n - i}, \quad i = 0, 1, \ldots, n,

furthermore

.. math::

  B_0^0(t) = 1, \quad B_i^n(t) = 0, \text{ha } i \notin [0, n].

:math:`\rhd` Let plot the Bernstein polynomials of degree :math:`n` above the interval :math:`t \in [0, 1]`!

The properties of the Bernstein polynomial:

* :math:`B_i^n(t) \geq 0`, when :math:`t \in [0, 1]`.
* :math:`B_i^n(t) = (1 - t)B_i^{n-1}(t) + t B_{i-1}^{n-1}(t), \forall t \in [0, 1]` (recursive property).
* Their sum is 1:

.. math::

  \sum_{i=0}^n B_i^n(t) = (t + (1 - t))^n = 1, \quad \forall t \in [0, 1],

* The derivatives can be expressed as lower degree Bernstein polynomials:

.. math::

  \left( B_i^n(t) \right)' = n(B_{i-1}^{n-1}(t) - B_{i}^{n-1}(t)).

* :math:`\text{argmax}_t B_i^n(t) = \dfrac{i}{n}, \forall i \in [0, n]`.

.. note::

  * https://en.wikipedia.org/wiki/Bernstein_polynomial
  * https://www.youtube.com/watch?v=AL0vcsLlYp4


The parametric form of the Bézier curve
=======================================

The de Casteljau algorithm results the points of the Bézier curve. Its parametric form by using the Bernstein polynomials:

.. math::

  \textbf{b}(t) = \sum_{i=0}^n \textbf{b}_i B_i^n(t), \quad t \in [0, 1].

We call the points :math:`\textbf{b}_i` *controll points* or *Bézier points*.

.. note::

  * Pierre Étienne Bézier, Renault
  * https://en.wikipedia.org/wiki/Pierre_B%C3%A9zier
  * https://www.youtube.com/watch?v=2HvH9cmHbG4
  * https://www.youtube.com/watch?v=A8CM297pq2Y


Connection with the de Casteljau algorithm
==========================================

We can determine the points of the de Casteljau algorithm by using the Bernstein polynomials:

.. math::

  \textbf{b}_i^r(t) =
  \sum_{j=0}^r \textbf{b}_{j+i} B_j^r(t),

where

.. math::

  r \in [0, n], i \in [0, n - r], \forall t \in [0, 1].


Properties of the curve
=======================

The curve is closed to affine transformation.

* We obtain the same curve, when we transform the points of a curve, or calculate the points by using the transformed control points.
* It practically means that, it is enough to transform the control points of the curve.
* This is the consequence of proportional subdivisions.

:math:`\rhd` How can we define the convexity?

:math:`\rhd` What is the convex hull?

The Bézier curve is in the convex hull of the control points.

* This is the consequence of the de Casteljau algorithm.
* It guarantees that the curve cannot contain unexpected undulations ("waves") (in contrast to Lagrange interpolation).

The Bézier curve is invariant to the affine transformation of its parameter.

* We can us an arbitrary parameter :math:`t = (u - a) / (b - a), u \in [a, b]`. The shape of the curve will not change.
* The parametrization does not affect the tangent lines, however the length of the tangent vectors can be changed.
* It is also the consequence of the de Casteljau algorithm.

The Bézier curve interpolates at the endpoints.

We obtain the same curve by using the control points in the opposite order.

It is globally modifiable. All of the control points affects the shape of the curve.

* However, the curve can be called *pseudo locally modifiable*, because the Bernstein polynom :math:`B_i^n` has its maximal value at :math:`t = i / n`. It means that we can expect the effect of the control point closer to the curve.

The curve is a straight line if and only if the control points are collinear.


Derivative of the curve
=======================

The derivative of the Bézier curve can be expressed for example in the following forms:

.. math::

  \begin{align}
  \dot{\textbf{b}}(t)
  &= n \sum_{i=0}^n \textbf{b}_i (B_{i-1}^{n-1}(t) - B_i^{n-1}(t)) \\
  &= n \sum_{i=1}^n \textbf{b}_i B_{i-1}^{n-1}(t) - n \sum_{i=0}^{n-1} \textbf{b}_i B_i^{n-1}(t)) \\
  &= n \sum_{i=0}^{n-1} \textbf{b}_{i+1} B_i^{n-1}(t) - n \sum_{i=0}^{n-1} \textbf{b}_i B_i^{n-1}(t) \\
  &= n \sum_{i=0}^{n-1}(\textbf{b}_{i+1} - \textbf{b}_i) B_i^{n-1}(t)
  \end{align}

for :math:`\forall t \in [0, 1]`.

Hodograph
---------

We can see that, the derivative of a Bézier curve degree :math:`n` is a Bézier curve degree :math:`(n-1)`.
We call the derivative curve *hodograph*.

* Let determine the vectors :math:`\Delta \textbf{b}_i = \textbf{b}_{i+1} - \textbf{b}_i` from the control points!
* Let multiply them by :math:`n`!
* Translate them to the origin!
* These points result the Bézier curve of the derivatives (the hodograph).

We can examine the properties of the Bézier curve by using the hodograph:

* If the hodograph passes through the origin the Bézier curve has zero length tangent vector.
* If there is a tangent line which contains the origin and it is a cusp or inflection point, the Bézier curve has flat (zero curvature) point.
* If there is a tangent line which contains the origin and it is a regular (non-singular) pont, the Bézier curve has inflexion point.

Connection with the de Casteljau algorithm
------------------------------------------

Let introduce a notation to the differences of control points:

.. math::

  \begin{align}
  &\Delta^0 \textbf{b}_i = \textbf{b}_i, \\
  &\Delta^1 \textbf{b}_i = \textbf{b}_{i+1} - \textbf{b}_i, \\
  &\Delta^2 \textbf{b}_i = \textbf{b}_{i+2} - 2 \textbf{b}_{i+1} + \textbf{b}_i, \\
  &\ldots \\
  &\Delta^r \textbf{b}_i = \sum_{k=0}^r \binom{r}{k} (-1)^{r-k} \textbf{b}_{i+k}.
  \end{align}

By using the auxiliary point of the de Casteljau algorithm :math:`\textbf{b}_i^k`, we can express the :math:`r^{\text{th}}` order derivatives as

.. math::

  \dfrac{\mathrm{d}^r}{\mathrm{d}t^r} \textbf{b}(t) =
  \dfrac{\mathrm{d}^r}{\mathrm{d}t^r} \textbf{b}_0^n(t) =
  \dfrac{n!}{(n-r)!} \Delta^r \textbf{b}_0^{n-r}(t), \quad
  \forall t \in [0, 1].

Based on this observation, we know that

* :math:`\textbf{b}_0^n` a point of the curve,
* :math:`(\textbf{b}_0^{n-1}, \textbf{b}_1^{n-1})` determines the tangent line,
* :math:`(\textbf{b}_0^{n-2}, \textbf{b}_1^{n-2}, \textbf{b}_2^{n-2})` determines the osculating plane.


Splitting the curve
===================

Let consider the Bézier curve of degree :math:`n`: :math:`\textbf{b}^n(t), t \in [0, 1]`! 
Let choose an arbitrary parameter :math:`c \in (0, 1)`!
We would like to find a Bézier curve of degree :math:`n` on the interval :math:`t \in [0, 1]` which are the same of the original Bézier curve :math:`\textbf{b}^n(t), t \in [0, c]`.

Let denote the wanted curve in the form of :math:`\textbf{c}^n(u)`! Let calculate its parameter as :math:`u = t / c`!
We would like to determine the control points, which fulfils:

.. math::

  \textbf{b}^n(t) = \textbf{c}^n(u(t)) = \textbf{c}^n \left( \dfrac{t}{c} \right),
  \forall t \in [0, c].

We can obtain the solution by using the de Casteljau algorithm. From symmetrical reasons, we can determine the two new curves at the same time.

Let denote the auxiliary points of the de Casteljau algorithm by :math:`\textbf{b}_i^j` (where :math:`(i + j) \in [0, n]`)!

The control points of the curve above the interval :math:`[0, c]`:

.. math::

  \textbf{b}_0^0, \textbf{b}_0^1(c), \textbf{b}_0^2(c), \ldots, \textbf{b}_0^{n-1}(c), \textbf{b}_0^n(c),

or shortly :math:`\textbf{c}_i = \textbf{b}_0^i(c)`.

The control points of the curve above the interval :math:`[c, 1]`:

.. math::

  \textbf{b}_n^0, \textbf{b}_{n-1}^1(c), \textbf{b}_{n-2}^2(c), \ldots, \textbf{b}_1^{n-1}(c), \textbf{b}_0^n(c),

or shortly :math:`\textbf{c}_i = \textbf{b}_{n-i}^i(c)`.

:math:`\rhd` Let visualize the calculation method for a curve of degree 4!

.. note::

   The resulted new control points are in the convex hull of the original control points, therefore

   * the convex hulls of the new curves are the subset of the convex hull of the original curve, and
   * it shows the variation diminishing property of the curve.


Variation diminishing
=====================

Any hyperplane cannot intersect more times a Bézier curve than its control polygon.

.. note::

   We consider the straight line in the previous statement, as a special, lower dimensional case of the hyperplanes.

The statement can be proved based on the de Casteljau algorithm, because the control polygon converges to the curve, therefore it is impossible to appear a new intersection point.


Bézier-spline
=============

The preference of lower degree polynomials and the locally modifiable property is also an important aspect from practical reasons.
The problem is that, how can we join the lower degree polynomial curves to each others?

In the case of Bézier-splines, we have to consider the joint points of the Bézier curves. For the sake of simplicity, let consider only two Bézier curves:

* :math:`\textbf{a}(u), u \in [u_0, u_1]`, and
* :math:`\textbf{b}(u), u \in [u_1, u_2]`.

Let their control points :math:`\{\textbf{a}_i\}_{i=0}^n` and :math:`\{\textbf{b}_i\}_{i=0}^n` respectively.

For describing the continuity at the points, let use the notations :math:`C^k` and :math:`G^k`, where :math:`k \in \mathbb{N}_0`.

* :math:`C^k`: we require that the :math:`k^{\text{th}}` derivatives must be the same.
* :math:`G^k`: we require that the direction of the :math:`k^{\text{th}}` must be the same.

It also means that :math:`C^k \Rightarrow G^k`.

For example, in the case of :math:`C^1` the tangent vectors must be the same at the joint point, while in the case of :math:`G^1` it is enought to use the same tangent line.

Zero order continuity
---------------------

In the case of :math:`C^0` it is enough to fulfil:

.. math::

  \textbf{a}(u_1) = \textbf{b}(u_1).

For the control points it means that: :math:`\textbf{a}_n = \textbf{b}_0`.

First order continuity
----------------------

For the continuity :math:`G^1` the control points

.. math::

  \textbf{a}_{n-1}, \textbf{a}_n = \textbf{b}_0, \textbf{b}_1

must be collinear.

For the continuity :math:`C^1` we also have some requirements against the proportions:

.. math::

  \lVert \textbf{a}_n - \textbf{a}_{n-1} \rVert : \lVert \textbf{b}_1 - \textbf{b}_0 \rVert =
  (u_1 - u_0) : (u_2 - u_1).

Second order continuity
-----------------------

For the continuity :math:`G^2` the control points

.. math::

  \textbf{a}_{n-2}, \textbf{a}_{n-1}, \textbf{a}_n = \textbf{b}_0, \textbf{b}_1, \textbf{b}_2

must be in the same plane. (This plane is the osculating plane.)

For the continuity :math:`C^1`, let consider the intersection point (denoted by :math:`\textbf{m}`) of the lines of the segments :math:`\textbf{a}_{n-2}\textbf{a}_{n-1}` and :math:`\textbf{b}_{1}\textbf{b}_{2}`!

It has to fulfil the following:

.. math::

  \dfrac{\lVert \textbf{m} - \textbf{a}_{n-1} \rVert}{\lVert \textbf{a}_{n-1} - \textbf{a}_{n-2} \rVert} =
  \dfrac{u_2 - u_1}{u_1 - u_0}, \quad
  \dfrac{\lVert \textbf{m} - \textbf{b}_{1} \rVert}{\lVert \textbf{b}_{1} - \textbf{b}_{2} \rVert} =
  \dfrac{u_1 - u_0}{u_2 - u_1}.

.. note::

   It is also possible to examine the continuity by using higher order derivatives.


Degree elevation
================

It is sometimes a practical requirement to determine a Bézier curve degree :math:`(n+1)` which describes the same point as the Bézier curve degree :math:`n`.

Let consider the control points :math:`\textbf{b}_0, \textbf{b}_1, \textbf{b}_2, \ldots, \textbf{b}_n` for a Bézier curve!
We would like to find control points :math:`\textbf{b}_0^1, \textbf{b}_1^1, \textbf{b}_2^1, \ldots, \textbf{b}_{n+1}^1` which fulfil:

.. math::

  \sum_{i=0}^n \textbf{b}_i B_i^n(t) =
  \sum_{i=0}^{n+1} \textbf{b}_i^1 B_i^{n+1}(t), \quad \forall t \in [0, 1].

Its solution is:

.. math::

  \textbf{b}_i^1 =
  \left( \dfrac{i}{n + 1} \right) \textbf{b}_{i-1} +
  \left(1 - \dfrac{i}{n + 1} \right) \textbf{b}_{i}.

It also can be expressed in the form:

.. math::

  \textbf{b}_i^1 =
  \textbf{b}_{i} +
  \dfrac{i}{n + 1} (\textbf{b}_{i-1} - \textbf{b}_{i})

Let notice that, the new control polygon has obtained by cutting the corners of the original one.

* By applying the degree elevation by multiple times, the control polygon will converge to the Bézier curve.
* In general, the reduction is not possible. (We can approximate a curve by using a lower degree Bézier curve.)


Polyline approximation
======================

The approximation of the Bézier curve by using a polyline (a segmented line) is necessary for example

* for plotting the curve, or
* for estimating the curve length.

We can apply an equidistant subdivision, for example:

.. math::

  t_i = a + i \dfrac{b - a}{n}

For a better approximation we have to take into account the curvature. We can apply for instance the following algorithm:

* Let find the farthest point from the line determined by the control points :math:`\textbf{b}_0` and :math:`\textbf{b}_n`! Let denote its index by :math:`j`, and its distance by :math:`m_j`!
* When :math:`m_j \leq \varepsilon` we are ready. The Bézier curve can be approximated by the line segment of the control points :math:`\textbf{b}_0` and :math:`\textbf{b}_n`.
* In the other case, we have to split the curve by the parameter :math:`t = j / n` and continue the algorithm recursively.

.. note::

   For closed curves we can split the curve at the parameter :math:`t = 0.5` in the initial step. After, we can apply the mentioned recursive algorithm.


Interpolation
=============

It is possible to find the control points of a Bézier curve, which pass through some specified points. Therefore, we can use (the originally approximative) Bézier curves for interpolation problems also.

Let consider the interpolation problem! The interpolation points are :math:`\textbf{p}_0, \textbf{p}_1, \textbf{p}_2, \ldots, \textbf{p}_n` and the parameter values are :math:`0 \leq u_0 < u_1 < \cdots < u_n \leq 1`.

We would like to find the control points :math:`{\textbf{b}_i}_{i=0}^n` which fulfils:

.. math::

  \textbf{b}(u_i) = \textbf{p}_i, \quad i \in [0, n].

By using the Bernstein polynomial form, it results:

.. math::

  \textbf{b}(u_i) = \sum_{j=0}^n B_j^n(u_i) \textbf{b}_j = \textbf{p}_i, \quad i \in [0, n].

By arranging it to the matrix form, the resulted inhomogeneous linear equation system is:

.. math::

  \begin{bmatrix}
  B_0^n(u_0) & B_1^n(u_0) & \cdots & B_n^n(u_0) \\
  B_0^n(u_1) & B_1^n(u_1) & \cdots & B_n^n(u_1) \\
  B_0^n(u_2) & B_1^n(u_2) & \cdots & B_n^n(u_2) \\
  \vdots & \vdots & \ddots & \vdots \\
  B_0^n(u_n) & B_1^n(u_n) & \cdots & B_n^n(u_n) \\
  \end{bmatrix}
  \cdot
  \begin{bmatrix}
  \textbf{b}_0 \\
  \textbf{b}_1 \\
  \textbf{b}_2 \\
  \vdots \\
  \textbf{b}_n \\
  \end{bmatrix}
  =
  \begin{bmatrix}
  \textbf{p}_0 \\
  \textbf{p}_1 \\
  \textbf{p}_2 \\
  \vdots \\
  \textbf{p}_n \\
  \end{bmatrix}.

In the assumption of different :math:`u_i` values, there will be unique solution of the linear equation systems. (We have to solve them for each coordinates.)


Theoretical questions
=====================

* What is the de Casteljau algorithm? (Describe it illustrated by figures and formulas!)
* Let define the Bernstein polynomial degree :math:`n`! Let describe its properties!
* Let describe the parametric form of the Bézier curve by using Bernstein polynomials!
* What are the connections between the de Casteljau algorithm and the Bézier curve?
* Let describe the main properties of the Bézier curves!
* What is the hodograph? How can be calculated in the case of Bézier curves?
* What is the connection between the derivative of the Bézier curve and the de Casteljau algorithm?
* How can we split the Bézier curve at the parameter :math:`c \in \mathbb{R}`?
* How can we construct Bézier-spline from Bézier curves? How can we guarantee the zero, first and second order continuity?
* How can we elevate the degree of a Bézier curve?
* Describe the algorithm of the polyline approximation of the Bézier curve!
* How can we use Bézier curves for interpolation problems?


Numerical exercises
===================

.. note::

   Let perform the calculations to 4 decimal places!

Let assume that we have the control points :math:`\textbf{p}_0 = (0, 0), \textbf{p}_1 = (2, 5), \textbf{p}_2 = (4, 3), \textbf{p}_3 = (5, -1)`.

* Let calculate the point of the Bézier curve at parameter :math:`t = 0.4` by using the de Casteljau algorithm!
* Let determine the point of the Bézier curve at parameter :math:`t = 0.2` by using the Bernstein polinomials!
* Let determine the tangent line at the parameter :math:`t = 0.3`!
* Let split the curve at the parameter :math:`t = 0.25`! Determine the control points both of the resulted curves!
* Let calculate the control points of the Bézier curve of degree 5, which results exactly the same curve!


Programming exercises
=====================

The de Casteljau algorithm
--------------------------

* Let implement the de Casteljau algorithm!
* Let visualize the auxiliary lines in the application!
* Let make possible to change the parameter :math:`t` (for example by using a slider)!

Binomial coefficients
---------------------

* Let plot the Bernstein polynomials degree :math:`n`! (Try to solve it by using the degree as the input of the program!)
* Let compare the calculation of binomial coefficients by using factorials and the the recursive formula!
* Let analyze the effect of using cache for the calculations!
* Let make some measurements and visualize and summarize its results!

Curve splitting
---------------

* Let implement an application for the visualization of curve splitting!
* Let distinguish the control points of the resulted curves by different colours!
* Let make possible to modify the parameter of the splitting point!

Degree elevation
----------------

Implement an algorithm which makes possible to increase the degree of a Bernstein curve interactively, in the sense that, we can continue the modification of the curve after arbitrary number of degree elevation!

Polyline approximation
----------------------

Let implement the algorithm of polyline approximation, which tries to minimize the number of necessary line segments for plotting!

Bézier interpolation
--------------------

* Let implement an application, which solves the Bézier interpolation problem!
* Let compare the Bézier and Lagrange interpolation curve for the same interpolation points!


Further exercises
=================

* Let examine that, how can we extimate the area of a planar shape surrounded by Bézier curves!
* Let consider the possibilities of using the Bézier approximation and interpolation in the case of the same curve!
* Let assume that we would like to approximatee arbitrary number of points by using a Bézier curve of degree :math:`n`! Let analyze the possible approximation and optimization methods!
* Let compare the speed of convergency in the case of curve splitting and degree elevation!
* Implement an application which displays a closed Bézier curve and bouncing points inside it!
* How can we determine an interpolative spline which has :math:`G^1` continuity, it contains only line segments and line arcs, we know the ratio of their lengths, and we would like to minimize the length of the curve?

