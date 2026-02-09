/**
 * BSpline
 */
class BSpline
{
  /**
   * Construct a new B-Spline.
   */
  constructor()
  {
    this._points = [];
    this._knots = [];
  }

  /**
   * Set the points and knots of the B-Spline.
   */
  setPointsAndKnots(points, knots)
  {
    // TODO: Proper error handling needed here!
    this._points = points;
    this._knots = knots;
  }

  /**
   * Calculate the normalized B-spline base function.
   */
  calcNormBase(i, k, u)
  {
    if (k == 1) {
      if (this._knots[i] <= u && u < this._knots[i + 1]) {
        return 1;
      } else {
        return 0;
      }
    } else {
      let a = (u - this._knots[i]) / (this._knots[i + k - 1] - this._knots[i]);
      let b = (this._knots[i + k] - u) / (this._knots[i + k] - this._knots[i + 1]);
      let na = this.calcNormBase(i, k - 1, u);
      let nb = this.calcNormBase(i + 1, k - 1, u);
      return a * na + b * nb;
    }
  }

  /**
   * Calculate the polyline approximation of the curve.
   */
  calcPolyline(k)
  {
    let polyline = [];
    let n = this._points.length;
    let u = this._knots[k - 1];
    while (u < this._knots[n]) {
      let x = 0.0;
      let y = 0.0;
      // let s = 0.0;
      for (let i = 0; i < this._points.length; i++) {
        let w = this.calcNormBase(i, k, u);
        // s += w;
        x += w * this._points[i].x;
        y += w * this._points[i].y;
      }
      // console.log(s);
      polyline.push({x: x, y: y});
      u += 0.1;
    }
    return polyline;
  }
}

