open Reprocessing;

type rgb = (int, int, int);
type point = (int, int);
type shape = {
  points: array((point, point)),
  color: rgb,
  last: bool,
  strokeWeight: int,
};
type state = {
  restart: bool,
  backgroundColor: rgb,
  shapes: array(shape),
};

let size = 600;
let height = size;
let width = size;
let weights = [|200.0, 25.0, 40.0|];

let getRandomAmount = value =>
  int_of_float(floor(Random.float(1.0) *. float_of_int(value)));

let getPoint = (offset, width, y) => (
  offset + getRandomAmount(width),
  (-40) + y + getRandomAmount(20),
);

let createShape = (palette, count, index) => {
  let pointCount = getRandomAmount(10) + 10;
  let y = getRandomAmount(height);
  let offset = width / 4 + (getRandomAmount(2) - 1) * width / 8;
  let points =
    Array.init(pointCount / 2, _index =>
      (getPoint(offset, width, y), getPoint(offset, width, y))
    );
  let paletteIndex = NumberUtils.getRandomWeight(weights, Random.float(1.0));
  let strokeWeight =
    (float_of_int(y) /. float_of_int(height))
    ** 1.75
    *. float_of_int(getRandomAmount(height * 4))
    *. float_of_int(1 - index / count);
  {
    points,
    color: ColorUtils.hexToRgb(List.nth(palette, paletteIndex)),
    last: List.length(palette) - 1 === paletteIndex,
    strokeWeight: int_of_float(strokeWeight),
  };
};

let make = () => {
  let randomIndex = Random.int(List.length(Palettes.colors) - 1);
  let palette = List.nth(Palettes.colors, randomIndex);
  /* I know there must be a better way to do this, but I'm a Reason newb */
  let palette = [
    List.nth(palette, 0),
    List.nth(palette, 1),
    List.nth(palette, 2),
  ];

  let count = getRandomAmount(5) + 200;
  let shapes = Array.init(count, createShape(palette, count));
  {
    restart: false,
    backgroundColor: ColorUtils.hexToRgb(List.nth(palette, 0)),
    shapes,
  };
};

let drawPoints = (env, _index, pts) => {
  let (p1, p2) = pts;
  let (p1x, p1y) = p1;
  let (p2x, p2y) = p2;
  let p1x = - width / 2 + p1x * 4;
  let p2x = - width / 2 + p2x * 4;
  Draw.line(~p1=(p1x, p1y), ~p2=(p2x, p2y), env);
};

let drawShape = (env, _index, {points, color, last, strokeWeight}) => {
  let (r, g, b) = color;
  let color = Utils.color(~r, ~g, ~b, ~a=last ? 13 : 191);
  Draw.fill(color, env);
  Draw.stroke(color, env);
  Draw.strokeWeight(strokeWeight / 2, env);
  Draw.strokeCap(Square, env);
  Array.iteri(drawPoints(env), points);
};

let setup = env => {
  Env.size(~width=size, ~height=size, env);
  make();
};

let draw = ({restart, backgroundColor, shapes}, env) => {
  let (r, g, b) = backgroundColor;
  Draw.background(Utils.color(~r, ~g, ~b, ~a=255), env);
  Array.iteri(drawShape(env), shapes);

  if (restart) {
    make();
  } else {
    {restart, backgroundColor, shapes};
  };
};

let mouseDown = (state, _env) => {...state, restart: true};
let mouseUp = (state, _env) => {...state, restart: false};

run(~setup, ~draw, ~mouseDown, ~mouseUp, ());