***************
Rational curves
***************

* There is an objective to describe most of the applied curves in a common, standardized way.
* NURBS - Non-Uniform Rational B-Spline

Rational Bézier curve
=====================

The rational Bézier curve is one of the many possible generalization of the Bézier curves.

Definition
----------

Let consider

* the :math:`\{\textbf{b}_i\}_{i=0}^n` control points, and
* the :math:`\{w_i\}_{i=0}^n` non-negative weights (:math:`\sum_{i=0}^n w_i \neq 0`).

We can define the degree :math:`n` rational Bézier curve in the following form:

.. math::

  \textbf{b}(t) =
  \sum_{i=0}^n \dfrac{w_i B_i^n(t)}{\sum_{j=0}^n w_j B_j^n(t)}
  \textbf{b}_i, \quad t \in [0, 1].

Properties of the curve
-----------------------

When we allow only non-negative weights, the curve remains in the convex hull of the control points.

.. admonition:: Proof

   Let consider the base functions in the expression of the curve:

   .. math::

      \dfrac{w_i B_i^n(t)}{\sum_{j=0}^n w_j B_j^n(t)}, \quad
      t \in [0, 1], i = 0, 1, \ldots, n.

   * We can see that this expression is non-negative.
   * When we summarize by the indices :math:`i \in [0, n]`, the denominator remains the same, and will be match the numerator. It means that, it results 1.

   Therefore, it is guaranteed that it is a convex combination. Therefore, the curve remains in the convex hull of the control points. :math:`\square`

Further properties:

* The curve remains the same, when we consider the control points (and its corresponding weights) in the opposite order.
* The curve is globally modifiable.
* It interpolates at the endpoints.
* The tangent line at the endpoint can be determined by the endpoint and the adjacent control point.
* Any line (plane or hyperplane in higher dimensions) intersects the curve at most as many points as the number of intersection points with the control polygon. (*variation diminishing property*)
* The curve is invariant to the affine transformation of the parameters.
* The curve is closed under the projective transformation of the control points.

Description of conics
---------------------

A segment of a cone can be results the following shapes:

* parabola,
* ellipse,
* hyperbola.

The second degree Bézier curve results a parabola, therefore it is given from the original construction.

Let consider a degree 2 Bézier curve, where :math:`w_0 = 1, w_2 = 1`! We can obtain the previously mentioned curve by the proper selection of the weight :math:`w_1`:

* :math:`0 < w_1 < 1` results ellipse,
* :math:`w_1 = 1` results parabola,
* :math:`w_1 > 1` results hyperbola.

Rational de Casteljau-algorithm
-------------------------------

A modified version of the de Casteljau algorithm is able to calculate the points of a rational Bézier curve. We have to calculate the weights for proportional subdivision in the function of the parameter :math:`t`. In the step :math:`r` it means:

.. math::

   w_i^r(t) = (1 - t)w_i^{r-1}(t) + t w_{i+1}^{r-1}(t).

We obtain the auxiliary points as

.. math::

   \textbf{b}_i^r(t) =
   (1-t)\dfrac{w_i^{r-1}(t)}{w_i^r(t)}{w_i^r(t)}\textbf{b}_i^{r-1} +
   t\dfrac{w_{i+1}^{r-1}(t)}{w_i^r(t)}\textbf{b}_{i+1}^{r-1}(t),

where

.. math::

   r = 1, \ldots, n, i = 0, 1, \ldots, n - r,

furthermore, in the step :math:`r = 0`:

.. math::

   w_i^0 = w_i, \textbf{b}_i^0 = \textbf{b}_i, \quad i = 0, 1, \ldots, n.

We get the point of the curve as :math:`\textbf{b}(t) = \textbf{b}_0^n(t)` (where :math:`t \in [0, 1]`).

.. note::

   This algorithm is also can split the curve.

Rational B-spline curve
=======================

We call the rational B-spline curves as NURBS (*Non-Uniform Rational B-Spline*). This name is mathematically not correct, because it does not exclude the uniform case. The name *not necessarily uniform* could be better, because the weights can be the same.

Definition
----------

Let denote

* :math:`N_i^k` the :math:`i`-th degree :math:`(k-1)` normalized B-spline base function,
* let given the control points (or *de Boor points*) :math:`\{\textbf{d}_i\}_{i=0}^n`,
* the knot values :math:`\{u_i\}_{i=0}^{n+k}`, and
* the :math:`\{w_i\}_{i=0}^n` non-negative weights (which are not identically zero).

We define the order :math:`k` (or in other words degree :math:`(k-1)`) rational B-spline curve as the following:

.. math::

   \textbf{s}(u) =
   \sum_{i=0}^n \textbf{d}_i
   \dfrac{w_i N_i^k(u)}{\sum_{j=0}^n w_j N_j^k(u)},
   u \in [u_{k-1}, u_{n+1}], 1 < k \leq n + 1.


.. seealso::

   * https://en.wikipedia.org/wiki/B%C3%A9zier_curve

Properties
----------

Fortunately, most of the properties of the B-spline curves are also valid in the case of rational B-spline curves.

* When the multiplicity at the endpoint is :math:`(k - 1)`, then the curve is interpolative at the endpoints.
* In the previous case, it also holds that the line determined by the endpoint and the adjacent point is the tangent line.
* The curve is locally modifiable.
* An arc of the curve :math:`\textbf{s}(u)`, :math:`u \in [u_i, u_{i+1})` (where :math:`i = k - 1, k, \ldots, n`) is in the convex hull of the control points :math:`\{\textbf{d}_j\}_{j=i-k+1}^i`. It also means that, the curve will be in the union of these convex hulls.
* Variation diminishing property: Any line (plane or hyperplane in higher dimensions) intersects the curve at most as many points as the number of intersection points with the control polygon.
* When the multiplicity is :math:`(k - 1)` at the endpoints, and there is no further inner control point, we obtain a Bézier curve.

Rational de Boor algorithm
--------------------------

Similarly to the de Casteljau algorithm, there is a rational version of the de Boor algoritm.

Application areas
=================

Scalable vector graphics
------------------------

* SVG standard, file format
* https://en.wikipedia.org/wiki/SVG

Its basic elements:

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Basic_Shapes
* https://www.w3.org/TR/SVG11/shapes.html

The Path command
~~~~~~~~~~~~~~~~

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths

Available operations:

* ``M``: Move To
* ``L``: Line To
* ``H``: Horizontal
* ``V``: Vertical
* ``Z``: Close Path

Their lower case counterparts use relative coordinates regarding to the last reached point.

Curve command
~~~~~~~~~~~~~

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths#curve_commands

HTML5 Canvas
------------

* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/bezierCurveTo

:math:`\rhd`
Let review the opportunities for drawing Bézier curves in various programming languages, libraries and frameworks!

PostScript
----------

* https://en.wikipedia.org/wiki/PostScript

TikZ
----

* https://en.wikipedia.org/wiki/PGF/TikZ
* https://tikz.net/

WaveFront OBJ format
--------------------

* https://paulbourke.net/dataformats/obj/

Vector graphics editors
-----------------------

* Inkscape: https://inkscape.org/
* CorelDRAW: https://www.coreldraw.com/en/

.. note::

   We can find functionality for drawing Bézier curves in raster editors also, for example the *path* tool of GIMP.

Design of font faces
--------------------

Font systems:

* https://en.wikipedia.org/wiki/PostScript
* https://en.wikipedia.org/wiki/Font_hinting
* https://en.wikipedia.org/wiki/OpenType
* https://fontforge.org/en-US/

Apple, font design:

* https://developer.apple.com/fonts/TrueType-Reference-Manual/RM01/Chap1.html
* https://developer.apple.com/fonts/TrueType-Reference-Manual/RM02/Chap2.html

.. http://chanae.walon.org/pub/ttf/ttf_glyphs.htm

.. todo:: Mutatni példát bázisfüggvény súlyozásos esetre, amely nem Bézier és nem B-Spline!

Theoretical questions
=====================

* How can we define the rational Bézier curves?
* What is the advantage of using rational Bézier curves related to the Bézier curves? What are the inherited properties?
* How can we describe conics by using rational Bézier curves?
* How can we define the rational B-spline curve?
* What are the properties of the rational B-spline curves?

Programming exercises
=====================

Rational Bézier curve
---------------------

* Let implement the calculation and visualization of the curve!
* Let make possible to modify the weights and knot values interactively!
* Let estimate the length of the curve!

Rational B-spline curve
-----------------------

* Let implement the calculation and visualization of the curve!
* Let make possible to modify the weights and knot values interactively!
* Let estimate the length of the curve!

Further exercises
=================

* Let examine the accurracy of the approximation of rational Bézier curves by using (uniform) Bézier curves!
* Let examine the accurracy of the approximation of rational B-spline curves by using (uniform) B-spline curves!
* Let given the set of points and we would like to fit a curve. (Let assume that, the curve is unable to pass over all off the sample points.) Let solve the curve fitting as an optimization problem, by finding the appropriate control points, knot values and weights!

