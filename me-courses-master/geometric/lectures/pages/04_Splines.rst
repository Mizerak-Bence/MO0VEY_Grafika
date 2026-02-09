*********
B-Splines
*********

*Bases Spline*

.. seealso::

   * https://en.wikipedia.org/wiki/B-spline
   * https://en.wikipedia.org/wiki/Spline_(mathematics)
   * https://en.wikipedia.org/wiki/Flat_spline
   * https://en.wikipedia.org/wiki/Isaac_Jacob_Schoenberg

Normalized B-spline base function
=================================

Let consider the values :math:`u_i \in \mathbb{R}, i \in \mathbb{Z}`, which fulfils :math:`u_i \leq u_{i+1}`! We can define the B-spline base function in the following form:

.. math::

  N_i^1(u) = \begin{cases}
  1, & \text{if } u_i \leq u < u_{i+1}, \\
  0, & \text{else},
  \end{cases}
  
.. math::

  N_i^k(u) = \dfrac{u - u_i}{u_{i+k-1} - u_i} N_i^{k-1}(u) + \dfrac{u_{i+k} - u}{u_{i+k} - u_{i+1}} N_{i+1}^{k-1}(u).

* The :math:`\{u_i\}_{i \in \mathbb{Z}}` values are the *knot values*.
* Its components results the *knot vector*.
* We define the result of zero division as 0 when it can occur.

:math:`\rhd` Let write the second and third order B-spline base functions!

For the determination of the values :math:`u_i` we can use uniform parametrization, for example :math:`u_i = i`.

The curve with the same degree can be derived from each others by translation:

.. math::

  N_i^k(u) = N_0^k(u - i), \quad \forall i \in \mathbb{Z}.

.. note::

  * The B-spline base function of order :math:`k` contains (at most) :math:`(k-1)` degree polynomials.
  
  * The base function :math:`N_i^k` can be non-zero only on the interval :math:`(u_i, u_{i+k})`.
  * Let consider the interval :math:`[u_i, u_{i+1})`! It has effect to the base functions :math:`N_j^k`, where :math:`(i - k + 1) \leq j \leq i`.


Theorem of local support
------------------------

.. math::

  N_i^k(u) = 0, \text{if } u \notin [u_i, u_{i+k}).

.. admonition:: Proof (induction)

  In the case of :math:`k = 1` the statement is true by definition.

  Let substitute the value :math:`(k-1)` and let consider that

  .. math::

    \begin{align}
    &N_i^{k-1}(u) = 0, \text{if } u \notin [u_i, u_{i+k-1}), \\
    &N_{i+1}^{k-1}(u) = 0, \text{if } u \notin [u_{i+1}, u_{i+k}). \\
    \end{align}

  When :math:`u \notin [u_i, u_{i+k})` we have to calculate the linear combination of them (in the function of :math:`u`), which guarantees that its value must be 0. :math:`\square`


Theory of non-negativity
------------------------

The normalized B-spline base functions are non-negate, in other words

.. math::

  N_i^k(u) \geq 0, \forall u \in \mathbb{R}, i \in \mathbb{Z}, k \geq 1.


Theorem of partition of unity
-----------------------------

The sum of the normalized B-spline base functions are 1 at any point in the defined domain:

.. math::

  \sum_j N_j^k (u) = 1, \quad \forall u \in \mathbb{R}, \forall k \geq 1.


Multiple knot values
--------------------

The definition makes possible to use the same :math:`u_i` knot values multiple times. Let consider its effect in the case of degree 3 B-spline base function!

We can write the normalized B-spline base function of degree 3 as

.. math::

  N_i^3(u) =
  \begin{cases}
  \dfrac{(u-u_i)^2}{(u_{i+2}-u_i)(u_{i+1}-u_i)},
  & \text{if } u \in [u_i, u_{i+1}), \\
  \dfrac{(u-u_i)(u_{i+2}-u)}{(u_{i+2}-u_i)(u_{i+2}-u_{i+1})}
  + \dfrac{(u_{i+3}-u)(u-u_{i+1})}{(u_{i+3}-u_{i+1})(u_{i+2}-u_{i+1})},
  & \text{if } u \in [u_{i+1}, u_{i+2}), \\
  \dfrac{(u_{i+3}-u)^2}{(u_{i+3}-u_{i+1})(u_{i+3}-u_{i+2})},
  & \text{if } u \in [u_{i+2}, u_{i+3}), \\
  0, & \text{else}.
  \end{cases}

For instance, let assume that :math:`u_{i+1} = u_{i+2}`! We get the following:

.. math::

  N_i^3(u) = \begin{cases}
  \dfrac{(u - u_i)^2}{(u_{i+1} - u_i)^2},
  & \text{if } u \in [u_i, u_{i+1}), \\
  \dfrac{(u_{i+3} - u)^2}{(u_{i+3} - u_{i+1})^2},
  & \text{if } u \in [u_{i+1}, u_{i+3}), \\
  0, & \text{else}.
  \end{cases}

We can imagine this operation as a translation of :math:`u_{i+1}` to the point :math:`u_{i+2}`. The base function remains continuous at that point, however it will not remain differentiable at that point.

We can define the coincide of consecutive knot values as the multiplicity of the knots.

The multiplicity of a knot value is :math:`m`, when there are :math:`m` same consecutive knot values.

.. math::

  u_{i-1} < u_i = u_{i+1} = \cdots = u_{i+m-1} < u_{i+m}.

Relation with the Bernstein polynomials
---------------------------------------

In the case of

.. math::

  u_0, u_1 = u_2 = \ldots = u_{k-1}, u_k = u_{k+1} = \ldots = u_{2k-2} = 1, u_{2k-1}

then

.. math::

  N_i^{k-j}(u) = B_{i-j}^{k-1-j}(u), \forall u \in [u_{k-1}, u_k], i = 0, 1, \ldots, k - 1, j = 0, 1, \ldots, i.


Theorem related to the multiplicity
-----------------------------------

If the multiplicity of the knot :math:`u_i` is :math:`k`, then :math:`N_i^k(u_i) = 1`.

Derivative
----------

The derivative of the normalized B-spline base function :math:`N_i^k(u)`:

.. math::

  \dfrac{\mathrm{d}}{\mathrm{d}u}
  N_i^k(u) = (k - 1)
  \left(
  \dfrac{1}{u_{i+k-1}-u_i}N_i^{k-1}(u)
  - \dfrac{1}{u_{i+k} - u_{i+1}}N_{i+1}^{k-1}(u)
  \right),

where :math:`[u_i, u_{i+k})`.

Linear independence
-------------------

Normalized B-spline functions :math:`\{N_j^k\}_{j=i-k+1}^i` are linearly independent on the interval :math:`[u_i, u_{i+1})`, if :math:`u_i < u_{i+1}`.


B-spline curve
==============

Let given the control points :math:`\textbf{d}_0, \textbf{d}_1, \ldots, \textbf{d}_n` and the :math:`\{u_j\}_{j=0}^{n+k}` knot values! We call the curve

.. math::

  \textbf{s}(u) = \sum_{i=0}^n N_i^k(u) \textbf{d}_i,
  u \in [u_{k-1}, u_{n+1}], 1 < k < n + 1

the order of :math:`k` (in other words the degree :math:`(k-1)`) B-spline curve.

* The points :math:`\textbf{d}_i` are the control points (or de Boor points).
* The :math:`N_i^k` denotes the normalized B-spline polynomial of degree :math:`(k-1)`.

The B-spline curve is an approximative curve in general. There can be for example the following cases:

* When :math:`k = 2`, it results the control polygon.
* It passes the control points when the control points are colinear.
* When the multiplicity at the endpoints is :math:`k`, then it interpolates at the given point.

.. note::

  It is easy to see the last one. Let assume, that :math:`u_1 = u_2 = \cdots = u_{k-1}`! We can call the point of the curve at the parameter :math:`u_{k-1}` as

  .. math::

    \textbf{s}(u_{k-1}) =
    \sum_{i=0}^{k-1} N_i^k(u_{k-1}) \textbf{d}_i.

  We know that :math:`N_i^k(u_{k-1}) = 0`, when :math:`i \in [1, k-2]`. By using the theorem :math:`N_0^k(u_{k-1}) = 1`, we obtain that

  .. math::

    \textbf{s}(u_{k-1}) = \textbf{d}_0.

  Similarly, we can conclude that the curve also will interpolate at the point :math:`\textbf{d}_n` for the proper multiplicity.


Properties of the curve
-----------------------

*Local modification*: The B-spline curve is locally modifiable. It means that, the modification of the control points only affects a well defined part of the curve.

*Convex hull property*: Any arc of the B-spline curve of degree :math:`(k - 1)` is within the convex hull of :math:`k` number of consecutive control points.


de Boor algorithm
-----------------

The de Boor algorithm is based on a recursive method similarly to the de Casteljau algorithm, which makes possible to calculate the point of the curve at parameter :math:`u`. It is a numerically stable algorithm.

Let introduce the following notations:

.. math::

  \alpha_j^l(u) = \begin{cases}
  1, & \text{if } l = 0, \\
  \dfrac{u - u_j}{u_{j+k-l} - u_j}, & \text{if } l > 0,
  \end{cases}

.. math::

  \textbf{d}_j^l(u) = \begin{cases}
  \textbf{d}_j, & \text{if } l = 0, \\
  \alpha_j^l(u)\textbf{d}_j^{l-1}(u) + (1 - \alpha_j^l(u)) \textbf{d}_{j-1}^{l-1}(u), & \text{if } l > 0,
  \end{cases}

where

.. math::

  l = 0, 1, \ldots, k - 1, j = i - k + 1 + l, \ldots, i.

The value :math:`l` at the top right corner denotes the iteration number. We calculate the subdivision points based on :math:`\alpha` ratios.

In the steps :math:`l < (k - 1)`:

.. math::

  \textbf{s}(u) = \sum_{j=i-k+l+1}^i \textbf{d}_j^l(u) N_j^{k-l}(u),

when :math:`l = (k - 1)`:

.. math::

  \textbf{s}(u) = \textbf{d}_i^{k-1},

because

.. math::

  N_i^1(u) = \begin{cases}
  1, & \text{if } u \in [u_i, u_{i+1}), \\
  0, & \text{else}.
  \end{cases}

.. todo:: A pontok származtatási viszonyait ábrázolni!

The algorithm is similar to the de Casteljau algorithm, however there are some key differences.

* We do not apply subdivision in the ratio :math:`u:(1-u)`.
* The calculation of a point does not make necessary to use all of the control points. (It is the reason of the locally modifiable property.)
* We cannot use the algorithm for splitting the curve.

.. seealso::

   * https://en.wikipedia.org/wiki/De_Boor%27s_algorithm
   * https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/de-Boor.html

Derivative of the curve
-----------------------

The derivative of the B-spline curve when :math:`u \in [u_i, u_{i+1})`:

.. math::

  \dfrac{\mathrm{d}}{\mathrm{d}u} \textbf{s}(u) =
  (k - 1)\sum_{j=i-k+2}^i
  \dfrac{\textbf{d}_j - \textbf{d}_{j-1}}{u_{j+k-1} - u_j} N_j^{k-1}(u).

It means that, the hodograph of a B-spline curve of degree :math:`(k - 1)` is also a B-spline curve of degree :math:`(k - 2)`.

We can express the derivative based on the subdivision points of the de Boor algorithm:

.. math::

  \dfrac{k-1}{u_{i+1} - u_i}
  (\textbf{d}_i^{k-2}(u) - \textbf{d}_{i-1}^{k-2}(u)).


Theoretical questions
=====================

* How can we define the normalized B-spline base function?
* Let write the theorem of local support in the case of normalized B-spline base function!
* Let write the theorem of non-negativity in the case of normalized B-spline base function!
* Let write the theorem of partition of unity in the case of normalized B-spline base function!
* Let define the B-spline curve!
* What are the properties of the B-spline curves?


Programming exercises
=====================

Visualization and analysis of the curve
---------------------------------------

* Let implement an application which is able to visualize a B-spline curve for 8 control points!
* Let make possible to set the degree of the curve!
* Let highlight the modifiable part of the curve while the user move a control point!
* Let make possible to set the multiplicity of the points!
* Let highlight the corresponding curve segments and their theoretical convex hulls (for example by toggling the segments of the curve)!
* Let implement the de Boor algorithm!
* Let calculate and visualize the tangent and normal vector at the given point of the curve!


Available implementations
-------------------------

Let check the available implementations of the B-spline curves, for instance:

* https://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.BSpline.html

Further exercises
=================

* Let implement the interpolation by using B-spline curves!
* Let approximate the set of points by using B-spline curve of degree :math:`k`! (We assume a large number of sample points, which means that we cannot use them as control points.)
* Let examine and compare the algorithms (in the assumption of the same graphic quality) from the aspect of the number of required line segments!
* Let determine the self-intersection points of a B-spline curve!
* Let approximate the area of a closed B-spline curve!
* Let develope an algorithm which able to approximate a larger degree B-spline curve with a lower degree one! Let examine the accuracy!

