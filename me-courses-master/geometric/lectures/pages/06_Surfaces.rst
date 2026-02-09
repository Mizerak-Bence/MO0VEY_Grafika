********
Surfaces
********

Description methods
===================

* Explicit: :math:`z = f(x, y)`
* Implicit: :math:`F(x, y, z) = 0`
* Parametric: :math:`\textbf{s}: \mathbb{R}^2 \rightarrow \mathbb{R}^3`

:math:`\rhd` Let describe a half sphere surface by using all of the three method!

:math:`\rhd` Let consider the possibilities of the changing between different description methods!

Explicit surfaces
-----------------

Similarly to the case of interpolation curves, we can find functions of two variables, which are interpolates over some given interpolation points.

Let consider the following simple method as an example!

Let given the points :math:`(x_0, y_0, z_0), (x_1, y_1, z_1), \ldots, (x_n, y_n, z_n)` in the space! Let assume that there are no multiple :math:`z` value for at the same :math:`x` value! It also must hold to the case of coordinate :math:`y`!

Let solve the interpolation problem for the points :math:`(x_0, z_0), (x_1, z_1), \ldots, (x_n, z_n)` on the plane! Let denote this interpolation function :math:`f_x(x, z)`! We can obtain an interpolation surface independently from :math:`y`.

Similarly, let solve the interpolation for the points :math:`(y_0, z_0), (y_1, z_1), \ldots, (y_n, z_n)`, which will results an interpolation surface, independently from :math:`x`.

It is easy to see, that both of the surfaces contains the interpolation points (from the direction of the given axis). The mean of these surfaces also solves the interpolation problem.

.. note::

   Let notice, that any direction can be used, when the problem remains interpolation problem from that direction.

Parametric surfaces
-------------------

Let given a domain :math:`G \subseteq \mathbb{R}^2`. We call the set of points, provided by the two-variable function

.. math::

   \textbf{s}(u, v) = \begin{bmatrix}
   r_x(u, v) \\
   r_y(u, v) \\
   r_z(u, v) \\
   \end{bmatrix}, (u, v) \in G
 
as a surface (in differential geometric term), when

* :math:`\textbf{s}(u, v)` is bijective and continuous,
* its (at least) partial derivatives exists on :math:`G`,
* the :math:`\dfrac{\partial}{\partial u}\textbf{s}(u, v)` and :math:`\dfrac{\partial}{\partial v}\textbf{s}(u, v)` vectors are linearly independent for all :math:`(u, v) \in G`.

Properties
==========

We can determine various properties which are belongs to any point of the surface. Some of them will be described in the following subsections.

Tangent plane
-------------

Let consider an arbitrary point :math:`\textbf{s}(u, v)` of the surface! The tangent lines of any curves on the surface is on the common plane. We call this plane as *tangent plane*.

Let consider the isoparametric lines of :math:`u` and :math:`v`! We can calculate the tangent plane by

.. math::

   \textbf{s}_u (u, v) = \dfrac{\partial}{\partial u}\textbf{s}(u, v),
   \quad
   \textbf{s}_v (u, v) = \dfrac{\partial}{\partial v}\textbf{s}(u, v).

Let choose an arbitrary curve on the surface :math:`\textbf{r}(t) = \textbf{s}(u(t), v(t))`! The formula

.. math::

   \dfrac{\mathrm{d}}{\mathrm{d}t}\textbf{r}(t) =
   \dfrac{\mathrm{d}}{\mathrm{d}t}\textbf{s}(u(t), v(t)) =
   \dfrac{\partial}{\partial u}\textbf{s}(u, v)\dfrac{\mathrm{d}}{\mathrm{d}t}u(t) +
   \dfrac{\partial}{\partial v}\textbf{s}(u, v)\dfrac{\mathrm{d}}{\mathrm{d}t}v(t)

means that any tangent line at the given point can be expressed as the linear combination of the vectors :math:`\textbf{s}_u` and :math:`\textbf{s}_v`. Therefore these are in the same plane (determined by these vectors).

Normal vector
-------------

The vector which is perpendicular to the tangent plane is the normal vector, and can be obtained as

.. math::

    \textbf{s}_u(u, v) \times \textbf{s}_v(u, v).

Its normalized (unit length) form:

.. math::

   \textbf{n}(u, v) = \dfrac
   {\textbf{s}_u(u, v) \times \textbf{s}_v(u, v)}
   {\lVert \textbf{s}_u(u, v) \times \textbf{s}_v(u, v) \rVert}.

:math:`\rhd` How can we write the equation of the tangent plane using the normal vector?

Twist-vector
------------

We call the partial derivate

.. math::

   \dfrac{\partial^2}{\partial v \partial u}\textbf{s}(u, v)

of the surface :math:`\textbf{s}` at the point :math:`\textbf{s}(u, v)` as twist vector.

Ruled surfaces
==============

We call ruled surface, the surface which contains a straight line for its any point. The straight lines are called generators (or rulings) of the surface.

A possible description method:

.. math::

   \textbf{s}(u, v) = \textbf{r}(u) + v \textbf{e}(u), \quad
   u \in [u_0, u_1], v \in [v_0, v_1],

where

* :math:`\textbf{r}`: arbitrary space curve,
* :math:`\textbf{e}`: a function of :math:`\mathbb{R} \rightarrow \mathbb{R}^3`, which provide the directions of the generators.

As an alternative approach, we can describe ruled surfaces as the convex combination of two curves, which has the same parametrization:

.. math::

   \textbf{s}(u, v) = (1 - v)\textbf{r}_1(u) + v\textbf{r}_2(u),
   \quad v \in [0, 1], u \in [u_0, u_1].

(It can be considered as the linear interpolation of two curves.)

Swept surfaces
==============

Let consider the spatial curve :math:`\textbf{r}(u), u \in [u_0, u_1]`!

* Let assume that we use homogeneous coordinate system, which means that, we can use :math:`4 \times 4` real matrices for describing the transformations.
* Let define a matrix in the function of :math:`v \in [v_0, v_1]` as :math:`M(v) \in \mathbb{R}^{4 \times 4}`! (The values of the transformation matrix must be change continuously in the function of parameter :math:`v`.)

We can define a wide range of surfaces by using them in the form of:

.. math::

   \textbf{s}(u, v) = \textbf{M}(v) \cdot \textbf{r}(u),
   \quad u \in [u_0, u_1], v \in [v_0, v_1].

Tensor product surfaces
=======================

* We can use some kind of points (control or interpolation points) for describing curves.
* It is possible to move those points on various curves. These are the control paths.
* The control path also can be some kind of spatial curve, which has been provided by control (or interpolation) points.

Let define

* :math:`\{\textbf{c}_i\}_{i=0}^n` control points,
* and their base functions :math:`\{F_i(u): u \in [u_0, u_1]\}_{i=0}^n`!

We can define a curve of the surface as

.. math::

   \textbf{r}(u) = \sum_{i=0}^n \textbf{c}_i F_i(u), \quad u \in [u_0, u_1].

For "moving" the control points, we can use also bases functions, which will results the control points :math:`\textbf{c}_i` in the function of parameter :math:`v`. Therefore, the control points are in a matrix of :math:`\{\textbf{a}_{i,j}\}_{j=0}^m`, which results

.. math::

    \textbf{c}_i(v) =
    \sum_{j=0}^m \textbf{a}_{i,j}G_j(v), \quad v \in [v_0, v_1], i = 0, 1, \ldots, n.

By substituting into the original description of the curve :math:`\textbf{r}(u)`:

.. math::

   \begin{align}
   \textbf{s}(u, v) &=
   \sum_{i=0}^n \left(
   \sum_{j=0}^m \textbf{a}_{i,j}G_j(v)
   \right) F_i(u) \\
   &= \sum_{i=0}^n \sum_{j=0}^m \textbf{a}_{i,j} F_i(u) G_j(v),
   \end{align}

where :math:`u \in [u_0, u_1], v \in [v_0, v_1]`.

We call these kind of surfaces as tensor product surfaces.

* The points :math:`[a_ij]_{i=0,j=0}^{n,m}` are the *control points*,
* the resulted net is the *control net* of the surface.

.. todo:: Polygon mesh konverzió, triangulization

Theoretical questions
=====================

* How can we describe the surfaces (from mathematical standpoints)?
* What is the differential geometric definition of the surface?
* What are the commonly used point-wise properties of the surfaces?
* What are the ruled surfaces?
* How can we obtain swepts surfaces?
* Let introduce the construction of tensor product surfaces!

Numerical exercises
===================

Let given a surface in its parametric (or explicit) form. (In the case of explicit form, at the first step, write the parametric form!)

* Let determine the point of the surface at the point :math:`(u, v)`!
* Let calculate the normal vector at the given point!
* Let write the equation of the tangent surface!
* Let calculate the twist vector!

Programming exercises
=====================

Examination of explicit surfaces
--------------------------------

Let consider the explicit function :math:`f(x, y) = x^3+(x-2)^2+(y+1)^3-(y+2)^2`!

* Let plot the surface on the domain :math:`(x, y) \in [-5, 5]^2` (for example by using https://academo.org/demos/3d-surface-plotter)!
* Let calculate the normal vector and the tangent plane at the point :math:`(1, 2)`!

Programming exercises
=====================

Analysis of the properties of the surface
-----------------------------------------

Let implement an application, which are able to plot a parametric surface above a fixed (rectangular) domain!

* Try to emphasize the shape of the surface by using colours and lights!
* Let visualize the point of the surface, the isoparametric lines and the normal vector for a given parameter :math:`(u, v)`!

Further exercises
=================

* Let thinking about the generalization of the polyline approximation of the Bézier curve for tensor product surfaces!

