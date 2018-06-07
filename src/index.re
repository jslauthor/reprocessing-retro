open Reprocessing;

type state = {
  restart: bool
};

let size = 1024;
let weights = [|200.0, 25.0, 40.0|];
let setup = env => {
  Env.size(~width=size, ~height=size, env);
  {restart: false};
};

let draw = ({restart}, env) => {
  if (restart) {
    let palette =
      List.nth(Palettes.colors, Random.int(List.length(Palettes.colors) - 1));
    
    let (r, g, b)  = ColorUtils.hexToRgb(List.nth(palette, 0));
    print_endline(string_of_int(r) ++ " " ++ string_of_int(g) ++ " " ++ string_of_int(b));
    /* print_endline(string_of_int(NumberUtils.getRandomWeight(weights, Random.float(1.0)))); */
  };
  Draw.background(Utils.color(~r=199, ~g=217, ~b=229, ~a=255), env);
  Draw.fill(Utils.color(~r=41, ~g=166, ~b=244, ~a=255), env);
  Draw.rect(~pos=(150, 150), ~width=300, ~height=300, env);
  {restart: restart};
};

let mouseDown = (_state, _env) => {restart: true};
let mouseUp = (_state, _env) => {restart: false};

/* print_endline(string_of_int(NumberUtils.getRandomWeight(weights, Random.float(1.0))));
print_endline(string_of_int(NumberUtils.getRandomWeight(weights, Random.float(1.0))));
print_endline(string_of_int(NumberUtils.getRandomWeight(weights, Random.float(1.0))));
print_endline(List.nth(palette, NumberUtils.getRandomWeight(weights, Random.float(1.0)) - 1)); */

run(~setup, ~draw, ~mouseDown, ~mouseUp, ());