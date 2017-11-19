type map('a, 'b) =
  | JSMap('a, 'b);

[@bs.new] external create_map : unit => map('a, 'b) = "Map";
[@bs.send] external set : (map('a, 'b), 'a, 'b) => unit = "set";
[@bs.send] [@bs.return nullable] external get : (map('a, 'b), 'a) => option('b) = "get";

let merge_in_pair = (acc, (k, v)) => {
  set(acc, k, v);
  acc
};

let create = (pairs: array(('a, 'b))) => {
  let empty_map = create_map();
  Js.Array.reduce(merge_in_pair, empty_map, pairs)
};
