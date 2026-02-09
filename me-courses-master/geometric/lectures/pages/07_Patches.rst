*********************
Further surface types
*********************

Coons patches
=============

By analogy of the splines, it is also possible in the case of surfaces to describe the complex shapes by joining many, relatively simple surfaces to each others. We call them as patches. Their domains are usually rectangular or triangle shaped. As the result, we obtain some kind of curved-edged rectangles and triangles.

In the case of Coons patches, we would like to obtain a rectangular patch. Let consider the parameter intervals :math:`u \in [0, 1]` and :math:`v \in [0, 1]`! (It also can be written as :math:`(u, v) \in [0, 1] \times [0, 1]`, or :math:`(u, v) \in [0, 1]^2` shortly.)

Let consider the curves :math:`\textbf{a}_1(u), \textbf{a}_2(u), \textbf{b}_1(v), \textbf{b}_2(v)`! We try to find the surface :math:`\textbf{s}(u, v)` which fulfils the following conditions:

.. math::

  \begin{align}
  \textbf{s}(u, 0) &= \textbf{a}_1(u), \\
  \textbf{s}(u, 1) &= \textbf{a}_2(u), \\
  \textbf{s}(0, v) &= \textbf{b}_1(v), \\
  \textbf{s}(1, v) &= \textbf{b}_2(v). \\
  \end{align}

Bilinearly blended Coons patches
--------------------------------

By using the curves :math:`\textbf{a}_1` and :math:`\textbf{a}_2`, moreover :math:`\textbf{b}_1` and :math:`\textbf{b}_2`, we can obtain two ruled surfaces:

.. math::

  \begin{align}
  \textbf{l}_{a}(u, v) &= (1 - v)\textbf{a}_1(u) + v \textbf{a}_2(u), \\
  \textbf{l}_{b}(u, v) &= (1 - u)\textbf{b}_1(v) + u \textbf{b}_2(v). \\
  \end{align}

Let notice, that the surface :math:`\textbf{l}_{a}(u, v)` are contains only the curves :math:`\textbf{a}_1(u)` and :math:`\textbf{a}_2(u)`, while the surface :math:`\textbf{l}_{b}(u, v)` contains only the curves :math:`\textbf{b}_1(v)` and :math:`\textbf{b}_2(v)` in the general case.

Let consider the bilinear combination of the four vertices:

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

By using it, we can describe the Coons patch by the following formula:

.. math::

  \textbf{s}(u, v) = \textbf{l}_{a}(u, v) + \textbf{l}_{b}(u, v) - \textbf{l}_{ab}(u, v).

.. note::

   The bilinearity of this kind of patch only applies to the construction of the surface. Only the surface :math:`\textbf{l}_{ab}(u, v)` is the bilinear combination of the vertices. Therefore, the bilinearly blended Coons patch can be a bilinear surface just in a specific case.

.. seealso::

  * https://www.mathcurve.com/surfaces.gb/patchcoons/patchcoons.shtml

Bicubic Coons patches
---------------------

In the case of bilinearly blended Coons patches, we only provide the edges of the surfaces as curves. However, in many applications we have to join these patches to each others, which requires the cross border derivatives along the boundary curves.

We describe the boundary curves, as functions. Overall, we have

* :math:`\textbf{a}_1(u)`, :math:`\textbf{a}_2(u)`, :math:`\textbf{b}_1(v)`, :math:`\textbf{b}_2(v)` boundary curves,
* :math:`\textbf{a}_{1v}(u)`, :math:`\textbf{a}_{2v}(u)`, :math:`\textbf{b}_{1u}(v)`, :math:`\textbf{b}_{2u}(v)` cross border derivatives,
* :math:`\textbf{s}_{uv}(0, 0)`, :math:`\textbf{s}_{uv}(0, 1)`, :math:`\textbf{s}_{uv}(1, 0)`, :math:`\textbf{s}_{uv}(1, 1)` as twist vectors.

We try to find a surface :math:`\textbf{s}(u, v)` which fulfils the following conditions:

* :math:`\textbf{s}(u, 0) = \textbf{a}_1(u)`, :math:`\textbf{s}(u, 1) = \textbf{a}_2(u)`, :math:`\textbf{s}(0, v) = \textbf{b}_1(v)`, :math:`\textbf{s}(1, v) = \textbf{b}_2(v)`,
* :math:`\textbf{s}_v(u, 0) = \textbf{a}_{1v}(u)`, :math:`\textbf{s}_v(u, 1) = \textbf{a}_{2v}(u)`, :math:`\textbf{s}_u(0, v) = \textbf{b}_{1u}(v)`, :math:`\textbf{s}_u(1, v) = \textbf{b}_{2u}(v)`,

for all :math:`u, v \in [0, 1]`.

The solution differs from the case of bilinearly blended patches, because we cannot use straight line segments between the curves on the opposite sides. Instead, we will use Hermite arcs, which are able to take into account the cross border derivatives at the boundary curves.

Hermite bicubic patches
-----------------------

The Hermite bicubic patch is a special case of the bicubic patches. We choose Hermite arcs as boundary curves. All of the requirements against the surface remains the same. By using the Hermite arc, as a relatively simple curve, it provides many possibility to simplify the formulas.

.. note::

   In the case of joining patches to each others, the determination of the twist vectors causes a further problem which must be solved. There are various heuristic for solving the problem.

Bézier surfaces
===============

Previously, in the case of tensor product surfaces, we have spoken about the curves in general. When those curves are Bézeier curves, we obtain Bézier surfaces.

Definition
----------

Let consider the control points :math:`\{\textbf{b}_{ij}\}_{i=0,j=0}^{n,m}` (or in other word, the control net). The Bézier curve of degree :math:`(n, m)` is defined as

.. math::

  \textbf{s}(u, v) = \sum_{i=0}^{n} \sum_{j=0}^m \textbf{b}_{ij} B_i^n(u) B_j^m(v), \quad (u, v) \in [0, 1]^2.

Properties
----------

* The direction of the traversal of the control points does not matter. (*Symmetry of the surface generation*)
* The boundary lines are on the surface, however any other control points are not (in general). (*Approximative property*)
* Any isoparametric curve of the surface is Bézier curve (of degree :math:`n` and :math:`m` repsectively).
* We can calculate any point of the surface by using the de Casteljau algorithm. It does not matter, that we start with the curves of parameter :math:`u` or parameter :math:`v`. Both will results the same surface point, however the number of the necessary calculation steps can be differ (when :math:`n \neq m`).
* We can split the surface at any isoparametric line, by using the de Casteljau algorithm.
* The surface is invariant to the affine transformation of the control net.
* The surface is in the convex hull of the control net (or simply the control points). It is the consequence of the fact, that the surface points are the convex combinations of the control points.
* The surface is invariant to the affine transformation of the parameters.

We also can apply the degree elevation method similarly to the case of Bézier curves.

The spatial de Casteljau algorithm
----------------------------------

In the case of line segments, we have one parameters. Therefore, it results a simple :math:`u : (1 - u)` proportional subdivision.

In the three dimensional space, for triangles we have to use baricentric coordinates. Therefore, we can generalize the de Casteljau algorithm for surfaces, which will results Bézier triangles.

.. todo:: Saját példával, számításokkal is részletesen kidolgozni!

.. seealso::

  * https://blog.demofox.org/2019/12/07/bezier-triangles/
  * https://en.wikipedia.org/wiki/B%C3%A9zier_triangle

B-spline surfaces
=================

We can construct surfaces as the tensor product of B-spline curves.

Definition
----------

Let given the followings:

* :math:`\{\textbf{d}_{ij}\}_{i=0,j=0}^{n,m}` control points (or de Boor points),
* :math:`N_i^k` (:math:`i`-th degree :math:`(k-1)`) and :math:`N_j^L` (:math:`j`-th degree :math:`(l-1)`) normalized B-spline base function,
* :math:`u_0 \leq u_1 \leq \cdots \leq u_{n+k}` and :math:`v_0 \leq v_1 \leq \cdots v_{m+l}` knot values, where :math:`1 < k \leq (n + 1)` and :math:`1 < l \leq (m + 1)`.

The B-spline surface defined as

.. math::

  \textbf{s}(u, v) = \sum_{i=0}^{n} \sum_{j=0}^m \textbf{d}_{ij} N_i^n(u) N_j^m(v)

where :math:`(u, v) \in [u_{k-1}, u_{n+1}] \times [v_{l-1}, v_{m+1}]`.

Properties
----------

* The isoparametric lines are B-spline curves.
* The surface is locally modifiable. The modification of the control point :math:`\textbf{d}_{ij}` only affects the surface on the domain :math:`(u, v) \in [u_i, u_{i+k}] \times [v_j, v_{j+l}]`.
* An arbitrary :math:`(u, v) \in [u_i, u_{i+1}) \times [v_j, v_{j+1})` point of the curve is in the convex hull of the control points :math:`[\textbf{d}_{rs}]_{r=i-k+1,s=j-l+1}^{i,j}`.
* We can obtain the surface points by applying the de Boor algorithm. It is independent from the direction, however the number of the necessary calculation steps can be differ.

Rational surfaces
=================

We can use rational curves for tensor product surfaces.

* In the case of rational Bézier curves these are called rational Bézier surfaces.
* In the case of rational B-spline curves these are called rational B-spline surfaces (or NURBS).

Theoretical questions
=====================

* What are the Coons patches? How can we calculate its bilinear case?
* Let define the Bézier surface and describe their properties!
* Let define the B-spline surface and describe their properties!

Numerical exercises
===================

Let assume that we know the four boundary curves of a bilinearly blended Coons patches!

* Let check, that the curves are joining to each others properly!
* Let determine the point of the surface at parameter :math:`(u, v)`!

Programming exercises
=====================

Coons patches
-------------

* Let implement an application, which calculates and visualize a bilinearly blended Coons patches of 4 Hermite arcs!

Bézier surfaces
---------------

* Let implement an application, which displays a Bézier surface provided by a control net shaped :math:`4 \times 4`.
* Let make possible to show and hide the control net!
* Let implement two sliders for changing the pair of parameters :math:`(u, v)`, and visualize the corresponding isoparametric lines!
* Let visualize the tangent vectors of the isoparametric lines and the normal vector at the given point!
* Let estimate the area of the surface!
* Let implement the method of degree elevation!

Further exercises
=================

* Let approximate a sphere by using Bézier surfaces!
* Let show some possible ways of the description of spheres by using rational B-spline surfaces!
* Let analyze how the Bézier curves works in spherical coordinate system!
* Let analyze how the B-spline curves works in spherical coordinate system!
* Let assume that we have a large number of points in the space! Let implement an application, which approximate the cloud of points by a Bézier surface of degree :math:`(n, m)`! Let estimate the approximation error in the function of :math:`n` and :math:`m`!
* Let assume that, we have a Bézier surface of degree :math:`(n, m)`! Let check the self intersections of the surface and visualize the resulted points (along the visualization of the surface)!

.. todo:: Nem négyzetes és háromszöges foltok esete

.. todo:: Metaballs

