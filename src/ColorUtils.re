let hexToRgb = hex => {
  let r = int_of_string("0x" ++ String.sub(hex, 1, 2));
  let g = int_of_string("0x" ++ String.sub(hex, 3, 2));
  let b = int_of_string("0x" ++ String.sub(hex, 5, 2));
  (r, g, b);
};