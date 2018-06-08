open Reprocessing;

type state = {restart: bool};

let size = 1024;
let height = size;
let width = size;
let weights = [|200.0, 25.0, 40.0|];
let setup = env => {
  Env.size(~width=size, ~height=size, env);
  {restart: false};
};

let getRandomAmount = value =>
  int_of_float(floor(Random.float(1.0) *. float_of_int(value)));

let draw = ({restart}, env) => {
  if (restart) {
    let randomIndex = Random.int(List.length(Palettes.colors) - 1);
    let palette = List.nth(Palettes.colors, randomIndex);
    let (r, g, b) = ColorUtils.hexToRgb(List.nth(palette, 0));
    Draw.background(Utils.color(~r, ~g, ~b, ~a=255), env);
    let count = getRandomAmount(5) + 200;
    for (_i in 0 to count) {
      let pointCount = getRandomAmount(10) + 10;
      let y = getRandomAmount(height);
      let offset = width / 4 + (getRandomAmount(2) - 1) * width / 8;
      let points =
        Array.init(pointCount / 2, _pos =>
          (
            (
              offset + getRandomAmount(width),
              (-20) + y + (-20) + getRandomAmount(20),
            ),
            (
              offset + getRandomAmount(width),
              (-20) + y + (-20) + getRandomAmount(20),
            ),
          )
        );

      let paletteIndex =
        NumberUtils.getRandomWeight(weights, Random.float(1.0));
      let (r, g, b) = ColorUtils.hexToRgb(List.nth(palette, paletteIndex));
      let last = List.length(palette) - 1 === paletteIndex;
      Draw.fill(Utils.color(~r, ~g, ~b, ~a=last ? 12 : 191), env);
      
      Array.iteri(
        (_index, pts) => {
          let (p1, p2) = pts;
          let (p1x, p1y) = p1;
          let (p2x, p2y) = p2;
          let width = abs(p2x - p1x);
          let height = abs(p2y - p1y);
          Draw.rect(~pos=(p1x, p1y), ~width, ~height, env);
        },
        points
      );
    };
  };
  
  {restart: restart};
};

let mouseDown = (_state, _env) => {restart: true};
let mouseUp = (_state, _env) => {restart: false};

run(~setup, ~draw, ~mouseDown, ~mouseUp, ());