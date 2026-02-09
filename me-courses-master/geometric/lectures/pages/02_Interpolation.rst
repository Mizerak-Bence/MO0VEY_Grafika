********************
Spline interpolation
********************

The interpolation problem
=========================

Let given the points :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n \in \mathbb{R}^D, n, D \in \mathbb{N}, n > 0`! We would like to find a function :math:`\textbf{r}(u)`, and parameters :math:`u_0, u_1, \ldots, u_n \in \mathbb{R}`, when :math:`\textbf{r}(u_i) = \textbf{p}_i, \forall i \in [0, n]`.

.. note::

   * The letter :math:`D` denote the dimension of the space, where we try to find the curve.
   * We could start the index from 1. It has only practical significance. In the following the 0-based index will be beneficial.
   * The problem of interpolation does not make necessary to find a parametric curve. We use parametric curves mostly in these topics. This is the reason of mentioning parametric curves in the definition of the problem.
   * From the aspect of designer, the interpolation practically means that, we know some points of the shape, and we would like to calculate the others by using the interpolation function.

In the literature, the interpolation points and the interpolation curve are often also notated as :math:`\textbf{p}`. It usually does not make problem. We have to understand the difference:

* the :math:`\textbf{p}_i` is the :math:`i`-th element of a series of points (vectors),
* the :math:`\textbf{p}(u)` is a vector-valued function at the parameter :math:`u`.


Lagrange interpolation
======================

In the case of Lagrange interpolation, we try to find a curve as a polynomial :math:`\textbf{p}(u)` of degree :math:`n` at most:

.. math::

  \textbf{p}(u) = \textbf{a}_n u^n + \textbf{a}_{n-1} u^{n-1} + \cdots + \textbf{a}_1 u + \textbf{a}_0,

or in a shorter form:

.. math::

  \textbf{p}(u) = \sum_{i=0}^n \textbf{a}_i u^i.


.. admonition:: Theorem

  There is always a unique solution of the problem, when we use different :math:`u_i` parameters for the interpolation.

.. admonition:: Proof (constructive)

  Let choose :math:`u_i` parameters for the interpolation points :math:`\textbf{p}_i`. We can construct vectors as

  .. math::

    \textbf{u}_i = \begin{bmatrix}
    u_i^0 & u_i^1 & \cdots & u_i^n \\
    \end{bmatrix}.

  Let's notice, that :math:`\textbf{p}_i = \textbf{u}_i \cdot \textbf{a}` teljesül :math:`\forall i \in [0, n]`!

  We can write the following matrix form:

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

  where the rows of the coefficient matrix are the vectors :math:`\textbf{u}_i`.

  For the existing and unique solution, the determinant of the coefficient matrix must be non-zero.
  Let's notice that the coefficient matrix is a Vandermonde matrix, which determinant can be calculated as

  .. math::

    \prod_{j < i} (u_i - u_j).

  In the case of different :math:`u_i` values, the determinant cannot be zero, which means that the solution is existing and unique. :math:`\square`

.. seealso::

  * https://en.wikipedia.org/wiki/Vandermonde_matrix


Lagrange interpolation polynomial
---------------------------------

Let given different parameter values :math:`u_i, i \in [0, n]`! We call the polynomial

.. math::

  L_i^n (u) = \dfrac
  {\prod_{j=0,j\neq i}^n (u - u_j)}
  {\prod_{j=0,j\neq i}^n (u_i - u_j)}, \quad i = 0, 1, \ldots, n

as the degree :math:`n` Lagrange interpolation polynomial.

We can describe the Lagrange interpolation curve as

.. math::

  \textbf{p}(u) = \sum_{i=0}^{n} \textbf{p}_i L_i^n(u).

The values :math:`L_i^n(u)` results the convex combination of points by using the parameter :math:`u`. In other words:

.. math::

  \sum_{i=0}^n L_i^n(u) = 1.

At the parameters :math:`u_i, i \in [0, n]`, the :math:`L_i^n(u_j) = \delta_{ij}` (Kronecker delta), which means

.. math::

  L_i^n(u_j) = \begin{cases}
  1, & \text{if } i = j, \\
  0, & \text{else}.
  \end{cases}

.. note::

   * The advantage is that it can be calculated relatively easily.
   * It causes some inconveniences in the design, because the curve only can be controlled globally.
   * We do not use the Lagrange interpolation in this form, because it tends to be oscillating.
   * The segmented line is a special case of the Lagrange interpolation.


Hermite arc
===========

Let assume, that we would like to interpolate two points (with an arc), and we know the tangent vectors at these points.

Let denote :math:`\textbf{p}_0` and :math:`\textbf{p}_1` the tangent vectors, furthermore :math:`\textbf{t}_0` and :math:`\textbf{t}_1` the tangent vectors!

We find the curve in the following form:

.. math::

  \textbf{a}(u) = \textbf{a}_0 + \textbf{a}_1 u + \textbf{a}_2 u^2 + \textbf{a}_3 u^3,
  \quad a \in [0, 1],

where

.. math::

  \textbf{a}(0) = \textbf{p}_0,
  \textbf{a}(1) = \textbf{p}_1, 
  \dot{\textbf{a}}(0) = \textbf{t}_0,
  \dot{\textbf{a}}(1) = \textbf{t}_1.

The solution of the resulted equation system provides us the coefficients, as

.. math::

  \begin{align}
  \textbf{a}_0 &= \textbf{p}_0, \\
  \textbf{a}_1 &= \textbf{t}_0, \\
  \textbf{a}_2 &= 3(\textbf{p}_1 - \textbf{p}_0) - 2\textbf{t}_0 - \textbf{t}_1, \\
  \textbf{a}_3 &= -2(\textbf{p}_1 - \textbf{p}_0) + \textbf{t}_0 + \textbf{t}_1. \\
  \end{align}

:math:`\rhd` Let check the previous calculation!

By substitution and some arrangements:

.. math::

  \textbf{a}(u) =
  (2u^3 - 3u^2 + 1)\textbf{p}_0 +
  (-2u^3 + 3u^2)\textbf{p}_1 +
  (u^3 - 2u^2 + u)\textbf{t}_0 +
  (u^3 - u^2)\textbf{t}_1.

We can calculate also in the following form:

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

The advantage of the latter form, is that in the case of curve plotting we have to calculate by using the same points and tangent vectors for different :math:`u` parameter values. It means that, it is enough to multiple a special vector (derived from parameter :math:`u`) by a contant matrix.

We can represent the interpolation by using the following Hermite polynomials:

.. math::

  \textbf{a}(u) =
  \textbf{p}_0 H_0^3(u) +
  \textbf{p}_1 H_1^3(u) +
  \textbf{t}_0 H_2^3(u) +
  \textbf{t}_1 H_3^3(u).

We call them third degree Hermite polynomials.

.. math::

  \begin{align}
  H_0^3(u) &= 2u^3 - 3u^2 + 1, \\
  H_1^3(u) &= -2u^3 + 3u^2, \\
  H_2^3(u) &= u^3 - 2u^2 + u, \\
  H_3^3(u) &= u^3 - u^2. \\
  \end{align}

.. note::

   * Beside the tangent vectors, we can use higher degree derivatives as boundary conditions. In this case, the degree of the interpolation polynomial also will be higher.
   * We also call Hermite arc the higher degree arcs which uses two fixed points and higher degree boundary conditions.


Spline interpolation
====================

In real world application the two points of the Hermite arc may be few. For more points, the global controllability and the oscillation of the Lagrange interpolation also can cause some difficulties. Therefore, it would be beneficial, to find a method which

* can use arbitrary number of control points,
* based on polynomial interpolation and
* the degree of the polynomial can be lower.

A possible solution is the usage of spline interpolation, which connects lower degree polynomial arcs.

.. seealso::

  * https://en.wikipedia.org/wiki/Spline_interpolation


Joining Hermite arcs
--------------------

Let consider the interpolation points :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n`, the corresponding, different parameter values :math:`u_0, u_1, \ldots, u_n` furthermore the tangential vectors :math:`\textbf{t}_0, \textbf{t}_1, \ldots, \textbf{t}_n`.

We find a curve :math:`\textbf{c}` which fulfills:

.. math::

  \textbf{c}(u_i) = \textbf{p}_i, \dot{\textbf{c}}(u_i) = \textbf{t}_i, \quad i = 1, 2, \ldots, n.

It is straightforward to determine a curve, by joining degree 3 Hermite arcs.


Bessel parabolas
----------------

Let assume that we would like to join degree 3 Hermite arcs continuously in the order of 1 (:math:`C^1`), but we would not like to specify the tangential vectors directly. Instead, we would like to calculate them from the control points. A possible solution is the usage of Bessel tangentials.

We would like to calculate the tangent vectors at the points :math:`\textbf{p}_i`, where :math:`i \in [1, n - 1]`. Let fit a second order curves (*parabolas*) to these points. Their general form is:

.. math::

  \textbf{c}_i(u) = \textbf{a}_0 + \textbf{a}_1 u + \textbf{a}_2 u^2.

It must be hold, that

.. math::

  \begin{align}
  \textbf{p}_{i-1} &= \textbf{c}_i(u_{i-1}) = \textbf{a}_0 + \textbf{a}_1 u_{i-1} + \textbf{a}_2 u_{i-1}^2, \\
  \textbf{p}_{i} &= \textbf{c}_i(u_{i}) = \textbf{a}_0 + \textbf{a}_1 u_{i} + \textbf{a}_2 u_{i}^2, \\
  \textbf{p}_{i+1} &= \textbf{c}_i(u_{i+1}) = \textbf{a}_0 + \textbf{a}_1 u_{i+1} + \textbf{a}_2 u_{i+1}^2. \\
  \end{align}

By using a matrix form, it results:

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

The coefficients :math:`\textbf{a}_0`, :math:`\textbf{a}_1` and :math:`\textbf{a}_2` are the solution of the linear equation system.

Therefore, the tangent vector at parameter :math:`u_i`:

.. math::

  \dot{\textbf{c}}(u_i) = \textbf{a}_1 + 2 \textbf{a}_2 u_i.


Calculating the tangent vectors from the neightbour points
----------------------------------------------------------

We can determine the tangent vector at the point :math:`\textbf{p}_i` from the neightbour points :math:`\textbf{p}_{i-1}` and :math:`\textbf{p}_{i+1}` for example by the following formula:

.. math::

  \textbf{t}_i = \dfrac{\textbf{p}_{i+1} - \textbf{p}_{i-1}}{\lVert \textbf{p}_{i+1} - \textbf{p}_{i-1} \rVert},
  \quad i = 1, 2, \ldots, n - 1.

We have to find a further method for calculating the tangent vectors :math:`\textbf{t}_0` and :math:`\textbf{t}_n`. (As a possible solution, we can use Bessel parabolas here also.)


Catmull-Rom spline
------------------

In the case of Catmull-Rom spline, the tangent vectors :math:`\textbf{t}_i, i \in [1, n-1]` can be calculated as

.. math::

  \textbf{t}_i = \tau (\textbf{p}_{i+1} - \textbf{p}_{i-1})

where :math:`\tau \in \mathbb{R}, \tau > 0`. In the case of the first and the last point:

.. math::

  \textbf{t}_0 = \tau (\textbf{p}_{1} - \textbf{p}_{0}),
  \quad
  \textbf{t}_n = \tau (\textbf{p}_{n} - \textbf{p}_{n-1}).

The parameter value :math:`\tau = 0.5` is a common choice.

Overhauser spline
-----------------

The Overhauser spline uses the control points :math:`\textbf{p}_0, \textbf{p}_1, \ldots, \textbf{p}_n` and the corresponding different parameter values :math:`u_0, u_1, \ldots, u_n`.

Let denote :math:`\textbf{a}_i` the arc between the points :math:`\textbf{p}_i` and :math:`\textbf{p}_{i+1}`. Let determine the Bessel parabolas for all of the possible points. For the arcs between the parameters :math:`u_1` and :math:`u_{n-1}` there are always two Bessel parabolas.

In fact, we obtain a spline as the convex combination of these Bessel parabolas in the function of :math:`u`, as

.. math::

  \textbf{a}_i (u) =
  \left( 1 - \dfrac{u - u_i}{u_{i+1} - u_i} \right) \textbf{c}_i(u) +
  \dfrac{u - u_i}{u_{i+1} - u_i} \textbf{c}_{i+1}(u),

where :math:`u \in [u_i, u_{i+1}], i = 1, 2, \ldots, n - 2`.

We can use the Bessel parabola directly for the first and the last arc.


Ferguson spline
---------------

Let assume that we would like to describe a curve, which

* contains degree 3 Hermite arcs and
* the arcs joining continuously in the second order (:math:`C^2` continuity, :math:`\ddot{\textbf{r}}_{i-1}(u_i) = \ddot{\textbf{r}}_{i}(u_i)`).

We have to calculate the appropriate tangent vectors for the Hermite arcs.

The second order derivate of the Hermite arc is :math:`\ddot{\textbf{r}}(u) = 2 \textbf{a}_2 + 6 \textbf{a}_3(u)`. We know these coefficients in the function of points, like:

.. math::

  \begin{align}
  \textbf{a}_2 &= 3(\textbf{p}_1 - \textbf{p}_0) - 2\textbf{t}_0 - \textbf{t}_1, \\
  \textbf{a}_3 &= -2(\textbf{p}_1 - \textbf{p}_0) + \textbf{t}_0 + \textbf{t}_1. \\
  \end{align}

The indices 0 and 1 here are the indices of a single arc, which means that:

* for :math:`\ddot{\textbf{r}}_{i-1}(u)` instead of 0 we can write :math:`(i-1)`, instead of 1 we can write :math:`i`, while
* for :math:`\ddot{\textbf{r}}_{i}(u)` instead of 0 we can write :math:`i`, and instead of 1 we can write :math:`(i+1)`.

By substituting to the equation :math:`\ddot{\textbf{r}}_{i-1}(u_i) = \ddot{\textbf{r}}_{i}(u_i)`, and after some arrangement:

.. math::

  \textbf{t}_{i-1} + \textbf{t}_{i} + (1 - 3u_i)\textbf{t}_{i+1} =
  3\textbf{p}_{i-1} - 6\textbf{p}_{i} + 6\textbf{p}_{i+1} +
  (-6\textbf{p}_{i-1} + 12\textbf{p}_{i} - 6\textbf{p}_{i+1})u_i.

Let's notice that, there are only contant values at the right side!

Let introduce the notation:

.. math::

  \textbf{q}_i = 3\textbf{p}_{i-1} - 6\textbf{p}_{i} + 6\textbf{p}_{i+1} +
  (-6\textbf{p}_{i-1} + 12\textbf{p}_{i} - 6\textbf{p}_{i+1})u_i.

It results a linear equation system of :math:`(n+1)` equations. However, we do not know the boundary conditions of the first and the last points. There are some possibilities for finding a unique solution. For instance:

* Clamped: Fixed or directly given. We provide the tangent vectors explicitly.
* Natural: We use null vector as tangent vector at the first and the last point.
* Quadratic: The derivatives (at the two points of the arcs) are the same for the first and last arc of the spline.
* Cubic continuity (not-a-knot): We can require :math:`C^3` continuity at the parameter :math:`u_1` and :math:`u_{n-1}`.
* Bessel: We use the tangent vector of the Bessel parabola at the first and the last point of the spline.
* Bessel parabola: We use the Bessel parabola as the first and the last arc.


Parametrization
===============

In the previous sections we have assumed the the parameters :math:`u_i` are known (for instance simply as :math:`u_i = i`). However, we have infinitely many possible parametrizations. In the following, we consider only some of them.

Uniform parametrization
-----------------------

We call uniform, or equidistant parametrization, when the expression :math:`(u_{i+1} - u_i)` is a contant value (for all :math:`i`).

* It can be for example :math:`u_i = i`.
* By dividing the curve into :math:`n \in \mathbb{N}` equidistant parts, the range of the parameters can be :math:`u \in [0, 1]` by the calculation :math:`u_i = i / n, i = 0, 1, \ldots, n`.

The advantage of this parametrization method:

* It is simple.
* It is invariant against the affine transformation of the points.

Disadvantage:

* It does not take into account the distance between the control points. The point of the curve "moving faster" between farther control points. The traversal speed can affect the shape of the curve.

Chord length proportional parametrization
-----------------------------------------

This is an approximation of the natural (arc length) parametrization. Calculation:

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert}{\sum_{j=1}^{n} \lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert},

where :math:`i = 1, 2, \ldots, n`.

It provides smaller differences in the speed of the traversal.


Centripetal parametrization
---------------------------

We try to minimize the centripetal force when we traverse the point of the curve. Calculation:

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\sqrt{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert}}{\sum_{j=1}^{n} \sqrt{\lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert}},

where :math:`i = 1, 2, \ldots, n`.


Exponential parametrization
---------------------------

Let denote an exponent by :math:`e`. It is possible to generalize the previous parametrization method in one formula by

.. math::

  u_0 = 0, u_i = u_{i-1} + \dfrac{\lVert \textbf{p}_i - \textbf{p}_{i-1}\rVert^e}{\sum_{j=1}^{n} \lVert \textbf{p}_j - \textbf{p}_{j-1}\rVert^e},

where :math:`e \in [0, 1], i = 1, 2, \ldots, n`.

It is easy to see, that

* :math:`e = 0` is the uniform parametrization,
* :math:`e = 0.5` is the centripetal parametrization,
* :math:`e = 1` is the chord length proportional parametrization.


Theoretical questions
=====================

* What is the definition of the interpolation problem (in this topic)?
* How can we calculate the Lagrange interpolation? What are its advantages and drawbacks?
* What is the Hermite arc? How can we calculate it?
* What are the Hermite polynomials (degree 3)?
* What are the advantages of using the splines?
* How can we construct splines by using Hermite arcs?
* What are the Bessel parabolas?
* How can we use the Bessel parabolas in the case of splines?
* How can we obtain the tangent vectors in the case of splines, only using the neightbour points?
* What is the Catmull-Rom spline? How can we calculate it?
* What is the Overhauser spline? How can we calculate it?
* What is the Ferguson spline? What are its typical boundary conditions?
* What are the commonly used parametrization methods in the case of spline interpolation?

Numerical exercises
===================

* Let given 4 points in the space and 4 parameter value! Let write a Langrange interpolation curve which interpolates these points!
* We have two points and two tangent vectors on the plane. Let write the corresponding Hermite arc!
* Let given 4 points on the plane! Let determine the tangent vectors by using Bessel parabolas!
* Let given 6 points on the plane! Let calculate the tangent vectors of the Catmull-Rom spline!
* Let given 4 points on the plane! Let write the Overhauser spline!
* Let given 6 points on the plane! Let calculate the chord length proportional parametrization (on the interval :math:`[0, 1]`)!

Programming exercises
=====================

Framework for experimentation
-----------------------------

* Let consider the possible APIs for your preferred programming language/technology! 
* Let implement a framework, which is able to display the control point, the curve and makes available its modification!
* Let see for example the frameworks at: https://gitlab.com/imre-piller/me-courses

Lagrange interpolation
----------------------

* Let write the Lagrange interpolation polynomials in the second and third order case!
* Let plot them in the function of :math:`u`!
* Let implement an application, which display 4 movable point! Draw the corresponding Lagrange interpolation curve!

Hermite arc
-----------

* Let plot the degree 3 Hermite polynomials!
* Let implement a program, which makes possible to set 2 points and 2 tangent vectors, and displays the corresponding Hermite polynomial curve!

Bessel parabola
---------------

* Let implement a program, which calculates and display the Bessel curve for 3 points on the plane!
* Let visualize the tangent vector (or tangent line) of the point in the middle!
* Let implement a spline based on Bessel tangent vectors and Hermite arcs! (Use at least 4 points for demonstration!)
* Let define a spline, which use circles for the determination of tangent vectors instead of parabolas!

Tangent calculation from the neightbour points
----------------------------------------------

* Let visualize the tangents based only on the neightbour points!
* Let draw a spline of Hermite curves by using these tangent vectors!

Catmull-Rom spline
------------------

* Let calculate and display the Catmull-Rom spline!
* Let examine the effect of the parameter :math:`\tau`!

Overhauser spline
-----------------

* Let calculate and display the Bessel parabolas for a spline!
* Let calculate and display the approximation of an Overhauser spline!

Parametrization methods
-----------------------

* Let implement and analyze the mentioned parametrization methods and their effects!

