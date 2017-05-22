type map 'a 'b =
  | JSMap 'a 'b;

external create_map : unit => map 'a 'b = "Map" [@@bs.new];

external set : map 'a 'b => 'a => 'b => unit = "set" [@@bs.send];

external get_internal : map 'a 'b => 'a => Js.undefined 'b = "get" [@@bs.send];

let get k v => Js.Undefined.to_opt (get_internal k v);

let merge_in_pair acc (k, v) => {
  set acc k v;
  acc
};

let create (pairs: array ('a, 'b)) => {
  let empty_map = create_map ();
  Array.fold_left merge_in_pair empty_map pairs
};
