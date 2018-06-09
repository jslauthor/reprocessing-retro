open Reprocessing;

type rgb = (int, int, int);
type point = (int, int);
type shape = {
  points: array((point, point)),
  color: rgb,
  last: bool,
};
type state = {
  restart: bool,
  backgroundColor: rgb,
  shapes: array(shape),
};

let size = 1024;
let height = size;
let width = size;
let weights = [|200.0, 25.0, 40.0|];

let getRandomAmount = value =>
  int_of_float(floor(Random.float(1.0) *. float_of_int(value)));

let couldBeNegative = () => Random.float(1.0) > 0.5 ? 1 : (-1);

let getPoint = (offset, width, y) => (
  getRandomAmount(offset) * couldBeNegative() + getRandomAmount(width),
  (-20) + y + (-20) + getRandomAmount(20),
);

let createShape = (palette, _pos) => {
  let pointCount = getRandomAmount(10) + 10;
  let y = getRandomAmount(height);
  let offset = width / 4 + (getRandomAmount(2) - 1) * width / 8;
  let points =
    Array.init(pointCount / 2, _pos =>
      (getPoint(offset, width, y), getPoint(offset, width, y))
    );
  let paletteIndex = NumberUtils.getRandomWeight(weights, Random.float(1.0));
  {
    points,
    color: ColorUtils.hexToRgb(List.nth(palette, paletteIndex)),
    last: List.length(palette) - 1 === paletteIndex,
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

  let shapes = Array.init(getRandomAmount(5) + 200, createShape(palette));
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
  let width = abs(p2x - p1x);
  let height = abs(p2y - p1y);
  Draw.rect(~pos=(p1x, p1y), ~width, ~height, env);
};

let drawShape = (env, _index, {points, color, last}) => {
  let (r, g, b) = color;
  Draw.fill(Utils.color(~r, ~g, ~b, ~a=last ? 10 : 80), env);
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