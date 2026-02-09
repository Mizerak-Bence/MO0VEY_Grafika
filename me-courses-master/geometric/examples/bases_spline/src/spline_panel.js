const POINT_RADIUS = 10;

/**
 * A panel for drawing splines.
 */
class SplinePanel extends Panel
{
  /**
   * Construct a new spline panel.
   */
  constructor(mock)
  {
    super();
    this._points = [
      {x: 200, y: 200},
      {x: 400, y: 200},
      {x: 200, y: 400},
      {x: 400, y: 400},
      {x: 600, y: 200},
      {x: 800, y: 200},
      {x: 600, y: 400},
      {x: 800, y: 400}
    ];
    this._selectedPoint = null;
    this._bspline = new BSpline();
    this._order = 2;
    this._polyline = [];
  }

  /**
   * Handle the mouse down event.
   */
  onMouseDown(mouse)
  {
    console.log("Mouse down");
    console.log(mouse);
    this._selectedPoint = this.findPoint(mouse.x, mouse.y);
  }

  /**
  * Handle the mouse move event.
  */
  onMouseMove(mouse)
  {
    //console.log("Mouse move");
    //console.log(mouse);
    if (this._selectedPoint != null) {
      this._selectedPoint.x = mouse.x;
      this._selectedPoint.y = mouse.y;
      this.updateSpline();
    }
    this.requireRedraw();
  }

  /**
   * Handle the mouse up event.
   */
  onMouseUp(mouse)
  {
    console.log("Mouse up");
    console.log(mouse);
    this._selectedPoint = null;
  }

  /**
   * Handle the key down event.
   */
  onKeyDown(key)
  {
    console.log("Key down");
    console.log(key);
    if (key.key == "i") {
      this._order++;
      this.updateSpline();
      this.requireRedraw();
    } else if (key.key == "k") {
      this._order--;
      if (this._order < 2) {
        this._order = 2;
      }
      this.updateSpline();
      this.requireRedraw();
    }
  }

  /**
   * Handle the key up event.
   */
  onKeyUp(key)
  {
    console.log("Key up");
    console.log(key);
  }

  /**
   * Find a control point at the given coordinates.
   */
  findPoint(x, y)
  {
    for (var point of this._points) {
      const dx = point.x - x;
      const dy = point.y - y;
      let distance = Math.sqrt(dx * dx + dy * dy);
      if (distance < POINT_RADIUS) {
        return point;
      }
    }
    return null;
  }

  /**
   * Update the spline.
   */
  updateSpline()
  {
    let knots = [];
    for (let i = 0; i < this._points.length + this._order; ++i) {
      knots.push(i);
    }
    this._bspline.setPointsAndKnots(this._points, knots);
    let polyline = this._bspline.calcPolyline(this._order);
    this._polyline = polyline;
  }

  /**
   * Draw the content of the panel.
   */
  draw(context)
  {
    context.fillStyle = "#FFF";
    context.fillRect(0, 0, this.width, this.height);
    this.drawPoints(context);
    context.strokeStyle = "#AAA";
    context.lineWidth = 1;
    context.beginPath();
    context.moveTo(this._points[0].x, this._points[0].y);
    for (let i = 1; i < this._points.length; i++) {
      context.lineTo(this._points[i].x, this._points[i].y);
    }
    context.stroke();
    this.drawPolyline(context, this._polyline);
  }

  /**
   * Draw the control points.
   */
  drawPoints(context)
  {
    for (const point of this._points) {
      this.drawPoint(context, point);
    }
  }

  /**
   * Draw a control point.
   */
  drawPoint(context, point)
  {
    context.strokeStyle = "#00F";
    context.lineWidth = 1;
    context.beginPath();
    context.moveTo(point.x - POINT_RADIUS, point.y);
    context.lineTo(point.x + POINT_RADIUS, point.y);
    context.stroke()
    context.beginPath();
    context.moveTo(point.x, point.y - POINT_RADIUS);
    context.lineTo(point.x, point.y + POINT_RADIUS);
    context.stroke()
  }

  /**
   * Draw a polyline.
   */
  drawPolyline(context, points)
  {
    if (points.length == 0) {
      return;
    }
    context.strokeStyle = "#F00";
    context.lineWidth = 2;
    context.moveTo(points[0].x, points[0].y);
    context.beginPath();
    for (let i = 1; i < points.length; i++) {
      context.lineTo(points[i].x, points[i].y);
    }
    context.stroke();
  }
}

